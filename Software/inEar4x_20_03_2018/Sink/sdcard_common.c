/**************************************************************************//**
 * @file sdcard_common.c
 * @brief common uSD-Interfacing Library for Wearable Platform & TrinkTracker
 * @author czimmer@fzi.de
 * @version 0.6
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
 * 2015-09-20 0.6   czimmer   Refactoring, Documentation
 *
 * ******************************************************************************
 * @section Issues
 * - Mark foreign code
 * - Use long Filenames
 * - Use Directorys
 * - Don't Overwrite
 * - Marked TODOs in Code
 *
 * *****************************************************************************/

#include "sdcard_common.h"

uint16_t directoryNumber = 0;  //Directory Number to start searching for non existing dir

/***************************************************************************
 * @brief
 *   Detects if SD-Card is present, initializes FAT File System and creates directory
 *
 * @details
 *   Initializes SD Card and creates new directory
 *
 * @return
 *   Returns created directory number, e.g. dir=data18 -> returns 18
 *
 ******************************************************************************/
uint16_t detectInitSdCardAndFat() {
  /*Detect micro-SD*/
  while (1) {
    MICROSD_Init(); /*Initialize MicroSD driver */

    resCard = disk_initialize(0); /*Check micro-SD card status */

    switch (resCard) {
      case STA_NOINIT: /* Drive not initialized */
        break;
      case STA_NODISK: /* No medium in the drive */
        break;
      case STA_PROTECT: /* Write protected */
        break;
      default:
        break;
    }

    if (!resCard)
      break; /* Drive initialized. */
    //TODO Handling when no SD-Card is present -> prevent infinite Loop
  }

  /* Initialize filesystem */
  if (f_mount(&Fatfs, 1, 1) != FR_OK) {
    /* Error.No micro-SD with FAT32 is present */
    while (1)
      ;
    //TODO Handling when no SD-Card is present -> prevent infinite Loop
  }

  /* Das DIR wird restartFATDir() erstellt */
}

/***************************************************************************
 * @brief
 *   Creates new Directory according to schema
 *
 * @details
 *   Creates new directory, increments dir number if needed
 *
 * @param[in] directoryNumberToStart
 *   Directory Number to start searching for non existing dir
 *
 * @return
 *   Returns created directory number, e.g. dir=data18 -> returns 18
 *
 ******************************************************************************/
uint16_t restartFATDir(uint16_t directoryNumberToStart) {

	/* Try to create base directory */
	char directory[10];
	sprintf(directory, DIRECTORYFORM, directoryNumberToStart);
	while (f_mkdir(directory) != FR_OK)
	{
		directoryNumber++;  // increment directory count
		sprintf(directory, DIRECTORYFORM, directoryNumber);  // form directory name
	}
	f_chdir(directory);         // change current directory

	return directoryNumber;

}

/***************************************************************************
 * @brief
 *   Open File and writes binary data
 *
 * @details
 *   Overwrites if data is already present
 *
 * @param[in] filename
 *   Used Filename for File to write
 *
 * @param[in] bufWr[]
 *   Values to write
 *
 * @param[in] counter
 *   Length of bufWr[]
 *
 ******************************************************************************/
void openFileAndWrite(int8_t filename[], uint8_t bufWr[], int8_t counter) {

  /* Open  the file for write */
  res = f_open(&fsrc, filename, FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
      /* Error. Cannot create the file */
      while (1)
        ;
    }
  }

  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK) {
    /* Error. Cannot set the file write pointer */
    while (1)
      ;
  }

  /*Write a buffer to file*/
  res = f_write(&fsrc, bufWr, counter, &bw);
  if ((res != FR_OK) || (counter != bw)) {
    /* Error. Cannot write the file */
    while (1)
      ;
  }

  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK) {
    /* Error. Cannot close the file */
    while (1)
      ;
  }
}

/***************************************************************************
 * @brief
 *   Opens File and appends binary data
 *
 * @details
 *   -
 *
 * @param[in] filename
 *   Used Filename for File to write
 *
 * @param[in] bufWr[]
 *   Values to write
 *
 * @param[in] counter
 *   Length of bufWr[]
 *
 ******************************************************************************/
