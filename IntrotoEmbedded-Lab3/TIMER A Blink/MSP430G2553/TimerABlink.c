/*
 * TimerABlink.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */
/*#include<msp430g2553.h>
void TimerABlink(void){

  P1DIR |= 0x41;                            // P1.0 output
  CCTL1 = CCIE;                             // CCR1 interrupt enabled
  CCR1 = 50000;
  CCTL2 = CCIE;                             // CCR2 interrupt enabled
  CCR2 = 10000;
  TACTL = TASSEL_2 + MC_2+ID_3;                  // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TA0IV )
  {
  case  2:                                  // CCR1
    {
    P1OUT ^= 0x01;                          // Toggle P1.0
    CCR1 += 50000;                          // Add Offset to CCR1
    }
           break;
  case  4:                                  //CCR2
      {
          P1OUT ^= 0x40;                     // Toggle P1.06
          CCR2 += 25000;                     // Add Offset to CCR2
      }
      break;

  case 10: break;                           // overflow not used
 }
}*/

