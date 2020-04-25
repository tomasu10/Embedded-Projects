#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//SimpleBlink();
	//MultipleBlink();
	//ButtonBlink();
	//BlinkButtonColorChange();
	//ButtonInterrupt();
	//TimerABlink();
	//ButtonBasedDelay();
	//Debouncing();
	//SoftwarePWM();
	HardwarePWM();
}
