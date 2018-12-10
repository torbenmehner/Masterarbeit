/******************************************************************************
 * @file config_inEar_v2.h
 * @brief Configuration File for inEar v2 Project
 * @author czimmer@fzi.de
 * @version 0.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2016 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2015-02-15	0.1		czimmer 	Initial Version, needs to be cleanded up
 * 2016-05-11 0.2   czimmer   Refactoring
 *
 * *****************************************************************************/
#ifndef CONFIG_INEAR_V2_H_
#define CONFIG_INEAR_V2_H_

#include "../config.h"
#include "board_list.h"

#if CONFIGSYSTEM==INEARV2

#define BOARD_TYPE BOARD_INEAR_V2_1

#define CONFIG_VERSION							70304						//Last digit of year, Month, Day

/* Debug Outputs */
#define CONFIG_DEBUG_PRINTOUT_ENABLE			1							// Enables Print Out on SWO for Debugging
#define CONFIG_DEBUG_LED_ENABLE					1							// Enables LED for Debugging


#define CONFIG_DEBUG_UART_TTL 					0




#define CONFIG_TT_RF_BLUEGIGA					2
#define CONFIG_POWER_SAFE_ENABLE				1							// Enables Power Saving

// TODO CLEANUP!!!!
#define CONFIG_BUFFERSIZE_ACC					1024//512//1024						// Buffer Size of Accelerometer Buffer in Bytes
#define CONFIG_BUFFERSIZE_GYRO					1024//512//1024						// Buffer Size of Gyro Buffer in Bytes
#define CONFIG_BUFFERSIZE_ANGLE					1024//512//1024						// Buffer Size of ANGLE Buffer in Bytes
//#define CONFIG_BUFFERSIZE_FFT_STATIC			2048						// Buffer for FFT
#define CONFIG_BUFFERSIZE_BLE					264//1024						// Buffer for BLE
#define CONFIG_BUFFERSIZE_TEMP					1024						// Buffer Size of Temperature Buffer in Bytes
#define CONFIG_BUFFERSIZE_ADC					1024//512						// Buffer Size of Adc Buffer in Bytes
#define CONFIG_BUFFERSIZE_PRESS					1024						// Buffer for Pressure
#define CONFIG_BUFFERSIZE_CORRELATE_PULSE		512 //in Byte
#define PRE_FILTER_BUFFER						16

#define CONFIG_SYSTEM_HFRCO_FREQ				14000000					// Low Frequency Oscillator Frequency
#define CONFIG_SYSTEM_HFXO_FREQ					48000000					// High Frequency Oscillator Frequency

// TrinkTracker Values
#define CONFIG_TT_TRESSHOLD_MAX_ACC				2000						// 4 g tresshold
#define CONFIG_TT_TRESSHOLD_MAX_TIMER_RUNS		7680						// Set Data valid Treshhold in Timer Ticks of Timer0, with 7680 and 128Hz Timer this means 60s
#define CONFIG_TT_TRESHHOLD_MIN_TIMER_RUNS		512							// Set Data valid Treshhold in Timer Ticks of Timer0, with 512 and 128Hz Timer this means 4s

//TODO END CLEANUP
//#define CONFIG_BUFFERSIZE_PRESS					768		// in bytes

/*
 * Configure Clocks
 */
#define CONFIG_SYSTEM_HFRCO_FREQ        14000000          // Internal High Frequency Oscillator Frequency
#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER0_TOP						1711						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER1_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER1_TOP						2390						// 314 Hz with 48MHz and 64-Prescaling -> 2390
#define CONFIG_TIMER2_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER2_TOP						2390						// 256 Hz with 48MHz and 32-Prescaling -> 5859, 128 Hz with 48MHz and 64-Prescaling -> 5859

///*Backup*/
//#define CONFIG_SYSTEM_HFRCO_FREQ        14000000          // Internal High Frequency Oscillator Frequency
//#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
//#define CONFIG_TIMER0_TOP						1711						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
//#define CONFIG_TIMER1_PRESCALE					timerPrescale64				// Prescaler for Timer 0
//#define CONFIG_TIMER1_TOP						1708						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
//#define CONFIG_TIMER2_PRESCALE					timerPrescale64				// Prescaler for Timer 0
//#define CONFIG_TIMER2_TOP						2390						// 256 Hz with 48MHz and 32-Prescaling -> 5859, 128 Hz with 48MHz and 64-Prescaling -> 5859

/*
 * ADC of EFM32
 * currently only support for one Source
 */
