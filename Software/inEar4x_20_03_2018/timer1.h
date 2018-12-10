#ifndef TIMER1_H_
#define TIMER1_H_

  #include "em_timer.h"
  #include "TIMER1.h"

  #define TIMER1_TOP      4125      // Counting Top Value of TIMER1
  #define TIMER1_PRESCALE timerPrescale1024  // Prescale of TIMER1

  void startTIMER1(void);
  void stopTIMER1(void);

#endif /* TIMER0_H_ */
