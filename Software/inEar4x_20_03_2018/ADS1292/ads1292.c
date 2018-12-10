
#include "ads1292.h"
#include "config.h"

void ads1292_Init(){
	/* CS Pin initial auf High setzen */
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);

	/* CLKSEL Pin auf high setzen, um interne Clock auszuwählen */
	GPIO_PinOutSet(CONFIG_ADS1292_CLK_SEL_PORT, CONFIG_ADS1292_CLK_SEL_PIN);
	RTCDRV_Delay(10);

	ads1292_Reset();
	RTCDRV_Delay(100);
//	ads1292_Disable_Start();
//	ads1292_Enable_Start();

//	ads1292_Hard_Stop();
	ads1292_Stop_Read_Data_Continuous();//
	ads1292_Start_Data_Conv_Command();
	ads1292_Soft_Stop();
	RTCDRV_Delay(50);
	ads1292_Stop_Read_Data_Continuous();		// SDATAC command
	RTCDRV_Delay(300);

	ads1292_Reg_Write(CONFIG1, SAMPLE_RATE_500); 			//Set sampling rate to 500 SPS
	RTCDRV_Delay(10);
	ads1292_Reg_Write(CONFIG2, TEST_SIGNAL_OFF);		//Lead-off comp off, test signal disabled
	RTCDRV_Delay(10);
	ads1292_Reg_Write(LOFF, 0b00010000);		//Lead-off defaults
	RTCDRV_Delay(10);
	ads1292_Reg_Write(CH1SET, CH1_GAIN12);		//Ch 1 enabled, gain 12, connected to electrode in
	RTCDRV_Delay(10);
	ads1292_Reg_Write(CH2SET, CH2_INPUT_SHORTED);		//Ch 2 power-down, Input shorted
	RTCDRV_Delay(10);
	ads1292_Reg_Write(RLDSENS, 0b00100011);		//RLD settings: fmod/16, RLD enabled, RLD inputs from Ch1 only
	RTCDRV_Delay(10);
	ads1292_Reg_Write(LOFFSENS, 0x00);			//LOFF settings: all disabled
	RTCDRV_Delay(10);
												//Skip register 8, LOFF Settings default
	ads1292_Reg_Write(RESP1, 0x02);				//Respiration: MOD/DEMOD turned only, phase 0
	RTCDRV_Delay(10);
	ads1292_Reg_Write(RESP2, 0b00000011);		//Respiration: Calib OFF, respiration freq defaults
	RTCDRV_Delay(10);

	ads1292_SPI_Command_Data(OFFSETCAL);		// Offset berechnen
	RTCDRV_Delay(10);

	ads1292_Start_Read_Data_Continuous();
	RTCDRV_Delay(10);

	ads1292_Start_Data_Conv_Command();//

//	ads1292_Enable_Start();

}

void ads1292_Reset(){
	GPIO_PinOutSet(CONFIG_ADS1292_RESET_PORT, CONFIG_ADS1292_RESET_PIN);
	RTCDRV_Delay(100);
	GPIO_PinOutClear(CONFIG_ADS1292_RESET_PORT, CONFIG_ADS1292_RESET_PIN);
	RTCDRV_Delay(100);
	GPIO_PinOutSet(CONFIG_ADS1292_RESET_PORT, CONFIG_ADS1292_RESET_PIN);
	RTCDRV_Delay(100);
}

void ads1292_Reg_Write (uint8_t READ_WRITE_ADDRESS, uint8_t DATA){
	switch (READ_WRITE_ADDRESS)
	  {
	    case 1:
			DATA = DATA & 0x87;
		    break;
	    case 2:
			DATA = DATA & 0xFB;
		    DATA |= 0x80;
		    break;
	    case 3:
		    DATA = DATA & 0xFD;
		    DATA |= 0x10;
		    break;
	    case 7:
		    DATA = DATA & 0x3F;
		    break;
	    case 8:
			DATA = DATA & 0x5F;
		    break;
	    case 9:
		    DATA |= 0x02;
		    break;
	    case 10:
		    DATA = DATA & 0x87;
		    DATA |= 0x01;
		    break;
	    case 11:
		    DATA = DATA & 0x0F;
		    break;
	    default:
		    break;
	}

	uint8_t dataToSend = READ_WRITE_ADDRESS | WREG;
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);

	USART_SpiTransfer(CONFIG_SENSOR_USART, dataToSend);
	USART_SpiTransfer(CONFIG_SENSOR_USART, 0x00);
	USART_SpiTransfer(CONFIG_SENSOR_USART, DATA);

	RTCDRV_Delay(2);
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
}

//void ads1292_Disable_Start(){
//	GPIO_PinOutClear(START_PORT, START_PIN);
//	RTCDRV_Delay(20);
//}
//
//void ads1292_Enable_Start(){
//	GPIO_PinOutSet(START_PORT, START_PIN);
//	RTCDRV_Delay(20);
//}
//
//void ads1292_Hard_Stop(){
//	GPIO_PinOutClear(START_PORT, START_PIN);
//	RTCDRV_Delay(100);
//}

void ads1292_Start_Data_Conv_Command(){
	ads1292_SPI_Command_Data(START);
}

void ads1292_Soft_Stop(){
	ads1292_SPI_Command_Data(STOP);
}

void ads1292_Start_Read_Data_Continuous(){
	ads1292_SPI_Command_Data(RDATAC);
}

void ads1292_Stop_Read_Data_Continuous(){
	ads1292_SPI_Command_Data(SDATAC);
}

void ads1292_read_data(uint8_t* buf, uint8_t len) {
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	for (uint8_t i = 0; i < len; i++) {
		buf[i] = USART_SpiTransfer(CONFIG_SENSOR_USART, 0xFF);
	}
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
}

void rdata_command_ads1292(uint8_t* p) {
  //using namespace ADS129x;
  //while (digitalRead(IPIN_DRDY) == HIGH);
	  while (GPIO_PinInGet(CONFIG_ADS1292_RDY_PORT, CONFIG_ADS1292_RDY_PIN) == 1){ //ToDo unschön, noch mit GPIO Interrupt machen
	  }
//	  adc_send_command_leave_cs_active(RDATA);
//
//	  sendSample();
//	  memcpy(p+2, serialBytes+9, 1);
//	  memcpy(p+1, serialBytes+10, 1);
//	  memcpy(p,   serialBytes+11, 1);

  //WiredSerial.println();
}

void ads1292_SPI_Command_Data(uint8_t data_in){
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	RTCDRV_Delay(2);

	USART_SpiTransfer(CONFIG_SENSOR_USART, data_in);
	RTCDRV_Delay(2);
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
}
