/*#include <msp430.h>


int Debouncing()
{


   //******GPIO Setup*******

    P1DIR &= 0x00;  // Shut down everything
    P1DIR |= BIT0;  // P1.0 pin output the rest are input
    P1OUT &= 0x00;
    P1OUT |= BIT1;  //Select pull-up mode for P1.1
    P1REN |= BIT1;  // Enable internal pull-up/down resistors
    TA0CCTL0  = CCIE;
    TA0CCR0 = 32000;
    P1IFG &= ~BIT1; // P1.1 IFG cleared
    P1IE   = BIT1;  // P1.1 interrupt enabled
    P1IES |= BIT1;  // P1.1 Hi/lo edge

    _bis_SR_register(LPM0_bits + GIE);  // Enter LPM0 w/ interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT  ^= BIT0;
    TA0CTL  = TASSEL_2 + MC_1 ;
    P1IE  &= ~BIT1;
    P1IFG &= ~BIT1;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1IE |= BIT1;
    TA0CTL = MC_0;
    TA0CTL = TACLR;
}

*/


