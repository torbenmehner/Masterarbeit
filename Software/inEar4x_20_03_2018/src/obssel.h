
#ifndef _OBSSEL_H_DEF_
#define _OBSSEL_H_DEF_


/* uncomment one of the following defines, depending on your target device
 *
 * EFR32BG1:  this setting is valid for BGMxxx modules and EFR32BG1 SoC designs
 * EFR32BG1X: valid for EFR32BG12, EFR32BG13
 * */

//#define EFR32BG1
#define EFR32BG1X

/* enable RX activity indicator, Pin PCx
 * Pin number is given as argument, valid range 6..11
 * */
void obssel_rx_setup(int rx_pin);


/* enable TX activity indicator, Pin PCx
 * Pin number is given as argument, valid range 6..11
 * */
void obssel_tx_setup(int rx_pin);


#endif
