/**************************************************************************//**
 * @file TIMER1.c
 * @brief TIMER1 for Wearable Platform & TrinkTracker
 * @author czimmer@fzi.de
 * @version 0.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014-2015 FZI Forschungszentrum Informatik, http://www.fzi.de</b>
 * ******************************************************************************
 * @section Version
 * Date			Version	Author		Comment
 * 2014-11-15	0.1		czimmer 	Initial Version
 * 2015-09-17 0.2   czimmer   Refactoring, Documentation
 *
 * ******************************************************************************
 * @section Issues
 * - one c/h file for all timers
 *
 * *****************************************************************************/

  #include "em_timer.h"
  #include "TIMER1.h"
	bool TimerDone;

  /* TIMER1 start parameters */
  TIMER_Init_TypeDef TIMER1Init = { .enable = true, .debugRun = true, .prescale =
      TIMER1_PRESCALE, .clkSel = timerClkSelHFPerClk, .fallAction =
      timerInputActionNone, .riseAction = timerInputActionNone, .mode =
      timerModeUp, .dmaClrAct = false, .quadModeX4 = false, .oneShot = false,
      .sync = false, };

  /* TIMER1 stop parameters */
  TIMER_Init_TypeDef TIMER1DeInit = { .enable = false, .debugRun = true,
      .prescale = TIMER1_PRESCALE, .clkSel = timerClkSelHFPerClk, .fallAction =
          timerInputActionNone, .riseAction = timerInputActionNone, .mode =
          timerModeUp, .dmaClrAct = false, .quadModeX4 = false, .oneShot = false,
      .sync = false, };

  /***************************************************************************
   * @brief
   *   Start Timer 1
   *
   **************************************************************************/

  void startTIMER1() {
    /* Enable overflow interrupt */
    TIMER_IntEnable(TIMER1, TIMER_IF_OF);

    /* Enable TIMER1 interrupt vector in NVIC */
    NVIC_SetPriority(TIMER1_IRQn, 3); //test prio runter gesetzt
    NVIC_EnableIRQ(TIMER1_IRQn);

    /* Set TIMER Top value */
    TIMER_TopSet(TIMER1, TIMER1_TOP);

    /* Configure TIMER */
    TIMER_Init(TIMER1, &TIMER1Init);
  }

  /***************************************************************************
   * @brief
   *   Stop Timer 0
   *
   **************************************************************************/
  void stopTIMER1() {
    /* Disable interrupt */
    TIMER_IntDisable(TIMER1, TIMER_IF_OF);

    /* Disable TIMER1 interrupt vector in NVIC */
    NVIC_DisableIRQ(TIMER1_IRQn);

    /* Configure TIMER */
    TIMER_Init(TIMER1, &TIMER1DeInit); //!!! will mit gcc nicht
  }