void openFileAndWriteAddon(int8_t filename[], int8_t bufWr[], int8_t counter) {

  /* Open  the file for write */
  res = f_open(&fsrc, filename, FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
      /* Error. Cannot create the file */
      while (1)
        ;
    }
  }

  /*Set the file write pointer to end of file */
  res = f_lseek(&fsrc, f_size(&fsrc));
  if (res != FR_OK) {
    /* Error. Cannot set the file write pointer */
    while (1)
      ;
  }

  /*Write a buffer to file*/
  res = f_write(&fsrc, bufWr, counter, &bw);
  if ((res != FR_OK) || (counter != bw)) {
    /* Error. Cannot write the file */
    while (1)
      ;
  }

  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK) {
    /* Error. Cannot close the file */
    while (1)
      ;
  }
}

/***************************************************************************
 * @brief
 *   Open File and writes as CSV
 *
 * @details
 *   *
 *
 * @param[in] filename
 *   Used Filename for File to write
 *
 * @param[in]  data[]
 *   Values to write
 *
 * @param[in] datasize
 *   Length of data[]
 *
 ******************************************************************************/
void openFileAndWriteCSV(int8_t filename[], int16_t data[], uint8_t datasize) {
  /* Output Rate: CSV
   * (60 use signs) (60Byte) , 90 Signs (90Byte) -> ~ 66ms -> (900baud/s 7,2kbit/s) 1355 baud/s 10,9kbit/s
   * (80 use signs) (80Byte) , 110 Signs (110Byte) -> ~ 70ms -> (1137baud/s 9,1kbit/s) 1564 baud/s 12,5kbit/s
   *? (160 use signs) (160Byte) , 210 Signs (210Byte)  -> ~ 82ms -> (1317baud/s 10,5kbit/s) 2560 baud/s 20,1kbit/s
   */
  int i_datasize;
  int j;
  /* Open  the file for write */
  res = f_open(&fsrc, filename, FA_WRITE);
  if (res != FR_OK) {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, filename, FA_CREATE_ALWAYS | FA_WRITE);
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

  /*Write a buffer to file*/
  // Time
  for (j = 0; j < 10; j++) {
    // Channel 1
    res = f_printf(&fsrc, "%d", data[0]);

    // Channel i+1
    for (i_datasize = 1; i_datasize < datasize; i_datasize++) {
      // Semikolon
      res = f_printf(&fsrc, "%c", ';');
      // Data Value
      res = f_printf(&fsrc, "%d", data[i_datasize]);
    }

    // End of Line
    res = f_printf(&fsrc, "%c", '\n');
  }

  /* Close the file */
  f_close(&fsrc);
  //  if (res != FR_OK)
  //  {
  //  /* Error. Cannot close the file */
  //  while(1);
  //  }
}

/***************************************************************************
 * @brief
 *   Stub: Open File and writes binary code
 *
 * @details
 *   TODO Needs to be programmed
 *
 * @param[in] filename
 *   Used Filename for File to write
 *
 * @param[in] bufWr[]
 *   Values to write
 *
 * @param[in] counter
 *   Length of bufWr[]
 *
 ******************************************************************************/
void openFileAndWrite16(int8_t filename[], int16_t bufWr[][4], int8_t counter,
                        int8_t length) {
  int16_t test[1];
  int i;
  for (i= 0; i < length; i++) {
    test[0] = bufWr[i][4];
  }
//    /* Open  the file for write */
//  res = f_open(&fsrc, filename,  FA_WRITE);
//  if (res != FR_OK) {
//    /*  If file does not exist create it*/
//    res = f_open(&fsrc, filename, FA_CREATE_ALWAYS | FA_WRITE );
//    if (res != FR_OK) {
//          /* Error. Cannot create the file */
//          while(1);
//    }
//  }
//
//  /*Set the file write pointer to end of file */
//  res = f_lseek(&fsrc, f_size(&fsrc));
//  if (res != FR_OK)
//  {
//  /* Error. Cannot set the file write pointer */
//  while(1);
//  }
//
//  /*Write a buffer to file*/
//  uint8_t hibyte, lowbyte;
//          hibyte = bufWr[0]>>8;
//          lowbyte = bufWr[0];
//  res = f_write(&fsrc, bufWr, counter, &bw);
//  if ((res != FR_OK) || (counter != bw))
//  {
//  /* Error. Cannot write the file */
//  while(1);
//  }
//
//  /* Close the file */
//  f_close(&fsrc);
//  if (res != FR_OK)
//  {
//  /* Error. Cannot close the file */
//  while(1);
//  }
}
