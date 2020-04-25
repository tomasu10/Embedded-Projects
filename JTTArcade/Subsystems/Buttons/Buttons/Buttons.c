#include<msp430fr5994.h>

int Buttons(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    initButtons();
    initInterrupts();
}

int initButtons(void)
{
    //B1 and B2
    P1OUT &= 0x00;                                      // Shut Port 1 Down
    P1DIR |= BIT0;                                      // Port 1 direction set
    P1OUT  = ~(BIT6 + BIT7);                            // Select pull-up mode for Pin 1
    P1REN |= BIT6 + BIT7;                               // Enable internal pull-up/down resistors

    //B3 and B4
    P3OUT &= 0x00;                                      // Shut Port 3 Down
    P3DIR &= 0x00;                                      // Port 3 direction set
    P3OUT  = ~(BIT6 + BIT7);                               // Select pull-up mode for Pin 3
    P3REN |= BIT6 + BIT7;                               // Enable internal pull-up/down resistors

    //B5 and B6
    P2OUT &= 0x00;                                      // Shut Port 2 Down
    P2DIR &= 0x00;                                      // Port 2 direction set
    P2OUT  = ~(BIT5 + BIT6);                               // Select pull-up mode for Pin 2
    P2REN |= BIT5 + BIT6;                               // Enable internal pull-up/down resistors

    //B7 and B8 and B9 and B10
    P4OUT &= 0x00;                                      // Shut Port 4 Down
    P4DIR &= 0x00;                                      // Port 4 direction set
    P4OUT  = ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4);          // Select pull-up mode for Pin 4
    P4REN |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;          // Enable internal pull-up/down resistors

    //B5 and B6 and DPad
    P7OUT &= 0x00;                                      // Shut Port 7 Down
    P7DIR &= 0x00;                                      // Port 7 direction set
    P7OUT  = ~(BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);   // Select pull-up mode for Pin 7
    P7REN |= BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;   // Enable internal pull-up/down resistors

    //Joystick
    P6OUT &= 0x00;                                      // Shut Port 6 Down
    P6DIR &= 0x00;                                      // Port 6 direction set
    P6OUT  = ~(BIT4 + BIT5 + BIT6 + BIT7);                 // Select pull-up mode for Pin 6
    P6REN |= BIT4 + BIT5 + BIT6 + BIT7;                 // Enable internal pull-up/down resistors
}

int initInterrupts(void)
{
    //B1 and B2
    P1IE  |= BIT6 + BIT7;                    // P1 interrupt enabled
    P1IES |= BIT6 + BIT7;                    // P1 Hi/lo edge
    P1IFG &= ~BIT6 + ~BIT7;                  // P1 IFG cleared

    //B3 and B4
    P3IE  |= BIT6 + BIT7;                    // P3 interrupt enabled
    P3IES |= BIT6 + BIT7;                    // P3 Hi/lo edge
    P3IFG &= ~BIT6 + ~BIT7;                  // P3 IFG cleared

    //B5 and B6
    P2IE  |= BIT6 + BIT5;                    // P2 interrupt enabled
    P2IES |= BIT6 + BIT5;                    // P2 Hi/lo edge
    P2IFG &= ~BIT6 + ~BIT5;                  // P2 IFG cleared

    //B7 and B8 and B9 and B10
    P4IE  |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;                    // P4 interrupt enabled
    P4IES |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;                    // P4 Hi/lo edge
    P4IFG &= ~BIT0 + ~BIT1 + ~BIT2 + ~BIT3 + ~BIT4;               // P4 IFG cleared

    //B5 and B6 and DPad
    P7IE  |= BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;             // P7 interrupt enabled
    P7IES |= BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;             // P7 Hi/lo edge
    P7IFG &= ~BIT2 + ~BIT3 + ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;       // P7 IFG cleared

    //Joystick
    P6IE  |= BIT4 + BIT5 + BIT6 + BIT7;                    // P6 interrupt enabled
    P6IES |= BIT4 + BIT5 + BIT6 + BIT7;                    // P6 Hi/lo edge
    P6IFG &= ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;                // P6 IFG cleared

    _BIS_SR(CPUOFF + GIE);                                 // Enter LPM0 w/ interrupt
}

