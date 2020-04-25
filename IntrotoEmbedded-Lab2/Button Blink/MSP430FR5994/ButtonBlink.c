/*
 * ButtonBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */

#include<msp430fr5994.h>
int ButtonBlink(void){
        P1DIR = 0x03;   //Set P1 Direction
        P1OUT = 0x00;   //Set P1.0 and P1.1 off
        P5DIR = 0x40;   //Set P5 Direction
        P5OUT = 0x40;   //Set pullup resistor to P5.6
        P5REN = 0x40;   //Set pullup resistor to P5.6

        while(1){
            if(P5IN & 0x40){    //Switch states of LEDs only button is pressed
                P1OUT = 0x00;

            }
            else{
                P1OUT=0x03;     //Toggle LEDs
            }
        }
}


