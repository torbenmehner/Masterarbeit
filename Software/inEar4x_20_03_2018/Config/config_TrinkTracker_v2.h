/******************************************************************************
 * @file config_TrinkTracker_v2.h
 * @brief Configuration File for TrinkTracker v2 Project
 * @author czimmer@fzi.de
 * @version 0.6
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2015 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2015-02-15	0.1		czimmer 	Initial Version
 * 2015-05-05	0.2		czimmer 	GIT Version, from now on TrinkTracker v2 Only
 * 2015-07-15	0.3		czimmer 	Merging of TrinkTracker v2 and dev
 * 2015-08-10	0.4		czimmer		New Debug Variables, added Option for Scale Fix
 * 2015-11-04	0.5		czimmer		New Variables
 * 2016-01-08	0.6		czimmer 	Power Supply Cfg
 *
 * *****************************************************************************/
#ifndef CONFIG_TRINKTRACKER_V2_H_
#define CONFIG_TRINKTRACKER_V2_H_

#include "../config.h"
#include "board_list.h"

#if CONFIGSYSTEM==TRINKTRACKERV2

#define BOARD_TYPE BOARD_TRINKTRACKER_V2

#define CONFIG_VERSION							60509						//Last digit of year, Month, Day

/* Debug Outputs */
#define CONFIG_DEBUG_PRINTOUT_ENABLE			1							// Enables Print Out on SWO for Debugging
#define CONFIG_DEBUG_LED_ENABLE					1							// Enables LED for Debugging
#define CONFIG_DEBUG_TRANSMIT_ENABLE			1							// Enables Transmit via IMST 868MHz Modul for Debugging


#define CONFIG_TT_ADC_HX711						0							// Uses HX711 instead of internal ADC / DAC
#define CONFIG_TT_SCALE_EMPTY_CUP_FIX			1							// If Enabled, System will only send out a message when the cup has been emptied for the first time, if 0 true scale Value will be used
#define CONFIG_TT_SCALE_CUP_WEIGHT				33
#define CONFIG_TT_SCALE_CUP_FLUID_WEIGHT		230
//#define CONFIG_TT_RF_IMST						1
#define CONFIG_TT_RF_BLUEGIGA					0
#define CONFIG_POWER_SAFE_ENABLE				1							// Enables Power Saving
#define CONFIG_POWER_SAFE_IMST_ENABLE			0							// Enables Power Saving for IMST Modules
#define CONFIG_IMST_BLE_ENABLE					0							// Enables IMST BLE Module, takes care of sleeping
#define CONFIG_IMST_BLE_SCANNING				0							// Enables Scanning of BLE Tags
//#define CONFIG_IMST_LORA_ENABLE					1							// Enables Lora module for Transmitting
#define CONFIG_IMST_LORA_DEFAULT_F				0							// Sets Lora Module to default frequency


// TODO CLEANUP!!!!
#define CONFIG_BUFFERSIZE_ACC					1024						// Buffer Size of Accelerometer Buffer in Bytes
#define CONFIG_BUFFERSIZE_GYRO					1024						// Buffer Size of Gyro Buffer in Bytes
#define CONFIG_BUFFERSIZE_ANGLE					1024						// Buffer Size of ANGLE Buffer in Bytes
#define CONFIG_BUFFERSIZE_TEMP					1024						// Buffer Size of Temperature Buffer in Bytes
#define CONFIG_BUFFERSIZE_ADC					1024						// Buffer Size of Adc Buffer in Bytes
#define CONFIG_BUFFERSIZE_DAC					1024


// TrinkTracker Values
#define CONFIG_TT_TRESSHOLD_MAX_ACC				2000						// 4 g tresshold
#define CONFIG_TT_TRESSHOLD_MAX_TIMER_RUNS		7680						// Set Data valid Treshhold in Timer Ticks of Timer0, with 7680 and 128Hz Timer this means 60s
#define CONFIG_TT_TRESHHOLD_MIN_TIMER_RUNS		512							// Set Data valid Treshhold in Timer Ticks of Timer0, with 512 and 128Hz Timer this means 4s

//TODO END CLEANUP
//#define CONFIG_BUFFERSIZE_PRESS					768		// in bytes

/*
 * Configure Clocks
 */
// Note Timer 0 and 1 used by IMST
#define CONFIG_SYSTEM_HFRCO_FREQ        14000000          // Internal High Frequency Oscillator Frequency
#define CONFIG_TIMER0_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER0_TOP						1711						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER1_PRESCALE					timerPrescale64				// Prescaler for Timer 0
#define CONFIG_TIMER1_TOP						1708						// 256 Hz with 14MHz and 32-Prescaling -> 1708, 128 Hz with 14MHz and 64-Prescaling -> 1708
#define CONFIG_TIMER2_PRESCALE					timerPrescale32				// Prescaler for Timer 0
#define CONFIG_TIMER2_TOP						5859						// 256 Hz with 48MHz and 32-Prescaling -> 5859, 128 Hz with 48MHz and 64-Prescaling -> 5859

