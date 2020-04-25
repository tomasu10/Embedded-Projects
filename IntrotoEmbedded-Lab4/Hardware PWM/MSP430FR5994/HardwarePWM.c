/*
 * HardwarePWM.c
 *
 *  Created on: Oct 8, 2017
 *      Author: tomas
 */

/**#include <msp430fr5994.h>
void HardwarePWM(void){


  // Configure GPIO
    P1OUT &= 0x00;             //Shutdown Output
    P1DIR |= 0x03;             // P1.1 and P1.2 output
    P1SEL0 |= 0x01;            //Select Pin to output to
    P1SEL1 = 0x00;

    P5OUT &= 0x00;      //Shut everything down
    P5DIR &= 0x00;
    P5DIR |= 0x00;
    P5REN |= BIT6;      // Enable internal pull-up/down resistors
    P5OUT |= BIT6;      //Select pull-up mode for P5.6
    P5IE  |= BIT6;      // P5.6 interrupt enabled
    P5IES |= BIT6;      // P5.6 Hi/lo edge
    P5IFG &= ~BIT6;     // P5.6 IFG cleared



    TA0CCR0 = 1000-1;                         // PWM Period
    TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TA0CCR1 = 500;                            // CCR1 PWM duty cycle
    TA0CTL = TASSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    __bis_SR_register(LPM0_bits+GIE);             // Enter LPM0
    __no_operation();                         // For debugger
}

 //Port 5 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    unsigned int i;
   if(TA0CCR1 > 1000){      //Check if 100% Duty Cycle
       TA0CCR1 = 0;         //Reset CCR1
   }
   else{
       TA0CCR1 += 100;      //Increment CCR1

   }

   for(i=0;i<32000;i++);                //Delay
   P5IFG &= ~BIT6;                     // P5.6 IFG cleared



}*/


