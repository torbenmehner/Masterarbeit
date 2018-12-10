/**************************************************************************//**
 * @file sdcard_unisens.h
 * @brief unisens SD Library for Wearable Platform & TrinkTracker & inEar
 * @author czimmer@fzi.de
 * @version 0.6
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2016 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2014-08-27	0.1		czimmer 	Initial Version, (Unisens) CSV working
 * 2014-10-29	0.2		czimmer 	bin write for Unisens
 * 2015-05-01	0.3		czimmer		Added BMP280
 * 2015-08-11	0.4		czimmer		directorynumbers as argument, debug.txt improvments
 * 2015-09-17	0.5		czimmer		Switched between unisens and debug outputs, refactoring
 * 2016-01-20	0.6		czimmer		Added Triggers
 *
 * ******************************************************************************
 * @section Issues
 * - Mark foreign code
 * - Don't Overwrite
 * - Marked TODOs in Code
 * - Get dynamic Definitions for samplerate, resolution, ...
 *
 * *****************************************************************************/

#ifndef SDCARD_UNISENS_H_
#define SDCARD_UNISENS_H_

#include "../config.h"
#include "sdcard_common.h"
#include <stdint.h>

#define SAVEUNISENS                   CONFIG_SAVEUNISENS					        // Save any Data to Unisens File on SD-Card
#define SAVEUNISENS_MPU6050_ACC 		  2	  	// Save ACC of MPU6050 to Unisens File on SD-Card
#define SAVEUNISENS_MPU6050_GYRO 		  2	  	// Save GYRO of MPU6050 to Unisens File on SD-Card

// Save ANGLE of MPU6050 to Unisens File on SD-Card
#ifdef CONFIG_SAVEUNISENS_MPU6050_ANGLE
  #define SAVEUNISENS_MPU6050_ANGLE     CONFIG_SAVEUNISENS_MPU6050_ANGLE
#else
  #define SAVEUNISENS_MPU6050_ANGLE     0 // Save Trigger from Button
#endif

#define SAVEUNISENS_MPU6050_TEMP		  2		  // Save TEMP of MPU6050 to Unisens File on SD-Card
#define SAVEUNISENS_BMP180_PRESS		  CONFIG_SAVEUNISENS_BMP180_PRESS		  // Save PRESSURE of BMP180 to Unisens File on SD-Card
#define SAVEUNISENS_BMP180_TEMP			  CONFIG_SAVEUNISENS_BMP180_TEMP		  // Save TEMP of BMP180 to Unisens File on SD-Card
#define SAVEUNISENS_EFM32_ADC_TT 		  2		  // Save ADC of EFM32 Unisens File on SD-Card




// Save TEMP of BMP280 to Unisens File on SD-Card
#ifdef CONFIG_SAVEUNISENS_BMP280_TEMP
  #define SAVEUNISENS_BMP280_TEMP     CONFIG_SAVEUNISENS_BMP280_TEMP
#else
  #define SAVEUNISENS_BMP280_TEMP     0 // Save Trigger from Button
#endif

// Save TEMP of BMP280 to Unisens File on SD-Card
#ifdef CONFIG_SAVEUNISENS_BMP280_FFT
  #define SAVEUNISENS_BMP280_FFT     CONFIG_SAVEUNISENS_BMP280_FFT
#else
  #define SAVEUNISENS_BMP280_FFT     0 // Save Trigger from Button
#endif


// Save PRESSURE of BMP280 to Unisens File on SD-Card
#ifdef CONFIG_SAVEUNISENS_BMP280_PRESS
  #define SAVEUNISENS_BMP280_PRESS     CONFIG_SAVEUNISENS_BMP280_PRESS
#else
  #define SAVEUNISENS_BMP280_PRESS     0 // Save Trigger from Button
#endif


// Save DAC Value of Sensor FSR Unit
#ifdef CONFIG_SAVEUNISENS_EFM32_DAC_FORCE
  #define SAVEUNISENS_EFM32_DAC_FORCE     CONFIG_SAVEUNISENS_EFM32_DAC_FORCE
#else
  #define SAVEUNISENS_EFM32_DAC_FORCE     0 // Save Trigger from Button
#endif

#ifdef CONFIG_SAVEUNISENS_TRIGGER
	#define SAVEUNISENS_TRIGGER			CONFIG_SAVEUNISENS_TRIGGER
#else
	#define SAVEUNISENS_TRIGGER			0	// Save Trigger from Button
#endif

void createUnisensXml(void);
void writeUnisensFile(FIL * filPtr, uint8_t sdBinWriteBuffer[],
                      int16_t BufferLength, uint8_t UnisensFileFormat);
void writeUnisensBinInt16(FIL * filPtr, uint8_t bufWr[], int16_t counter);
void openUnisensFile(FIL * filPtr, const char filename[]);

#endif /* SDCARD_UNISENS_H_ */
