#include <msp430fr6989.h>
/**
 * ButtonInterrupt
 */
int ButtonInterrupt(void)
{


    P1OUT &= 0x00;  // Shut down everything
    P1DIR &= 0x00;
    P1DIR |= 0x01;  // Set P1.0 to output direction
    P9OUT &= 0x00;  // Shut down everything
    P9DIR &= 0x00;
    P9DIR |= 0x80;  // Set P9.7 to output direction
    P1REN |= 0x02;  // Enable internal pull-up/down resistors
    P1OUT |= 0x02;  //Select pull-up mode for P1.1
    P1IE  = 0x02;   // P1.1 interrupt enabled                      //interrupt is enabled here, as well as interrupt clear
    P1IES |= 0x02;  // P1.1 Hi/lo edge
    P1IFG &= ~BIT1; // P1.1 IFG cleared
    _BIS_SR(LPM4_bits + GIE); // Enter LPM4 w/interrupt

}


// Port 1 interrupt service routine
/*#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

    //ButtonInterrupt
    unsigned int i;
    P1OUT  ^=  0x01; // Toggle LEDs
    P9OUT  ^=  0x80;
    for(i = 0; i<50000; i++);   //Delay
    P1IFG  &= ~BIT1; // P1.3 IFG cleared  // P1.1 IFG cleared

}*/

