/**************************************************************************//**
 * @file
 * @brief This project demonstrates a using GPIOs to trigger external
 * interrupts. When PB0 or PB1 is pressed, LED0 or LED1 is toggled,
 * respectively. See readme.txt for details.
 * @version 0.0.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "bsp.h"

// GG11 STK currently does not have LEDs defined
#if defined BSP_STK_BRD2204A
#ifndef BSP_GPIO_LED0_PORT
#define BSP_GPIO_LED0_PORT      gpioPortH
#endif
#ifndef BSP_GPIO_LED0_PIN
#define BSP_GPIO_LED0_PIN       10
#endif
#ifndef BSP_GPIO_LED1_PORT
#define BSP_GPIO_LED1_PORT      gpioPortH
#endif
#ifndef BSP_GPIO_LED1_PIN
#define BSP_GPIO_LED1_PIN       13
#endif
#endif

/**************************************************************************//**
 * @brief GPIO Even IRQ for pushbuttons on even-numbered pins
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
  // Clear all even pin interrupt flags
  GPIO_IntClear(0x5555);

  // Toggle LED0
  GPIO_PinOutToggle(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN);
}

/**************************************************************************//**
 * @brief GPIO Odd IRQ for pushbuttons on odd-numbered pins
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
  // Clear all odd pin interrupt flags
  GPIO_IntClear(0xAAAA);

  // Toggle LED01
  GPIO_PinOutToggle(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN);
}

/**************************************************************************//**
 * @brief GPIO initialization
 *****************************************************************************/
void initGPIO(void)
{
  // Configure GPIO pins
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PB0 and PB1 as input with glitch filter enabled
  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInputPullFilter, 1);
  GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeInputPullFilter, 1);

  // Configure LED0 and LED1 as output
  GPIO_PinModeSet(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN, gpioModePushPull, 0);

  // Enable IRQ for even numbered GPIO pins
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  // Enable IRQ for odd numbered GPIO pins
  NVIC_EnableIRQ(GPIO_ODD_IRQn);

  // Enable falling-edge interrupts for PB pins
  GPIO_IntConfig(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, 0, 1, true);
  GPIO_IntConfig(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, 0, 1, true);
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  // Chip errata
  CHIP_Init();

  // Initializations
  initGPIO();

  while (1){
    // Enter Low Energy Mode until an interrupt occurs
    EMU_EnterEM3(false);
  }
}
