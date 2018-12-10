/**************************************************************************//**
 * @file i2functions.c
 * @brief I2C Library for Wearable Plattform v1
 * @author czimmer@fzi.de
 * @version 0.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2014-08-27	0.1		czimmer 	Initial Version, Write 1, Read 1-2 Register
 * 2014-10-17	0.11	czimmer 	Added GPIO Clock Init in setupI2C
 * 2014-10-18	0.2		czimmer 	External Config, Fast-Mode Support, Refactoring
 *
 * *****************************************************************************/

#include "i2cfunctions.h"

/** Suggested default config for I2C init structure. */
#define I2C_INIT_FAST                                                    \
  { true,                    /* Enable when init done */                    \
    true,                    /* Set to master mode */                       \
    0,                       /* Use currently configured reference clock */ \
    I2C_FREQ_FAST_MAX,		 /* Set to fast rate assuring being */      \
                             /* within I2C spec */                          \
    i2cClockHLRAsymetric     /* Set to use 6:3 low/high duty cycle */       \
  }

/***************************************************************************
 * @brief
 *   Setup I2C
 *
 * @details
 *    Setup I2C0 for BMI160
/**************************************************************************/
void setupI2C(void)
{
	  /* Enable clock for GPIO */
	  CMU_ClockEnable(cmuClock_GPIO, true);
	  CMU_ClockEnable(cmuClock_I2C0, true);
	// $[I2C0 I/O setup]
	/* Set up SCL */
	  I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SCLPEN;
	  I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SCLLOC_MASK))
			| CONFIG_BMI_LOC_SCL;
	  /* Set up SDA */
	  I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SDAPEN;
	  I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SDALOC_MASK))
			| CONFIG_BMI_LOC_SDA;
	  // [I2C0 I/O setup]$

	  /* Pin SDA is configured to Open-drain with pull-up and filter */
	  GPIO_PinModeSet(CONFIG_BMI_I2C0_PORT_SDA, CONFIG_BMI_I2C0_PIN_SDA, gpioModeWiredAndPullUpFilter, 0);

	  /* Pin SCL is configured to Open-drain with pull-up and filter */
	  GPIO_PinModeSet(CONFIG_BMI_I2C0_PORT_SCL, CONFIG_BMI_I2C0_PIN_SCL, gpioModeWiredAndPullUpFilter, 0);

	  GPIO_PinModeSet(CONFIG_BMI_I2C0_PORT_ADD, CONFIG_BMI_I2C0_PIN_ADD, gpioModePushPull, 0);
	  GPIO_PinModeSet(CONFIG_BMI_I2C0_PORT_PROT, CONFIG_BMI_I2C0_PIN_PROT, gpioModePushPull, 1);

	  // $[I2C0 initialization]
	  I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	  init.enable = 1;
	  init.master = 1;
	  init.freq = I2C_FREQ_STANDARD_MAX;
	  init.clhr = i2cClockHLRStandard;
	  I2C_Init(I2C0, &init);
      // [I2C0 initialization]$

}


static int32_t I2C_WriteUserReg2(I2C_TypeDef *i2c, uint8_t addr, int8_t data)
{
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[2];
  uint8_t                    i2c_write_data[2];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE;
  /* Select command to issue */
  i2c_write_data[0] = 0x50;
  i2c_write_data[1] = data;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 2;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 0;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    return((int) ret);
  }

  return((int) 0);
}

