/*
 * lcdbacklight.c
 *
 *  Created on: Dec 15, 2017
 *      Author: Tanner
 */

/*
 * pwm_rgb.c
 *
 *  Created on: Oct 13, 2017
 *      Author: Tanner
 */


#include <msp430fr5994.h>
#include "lcdbacklight.h"

int count = 0;
int count2 = 0;

void LCDBACKLIGHT_Init(int red, int green, int blue){

    /* Initialize Timer B0 to run at 1kHz in up mode */
    TB0CTL = TBSSEL_1 + MC_1;
    TB0CCR0 = 256;

    /* Configure P2.2 to output Red PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TB0CCR2 = red;
    P2DIR  |= BIT2;
    P2SEL0 |= BIT2;
    P2SEL1 &= ~BIT2;
    TB0CCTL2 |= OUTMOD_7;


    /* Configure P3.4 to output Green PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TB0CCR3 = green;
    P3DIR  |= BIT4;
    P3SEL0 |= BIT4;
    P3SEL1 &= ~BIT4;
    TB0CCTL3 |= OUTMOD_7;

    /* Configure P3.5 to output Blue PWM
     * Used an array of values to linearize
     * the brightness to human eyes.
     */
    TB0CCR4 = blue;
    P3DIR  |= BIT5;
    P3SEL0 |= BIT5;
    P3SEL1 &= ~BIT5;
    TB0CCTL4 |= OUTMOD_7;

}

/* Set Red PWM value */
void LCDBACKLIGHT_SetRed(int red){
    TB0CCR2 = red;
}

/* Set Green PWM value */
void LCDBACKLIGHT_SetGreen(int green){
    TB0CCR3 = green;
}

/* Set Blue PWM value */
void LCDBACKLIGHT_(int blue){
    TB0CCR4 = blue;
}


