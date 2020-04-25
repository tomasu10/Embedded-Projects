/*
 * SimpleBlink.c
 *
 *  Created on: Sep 14, 2017
 *      Author: tomas
 */

#include <SimpleBlink.h>
#include <msp430g2553.h>
int SimpleBlink(void){
    P1DIR = 0x41;       //Set Input/outputs
    P1OUT = 0x01;       // Set P1.0 on
    unsigned int i = 0;
    while(1){
        P1OUT ^= 0x41;    //Toggle LED

        for(i=0;i<30000;i++);   //Delay
    }
    return 0;
}


