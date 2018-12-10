 /*
****************************************************************************
* Copyright (C) 2014 - 2015 Bosch Sensortec GmbH
*
* bmp280_support.c
* Date: 2015/03/27
* Revision: 1.0.5
*
* Usage: Sensor Driver support file for BMP280 sensor
*
****************************************************************************
* License:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
* OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility
* for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
**************************************************************************/
/*---------------------------------------------------------------------------*/
/* Includes*/
/*---------------------------------------------------------------------------*/
#include "bmp280.h"
#include "bosch_support_FZI.h"
//#include "../../libs/i2cfunctions.h"
#include <stdio.h>
//#include "../../config.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "config.h"

#ifdef CONFIGSYSTEM	== INEARV3_2
#include "../Config/config_inEar_v3_2.h"
#elif	CONFIGSYSTEM == INEARV4_0
#include "../Config/config_inEar_v4_0.h"
#endif


#define BMP280_HI_SPI_FREQ  CONFIG_BMP280_HI_SPI_FREQ
#define BMP280_LO_SPI_FREQ  CONFIG_BMP280_LO_SPI_FREQ
//#define BMP280_USART      CONFIG_BMP280_USART
#define BMP280_LOC       	CONFIG_BMP280_LOC
#define BMP280_CMUCLOCK     CONFIG_BMP280_CMUCLOCK
#define BMP280_GPIOPORT     CONFIG_BMP280_GPIO


#define BMP280_MOSIPIN      CONFIG_BMP280_MOSIPIN
#define BMP280_MISOPIN      CONFIG_BMP280_MISOPIN
#define BMP280_CSPIN      CONFIG_BMP280_CSPIN
#define BMP280_CLKPIN     CONFIG_BMP280_CLKPIN
//#define CS_DOWN         BMP280_CS_DOWN
//#define CS_UP         BMP280_CS_UP



/*********************** START INITIALIZATION ************************/
  /*  Based on the user need configure I2C or SPI interface.
   *  It is example code to explain how to use the bma2x2 API*/
   #ifdef BMP280
  I2C_routine();
  /*SPI_routine(); */
  #endif
/*--------------------------------------------------------------------------*
 *  This function used to assign the value/reference of
 *  the following parameters
 *  I2C address
 *  Bus Write
 *  Bus read
 *  Chip id
*-------------------------------------------------------------------------*/

#define BMP280_I2C_BUS 0


/************** I2C/SPI buffer length ******/

#define I2C_BUFFER_LEN 8
#define SPI_BUFFER_LEN 5
#define BUFFER_LENGTH 0xFF
#define MASK_DATA 0x80
#define REGISTER_MASK 0x7F

//Bosch lib bug:
#define BMP280_ONE_U8X 		0x01
#define BMP280_TWO_U8X		0x02

  /*-------------------------------------------------------------------*
* This is a sample code for read and write the data by using I2C/SPI
* Use either I2C or SPI based on your need
* The device address defined in the bmp180.c
*
*-----------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*
* The following function is used to map the I2C bus read, write, delay and
* device address with global structure bmp280_t
*-------------------------------------------------------------------------*/
//s8 I2C_routine(void) {
// 	#define BMP280_I2C_BUS 1

/*--------------------------------------------------------------------------*
 *  By using bmp280 the following structure parameter can be accessed
 *  Bus write function pointer: BMP280_WR_FUNC_PTR
 *  Bus read function pointer: BMP280_RD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *--------------------------------------------------------------------------*/
//  bmp280.bus_write = BMP280_I2C_bus_write;
//  bmp280.bus_read = BMP280_I2C_bus_read;
//  bmp280.dev_addr = BMP280_I2C_ADDRESS2;
//  bmp280.delay_msec = BMP280_delay_msek;
//
//  return BMP280_INIT_VALUE;
//
//}


 /* \Brief: The function is used as I2C bus write
 *  \Return : Status of the I2C write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *    will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8  BMI160_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
  s32 iError = BMP280_INIT_VALUE;

  writeI2cRegister(BMP280_I2C_BUS, dev_addr, reg_addr, *reg_data);
  /*
  * Please take the below function as your reference for
  * write the data using I2C communication
  * "IERROR = I2C_WRITE_STRING(DEV_ADDR, ARRAY, CNT+1)"
  * add your I2C write function here
  * iError is an return value of I2C read function
  * Please select your valid return value
  * In the driver SUCCESS defined as BMP280_INIT_VALUE
    * and FAILURE defined as -1
  * Note :
  * This is a full duplex operation,
  * The first read data is discarded, for that extra write operation
  * have to be initiated. For that cnt+1 operation done in the I2C write string function
  * For more information please refer data sheet SPI communication:
  */


  return (s8)iError;
}


 /* \Brief: The function is used as I2C bus read
 *  \Return : Status of the I2C read
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be read
 *  \param reg_data : This data read from the sensor, which is hold in an array
 *  \param cnt : The no of data to be read
 */
