/*
 * ads129x.h
 *
 * Copyright (c) 2013 by Adam Feuer <adam@adamfeuer.com>
 * Copyright (c) 2012 by Chris Rorden
 * Copyright (c) 2012 by Steven Cogswell and Stefan Rado
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation either version 3 of the License or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not see <http://www.gnu.org/licenses/>.
 *
 */
#include "em_usart.h"

#include "em_gpio.h"
#include <stdint.h>
#if CONFIGSYSTEM == INEARV3_2
#include "../Config/config_inEar_v3_2.h"
#elif	CONFIGSYSTEM == INEARV4_0
#include "../Config/config_inEar_v4_0.h"
#endif

//function prototypes

//void ads198xspiSend(uint8_t b);
void ads129xspiSend(const uint8_t* buf, uint8_t len);
//uint8_t ads129xspiRec();
uint8_t ads129xspiRec(uint8_t* buf, uint8_t len);

void adc_send_command(int cmd);
void adc_send_command_leave_cs_active(int cmd);
void adc_wreg(int reg, int val);
int  adc_rreg(int reg);
void readRegister_command();
void writeRegister_command();
void wakeup_command();
void standby_command();
void reset_command();
void start_command();
void stop_command();
void rdata_command(uint8_t* p);
void rdatac_command();
void sdatac_command();
void unrecognized(const char *command);
void detectActiveChannels();
void ADS129x_Init();
void sendSamples(uint8_t* p);
void sendSample();
//	enum {
	//enum spi_command {
// system commands
#define WAKEUP 0x02
#define STANDBY 0x04
#define RESET 0x06
#define START 0x08
#define STOP 0x0a

// read commands
#define RDATAC 0x10
#define SDATAC 0x11
#define RDATA 0x12

// register commands
#define RREG 0x20
#define WREG 0x40
	//};
	//enum reg {
#define IDreg 0x00

// global settings
#define CONFIG1 0x01
#define CONFIG2 0x02
#define CONFIG3 0x03
#define LOFF 0x04
// channel specific settings
#define CHnSET 0x04
#define CH1SET CHnSET + 1
#define CH2SET CHnSET + 2
#define CH3SET CHnSET + 3
#define CH4SET CHnSET + 4
#define CH5SET CHnSET + 5
#define CH6SET CHnSET + 6
#define CH7SET CHnSET + 7
#define CH8SET CHnSET + 8
#define RLD_SENSP 0x0d
#define RLD_SENSN 0x0e
#define LOFF_SENSP 0x0f
#define LOFF_SENSN 0x10
#define LOFF_FLIP 0x11
// lead off status
#define LOFF_STATP 0x12
#define LOFF_STATN 0x13

// other
#define GPIOreg 0x14
#define PACE 0x15
#define RESP 0x16
#define CONFIG4 0x17
#define WCT1 0x18
#define WCT2 0x19
//	};
//
////	enum ID_bits {
#define DEV_ID7 0x80
#define DEV_ID6 0x40
#define DEV_ID5 0x20
#define DEV_ID2 0x04
#define DEV_ID1 0x02
#define DEV_ID0 0x01

#define ID_const 0x10
#define ID_ADS129x DEV_ID7
#define ID_ADS129xR (DEV_ID7 | DEV_ID6)

#define ID_4CHAN 0
#define ID_6CHAN DEV_ID0
#define ID_8CHAN DEV_ID1

#define ID_ADS1294 (ID_ADS129x | ID_4CHAN)
#define ID_ADS1296 (ID_ADS129x | ID_6CHAN)
#define ID_ADS1298 (ID_ADS129x | ID_8CHAN)
#define ID_ADS1294R (ID_ADS129xR | ID_4CHAN)
#define ID_ADS1296R (ID_ADS129xR | ID_6CHAN)
#define ID_ADS1298R (ID_ADS129xR | ID_8CHAN)
////	};
//
////	enum CONFIG1_bits {
#define HR 0x80
#define DAISY_EN 0x40
#define CLK_EN 0x20
#define DR2 0x04
#define DR1 0x02
#define DR0 0x01
                
                // correct for ADS1298/1294; incorrect for ADS1299
                // TODO: Fix for ADS1299
                
                // ADS1298
//CONFIG1_const 0x00

                // ADS1299
#define CONFIG1_const 0xE0

                // ADS1298
                /*
#define HIGH_RES_32k_SPS HR
#define HIGH_RES_16k_SPS (HR | DR0)
#define HIGH_RES_8k_SPS (HR | DR1)
#define HIGH_RES_4k_SPS (HR | DR1 | DR0)
#define HIGH_RES_2k_SPS (HR | DR2)
#define HIGH_RES_1k_SPS (HR | DR2 | DR0)
#define HIGH_RES_500_SPS (HR | DR2 | DR1)
#define LOW_POWR_250_SPS (DR2 | DR1)
                */
                
                // ADS1299
