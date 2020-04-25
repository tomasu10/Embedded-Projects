#include <msp430fr5994.h>
#include "buttons.h"
#include "led.h"
#include "ledspi.h"
#include "lcd.h"
#include "lcdbacklight.h"
#include "touchpad.h"
#include "bluetooth.h"
#include "bluetooth_functions.h"

/**
 * main.c
 */
void main(){
  WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(GIE);

    /*** BUTTON Test ***/
    BLUETOOTH_Init();
    BUTTONS_Init();
    BUTTONS_InterruptInit();

    /*** LED Test ***/
    LED_Init();
//    //int colors[8] = {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF};
//    //int colors[28] = {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};

//    __bis_SR_register(GIE);
//
//    int colors[4] = {0xFF, 0xFF, 0x00, 0x00};
//    int colors[8] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF};
//    LED_SendData(colors, 4);

    /*** LCD Test ***/
    LCD_Init();
    LCDBACKLIGHT_Init(0x00, 0x00, 0x00);

    /*** TouchPad Test ***/
//    BLUETOOTH_Init();
//    TOUCHPAD_Init();


    /*** Bluetooth Test ***/
//    __bis_SR_register(GIE);
//

//    __bis_SR_register(GIE);                                 // Enter LPM0 w/ interrupt=
//    __delay_cycles(500000);
//    BLUETOOTH_Init();
//    BLUETOOTH_SendPacket("Hello");

//      BLUETOOTH_Init();
//    BT_FactoryReset_TurnOn();
//    __delay_cycles(5000000);
//    BT_FactoryReset_TurnOff();
//    __delay_cycles(5000000);
//    BT_FactoryReset_TurnOn();
//    __delay_cycles(5000000);
//    BT_FactoryReset_TurnOff();
//    __delay_cycles(5000000);
//    BT_FactoryReset_TurnOn();

//
//    __bis_SR_register(GIE);                                 // Enter LPM0 w/ interrupt=

    /*** FLAPPY BIRD TEST ***/
//    BLUETOOTH_Init();
//    BUTTONS_Init();
//    BUTTONS_InterruptInit();


    __bis_SR_register(GIE);                                 // Enter LPM0 w/ interrupt=

    while(1);
}
