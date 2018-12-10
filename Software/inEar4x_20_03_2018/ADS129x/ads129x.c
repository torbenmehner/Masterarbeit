/* adsCommand.cpp
 *
 * send and receive commands from TI ADS129x chips. 
 *
 * Copyright (c) 2013 by Adam Feuer <adam@adamfeuer.com>
 * Copyright (c) 2012 by Chris Rorden
 * Copyright (c) 2012 by Steven Cogswell and Stefan Rado
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//#include "Arduino.h"   // use: Wprogram.h for Arduino versions prior to 1.0
//#include "adsCommand.h"
#include "ads129x.h"
#include <stdio.h>
#include <string.h>
//#include "SpiDma.h"


int maxChannels = 0;
int numActiveChannels = 0;
bool gActiveChan[9]; // reports whether channels 1..9 are active
bool isRdatac = false;
bool base64Mode = true;

char hexDigits[] = "0123456789ABCDEF";
uint8_t serialBytes[200];
char sampleBuffer[1000];

const char *hardwareType = "unknown";
const char *boardName = "HackEEG";
const char *makerName = "StarCat, LLC";
const char *driverVersion = "ADS129x driver v0.2.1";
int8_t sendBuff;
/*void wait_for_drdy(int interval)
{
	int i = 0;
	while (digitalRead(IPIN_DRDY) == HIGH) {
		if (i < interval) {
			continue;
		}
		i = 0;
	}
}*/

/** SPI send a byte */
//void ads129xspiSend(uint8_t b) {
//		 USART_SpiTransfer(CONFIG_SENSOR_USART, b);
//}
//------------------------------------------------------------------------------
/** SPI send multiple bytes */
void ads129xspiSend(const uint8_t* buf, uint8_t len) {
		for (uint8_t stringpos = 0; stringpos < len; stringpos++) {
		 USART_SpiTransfer(CONFIG_SENSOR_USART, *buf+stringpos);
		}
}

//------------------------------------------------------------------------------
/** SPI receive a byte */
//uint8_t ads129xspiRec() {
//  return USART_SpiTransfer(CONFIG_SENSOR_USART, 0XFF);
//}
//------------------------------------------------------------------------------
/** SPI receive multiple bytes */
uint8_t ads129xspiRec(uint8_t* buf, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    buf[i] = USART_SpiTransfer(CONFIG_SENSOR_USART, 0XFF);
  }
  return 0;
}

void adc_send_command(int cmd) {
   GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
   ads129xspiSend(&cmd, 1);
   //RTCDRV_Delay(1);
   GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
}

void adc_send_command_leave_cs_active(int cmd) {
   GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
   ads129xspiSend(&cmd, 1);
}

void adc_wreg(int reg, int val) {
   //see pages 40,43 of datasheet - 
   GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
   sendBuff=WREG | reg;
   ads129xspiSend(&sendBuff, 1);
   RTCDRV_Delay(2);
   sendBuff=0;
   ads129xspiSend(&sendBuff, 1);	// number of registers to be read/written â€“ 1
   RTCDRV_Delay(2);
   ads129xspiSend(&val, 1);
   RTCDRV_Delay(1);
   GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
}

int adc_rreg(int reg){
   uint8_t out = 0;
   GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
   sendBuff=(RREG | reg);
   ads129xspiSend(&sendBuff, 1);
   RTCDRV_Delay(2);
   sendBuff=0;
   ads129xspiSend(&sendBuff, 1);	// number of registers to be read/written â€“ 1
   RTCDRV_Delay(2);
   ads129xspiRec(&out, 1);
   RTCDRV_Delay(1);
   GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
   return((int)out);
}


void wakeup_command() {
  //using namespace ADS129x;
  adc_send_command(WAKEUP);
  //WiredSerial.println("200 Ok ");
  //WiredSerial.println("Wakeup command sent.");
  //WiredSerial.println(); 
}

void standby_command() {
  //using namespace ADS129x;
  adc_send_command(STANDBY);
  //WiredSerial.println("200 Ok ");
  //WiredSerial.println("Standby command sent.");
  //WiredSerial.println(); 
}

void reset_command() {
  //using namespace ADS129x;
  adc_send_command(RESET);
  //WiredSerial.println("200 Ok ");
  //WiredSerial.println("Reset command sent.");
  //WiredSerial.println(); 
}

