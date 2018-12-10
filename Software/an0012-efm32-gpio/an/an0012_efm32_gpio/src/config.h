/*****************************************************************************
 * @file config.h
 * @brief Watchdog Demo Application
 * @author Silicon Labs
 * @version 2.01
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2017 Silicon Labs, http://www.silabs.com</b>
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

/* MACRO */
#if defined ( STK3300 )
  /* Tiny Gecko STK */
  #define LED_PORT  gpioPortD
  #define LED_PIN   7
#elif defined ( Gxxx_STK )
  /* Gecko STK */
  #define LED_PORT  gpioPortC
  #define LED_PIN   0
#elif defined ( STK3600 )
  /* Leopard Gecko STK */
  #define LED_PORT  gpioPortE
  #define LED_PIN   2
#elif defined ( STK3700 )
  /* Giant Gecko STK */
  #define LED_PORT  gpioPortE
  #define LED_PIN   2
#elif defined ( STK3800 )
  /* Wonder Gecko STK */
  #define LED_PORT  gpioPortE
  #define LED_PIN   2
#elif defined ( STK3200 )
  /* Zero Gecko STK */
  #define LED_PORT  gpioPortC
  #define LED_PIN   10
#elif defined ( STK3400 )
  /* Happy Gecko STK */
  #define LED_PORT  gpioPortF
  #define LED_PIN   4
#elif defined ( STK3401 )
  /* Pearl Gecko (PG1) STK */
  #define LED_PORT  gpioPortF
  #define LED_PIN   4
#elif defined ( STK3402 )
  /* Pearl Gecko (PG12) STK */
  #define LED_PORT  gpioPortF
  #define LED_PIN   4
#elif defined ( STK3403 )
  /* Giant Gecko (GG11) STK */
  #define LED_PORT  gpioPortF
  #define LED_PIN   4
#else
  #error "undefined KIT"
#endif

#if defined ( Gxxx_STK ) || defined ( STK3300 ) || defined ( STK3600 ) || defined ( STK3700 ) || defined ( STK3800 )
/* Series 0 with segment LCD */
#define SEG_LCD_S0
#elif defined ( STK3200 ) || defined ( STK3400 )
/* Series 0 with TFT LCD */
#define TFT_LCD_S0
#else
/* Series 1 with TFT LCD */
#define TFT_LCD_S1
#endif

#if defined ( TFT_LCD_S1 )
#define  T_DOG     0
#define  T_LCK     1
#define  T_INT     2
#define  T_CLR     3
#define  T_EVT     4
#define  T_WRN     5
#define  T_WIN     6
#define  T_DOG2    8
#define  T_END     7
#else
#define  T_DOG     0
#define  T_LCK     1
#define  T_END     2
#endif

#define PRS_CH_CTRL_SOURCESEL_WDOG PRS_CH_CTRL_SOURCESEL_LETIMER0  /* PRS channel */
#define TIMER_WAKEUP_INTERVAL_MS    500                            /* Wake interval */
#define RTC_WAKEUP_INTERVAL_MS    50                               /* Wake interval */

/* Function declaration */
int selectState(void);
void gpioSetup(void);
void lcdInit(void);

#if defined ( SEG_LCD_S0 )
void rtcSetup(void);
#endif

#if defined ( TFT_LCD_S1 )
void prsSetup(void);
void testDog(void);
void testLock(void);
void testInterrupt(void);
void testClear(void);
void testEvent(void);
void testWarning(void);
void testWindow(void);
void modeTest(unsigned int tMode);
void wdogSetup(unsigned int tMode);
void letimerSetup(unsigned int tMode);
#endif

#if defined ( TFT_LCD_S0 ) || defined ( TFT_LCD_S1 )
void timerSetup(void);
#endif
