/*
 * HardwarePWM.c
 *
 *  Created on: Oct 7, 2017
 *      Author: tomas
 */
#include <msp430fr2311.h>
void HardwarePWM(void){


    // Configure GPIO
    P2DIR |= BIT0 ;     // P2.0 output
    P2SEL0 |= BIT0;     //Select Pin to output to
    P1OUT &= 0x00;      //Shut everything down
    P1DIR &= 0x00;
    P1DIR |= 0x01;  // Set P1.0 to output direction
    P1REN |= 0x02;  // Enable internal pull-up/down resistors
    P1OUT |= 0x02;  //Select pull-up mode for P1.1
    P1IE  |= 0x02; // P1.1 interrupt enabled
    P1IES |= 0x02;  // P1.1 Hi/lo edge
    P1IFG &= ~BIT1; // P1.1 IFG cleared

    TB1CCR0 = 1000-1;                         // PWM Period
    TB1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB1CCR1 = 500;                            // CCR1 PWM duty cycle
    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    __bis_SR_register(LPM0_bits+GIE);             // Enter LPM0
    __no_operation();                         // For debugger
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;
   if(TB1CCR1 > 1000){      //Check if 100% Duty Cycle
       TB1CCR1 = 0;         //Reset CCR1
   }
   else{
       TB1CCR1 += 100;  //Increment CCR1

   }

   for(i=0;i<32000;i++);                //Delay
   P1IFG &= ~BIT1;                     // P1.1 IFG cleared



}

