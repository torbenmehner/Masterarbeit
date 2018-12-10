/***********************************************************************************************//**
 * \file   main.c
 * \brief  Silicon Labs Thermometer Example Application
 *
 * This Thermometer and OTA example allows the user to measure pressure
 * using the pressure sensor on the WSTK. The values can be read with the
 * Health Thermometer reader on the Blue Gecko smartphone app.
 ***************************************************************************************************
 * <b> (C) Copyright 2016 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#include "config.h"

#if CONFIGSYSTEM	== INEARV3_2
#include "CONFIG\config_inEar_v3_2.h"
#elif	CONFIGSYSTEM == INEARV4_0
#include "CONFIG\config_inEar_v4_0.h"
#endif

/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "ble-configuration.h"
#include "board_features.h"

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
//#include "aat.h"

// SYNC

#include "src/obssel.h"

//#include "aat.h"
#include "infrastructure.h"

/* GATT database */
#include "gatt_db.h"

/* EM library (EMlib) */
#include "em_system.h"

//SD Card
#include "Libs/FatFS/ff.h"
#include "Libs/FatFS/diskio.h"
#include "Libs/FreeRTOS_Stream_Buffer.h"

#include "Sink/sdcard_common.h"
#include "Sink/sdcard_unisens.h"
//#include "../Sink/hilfsFunktionen.h"
/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include "em_rtcc.h"
#include "gpiointerrupt.h"


#ifdef FEATURE_BOARD_DETECTED
//#include "bspconfig.h"
#include "pti.h"
#else
#error This sample app only works with a Silicon Labs Board
#endif

#ifdef FEATURE_IOEXPANDER
#include "ioexp.h"
#endif

// BMP280
#include "bmp280_Bosch/bmp280.h"
#include "bmp280_Bosch/bosch_support_FZI.h"
#include "em_usart.h"
#include "em_gpio.h"

// BMI160
#include "bmi160_Bosch/bmi160.h"
#include "bmi160_Bosch/bmi160_defs.h"

// BME680
#include "bme680_Bosch/bme680.h"
#include "bme680_Bosch/bme680_defs.h"
#include "bme680_Bosch/bme680_selftest.h"

// AFE44x0
#include "AFE44x0/AFE44x0.h"

// ADS129x
#include "ADS129x/ADS129x.h"

// ADS1292
#include "ADS1292/ADS1292.h"

// others
#include "rtcdriver.h"
#include "em_chip.h"
#include "platform/emlib/inc/em_letimer.h"
#include "platform/emlib/inc/em_timer.h"
#include "TIMER0.h"
#include "TIMER1.h"
#include <time.h>

//#ifdef FEATURE_SPI_FLASH
//#include "flashpwr.h"
//#endif

// Variablen
static struct bmp280_t bmp280[3];
static struct bmi160_dev bmi160;
static struct bme680_dev bme680;

static uint16_t sampleCounter = CONFIG_SAMPLE_TIMERCOUNT;

int8_t bme_rslt = BME680_OK;

/* The variable used to read sensor data*/
static s32 v_actual_temp_s32 = BMP280_INIT_VALUE;
static u32 v_actual_press_u32 = BMP280_INIT_VALUE;
static bool startup = true;
static bool syncTimeDone = false;


static struct bmi160_sensor_data accel;
static struct bmi160_sensor_data gyro;

struct bme680_field_data data;

static uint8_t htmPressBuffer[10]; /* Stores the pressure data in the Health Thermometer (HTM) format. */

static uint8_t msgcounter;

static uint8_t sendByteNumber=0;
const uint8_t DEVICE_NUM = CONF_DEVICE_NUM;

int state = 0;



//AFE44x0 variables
//int32_t valueRED_Diff;
//int32_t valueRED_A;
//int32_t valueRED;
//int32_t valueIR;
//int32_t valueIR_A;
//int32_t valueIR_Diff;


//sync

static uint8_t SyncCOUNT = 0;
uint8_t SyncCONN[2];
uint32_t SyncRTCC[3];
uint16_t SyncLETIME[3];
uint8_t  SyncREP[3];

//start
uint32_t startSampling;
uint8_t save_active = 1;

//live Stream
uint8_t live_stream_active = 1;

//Streambuffer
xStreamBuffer *accGyroStreamBuffer = NULL;
xStreamBuffer *sensStreamBuffer = NULL;
xStreamBuffer *bleStreamBuffer = NULL;

uint8_t sdBinWriteBuffer[SD_WRITE_VALUES];

/* Calendar struct for initial date setting */
struct tm initialCalendar;
time_t currentTime;
struct tm currentCalendar;
int16_t milliSeconds = 0;

/* File system */
FIL   fh;
//char path[100];

/* Command buffer and read data buffer */

static char buffer[CONFIG_HIL_BUFSIZE];
static UINT bufRead;


const uint8 CHAR_UUID_SYNC[16] = {0x01, 0x43, 0xC6, 0xB8, 0x39, 0x3A, 0x59, 0x8A, 0xAD, 0x42, 0x10, 0xD6, 0x95, 0x01, 0x46, 0xD9};

FIL fileAccGyro, fileSens;

/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

/* Gecko configuration parameters (see gecko_configuration.h) */
#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 3
#endif
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

static const gecko_configuration_t config = {
  .config_flags=0,
  .sleep.flags=SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections=MAX_CONNECTIONS,
  .bluetooth.heap=bluetooth_stack_heap,
  .bluetooth.heap_size=sizeof(bluetooth_stack_heap),
  .gattdb=&bg_gattdb_data,
  .ota.flags=0,
  .ota.device_name_len=3,
  .ota.device_name_ptr="OTA",
};



/**
 * @brief Function for taking a single pressure measurement with the WSTK Relative Humidity and pressure (RHT) sensor.
 */

