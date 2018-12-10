/***************************************************************************//**
 * @file
 * @brief Provide MicroSD SPI configuration parameters.
 * @version 4.1.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __MICROSDCONFIG_H
#define __MICROSDCONFIG_H

#include "../../config.h"

/* Don't increase MICROSD_HI_SPI_FREQ beyond 12MHz. Next step will be 24MHz */
/* which is out of spec.                                                    */

#define MICROSD_HI_SPI_FREQ     CONFIG_MICROSD_HI_SPI_FREQ
#define MICROSD_LO_SPI_FREQ		CONFIG_MICROSD_LO_SPI_FREQ
#define MICROSD_USART			CONFIG_MICROSD_USART

#define MICROSD_LOC_CLK			CONFIG_MICROSD_LOC_CLK
#define MICROSD_LOC_CS			CONFIG_MICROSD_LOC_CS
#define MICROSD_LOC_RX			CONFIG_MICROSD_LOC_RX
#define MICROSD_LOC_TX			CONFIG_MICROSD_LOC_TX
#define MICROSD_CMUCLOCK		CONFIG_MICROSD_CMUCLOCK

#define MICROSD_MOSIPIN			CONFIG_MICROSD_PIN_TX
#define MICROSD_MISOPIN			CONFIG_MICROSD_PIN_RX
#define MICROSD_CSPIN			CONFIG_MICROSD_PIN_CS
#define MICROSD_CLKPIN			CONFIG_MICROSD_PIN_CLK
#define MICROSD_VCCPIN			CONFIG_MICROSD_PIN_VCC

#define MICROSD_MOSIPORT		CONFIG_MICROSD_PORT_TX
#define MICROSD_MISOPORT		CONFIG_MICROSD_PORT_RX
#define MICROSD_CSPORT			CONFIG_MICROSD_PORT_CS
#define MICROSD_CLKPORT			CONFIG_MICROSD_PORT_CLK
#define MICROSD_VCCPORT			CONFIG_MICROSD_PORT_VCC


#endif /* __MICROSDCONFIG_H */
