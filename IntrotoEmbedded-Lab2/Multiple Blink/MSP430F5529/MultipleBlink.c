/*
 * MultipleBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */


#include<msp430f5529.h>

int MultipleBlink(void){
        P1DIR = 0x01;   //Set P1 Direction
        P1OUT = 0x01;   //Set P1.0 on
        P4DIR = 0x80;   //Set P4 Direction
        P4OUT= 0x00;    //Set P4.7 off
       unsigned int counter = 0;
       while(1){
           if((counter%500)==0){    //Check if counter is multiple of 500
           P1OUT ^= 0x01;           //Toggle LED
           }
           if((counter%1600)==0){   //Check if counter is multiple of 1600
               P4OUT^=0x80;         //Toggle LED

           }
           counter++;               //Increment Counter
           }


}

