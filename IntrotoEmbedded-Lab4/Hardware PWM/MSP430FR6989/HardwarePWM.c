#include <msp430.h>

int HardwarePWM(void)
{

  P1IE   = 0x02;    // P1.1 interrupt enabled,
  P1IES |= 0x02;    // P1.1 Hi/lo edge
  P1IFG &= ~BIT1;   // P1.1 IFG cleared
  P1REN |= BIT1;    // Enable internal pull-up/down resistors

  P1DIR |= BIT0;  // P1.0 Output
  P1SEL0 |= BIT0;  //Select Pin to output to
  P1SEL1 = 0;
  TA0CCR0 = 1000; // PWM Period
  TA0CCTL1 = OUTMOD_7;  // CCR1 reset/set
  TA0CCR1 = 500;        // CCR1 PWM duty cycle
  TA0CTL = TASSEL_2 + MC_1; // SMCLK, up mode

   __bis_SR_register(LPM4_bits + GIE);           //Switch to low power mode 0.
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
        unsigned int i;

          if (TA0CCR1 == 1000){ //Check if 100% Duty Cycle
            TA0CCR1 = 0;        //Reset CCR1
          }
          else{
            TA0CCR1 = TA0CCR1 + 100;    //Increment CCR1
          }
       for(i=0;i<10000;i++);                //Delay
       P1IFG &= ~BIT1;                      // P1.1 IFG cleared
}




