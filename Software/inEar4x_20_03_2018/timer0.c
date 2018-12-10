/**************************************************************************//**
 * @file TIMER0.c
 * @brief TIMER0 for Wearable Platform & TrinkTracker
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
  #include "em_letimer.h"
  #include "TIMER0.h"
	bool TimerDone;

	  /* LETIMER0 start parameters */
	 LETIMER_Init_TypeDef letimerInit ={
		  .enable   = true,       /* Start counting when init completed */
		  .debugRun = false,      /* Counter shall not keep running during debug halt. */
		  .comp0Top = true,      /* Dont load COMP0 register into CNT when counter underflows.*/
		  .bufTop   = false,      /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
		  .out0Pol  = 0,       /* Idle value for output 0. */
		  .out1Pol  = 0,       /* Idle value for output 1. */
		  .ufoa0    = letimerUFOANone,  /* No output on output 1 */
		  .ufoa1    = letimerUFOANone,  /* No output on output 1*/
		  .repMode  = letimerRepeatBuffered /* Count while REP != 0 */
		  };
	  /* LETIMER0 stop parameters */
	 LETIMER_Init_TypeDef letimerDeInit ={
		  .enable   = false,       /* Start counting when init completed */
		  .debugRun = false,      /* Counter shall not keep running during debug halt. */
		  .comp0Top = true,      /* Dont load COMP0 register into CNT when counter underflows.*/
		  .bufTop   = false,      /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
		  .out0Pol  = 0,       /* Idle value for output 0. */
		  .out1Pol  = 0,       /* Idle value for output 1. */
		  .ufoa0    = letimerUFOANone,  /* No output on output 1 */
		  .ufoa1    = letimerUFOANone,  /* No output on output 1*/
		  .repMode  = letimerRepeatBuffered /* Count while REP != 0 */
		  };



  /* TIMER0 start parameters */
  TIMER_Init_TypeDef TIMER0Init = { .enable = true, .debugRun = true, .prescale =
      TIMER0_PRESCALE, .clkSel = timerClkSelHFPerClk, .fallAction =
      timerInputActionNone, .riseAction = timerInputActionNone, .mode =
      timerModeUp, .dmaClrAct = false, .quadModeX4 = false, .oneShot = false,
      .sync = false, };

  /* TIMER0 stop parameters */
  TIMER_Init_TypeDef TIMER0DeInit = { .enable = false, .debugRun = true,
      .prescale = TIMER0_PRESCALE, .clkSel = timerClkSelHFPerClk, .fallAction =
          timerInputActionNone, .riseAction = timerInputActionNone, .mode =
          timerModeUp, .dmaClrAct = false, .quadModeX4 = false, .oneShot = false,
      .sync = false, };

  /***************************************************************************
   * @brief
   *   Start Timer 0
   *
   **************************************************************************/
  void startLETIMER0()
  {
    LETIMER_CompareSet(LETIMER0, 0, LETIMER0_CC0);
	LETIMER_RepeatSet(LETIMER0, 0,  LETIMER0_REP0);
	LETIMER_RepeatSet(LETIMER0, 1,  LETIMER0_REP1);
    NVIC_SetPriority(LETIMER0_IRQn, 0); //höchste prio
    //TIMER_TopSet(LETIMER0, LETIMER0_TOP);
    //LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
    LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);  //LETIMER_IF_UF LETIMER_IEN_COMP0
    NVIC_ClearPendingIRQ(LETIMER0_IRQn);
    NVIC_EnableIRQ(LETIMER0_IRQn);
    LETIMER_Init(LETIMER0, &letimerInit);
  }

  void stopLETIMER0() {
    /* Disable interrupt */
    LETIMER_IntDisable(LETIMER0, LETIMER_IF_UF);

    /* Disable TIMER0 interrupt vector in NVIC */
    NVIC_DisableIRQ(LETIMER0_IRQn);

    /* Configure TIMER */
    LETIMER_Init(LETIMER0, &letimerDeInit); //!!! will mit gcc nicht
  }

  void startTIMER0() {
    /* Enable overflow interrupt */
    TIMER_IntEnable(TIMER0, TIMER_IF_OF);

    /* Enable TIMER0 interrupt vector in NVIC */
    NVIC_SetPriority(TIMER0_IRQn, 3); //test prio runter gesetzt
    NVIC_EnableIRQ(TIMER0_IRQn);

    /* Set TIMER Top value */
    TIMER_TopSet(TIMER0, TIMER0_TOP);

    /* Configure TIMER */
    TIMER_Init(TIMER0, &TIMER0Init);
  }

  /***************************************************************************
   * @brief
   *   Stop Timer 0
   *
   **************************************************************************/
  void stopTIMER0() {
    /* Disable interrupt */
    TIMER_IntDisable(TIMER0, TIMER_IF_OF);

    /* Disable TIMER0 interrupt vector in NVIC */
    NVIC_DisableIRQ(TIMER0_IRQn);

    /* Configure TIMER */
    TIMER_Init(TIMER0, &TIMER0DeInit); //!!! will mit gcc nicht
  }

