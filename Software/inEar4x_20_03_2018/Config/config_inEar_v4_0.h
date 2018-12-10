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
#ifndef CONFIG_INEAR_V4_0_H_
#define CONFIG_INEAR_V4_0_H_
#include "../config.h"
#if CONFIGSYSTEM==INEARV4_0

#define CONFIG_DEBUG_PRINTOUT_ENABLE			0							// Enables Print Out on SWO for Debugging Achtung wenn enable kein SD Support
																			// Tell CSMIS-DSP Lib to use Lib for Cortex M3
#define CONFIG_SYSTEM_TYPE						0



#define BUFFER_SAMPLES							512

#define SD_WRITE_VALUES 	512 // in bytes (SECTOR SIZE)
#define BLE_WRITE_VALUES 	80 // in bytes (SECTOR SIZE)


/*
 * Timer0 of EFR32
 */
#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER0_TOP						1708	//987					// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER1_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER1_TOP						1708						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER2_PRESCALE          		timerPrescale32       // Prescaler for Timer 0
#define CONFIG_TIMER2_TOP           			5859            // 256 Hz with 48MHz and 32-Prescaling -> 5859, 128 Hz with 48MHz and 64-Prescaling -> 5859


// TODO CLEANUP!!!!
#define CONFIG_BUFFERSIZE_SENS 					1024
#define CONFIG_BUFFERSIZE_ACC 					1024
#define CONFIG_BUFFERSIZE_BLE 					256


#define CONFIG_BUFFERSIZE_ACC					1024						// Buffer Size of Accelerometer Buffer in Bytes
#define CONFIG_BUFFERSIZE_GYRO					1024						// Buffer Size of Gyro Buffer in Bytes
#define CONFIG_BUFFERSIZE_TEMP					1024						// Buffer Size of Temperature Buffer in Bytes
#define CONFIG_BUFFERSIZE_RTCC					1024						// Buffer Size of Temperature Buffer in Bytes
#define CONFIG_BUFFERSIZE_ADC					1024						// Buffer Size of Adc Buffer in Bytes
#define CONFIG_SYSTEM_HFRCO_FREQ				14000000					// Low Frequency Oscillator Frequency
#define CONFIG_SYSTEM_HFXO_FREQ					38400000					// High Frequency Oscillator Frequency
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

#define CONFIG_SAVEUNISENS_BMP280_PRESS     2             // Save PRESSURE of BMP280 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_BMP280_TEMP      2             // Save TEMP of BMP280 to Unisens File on SD-Card



/****************************************************************************
 * Hardware Configuration Section
 *
 * Note: Do not change anything unless you know what to change!
 * **************************************************************************/

/*
 * Configuration for BLE SYNC
 */
//#define CONFIG_SYNC_RX_PIN				    7							// Pin for BLE RX
#define CONFIG_SYNC_TX_PIN						9							// Pin for BLE TX

/*
 * Configuration for SAMPLE time
 */
#define CONFIG_SAMPLE_TIMERCOUNT				8

/*
 * Configuration for RGB LEDs
 */
#define CONFIG_LED_ENABLE						1							// Enable RGB LEDs
#define CONFIG_LED_PWM_AVAILABLE				0							// set if LED pins have PWM available
#define CONFIG_LED_RED_PORT						gpioPortC					// Port for Red LED
#define CONFIG_LED_RED_PIN						9							// Pin for Red LED
#define CONFIG_LED_GREEN_PORT					gpioPortC					// Port for Green LED
#define CONFIG_LED_GREEN_PIN					11							// Pin for Green LED
#define CONFIG_LED_BLUE_PORT					gpioPortC					// Port for Blue LED
#define CONFIG_LED_BLUE_PIN						10							// Pin for Blue LED


/*
 * Configuration for Button
 */
#define CONFIG_BUTTON_PORT						gpioPortA					// Port for Button
#define CONFIG_BUTTON_PIN						5							// Pin for Button

/*
 * Configuration BMI160 SPI
 */
