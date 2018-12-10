/*
 * AFE44x0.h
 *
 *  Created on: 13.09.2017
 *      Author: diehl
 */
#include "em_usart.h"

#include "em_gpio.h"
#include <stdint.h>

#if CONFIGSYSTEM	== INEARV3_2
#include "../Config/config_inEar_v3_2.h"
#elif	CONFIGSYSTEM == INEARV4_0
#include "../Config/config_inEar_v4_0.h"
#endif

#ifndef AFE44x0_H_
#define AFE44x0_H_



void AFE44x0_Init();

void AFE44x0_Write(uint8_t address, uint32_t data);
/* Reads 3 Bytes of Data from the address */
int32_t AFE44x0_Read(uint8_t address);


// AFE4400 Register Setup

// all Registers are mapped
#define CONTROL0 0x00
#define LED2STC 0x01
#define LED2ENDC 0x02
#define LED2LEDSTC 0x03
#define LED2LEDENDC 0x04
#define ALED2STC 0x05
#define ALED2ENDC 0x06
#define LED1STC 0x07
#define LED1ENDC 0x08
#define LED1LEDSTC 0x09
#define LED1LEDENDC 0x0A
#define ALED1STC 0x0B
#define ALED1ENDC 0x0C
#define LED2CONVST 0x0D
#define LED2CONVEND 0x0E
#define ALED2CONVST 0x0F
#define ALED2CONVEND 0x10
#define LED1CONVST 0x11
#define LED1CONVEND 0x12
#define ALED1CONVST 0x13
#define ALED1CONVEND 0x14
#define ADCRSTSTCT0 0x15
#define ADCRSTENDCT0 0x16
#define ADCRSTSTCT1 0x17
#define ADCRSTENDCT1 0x18
#define ADCRSTSTCT2 0x19
#define ADCRSTENDCT2 0x1A
#define ADCRSTSTCT3 0x1B
#define ADCRSTENDCT3 0x1C
#define PRPCOUNT 0x1D
#define CONTROL1 0x1E
#define SPARE1 0x1F
#define TIAGAIN 0x20
#define TIA_AMB_GAIN 0x21
#define LEDCNTRL 0x22
#define CONTROL2 0x23
#define SPARE2 0x24
#define SPARE3 0x25
#define SPARE4 0x26
#define RESERVED1 0x27
#define RESERVED2 0x28
#define ALARM 0x29
#define LED2VAL 0x2A
#define ALED2VAL 0x2B
#define LED1VAL 0x2C
#define ALED1VAL 0x2D
#define LED2_ALED2VAL 0x2E
#define LED1_ALED1VAL 0x2F
#define DIAG 0x30
// Class definition

#endif /* AFE44x0_H_ */