#define HIGH_RES_16k_SPS HR
#define HIGH_RES_8k_SPS (HR | DR0)
#define HIGH_RES_4k_SPS (HR | DR1)
#define HIGH_RES_2k_SPS (HR | DR1 | DR0)
#define HIGH_RES_1k_SPS (HR | DR2)
#define HIGH_RES_500_SPS (HR | DR2 | DR0)
#define HIGH_RES_250_SPS (HR | DR2 | DR1)

////	};
//
////	enum CONFIG2_bits {
#define WCT_CHOP 0x20
#define INT_TEST 0x10
#define TEST_AMP 0x04
#define TEST_FREQ1 0x02
#define TEST_FREQ0 0x01

                // ADS1298
//CONFIG2_const 0x00

                // ADS1299
#define CONFIG2_const 0xC0

#define INT_TEST_4HZ INT_TEST
#define INT_TEST_8HZ (INT_TEST | TEST_FREQ0)
#define INT_TEST_DC (INT_TEST | TEST_FREQ1 | TEST_FREQ0)
////	};
//
////	enum CONFIG3_bits {
#define PD_REFBUF 0x80
#define VREF_4V 0x20
#define RLD_MEAS 0x10
#define RLDREF_INT 0x08
#define PD_RLD 0x04
#define RLD_LOFF_SENS 0x02
#define RLD_STAT 0x01

                // ADS1298
//CONFIG3_const 0x40

                // ADS1299
#define CONFIG3_const 0x60
////	};
//
////	enum LOFF_bits {
#define COMP_TH2 0x80
#define COMP_TH1 0x40
#define COMP_TH0 0x20
#define VLEAD_OFF_EN 0x10
#define ILEAD_OFF1 0x08
#define ILEAD_OFF0 0x04
#define FLEAD_OFF1 0x02
#define FLEAD_OFF0 0x01

#define LOFF_const 0x00

#define COMP_TH_95 0x00
#define COMP_TH_92_5 COMP_TH0
#define COMP_TH_90 COMP_TH1
#define COMP_TH_87_5 (COMP_TH1 | COMP_TH0)
#define COMP_TH_85 COMP_TH2
#define COMP_TH_80 (COMP_TH2 | COMP_TH0)
#define COMP_TH_75 (COMP_TH2 | COMP_TH1)
#define COMP_TH_70 (COMP_TH2 | COMP_TH1 | COMP_TH0)

#define ILEAD_OFF_6nA 0x00
#define ILEAD_OFF_12nA ILEAD_OFF0
#define ILEAD_OFF_18nA ILEAD_OFF1
#define ILEAD_OFF_24nA (ILEAD_OFF1 | ILEAD_OFF0)

#define FLEAD_OFF_AC FLEAD_OFF0
#define FLEAD_OFF_DC (FLEAD_OFF1 | FLEAD_OFF0)
////	};
//
////	enum CHnSET_bits {
#define PDn 0x80
#define PD_n 0x80
#define GAINn2 0x40
#define GAINn1 0x20
#define GAINn0 0x10
#define MUXn2 0x04
#define MUXn1 0x02
#define MUXn0 0x01

#define CHnSET_const 0x00

#define GAIN_1X GAINn0
#define GAIN_2X GAINn1
#define GAIN_3X (GAINn1 | GAINn0)
#define GAIN_4X GAINn2
#define GAIN_6X 0x00
#define GAIN_8X (GAINn2 | GAINn0)
#define GAIN_12X (GAINn2 | GAINn1)

#define ELECTRODE_INPUT 0x00
#define SHORTED MUXn0
#define RLD_INPUT MUXn1
#define MVDD (MUXn1 | MUXn0)
#define TEMP MUXn2
#define TEST_SIGNAL (MUXn2 | MUXn0)
#define RLD_DRP (MUXn2 | MUXn1)
#define RLD_DRN (MUXn2 | MUXn1 | MUXn0)
////	};
//
////	enum CH1SET_bits {
#define PD_1 0x80
#define GAIN12 0x40
#define GAIN11 0x20
#define GAIN10 0x10
#define MUX12 0x04
#define MUX11 0x02
#define MUX10 0x01

#define CH1SET_const 0x00
//	};

//	enum CH2SET_bits {
#define PD_2 0x80
#define GAIN22 0x40
#define GAIN21 0x20
#define GAIN20 0x10
#define MUX22 0x04
#define MUX21 0x02
#define MUX20 0x01

#define CH2SET_const 0x00
//	};