/*
 * ADC of EFM32
 * currently only support for one Source
 */
#define CONFIG_ADC_MYO_ENABLE					0							// Switch ADC for Myo on
#define CONFIG_ADC_TT_ENABLE					1							// Switch ADC for TrinkTracker on
#define CONFIG_ADC_BATT_ENABLE					0							//TODO not used yet Switch ADC for Battery on
#define CONFIG_ADC_TEMP_ENABLE					0							//TODO not used yet Switch ADC for internal Temp Sensor on
#define CONFIG_ADC_CONTINUOUS_SAMPLING			0							// Continuous Sampling of ADC Data from Timer2
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
#define CONFIG_MPU6050_INT_TRESHHOLD_VALUE 		0x01						// Set Interrupt Treshhold Value of MPU650 in [2mg] for Wakeup
#define CONFIG_MPU6050_INT_TRESHHOLD_DURATION 	0x02						// Set Interrupt Treshhold Duration of MPU650 in [ms] for Wakeup
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_ACC		500 //800							// Set Sleep Treshhold of two following Values in Value *[0.0610mg] for Sleep, Value has to be lower to go to sleep
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_GYRO		2400 //32765						// Set Sleep Treshhold of two following Values in Value *[??s] for Sleep, Value has to be lower to go to sleep
#define CONFIG_MPU6050_SLEEP_TRESHHOLD_DURATION	1024						// Set Sleep Treshhold Value in Timer Ticks of Timer0, with 1024 and 256Hz Timer this means 4s

/*
 * Saving to Unisens
 * 0 - No Saving
 * 1 - Save as CSV // Currently not working for all data
 * 2 - Save as BIN
 */
#define CONFIG_SAVEUNISENS 						1							// Save any Data to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ACC 			2							// Save ACC of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_GYRO 		2							// Save GYRO of MPU6050 to Unisens File on SD-Card
#define CONFIG_SAVEUNISENS_MPU6050_ANGLE 		2							// Computed Angle from ACC & GYRO of MPU6050
#define CONFIG_SAVEUNISENS_MPU6050_TEMP			2							// Save TEMP of MPU6050 to Unisens File on SD-Card

/****************************************************************************
 * Hardware Configuration Section
 *
 * Note: Do not change anything unless you know what to change!
 * **************************************************************************/

#define CONFIG_HAS_IMST_RF 1
#define CONFIG_HAS_QI_BQ51013B 1
/*
 * Configuration for RGB LEDs
 *
 * Supported:
 * 				TrinkTracker v1 		- No
 * 				TrinkTracker v2 		- Yes
 * 				Wearable Platform v1 	- Yes
 */
#define CONFIG_LED_ENABLE						1							// Enable RGB LEDs



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
 * Configuration for ADXL345
 */
// If pin SDO/ALT ADDRESS is high or grounded ---> check ADXL345.h and change parameter (address)
#define CONFIG_ADXL345_ENABLE					0							// Enable ADXL345
#define CONFIG_ADXL345_I2CBUS					1							// Used EFM32 I2C BUS

/*
 * Configuration for I2C Bus
 * 				TrinkTracker v2 		- Yes
 * 					I2C0->MPU6050, I2C1->ADXL345
 */

#define CONFIG_I2C1_ENABLE						0							// Enable I2C1, Off=0 and On=1



//------------------------------------------------------------------------------
//
// Section Include Files FROM IMST TODO Clean up
//
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//
// Section Oscillator & Frequency Settings
//
//------------------------------------------------------------------------------



//#define BSP_XTAL_FREQ_MHZ               ( 14 )
//#define BSP_XTAL_FREQ_HZ                ( 14000000UL )


#define BSP_XTAL_FREQ_MHZ               ( 48 )
#define BSP_XTAL_FREQ_HZ                ( 48000000UL )



// true for external, false for internal
#define BSP_RTC_USE_EXTERNAL    true


//------------------------------------------------------------------------------
//
// Section User Interface (UI)
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
// Section USART HOST Interface
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
// Section SPI HOST Interface
//
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//
// Section I2C / TWI Interface
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
// Section RF Transceiver
//
//------------------------------------------------------------------------------

// define Radio Version
#define USE_SX1276_RADIO
#define LORA                    1 // [0: OFF, 1: ON]
#define USE_LORA_MODE
//#define iM880A über compiler definiert



