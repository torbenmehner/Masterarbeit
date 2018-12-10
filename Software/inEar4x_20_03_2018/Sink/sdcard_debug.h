/**************************************************************************//**
 * @file sdcard_debug.h
 * @brief unisens SD Debug Library for Wearable Platform & TrinkTracker
 * @author czimmer@fzi.de
 * @version 0.7
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2015 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date     Version Author    Comment
 * 2014-08-27 0.1   czimmer   Initial Version, (Unisens) CSV working
 * 2014-10-29 0.2   czimmer   bin write for Unisens
 * 2015-05-01 0.3   czimmer   Added BMP280
 * 2015-08-11 0.4   czimmer   directorynumbers as argument, debug.txt improvments
 * 2015-09-17 0.5   czimmer   Switched between unisens and debug outputs, refactoring
 * 2015-09-20 0.6   czimmer   Documentation, Method for TrinkTracker Factory calibration
 *                            Example Sceleton for small Data Storage
 * 2015-09-20 0.7   czimmer   Better Data Representation for TrinkTracker Debug
 *
 * *****************************************************************************/
#ifndef SDCARD_DEBUG_H_
#define SDCARD_DEBUG_H_

#include <stdint.h>
#include "sdcard_common.h"

typedef struct {
  uint8_t savedSystemID;
  uint16_t calculatedMeasurementID;
  uint8_t calculatedMessageCounter;
  uint8_t calculatedMessageType;
  uint16_t calculatedBluetoothID;
  uint16_t calculatedWeightDifference;
  uint16_t calculatedWeightBeforeDrinking;
  uint16_t calculatedWeightAfterDrinking;
  uint16_t calculatedADCBeforeDrinking;
  uint16_t calculatedADCAfterDrinking;
  uint16_t savedDAC;
  uint16_t savedADCOffset;
  uint16_t savedADCScaling;
  uint8_t configTTScaleFix;
  uint16_t configTTScaleCupWeight;
  uint16_t configTTScaleFluidWeight;
  uint16_t configTTProcessingTreshholdTimerMax;
  uint16_t configTTProcessingTreshholdTimerMin;
  uint16_t configTTProcessingTreshholdACCMax;
  uint16_t configTTProcessingTreshholdACCMin;
  uint16_t configTTSleepingTreshholdTimer;
  uint16_t configTTSleepingTreshholdACC;
  uint16_t configVersion;
} SAVE_TRINKTRACKER_TypeDef;
typedef struct {
  uint32_t calculatedUniqueID0;
  uint32_t calculatedUniqueID1;
  uint8_t savedSystemID;
  uint16_t calculatedDAC;
  uint16_t configVersion;
  uint8_t scaleType;
} SAVE_TRINKTRACKER_FACTORY_TypeDef;

void createTrinkTrackerDebugTxt(SAVE_TRINKTRACKER_TypeDef *infoPtr);
void createTrinkTrackerFactoryTxt(SAVE_TRINKTRACKER_FACTORY_TypeDef *infoPtr);
void createTxtExample(uint16_t value1, uint8_t value2);

#endif /* SDCARD_DEBUG_H_ */
