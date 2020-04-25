/*
 * ButtonBlink.c
 *
 *  Created on: Sep 14, 2017
 *      Author: tomas
 */
#include<msp430g2553.h>
int ButtonBlink(void){
        P1DIR = 0x41;   //Set P1 Direction
        P1OUT = 0x08;   //Set P1.3 hi
        P1REN = 0x08;   //Set pullup resistor to P1.3

        while(1){
            if(P1IN & 0x08){    //Switch states of LEDs only button is pressed
                P1OUT = 0x08;

            }
            else{
                P1OUT=0x49;     //Toggle LEDs
            }
        }
}



