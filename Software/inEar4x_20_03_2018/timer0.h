#ifndef TIMER0_H_
#define TIMER0_H_

  #include "em_timer.h"
  #include "TIMER0.h"

  #define TIMER0_TOP      5500      // Counting Top Value of TIMER0 38500
  #define TIMER0_PRESCALE timerPrescale64  // Prescale of TIMER0

  #define LETIMER0_CC0 	  31

  #define LETIMER0_REP0	  0xFF //EFR32 REP nur 8Bit breit
  #define LETIMER0_REP1	  0xFF

  void startTIMER0(void);
  void stopTIMER0(void);
  void startLETIMER0(void);

#endif /* TIMER0_H_ */