#define CONFIG_ADC_MYO_ENABLE					0							// Switch ADC for Myo on
#define CONFIG_ADC_TT_ENABLE					1							// Switch ADC for TrinkTracker on //TODO muss umbenannt werden
#define CONFIG_ADC_BATT_ENABLE					0							//TODO not used yet Switch ADC for Battery on
#define CONFIG_ADC_TEMP_ENABLE					0							//TODO not used yet Switch ADC for internal Temp Sensor on
#define CONFIG_ADC_CONTINUOUS_SAMPLING			1							// Continuous Sampling of ADC Data from Timer1
#define CONFIG_ADC_TT_SAMPLING					0							// ACD Sampling before/after each measurment

/*
 * ACC & Gyro & Interrupts of MPU6050
 */
#define CONFIG_MPU6050_ACC_ENABLE				0							//TODO not used yet Switch ACC of MPU6050 on
#define CONFIG_MPU6050_ACC_LSB					0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SAMPLERATE_DLPF		0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SAMPLERATE			0							//TODO not used yet
#define CONFIG_MPU6050_ACC_SLEEP_SAMPLERATE		0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_ENABLE				0							//TODO not used yet Switch GYRO of MPU6050 on
#define CONFIG_MPU6050_GYRO_LSB					0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_SAMPLERATE_DLPF		0							//TODO not used yet
#define CONFIG_MPU6050_GYRO_SAMPLERATE			0							//TODO not used yet
#define CONFIG_MPU6050_TEMP_ENABLE				0							//TODO not used yet  Switch TEMP of MPU6050 on
#define CONFIG_MPU6050_INT_ENABLE				0							// Switch Interrupt of MPU6050 on
#define CONFIG_MPU6050_INT_TRESHHOLD_VALUE 		0x01						// Set Interrupt Treshhold Value of MPU650 in [2mg] for Wakeup
#define CONFIG_MPU6050_INT_TRESHHOLD_DURATION 	0x02						// Set Interrupt Treshhold Duration of MPU650 in [ms] for Wakeup
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_ACC		400 //800					// Set Sleep Treshhold of two following Values in Value *[0.0610mg] for Sleep, Value has to be lower to go to sleep
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_GYRO		2400 //32765				// Set Sleep Treshhold of two following Values in Value *[??s] for Sleep, Value has to be lower to go to sleep
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_DURATION	1024						// Set Sleep Treshhold Value in Timer Ticks of Timer0, with 1024 and 256Hz Timer this means 4s

/*
 * Saving to Unisens
 * 0 - No Saving
 * 1 - Save as CSV // Currently not working for all data
 * 2 - Save as BIN
 */
#define CONFIG_SAVEUNISENS 						1							// Save any Data to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ACC 			0							// Save ACC of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_GYRO 		0							// Save GYRO of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ANGLE 		0							// Computed Angle from ACC & GYRO of MPU6050
#define CONFIG_SAVEUNISENS_MPU6050_TEMP			0							// Save TEMP of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_PRESS			2							// Save PRESSURE of BMP280 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_TEMP			2							// Save TEMP of BMP280 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_FFT			0							// Save FFT of BMP280 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_TRIGGER				0							// Save Trigger from Button
#define CONFIG_SAVEUNISENS_EFM32_ADC_TT			2							// Save Blood Pressure or ECG  Unisens File on SD-Card


#define CONFIG_LED_ENABLE           	1             // Enable RGB LEDs
#define CONFIG_LL_ENABLE				0				// Enable Looping Louis GPIO
  /*
   * Configuration for I2C Bus
   */
  #define CONFIG_I2C0_ENABLE            1             // Enable I2C0, Off=0 and On=1   //TODO
  #define CONFIG_I2C1_ENABLE            0             // Enable I2C1, Off=0 and On=1   //TODO
  /*
   * Configuration for MPU6050
   *
   * Supported:
   *        TrinkTracker v1     - Yes
   *        Wearable Platform v1  - Yes
   */
  #define CONFIG_MPU6050_ENABLE         0            // Enable MPU6050

