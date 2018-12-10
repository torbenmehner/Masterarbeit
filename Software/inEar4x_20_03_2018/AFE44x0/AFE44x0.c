/*
 * AFE44x0.c
 *
 *  Created on: 20.10.2014
 *      Author: krause
 */
#include "AFE44x0.h"



void AFE44x0_Init(){
	/*Soft Reset*/
	AFE44x0_Write(CONTROL0, 0x08);

//	/*Writing Default Data into Registers*/
//	AFE44x0_Write(LED2STC, 0x00B498);
//	AFE44x0_Write(LED2ENDC, 0x00F05E);
//	AFE44x0_Write(LED2LEDSTC, 0x00B448);
//	AFE44x0_Write(LED2LEDENDC, 0x00F05F);
//	AFE44x0_Write(ALED2STC, 0x000050);
//	AFE44x0_Write(ALED2ENDC, 0x003C16);
//
//	AFE44x0_Write(LED1STC, 0x003C68);
//	AFE44x0_Write(LED1ENDC, 0x00782E);
//	AFE44x0_Write(LED1LEDSTC, 0x003C18);
//	AFE44x0_Write(LED1LEDENDC, 0x00782F);
//	AFE44x0_Write(ALED1STC, 0x007880);
//	AFE44x0_Write(ALED1ENDC, 0x00B446);
//
//	AFE44x0_Write(LED2CONVST, 0x000006);
//	AFE44x0_Write(LED2CONVEND, 0x003C17);
//	AFE44x0_Write(ALED2CONVST, 0x003C1E);
//	AFE44x0_Write(ALED2CONVEND, 0x00782F);
//
//	AFE44x0_Write(LED1CONVST, 0x007836);
//	AFE44x0_Write(LED1CONVEND, 0x00B447);
//	AFE44x0_Write(ALED1CONVST, 0x00B44E);
//	AFE44x0_Write(ALED1CONVEND, 0x00F05F);
//
//	AFE44x0_Write(ADCRSTSTCT0, 0x000000);
//	AFE44x0_Write(ADCRSTENDCT0, 0x000005);
//
//	AFE44x0_Write(ADCRSTSTCT1, 0x003C18);
//	AFE44x0_Write(ADCRSTENDCT1, 0x003C1D);
//
//	AFE44x0_Write(ADCRSTSTCT2, 0x007830);
//	AFE44x0_Write(ADCRSTENDCT2, 0x007835);
//	AFE44x0_Write(ADCRSTSTCT3, 0x00B448);
//	AFE44x0_Write(ADCRSTENDCT3, 0x00B44D);
//
//	AFE44x0_Write(PRPCOUNT, 0x00F061);		//65H z0x00F061
//	AFE44x0_Write(CONTROL1, 0x000101);
//	//AFE44x0_Write(LEDCNTRL,0x011455);
//    AFE44x0_Write(LEDCNTRL, 0x018080);
//    AFE44x0_Write(TIA_AMB_GAIN, 0x141FE);
//    uint32_t GainRegVal = 0b000000100100001011111110; //0b000010100100001011111110;
//	//cancellationCurrent = 0b00000000;
//	//GainRegVal |= (cancellationCurrent << 16);
//	AFE44x0_Write(TIA_AMB_GAIN, GainRegVal);
//	AFE44x0_Write(CONTROL2, 0x1);


	   	  AFE44x0_Write(CONTROL0,0x000000);

	     AFE44x0_Write(CONTROL0,0x000008);

	     AFE44x0_Write(TIAGAIN,0x000000); // CF = 5pF, RF = 500kR
	     AFE44x0_Write(TIA_AMB_GAIN,0x000001);

	     AFE44x0_Write(LEDCNTRL,0x001414);
	     AFE44x0_Write(CONTROL2,0x000000); // LED_RANGE=100mA, LED=50mA
	     AFE44x0_Write(CONTROL1,0x010707); // Timers ON, average 3 samples

	     AFE44x0_Write(PRPCOUNT, 0X001F3F);

	    AFE44x0_Write(LED2STC, 0X001770);
	    AFE44x0_Write(LED2ENDC,0X001F3E);
	    AFE44x0_Write(LED2LEDSTC,0X001770);
	    AFE44x0_Write(LED2LEDENDC,0X001F3F);
	    AFE44x0_Write(ALED2STC, 0X000000);
	    AFE44x0_Write(ALED2ENDC, 0X0007CE);
	    AFE44x0_Write(LED2CONVST,0X000002);
	    AFE44x0_Write(LED2CONVEND, 0X0007CF);
	    AFE44x0_Write(ALED2CONVST, 0X0007D2);
	    AFE44x0_Write(ALED2CONVEND,0X000F9F);

	    AFE44x0_Write(LED1STC, 0X0007D0);
	    AFE44x0_Write(LED1ENDC, 0X000F9E);
	    AFE44x0_Write(LED1LEDSTC, 0X0007D0);
	    AFE44x0_Write(LED1LEDENDC, 0X000F9F);
	    AFE44x0_Write(ALED1STC, 0X000FA0);
	    AFE44x0_Write(ALED1ENDC, 0X00176E);
	    AFE44x0_Write(LED1CONVST, 0X000FA2);
	    AFE44x0_Write(LED1CONVEND, 0X00176F);
	    AFE44x0_Write(ALED1CONVST, 0X001772);
	    AFE44x0_Write(ALED1CONVEND, 0X001F3F);

	    AFE44x0_Write(ADCRSTSTCT0, 0X000000);
	    AFE44x0_Write(ADCRSTENDCT0,0X000000);
	    AFE44x0_Write(ADCRSTSTCT1, 0X0007D0);
	    AFE44x0_Write(ADCRSTENDCT1, 0X0007D0);
	    AFE44x0_Write(ADCRSTSTCT2, 0X000FA0);
	    AFE44x0_Write(ADCRSTENDCT2, 0X000FA0);
	    AFE44x0_Write(ADCRSTSTCT3, 0X001770);
	    AFE44x0_Write(ADCRSTENDCT3, 0X001770);
	    AFE44x0_Write(CONTROL2, 0x1);
}

