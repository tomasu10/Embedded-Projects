#include<msp430fr5994.h>
#include "bluetooth.h"
#include "mode.h"

#define BUTTON1              1
#define BUTTON2              2
#define BUTTON3              3
#define BUTTON4              4
#define BUTTON5              5
#define BUTTON6              6
#define BUTTON7              7
#define BUTTON8              8
#define BUTTON9              9
#define BUTTON10            10
#define BUTTON11            11
#define BUTTON12            12
#define DPAD_RIGHT          13
#define DPAD_LEFT           14
#define DPAD_UP             15
#define DPAD_DOWN           16
#define JOYSTICK_RIGHT      17
#define JOYSTICK_LEFT       18
#define JOYSTICK_UP         19
#define JOYSTICK_DOWN       20

int i,j = 0;

void BUTTONS_SendData(int button){

    switch(button){
        case BUTTON1:
            BLUETOOTH_SendString("a");
            break;
        case BUTTON2:
            BLUETOOTH_SendString("b");
            break;
        case BUTTON3:
            BLUETOOTH_SendString("c");
            break;
        case BUTTON4:
            BLUETOOTH_SendString(" ");
            break;
        case BUTTON5:
            BLUETOOTH_SendString("e");
            break;
        case BUTTON6:
            BLUETOOTH_SendString("f");
            break;
        case BUTTON7:
            BLUETOOTH_SendString("g");
            break;
        case BUTTON8:
            BLUETOOTH_SendString("h");
            break;
        case BUTTON9:
            BLUETOOTH_SendString("i");
            break;
        case BUTTON10:
            BLUETOOTH_SendString("j");
            break;
        case BUTTON11:
            MODE_Cycle();
            break;
        case BUTTON12:

            break;
        case DPAD_RIGHT:
            BLUETOOTH_SendString("k");
            break;
        case DPAD_LEFT:
            BLUETOOTH_SendString("l");
            break;
        case DPAD_UP:
            BLUETOOTH_SendString("m");
            break;
        case DPAD_DOWN:
            BLUETOOTH_SendString("n");
            break;
        case JOYSTICK_RIGHT:
            BLUETOOTH_SendString("o");
            break;
        case JOYSTICK_LEFT:
            BLUETOOTH_SendString("p");
            break;
        case JOYSTICK_UP:
            BLUETOOTH_SendString("q");
            break;
        case JOYSTICK_DOWN:
            BLUETOOTH_SendString("r");
            break;

        default:

            break;
    }

}

void BUTTONS_Send(char* c){

}

void BUTTONS_Init(){
    //B1 and B2
    P1OUT &= 0x00;                                      // Shut Port 1 Down
    P1DIR &= 0x00;                                      // Port 1 direction set
    P1OUT  = ~(BIT6 + BIT7);                            // Select pull-up mode for Pin 1
    P1REN |= BIT6 + BIT7;                               // Enable internal pull-up/down resistors

    //B3 and B4
    P3OUT &= 0x00;                                      // Shut Port 3 Down
    P3DIR &= 0x00;                                      // Port 3 direction set
    P3OUT  = ~(BIT6 + BIT7);                            // Select pull-up mode for Pin 3
    P3REN |= BIT6 + BIT7;                               // Enable internal pull-up/down resistors

    //B5 and B6
    P2OUT &= 0x00;                                      // Shut Port 2 Down
    P2DIR &= 0x00;                                      // Port 2 direction set
    P2OUT  = ~(BIT5 + BIT6);                             // Select pull-up mode for Pin 2
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

void BUTTONS_InterruptInit(){

    //B1 and B2
    P1IE  |= BIT6 + BIT7;                    // P1 interrupt enabled
    P1IES &= ~BIT6 + ~BIT7;                    // P1 Hi/lo edge
    P1IFG &= ~BIT6 + ~BIT7;                  // P1 IFG cleared

    //B3 and B4
    P3IE  |= BIT6 + BIT7;                    // P3 interrupt enabled
    P3IES &= ~BIT6 + ~BIT7;                    // P3 Hi/lo edge
    P3IFG &= ~BIT6 + ~BIT7;                  // P3 IFG cleared

    //B5 and B6
    P2IE  |= BIT6 + BIT5;                    // P2 interrupt enabled
    P2IES &= ~BIT6 + ~BIT5;                    // P2 Hi/lo edge
    P2IFG &= ~BIT6 + ~BIT5;                  // P2 IFG cleared

    //B7 and B8 and B9 and B10
    P4IE  |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;                    // P4 interrupt enabled
    P4IES &= ~BIT0 + ~BIT1 + ~BIT2 + ~BIT3 + ~BIT4;                    // P4 Hi/lo edge
    P4IFG &= ~BIT0 + ~BIT1 + ~BIT2 + ~BIT3 + ~BIT4;               // P4 IFG cleared

    //B5 and B6 and DPad
    P7IE  |= BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;             // P7 interrupt enabled
    P7IES &= ~BIT2 + ~BIT3 + ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;             // P7 Hi/lo edge
    P7IFG &= ~BIT2 + ~BIT3 + ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;       // P7 IFG cleared

    //Joystick
    P6IE  |= BIT4 + BIT5 + BIT6 + BIT7;                    // P6 interrupt enabled
    P6IES &= ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;                    // P6 Hi/lo edge
    P6IFG &= ~BIT4 + ~BIT5 + ~BIT6 + ~BIT7;                // P6 IFG cleared

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG & BIT6)                                  //If B1 is pressed
    {
       BUTTONS_SendData(BUTTON1);
       P1IFG &= ~BIT6;
    }

    if(P1IFG & BIT7)                                  //If B2 is pressed
    {
       BUTTONS_SendData(BUTTON2);
       P1IFG &= ~BIT7;
    }
}

