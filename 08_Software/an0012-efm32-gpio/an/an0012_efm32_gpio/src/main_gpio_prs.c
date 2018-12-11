/*****************************************************************************
 * @file
 * @brief GPIO Demo Application
 * @version 2.01
*******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_adc.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "em_chip.h"
#include "bsp.h"


volatile uint32_t adcResult;

/**************************************************************************//**
 * @brief  Delay function
 * causes a delay equal to miliseconds input parameter
 *****************************************************************************/
void Delay(uint16_t milliseconds)
{
  uint16_t countMs=0;
  /* Initialize clock for TIMER0*/
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0; 
  
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_CLKSEL_MASK) | TIMER_CTRL_CLKSEL_PRESCHFPERCLK; 
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) | TIMER_CTRL_PRESC_DIV1; //no prescaling
  TIMER0->IEN = (TIMER0->IEN & ~_TIMER_IEN_RESETVALUE) | TIMER_IEN_OF; //overflow interrupt enable 
  TIMER0->IFC = (TIMER0->IFC & ~_TIMER_IFC_MASK) | TIMER_IFC_OF; //clear interrupt flag
  TIMER0->TOP = 14285; //counts up to this value and goes back to 0 -> 1ms
  TIMER0->CMD = TIMER_CMD_START; 
  
  while(countMs < milliseconds)
  {
    if(TIMER0->IF & _TIMER_IF_OF_MASK) //overflow interrupt occured
    {
      countMs++; //1ms has passed, so increase counter
      TIMER0->IFC = (TIMER0->IFC & ~_TIMER_IFC_MASK) | TIMER_IFC_OF; //clear interrupt flag
    }  
  }
  
  TIMER0->CMD = TIMER_CMD_STOP;//stop timer
}

/**************************************************************************//**
 * @brief ADC0_IRQHandler
 * Interrupt Service Routine for ADC
 *****************************************************************************/
void ADC0_IRQHandler(void)
{ 
  /* Clear ADC0 interrupt flag */
  ADC0->IFC = 1;
  
  /* Read conversion result to clear Single Data Valid flag */
  adcResult = ADC0->SINGLEDATA;
}
/**************************************************************************//**
 * @brief  Main function
 * Main is called from __iar_program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{  
  /* Initialize chip */
  CHIP_Init();
  
  /* Enable clock for GPIO module */
  CMU_ClockEnable(cmuClock_GPIO, true);
  
  /* Enable clock for ADC0 module */
  CMU_ClockEnable(cmuClock_ADC0, true);
  
  /* Enable clock for PRS module */
  CMU_ClockEnable(cmuClock_PRS, true);
  
  /* Configure PD8 as an input for PB0 button with filter enable (out = 1)*/
  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInput, 1);
  
  /* Select PD8 as PRS output */
  GPIO_IntConfig(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, 0, 1, true);
  
  /* Select the correct PRS Source and Signal depending on the PB button port and pin */
  uint32_t source;
  uint32_t signal;
  if (BSP_GPIO_PB0_PIN >= 8)
  {
    source = PRS_CH_CTRL_SOURCESEL_GPIOH;
    signal = BSP_GPIO_PB0_PIN - 8;
  }
  else
  {
    source = PRS_CH_CTRL_SOURCESEL_GPIOL;
    signal = BSP_GPIO_PB0_PIN;
  }

  /* Select GPIO as source and GPIOPIN8 as signal (falling edge) */
  PRS_SourceSignalSet(0, source, signal, prsEdgeNeg);

  /* Initialize ADC common parts for both single conversion and scan sequence */
  ADC_Init_TypeDef ADCInit = ADC_INIT_DEFAULT;
  ADC_Init(ADC0, &ADCInit);
  
  /* Initialize ADC single sample conversion */
  ADC_InitSingle_TypeDef ADCInitSingle = ADC_INITSINGLE_DEFAULT;
  ADCInitSingle.prsEnable = true;
  ADC_InitSingle(ADC0, &ADCInitSingle);
  
  /* Enable ADC Interrupt when Single Conversion Complete */
  ADC0->IEN = ADC_IEN_SINGLE;
  
  /* Enable ADC interrupt vector in NVIC*/
  NVIC_EnableIRQ(ADC0_IRQn);
   
  while(1)
  {
    /* Enter EM1 */ 
    EMU_EnterEM1();
    
    /* After ADC Single conversion wake up -> Delay 1000mS */  
    Delay(1000);
  }
}