#define CONFIG_BMI160_ENABLE           			1
#define CONFIG_BMI160_VCC_ENABLE				1
#define CONFIG_BMI_PORT_VCC						gpioPortD
#define CONFIG_BMI_PIN_VCC						12
#define CONFIG_BMI_USART           				USART3
#define CONFIG_BMI_CMUCLOCK        				cmuClock_USART3
#define CONFIG_BMI_BAUDRATE						57600
#define CONFIG_BMI_LOC_CLK						USART_ROUTELOC0_CLKLOC_LOC3
#define CONFIG_BMI_LOC_CS						USART_ROUTELOC0_CSLOC_LOC31
#define CONFIG_BMI_LOC_RX						USART_ROUTELOC0_RXLOC_LOC6
#define CONFIG_BMI_LOC_TX						USART_ROUTELOC0_TXLOC_LOC6
#define CONFIG_BMI_PORT_CLK						gpioPortD
#define CONFIG_BMI_PIN_CLK						13
#define CONFIG_BMI_PORT_CS						gpioPortD
#define CONFIG_BMI_PIN_CS						10
#define CONFIG_BMI_PORT_RX						gpioPortD
#define CONFIG_BMI_PIN_RX						15
#define CONFIG_BMI_PORT_TX						gpioPortD
#define CONFIG_BMI_PIN_TX						14

#define	CONFIG_I2C0_ENABLE						0							// Enable I2C0, Off=0 and On=1
#define CONFIG_BMI_LOC_SDA						I2C_ROUTELOC0_SDALOC_LOC18		// Set Location for I2C0
#define CONFIG_BMI_LOC_SCL						I2C_ROUTELOC0_SCLLOC_LOC18
#define	CONFIG_BMI_I2C0_PORT_SDA				gpioPortD					// Port for I2C0
#define CONFIG_BMI_I2C0_PIN_SDA						10							// Pin for I2C0 SDA
#define	CONFIG_BMI_I2C0_PORT_SCL				gpioPortD					// Port for I2C0
#define CONFIG_BMI_I2C0_PIN_SCL						11							// Pin for I2C0 SCL
#define	CONFIG_BMI_I2C0_PORT_ADD				gpioPortD
#define CONFIG_BMI_I2C0_PIN_ADD						9
#define	CONFIG_BMI_I2C0_PORT_PROT				gpioPortA
#define CONFIG_BMI_I2C0_PIN_PROT					11
#define CONFIG_I2C0_FAST_MODE					1							// 0 = STANDARD = 100kHz, 1 = FAST = 400 kHz
/*
 * Configuration SENSOR SPI
 */
#define CONFIG_SPI_SENSOR_ENABLE				1

#define CONFIG_BMP280_ENABLE           			0
#define CONFIG_BMP388_ENABLE           			0
#define CONFIG_AFE44x0_ENABLE           		1
#define CONFIG_ADS129x_ENABLE           		0
#define CONFIG_BME680_ENABLE  					0

#define CONFIG_SENSOR_USART           			USART0
#define CONFIG_SENSOR_CMUCLOCK        			cmuClock_USART0

#if CONFIG_BMP280_ENABLE == 1
	#define CONFIG_SENSOR_BAUDRATE					115200
	#define CONFIG_SENSOR_CLOCKMODE					usartClockMode0
#elif	CONFIG_AFE44x0_ENABLE == 1
	#define CONFIG_SENSOR_BAUDRATE					3125000
	#define CONFIG_SENSOR_CLOCKMODE					usartClockMode0
#elif	CONFIG_ADS129x_ENABLE == 1
	#define CONFIG_SENSOR_BAUDRATE					500000
	#define CONFIG_SENSOR_CLOCKMODE					usartClockMode1

#elif	CONFIG_BME680_ENABLE == 1
	#define CONFIG_SENSOR_BAUDRATE					115200
	#define CONFIG_SENSOR_CLOCKMODE					usartClockMode0
#elif	CONFIG_BMP388_ENABLE == 1
	#define CONFIG_SENSOR_BAUDRATE					115200
	#define CONFIG_SENSOR_CLOCKMODE					usartClockMode0
#endif


	#define CONFIG_ADS129x_RDY_PORT					gpioPortF
	#define CONFIG_ADS129x_RDY_PIN					7
	#define CONFIG_AFE44x0_RDY_PORT				gpioPortF
	#define CONFIG_AFE44x0_RDY_PIN				7
	#define CONFIG_ADS1292_RDY_PORT				gpioPortF
	#define CONFIG_ADS1292_RDY_PIN				7

	#define CONFIG_ADS1292_CLK_SEL_PORT			gpioPortD //°!!!!! falsch bisher
	#define CONFIG_ADS1292_CLK_SEL_PIN			12
	#define CONFIG_ADS1292_RESET_PORT				gpioPortD
	#define CONFIG_ADS1292_RESET_PIN				14