// Port 3 interrupt service routine
#pragma vector=PORT3_VECTOR
__interrupt void Port_3(void)
{
        if(P3IFG & BIT7)                                  //If B3 is pressed
        {
           BUTTONS_SendData(BUTTON3);
           P3IFG &= ~BIT7;
        }

        if(P3IFG & BIT6)                                  //If B4 is pressed
        {
           BUTTONS_SendData(BUTTON4);
           P3IFG &= ~BIT6;
        }
    }

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
        if(P2IFG & BIT6)                              //If B5 is pressed
        {
           BUTTONS_SendData(BUTTON5);
           P2IFG &= ~BIT6;
        }

        if(P2IFG & BIT5)                              //If B6 is pressed
        {
           BUTTONS_SendData(BUTTON6);
           P2IFG &= ~BIT5;
        }
}

// Port 4 interrupt service routine
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
        if(P4IFG & BIT3)                        //If B7 is pressed
        {
           BUTTONS_SendData(BUTTON7);
           P4IFG &= ~BIT3;
        }

        if(P4IFG & BIT2)                        //If B8 is pressed
        {
           BUTTONS_SendData(BUTTON8);
           P4IFG &= ~BIT2;
        }

       if(P4IFG & BIT1)                        //If B9 is pressed
        {
           BUTTONS_SendData(BUTTON9);
           P4IFG &= ~BIT1;
        }
        if(P4IFG & BIT0)                        //If B10 is pressed
        {
           BUTTONS_SendData(BUTTON10);
           P4IFG &= ~BIT0;
        }
}

// Port 7 interrupt service routine
#pragma vector=PORT7_VECTOR
__interrupt void Port_7(void)
    {
        if(P7IFG & BIT7)                    //If B11 is pressed
        {
           BUTTONS_SendData(BUTTON11);
           P7IFG &= ~BIT7;
        }
        if(P7IFG & BIT6)                    //If B12 is pressed
        {
           BUTTONS_SendData(BUTTON12);
           P7IFG &= ~BIT6;
        }
        if(P7IFG & BIT2)                    //If Right is pressed
        {
           BUTTONS_SendData(DPAD_RIGHT);
           P7IFG &= ~BIT2;
        }
        if(P7IFG & BIT3)                    //If Left is pressed
        {
           BUTTONS_SendData(DPAD_LEFT);
           P7IFG &= ~BIT3;
        }
        if(P7IFG & BIT4)                    //If Up is pressed
        {
           BUTTONS_SendData(DPAD_UP);
           P7IFG &= ~BIT4;
        }
        if(P7IFG & BIT5)                    //If Down is pressed
        {
           BUTTONS_SendData(DPAD_DOWN);
           P7IFG &= ~BIT5;
        }
}
// Port 6 interrupt service routine
#pragma vector=PORT6_VECTOR
__interrupt void Port_6(void)
{
       if(P6IFG & BIT7)                     //If Joystick Right is pressed
       {
          BUTTONS_SendData(JOYSTICK_RIGHT);
          P6IFG &= ~BIT7;
       }
       if(P6IFG & BIT6)                     //If Joystick Left is pressed
       {
          BUTTONS_SendData(JOYSTICK_LEFT);
          P6IFG &= ~BIT6;
       }
       if(P6IFG & BIT5)                     //If Joystick Up is pressed
       {
          BUTTONS_SendData(JOYSTICK_UP);
          P6IFG &= ~BIT5;
       }
       if(P6IFG & BIT4)                     //If Joystick Down is pressed
       {
          BUTTONS_SendData(JOYSTICK_DOWN);
          P6IFG &= ~BIT4;
       }
}
