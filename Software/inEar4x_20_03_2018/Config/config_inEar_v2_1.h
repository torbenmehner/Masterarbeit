/******************************************************************************
 * @file config_inEar_v1.h
 * @brief Configuration File for TrinkTracker v1 Project
 * @author czimmer@fzi.de
 * @version 0.1
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2015-05-01	0.1		czimmer 	Initial Version
 *
 * *****************************************************************************/
#ifndef CONFIG_INEAR_V2_1_H_
#define CONFIG_INEAR_V2_1_H_
#include "../config.h"
#if CONFIGSYSTEM==INEARV2_1

#define CONFIG_DEBUG_PRINTOUT_ENABLE			1							// Enables Print Out on SWO for Debugging
																			// Tell CSMIS-DSP Lib to use Lib for Cortex M3
#define CONFIG_SYSTEM_TYPE						0
/*
 * Timer0 of EFM32
 */
#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER0_TOP						1708	//987					// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER1_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER1_TOP						1708						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER2_PRESCALE          		timerPrescale32       // Prescaler for Timer 0
#define CONFIG_TIMER2_TOP           			5859            // 256 Hz with 48MHz and 32-Prescaling -> 5859, 128 Hz with 48MHz and 64-Prescaling -> 5859


// TODO CLEANUP!!!!
#define CONFIG_BUFFERSIZE_ACC					1024						// Buffer Size of Accelerometer Buffer in Bytes
#define CONFIG_BUFFERSIZE_GYRO					1024						// Buffer Size of Gyro Buffer in Bytes
#define CONFIG_BUFFERSIZE_TEMP					1024						// Buffer Size of Temperature Buffer in Bytes
#define CONFIG_BUFFERSIZE_ADC					1024						// Buffer Size of Adc Buffer in Bytes
#define CONFIG_SYSTEM_HFRCO_FREQ				14000000					// Low Frequency Oscillator Frequency
#define CONFIG_SYSTEM_HFXO_FREQ					48000000					// High Frequency Oscillator Frequency
#define CONFIG_TT_TRESSHOLD_MAX_ACC				16000
#define CONFIG_TT_TRESSHOLD_MAX_TIMER_RUNS		7680						// Set Data valid Treshhold in Timer Ticks of Timer0, with 7680 and 128Hz Timer this means 60s
#define CONFIG_TT_TRESHHOLD_MIN_TIMER_RUNS		512							// Set Data valid Treshhold in Timer Ticks of Timer0, with 512 and 128Hz Timer this means 4s


//TODO END CLEANUP
#define CONFIG_BUFFERSIZE_PRESS					1024		// in bytes

/*
 * Timer0 of EFM32
 */
#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER0_TOP						1708						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708

/*
 * ADC of EFM32
 * currently only support for one Source
 */
#define CONFIG_ADC_MYO_ENABLE					0							// Switch ADC for Myo on
#define CONFIG_ADC_TT_ENABLE					1							// Switch ADC for TrinkTracker on
#define CONFIG_ADC_BATT_ENABLE					0							//TODO not used yet Switch ADC for Battery on
#define CONFIG_ADC_TEMP_ENABLE					0							//TODO not used yet Switch ADC for internal Temp Sensor on
#define CONFIG_ADC_CONTINUOUS_SAMPLING			1							// Continuous Sampling of ADC Data from Timer0
#define CONFIG_ADC_TT_SAMPLING					1							// ACD Sampling before/after each measurment

/*
 * ACC & Gyro & Interrupts of MPU6050
 */
