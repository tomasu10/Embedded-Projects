/*
 * MultipleBlink.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */

#include<msp430fr5994.h>
 int MultipleBlink(void){
       P1DIR = 0x03;    //Set P1 Direction
       P1OUT = 0x01;    //Set P1.0 on
       unsigned int counter = 0;
       while(1){
           if((counter%500)==0){    //Check if counter is multiple of 500
           P1OUT ^= 0x01;           //Toggle LED
           }
           if((counter%1600)==0){   //Check if counter is multiple of 1600
               P1OUT^=0x02;         //Toggle LED

           }
           counter++;               //Increment counter
           }

 }
