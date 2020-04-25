#include <msp430fr6989.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
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
