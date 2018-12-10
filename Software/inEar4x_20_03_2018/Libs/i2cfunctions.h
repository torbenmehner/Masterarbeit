/**************************************************************************//**
 * @file i2functions.h
 * @brief I2C Library for Wearable Plattform v1
 * @author czimmer@fzi.de
 * @version 0.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2014-08-27	0.1		czimmer 	Initial Version, Write 1, Read 1-2 Register
 * 2014-10-17	0.11	czimmer 	Added GPIO Clock Init in setupI2C
 * 2014-10-18	0.2		czimmer 	External Config, Fast-Mode Support, Refactoring
 *
 * *****************************************************************************/

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

#include <stdint.h>
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "../config.h"

#define I2C0_ENABLE					CONFIG_I2C0_ENABLE
#define I2C0_LOCATION				CONFIG_I2C0_LOCATION
#define I2C0_PORT					CONFIG_I2C0_PORT
#define I2C0_PIN_SDA				CONFIG_I2C0_PIN_SDA
#define I2C0_PIN_SCL				CONFIG_I2C0_PIN_SCL
#define I2C0_FAST_MODE				CONFIG_I2C0_FAST_MODE

#define I2C1_ENABLE					CONFIG_I2C1_ENABLE
#define I2C1_LOCATION				CONFIG_I2C1_LOCATION
#define I2C1_PORT					CONFIG_I2C1_PORT
#define I2C1_PIN_SDA				CONFIG_I2C1_PIN_SDA
#define I2C1_PIN_SCL				CONFIG_I2C1_PIN_SCL
#define I2C1_FAST_MODE				CONFIG_I2C1_FAST_MODE

void setupI2C(void);

uint8_t readI2cRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr);
uint16_t readI2c2Register(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr);
uint16_t readI2cMultipleRegisters(uint8_t *data, uint8_t size, uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr);

int writeI2cRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr, uint8_t regValue);
int writeI2cMultipleRegister(uint8_t i2cBus, uint8_t deviceAddr, uint8_t regAddr, uint8_t *data, uint8_t size);

#endif /* I2CFUNCTIONS_H_ */
