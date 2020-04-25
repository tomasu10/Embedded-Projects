#include <msp430.h>

int HardwarePWM(void)
{


  P1IE   = 0x02;           // P1.1 interrupt enabled
  P1IES |= 0x02;            // P1.1 Hi/lo edge
  P1IFG &= ~BIT1;           // P1.1 IFG cleared
  P1REN |= BIT1;            // Enable internal pull-up/down resistors

  P1DIR |= BIT0;          //Set pin 1.0 to the output direction.
  P1SEL |= BIT0;         //Select pin 1.0 as our PWM output.
  TA0CCR0 = 1000;        // PWM Period
  TA0CCTL1 = OUTMOD_7;  // CCR1 reset/set
  TA0CCR1 = 500;        // CCR1 PWM duty cycle

   __bis_SR_register(LPM4_bits + GIE);           //Switch to low power mode 0.
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
        unsigned int i;

          if (TA0CCR1 == 1000){     //Check if 100% Duty Cycle
            TA0CCR1 = 0;            //Reset CCR1
          }
          else{
            TA0CCR1 = TA0CCR1 + 100;    //Increment CCR1
          }
       for(i=0;i<1000;i++);                //Delay
       P1IFG &= ~BIT1;                      // P1.1 IFG cleared
}





