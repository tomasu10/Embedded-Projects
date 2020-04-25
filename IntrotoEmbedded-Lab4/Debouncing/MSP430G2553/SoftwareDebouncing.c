/*
 * SoftwareDebouncing.c
 *
 *  Created on: Oct 8, 2017
 *      Author: tomas
 */

/**#include<msp430g2553.h>
void SoftwareDebouncing(void){

         P1OUT &= 0x00;               // Shut down everything
         P1DIR &= 0x00;
         P1DIR |= BIT0 + BIT6;            // P1.0 and P1.1 pins output the rest are input
         P1REN |= BIT3;                   // Enable internal pull-up/down resistors
         P1OUT |= BIT3;                   //Select pull-up mode for P1.3
         P1IE |= BIT3;                       // P1.3 interrupt enabled
         P1IES |= BIT3;                     // P1.3 Hi/lo edge
         P1IFG &= ~BIT3;                  // P1.3 IFG cleared


        //Timer B
        TA0CCTL0 = CCIE;                             // TA0CCR0 interrupt enabled


        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  if(P1IES & BIT3){
   TA0CCR0 = 3000;
   TA0CTL = TASSEL_2 + MC_1+ID_3;       //Start TimerA_0
   P1OUT ^= BIT0;                      //Toggle LEDs
   P1OUT ^= BIT6;
   P1IES &= ~BIT3;                      //Flip edge
   P1IE &= ~BIT3;                      //Disable interrupt
  }
  else{
         TA0CCR0 =3000;
         TA0CTL = TASSEL_2 + MC_1+ID_3;       //Start TimerA_0
         P1IES |= BIT3;
         P1IE &= ~BIT3;                      //Disable interrupt
  }

  P1IFG &= ~BIT3;                     // P5.6 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

   P1IE |=BIT3;
   TA1CTL = MC_0;               //Halt TimerA_1
   TA1CTL = TACLR;              //Turn off TimerA_1


}*/


