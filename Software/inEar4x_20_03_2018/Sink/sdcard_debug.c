/**************************************************************************//**
 * @file sdcard_debug.c
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
 * 2015-09-20 0.7   czimmer   Better Data Representation for TrinkTracker Debug, Clean Up
 *
 * *****************************************************************************/

#include "sdcard_debug.h"

/***************************************************************************
 * @brief
 *   Store TrinkTracker Debug Data on SD-Card
 *
 * @details
 *   Store Debug Information on SD-Card:
 *
 *   savedSystemID - System ID from Unique ID
 *   calculatedMeasurementID - Measurement / SD Card Directory ID
 *   calculatedMessageCounter - Counter for Transmitted Messages
 *   calculatedMessageType - Type of Message
 *   calculatedBluetoothID - Scaned Bluetooth ID while drinking
 *   calculatedWeightDifference - Calculated Difference in Weight
 *   calculatedWeightBeforeDrinking - Weight on Scale before current Measurement
 *   calculatedWeightAfterDrinking - Weight on Scale after current Measurement
 *   calculatedADCBeforeDrinking - Raw ADC Value before current Measurement
 *   calculatedADCAfterDrinking - Raw ADC Value after current Measurement
 *   savedDAC - Calibrated DAC Value
 *   savedADCOffset - Calibrated ADC Offset for Weight Calculation
 *   savedADCScaling - Calibrated Scaling for Weight Calculation
 *   configTTScaleFix - Bugfix (Cup Empty/Full) enabled?
 *   configTTScaleCupWeight - Bugfix Stored Cup Weight
 *   configTTScaleFluidWeight - Bugfix Stored Max Fluid Weight
 *   configTTProcessingTreshholdTimerMax - Stored Treshhold for Max Drinking Time
 *   configTTProcessingTreshholdTimerMin - Stored Treshhold for Min Drinking Time
 *   configTTProcessingTreshholdACCMax - Stored Treshhold for Max Drinking Acceleration
 *   configTTProcessingTreshholdACCMin - Stored Treshhold for Min Drinking Acceleration
 *   configTTSleepingTreshholdTimer - Stored Time Value (in Ticks) how long no movement must be present
 *   configTTSleepingTreshholdACC - Stored ACC Value, Value must be lower to go to sleep
 *   configVersion - Stored Config Flag (ymmdd)
 *
 * @param[in] infoPtr
 *   Pointer to TrinkTracker Typdef
 *
 ******************************************************************************/
void createTrinkTrackerDebugTxt(SAVE_TRINKTRACKER_TypeDef *infoPtr) {
  /* Open  the file for write */
  res = f_open(&fsrc, "debug.txt", FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, "debug.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
      /* Error. Cannot create the file */
      while (1)
        ;
    }
  }

  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, fsrc.fptr);
  if (res != FR_OK) {
    /* Error. Cannot set the file write pointer */
    while (1)
      ;
  }

  /*Write Textfile*/
  res = f_printf(&fsrc, "%s", "SystemID;");
  res = f_printf(&fsrc, "%d", infoPtr->savedSystemID);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "MeasurementID;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedMeasurementID);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "MessageCounter;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedMessageCounter);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "MessageType;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedMessageType);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "BluetoothID;");
  res = f_printf(&fsrc, "%04LX", infoPtr->calculatedBluetoothID);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "WeightDifference;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedWeightDifference);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "WeightBeforeDrinking;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedWeightBeforeDrinking);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "WeightAfterDrinking;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedWeightAfterDrinking);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ADCBeforeDrinking;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedADCBeforeDrinking);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ADCAfterDrinking;");
  res = f_printf(&fsrc, "%d", infoPtr->calculatedADCAfterDrinking);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "DACValue;0x");
  res = f_printf(&fsrc, "%04x", infoPtr->savedDAC);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ADCOffset;");
  res = f_printf(&fsrc, "%d", infoPtr->savedADCOffset);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ADCScaling;");
  res = f_printf(&fsrc, "%d", infoPtr->savedADCScaling);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ScaleFix;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTScaleFix);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "CupWeight;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTScaleCupWeight);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "FluidWeight;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTScaleFluidWeight);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "TTProcessTimerMax;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTProcessingTreshholdTimerMax);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "TTProcessTimerMin;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTProcessingTreshholdTimerMin);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "TTProcessACCMax;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTProcessingTreshholdACCMax);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "STUBTTProcessACCMin;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTProcessingTreshholdACCMin);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "SleepTreshholdTimer;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTSleepingTreshholdTimer);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "SleepTreshholdACC;");
  res = f_printf(&fsrc, "%d", infoPtr->configTTSleepingTreshholdACC);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "Version;");
  res = f_printf(&fsrc, "%d", infoPtr->configVersion);
  res = f_printf(&fsrc, "%c", '\n');
