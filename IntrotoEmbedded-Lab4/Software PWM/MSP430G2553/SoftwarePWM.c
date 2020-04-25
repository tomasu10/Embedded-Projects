/*
 * SoftwarePWM.c
 *
 *  Created on: Oct 8, 2017
 *      Author: tomas
 */


/**#include <msp430g2553.h>


void SoftwarePWM(void)
{
     P1OUT &= 0x00;               // Shut down everything
     P1DIR &= 0x00;
     P1DIR |= BIT0 + BIT6;            // P1.0 and P1.1 pins output the rest are input
     P1REN |= BIT3;                   // Enable internal pull-up/down resistors
     P1OUT |= BIT3;                   //Select pull-up mode for P1.3
     P1IE |= BIT3;                       // P1.3 interrupt enabled
     P1IES |= BIT3;                     // P1.3 Hi/lo edge
     P1IFG &= ~BIT3;                  // P1.3 IFG cleared


      //Timer A
      TA0CTL |= TAIE;
      TA0CCTL0 |= CCIE;                           // TA0CCR0 interrupt enabled
      TA0CCTL1 |= CCIE;                          //TA0CCR1 interrupt enabled
      TA0CCR0 = 1000;                              //Sets TA0CCR0 to 1000
      TA0CCR1 = 500;                               //Sets TA0CCR1 to 500
      TA0CTL = TASSEL_2 + MC_1+ID_0;                 //Start TimerA_0
      //TB1CTL = TBSSEL_2 + MC_1+ID_0;               //Start TimerB_1

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;
   if(TA0CCR1 == 1000){                     //Check if 100% Duty Cycle
       TA0CCR1 = 0;                         //Reset CCR1
   }
   else{
       TA0CCR1 += 100;                      //Increment CCR1

   }

   for(i=0;i<32000;i++);                //Delay
   P1IFG &= ~BIT3;                     // P1.3 IFG cleared



}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT |= BIT0;        //Toggle LED

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch(TA0IV){            //Used to access CCR1
  case 2:{
      P1OUT &= ~BIT0;       //Toggle LED
  } break;
 }


}*/

