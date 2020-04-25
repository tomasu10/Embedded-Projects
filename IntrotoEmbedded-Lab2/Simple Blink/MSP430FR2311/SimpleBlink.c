/*
 * SimpleBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */

#include <msp430fr2311.h>
int SimpleBlink(void){
    P1DIR = 0x01;   //Set Port1 Input/Outputs
    P1OUT = 0x01;   //Set P1.0 on
    P2DIR = 0x01;   //Set Port2 Input/Outputs
    P2OUT= 0x00;    //Set P2.0 off
    unsigned int i = 0;
    while(1){
        P1OUT ^= 0x01;  //Toggle LEDs
        P2OUT ^= 0x01;

        for(i=0;i<30000;i++); //Delay
    }

}