DWORD get_fattime (void)
{
	DWORD tmr;

	currentTime = time( NULL );
	currentCalendar = *localtime( &currentTime );

	/* Pack date and time into a DWORD variable */
	tmr =     (((DWORD)currentCalendar.tm_year) << 25)			//year in calendar is represented in years since 1900, FATFS needs since 1980
																									  | ((DWORD)(currentCalendar.tm_mon) << 21)				//rtcMon
																									  | ((DWORD)currentCalendar.tm_mday << 16)				//rtcMday
																									  | (WORD)(currentCalendar.tm_hour << 11)				//rtcHour
																									  | (WORD)(currentCalendar.tm_min << 5)					//rtcMin
																									  | (WORD)(currentCalendar.tm_sec >> 1);				//rtcSec

	return (tmr);
}


void pressureMeasure()
{
	  uint16 result;
	  uint32_t bleBuffer[1];
	  uint32_t messurement;   /* Stores the pressure data read from the sensor in the correct format */

	  uint8_t *p = NULL;
	  if(sendByteNumber == 0){
		  sendByteNumber=1;
		  p = &htmPressBuffer[0]; /* Pointer to HTM pressure buffer needed for converting values to bitstream. */
	  }
	  else if(sendByteNumber == 1){
		  sendByteNumber=0;
		  p = &htmPressBuffer[4]; /* Pointer to HTM pressure buffer needed for converting values to bitstream. */
	  }
		int n = 0;
		uint8_t temp;
		//GPIO_PinOutToggle(gpioPortC, CONFIG_SYNC_RX_PIN);

	#if CONFIG_HIL_ENABLE == 1
		  if (res == FR_OK) {
				res = f_read(&fh, buffer, CONFIG_HIL_BUFSIZE , &bufRead);
				if (res == FR_OK) {
				while(n <= CONFIG_HIL_BUFSIZE){
					//temp= ((buffer[n] & 0xF) << 4)|((buffer[n] >> 4) & 0xF); Byteorder vertauschen
					htmPressBuffer[n]=buffer[n];
					n++;
					}
				htmPressBuffer[2]=0; //Demo workaround
				htmPressBuffer[3]=0;
			}


		  }
	#elif CONFIG_BMP280_ENABLE == 1
		  	uint32_t BMP280Buffer[3];
			/* Convert sensor data to correct pressure format */
			bmp280_read_pressure_temperature(&v_actual_press_u32, &v_actual_temp_s32);
			messurement = v_actual_press_u32;
			UINT32_TO_BITSTREAM(p, messurement);

			BMP280Buffer[0]=v_actual_press_u32;
			BMP280Buffer[1]=v_actual_temp_s32;
			BMP280Buffer[2]=RTCC_CounterGet();
			if(save_active){
			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) BMP280Buffer, 12 );
			}

	#elif CONFIG_AFE44x0_ENABLE == 1
			uint32_t plethBuffer[3];
			  while (GPIO_PinInGet(CONFIG_AFE44x0_RDY_PORT, CONFIG_AFE44x0_RDY_PIN) == 1){ //ToDo unschön, noch mit GPIO Interrupt machen
			  }
			messurement = AFE44x0_Read(LED2_ALED2VAL);
			plethBuffer[0]=messurement;
			plethBuffer[1]=0;
			plethBuffer[2]=RTCC_CounterGet();
			UINT32_TO_BITSTREAM(p, messurement);
			if(save_active){
			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) plethBuffer, 12 );
			}

	#elif CONFIG_ADS129x_ENABLE == 1
			uint32_t ADSBuffer[3];
			start_command();
			rdata_command(&v_actual_press_u32);
			//stop_command(); //bei single shot nicht nötig


			messurement = v_actual_press_u32;
			UINT32_TO_BITSTREAM(p, messurement);

			ADSBuffer[0]=v_actual_press_u32;
			ADSBuffer[1]=0;
			ADSBuffer[2]=RTCC_CounterGet();
			if(save_active){
			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) ADSBuffer, 12 );
			}

	#elif CONFIG_BME680_ENABLE == 1
		    bme680_get_sensor_data(&data, &bme680);
			messurement = data.gas_resistance;
		  	bme680_set_sensor_mode(&bme680);
		    UINT32_TO_BITSTREAM(p, messurement);
	#endif


	#if CONFIG_BMI160_ENABLE
	uint16_t AccGyroBuffer[6];
	bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel, &gyro, &bmi160);
	AccGyroBuffer[0]=accel.x;
	AccGyroBuffer[1]=accel.y;
	AccGyroBuffer[2]=accel.z;
	AccGyroBuffer[3]=gyro.x;
	AccGyroBuffer[4]=gyro.y;
	AccGyroBuffer[5]=gyro.z;
	if(save_active){
	lStreamBufferAdd( accGyroStreamBuffer, 0, (uint8_t *) AccGyroBuffer, 12);
	}

	#endif


	/* Send indication of the pressure in htmPressBuffer to all "listening" clients.

     *  0xFF as connection ID will send indications to all connections. */

		if(sendByteNumber == 0){ //if 2. pressure value was written
			  if (msgcounter < 255){
				  msgcounter++;
			  }else {
				  msgcounter=0;
			  }
			  // LED Flash
			  if(msgcounter % 128 == 0){
				  GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
			  }else if (msgcounter % 128 == 1){
		      GPIO_PinOutSet(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
			  }
			 htmPressBuffer[8]=msgcounter;
			 htmPressBuffer[9]=DEVICE_NUM;

			 gecko_cmd_gatt_server_send_characteristic_notification(

			 0xFF, gattdb_payload, 10, htmPressBuffer);
		}
		while(result == bg_err_out_of_memory);


	//}

}


