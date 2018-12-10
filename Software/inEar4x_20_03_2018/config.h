/******************************************************************************
 * @file config.h
 * @brief Configuration File for Project
 * @author czimmer@fzi.de
 * @version 1.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2016 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2014-09-25	0.1		czimmer 	Initial Version
 * 2014-10-18	0.2		czimmer 	More Parameters to config, cleanup
 * 2015-02-15	1.0		czimmer 	Stub for individual Config Files
 * 2015-05-03	1.1		czimmer 	Docu & inEarv1, Cleared unused stuff
 * 2016-01-08	1.2		czimmer 	inEar v2
 *
 * *****************************************************************************/

/****************************************************************************
 * Systems Configuration
 *
 * 000 - Default: Wearable Platform v1			(HW: Wearable Platform v1)
 * 100 - TrinkTracker_v1						(HW: Trinktracker v1)
 * 101 - TrinkTracker_v2						(HW: Trinktracker v2)
 * 200 - Myo_v1									(HW: Wearable Platform v1)
 * 201 - Myo_v2									(HW: Myo Board v2)
 * 300 - inEar_v1								(HW: Wearable Platform v1)
 * 301 - inEar_v2								(HW: inEar v2)
 *
 * **************************************************************************/
#define DEFAULT 		000
#define TRINKTRACKERV1	100 //Legacy
#define TRINKTRACKERV2 	101
#define MYOV1			200
#define MYOV2			201 //Not working
#define INEARV1			300
#define INEARV2			301
#define INEARV2_1		302
#define INEARV3_2		402
#define INEARV4_0		500

// Select System here
#define CONFIGSYSTEM	INEARV4_0

// Load individual config file
#if		CONFIGSYSTEM == TRINKTRACKERV1
	#include "CONFIG\config_TrinkTracker_v1.h"
#elif	CONFIGSYSTEM == TRINKTRACKERV2
	#include "CONFIG\config_TrinkTracker_v2.h"
#elif	CONFIGSYSTEM == MYOV1
	#include "CONFIG\config_Myo_v1.h"
#elif	CONFIGSYSTEM == MYOV2
	#include "CONFIG\config_Myo_v2.h"
#elif	CONFIGSYSTEM == INEARV1
	#include "CONFIG\config_inEar_v1.h"
#elif	CONFIGSYSTEM == INEARV2
	#include "CONFIG\config_inEar_v2.h"
#elif	CONFIGSYSTEM == INEARV2_1
	#include "CONFIG\config_inEar_v2_1.h"
#elif	CONFIGSYSTEM == INEARV3_2
	#include "CONFIG\config_inEar_v3_2.h"
#elif	CONFIGSYSTEM == INEARV4_0
	#include "CONFIG\config_inEar_v4_0.h"
#else
	#include "CONFIG\config_Default.h"
#endif
