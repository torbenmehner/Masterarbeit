/**************************************************************************//**
 * @file sdcard_common.h
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
 * *****************************************************************************/

#ifndef SDCARD_COMMON_H_
#define SDCARD_COMMON_H_

#include "../config.h"
#include "../Libs/FatFS/ff.h"
#include "../Libs/FatFS/diskio.h"
#include "../Libs/FatFS/microsd.h"
#include <stdint.h>

#define BUFFERSIZE_SD      512
#define DIRECTORYNAME "/data" /* Diretory Name for saving data */
#define DIRECTORYFORM   "/data%d" /* Schema to create new directorys */

FIL fsrc; /* File objects */
FATFS Fatfs; /* File system specific */
FRESULT res; /* FatFs function common result code */
UINT br, bw; /* File read/write count */
DSTATUS resCard; /* SDcard status */
int8_t ramBufferWrite[BUFFERSIZE_SD]; /* Temporary buffer for write file */
int8_t ramBufferRead[BUFFERSIZE_SD]; /* Temporary buffer for read file */

uint16_t detectInitSdCardAndFat();
uint16_t restartFATDir(uint16_t directoryNumberToStart);

void openFileAndWrite(int8_t filename[], uint8_t bufWr[], int8_t counter);
void openFileAndWriteAddon(int8_t filename[], int8_t bufWr[], int8_t counter);
void openFileAndWriteCSV(int8_t filename[], int16_t data[], uint8_t datasize);
void openFileAndWrite16(int8_t filename[], int16_t bufWr[][4], int8_t counter,
                        int8_t length);  //currently stub

#endif /* SDCARD_COMMON_H_ */