//void pressureMeasure()
//{
//	  uint32_t messurement;   /* Stores the pressure data read from the sensor in the correct format */
//	  uint8_t *p = NULL;
//	  if(sendByteNumber == 0){
//		  sendByteNumber=1;
//		  p = &htmPressBuffer[0]; /* Pointer to HTM pressure buffer needed for converting values to bitstream. */
//	  }
//	  else if(sendByteNumber == 1){
//		  sendByteNumber=0;
//		  p = &htmPressBuffer[4]; /* Pointer to HTM pressure buffer needed for converting values to bitstream. */
//	  }
//
//		int n = 0;
//		uint8_t temp;
//
//
//	#if CONFIG_HIL_ENABLE == 1
//		  if (res == FR_OK) {
//				res = f_read(&fh, buffer, CONFIG_HIL_BUFSIZE , &bufRead);
//				if (res == FR_OK) {
//				while(n <= CONFIG_HIL_BUFSIZE){
//					//temp= ((buffer[n] & 0xF) << 4)|((buffer[n] >> 4) & 0xF); Byteorder vertauschen
//					htmPressBuffer[n]=buffer[n];
//					n++;
//					}
//				htmPressBuffer[2]=0; //Demo workaround
//				htmPressBuffer[3]=0;
//			}
//
//
//		  }
//	#else
//			/* Convert sensor data to correct pressure format */
//			bmp280_read_pressure_temperature(&v_actual_press_u32, &v_actual_temp_s32);
//			messurement = v_actual_press_u32;
//		    UINT32_TO_BITSTREAM(p, messurement);
//			/* Convert pressure to bitstream and place it in the HTM pressure data buffer (htmPressBuffer) */
//	#endif
//    /* Send indication of the pressure in htmPressBuffer to all "listening" clients.
//
//     *  0xFF as connection ID will send indications to all connections. */
//    //Bytes vertauschen, geht bestimmt auch schoener
//
////	    htmPressBuffer[4]=htmPressBuffer[0];
////	    htmPressBuffer[0]=htmPressBuffer[3];
////	    htmPressBuffer[3]=htmPressBuffer[1];
////	    htmPressBuffer[1]=htmPressBuffer[2];
////	    htmPressBuffer[2]=htmPressBuffer[3];
////	    htmPressBuffer[3]=htmPressBuffer[4];
//		    GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
//		if(sendByteNumber == 0){ //if 2. pressure value was written
//			  if (msgcounter < 255){
//			  	  msgcounter++;
//			  } else {
//				  msgcounter=0;
//			  }
//
//			 htmPressBuffer[8]=msgcounter;
//			 htmPressBuffer[9]=DEVICE_NUM;
//
//			 gecko_cmd_gatt_server_send_characteristic_notification(
//			 0xFF, gattdb_payload, 10, htmPressBuffer);
//		}
//
//
//}
//void pressureMeasure()
//{
//	  uint16 result;
//	  uint32_t bleBuffer[1];
//	  uint8_t htmPressBuffer[5]; /* Stores the pressure data in the Health Thermometer (HTM) format. */
//	  uint32_t messurement;   /* Stores the pressure data read from the sensor in the correct format */
//
//	  uint8_t *p = htmPressBuffer; /* Pointer to HTM pressure buffer needed for converting values to bitstream. */
//		int n = 0;
//		uint8_t temp;
//		//GPIO_PinOutToggle(gpioPortC, CONFIG_SYNC_RX_PIN);
//
//	#if CONFIG_HIL_ENABLE == 1
//		  if (res == FR_OK) {
//				res = f_read(&fh, buffer, CONFIG_HIL_BUFSIZE , &bufRead);
//				if (res == FR_OK) {
//				while(n <= CONFIG_HIL_BUFSIZE){
//					//temp= ((buffer[n] & 0xF) << 4)|((buffer[n] >> 4) & 0xF); Byteorder vertauschen
//					htmPressBuffer[n]=buffer[n];
//					n++;
//					}
//				htmPressBuffer[2]=0; //Demo workaround
//				htmPressBuffer[3]=0;
//			}
//
//
//		  }
//	#elif CONFIG_BMP280_ENABLE == 1
//		  	uint32_t BMP280Buffer[3];
//			/* Convert sensor data to correct pressure format */
//			bmp280_read_pressure_temperature(&v_actual_press_u32, &v_actual_temp_s32);
//			messurement = v_actual_press_u32;
//			UINT32_TO_BITSTREAM(p, messurement);
//
//			BMP280Buffer[0]=v_actual_press_u32;
//			BMP280Buffer[1]=v_actual_temp_s32;
//			BMP280Buffer[2]=RTCC_CounterGet();
//			if(save_active){
//			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) BMP280Buffer, 12 );
//			}
//
//	#elif CONFIG_AFE44x0_ENABLE == 1
//			uint32_t plethBuffer[3];
//			  while (GPIO_PinInGet(CONFIG_AFE44x0_RDY_PORT, CONFIG_AFE44x0_RDY_PIN) == 1){ //ToDo unschön, noch mit GPIO Interrupt machen
//			  }
//			messurement = AFE44x0_Read(LED2_ALED2VAL);
//			plethBuffer[0]=messurement;
//			plethBuffer[1]=0;
//			plethBuffer[2]=RTCC_CounterGet();
//			UINT32_TO_BITSTREAM(p, messurement);
//			if(save_active){
//			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) plethBuffer, 12 );
//			}
//
//	#elif CONFIG_ADS129x_ENABLE == 1
//			uint32_t ADSBuffer[3];
//			start_command();
//			rdata_command(&v_actual_press_u32);
//			//stop_command(); //bei single shot nicht nötig
//
//
//			messurement = v_actual_press_u32;
//			UINT32_TO_BITSTREAM(p, messurement);
//
//			ADSBuffer[0]=v_actual_press_u32;
//			ADSBuffer[1]=0;
//			ADSBuffer[2]=RTCC_CounterGet();
//			if(save_active){
//			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) ADSBuffer, 12 );
//			}
//
//	#elif CONFIG_ADS1292_ENABLE == 1
//			uint32_t ADSBuffer[3];
//			ads1292_Start_Data_Conv_Command();
//
////			ads1292_read_data(&v_actual_press_u32, uint8_t 4)
////			rdata_command(&v_actual_press_u32);
////
////
////			messurement = v_actual_press_u32;
////			UINT32_TO_BITSTREAM(p, messurement);
////
////			ADSBuffer[0]=v_actual_press_u32;
////			ADSBuffer[1]=0;
////			ADSBuffer[2]=RTCC_CounterGet();
////			if(save_active){
////			lStreamBufferAdd( sensStreamBuffer, 0, (uint8_t *) ADSBuffer, 12 );
////			}
//	#elif CONFIG_BME680_ENABLE == 1
//		    bme680_get_sensor_data(&data, &bme680);
//			messurement = data.gas_resistance;
//		  	bme680_set_sensor_mode(&bme680);
//		    UINT32_TO_BITSTREAM(p, messurement);
//	#endif
//
//
//	#if CONFIG_BMI160_ENABLE
//	uint16_t AccGyroBuffer[6];
//	bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel, &gyro, &bmi160);
//	AccGyroBuffer[0]=accel.x;
//	AccGyroBuffer[1]=accel.y;
//	AccGyroBuffer[2]=accel.z;
//	AccGyroBuffer[3]=gyro.x;
//	AccGyroBuffer[4]=gyro.y;
//	AccGyroBuffer[5]=gyro.z;
//	if(save_active){
//	lStreamBufferAdd( accGyroStreamBuffer, 0, (uint8_t *) AccGyroBuffer, 12);
//	}
//
//	#endif
//
//
//	/* Send indication of the pressure in htmPressBuffer to all "listening" clients.
//
//     *  0xFF as connection ID will send indications to all connections. */
//	    GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);  //keine ahnung warum der pin immer zurückgesetz wird
//		htmPressBuffer[4]=msgcounter;
//		htmPressBuffer[5]=DEVICE_NUM;
//
//		//lStreamBufferAdd( bleStreamBuffer, 0, p, 4 );
//		bleBuffer[0]=messurement;
//		lStreamBufferAdd( bleStreamBuffer, 0, (uint8_t *) bleBuffer, 4 );
//	//if (live_stream_active ==1){
//
//		//do
//		{
//			//result = gecko_cmd_gatt_server_send_characteristic_notification(0xFF, gattdb_payload, 6, htmPressBuffer)->result;
//			//gecko_peek_event();
//		}
//		while(result == bg_err_out_of_memory);
//
//
//	//}
//
//}

