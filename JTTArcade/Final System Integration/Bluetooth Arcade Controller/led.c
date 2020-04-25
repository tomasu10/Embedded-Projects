/*
 * led.c
 *
 *  Created on: Dec 14, 2017
 *      Author: Tanner
 */

#include "msp430fr5994.h"
#include "led.h"
#include "ledspi.h"
#include "timer.h"

#define NUM_OF_BUTTON_LEDS             14
#define NUM_OF_RING_LEDS               52
#define NUM_OF_UNDERGLOW_LEDS           4

#define SOLID_MODE                      0
#define CHASE_MODE                      1
#define SHIFT_MODE                      2

static int i = 0;
int chase_index = 0;
int shift_index = 0;

int chase_length = 15;

int button_pixels[NUM_OF_BUTTON_LEDS][3]         = {};
int ring_pixels[NUM_OF_RING_LEDS][3]             = {};
int underglow_pixels[NUM_OF_UNDERGLOW_LEDS][3]   = {};

int current_mode = SOLID_MODE;

void LED_SetOff(int* pixel_pointer, int num_of_leds);
void LED_SetRed(int* pixel_pointer, int num_of_leds);
void LED_SetBlue(int* pixel_pointer, int num_of_leds);
void LED_SetGreen(int* pixel_pointer, int num_of_leds);
void LED_SetPurple(int* pixel_pointer, int num_of_leds);
void LED_SetYellow(int* pixel_pointer, int num_of_leds);
void LED_SetBlueGreen(int* pixel_pointer, int num_of_leds);
void LED_SetChristmas(int* pixel_pointer, int num_of_leds);
void LED_SetRainbow(int* pixel_pointer, int num_of_leds);
void LED_SendStartMessage();
void LED_SendPixelMessage(int* pixel_pointer, int brightness);
void LED_SendEndMessage();

void LED_SetMode(int mode);
void LED_UpdateSolidMode();
void LED_UpdateChaseMode();
void LED_UpdateShiftMode();

void LED_Init(){
    LEDSPI_Init();
    LED_SetOffMode();

    TimerA_Init(ACLK, UP, DIV1, 5000);
    TimerA_EnableInterrupt0();

    LED_SetMode(SHIFT_MODE);
}

void LED_SetOffMode(){
    LED_SetOff(&button_pixels[0][0], NUM_OF_BUTTON_LEDS);
    LED_SetOff(&ring_pixels[0][0], NUM_OF_RING_LEDS);
    LED_SetOff(&underglow_pixels[0][0], NUM_OF_UNDERGLOW_LEDS);

    LED_SetMode(SOLID_MODE);
}

void LED_SetChristmasMode(){
    LED_SetChristmas(&button_pixels[0][0], NUM_OF_BUTTON_LEDS);
    LED_SetChristmas(&ring_pixels[0][0], NUM_OF_RING_LEDS);
    LED_SetChristmas(&underglow_pixels[0][0], NUM_OF_UNDERGLOW_LEDS);

    LED_SetMode(SHIFT_MODE);
}

void LED_SetRainbowMode(){
    LED_SetRainbow(&button_pixels[0][0], NUM_OF_BUTTON_LEDS);
    LED_SetRainbow(&ring_pixels[0][0], NUM_OF_RING_LEDS);
    LED_SetRainbow(&underglow_pixels[0][0], NUM_OF_UNDERGLOW_LEDS);

    LED_SetMode(SHIFT_MODE);
}

void LED_SetBlueChaseMode(){
    LED_SetBlue(&button_pixels[0][0], NUM_OF_BUTTON_LEDS);
    LED_SetBlue(&ring_pixels[0][0], NUM_OF_RING_LEDS);
    LED_SetBlue(&underglow_pixels[0][0], NUM_OF_UNDERGLOW_LEDS);

    LED_SetMode(CHASE_MODE);
}

void LED_SetRedSolidMode(){
    LED_SetRed(&button_pixels[0][0], NUM_OF_BUTTON_LEDS);
    LED_SetRed(&ring_pixels[0][0], NUM_OF_RING_LEDS);
    LED_SetRed(&underglow_pixels[0][0], NUM_OF_UNDERGLOW_LEDS);

    LED_SetMode(SOLID_MODE);
}

void LED_SetOff(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
    }
}

void LED_SetRed(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
    }
}

void LED_SetBlue(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
    }
}

void LED_SetGreen(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
    }
}

void LED_SetPurple(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
    }
}

void LED_SetYellow(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
    }
}

void LED_SetBlueGreen(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i++){
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0xFF;
    }
}

void LED_SetChristmas(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i = i+2){
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
    }
}



