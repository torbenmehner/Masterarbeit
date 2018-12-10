
#include "obssel.h"

#include "em_gpio.h"

#define PRS_CH_CTRL_SIGSEL_RACTX  0x00000001UL
#define PRS_CH_CTRL_SIGSEL_RACRX  0x00000002UL

#ifdef EFR32BG1
#define _PRS_CH_CTRL_SOURCESEL_RAC             0x00000020UL
#endif

#ifdef EFR32BG1X
#define _PRS_CH_CTRL_SOURCESEL_RAC             0x00000051UL
#endif

#define PRS_CH_CTRL_SOURCESEL_RAC                  (_PRS_CH_CTRL_SOURCESEL_RAC << 8)

void obssel_rx_setup(int rx_pin)
{

    // Configure the PRS channel GPIOs as outputs
    // GPIO Port C Pins 6-11
    GPIO_PinModeSet(gpioPortC, rx_pin, gpioModePushPull, 0);

    // Setup the PRS to output Rx enable on channel 10
    PRS->CH[10].CTRL = PRS_CH_CTRL_SIGSEL_RACRX
                       | PRS_CH_CTRL_SOURCESEL_RAC
                       | PRS_CH_CTRL_EDSEL_OFF;

    // Configure the PRS route locations
    switch (rx_pin) {
      case 6:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC0;
        break;
      case 7:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC1;
        break;
      case 8:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC2;
        break;
      case 9:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC3;
        break;
      case 10:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC4;
        break;
      case 11:
        PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH10LOC_LOC5;
        break;
      default:
        break;
    }
    // Enable the channel 10 output
    PRS->ROUTEPEN |= PRS_ROUTEPEN_CH10PEN;

}

void obssel_tx_setup(int tx_pin)
{

	// Configure the PRS channel GPIOs as outputs
	// GPIO Port C Pins 6-11
	GPIO_PinModeSet(gpioPortC, tx_pin, gpioModePushPull, 0);

	// Setup the PRS to output Tx enable on channel 11
	PRS->CH[11].CTRL = PRS_CH_CTRL_SIGSEL_RACTX
			| PRS_CH_CTRL_SOURCESEL_RAC
			| PRS_CH_CTRL_EDSEL_OFF;

	// Configure the PRS channel GPIOs as outputs
	// GPIO Port C Pins 6-11
	switch (tx_pin) {
	case 6:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC5;
		break;
	case 7:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC0;
		break;
	case 8:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC1;
		break;
	case 9:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC2;
		break;
	case 10:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC3;
		break;
	case 11:
		PRS->ROUTELOC2 |= PRS_ROUTELOC2_CH11LOC_LOC4;
		break;
	default:
		break;
	}
	// Enable the channel 11 output
	//PRS->ROUTEPEN |= PRS_ROUTEPEN_CH11PEN; //Hier noch nicht enable, da mit SD Karte doppelt belegt
	//diable 0xFFFFF7FF
}
