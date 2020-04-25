/*
 * TimerABlink.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */
/**#include<msp430fr2311.h>
void TimerABlink(void){

  P1DIR |= 0x01;                            // P1.0 output
  P2DIR |= 0x01;                            // P2.0 output
  TB0CCTL1 = CCIE;                             // CCR1 interrupt enabled
  TB0CCR1 = 50000;
  TB0CCTL2 = CCIE;                             // CCR2 interrupt enabled
  TB0CCR2 = 10000;
  TBCTL = TBSSEL_2 + MC_2+ID_3;                  // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_B3 Interrupt Vector (TB0IV) handler
#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer_B(void)
{
  switch( TB0IV )
  {
  case  2:                                  // CCR1
    {
    P1OUT ^= 0x01;                          // Toggle P1.0
    TB0CCR1 += 50000;                          // Add Offset to CCR1
    }
           break;
  case  4:                                  // CCR2
      {
          P2OUT ^= 0x01;                    // Toggle P2.0
          TB0CCR2 += 25000;                  // Add Offset to CCR2
    }
      }
      break;

  case 10: break;                           // overflow not used
 }
}
*/