#define BSP_SPI_TRX_INTERFACE              USART2
#define BSP_SPI_TRX_LOCATION               0
#define BSP_SPI_TRX_IF_NR                  2
#define BSP_SPI_TRX_BAUDRATE               3800000ul   // 4 MHz





// SPI Chip Select RF
#define BSP_SPI_TRX_GPIO_CS_PORT            gpioPortC
#define BSP_SPI_TRX_GPIO_CS_PIN_NR          1
#define BSP_SPI_TRX_GPIO_CS_PIN_MASK        (1 << BSP_SPI_TRX_GPIO_CS_PIN_NR)

// Reset RF
#define BSP_GPIO_TRX_RST_PORT               gpioPortA
#define BSP_GPIO_TRX_RST_PIN_NR             0
#define BSP_GPIO_TRX_RST_PIN_MASK           (1 << BSP_GPIO_TRX_RST_PIN_NR)

// TCXO Enable
#define BSP_GPIO_TRX_TCXO_EN_PORT           gpioPortA
#define BSP_GPIO_TRX_TCXO_EN_PIN_NR         1
#define BSP_GPIO_TRX_TCXO_EN_PIN_MASK       (1 << BSP_GPIO_TRX_TCXO_EN_PIN_NR)

// VDD LDO Enable
#define BSP_GPIO_TRX_LDO_EN_PORT            gpioPortA
#define BSP_GPIO_TRX_LDO_EN_PIN_NR          2
#define BSP_GPIO_TRX_LDO_EN_PIN_MASK        (1 << BSP_GPIO_TRX_LDO_EN_PIN_NR)

// RF Switch HF Tx
#define BSP_GPIO_TRX_TX_HF_PORT             gpioPortA
#define BSP_GPIO_TRX_TX_HF_PIN_NR           3
#define BSP_GPIO_TRX_TX_HF_PIN_MASK         (1 << BSP_GPIO_TRX_TX_HF_PIN_NR)

// RF Switch HF Rx
#define BSP_GPIO_TRX_RX_HF_PORT             gpioPortA
#define BSP_GPIO_TRX_RX_HF_PIN_NR           4
#define BSP_GPIO_TRX_RX_HF_PIN_MASK         (1 << BSP_GPIO_TRX_RX_HF_PIN_NR)

// RF DIO0
#define BSP_GPIO_TRX_DIO0_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO0_PIN_NR            5
#define BSP_GPIO_TRX_DIO0_PIN_MASK          (1 << BSP_GPIO_TRX_DIO0_PIN_NR)

// RF DIO1
#define BSP_GPIO_TRX_DIO1_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO1_PIN_NR            6
#define BSP_GPIO_TRX_DIO1_PIN_MASK          (1 << BSP_GPIO_TRX_DIO1_PIN_NR)

// RF DIO2
#define BSP_GPIO_TRX_DIO2_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO2_PIN_NR            8
#define BSP_GPIO_TRX_DIO2_PIN_MASK          (1 << BSP_GPIO_TRX_DIO2_PIN_NR)

// RF DIO3
#define BSP_GPIO_TRX_DIO3_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO3_PIN_NR            9
#define BSP_GPIO_TRX_DIO3_PIN_MASK          (1 << BSP_GPIO_TRX_DIO3_PIN_NR)

// RF DIO4
#define BSP_GPIO_TRX_DIO4_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO4_PIN_NR            10
#define BSP_GPIO_TRX_DIO4_PIN_MASK          (1 << BSP_GPIO_TRX_DIO4_PIN_NR)

// RF DIO5
#define BSP_GPIO_TRX_DIO5_PORT              gpioPortA
#define BSP_GPIO_TRX_DIO5_PIN_NR            15
#define BSP_GPIO_TRX_DIO5_PIN_MASK          (1 << BSP_GPIO_TRX_DIO5_PIN_NR)



// LoRA: UART0

#define BSP_LORA_USART_INTERFACE            USART0

#define BSP_LORA_USART_LOCATION             USART_ROUTE_LOCATION_LOC0

#define BSP_LORA_USART_CLOCK_MODULE         cmuClock_USART0

#define BSP_LORA_USART_GPIO_TX_PIN_PORT     gpioPortE
#define BSP_LORA_USART_GPIO_TX_PIN_NR       10

#define BSP_LORA_USART_GPIO_RX_PIN_PORT     gpioPortE
#define BSP_LORA_USART_GPIO_RX_PIN_NR       11

#define BSP_LORA_USART_RX_IRQ_VEC           USART0_RX_IRQn
#define BSP_LORA_USART_TX_IRQ_VEC           USART0_TX_IRQn

#define BSP_LORA_USART_IRQ_HANDLER_RX       USART0_RX_IRQHandler
#define BSP_LORA_USART_IRQ_HANDLER_TX       USART0_TX_IRQHandler



