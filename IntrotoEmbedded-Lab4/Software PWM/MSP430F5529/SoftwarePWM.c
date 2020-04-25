#include <msp430.h>
/**
int SoftwarePWM(void)
{
        P1OUT &= 0x00;   // Shut down everything
        P1DIR &= 0x00;
        P1DIR |= 0x01; // Set P1.0 to output direction
        P1REN |= 0x02;  // Enable internal pull-up/down resistors
        P1OUT |= 0x02;  //Select pull-up mode for P1.1
        TA0CCTL0  = CCIE;   // CCR0 interrupt enabled
        TA0CCTL1  = CCIE;   //CCR1 interrupt enabled
        P1IE   = 0x02; // P1.1 interrupt enabled
        P1IES |= 0x02;  // P1.1 Hi/lo edge
        P1IFG &= ~BIT1; // P1.1 IFG cleared
        TA0CCR0 = 1000; //Sets TA0CCR0 to 1000
        TA0CCR1 = 500;  //Sets TA0CCR1 to 500


        TA0CTL  = TASSEL_2 + MC_1;  //Start TimerA_0
      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;

          if (TA0CCR1 == 1000){ //Check if 100% Duty Cycle
            TA0CCR1 = 0;        //Reset CCR1
          }
          else{
            TA0CCR1 = TA0CCR1 + 100;     //Increment CCR1
          }
       for(i=0;i<5000;i++);                //Delay
       P1IFG &= ~BIT1;                      // P1.1 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT |= 0x01;      //Toggle LED
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    switch(TA0IV){  //Used to access CCR1
    case 2:
    {
        P1OUT &= ~0x01;      //Toggle LED
    } break;
    }
}
*/