s8  BMI160_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
  s32 iError = BMP280_INIT_VALUE;

  /* Please take the below function as your reference
   * for read the data using I2C communication
   * add your I2C rad function here.
   * "IERROR = I2C_WRITE_READ_STRING(DEV_ADDR, ARRAY, ARRAY, 1, CNT)"
   * iError is an return value of SPI write function
   * Please select your valid return value
   * In the driver SUCCESS defined as BMP280_INIT_VALUE
     * and FAILURE defined as -1
   */
  readI2cMultipleRegisters(reg_data, cnt, BMP280_I2C_BUS, dev_addr, reg_addr);
  return (s8)iError;
}


//#ifdef USE_SPI


/*---------------------------------------------------------------------------*
 * The following function is used to map the SPI bus read, write and delay
 * with global structure bmp280_t
 *--------------------------------------------------------------------------*/
//s8 SPI_routine(void) {
///*--------------------------------------------------------------------------*
// *  By using bmp280 the following structure parameter can be accessed
// *  Bus write function pointer: BMP280_WR_FUNC_PTR
// *  Bus read function pointer: BMP280_RD_FUNC_PTR
// *  Delay function pointer: delay_msec
// *--------------------------------------------------------------------------*/
//
//  bmp280.bus_write = BMP280_SPI_bus_write;
//  bmp280.bus_read = BMP280_SPI_bus_read;
//  bmp280.delay_msec = BMP280_delay_msek;
//
//  return BMP280_INIT_VALUE;
//}


/*  \Brief: The function is used as SPI bus read
 *  \Return : Status of the SPI read
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be read
 *  \param reg_data : This data read from the sensor, which is hold in an array
 *  \param cnt : The no of data to be read
 */
s8  BMP280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
s32 iError=BMP280_INIT_VALUE;
u8 array[SPI_BUFFER_LEN]={BUFFER_LENGTH};
u8 stringpos;
/*	For the SPI mode only 7 bits of register addresses are used.
The MSB of register address is declared the bit what functionality it is
read/write (read as 1/write as BMP280_INIT_VALUE)*/
array[BMP280_INIT_VALUE] = reg_addr|MASK_DATA;/*read routine is initiated register address is mask with 0x80*/
/*
* Please take the below function as your reference for
* read the data using SPI communication
* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
* add your SPI read function here
* iError is an return value of SPI read function
* Please select your valid return value
* In the driver SUCCESS defined as BMP280_INIT_VALUE
* and FAILURE defined as -1
* Note :
* This is a full duplex operation,
* The first read data is discarded, for that extra write operation
* have to be initiated. For that cnt+1 operation done in the SPI read
* and write string function
* For more information please refer data sheet SPI communication:
*/
GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
if (dev_addr == 0)
	{
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	USART_SpiTransfer(CONFIG_SENSOR_USART, reg_addr);
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data++) = USART_SpiTransfer(CONFIG_SENSOR_USART, 0xFF);
	}
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	}
//else if (dev_addr == 1)
//	{
//	//GPIO_PinOutClear(gpioPortD, 3);
//	USART_SpiTransfer(USART1, reg_addr);
//	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data++) = USART_SpiTransfer(USART1, 0xFF);
//	}
//	//GPIO_PinOutSet(gpioPortD, 3);
//	}
////GPIO_PinOutSet(gpioPortE, 13);
return (s8)iError;
}


/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *    will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8  BMP280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN * BMP280_TWO_U8X];
	u8 stringpos = BMP280_INIT_VALUE;
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		/* the operation of (reg_addr++)&0x7F done: because it ensure the
		   BMP280_INIT_VALUE and 1 of the given value
		   It is done only for 8bit operation*/
		//array[stringpos * BMP280_TWO_U8X] = (reg_addr++) & REGISTER_MASK; //Alt von Bosch ?
		array[stringpos * BMP280_TWO_U8X] = (reg_addr) & REGISTER_MASK;
		array[stringpos * BMP280_TWO_U8X + BMP280_ONE_U8X] = *(reg_data + stringpos);
	}
	/* Please take the below function as your reference
	 * for write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS defined as BMP280_INIT_VALUE
     * and FAILURE defined as -1
	 */

	 if (dev_addr == 0)
	 	{
		 GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos]);
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos+1]);
		}
		 GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	 	}
