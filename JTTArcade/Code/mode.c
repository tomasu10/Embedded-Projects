/*
 * mode.c
 *
 *  Created on: Dec 19, 2017
 *      Author: Tanner
 */

#define NUM_OF_MODES        5

int mode = 0;

#include "mode.h"
#include "led.h"
#include "lcd.h"
#include "lcdbacklight.h"

void MODE_SetOff();
void MODE_SetChristmas();
void MODE_SetRainbow();
void MODE_SetRedSolid();
void MODE_SetBlueChase();

void MODE_Cycle(){
    mode++;

    if(mode >= NUM_OF_MODES){
        mode = 0;
    }

    switch(mode){
    case 0:
        MODE_SetOff();
        break;
    case 1:
        MODE_SetChristmas();
        break;
    case 2:
        MODE_SetRainbow();
        break;
    case 3:
        MODE_SetRedSolid();
        break;
    case 4:
        MODE_SetBlueChase();
        break;

    default:
        MODE_SetOff();
        break;
    }
}

void MODE_SetOff(){
    LCD_Display("Off", 1, 30);
    LCDBACKLIGHT_Init(0x00, 0x00, 0x00);
    LED_SetOffMode();
}

void MODE_SetChristmas(){
    LCD_Display("Christmas Mode", 1, 30);
    LCDBACKLIGHT_Init(0x00, 0xFF, 0x00);
    LED_SetChristmasMode();

}

void MODE_SetRainbow(){
    LCD_Display("Rainbow Mode", 1, 30);
    LCDBACKLIGHT_Init(0xFF, 0x00, 0xFF);
    LED_SetRainbowMode();
}

void MODE_SetRedSolid(){
    LCD_Display("Solid Red Mode", 1, 30);
    LCDBACKLIGHT_Init(0xFF, 0x00, 0x00);
    LED_SetRedSolidMode();

}

void MODE_SetBlueChase(){
    LCD_Display("Blue Chase Mode", 1, 30);
    LCDBACKLIGHT_Init(0x00, 0x00, 0xFF);
    LED_SetBlueChaseMode();
}