//  res = f_printf(&fsrc, "%s", "Version;");
//  res = f_printf(&fsrc, "%d", infoPtr->configHX711);
//  res = f_printf(&fsrc, "%c", '\n');

  /* Close the file */
  f_close(&fsrc);
}

/***************************************************************************
 * @brief
 *   Store TrinkTracker Factory Data
 *
 * @details
 *   Store Data for initial Factory Processing:
 *
 *   calculatedUniqueID - EFM32 Chip ID
 *   savedSystemID - Just make sure System ID is not set, should be 0
 *   calculatedDAC - Measured DAC Value
 *   configVersion - Stored Config Flag (ymmdd)
 *
 * @param[in] infoPtr
 *   Pointer to TrinkTracker Factory Typdef
 *
 ******************************************************************************/
void createTrinkTrackerFactoryTxt(SAVE_TRINKTRACKER_FACTORY_TypeDef *infoPtr) {
  /* Open  the file for write */
  res = f_open(&fsrc, "factory.txt", FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, "factory.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
      /* Error. Cannot create the file */
      while (1)
        ;
    }
  }

  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, fsrc.fptr);
  if (res != FR_OK) {
    /* Error. Cannot set the file write pointer */
    while (1)
      ;
  }

  /*Write Textfile*/
  res = f_printf(&fsrc, "%s", "UniqueID0;0x");
  res = f_printf(&fsrc, "%08x", infoPtr->calculatedUniqueID0);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "UniqueID1;0x");
  res = f_printf(&fsrc, "%08x", infoPtr->calculatedUniqueID1);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "SystemID;");
  res = f_printf(&fsrc, "%d", infoPtr->savedSystemID);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "DACValue;0x");
  res = f_printf(&fsrc, "%04x", infoPtr->calculatedDAC);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "Version;");
  res = f_printf(&fsrc, "%d", infoPtr->configVersion);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "ScaleHX711;");
  res = f_printf(&fsrc, "%d", infoPtr->scaleType);
  res = f_printf(&fsrc, "%c", '\n');

  /* Close the file */
  f_close(&fsrc);
}

/***************************************************************************
 * @brief
 *   Example Sceleton for Storing storing small data to a txt file
 *
 * @details
 *   Example for storing only less data as a txt file
 *   For larger Data typdef struct should be used
 *
 * @param[in] value1
 *    Value 1
 *
 * @param[in] value2
 *    Value 2
 *
 ******************************************************************************/
void createTxtExample(uint16_t value1, uint8_t value2) {
  /* Open  the file for write */
  res = f_open(&fsrc, "text.txt", FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, "text.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
      /* Error. Cannot create the file */
      while (1)
        ;
    }
  }

  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, fsrc.fptr);
  if (res != FR_OK) {
    /* Error. Cannot set the file write pointer */
    while (1)
      ;
  }

  /*Step6*/
  /*Write Textfile*/
  res = f_printf(&fsrc, "%s", "Text TXT");
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "Value 1 : ");
  res = f_printf(&fsrc, "%d", value1);
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "Value 2 : ");
  res = f_printf(&fsrc, "%d", value2);

  /*Step7*/
  /* Close the file */
  f_close(&fsrc);
}
