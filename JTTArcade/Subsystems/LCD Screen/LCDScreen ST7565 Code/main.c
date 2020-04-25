#include <msp430fr5994.h>
#include <eusci_b_spi.h>
#include <gpio.h>
#include <pmm.h>
#include <cs.h>
#include "driverlib.h"
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//LCDDisplay();
	  //lcdspi();
	//lcdspi2();
	touchpad();
	
	while(1);

	return 0;
}