//	 else if (dev_addr == 1)
//	 	{
//		 //GPIO_PinOutClear(gpioPortD, 3);
//		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
//		 USART_SpiTransfer(USART1, array[stringpos]);
//		 USART_SpiTransfer(USART1, array[stringpos+1]);
//		}
//		 //GPIO_PinOutSet(gpioPortD, 3);
//	 	}
	return (s8)iError;
}




s8  BME680_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
s32 iError=BMP280_INIT_VALUE;
u8 array[SPI_BUFFER_LEN]={BUFFER_LENGTH};
u8 stringpos;
/*	For the SPI mode only 7 bits of register addresses are used.
The MSB of register address is declared the bit what functionality it is
read/write (read as 1/write as BMP280_INIT_VALUE)*/
array[BMP280_INIT_VALUE] = reg_addr; //|MASK_DATA;/*read routine is initiated register address is mask with 0x80*/
/*
* Please take the below function as your reference for
* read the data using SPI communication
* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
* add your SPI read function here
* iError is an return value of SPI read function
* Please select your valid return value
* In the driver SUCCESS defined as BMP280_INIT_VALUE
* and FAILURE defined as -1
* Note :
* This is a full duplex operation,
* The first read data is discarded, for that extra write operation
* have to be initiated. For that cnt+1 operation done in the SPI read
* and write string function
* For more information please refer data sheet SPI communication:
*/
GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
if (dev_addr == 0)
	{
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	USART_SpiTransfer(CONFIG_SENSOR_USART, reg_addr);
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data++) = USART_SpiTransfer(CONFIG_SENSOR_USART, 0xFF);
	}
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	}
//else if (dev_addr == 1)
//	{
//	//GPIO_PinOutClear(gpioPortD, 3);
//	USART_SpiTransfer(USART1, reg_addr);
//	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data++) = USART_SpiTransfer(USART1, 0xFF);
//	}
//	//GPIO_PinOutSet(gpioPortD, 3);
//	}
////GPIO_PinOutSet(gpioPortE, 13);
return (s8)iError;
}


/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *    will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8  BME680_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN * BMP280_TWO_U8X];
	u8 stringpos = BMP280_INIT_VALUE;
	array[0] = (reg_addr) & REGISTER_MASK;
	for (stringpos = 0; stringpos < ((2*cnt)-1); stringpos++) {
		/* the operation of (reg_addr++)&0x7F done: because it ensure the
		   BMP280_INIT_VALUE and 1 of the given value
		   It is done only for 8bit operation*/
		//array[stringpos * BMP280_TWO_U8X] = (reg_addr++) & REGISTER_MASK; //Alt von Bosch ?
		array[stringpos+1] = *(reg_data + stringpos);
	}
	/* Please take the below function as your reference
	 * for write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS defined as BMP280_INIT_VALUE
     * and FAILURE defined as -1
	 */

	 if (dev_addr == 0)
	 	{
		 GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos]);
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos+1]);
		}
		 GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	 	}
//	 else if (dev_addr == 1)
//	 	{
//		 //GPIO_PinOutClear(gpioPortD, 3);
//		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
//		 USART_SpiTransfer(USART1, array[stringpos]);
//		 USART_SpiTransfer(USART1, array[stringpos+1]);
//		}
//		 //GPIO_PinOutSet(gpioPortD, 3);
//	 	}
	return (s8)iError;
}