//  /*
//   * Configuration for BMP180
//   *
//   * Supported:
//   *        TrinkTracker v1     - Yes
//   *        Wearable Platform v1  - Yes
//   */
//  #define CONFIG_BMP180_ENABLE          0             // Enable BMP180
//  #define CONFIG_BMP180_I2CBUS          1             // Used EFM32 I2C BUS

  /*
   * Configuration for BMP280
   *
   * Supported:
   *        TrinkTracker v1     - Yes
   *        Wearable Platform v1  - Yes
   */
  #define CONFIG_BMP280_ENABLE          1             // Enable BMP280
  #define CONFIG_BMP280_DOUBLE          1             // Enable Second BMP280 with other Address
  #define CONFIG_BMP280_I2CBUS          0             // Used EFM32 I2C BUS
  #define CONFIG_BMP280_SPIBUS          1             // Used EFM32 SPI BUS
  #define CONFIG_BMP280_SPIBUS0_ENABLE          1             // Used EFM32 SPI BUS
  #define CONFIG_BMP280_SPIBUS1_ENABLE          1             // Used EFM32 SPI BUS

  #if (CONFIG_BMP280_DOUBLE == 1)
 	#if (CONFIG_BMP280_SPIBUS0_ENABLE == 0) || (CONFIG_BMP280_SPIBUS1_ENABLE  == 0)
    #error CONFIG_BMP280_DOUBLE eingeschaltet, ohne CONFIG_BMP280_SPIBUS0_ENABLE bzw. CONFIG_BMP280_SPIBUS1_ENABLE an
	#endif
  #endif


  #define SPI_BAUDRATE				115200

/** (Approximate) sample rate used for sampling data. */

  #define SAMPLE_RATE           		        78.5
  #define SAMPLE_RATE_BREATH	                19.625
  //#define CONFIG_BMP280_HI_SPI_FREQ           8000000
  //#define CONFIG_BMP280_LO_SPI_FREQ           100000
  //#define CONFIG_BMP280_USART                 USART1
  //#define CONFIG_BMP280_LOC                   USART_ROUTE_LOCATION_LOC1
  //#define CONFIG_BMP280_CMUCLOCK              cmuClock_USART1
  //#define CONFIG_BMP280_GPIOPORT              gpioPortD
  //#define CONFIG_BMP280_MOSIPIN               0
  //#define CONFIG_BMP280_MISOPIN               1
  //#define CONFIG_BMP280_CSPIN                 3
  //#define CONFIG_BMP280_CLKPIN          2
  //#define BMP280_CS_DOWN        GPIO->P[ BMP280_GPIOPORT ].DOUTCLR = 1 << BMP280_CSPIN /* CS pin low. */
  //#define BMP280_CS_UP        GPIO->P[ BMP280_GPIOPORT ].DOUTSET = 1 << BMP280_CSPIN /* CS pin high. */
  //#define   BMP280_API
  //#define   BMP280

	//FFT
	#define CONFIG_BUFFERSIZE_FFT_STATIC		4096// Buffer for FFT
	#define CONFIG_BUFFERSIZE_FFT_SOLUTION		2048// Buffer for FFT

	#define BUFFER_SAMPLES                  	512 // Supported FFT Lengths are 128, 512, 2048
	#define LOWEST_FREQ_PULSE					0.83 // Hz
	#define HIGHEST_FREQ_PULSE					3.33 // Hz
	#define LOWEST_FREQ_BREATH					0.08 // Hz
	#define HIGHEST_FREQ_BREATH					0.33 // Hz

	//OFFSET
	#define OFFSET_SIZE							127 // 2er potenz - 1
	#define OFFSET_VARIATION					200 // after clean up the signal from Offset added Offset to get only pos. values

	//FIR
	#define CONFIG_BUFFERSIZE_FIR_STATIC		4096//

	//Correlate
	#define 	CONFIG_BUFFERSIZE_CORRELATE_PULSE	512 //in Byte
    #define 	SAMPLERATE_PEAK						78.5

	//LEUART BLE
	#define BUFFERSIZE        256		//byte
	#define LEUART_COM_STARTBYTE					0x11
	#define LEUART_COM_STOPBYTE						0x13
//	#define UART_LOC LEUART_ROUTE_LOCATION_LOC1
//	#define SERIAL_GPIOPORT gpioPortA
//	#define SERIAL_TX_OUT_PIN 5
//	#define SERIAL_RX_IN_PIN 6
	#define SERIAL_BAUD	9600
	#define SERIAL_DATABITS  leuartDatabits8
	#define SERIAL_PARITY leuartNoParity
	#define SERIAL_STOPBITS leuartStopbits2

	#define SERIAL_IRQ LEUART1_IRQn
	#define SERIAL_IRQ_HAN LEUART1_IRQHandler



/*
 * Sanity Checks
 */

// Include standard defines
#include "boards.h"
#include "conditionals.h"
#endif

#endif /* CONFIG_TRINKTRACKER_V2_H_ */
