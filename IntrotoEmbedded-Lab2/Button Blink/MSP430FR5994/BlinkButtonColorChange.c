/*
 * BlinkButtonColorChange.c
 *
 *  Created on: Sep 19, 2017
 *      Author: tomas
 */

#include <msp430fr5994.h>
int BlinkButtonColorChange(void)
{

    unsigned int i;

     // set up bit 6 and 0 of P1 as output
            P1DIR = 0x03;
            P1OUT = 0x02;
            P5DIR = 0x40;
            P5OUT = 0x40;
            P5REN = 0x40;

     int prevINState = 0;

     while(1){
     if (P5IN & 0x40){

         prevINState = 1;
         }
     else //if button is pressed
     {
         if (P1OUT == 0x02 & prevINState){
             P1OUT = 0x01;

             prevINState = 0;
         }

         else if (P1OUT == 0x01 & prevINState){
             P1OUT = 0x02;

             prevINState = 0;
 }
                 }
     for (i = 0; i < 1000; i++);
             }
         }