//	enum CH3SET_bits {
#define PD_3 0x80
#define GAIN32 0x40
#define GAIN31 0x20
#define GAIN30 0x10
#define MUX32 0x04
#define MUX31 0x02
#define MUX30 0x01

#define CH3SET_const 0x00
//	};

//	enum CH4SET_bits {
#define PD_4 0x80
#define GAIN42 0x40
#define GAIN41 0x20
#define GAIN40 0x10
#define MUX42 0x04
#define MUX41 0x02
#define MUX40 0x01

#define CH4SET_const 0x00
//	};

//	enum CH5SET_bits {
#define PD_5 0x80
#define GAIN52 0x40
#define GAIN51 0x20
#define GAIN50 0x10
#define MUX52 0x04
#define MUX51 0x02
#define MUX50 0x01

#define CH5SET_const 0x00
//	};

//	enum CH6SET_bits {
#define PD_6 0x80
#define GAIN62 0x40
#define GAIN61 0x20
#define GAIN60 0x10
#define MUX62 0x04
#define MUX61 0x02
#define MUX60 0x01

#define CH6SET_const 0x00
//	};

//	enum CH7SET_bits {
#define PD_7 0x80
#define GAIN72 0x40
#define GAIN71 0x20
#define GAIN70 0x10
#define MUX72 0x04
#define MUX71 0x02
#define MUX70 0x01

#define CH7SET_const 0x00
//	};

//	enum CH8SET_bits {
#define PD_8 0x80
#define GAIN82 0x40
#define GAIN81 0x20
#define GAIN80 0x10
#define MUX82 0x04
#define MUX81 0x02
#define MUX80 0x01

#define CH8SET_const 0x00
//	};

//	enum RLD_SENSP_bits {
#define RLD8P 0x80
#define RLD7P 0x40
#define RLD6P 0x20
#define RLD5P 0x10
#define RLD4P 0x08
#define RLD3P 0x04
#define RLD2P 0x02
#define RLD1P 0x01

#define RLD_SENSP_const 0x00
//	};

//	enum RLD_SENSN_bits {
#define RLD8N 0x80
#define RLD7N 0x40
#define RLD6N 0x20
#define RLD5N 0x10
#define RLD4N 0x08
#define RLD3N 0x04
#define RLD2N 0x02
#define RLD1N 0x01

#define RLD_SENSN_const 0x00
//	};

//	enum LOFF_SENSP_bits {
#define LOFF8P 0x80
#define LOFF7P 0x40
#define LOFF6P 0x20
#define LOFF5P 0x10
#define LOFF4P 0x08
#define LOFF3P 0x04
#define LOFF2P 0x02
#define LOFF1P 0x01

#define LOFF_SENSP_const 0x00
//	};

//	enum LOFF_SENSN_bits {
#define LOFF8N 0x80
#define LOFF7N 0x40
#define LOFF6N 0x20
#define LOFF5N 0x10
#define LOFF4N 0x08
#define LOFF3N 0x04
#define LOFF2N 0x02
#define LOFF1N 0x01

#define LOFF_SENSN_const 0x00
//	};

//	enum LOFF_FLIP_bits {
#define LOFF_FLIP8 0x80
#define LOFF_FLIP7 0x40
#define LOFF_FLIP6 0x20
#define LOFF_FLIP5 0x10
#define LOFF_FLIP4 0x08
#define LOFF_FLIP3 0x04
#define LOFF_FLIP2 0x02
#define LOFF_FLIP1 0x01

#define LOFF_FLIP_const 0x00
//	};

//	enum LOFF_STATP_bits {
#define IN8P_OFF 0x80
#define IN7P_OFF 0x40
#define IN6P_OFF 0x20
#define IN5P_OFF 0x10
#define IN4P_OFF 0x08
#define IN3P_OFF 0x04
#define IN2P_OFF 0x02
#define IN1P_OFF 0x01

#define LOFF_STATP_const 0x00
//	};

//	enum LOFF_STATN_bits {
#define IN8N_OFF 0x80
#define IN7N_OFF 0x40
#define IN6N_OFF 0x20
#define IN5N_OFF 0x10
#define IN4N_OFF 0x08
#define IN3N_OFF 0x04
#define IN2N_OFF 0x02
#define IN1N_OFF 0x01

#define LOFF_STATN_const 0x00
//	};

//	enum GPIO_bits {
#define GPIOD4 0x80
#define GPIOD3 0x40
#define GPIOD2 0x20
#define GPIOD1 0x10
#define GPIOC4 0x08
#define GPIOC3 0x04
#define GPIOC2 0x02
#define GPIOC1 0x01

#define GPIO_const 0x00
//	};