// BLE: UART1

#define BSP_BLE_USART_INTERFACE             USART1

#define BSP_BLE_USART_LOCATION              USART_ROUTE_LOCATION_LOC1

#define BSP_BLE_USART_CLOCK_MODULE          cmuClock_USART1

#define BSP_BLE_USART_GPIO_TX_PIN_PORT      gpioPortD
#define BSP_BLE_USART_GPIO_TX_PIN_NR        0

#define BSP_BLE_USART_GPIO_RX_PIN_PORT      gpioPortD
#define BSP_BLE_USART_GPIO_RX_PIN_NR        1

#define BSP_BLE_USART_RX_IRQ_VEC            USART1_RX_IRQn
#define BSP_BLE_USART_TX_IRQ_VEC            USART1_TX_IRQn

#define BSP_BLE_USART_IRQ_HANDLER_RX        USART1_RX_IRQHandler
#define BSP_BLE_USART_IRQ_HANDLER_TX        USART1_TX_IRQHandler

#define BSP_BLE_RESET_PORT                  gpioPortE
#define BSP_BLE_RESET_PIN_NR                8
#define BSP_BLE_RESET_PIN_MASK              (1 << BSP_BLE_RESET_PIN_NR)



// Common
#define BSP_USART_TX_IF_FLAG                USART_IF_TXBL
#define BSP_USART_TX_STATUS_FLAG            USART_STATUS_TXBL
#define BSP_USART_RX_DATA_FLAG              USART_STATUS_RXDATAV

#define BSP_USART_IF_CLEAR_MASK             _USART_IF_MASK
#define BSP_USART_IF_RXDATAV                USART_IF_RXDATAV

#define BSP_USART_RX_ROUTE_EN               USART_ROUTE_RXPEN
#define BSP_USART_TX_ROUTE_EN               USART_ROUTE_TXPEN


typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef unsigned char       BOOL;
//typedef unsigned char       bool;

typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

#define EOF                 -1
#define BV(x)               (1<<(x))
#define st(x)               do{x}while(0)

//------------------------------------------------------------------------------
// Boolean Constants
//------------------------------------------------------------------------------

#define false   0
#define true    1

#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

#ifndef NULL
   #define NULL 0
#endif

//------------------------------------------------------------------------------
// Integer Conversion Macros
//------------------------------------------------------------------------------

#define HINIBBLE(x)         ((uint8_t) (((uint8_t) (x)) >> 4))
#define LONIBBLE(x)         ((uint8_t) (((uint8_t) (x)) & 0xF))
#define HIBYTE(x)           ((uint8_t) (((uint16_t)(x)) >> 8))
#define LOBYTE(x)           ((uint8_t) (((uint16_t)(x)) & 0xFF))
#define HIWORD(x)           ((uint16_t)(((uint32_t)(x)) >> 16))
#define LOWORD(x)           ((uint16_t)(((uint32_t)(x)) & 0xFFFF))

#define MAKEBYTE(lo, hi)    ((uint8_t) (((uint8_t) (lo)) | (((uint8_t) ((uint8_t) (hi))) << 4)))
#define MAKEWORD(lo, hi)    ((uint16_t)(((uint8_t) (lo)) | (((uint16_t)((uint8_t) (hi))) << 8)))
#define MAKEDWORD(lo, hi)   ((uint32_t)(((uint16_t)(lo)) | (((uint32_t)((uint16_t)(hi))) << 16)))

#define SWAPBYTE(x)         MAKEWORD(HIBYTE(x), LOBYTE(x))

//------------------------------------------------------------------------------
// Byte-Order Conversion Macros
//------------------------------------------------------------------------------

#define NTOH16(srcPtr)  MAKEWORD((srcPtr)[0], (srcPtr)[1])

#define HTON16(dstPtr, value)           \
        (dstPtr)[0] = LOBYTE(value);    \
        (dstPtr)[1] = HIBYTE(value);

#define NTOH32(srcPtr)  MAKEDWORD(MAKEWORD((srcPtr)[0], (srcPtr)[1]),MAKEWORD((srcPtr)[2], (srcPtr)[3]))

#define HTON32(dstPtr, value)                   \
        (dstPtr)[0] = LOBYTE(LOWORD(value));    \
        (dstPtr)[1] = HIBYTE(LOWORD(value));    \
        (dstPtr)[2] = LOBYTE(HIWORD(value));    \
        (dstPtr)[3] = HIBYTE(HIWORD(value));


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

/*
 * TODO Stuff that needs to be cleaned up
 */
#define	CONFIG_BMP280_I2CBUS 0

// Include standard defines
#include "boards.h"
#include "conditionals.h"

#endif

#endif /* CONFIG_TRINKTRACKER_V2_H_ */