#define CONFIG_MPU6050_ACC_ENABLE				1							//TODO not used yet Switch ACC of MPU6050 on
#define CONFIG_MPU6050_ACC_LSB					0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SAMPLERATE_DLPF		0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SAMPLERATE			0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SLEEP_SAMPLERATE		0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_ENABLE				0							//TODO not used yet Switch GYRO of MPU6050 on
#define CONFIG_MPU6050_GYRO_LSB					0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_SAMPLERATE_DLPF		0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_SAMPLERATE			0							//TODO not used yet
#define CONFIG_MPU6050_TEMP_ENABLE				1							//TODO not used yet  Switch TEMP of MPU6050 on
#define CONFIG_MPU6050_INT_ENABLE				1							// Switch Interrupt of MPU6050 on
#define CONFIG_MPU6050_INT_TRESHHOLD_VALUE 		0x02						// Set Interrupt Treshhold Value of MPU650 in [2mg] for Wakeup
#define CONFIG_MPU6050_INT_TRESHHOLD_DURATION 	0x02						// Set Interrupt Treshhold Duration of MPU650 in [ms] for Wakeup
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_VALUE	400							// Set Sleep Treshhold Value in [2mg] for Sleep, Value has to be lower to go to sleep
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_DURATION	512							// Set Sleep Treshhold Value in Timer Ticks of Timer0, with 512 and 128Hz Timer this means 4s

/*
 * Saving to Unisens
 * 0 - No Saving
 * 1 - Save as CSV // Currently not working for all data
 * 2 - Save as BIN
 */
#define CONFIG_SAVEUNISENS_TRIGGER  		2
#define CONFIG_SAVEUNISENS_EXT1		  		2
#define CONFIG_SAVEUNISENS_EXT2		  		2

#define CONFIG_SAVEUNISENS            		1             // Save any Data to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ACC      2             // Save ACC of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_GYRO     2             // Save GYRO of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ANGLE    2             // Computed Angle from ACC & GYRO of MPU6050
#define CONFIG_SAVEUNISENS_MPU6050_TEMP     2             // Save TEMP of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_EFM32_ADC_MYO    0             //TODO not used yet
#define CONFIG_SAVEUNISENS_EFM32_ADC_TT     2             // Save ADC of EMF32 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_EFM32_ADC_BATT   0             //TODO not used yet
#define CONFIG_SAVEUNISENS_EFM32_DAC_FORCE    0             // Save DAC Value of Sensor FSR Unit
#define CONFIG_SAVEUNISENS_BMP180_PRESS     0             // Save PRESSURE of BMP180 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP180_TEMP      0             // Save TEMP of BMP180 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_PRESS     2             // Save PRESSURE of BMP280 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_TEMP      2             // Save TEMP of BMP280 to Unisens File on SD-Card
#define BIN_FILENAME_ACC          "acc.bin"
#define CSV_FILENAME_ACC          "acc.csv"
#define BIN_FILENAME_GYRO         "gyro.bin"
#define CSV_FILENAME_GYRO           "gyro.csv"
#define BIN_FILENAME_ANGLE          "angle.bin"
#define BIN_FILENAME_TEMP         "temp.bin"
#define CSV_FILENAME_TEMP         "temp.csv"
#define BIN_FILENAME_PRESS          "press.bin"
#define CSV_FILENAME_PRESS          "press.csv"
#define BIN_FILENAME_PRESS_TEMP       "temp2.bin"
#define CSV_FILENAME_PRESS_TEMP       "temp2.csv"
#define BIN_FILENAME_ADC          "adc.bin"
#define CSV_FILENAME_ADC          "adc.csv"
#define BIN_FILENAME_DAC          "dac.bin"
#define CSV_FILENAME_DAC          "dac.csv"
//KON
#define BIN_FILENAME_TRIGGER		"trigger.bin"
#define CSV_FILENAME_TRIGGER		"trigger.csv"
#define BIN_FILENAME_EXT1		"ext1.bin"
#define CSV_FILENAME_EXT1		"ext1.csv"
#define BIN_FILENAME_EXT2		"ext2.bin"
#define CSV_FILENAME_EXT2		"ext2.csv"

/****************************************************************************
 * Hardware Configuration Section
 *
 * Note: Do not change anything unless you know what to change!
 * **************************************************************************/