#define CONFIG_SENSOR_LOC_CLK					USART_ROUTELOC0_CLKLOC_LOC27
#define CONFIG_SENSOR_LOC_CS					USART_ROUTELOC0_CSLOC_LOC27
#define CONFIG_SENSOR_LOC_RX					USART_ROUTELOC0_RXLOC_LOC27
#define CONFIG_SENSOR_LOC_TX					USART_ROUTELOC0_TXLOC_LOC8
#define CONFIG_SENSOR_PORT_CLK					gpioPortF
#define CONFIG_SENSOR_PIN_CLK					5
#define CONFIG_SENSOR_PORT_CS					gpioPortF
#define CONFIG_SENSOR_PIN_CS					6
#define CONFIG_SENSOR_PORT_RX					gpioPortF
#define CONFIG_SENSOR_PIN_RX					4
#define CONFIG_SENSOR_PORT_TX					gpioPortB
#define CONFIG_SENSOR_PIN_TX					13

#if CONFIG_BMP280_ENABLE
	#define CONF_DEVICE_NUM  						1
#endif

#if CONFIG_AFE44x0_ENABLE
	#define CONF_DEVICE_NUM  						1
#endif

#if CONFIG_ADS129x_ENABLE
	#define CONF_DEVICE_NUM  						3
#endif

#if CONFIG_BME680_ENABLE
	#define CONF_DEVICE_NUM  						4
#endif

#if CONFIG_BMP388_ENABLE
	#define CONF_DEVICE_NUM  						6
#endif


#if CONFIG_BMP280_ENABLE
	#define BIN_FILENAME_ACCGYRO          "accgyro_press.bin"
	#define BIN_FILENAME_SENS          		"sens_press.bin"
#endif

#if CONFIG_BMP388_ENABLE
	#define BIN_FILENAME_ACCGYRO          "accgyro_press.bin"
	#define BIN_FILENAME_SENS          		"sens_press.bin"
#endif

#if CONFIG_AFE44x0_ENABLE
	#define BIN_FILENAME_ACCGYRO          "accgyro_ppg.bin"
	#define BIN_FILENAME_SENS          		"sens_ppg.bin"
#endif

#if CONFIG_ADS129x_ENABLE
	#define BIN_FILENAME_ACCGYRO          "accgyro_ekg.bin"
	#define BIN_FILENAME_SENS          		"sens_ekg.bin"
#endif

#if CONFIG_BME680_ENABLE
	#define BIN_FILENAME_ACCGYRO          "accgyro_gas.bin"
	#define BIN_FILENAME_SENS          		"sens_gas.bin"
#endif


//Button
#define DBL_CLICK_TIMEOUT   16384  //500ms
#define LONG_PRESS_TIMEOUT  16384  //500ms

#define CLICK_BASE          20
#define CLICK_BUTTON           28
#define LONG_PRESS_BASE     40
#define LONG_PRESS_BUTTON      48
#define DBL_CLICK_BASE      60
#define DBL_CLICK_BUTTON       68

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
#define CONFIG_MICROSD_ENABLE           		1
#define CONFIG_MICROSD_VCC_ENABLE				0
#define CONFIG_MICROSD_HI_SPI_FREQ     			16000000
#define CONFIG_MICROSD_LO_SPI_FREQ     			100000
#define CONFIG_MICROSD_USART           			USART1
#define CONFIG_MICROSD_CMUCLOCK        			cmuClock_USART1
#define CONFIG_MICROSD_LOC_CLK					USART_ROUTELOC0_CLKLOC_LOC11
#define CONFIG_MICROSD_LOC_CS					USART_ROUTELOC0_CSLOC_LOC8
#define CONFIG_MICROSD_LOC_RX					USART_ROUTELOC0_RXLOC_LOC11
#define CONFIG_MICROSD_LOC_TX					USART_ROUTELOC0_TXLOC_LOC26
#define CONFIG_MICROSD_PORT_CLK					gpioPortC
#define CONFIG_MICROSD_PIN_CLK					8
#define CONFIG_MICROSD_PORT_CS					gpioPortC
#define CONFIG_MICROSD_PIN_CS					6
#define CONFIG_MICROSD_PORT_RX					gpioPortC
#define CONFIG_MICROSD_PIN_RX					7
#define CONFIG_MICROSD_PORT_TX					gpioPortF
#define CONFIG_MICROSD_PIN_TX					2
#define CONFIG_MICROSD_PORT_VCC					gpioPortA
#define CONFIG_MICROSD_PIN_VCC					2


#define CONFIG_HIL_ENABLE						0
#define CONFIG_HIL_FILE 						"adc.bin"
#define CONFIG_HIL_BUFSIZE    					2

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


#endif

#endif /* CONFIG_INEAR_V2_1_H_ */
