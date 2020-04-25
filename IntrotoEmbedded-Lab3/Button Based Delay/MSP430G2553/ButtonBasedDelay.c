/*
 * ButtonBasedDelay.c
 *
 *  Created on: Sep 27, 2017
 *      Author: tomas
 */


/**#include <msp430g2553.h>


void ButtonBasedDelay(void)
{

        P1OUT &= 0x00;      //Shut everything down
        P1DIR &= 0x00;
        P1DIR |= 0x41; // Set P1.0 to output direction
        P1REN |= 0x08;
        P1OUT |= 0x08;
        P1IE  |= 0x08; // P1.3 interrupt enabled
        P1IES |= 0x08;
        P1IFG &= ~BIT3; // P1.3 IFG cleared


      //Timer A
      CCTL0 = CCIE;                             // TA0CCR0 interrupt enabled
      TA1CCTL1 = CCIE;                          //TA1CCR0 interrupt enabled
      TA0CCR0 = 0;                              //Sets TA0CCR0 to 0
      TA0CTL = TASSEL_1 + MC_1;                 //Start TimerA_0

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

    unsigned int i;
    unsigned int recTime = 0;
    if(P1IES & 0x08){
        P1OUT |= BIT6 ;                         // Toggle P1.6
        TA1CTL = TASSEL_1 + MC_2;               //Start TimerA_1
        P1IES &= 0xF7;                          //Flip Edge of Button interrupt
    }
    else{
        recTime = TA1R;                         //Set TimerA_1 counter to recTime
        TA0CCR0 = recTime;                      //Set recTime to TA0CCR0
        TA1CTL = TACLR;                         //Turn off TimerA_1
        P1OUT &= ~BIT6;                         //Toggle P1.6
        P1IES |= 0x08;                          //Flip Edge of Button interrupt
    }

   for(i=0;i<10000;i++);                //Delay
   P1IFG &= ~BIT3;                     // P1.3 IFG cleared



}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT ^= BIT0;        //Toggle P1.0

}*/