void start_command() {
  //using namespace ADS129x;
  adc_send_command(START);
  //WiredSerial.println("200 Ok ");
  //WiredSerial.println("Start command sent.");
  //WiredSerial.println(); 
}

void stop_command() {
  //using namespace ADS129x;
  adc_send_command(STOP);
  //WiredSerial.println("200 Ok ");
  //WiredSerial.println("Stop command sent.");
  //WiredSerial.println(); 
}

void rdata_command(uint8_t* p) {
  //using namespace ADS129x;
  //while (digitalRead(IPIN_DRDY) == HIGH);
	  while (GPIO_PinInGet(CONFIG_ADS129x_RDY_PORT, CONFIG_ADS129x_RDY_PIN) == 1){ //ToDo unschön, noch mit GPIO Interrupt machen
	  }
	  adc_send_command_leave_cs_active(RDATA);
	  //WiredSerial.println("200 Ok ");
	  sendSample();
	  memcpy(p+2, serialBytes+9, 1);
	  memcpy(p+1, serialBytes+10, 1);
	  memcpy(p,   serialBytes+11, 1);

  //WiredSerial.println(); 
}

void rdatac_command() {
  //using namespace ADS129x;
  detectActiveChannels();
  if (numActiveChannels > 0) { 
    isRdatac = true;
    adc_send_command(RDATAC);
    //WiredSerial.println("200 Ok");
    //WiredSerial.println("RDATAC mode on."); 
  } else {
    //WiredSerial.println("405 Error: no active channels.");
  }
  //WiredSerial.println(); 
}

