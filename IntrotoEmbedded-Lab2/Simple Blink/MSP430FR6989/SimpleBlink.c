/*
 * SimpleBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */


#include <msp430fr6989.h>
int SimpleBlink(void){
    P1DIR = 0x01;   //Set Port1 Input/Outputs
    P1OUT = 0x01;   //Set P1.0 on
    P9DIR = 0x80;   //Set Port9 Input/Outputs
    P9OUT= 0x00;    //Set P9.7 off
    unsigned int i = 0;
    while(1){
        P1OUT ^= 0x01;  //Toggle LEDs
        P9OUT ^= 0x80;

        for(i=0;i<30000;i++); //Delay
    }

}


