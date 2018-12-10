/******************************************************************************
 * @file conditionals.h
 * @brief Default Defines for all Projects
 * @author czimmer@fzi.de
 * @version 0.1
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2016 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2016-05-10	0.1		czimmer 	Initial Version
 *
 * *****************************************************************************/
#ifndef CONDITIONALS_H_
#define CONDITIONALS_H_

//Version Nr. - Last digit of year, Month, Day
//#ifndef CONFIG_VERSION
//	#error	Bitte  CONFIG_VERSION im Format YMMDD angeben zb 60131 für 31.01.2016
//#endif

// 1 -  Enables Print Out on SWO for Debugging
#ifndef CONFIG_DEBUG_PRINTOUT_ENABLE
	#define CONFIG_DEBUG_PRINTOUT_ENABLE 0
#endif




// 1 -  Enables Unisens Saving
#ifndef CONFIG_SAVEUNISENS
	#define CONFIG_SAVEUNISENS 						0							// Save any Data to Unisens File on SD-Card
#endif

/*
 * Saving to Unisens
 * 0 - No Saving
 * 1 - Save as CSV // Currently not working for all data
 * 2 - Save as BIN
 */
#ifndef CONFIG_SAVEUNISENS_MPU6050_ACC
	#define CONFIG_SAVEUNISENS_MPU6050_ACC 			0							// Save ACC of MPU6050 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_MPU6050_GYRO
	#define CONFIG_SAVEUNISENS_MPU6050_GYRO 		0							// Save GYRO of MPU6050 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_MPU6050_ANGLE
	#define CONFIG_SAVEUNISENS_MPU6050_ANGLE 		0							// Computed Angle from ACC & GYRO of MPU6050
#endif
#ifndef CONFIG_SAVEUNISENS_MPU6050_TEMP
#define CONFIG_SAVEUNISENS_MPU6050_TEMP				0							// Save TEMP of MPU6050 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_EFM32_ADC_MYO
	#define CONFIG_SAVEUNISENS_EFM32_ADC_MYO		0							//TODO not used yet
#endif
#ifndef CONFIG_SAVEUNISENS_EFM32_ADC_TT
	#define CONFIG_SAVEUNISENS_EFM32_ADC_TT			0							// Save ADC of EMF32 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_EFM32_ADC_BATT
	#define CONFIG_SAVEUNISENS_EFM32_ADC_BATT		0							//TODO not used yet
#endif
#ifndef CONFIG_SAVEUNISENS_EFM32_DAC_FORCE
	#define CONFIG_SAVEUNISENS_EFM32_DAC_FORCE		0							// Save DAC Value of Sensor FSR Unit
#endif
#ifndef CONFIG_SAVEUNISENS_BMP180_PRESS
	#define CONFIG_SAVEUNISENS_BMP180_PRESS			0							// Save PRESSURE of BMP180 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_BMP180_TEMP
	#define CONFIG_SAVEUNISENS_BMP180_TEMP			0							// Save TEMP of BMP180 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_BMP280_PRESS
	#define CONFIG_SAVEUNISENS_BMP280_PRESS			2							// Save PRESSURE of BMP280 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_BMP280_TEMP
	#define CONFIG_SAVEUNISENS_BMP280_TEMP			2							// Save TEMP of BMP280 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_BMP280_FFT
	#define CONFIG_SAVEUNISENS_BMP280_FFT			2							// Save TEMP of BMP280 to Unisens File on SD-Card
#endif
#ifndef CONFIG_SAVEUNISENS_TRIGGER
	#define CONFIG_SAVEUNISENS_TRIGGER				1							// Save Trigger from Button
#endif

/* Default File Names */
#ifndef BIN_FILENAME_ACC
	#define BIN_FILENAME_ACC					"acc.bin"
#endif
#ifndef CSV_FILENAME_ACC
	#define CSV_FILENAME_ACC					"acc.csv"
#endif
#ifndef BIN_FILENAME_GYRO
	#define BIN_FILENAME_GYRO					"gyro.bin"
#endif
#ifndef CSV_FILENAME_GYRO
	#define CSV_FILENAME_GYRO 					"gyro.csv"
#endif
#ifndef BIN_FILENAME_TEMP
	#define BIN_FILENAME_TEMP					"temp.bin"
#endif
#ifndef CSV_FILENAME_TEMP
	#define CSV_FILENAME_TEMP					"temp.csv"
#endif
#ifndef BIN_FILENAME_FFT
	#define BIN_FILENAME_FFT					"fft.bin"
#endif
#ifndef BIN_FILENAME_PRESS
	#define BIN_FILENAME_PRESS					"press.bin"
#endif
#ifndef CSV_FILENAME_PRESS
	#define CSV_FILENAME_PRESS					"press.csv"
#endif
#ifndef BIN_FILENAME_PRESS_TEMP
	#define BIN_FILENAME_PRESS_TEMP				"temp2.bin"
#endif
#ifndef CSV_FILENAME_PRESS_TEMP
	#define CSV_FILENAME_PRESS_TEMP				"temp2.csv"
#endif
#ifndef BIN_FILENAME_ADC
	#define BIN_FILENAME_ADC					"adc.bin"
#endif
#ifndef CSV_FILENAME_ADC
	#define CSV_FILENAME_ADC 					"adc.csv"
#endif
#ifndef BIN_FILENAME_DAC
	#define BIN_FILENAME_DAC					"dac.bin"
#endif
#ifndef CSV_FILENAME_DAC
	#define CSV_FILENAME_DAC 					"dac.csv"
#endif
#ifndef CSV_FILENAME_TRIGGER
	#define CSV_FILENAME_TRIGGER				"trigger.csv"
#endif
#ifndef BIN_FILENAME_ANGLE
	#define BIN_FILENAME_ANGLE					"angle.bin"
#endif


/****************************************************************************
 * Hardware Configuration Section
 *
 * Note: Do not change anything unless you know what to change!
 * **************************************************************************/

#ifndef CONFIG_HAS_IMST_RF
  #define CONFIG_HAS_IMST_RF 0
#endif

#ifndef CONFIG_HAS_QI_BQ51013B
  #define CONFIG_HAS_QI_BQ51013B 0
#endif

#ifndef CONFIG_HAS_BMP280
  #define CONFIG_HAS_BMP280 0
#endif

#endif /* CONDITIONALS_H_ */
