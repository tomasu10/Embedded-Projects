/*
 * ButtonInterrupt.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */

/**#include<msp430fr2311.h>

int ButtonInterrupt(void){
      P2OUT &= 0x00;                //Shut down Port 2
      P2DIR &= 0x00;
      P2DIR |= BIT0;                // P2.0 pin output the rest are input
      P1OUT &= 0x00;               // Shut down everything
      P1DIR &= 0x00;
      P1DIR |= BIT0 ;            // P1.0 pin output the rest are input
      P1REN |= BIT1;                   // Enable internal pull-up/down resistors
      P1OUT |= BIT1;                   //Select pull-up mode for P1.1
      P1IE |= BIT1;                       // P1.1 interrupt enabled
      P1IES |= BIT1;                     // P1.1 Hi/lo edge
      P1IFG &= ~BIT1;                  // P1.1 IFG cleared
      _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt

}

    // Port 1 interrupt service routine
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        unsigned int i;
       P1OUT ^= BIT0;                      // Toggle P1.0
       P2OUT ^= BIT0;
       for(i=0;i<50000;i++);                   //Delay
       P1IFG &= ~BIT1;                     // P1.1 IFG cleared


    }
*/
