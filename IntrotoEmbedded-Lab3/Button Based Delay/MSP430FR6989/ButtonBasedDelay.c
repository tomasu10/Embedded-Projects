/**#include <msp430.h>


int ButtonBasedDelay(void)
{

        P1OUT &= 0x00;  //Shut everything down
        P1DIR &= 0x00;
        P1DIR |= 0x01; // Set P1.0 to output direction
        P9DIR |= 0x80;
        P1REN |= 0x02;  //Set pull up/down resistors
        P1OUT |= 0x02;  //Select pull up resistor
        TA0CCTL0  = CCIE;   // CCR0 interrupt enabled
        TA1CCTL1  = CCIE;   // CCR1 interrupt enabled
        P1IE   = 0x02; // P1.1 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x02;
        P1IFG &= ~BIT1; // P1.1 IFG cleared
        TA0CCR0 = 0;

        TA0CTL  = TASSEL_1 + MC_1;
      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#pragma vector=PORT1_VECTOR             //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{
    unsigned int i;
        unsigned int time = 0;
        if(P1IES & 0x02){
            P1OUT |= BIT0 ;                         // Toggle P1.0
            TA1CTL  = TASSEL_1 + MC_2;              //Start TimerA_1
            P1IES &= 0xFC;                          //Flip Edge of Button interrupt
        }
        else
        {
            time = TA1R;                            //Set TimerA_1 counter to time
            TA0CCR0 = time;                         //Set time to TA0CCR0
            TA1CTL = TACLR;                         //Turn off TimerA_1
            P1OUT &= ~BIT0;                         //Toggle P1.0
            P1IES |= 0x02;                          //Flip Edge of Button interrupt
        }

       for(i=0;i<5000;i++);                //Delay
       P1IFG &= ~BIT1;                     // P1.1 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P9OUT ^= 0x80;          //Toggle P9.7
}
*/



