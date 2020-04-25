/*
 * ButtonBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */


#include<msp430fr2311.h>
int ButtonBlink(void){
        P1DIR = 0x01;   //Set P1 Direction
        P1OUT = 0x02;   //Set P1.1 hi
        P1REN = 0x02;   //Set pullup resistor to P1.1
        P2DIR = 0x01;   //Set P2 Direction
        P2OUT = 0x00;   //Set P2.0 off

        while(1){
            if(P1IN & 0x02){    //Switch states of LEDs only button is pressed
                P1OUT = 0x02;
                P2OUT = 0x00;

            }
            else{
                P1OUT=0x03;     //Toggle LEDs
                P2OUT=0x01;
            }
        }
}

