#include <msp430.h> 
#include "ledspi.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	ADDRS_LED();

	return 0;
}
