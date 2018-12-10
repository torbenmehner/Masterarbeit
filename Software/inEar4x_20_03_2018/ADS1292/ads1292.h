#ifndef ADS_1292_H
#define ADS_1292_H

#include "rtcdriver.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"

// system commands
#define WAKEUP 		0x02
#define STANDBY 	0x04
#define RESET 		0x06
#define START 		0x08
#define STOP 		0x0A
#define OFFSETCAL	0x1A

// read commands
#define RDATAC 	0x10
#define SDATAC 	0x11
#define RDATA 	0x12

// register commands
#define RREG 0x20
#define WREG 0x40

// global settings
#define CONFIG1 	0x01
#define CONFIG2 	0x02
#define LOFF 		0x03
#define CH1SET  	0x04
#define CH2SET		0x05
#define RLDSENS		0x06
#define LOFFSENS 	0x07
#define LOFFSTAT 	0x08
#define RESP1		0x09
#define RESP2		0x0A
#define GPIO_REG	0x0B



//sample rate
#define SAMPLE_RATE_125	0x00
#define SAMPLE_RATE_250 0x01
#define SAMPLE_RATE_500 0x02
#define SAMPLE_RATE_1k	0x03
#define SAMPLE_RATE_2k	0x04
#define SAMPLE_RATE_4k	0x05
#define SAMPLE_RATE_8k	0x06

//test signal definition
#define TEST_SIGNAL_SQUARE 	0b10100011
#define TEST_SIGNAL_DC		0b10100010
#define TEST_SIGNAL_OFF		0b10100000

//channel definition
#define CH1_TEST_SIGNAL		0b00000101
#define CH1_DEFAULT			0x00
#define CH1_GAIN1			0b00010000
#define CH1_GAIN2			0b00100000
#define CH1_GAIN3			0b00110000
#define CH1_GAIN4			0b01000000
#define CH1_GAIN8			0b01010000
#define CH1_GAIN12			0b01100000
#define CH2_INPUT_SHORTED 	0b10000001
#define CH1_INPUT_SHORTED 	0b10000001

void ads1292_Reset();
void rdata_command_ads1292(uint8_t* p);
void ads1292_Reg_Write (uint8_t READ_WRITE_ADDRESS, uint8_t DATA);
void ads1292_SPI_Command_Data(uint8_t data_in);
void ads1292_Disable_Start();
void ads1292_Enable_Start();
void ads1292_Hard_Stop();
void ads1292_Start_Data_Conv_Command();
void ads1292_Soft_Stop();
void ads1292_Start_Read_Data_Continuous();
void ads1292_Stop_Read_Data_Continuous();
void ads1292_read_data(uint8_t* buf, uint8_t len);
void ads1292_SPI_Command_Data(uint8_t data_in);
void ads1292_Init();


#endif //ADS_1292_H
