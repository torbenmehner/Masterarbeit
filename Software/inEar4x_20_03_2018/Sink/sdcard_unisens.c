/**************************************************************************//**
 * @file sdcard_unisens.c
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

#include "sdcard_unisens.h"

/***************************************************************************
 * @brief
 *   Creates Unisens.xml
 *
 ******************************************************************************/
void createUnisensXml() {

  /* Open  the file for write */
  res = f_open(&fsrc, "unisens.xml", FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, "unisens.xml", FA_CREATE_ALWAYS | FA_WRITE);
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

  /*Write Unisens XML*/
  res = f_printf(
      &fsrc, "%s",
      "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
  res = f_printf(&fsrc, "%c", '\n');
  //TODO: add data: Timestamp
  res =
      f_printf(
          &fsrc,
          "%s",
          "<unisens comment=\"\" duration=\"17694.0\" measurementId=\"2012-09-05 Langzeitmessung\" timestampStart=\"2012-09-05T18:32:52.024\" version=\"2.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.unisens.org/unisens2.0 http://www.unisens.org/unisens2.0/unisens.xsd\" xmlns=\"http://www.unisens.org/unisens2.0\">");
  res = f_printf(&fsrc, "%c", '\n');

  /* MPU650 ACC Saving */
  if (SAVEUNISENS_MPU6050_ACC == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"acc.csv\" lsbValue=\"0.00006103515625\" sampleRate=\"10\" unit=\"g\" contentClass=\"ACC\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accX\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accY\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accZ\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_MPU6050_ACC == 2) {
    res =
        f_printf(
            &fsrc,
            "%s%s%s",
			"  <signalEntry id=\"", BIN_FILENAME_ACCGYRO,"\" dataType=\"int16\" lsbValue=\"0.00006103515625\" sampleRate=\"170.66666\" unit=\"g\" contentClass=\"ACC\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accX\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accY\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"accZ\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroX\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroY\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroZ\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');

    /* MPU650 Gyro Saving */
  }
  if (SAVEUNISENS_MPU6050_GYRO == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"gyro.csv\" lsbValue=\"0.00763358778625954198473282442748\" sampleRate=\"10\" unit=\"grad/s\" contentClass=\"GYRO\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroX\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroY\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroZ\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_MPU6050_GYRO == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
			 "  <signalEntry id=\"gyro.bin\" dataType=\"int16\" lsbValue=\"0.00763358778625954198473282442748\" sampleRate=\"157\" unit=\"grad/s\" contentClass=\"GYRO\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroX\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroY\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"gyroZ\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* MPU650 Temp Saving */
  if (SAVEUNISENS_MPU6050_TEMP == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"temp.csv\" sampleRate=\"10\" lsbValue=\"0.0029411764705882\" baseline=\"-12420\" contentClass=\"TEMP\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"temp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_MPU6050_TEMP == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
			 "  <signalEntry id=\"temp.bin\" dataType=\"int16\" sampleRate=\"157\" lsbValue=\"0.0029411764705882\" baseline=\"-12420\" contentClass=\"TEMP\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"temp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }


  /* BMP280 Pressure Saving */
  if (SAVEUNISENS_BMP280_PRESS == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"press.csv\" sampleRate=\"170.66666\" lsbValue=\"1\" baseline=\"0\" unit=\"Pa\" contentClass=\"PRESS\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"press\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_BMP280_PRESS == 2) {
    res =
        f_printf(
            &fsrc,
            "%s%s%s",
            "  <signalEntry id=\"", BIN_FILENAME_SENS,"\" dataType=\"int32\" sampleRate=\"170.66666\" lsbValue=\"1\" baseline=\"0\" unit=\"\" contentClass=\"SENSOR\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"pressure\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"temperature\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"RTCC\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* BMP280 Temp Saving */
  if (SAVEUNISENS_BMP280_TEMP == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"temp2.csv\" sampleRate=\"170.66666\" lsbValue=\"0.01\" baseline=\"0\" contentClass=\"TEMP\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"tempbmp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_BMP280_TEMP == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <signalEntry id=\"temp2.bin\" dataType=\"int16\" sampleRate=\"170.66666\" lsbValue=\"0.01\" baseline=\"0\" contentClass=\"TEMP\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"tempbmp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* BMP280 FFT Saving */
  if (SAVEUNISENS_BMP280_FFT == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <signalEntry id=\"FFT.bin\" dataType=\"int32\" sampleRate=\"64\" lsbValue=\"0.01\" baseline=\"0\" contentClass=\"FFT\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"fftbmp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');

    //---gefiltert
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <signalEntry id=\"FFT_FIR.bin\" dataType=\"float\" sampleRate=\"78.5\" lsbValue=\"0.01\" baseline=\"0\" contentClass=\"Filter\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"fft_fir_bmp\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  // RTCC saving
  res =
      f_printf(
          &fsrc,
          "%s",
          "  <signalEntry id=\"rtcc.bin\" dataType=\"int32\" sampleRate=\"170.66666\" lsbValue=\"1\" baseline=\"0\" contentClass=\"FFT\">");
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "    <channel name=\"RTCC\" />");
  res = f_printf(&fsrc, "%c", '\n');
  res = f_printf(&fsrc, "%s", "  </signalEntry>");
  res = f_printf(&fsrc, "%c", '\n');


  /* EFM32 ADC Saving */
  if (SAVEUNISENS_EFM32_ADC_TT == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"adc.csv\" sampleRate=\"256\" lsbValue=\"1\" baseline=\"0\" contentClass=\"ECG\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"adc\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_EFM32_ADC_TT == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <signalEntry id=\"adc.bin\" dataType=\"int16\" sampleRate=\"157\" lsbValue=\"1\" baseline=\"0\" contentClass=\"ECG\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"adc\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* EFM32 ADC Saving */
  if (SAVEUNISENS_EFM32_DAC_FORCE == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <valuesEntry id=\"dac.csv\" sampleRate=\"256\" lsbValue=\"1\" baseline=\"0\" contentClass=\"ECG\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat decimalSeparator=\".\" separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"dac\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </valuesEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  } else if (SAVEUNISENS_EFM32_DAC_FORCE == 2) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <signalEntry id=\"dac.bin\" dataType=\"int16\" sampleRate=\"256\" lsbValue=\"1\" baseline=\"0\" contentClass=\"ECG\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <binFileFormat endianess=\"LITTLE\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "    <channel name=\"dac\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </signalEntry>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* Trigger Saving */
  if (SAVEUNISENS_TRIGGER == 1) {
    res =
        f_printf(
            &fsrc,
            "%s",
            "  <eventEntry id=\"trigger.csv\" sampleRate=\"128\" contentClass=\"TRIGGER\">");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(
        &fsrc, "%s",
        "    <csvFileFormat separator=\";\" />");
    res = f_printf(&fsrc, "%c", '\n');
    res = f_printf(&fsrc, "%s", "  </eventEntry>>");
    res = f_printf(&fsrc, "%c", '\n');
  }

  res = f_printf(&fsrc, "%s", "</unisens>");
  res = f_printf(&fsrc, "%c", '\n');

  /*Step7*/
  /* Close the file */
  f_close(&fsrc);
  //	if (res != FR_OK)
  //	{
  //	/* Error. Cannot close the file */
  //	while(1);
  //	}
}

/***************************************************************************
 * @brief
 *   Writes Unisens File
 *
 * @details
 *   writes either binary or csv file
 *   TODO: currently CSV not working
 *
 * @param[in] *filPtr
 *   Pointer to File
 *
 * @param[in] sdBinWriteBuffer[]
 *   Values to write
 *
 * @param[in] BufferLength
 *   Length of sdBinWriteBuffer[]
 *
 * @param[in] UnisensFileFormat
 *   1 for CSV / 2 for Binary
 *
 ******************************************************************************/
void writeUnisensFile(FIL * filPtr, uint8_t sdBinWriteBuffer[],
                      int16_t BufferLength, uint8_t UnisensFileFormat) {
  /* Handling for Temp of MPU6050 */
  //	if (cbDataInBuffer(&tempRingBuffer)>BufferLength)
  //	{
  if (UnisensFileFormat == 1) {
    /* write CSV File */
    //TODO Timestamp at [0], bsp timerruncounter
    //openFileAndWriteCSV(filPtr, sdBinWriteBuffer , 4);
  } else if (UnisensFileFormat == 2) {
    /* write Bin File */
    writeUnisensBinInt16(filPtr, sdBinWriteBuffer, BufferLength);
  }
  //	}
}

/***************************************************************************
 * @brief
 *   Writes Unisens Binary
 *
 * @details
 *   Writes singned Integer into a Binary File
 *
 * @param[in] *filPtr
 *   Pointer to File
 *
 * @param[in] bufWr[]
 *   Values to write
 *
 * @param[in] counter
 *   Length of bufWr[]
 *
 ******************************************************************************/
void writeUnisensBinInt16(FIL * filPtr, uint8_t bufWr[], int16_t counter) {
  /*Step6*/
  /*Write a buffer to file*/
  res = f_write(filPtr, bufWr, counter, &bw);
  if ((res != FR_OK) || (counter != bw)) {
    /* Error. Cannot write the file */
    while (1)
      ;
  }

  /*Step7*/
  /* Flush data to the file */
  f_sync(filPtr);
  if (res != FR_OK) {
    /* Error. Cannot close the file */
    while (1)
      ;
  }
}

/***************************************************************************
 * @brief
 *   Open Unisens File for Writing
 *
 * @details
 *   -
 *
 * @param[in] *filPtr
 *   Pointer to File
 *
 * @param[in] filename[]
 *   Filename
 *
 ******************************************************************************/
void openUnisensFile(FIL * filPtr, const char filename[]) {
  /*Step4*/
  /* Open  the file for write and if file does not exist create it */
  res = f_open(filPtr, filename, FA_CREATE_ALWAYS | FA_WRITE);
  if (res != FR_OK) {
    /* Error. Cannot create the file */
    while (1)
      ;
  }
}
