#include <msp430.h>
int BlinkButtonColorChange(void)
{

unsigned int i;

     // set up bit 6 and 0 of P1 as output
     P1DIR = 0x41; // 0100 0001
     P1OUT = 0x48; // intialize bit 0, and 6 of P1 to 1
     P1REN = 0x08;  // adds a pull up resistor on the switch (P1: 00001000)


     int prevINState = 0;   //Use to prevent processor from toggling LEDs mulitple times per button press

     while(1){
     if (P1IN & 0x08){      //Checks to see if button is pressed

         prevINState = 1;
         }
     else //if button is pressed
     {
         if (P1OUT == 0x48 & prevINState){      //Switch states of LEDs only once per button press
             P1OUT = 0x09;

             prevINState = 0;
         }

         else if (P1OUT == 0x09 & prevINState){ //Switch states of LEDs only once per button press
             P1OUT = 0x48;

             prevINState = 0;
 }
                 }
     for (i = 0; i < 1000; i++);                //Delay
             }
         }