//	enum PACE_bits {
#define PACEE1 0x10
#define PACEE0 0x08
#define PACEO1 0x04
#define PACEO0 0x02
#define PD_PACE 0x01

#define PACE_const 0x00

#define PACEE_CHAN2 0x00
#define PACEE_CHAN4 PACEE0
#define PACEE_CHAN6 PACEE1
#define PACEE_CHAN8 (PACEE1 | PACEE0)

#define PACEO_CHAN1 0x00
#define PACEO_CHAN3 PACEE0
#define PACEO_CHAN5 PACEE1
#define PACEO_CHAN7 (PACEE1 | PACEE0)
//	};

//	enum RESP_bits {
#define RESP_DEMOD_EN1 0x80
#define RESP_MOD_EN1 0x40
#define RESP_PH2 0x10
#define RESP_PH1 0x08
#define RESP_PH0 0x04
#define RESP_CTRL1 0x02
#define RESP_CTRL0 0x01

#define RESP_const 0x20

#define RESP_PH_22_5 0x00
#define RESP_PH_45 RESP_PH0
#define RESP_PH_67_5 RESP_PH1
#define RESP_PH_90 (RESP_PH1 | RESP_PH0)
#define RESP_PH_112_5 RESP_PH2
#define RESP_PH_135 (RESP_PH2 | RESP_PH0)
#define RESP_PH_157_5 (RESP_PH2 | RESP_PH1)

#define RESP_NONE 0x00
#define RESP_EXT RESP_CTRL0
#define RESP_INT_SIG_INT RESP_CTRL1
#define RESP_INT_SIG_EXT (RESP_CTRL1 | RESP_CTRL0)
//	};

//	enum CONFIG4_bits {
#define RESP_FREQ2 0x80
#define RESP_FREQ1 0x40
#define RESP_FREQ0 0x20
#define SINGLE_SHOT 0x08
#define WCT_TO_RLD 0x04
#define PD_LOFF_COMP 0x02

#define CONFIG4_const 0x00

#define RESP_FREQ_64k_Hz 0x00
#define RESP_FREQ_32k_Hz RESP_FREQ0
#define RESP_FREQ_16k_Hz RESP_FREQ1
#define RESP_FREQ_8k_Hz (RESP_FREQ1 | RESP_FREQ0)
#define RESP_FREQ_4k_Hz RESP_FREQ2
#define RESP_FREQ_2k_Hz (RESP_FREQ2 | RESP_FREQ0)
#define RESP_FREQ_1k_Hz (RESP_FREQ2 | RESP_FREQ1)
#define RESP_FREQ_500_Hz (RESP_FREQ2 | RESP_FREQ1 | RESP_FREQ0)
//	};

//	enum WCT1_bits {
#define aVF_CH6 0x80
#define aVL_CH5 0x40
#define aVR_CH7 0x20
#define avR_CH4 0x10
#define PD_WCTA 0x08
#define WCTA2 0x04
#define WCTA1 0x02
#define WCTA0 0x01

#define WCT1_const 0x00

#define WCTA_CH1P 0x00
#define WCTA_CH1N WCTA0
#define WCTA_CH2P WCTA1
#define WCTA_CH2N (WCTA1 | WCTA0)
#define WCTA_CH3P WCTA2
#define WCTA_CH3N (WCTA2 | WCTA0)
#define WCTA_CH4P (WCTA2 | WCTA1)
#define WCTA_CH4N (WCTA2 | WCTA1 | WCTA0)
	//};

	//enum WCT2_bits {
#define PD_WCTC 0x80
#define PD_WCTB 0x40
#define WCTB2 0x20
#define WCTB1 0x10
#define WCTB0 0x08
#define WCTC2 0x04
#define WCTC1 0x02
#define WCTC0 0x01

#define WCT2_const 0x00

#define WCTB_CH1P 0x00
#define WCTB_CH1N WCTB0
#define WCTB_CH2P WCTB1
#define WCTB_CH2N (WCTB1 | WCTB0)
#define WCTB_CH3P WCTB2
#define WCTB_CH3N (WCTB2 | WCTB0)
#define WCTB_CH4P (WCTB2 | WCTB1)
#define WCTB_CH4N (WCTB2 | WCTB1 | WCTB0)

#define WCTC_CH1P 0x00
#define WCTC_CH1N WCTC0
#define WCTC_CH2P WCTC1
#define WCTC_CH2N (WCTC1 | WCTC0)
#define WCTC_CH3P WCTC2
#define WCTC_CH3N (WCTC2 | WCTC0)
#define WCTC_CH4P (WCTC2 | WCTC1)
#define WCTC_CH4N (WCTC2 | WCTC1 | WCTC0)
//	};