void AFE44x0_Write(uint8_t address, uint32_t data){
	uint8_t dummy;

	/* Select Chip */
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);;

	/*Send Address*/
	dummy = USART_SpiTransfer(CONFIG_SENSOR_USART, address & 0xFF);
	/*Send first Byte */
	dummy = USART_SpiTransfer(CONFIG_SENSOR_USART, (data >> 16) & 0xFF);
	/*Send second Byte */
	dummy = USART_SpiTransfer(CONFIG_SENSOR_USART, (data >> 8) & 0xFF);
	/*Send last Byte */
	dummy = USART_SpiTransfer(CONFIG_SENSOR_USART, data & 0xFF);

	/* Deselect Chip */
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);;
}


int32_t AFE44x0_Read(uint8_t address){
	uint8_t tempbuff[3];
	uint8_t dummy;
	int32_t value = 0;

	/* Set bit 1 in CONTROL0 high for enable reading */
	AFE44x0_Write(CONTROL0, 0x01);

	/* Select Chip */
	GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);;

	/*Send Address */
	dummy = USART_SpiTransfer(CONFIG_SENSOR_USART, address & 0xFF);

	/*Receive first Byte */
	tempbuff[0] = USART_SpiTransfer(CONFIG_SENSOR_USART, 0x00 & 0xFF);
	/*Receive second Byte */
	tempbuff[1] = USART_SpiTransfer(CONFIG_SENSOR_USART, 0x00 & 0xFF);
	/*Receive last Byte */
	tempbuff[2] = USART_SpiTransfer(CONFIG_SENSOR_USART, 0x00 & 0xFF);

	/* Deselect Chip */
	GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);;
	/* Clear CONTROL0 for disable reading */
	AFE44x0_Write(CONTROL0, 0x00);

//	if((temp[0] & 0x20) != 0 ) {
//		value  = 0xFFFFFFFF;
//		temp[0] |=  0xC0;
//	}else{
//		value = 0;
//	}
	uint32_t bla =0;
	tempbuff[0] &= 0x3F;
	value |= (tempbuff[0] << 16) | (tempbuff[1] << 8) | (tempbuff[2]);
	int32_t test = value & 0x200000;
//	if (test != bla){
//		value |= 0xFFC00000;
//	}
//	else{
//		value &= 0x1FFFF;
//	}
	return value;
}