void LED_SetRainbow(int* pixel_pointer, int num_of_leds){
    for(i = 0; i < num_of_leds; i = i + 6){
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;

        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;

        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;

        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0xFF;

        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;

        *pixel_pointer++ = 0xFF;
        *pixel_pointer++ = 0x00;
        *pixel_pointer++ = 0xFF;

    }
}



void LED_SendStartMessage(){
    for(i = 0; i < 4; i++){
        LEDSPI_Transmit(0x00);
    }
}

void LED_SendPixelMessage(int* pixel_pointer, int brightness){
    LEDSPI_Transmit(brightness);
    LEDSPI_Transmit(*pixel_pointer++);
    LEDSPI_Transmit(*pixel_pointer++);
    LEDSPI_Transmit(*pixel_pointer++);
}

void LED_SendEndMessage(){
    for(i = 0; i < 4; i++){
        LEDSPI_Transmit(0xFF);
    }
}

void LED_SetMode(int mode){
    switch(mode){
    case CHASE_MODE:
        TimerA_SetCompareVal0(200);
        break;

    case SHIFT_MODE:
        TimerA_SetCompareVal0(5000);
        break;

    default:
        TimerA_SetCompareVal0(1000);
        break;
    }

    current_mode = mode;
}

void LED_UpdateSolidMode(){
    LED_SendStartMessage();

    for(i = 0; i < NUM_OF_BUTTON_LEDS; i++){
        LED_SendPixelMessage(&button_pixels[i][0], 0xFF);
    }
    for(i = 0; i < NUM_OF_RING_LEDS; i++){
        LED_SendPixelMessage(&ring_pixels[i][0], 0xFF);
    }
    for(i = 0; i < NUM_OF_UNDERGLOW_LEDS; i++){
        LED_SendPixelMessage(&underglow_pixels[i][0], 0xFF);
    }

    LED_SendEndMessage();
}

void LED_UpdateChaseMode(){
    int blank_pixel[1][3] = {0, 0, 0};

    chase_index ++;

    if(chase_index >= NUM_OF_RING_LEDS){
        chase_index = 0;
    }

    LED_SendStartMessage();
    for(i = 0; i < NUM_OF_BUTTON_LEDS; i++){
        LED_SendPixelMessage(&button_pixels[i][0], 0xFF);
    }

    if((chase_index + chase_length) < NUM_OF_RING_LEDS){
        for(i = 0; i < chase_index; i++){
            LED_SendPixelMessage(&blank_pixel[0][0], 0xFF);
        }
        for(i = chase_index; i < chase_index + chase_length; i++){
            LED_SendPixelMessage(&ring_pixels[i][0], 0xFF);
        }
        for(i = chase_index + chase_length; i < NUM_OF_RING_LEDS; i++){
            LED_SendPixelMessage(&blank_pixel[0][0], 0xFF);
        }
    }
    else{
        for(i = 0; i < (chase_length - (NUM_OF_RING_LEDS - chase_index)); i++){
            LED_SendPixelMessage(&ring_pixels[i][0], 0xFF);
        }
        for(i = (chase_length - (NUM_OF_RING_LEDS - chase_index)); i < chase_index; i++){
            LED_SendPixelMessage(&blank_pixel[0][0], 0xFF);
        }
        for(i = chase_index; i < NUM_OF_RING_LEDS; i++){
            LED_SendPixelMessage(&ring_pixels[i][0], 0xFF);
        }
    }

    for(i = 0; i < NUM_OF_UNDERGLOW_LEDS; i++){
        LED_SendPixelMessage(&underglow_pixels[i][0], 0xFF);
    }

    LED_SendEndMessage();

}

void LED_UpdateShiftMode(){

    LED_SendStartMessage();

    shift_index ++;

    if(shift_index >= NUM_OF_RING_LEDS){
        shift_index = 0;
    }

    for(i = 0; i < NUM_OF_BUTTON_LEDS; i++){
        LED_SendPixelMessage(&button_pixels[i][0], 0xE4);
    }

    for(i = shift_index; i < NUM_OF_RING_LEDS; i++){
        LED_SendPixelMessage(&ring_pixels[i][0], 0xE4);
    }

    for(i = 0; i < shift_index; i++){
        LED_SendPixelMessage(&ring_pixels[i][0], 0xE4);
    }

    for(i = 0; i < NUM_OF_UNDERGLOW_LEDS; i++){
        LED_SendPixelMessage(&underglow_pixels[i][0], 0xE4);
    }
    LED_SendEndMessage();
}



#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void){
    switch(current_mode){
        case SOLID_MODE:
            LED_UpdateSolidMode();
            break;

        case CHASE_MODE:
            LED_UpdateChaseMode();
            break;

        case SHIFT_MODE:
            LED_UpdateShiftMode();
            break;

        default:
            LED_UpdateSolidMode();
            break;
    }
}

