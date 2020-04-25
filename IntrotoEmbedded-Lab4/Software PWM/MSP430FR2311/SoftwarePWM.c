/*
 * SoftwarePWM.c
 *
 *  Created on: Oct 7, 2017
 *      Author: tomas
 */

/**#include <msp430fr2311.h>


void SoftwarePWM(void)
{
        P2OUT &= 0x00;      //Shut everything down
        P2DIR &= 0x00;
        P2DIR |= 0x01;      // Set P2.0 to output direction
        P1OUT &= 0x00;      //Shut everything down
        P1DIR &= 0x00;
        P1DIR |= 0x01; // Set P1.0 to output direction
        P1REN |= 0x02;
        P1OUT |= 0x02;
        P1IE  |= 0x02; // P1.1 interrupt enabled
        P1IES |= 0x02;
        P1IFG &= ~BIT1; // P1.1 IFG cleared


      //Timer B
      TB0CTL |= TBIE;
      TB0CCTL0 |= CCIE;                           // TB0CCR0 interrupt enabled
      TB0CCTL1 |= CCIE;                          //TB0CCR1 interrupt enabled
      TB0CCR0 = 1000;                              //Sets TB0CCR0 to 1000
      TB0CCR1 = 500;
      TB0CTL = TBSSEL_2 + MC_1+ID_0;                 //Start TimerB_0
      //TB1CTL = TBSSEL_2 + MC_1+ID_0;               //Start TimerB_1

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;
   if(TB0CCR1 == 1000){          //Check if 100% Duty Cycle
       TB0CCR1 = 0;              //Reset CCR1
   }
   else{
       TB0CCR1 += 100;           //Increment CCR1

   }

   for(i=0;i<32000;i++);                //Delay
   P1IFG &= ~BIT1;                     // P1.1 IFG cleared



}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{
  P2OUT |= BIT0;         //Toggle LED

}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer_B1(void)
{
  switch(TB0IV){        //Used to access CCR1
  case 2:{
      P2OUT &= ~BIT0;   //Toggle LED
  } break;
 }


}*/


