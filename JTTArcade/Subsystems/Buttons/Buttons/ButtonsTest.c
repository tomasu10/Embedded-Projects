#include<msp430fr5994.h>

int ButtonsTest(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    initButtonsTest();
    initInterruptsTest();
}

int initButtonsTest(void)
{

    P1OUT &= 0x00;                                      // Shut Port 1 Down
    P1DIR |= BIT0;                               // Port 1 direction set

    //B3 and B4
    P3OUT &= 0x00;                                      // Shut Port 3 Down
    P3DIR &= 0x00;                                      // Port 3 direction set
    P3OUT  = BIT6 + BIT7;                               // Select pull-up mode for Pin 3
    P3REN |= BIT6 + BIT7;                               // Enable internal pull-up/down resistors

}

int initInterruptsTest(void)
{
    //B3 and B4
    P3IE  |= BIT6 + BIT7;                    // P3 interrupt enabled
    P3IES |= BIT6 + BIT7;                    // P3 Hi/lo edge
    P3IFG &= ~BIT6 + ~BIT7;                  // P3 IFG cleared

    _BIS_SR(CPUOFF + GIE);                   // Enter LPM0 w/ interrupt
}