void sdatac_command() {
  //using namespace ADS129x;
  isRdatac = false;
  adc_send_command(SDATAC);
  //using namespace ADS129x;
  //WiredSerial.println("200 Ok");
  //WiredSerial.println("RDATAC mode off."); 
  //WiredSerial.println(); 
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized(const char *command) {
  //WiredSerial.println("406 Error: Unrecognized command."); 
  //WiredSerial.println();   
}


void detectActiveChannels() {  //set device into RDATAC (continous) mode -it will stream data
  if ((isRdatac) ||  (maxChannels < 1)) return; //we can not read registers when in RDATAC mode
  //Serial.println("Detect active channels: ");
  //using namespace ADS129x;
  numActiveChannels = 0;
  for (int i = 1; i <= maxChannels; i++) {
    RTCDRV_Delay(1);
    int chSet = adc_rreg(CHnSET + i);
    gActiveChan[i] = ((chSet & 7) != SHORTED);
    if ( (chSet & 7) != SHORTED) numActiveChannels ++;   
  }
}

//#define testSignal //use this to determine if your software is accurately measuring full range 24-bit signed data -8388608..8388607
#ifdef testSignal
int testInc = 1;
int testPeriod = 100;
byte testMSB, testLSB; 
#endif 

void sendSamples(uint8_t* p) {
  if ((!isRdatac) || (numActiveChannels < 1) )  return;
  if (GPIO_PinInGet(CONFIG_ADS129x_RDY_PORT, CONFIG_ADS129x_RDY_PIN) == 1) return; //ToDo unschön, noch mit GPIO Interrupt machen
  sendSample();
  memcpy(p+2, serialBytes+9, 1);
  memcpy(p+1, serialBytes+10, 1);
  memcpy(p,   serialBytes+11, 1);
//  memcpy(p+3, serialBytes+8, 1);
//  memcpy(p+2, serialBytes+9, 1);
//  memcpy(p+1, serialBytes+10, 1);
//  memcpy(p, serialBytes+11, 1);
}


void sendSample() {
  GPIO_PinOutClear(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
  register int numSerialBytes = (3 * (maxChannels+1)); //24-bits header plus 24-bits per channel
  uint8_t returnCode = ads129xspiRec(serialBytes, numSerialBytes);
  GPIO_PinOutSet(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
  register unsigned int count = 0;
  //encodeHex(sampleBuffer, (char *)serialBytes, numSerialBytes);
  //WiredSerial.println(sampleBuffer);
}

void ADS129x_Init() { //default settings for ADS1298 and compatible chips
  //using namespace ADS129x;
  // Send SDATAC Command (Stop Read Data Continuously mode)
  RTCDRV_Delay(1000); //pause to provide ads129n enough time to boot up...
  adc_send_command(SDATAC);
  // RTCDRV_Delay(2);
  RTCDRV_Delay(100); 
  int val = adc_rreg(IDreg) ;
  switch (val & 0b00011111 ) { //least significant bits reports channels
  case  0b10000: //16
    hardwareType = "ADS1294";
    maxChannels = 4;
    break;
  case 0b10001: //17
    hardwareType = "ADS1296";
    maxChannels = 6; 
    break;
  case 0b10010: //18
    hardwareType = "ADS1298";
    maxChannels = 8; 
    break;
  case 0b11110: //30
    hardwareType = "ADS1299";
    maxChannels = 8; 
    break;
  default: 
    maxChannels = 0;
  }

  // Config für 3 elktroden mit driven right leg
  adc_wreg(CONFIG1,0x86);
  adc_wreg(CONFIG2,0x10);
  adc_wreg(CONFIG3,0xDC);
  adc_wreg(CONFIG4,0xC);
  adc_wreg(LOFF,0x03);
  adc_wreg(CH1SET,0x05);
  adc_wreg(CH2SET,0x66);
  adc_wreg(CH3SET,0x60);
  adc_wreg(CH4SET,0x05);
  adc_wreg(CH5SET,0x05);
  adc_wreg(CH6SET,0x05);
  adc_wreg(CH7SET,0x05);
  adc_wreg(CH8SET,0x05);
  adc_wreg(RLD_SENSP,0x06);
  adc_wreg(RLD_SENSN,0x02);
  adc_wreg(LOFF_SENSP,0x00);
  adc_wreg(LOFF_SENSN,0x00);
  adc_wreg(LOFF_FLIP,0x00);
  adc_wreg(LOFF_STATP,0x00);
  adc_wreg(LOFF_STATN,0x00);
  adc_wreg(GPIOreg,0x00);
  adc_wreg(PACE,0x00);
  adc_wreg(RESP,0xF0);
  stop_command();
  //WiredSerial.println("Max channels: " + maxChannels);
  // All GPIO set to output 0x0000: (floating CMOS inputs can flicker on and off, creating noise)
//  adc_wreg(GPIOreg, 0);
//  adc_wreg(CONFIG3,PD_REFBUF | CONFIG3_const);
//  //FOR RLD: Power up the internal reference and wait for it to settle
//  // adc_wreg(CONFIG3, RLDREF_INT | PD_RLD | PD_REFBUF | VREF_4V | CONFIG3_const);
//  // RTCDRV_Delay(150);
//  // adc_wreg(RLD_SENSP, 0x01);	// only use channel IN1P and IN1N
//  // adc_wreg(RLD_SENSN, 0x01);	// for the RLD Measurement
//  adc_wreg(CONFIG1,HIGH_RES_500_SPS);
//  adc_wreg(CONFIG2, INT_TEST);	// generate internal test signals
//  // Set the first two channels to input signal
//  for (int i = 1; i <= 1; ++i) {
//    //adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_1X); //report this channel with x12 gain
//    //adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_12X); //report this channel with x12 gain
//    adc_wreg(CHnSET + i, TEST_SIGNAL | GAIN_12X); //create square wave
//    //adc_wreg(CHnSET + i,SHORTED); //disable this channel
//  }
//  for (int i = 2; i <= 2; ++i) {
//    //adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_1X); //report this channel with x12 gain
//    //adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_12X); //report this channel with x12 gain
//    adc_wreg(CHnSET + i, TEST_SIGNAL | GAIN_12X); //create square wave
//    //adc_wreg(CHnSET + i,SHORTED); //disable this channel
//  }
//  for (int i = 3; i <= 6; ++i) {
//    adc_wreg(CHnSET + i, SHORTED); //disable this channel
//  }
//  for (int i = 7; i <= 8; ++i) {
//    adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_1X); //report this channel with x12 gain
//    //adc_wreg(CHnSET + i, ELECTRODE_INPUT | GAIN_12X); //report this channel with x12 gain
//    //adc_wreg(CHnSET + i, TEST_SIGNAL | GAIN_12X); //create square wave
//    //adc_wreg(CHnSET + i,SHORTED); //disable this channel
//  }

  //digitalWrite(PIN_START, HIGH);  
}