// Port 1 interrupt service routine
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        if(P1IFG & BIT6)                                  //If B1 is pressed
        {
           P1OUT = BIT6;
           P1IFG &= ~BIT6;
        }

        if(P1IFG & BIT7)                                  //If B2 is pressed
        {
           P1OUT = BIT7;
           P1IFG &= ~BIT7;
        }
    }

// Port 3 interrupt service routine
    #pragma vector=PORT3_VECTOR
    __interrupt void Port_3(void)
    {
            if(P3IFG & BIT7)                                  //If B3 is pressed
            {
               P3OUT = BIT7;
               P3IFG &= ~BIT7;
            }

            if(P3IFG & BIT6)                                  //If B4 is pressed
            {
               P3OUT = BIT6;
               P3IFG &= ~BIT6;
            }
        }

// Port 2 interrupt service routine
    #pragma vector=PORT2_VECTOR
    __interrupt void Port_2(void)
    {
                if(P2IFG & BIT6)                              //If B5 is pressed
                {
                   P2OUT = BIT6;
                   P2IFG &= ~BIT6;
                }

                if(P2IFG & BIT5)                              //If B6 is pressed
                {
                   P2OUT = BIT5;
                   P2IFG &= ~BIT5;
                }
            }

// Port 4 interrupt service routine
    #pragma vector=PORT4_VECTOR
    __interrupt void Port_4(void)
    {
                    if(P4IFG & BIT3)                        //If B7 is pressed
                    {
                       P4OUT = BIT3;
                       P4IFG &= ~BIT3;
                    }

                    if(P4IFG & BIT2)                        //If B8 is pressed
                    {
                       P4OUT = BIT2;
                       P4IFG &= ~BIT2;
                    }

                    if(P4IFG & BIT1)                        //If B9 is pressed
                    {
                       P4OUT = BIT1;
                       P4IFG &= ~BIT1;
                    }
                    if(P4IFG & BIT0)                        //If B10 is pressed
                    {
                       P4OUT = BIT0;
                       P4IFG &= ~BIT0;
                    }
           }

// Port 7 interrupt service routine
   #pragma vector=PORT7_VECTOR
   __interrupt void Port_7(void)
        {
                        if(P7IFG & BIT7)                    //If B11 is pressed
                        {
                           P7OUT = BIT7;
                           P7IFG &= ~BIT7;
                        }
                        if(P7IFG & BIT6)                    //If B12 is pressed
                        {
                           P7OUT = BIT6;
                           P7IFG &= ~BIT6;
                        }
                        if(P7IFG & BIT2)                    //If Right is pressed
                        {
                           P7OUT = BIT2;
                           P7IFG &= ~BIT2;
                        }
                        if(P7IFG & BIT3)                    //If Left is pressed
                        {
                           P7OUT = BIT3;
                           P7IFG &= ~BIT3;
                        }
                        if(P7IFG & BIT4)                    //If Up is pressed
                        {
                           P7OUT = BIT4;
                           P7IFG &= ~BIT4;
                        }
                        if(P7IFG & BIT5)                    //If Down is pressed
                        {
                           P7OUT = BIT5;
                           P7IFG &= ~BIT5;
                        }
               }
// Port 6 interrupt service routine
   #pragma vector=PORT6_VECTOR
   __interrupt void Port_6(void)
       {
                       if(P6IFG & BIT7)                     //If Joystick Right is pressed
                       {
                          P6OUT = BIT7;
                          P6IFG &= ~BIT7;
                       }
                       if(P6IFG & BIT6)                     //If Joystick Left is pressed
                       {
                          P6OUT = BIT6;
                          P6IFG &= ~BIT6;
                       }
                       if(P6IFG & BIT5)                     //If Joystick Up is pressed
                       {
                          P6OUT = BIT5;
                          P6IFG &= ~BIT5;
                       }
                       if(P6IFG & BIT3)                     //If Joystick Down is pressed
                       {
                          P6OUT = BIT4;
                          P6IFG &= ~BIT4;
                       }
              }