/***************************************************************************
 * @brief
 *   Reads I2C Register
 *
 * @details
 *    Reads one 8-Bit I2C Register
 *
 * @param[in] i2cBus
 *   I2C Bus used for the device
 *
 * @param[in] deviceAddr
 *   I2C address for sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] regAddr
 *   Register to read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
uint8_t readI2cRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr){

	I2C_TransferSeq_TypeDef transfer;
	I2C_TransferReturn_TypeDef ret;
	uint8_t dataBuffer[2];

	transfer.addr = deviceAddr<<1; // bitshift because last bit is W/R
	transfer.flags = I2C_FLAG_WRITE_READ;
	transfer.buf[0].len = 1;
	transfer.buf[0].data = &regAddr;
	transfer.buf[1].len = 1;
	transfer.buf[1].data = dataBuffer;

	// Select used Bus and Read Data
	if (i2cBus == 0)
	{
		ret = I2C_TransferInit(I2C0, &transfer);
			while (ret == i2cTransferInProgress)
			{
				ret = I2C_Transfer(I2C0);
			}
	}

	return dataBuffer[0];
}

/***************************************************************************
 * @brief
 *   Reads a burst of 2 Registers from I2C
 *
 * @details
 *    Reads two 8-Bit I2C Register
 *
 * @param[in] i2cBus
 *   I2C Bus used for the device
 *
 * @param[in] deviceAddr
 *   I2C address for sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] regAddr
 *   Register to read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
uint16_t readI2c2Register(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr){

	I2C_TransferSeq_TypeDef transfer;
	I2C_TransferReturn_TypeDef ret;
	uint8_t dataBuffer[2];

	transfer.addr = deviceAddr<<1; // bitshift because last bit is W/R
	transfer.flags = I2C_FLAG_WRITE_READ;
	transfer.buf[0].len = 1;
	transfer.buf[0].data = &regAddr;
	transfer.buf[1].len = 2;
	transfer.buf[1].data = dataBuffer;

	// Select used Bus and Read Data
	if (i2cBus == 0)
	{
		ret = I2C_TransferInit(I2C0, &transfer);
			while (ret == i2cTransferInProgress)
			{
				ret = I2C_Transfer(I2C0);
			}
	}

	return ((dataBuffer[0] << 8) | dataBuffer[1]);
}

/***************************************************************************
 * @brief
 *   Writes in an I2C Register
 *
 * @details
 *    writes 8-Bit in a I2C Register
 *
 * @param[in] i2cBus
 *   I2C Bus used for the device
 *
 * @param[in] deviceAddr
 *   I2C address for sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] regAddr
 *   Register to write.
 *
 * @param[in] regValue
 *   Value to write.
 *
 ******************************************************************************/
int writeI2cRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr, uint8_t regValue){

	I2C_TransferSeq_TypeDef transfer;
	I2C_TransferReturn_TypeDef ret;
	uint8_t dataBuffer[2];

	transfer.addr = deviceAddr<<1; // bitshift because last bit is W/R
	transfer.flags = I2C_FLAG_WRITE;
	dataBuffer[0] = regAddr;
	dataBuffer[1] = regValue;
	transfer.buf[0].len = 2;
	transfer.buf[0].data = dataBuffer;
	transfer.buf[1].len = 1;
	transfer.buf[1].data = dataBuffer;

	// Select used Bus and Read Data
	if (i2cBus == 0)
	{
		ret = I2C_TransferInit(I2C0, &transfer);
		while (ret == i2cTransferInProgress)
		{
			ret = I2C_Transfer(I2C0);
		}
	}

	return ret;
}

/***************************************************************************
 * @brief
 *   Writes in multiple consecutive I2C Registers
 *
 * @details
 *    writes 8-Bit data in a I2C Registers
 *
 * @param[in] i2cBus
 *   I2C Bus used for the device
 *
 * @param[in] deviceAddr
 *   I2C address for sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] regAddr
 *   Register to write.
 *
 * @param[in] regValue
 *   Value to write.
 *
 ******************************************************************************/
int writeI2cMultipleRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr, uint8_t *data, uint8_t size){

	I2C_TransferSeq_TypeDef transfer;
	I2C_TransferReturn_TypeDef ret;
	uint8_t dataBuffer[size+1];

	transfer.addr = deviceAddr<<1; // bitshift because last bit is W/R
	transfer.flags = I2C_FLAG_WRITE;
	// Prepare dataBuffer contaning regAddress | DATA | DATA | ...
	dataBuffer[0] = regAddr; // 1st data to be sent is the register address where data will be written
	for(int i = 0; i < size; i++)
	{
		dataBuffer[i+1] = data[i]; //*(data+i);
	}
	transfer.buf[0].len = size+1; // regAddress + data
	transfer.buf[0].data = dataBuffer;
//	transfer.buf[1].len = size;
//	transfer.buf[1].data = dataBuffer;

	// Select used Bus and Read Data
	if (i2cBus == 0)
	{
		ret = I2C_TransferInit(I2C0, &transfer);
		while (ret == i2cTransferInProgress)
		{
			ret = I2C_Transfer(I2C0);
		}
	}

//	if(ret == i2cTransferDone)
//		    return transfer.buf[1].len;
//	else
//			return ret;

	return ret;
}