s8  BMI160_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
s32 iError=BMP280_INIT_VALUE;
u8 array[SPI_BUFFER_LEN]={BUFFER_LENGTH};
u8 stringpos;
/*	For the SPI mode only 7 bits of register addresses are used.
The MSB of register address is declared the bit what functionality it is
read/write (read as 1/write as BMP280_INIT_VALUE)*/
array[BMP280_INIT_VALUE] = reg_addr|MASK_DATA;/*read routine is initiated register address is mask with 0x80*/
/*
* Please take the below function as your reference for
* read the data using SPI communication
* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
* add your SPI read function here
* iError is an return value of SPI read function
* Please select your valid return value
* In the driver SUCCESS defined as BMP280_INIT_VALUE
* and FAILURE defined as -1
* Note :
* This is a full duplex operation,
* The first read data is discarded, for that extra write operation
* have to be initiated. For that cnt+1 operation done in the SPI read
* and write string function
* For more information please refer data sheet SPI communication:
*/
GPIO_PinOutClear(CONFIG_BMI_PORT_CS, CONFIG_BMI_PIN_CS);
if (dev_addr == 0)
	{
	GPIO_PinOutClear(CONFIG_BMI_PORT_CS, CONFIG_BMI_PIN_CS);
	USART_SpiTransfer(CONFIG_BMI_USART, reg_addr);
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data++) = USART_SpiTransfer(CONFIG_BMI_USART, 0xFF);
	}
	GPIO_PinOutSet(CONFIG_BMI_PORT_CS, CONFIG_BMI_PIN_CS);
	}
//else if (dev_addr == 1)
//	{
//	//GPIO_PinOutClear(gpioPortD, 3);
//	USART_SpiTransfer(USART1, reg_addr);
//	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data++) = USART_SpiTransfer(USART1, 0xFF);
//	}
//	//GPIO_PinOutSet(gpioPortD, 3);
//	}
////GPIO_PinOutSet(gpioPortE, 13);
return (s8)iError;
}


/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *    will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8  BMI160_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN * BMP280_TWO_U8X];
	u8 stringpos = BMP280_INIT_VALUE;
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		/* the operation of (reg_addr++)&0x7F done: because it ensure the
		   BMP280_INIT_VALUE and 1 of the given value
		   It is done only for 8bit operation*/
		//array[stringpos * BMP280_TWO_U8X] = (reg_addr++) & REGISTER_MASK; //Alt von Bosch ?
		array[stringpos * BMP280_TWO_U8X] = (reg_addr) & REGISTER_MASK;
		array[stringpos * BMP280_TWO_U8X + BMP280_ONE_U8X] = *(reg_data + stringpos);
	}
	/* Please take the below function as your reference
	 * for write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS defined as BMP280_INIT_VALUE
     * and FAILURE defined as -1
	 */

	 //if (dev_addr == 0)
	 	{
		 GPIO_PinOutClear(CONFIG_BMI_PORT_CS, CONFIG_BMI_PIN_CS);
		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
		 USART_SpiTransfer(CONFIG_BMI_USART, array[stringpos]);
		 USART_SpiTransfer(CONFIG_BMI_USART, array[stringpos+1]);
		}
		 GPIO_PinOutSet(CONFIG_BMI_PORT_CS, CONFIG_BMI_PIN_CS);
	 	}
//	 else if (dev_addr == 1)
//	 	{
//		 //GPIO_PinOutClear(gpioPortD, 3);
//		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
//		 USART_SpiTransfer(USART1, array[stringpos]);
//		 USART_SpiTransfer(USART1, array[stringpos+1]);
//		}
//		 //GPIO_PinOutSet(gpioPortD, 3);
//	 	}
	return (s8)iError;
}


/*  Brief : The delay routine
 *  \param : delay in ms
*/

s8  BMP388_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
s32 iError=BMP280_INIT_VALUE;
u8 array[SPI_BUFFER_LEN]={BUFFER_LENGTH};
u8 stringpos;
/*	For the SPI mode only 7 bits of register addresses are used.
The MSB of register address is declared the bit what functionality it is
read/write (read as 1/write as BMP280_INIT_VALUE)*/
array[BMP280_INIT_VALUE] = reg_addr; //|MASK_DATA;/*read routine is initiated register address is mask with 0x80*/
/*
* Please take the below function as your reference for
* read the data using SPI communication
* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
* add your SPI read function here
* iError is an return value of SPI read function
* Please select your valid return value
* In the driver SUCCESS defined as BMP280_INIT_VALUE
* and FAILURE defined as -1
* Note :
* This is a full duplex operation,
* The first read data is discarded, for that extra write operation
* have to be initiated. For that cnt+1 operation done in the SPI read
* and write string function
* For more information please refer data sheet SPI communication:
*/
GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
if (dev_addr == 0)
	{
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	USART_SpiTransfer(CONFIG_SENSOR_USART, reg_addr);
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data++) = USART_SpiTransfer(CONFIG_SENSOR_USART, 0xFF);
	}
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	}
//else if (dev_addr == 1)
//	{
//	//GPIO_PinOutClear(gpioPortD, 3);
//	USART_SpiTransfer(USART1, reg_addr);
//	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data++) = USART_SpiTransfer(USART1, 0xFF);
//	}
//	//GPIO_PinOutSet(gpioPortD, 3);
//	}
////GPIO_PinOutSet(gpioPortE, 13);
return (s8)iError;
}


