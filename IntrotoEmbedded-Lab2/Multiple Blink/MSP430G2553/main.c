#include <msp430g2553.h>
#include <SimpleBlink.h>
#include<MultipleBlink.h>
#include<BlinkButtonColorChange.h>

/**
 * main.c
 */
int main(void)
{

     WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    //SimpleBlink();
    //MultipleBlink();
    //ButtonBlink();
    //BlinkButtonColorChange();
    //ButtonInterrupt();
    //TimerABlink();
    //ButtonBasedDelay();
     //SoftwareDebouncing();
     //SoftwarePWM();
     HardwarePWM();

	 return 0;

}
