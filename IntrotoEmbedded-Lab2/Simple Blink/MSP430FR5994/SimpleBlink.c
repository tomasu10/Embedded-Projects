/*
 * SimpleBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */

#include<msp430fr5994.h>
int SimpleBlink(void){

    P1DIR = 0x03;   //Set Port 1 Inputs/Outputs
    P1OUT = 0x01;   //Set P1.0 on
    unsigned int i;
       while(1){
            P1OUT ^= 0x03;  //Toggle LEDs

             for(i=0;i<30000;i++);  //Delay
           }
}