/*
 * Configuration for RGB LEDs
 *
 * Supported:
 * 				TrinkTracker v1 		- No
 * 				Wearable Platform v1 	- Yes
 */
#define CONFIG_LED_ENABLE						1							// Enable RGB LEDs
#define CONFIG_LED_PWM_AVAILABLE					1							// set if LED pins have PWM available
#define CONFIG_LED_RED_PORT						gpioPortA					// Port for Red LED
#define CONFIG_LED_RED_PIN						10							// Pin for Red LED
#define CONFIG_LED_GREEN_PORT					gpioPortA					// Port for Green LED
#define CONFIG_LED_GREEN_PIN					8							// Pin for Green LED
#define CONFIG_LED_BLUE_PORT					gpioPortA					// Port for Blue LED
#define CONFIG_LED_BLUE_PIN						9							// Pin for Blue LED


/*
 * Configuration for SD-Card
 *
 * Supported:
 * 				TrinkTracker v1 		- Yes, if IMST Module via SPI is not used
 * 				Wearable Platform v1 	- Yes
 *
 * 	Notes:
 * 				More config in ffconf.h
 */
/* Don't increase MICROSD_HI_SPI_FREQ beyond 8MHz. Next step will be 16MHz  */
/* which is out of spec. TODO check 12 and 16 MHz                           */
#define CONFIG_MICROSD_HI_SPI_FREQ     			8000000
#define CONFIG_MICROSD_LO_SPI_FREQ     			100000
#define CONFIG_MICROSD_USART           			USART2
#define CONFIG_MICROSD_LOC             			USART_ROUTE_LOCATION_LOC0
#define CONFIG_MICROSD_CMUCLOCK        			cmuClock_USART2
#define CONFIG_MICROSD_GPIOPORT        			gpioPortC
#define CONFIG_MICROSD_MOSIPIN         			2
#define CONFIG_MICROSD_MISOPIN         			3
#define CONFIG_MICROSD_CSPIN           			5
#define CONFIG_MICROSD_CLKPIN					4
#define CONFIG_MICROSD_ENPIN					1

/*
 * Configuration for MPU6050
 *
 * Supported:
 * 				TrinkTracker v1 		- Yes
 * 				Wearable Platform v1 	- Yes
 */
#define CONFIG_MPU6050_ENABLE					1							// Enable MPU6050
#define CONFIG_MPU6050_I2CBUS					0							// Used EFM32 I2C BUS

/*
 * Configuration for BMP180
 *
 * Supported:
 * 				TrinkTracker v1 		- Yes
 * 				Wearable Platform v1 	- Yes
 */
#define CONFIG_BMP180_ENABLE					0							// Enable BMP180
#define CONFIG_BMP180_I2CBUS					1							// Used EFM32 I2C BUS

/*
 * Configuration for BMP280
 *
 * Supported:
 * 				TrinkTracker v1 		- Yes
 * 				Wearable Platform v1 	- Yes
 */
#define CONFIG_BMP280_ENABLE					0							// Enable BMP280
#define CONFIG_BMP280_DOUBLE          			0             // Enable Second BMP280 with other Address
#define CONFIG_BMP280_I2CBUS					1							// Used EFM32 I2C BUS

/*
 * Configuration for ADXL345
 */
// If pin SDO/ALT ADDRESS is high or grounded ---> check ADXL345.h and change parameter (address)
#define CONFIG_ADXL345_ENABLE					0							// Enable ADXL345
#define CONFIG_ADXL345_I2CBUS					1							// Used EFM32 I2C BUS

/*
 * Configuration for BMP280
 */