void sd_file_init()
{
#if  CONFIG_MICROSD_ENABLE == 1
	  //GPIO_PinModeSet(CONFIG_MICROSD_PORT_VCC,CONFIG_MICROSD_PIN_VCC,gpioModePushPull,0);
	  //GPIO_PinOutSet(CONFIG_MICROSD_PORT_VCC, CONFIG_MICROSD_PIN_VCC);
	  GPIO_PinOutClear(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
	  detectInitSdCardAndFat();
	  GPIO_PinOutSet(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);

		if (CONFIG_SAVEUNISENS)
		{
			restartFATDir(0);
			createUnisensXml();
			openUnisensFile( &fileAccGyro, BIN_FILENAME_ACCGYRO );
			openUnisensFile( &fileSens, BIN_FILENAME_SENS );

		}
		#if CONFIG_HIL_ENABLE == 1
		  char *fileName = CONFIG_HIL_FILE;

		  res = f_open(&fh, fileName, FA_READ);
		#endif
#endif
}


void handle_button_release(uint8_t pin)
{
	sd_file_init();
	GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
	GPIO_PinOutSet(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
	GPIO_PinOutSet(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);
	state = 1;
}

/* push button generates external signal event for the stacks */
void handle_button_change(uint8_t pin)
{
	GPIO_ExtIntConfig(CONFIG_BUTTON_PORT,CONFIG_BUTTON_PIN,CONFIG_BUTTON_PIN,true,true,false);
	if (GPIO_PinInGet(CONFIG_BUTTON_PORT,pin))
	{
		if (state==1){
			RTCDRV_Delay(200);
			NVIC_SystemReset();
		}
		else{
			RTCDRV_Delay(200);
			handle_button_release(pin);
		}
	}
	GPIO_ExtIntConfig(CONFIG_BUTTON_PORT,CONFIG_BUTTON_PIN,CONFIG_BUTTON_PIN,true,true,true);
}


///Sync

void handle_sync_change(uint8_t pin)
{
	SyncRTCC[0] = RTCC_CounterGet();
	SyncREP[0] = LETIMER_RepeatGet(LETIMER0, 0);
	SyncLETIME[0] = LETIMER_CounterGet(LETIMER0);
	GPIO_ExtIntConfig(gpioPortC,CONFIG_SYNC_TX_PIN,CONFIG_SYNC_TX_PIN,true,true,false);
	PRS->ROUTEPEN &= 0xFFFFF7FF; //disable RADIO TX pin
	syncTimeDone = true;
}

void TIMER1_IRQHandler(void) //SYNC
{
	startup=false;
	TIMER_IntClear(TIMER1, TIMER_IF_OF);
	stopTIMER1();
	gecko_cmd_system_halt(0);
}

void gpioSetup(void)
{
  /* Enable GPIO in CMU */
	CMU_ClockEnable(cmuClock_GPIO, true);
//normal
	GPIO_PinModeSet(CONFIG_LED_RED_PORT,CONFIG_LED_RED_PIN,gpioModePushPull,1); 	//LED1
	GPIO_PinModeSet(CONFIG_LED_GREEN_PORT,CONFIG_LED_GREEN_PIN,gpioModePushPull,1); //LED2
	GPIO_PinModeSet(CONFIG_LED_BLUE_PORT,CONFIG_LED_BLUE_PIN,gpioModePushPull,1); 	//LED3

	GPIO_PinModeSet(CONFIG_BUTTON_PORT,CONFIG_BUTTON_PIN,gpioModeInputPullFilter,1);
	GPIO_ExtIntConfig(CONFIG_BUTTON_PORT,CONFIG_BUTTON_PIN,CONFIG_BUTTON_PIN,true,true,true);
	GPIOINT_CallbackRegister(CONFIG_BUTTON_PIN,handle_button_change);

	GPIO_ExtIntConfig(gpioPortC,CONFIG_SYNC_TX_PIN,CONFIG_SYNC_TX_PIN,true,true,false);
	GPIOINT_CallbackRegister(CONFIG_SYNC_TX_PIN,handle_sync_change);
	GPIO_PinModeSet(gpioPortC,CONFIG_SYNC_TX_PIN,gpioModePushPull,1);
}

void syncTIMERS(void)
{
	if (syncTimeDone){
	SyncRTCC[2] = SyncRTCC[1] - SyncRTCC[0];
	//if((SyncRTCC[2] < 10 && SyncRTCC[2] > -10)||(SyncRTCC[2] > 300 && SyncRTCC[2] < -300)){
		SyncLETIME[0] = LETIMER_CounterGet(LETIMER0);
		RTCC->CNT = SyncRTCC[2]+RTCC->CNT;
		LETIMER_RepeatSet(LETIMER0, 0, SyncREP[1] + (LETIMER_RepeatGet(LETIMER0, 0)-SyncREP[0]));
		startup=false;
	//}
		GPIO_PinOutToggle(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);

		if (SyncCOUNT >= 5){
			SyncCOUNT=0;
		}
		else{
			SyncCOUNT++;
		}
	}
	else{
		//RTCDRV_Delay(1)
	}
}

void timerSetup(void)
{
	  CMU_ClockEnable(cmuClock_GPIO, true);
      /* Enable clock for TIMER0 module */
	  CMU_ClockEnable(cmuClock_TIMER0, true);
	  CMU_ClockEnable(cmuClock_TIMER1, true);
	  CMU_ClockEnable(cmuClock_LETIMER0, true);
	  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);

}

void spiSetup(void)
{
	#if CONFIG_SPI_SENSOR_ENABLE == 1
		CMU_ClockEnable(CONFIG_SENSOR_CMUCLOCK, true);

		USART_InitSync_TypeDef initsyncBMP280 = USART_INITSYNC_DEFAULT;

		initsyncBMP280.enable = usartEnable;
		initsyncBMP280.baudrate = CONFIG_SENSOR_BAUDRATE;  //115200 oder 57600;
		initsyncBMP280.databits = usartDatabits8;
		initsyncBMP280.master = 1;
		initsyncBMP280.msbf = 1;
		initsyncBMP280.clockMode = CONFIG_SENSOR_CLOCKMODE; //usartClockMode0;
	//	initsyncBMP280.autoCsEnable = 1;

		USART_InitSync(CONFIG_SENSOR_USART, &initsyncBMP280);
		/* Set up CLK pin */
		CONFIG_SENSOR_USART->ROUTELOC0 = (CONFIG_SENSOR_USART->ROUTELOC0 & (~_USART_ROUTELOC0_CLKLOC_MASK))
					| CONFIG_SENSOR_LOC_CLK;
		/* Set up CS pin */
		CONFIG_SENSOR_USART->ROUTELOC0 = (CONFIG_SENSOR_USART->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
						| CONFIG_SENSOR_LOC_CS;
		/* Set up RX pin */
		CONFIG_SENSOR_USART->ROUTELOC0 = (CONFIG_SENSOR_USART->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
					| CONFIG_SENSOR_LOC_RX;
		/* Set up TX pin */
		CONFIG_SENSOR_USART->ROUTELOC0 = (CONFIG_SENSOR_USART->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
				| CONFIG_SENSOR_LOC_TX;
		//route all
		CONFIG_SENSOR_USART->ROUTEPEN |= USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;

		GPIO_PinModeSet(CONFIG_SENSOR_PORT_CLK,CONFIG_SENSOR_PIN_CLK,gpioModePushPull,0); //CLK
		GPIO_PinModeSet(CONFIG_SENSOR_PORT_CS,CONFIG_SENSOR_PIN_CS,gpioModePushPull,1); //CS
		GPIO_PinModeSet(CONFIG_SENSOR_PORT_RX,CONFIG_SENSOR_PIN_RX,gpioModeInput,0); 	//RX
		GPIO_PinModeSet(CONFIG_SENSOR_PORT_TX,CONFIG_SENSOR_PIN_TX,gpioModePushPull,0); //TX
	#endif

	#if CONFIG_BMI160_ENABLE == 1 &&  CONFIG_BMI160_I2C == 0
		CMU_ClockEnable(CONFIG_BMI_CMUCLOCK, true);

		USART_InitSync_TypeDef initsyncBMI160 = USART_INITSYNC_DEFAULT;

		initsyncBMI160.enable = usartEnable;
		initsyncBMI160.baudrate = CONFIG_BMI_BAUDRATE;  //115200 oder 57600;
		initsyncBMI160.databits = usartDatabits8;
		initsyncBMI160.master = 1;
		initsyncBMI160.msbf = 1;
		initsyncBMI160.clockMode = usartClockMode0;
	//	initsync.autoCsEnable = 1;

		USART_InitSync(CONFIG_BMI_USART, &initsyncBMI160);
		/* Set up CLK pin */
		CONFIG_BMI_USART->ROUTELOC0 = (CONFIG_BMI_USART->ROUTELOC0 & (~_USART_ROUTELOC0_CLKLOC_MASK))
					| CONFIG_BMI_LOC_CLK;
		/* Set up CS pin */
		CONFIG_BMI_USART->ROUTELOC0 = (CONFIG_BMI_USART->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
						| CONFIG_BMI_LOC_CS;
		/* Set up RX pin */
		CONFIG_BMI_USART->ROUTELOC0 = (CONFIG_BMI_USART->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
					| CONFIG_BMI_LOC_RX;
		/* Set up TX pin */
		CONFIG_BMI_USART->ROUTELOC0 = (CONFIG_BMI_USART->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
				| CONFIG_BMI_LOC_TX;
		//route all
		CONFIG_BMI_USART->ROUTEPEN |= USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;

		GPIO_PinModeSet(CONFIG_BMI_PORT_CLK,CONFIG_BMI_PIN_CLK,gpioModePushPull,0); //CLK
		GPIO_PinModeSet(CONFIG_BMI_PORT_CS,CONFIG_BMI_PIN_CS,gpioModePushPull,1); //CS
		GPIO_PinModeSet(CONFIG_BMI_PORT_RX,CONFIG_BMI_PIN_RX,gpioModeInput,0); 	//RX
		GPIO_PinModeSet(CONFIG_BMI_PORT_TX,CONFIG_BMI_PIN_TX,gpioModePushPull,0); //TX

		#ifdef CONFIG_BMI160_VCC_ENABLE == 1;
		GPIO_PinModeSet(CONFIG_BMI_PORT_VCC,CONFIG_BMI_PIN_VCC,gpioModePushPull,0); //VCC
		#endif
		#endif
	}

void init_inEar_BMP280(void)
{
	//sensor 0
	bmp280[0].bus_write = BMP280_SPI_bus_write;
	bmp280[0].bus_read = BMP280_SPI_bus_read;
	bmp280[0].dev_addr = 0;
	bmp280[0].delay_msec = SENSOR_delay_msek;
	bmp280[0].oversamp_pressure	 = 1;
	bmp280[0].oversamp_pressure	 = 1;

	bmp280_init(&bmp280[0]);
	bmp280_set_power_mode(BMP280_SLEEP_MODE); 
	bmp280_set_standby_durn(BMP280_STANDBY_TIME_1_MS);
	bmp280_set_work_mode(BMP280_ULTRA_LOW_POWER_MODE);
	bmp280[1]=bmp280[0];
}

void init_BME680(void)
{
	/* You may assign a chip select identifier to be handled later */
	bme680.dev_id = 0;
	bme680.intf = BME680_SPI_INTF;
	bme680.read = BME680_SPI_bus_read;
	bme680.write = BME680_SPI_bus_write;
	bme680.delay_ms = SENSOR_delay_msek;

	int8_t rslt = BME680_OK;
	rslt = bme680_init(&bme680);

	uint8_t set_required_settings;

	/* Set the temperature, pressure and humidity settings */
	bme680.tph_sett.os_hum = BME680_OS_1X;
	bme680.tph_sett.os_pres = BME680_OS_1X;
	bme680.tph_sett.os_temp = BME680_OS_1X;
	bme680.tph_sett.filter = BME680_FILTER_SIZE_0;

	/* Set the remaining gas sensor settings and link the heating profile */
	bme680.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
	/* Create a ramp heat waveform in 3 steps */
	bme680.gas_sett.heatr_temp = 320; /* degree Celsius */
	bme680.gas_sett.heatr_dur = 150; /* milliseconds */

	/* Select the power mode */
	/* Must be set before writing the sensor configuration */
	bme680.power_mode = BME680_FORCED_MODE;

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL
		| BME680_GAS_SENSOR_SEL;
	/* Set the desired sensor configuration */
	rslt = bme680_set_sensor_settings(set_required_settings,&bme680);
	rslt = bme680_get_sensor_settings(set_required_settings,&bme680);

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(&bme680);
	//rslt = bme680_get_sensor_mode(&bme680);

	/* Get the total measurement duration so as to sleep or wait till the
	 * measurement is complete */
	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, &bme680);
	SENSOR_delay_msek(meas_period); /* Delay till the measurement is ready */


}

void init_BMI160(void)
{
	#if CONFIG_BMI160_VCC_ENABLE == 1
		GPIO_PinOutSet(CONFIG_BMI_PORT_VCC, CONFIG_BMI_PIN_VCC);
	#endif

	#if CONFIG_BMI160_I2C ==0
	bmi160.id = 0;
	bmi160.interface = BMI160_SPI_INTF;
	bmi160.read = BMI160_SPI_bus_read;
	bmi160.write = BMI160_SPI_bus_write;
	bmi160.delay_ms = SENSOR_delay_msek;
	#endif

	#if CONFIG_BMI160_I2C ==1
	bmi160.id = BMI160_I2C_ADDR;
	bmi160.interface = BMI160_I2C_INTF;
	bmi160.read = BMI160_I2C_bus_read;
	bmi160.write = BMI160_I2C_bus_write;
	bmi160.delay_ms = SENSOR_delay_msek;
	#endif


	int8_t rslt = BMI160_OK;
	rslt = bmi160_init(&bmi160);
	/* Select the Output data rate, range of accelerometer sensor */
	bmi160.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
	bmi160.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
	bmi160.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;

	/* Select the power mode of accelerometer sensor */
	bmi160.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;

	/* Select the Output data rate, range of Gyroscope sensor */
	bmi160.gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
	bmi160.gyro_cfg.range = BMI160_GYRO_RANGE_2000_DPS;
	bmi160.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;

	/* Select the power mode of Gyroscope sensor */
	bmi160.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

	/* Set the sensor configuration */
	rslt = bmi160_set_sens_conf(&bmi160);

//	#ifdef CONFIG_BMI160_VCC_ENABLE == 1;
//		GPIO_PinOutClear(CONFIG_BMI_PORT_VCC, CONFIG_BMI_PIN_VCC);
//	#endif
}


void TIMER0_FHandler(void)
{
	TIMER_IntClear(TIMER0, TIMER_IF_OF);
	pressureMeasure();
}

void LETIMER0_IRQHandler(void)
{
	//gecko_external_signal(31);
	LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
	//GPIO_PinOutToggle(CONFIG_SENSOR_PORT_CS, CONFIG_SENSOR_PIN_CS);
	//GPIO_PinOutToggle(gpioPortC, CONFIG_SYNC_TX_PIN);
	if (LETIMER_RepeatGet(LETIMER0, 0)<8){
		LETIMER_RepeatSet(LETIMER0, 1,  LETIMER0_REP1);
	}

	if (sampleCounter == CONFIG_SAMPLE_TIMERCOUNT){
		sampleCounter = 0;
		pressureMeasure();
	}
	sampleCounter++;
}

/**
 * @brief  Main function
 */

void main(void)
{
	  // Initialize device
	  initMcu();
	  // Initialize board
	  initBoard();
	  // Initialize application
	  //initApp();
  /* Initialize stack */
  gecko_init(&config);
  //obssel_rx_setup(CONFIG_SYNC_RX_PIN);  // map RX activity
  obssel_tx_setup(CONFIG_SYNC_TX_PIN);  // map TX activity
  timerSetup();
  RTCDRV_Init();
	/* Configure Backup Domain */
	//budSetup();
	/* Setting up a structure to initialize the calendar
	 for January 1 2012 12:00:00
	 The struct tm is declared in time.h
	 More information for time.h library in http://en.wikipedia.org/wiki/Time.h */
	initialCalendar.tm_sec    = 0;   /* 0 seconds (0-60, 60 = leap second)*/
	initialCalendar.tm_min    = 0;   /* 0 minutes (0-59) */
	initialCalendar.tm_hour   = 12;  /* 6 hours (0-23) */
	initialCalendar.tm_mday   = 1;   /* 1st day of the month (1 - 31) */
	initialCalendar.tm_mon    = 1;   /* January (1 - 12, 1 = January) */
	initialCalendar.tm_year   = 112 - 80; /* Year 2012 (year since 1900), FATFS needs since 1980 */
	initialCalendar.tm_wday   = 0;   /* Sunday (0 - 6, 0 = Sunday) */
	initialCalendar.tm_yday   = 0;   /* 1st day of the year (0-365) */
	initialCalendar.tm_isdst  = -1;  /* Daylight saving time; enabled (>0), disabled (=0) or unknown (<0) */

	/* Set the calendar */
	//clockInit(&initialCalendar);

  gpioSetup();
  spiSetup();
	#if CONFIG_BMI160_I2C
	  setupI2C();
	#endif

	/* Init Circular Buffers */
	accGyroStreamBuffer = vCreateBuffer( accGyroStreamBuffer, CONFIG_BUFFERSIZE_ACC);
	sensStreamBuffer = vCreateBuffer( sensStreamBuffer, CONFIG_BUFFERSIZE_SENS);
	bleStreamBuffer = vCreateBuffer( bleStreamBuffer, CONFIG_BUFFERSIZE_BLE);

	#if CONFIG_BMI160_ENABLE
	  init_BMI160();
	  //while(1)
		{
			bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel, &gyro, &bmi160);
		}
	#endif

	#if CONFIG_BMP280_ENABLE
	  init_inEar_BMP280();
	  bmp280[0]=bmp280[1]; //Singel Sensor 0
	  //while(1) // BMP testen
//		{
			bmp280_read_pressure_temperature(&v_actual_press_u32, &v_actual_temp_s32);
//		}
	#endif

	#if CONFIG_ADS129x_ENABLE
	  	ADS129x_Init();
	//  while(1) // testen
	//	{
	//	  uint8_t testbuff[4];
	//	  sendSamples(testbuff);
	//	}
	#endif

	#if CONFIG_ADS1292_ENABLE
		GPIO_PinModeSet(CONFIG_ADS1292_RDY_PORT,CONFIG_ADS1292_RDY_PIN,gpioModePushPull,0); //ADReady
		GPIO_PinModeSet(CONFIG_ADS1292_CLK_SEL_PORT,CONFIG_ADS1292_CLK_SEL_PIN,gpioModePushPull,0); //Clock Select

		ads1292_Init();
	//  while(1) // testen
	//	{
	//	  uint8_t testbuff[4];
	//	  sendSamples(testbuff);
	//	}
	#endif

	#if CONFIG_AFE44x0_ENABLE
		AFE44x0_Init();
//		while(1) // AFE testen
//		{
//			  while (GPIO_PinInGet(CONFIG_AFE44x0_RDY_PORT, CONFIG_AFE44x0_RDY_PIN) == 1){ //ToDo unschön, noch mit GPIO Interrupt machen
//			  }
//			valueIR_A = AFE44x0_Read(ALED1VAL);
//			valueIR = AFE44x0_Read(LED1VAL);
//			valueIR_Diff = AFE44x0_Read(LED1_ALED1VAL);
//
//			valueRED_A = AFE44x0_Read(ALED2VAL);
//			valueRED = AFE44x0_Read(LED2VAL);
//			valueRED_Diff = AFE44x0_Read(LED2_ALED2VAL);
//
//		}
	#endif


	#if CONFIG_BME680_ENABLE
	  init_BME680();
	  //while(1)
		{

		 // bme680_self_test(&bme680);

		  	bme_rslt = bme680_get_sensor_data(&data, &bme680);
		  	bme680_set_sensor_mode(&bme680);
//			bme680_set_sensor_settings(BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL
//					| BME680_GAS_SENSOR_SEL,&bme680);
//			bme680.power_mode = BME680_FORCED_MODE;
//			bme680_set_sensor_mode(&bme680);
//			uint16_t meas_period;
//			bme680_get_profile_dur(&meas_period, &bme680);
//			SENSOR_delay_msek(meas_period); /* Delay till the measurement is ready */
		  //bme680_soft_reset(&bme680);
		}
	#endif
// while(1){
//	 SyncRTCC[0]=RTCC_CounterGet();
//	 RTCDRV_Delay(10);
//	    SyncRTCC[1]=RTCC->CNT;
//	 RTCDRV_Delay(1);
//	    RTCC->CNT =0;
//	    SyncRTCC[2]=RTCC->CNT;
//	    ;
//	    ;
//	    RTCDRV_Delay(1);
//		RTCDRV_Delay(1);
// }
	GPIOINT_Init();
	EMU_EnterEM2(true);

	while (1) {

//	  if (state == 1){
				/* Event pointer for handling events */
			  if (1){

				struct gecko_cmd_packet* evt;
				//gecko_cmd_hardware_set_soft_timer(209,0,0);

				/* Check for stack event. */
				evt = gecko_peek_event();
				/* Handle events */
				switch (BGLIB_MSG_ID(evt->header)) {

				  /* This boot event is generated when the system boots up after reset.
				   * Here the system is set to start advertising immediately after boot procedure. */
				  case gecko_evt_system_boot_id:
					/* Set advertising parameters. 100ms advertisement interval. All channels used.
					 * The first two parameters are minimum and maximum advertising interval, both in
					 * units of (milliseconds * 1.6). The third parameter '7' sets advertising on all channels. */
					gecko_cmd_le_gap_set_adv_parameters(160,160,7);

					/* Start general advertising and enable connections. */
					gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
					break;
				 //test sync

				  case gecko_evt_le_connection_parameters_id:
					  if ((evt->data.evt_le_connection_parameters.timeout) == 301){
						  	syncTimeDone = false;
							PRS->ROUTEPEN |= PRS_ROUTEPEN_CH11PEN; //enable RADIO TX pinRoute
						  	GPIO_ExtIntConfig(gpioPortC,CONFIG_SYNC_TX_PIN,CONFIG_SYNC_TX_PIN,true,true,true);
							//}
						}
					  break;


				  /* This event is generated when a connected client has either
				   * 1) changed a Characteristic Client Configuration, meaning that they have enabled
				   * or disabled Notifications or Indications, or
				   * 2) sent a confirmation upon a successful reception of the indication. */
				  case gecko_evt_gatt_server_characteristic_status_id:
					/* Check that the characteristic in question is pressure - its ID is defined
					 * in gatt.xml as "temp_measurement". Also check that status_flags = 1, meaning that
					 * the characteristic client configuration was changed (notifications or indications
					 * enabled or disabled). */
					if ((((evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_payload)))
					  && (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)) {
					  if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == 0x01) {
						/* Indications have been turned ON - start the repeating timer. .*/
							#if CONFIG_AFE44x0_ENABLE
							AFE44x0_Write(CONTROL2, 0x0);
							#endif
							#if CONFIG_BMP280_ENABLE
								bmp280_set_power_mode(BMP280_NORMAL_MODE);
							#endif
						  startLETIMER0();
					    	GPIO_PinOutSet(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
					    	GPIO_PinOutSet(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);
					    	GPIO_PinOutSet(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
					  } else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == 0x00) {
						/* Indications have been turned OFF - stop the timer. */
						  //stopTIMER0();
						  //stopLETIMER0();
					  }
					}
					break;

				  /* This event is generated when the software timer has ticked. In this example the pressure
				   * is read after every 1 second and then the indication of that is sent to the listening client. */

			      case gecko_evt_le_connection_closed_id:


			        break;

					/* This event is generated when GPIO Interrupt trigger
					 *
					 */
			      case gecko_evt_system_external_signal_id:


			    	  switch (evt->data.evt_system_external_signal.extsignals)
			    	  {

			    	  	  case CLICK_BUTTON:
			    	  		NVIC_SystemReset();
   		    	  		    break;
			    	  	  case LONG_PRESS_BUTTON:
//				    	  		GPIO_PinOutClear(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);
//				    	  		GPIO_PinOutSet(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
//				    	  		GPIO_PinOutSet(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
//				    	  		EMU_EnterEM2(true);
//				    			CMU_OscillatorEnable(cmuOsc_HFXO, false, false);
//				    	  		state=0;
//			    	  		}

//			    	  		NVIC_SystemReset();
			    	  		  break;
			    	  	  case DBL_CLICK_BUTTON:
			    	  		GPIO_PinOutClear(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);
			    	  		GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
			    	  		GPIO_PinOutSet(CONFIG_LED_BLUE_PORT, CONFIG_LED_BLUE_PIN);
			    	  		  break;
			    	  }
			    	  break;

			          case gecko_evt_hardware_soft_timer_id:
						  GPIO_PinOutClear(CONFIG_LED_GREEN_PORT, CONFIG_LED_GREEN_PIN);
						  GPIO_PinOutSet(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
//							#if CONFIG_AFE44x0_ENABLE
//							AFE44x0_Write(CONTROL2, 0x0);
//							#endif
//							#if CONFIG_BMP280_ENABLE
//								bmp280_set_power_mode(BMP280_NORMAL_MODE);
//							#endif
							//startLETIMER0();
							save_active = 1;
			            break;

				  /* Events related to OTA upgrading
				  ----------------------------------------------------------------------------- */

				  /* Checks if the user-type OTA Control Characteristic was written.
				   * If written, boots the device into Device Firmware Upgrade (DFU) mode. */
				  case gecko_evt_gatt_server_user_write_request_id:
					empty: ;
					  uint8_t SyncBuffer[8];
					if(evt->data.evt_gatt_server_user_write_request.characteristic==gattdb_ota_control) {
					  gecko_cmd_system_reset(1);
						//GPIO_PinOutClear(CONFIG_LED_RED_PORT, CONFIG_LED_RED_PIN);
					}
					break;

				  default:
				  break;
				}

				if (lStreamBufferGetSize(bleStreamBuffer)> BLE_WRITE_VALUES && live_stream_active == 1)
				{
				  if (msgcounter < 255){
					  msgcounter++;
				  } else {
					  msgcounter=0;
				  }
  	  	  		  sdBinWriteBuffer[0]=msgcounter;
  	  	  		  sdBinWriteBuffer[1]=DEVICE_NUM;
  	  	  		  lStreamBufferGet( bleStreamBuffer, 0, (uint8_t *)&sdBinWriteBuffer[2], BLE_WRITE_VALUES, pdFALSE );
  	  	  		  //if (live_stream_active ==1){
  	  			  gecko_cmd_gatt_server_send_characteristic_notification(0xFF, gattdb_payload, 82, sdBinWriteBuffer);

  	  			  //}
				}
				/* Save Data, if Save to Unisens is activated */
				if (SAVEUNISENS == 1 && CONFIG_MICROSD_ENABLE == 1)
				{
					/* Handling for SENS */
					if (lStreamBufferGetSize(sensStreamBuffer)> SD_WRITE_VALUES)
					{
						lStreamBufferGet( sensStreamBuffer, 0, (uint8_t *)sdBinWriteBuffer, SD_WRITE_VALUES, pdFALSE );
						writeUnisensFile(&fileSens, sdBinWriteBuffer, SD_WRITE_VALUES, 2);
					}
					/* Handling for ACC/GYRO*/
					if (lStreamBufferGetSize(accGyroStreamBuffer)> SD_WRITE_VALUES)
					{
						lStreamBufferGet( accGyroStreamBuffer, 0, (uint8_t *)sdBinWriteBuffer, SD_WRITE_VALUES, pdFALSE );
						writeUnisensFile(&fileAccGyro, sdBinWriteBuffer, SD_WRITE_VALUES, SAVEUNISENS_MPU6050_ACC);
					}
				}


			  }
  }
}



/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