/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register, will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *    will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8  BMP388_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN * BMP280_TWO_U8X];
	u8 stringpos = BMP280_INIT_VALUE;
	array[0] = (reg_addr) & REGISTER_MASK;
	for (stringpos = 0; stringpos < ((2*cnt)-1); stringpos++) {
		/* the operation of (reg_addr++)&0x7F done: because it ensure the
		   BMP280_INIT_VALUE and 1 of the given value
		   It is done only for 8bit operation*/
		//array[stringpos * BMP280_TWO_U8X] = (reg_addr++) & REGISTER_MASK; //Alt von Bosch ?
		array[stringpos+1] = *(reg_data + stringpos);
	}
	/* Please take the below function as your reference
	 * for write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS defined as BMP280_INIT_VALUE
     * and FAILURE defined as -1
	 */

	 if (dev_addr == 0)
	 	{
		 GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos]);
		 USART_SpiTransfer(CONFIG_SENSOR_USART, array[stringpos+1]);
		}
		 GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	 	}
//	 else if (dev_addr == 1)
//	 	{
//		 //GPIO_PinOutClear(gpioPortD, 3);
//		for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos=stringpos+2) {
//		 USART_SpiTransfer(USART1, array[stringpos]);
//		 USART_SpiTransfer(USART1, array[stringpos+1]);
//		}
//		 //GPIO_PinOutSet(gpioPortD, 3);
//	 	}
	return (s8)iError;
}

void  SENSOR_delay_msek(uint32_t ms)
{
  /*Here you can write your own delay routine*/
	RTCDRV_Delay( ms >>1 );
}


//char SPI_READ_WRITE_STRING(unsigned char *values, char length)
//{
//  char reg_addr = values[0];
//  uint8_t x = 1;
//
//    CS_DOWN; // CS PIN DOWN start
//
//    USART_SpiTransfer(BMP280_USART, reg_addr);
//
//    do
//      {
//      /* Transmit a dummy data block, "length" times. */
//
//      BMP280_USART->TXDATA = 0xff;
//
//        while (!(BMP280_USART->STATUS & USART_STATUS_TXC));
//
//        values[x++] = BMP280_USART->RXDATA;
//
//      } while (x < length);
//
//    CS_UP; // CS PIN UP finish
//
//  return(BMP280_ZERO_U8X);
//}

//char SPI_WRITE_STRING(unsigned char *values, char length)
//{
//  uint8_t reg_addr = values[0];
//  uint8_t x = 1; // first data to be written is values[1]
//
//  uint16_t txValue; // for SPI
//  uint32_t framectrl, ctrl;
//
//  /* Save current configuration. */
//  framectrl = BMP280_USART->FRAME;
//  ctrl      = BMP280_USART->CTRL;
//
//  CS_DOWN; // CS PIN DOWN start
//
//
//    /* Set frame length to 16 bit. This will increase the effective data rate. */
//    BMP280_USART->FRAME = (BMP280_USART->FRAME & (~_USART_FRAME_DATABITS_MASK))
//                           | USART_FRAME_DATABITS_SIXTEEN;
//    BMP280_USART->CTRL |= USART_CTRL_BYTESWAP;
//
//    /* Clear send and receive buffers. */
//    BMP280_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
//
//    do
//    {
//    /* Transmit a "length" dummy data block to the SD-Card. */
//
//      txValue  = values[x++];
//      txValue |= values[x++] << 8;
//
//      while (!(BMP280_USART->STATUS & USART_STATUS_TXBL));
//
//      BMP280_USART->TXDOUBLE = txValue;
//    } while (x < length);
//
//    while (!(BMP280_USART->STATUS & USART_STATUS_TXBL));
//
//    /* Transmit two dummy CRC bytes. */
//    BMP280_USART->TXDOUBLE = 0xFFFF;
//
//    while (!(BMP280_USART->STATUS & USART_STATUS_TXC));
//
//    /* Clear send and receive buffers. */
//    BMP280_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
//
//    CS_UP; // CS PIN UP finish
//
//    /* Restore old settings. */
//    BMP280_USART->FRAME = framectrl;
//    BMP280_USART->CTRL  = ctrl;
//
//    return(BMP280_ZERO_U8X);

//}