// If pin SDO is high or grounded ---> check BMP280.h and change parameter (address)
#define CONFIG_BMP280_ENABLE					0							// Enable BMP280
#define CONFIG_BMP280_I2CBUS					1							// Used EFM32 I2C BUS
//#define CONFIG_BMP280_HI_SPI_FREQ     			8000000
//#define CONFIG_BMP280_LO_SPI_FREQ     			100000
//#define CONFIG_BMP280_USART           			USART1
//#define CONFIG_BMP280_LOC             			USART_ROUTE_LOCATION_LOC1
//#define CONFIG_BMP280_CMUCLOCK        			cmuClock_USART1
//#define CONFIG_BMP280_GPIOPORT        			gpioPortD
//#define CONFIG_BMP280_MOSIPIN         			0
//#define CONFIG_BMP280_MISOPIN         			1
//#define CONFIG_BMP280_CSPIN           			3
//#define CONFIG_BMP280_CLKPIN					2
//#define	BMP280_CS_DOWN 				GPIO->P[ BMP280_GPIOPORT ].DOUTCLR = 1 << BMP280_CSPIN /* CS pin low. */
//#define	BMP280_CS_UP				GPIO->P[ BMP280_GPIOPORT ].DOUTSET = 1 << BMP280_CSPIN /* CS pin high. */
//#define		BMP280_API
//#define 	BMP280

/*
 * Configuration for I2C Bus
 *
 * Supported:
 * 				TrinkTracker v1 		- Yes
 * 					I2C0->MPU6050, I2C1 -> External Header
 * 				Wearable Platform v1 	- Yes
 * 					I2C0->MPU6050, I2C1 -> External Header
 */
#define	CONFIG_I2C0_ENABLE						1							// Enable I2C0, Off=0 and On=1
#define CONFIG_I2C0_LOCATION					I2C_ROUTE_LOCATION_LOC1		// Set Location for I2C0
#define	CONFIG_I2C0_PORT						gpioPortD					// Port for I2C0
#define CONFIG_I2C0_PIN_SDA						6							// Pin for I2C0 SDA
#define CONFIG_I2C0_PIN_SCL						7							// Pin for I2C0 SCL
#define CONFIG_I2C0_FAST_MODE					1							// 0 = STANDARD = 100kHz, 1 = FAST = 400 kHz

#define CONFIG_I2C1_ENABLE						1							// Enable I2C1, Off=0 and On=1
#define CONFIG_I2C1_LOCATION					I2C_ROUTE_LOCATION_LOC1		// Set Location for I2C1
#define	CONFIG_I2C1_PORT						gpioPortB					// Port for I2C1
#define CONFIG_I2C1_PIN_SDA						11							// Pin for I2C1 SDA
#define CONFIG_I2C1_PIN_SCL						12							// Pin for I2C1 SCL
#define CONFIG_I2C1_FAST_MODE					0							// 0 = STANDARD = 100kHz, 1 = FAST = 400 kHz

// TO TEST ADXL345/BMP280 I2C WITH EVALBOARD:
//#define CONFIG_I2C1_ENABLE						1							// Enable I2C1, Off=0 and On=1
//#define CONFIG_I2C1_LOCATION					I2C_ROUTE_LOCATION_LOC0		// Set Location for I2C1
//#define	CONFIG_I2C1_PORT						gpioPortC					// Port for I2C1
//#define CONFIG_I2C1_PIN_SDA						4							// Pin for I2C1 SDA
//#define CONFIG_I2C1_PIN_SCL						5							// Pin for I2C1 SCL
//#define CONFIG_I2C1_FAST_MODE					1							// 0 = STANDARD = 100kHz, 1 = FAST = 400 kHz

/* BLE113 configuration */
#define BLE113_RESET_PORT						gpioPortE
#define BLE113_RESET_PIN						14
#define CONFIG_UART_SEND 						1


/* LEUART1 config*/
#define LEUART1_PORT							gpioPortA
#define LEUART1_CT_PIN							3
#define LEUART1_RT_PIN							4
#define LEUART1_TX_PIN							5
#define LEUART1_RX_PIN							6
#define LEUART_COM_STARTBYTE					0x11
#define LEUART_COM_STOPBYTE						0x13


#endif

#endif /* CONFIG_INEAR_V2_1_H_ */
