/*
 * ButtonInterrupt.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */

//#include<msp430g2553.h>

/*int ButtonInterrupt(void){

      P1OUT &= 0x00;               // Shut down everything
      P1DIR &= 0x00;
      P1DIR |= BIT0 + BIT1;            // P1.0 and P1.1 pins output the rest are input
      P1REN |= BIT3;                   // Enable internal pull-up/down resistors
      P1OUT |= BIT3;                   //Select pull-up mode for P1.3
      P1IE |= BIT3;                       // P1.3 interrupt enabled
      P1IES |= BIT3;                     // P1.3 Hi/lo edge
      P1IFG &= ~BIT3;                  // P1.3 IFG cleared
      _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt

}

    // Port 1 interrupt service routine
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        unsigned int i;
       P1OUT ^= BIT6 +BIT0;                      // Toggle P1.6 and P1.0
       for(i=0;i<50000;i++);                   //Delay
       P1IFG &= ~BIT3;                     // P1.3 IFG cleared


    }
*/
