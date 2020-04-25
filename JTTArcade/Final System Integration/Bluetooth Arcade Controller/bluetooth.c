/*
 * bluetooth.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Tanner
 */

#include "bluetooth.h"
#include "bluetooth_functions.h"
#include "bluetooth_uart.h"



void BLUETOOTH_Init(){

    BT_Init_Port();
    BT_NewDiscovery_TurnOff();
    BT_FactoryReset_TurnOff();
    BT_ConnectAddress_TurnOff();
    BT_9600Baud_TurnOff();

    BLUETOOTH_UART_Init(115200);
}

void BLUETOOTH_SendString(char* s){
    while(*s){
        BLUETOOTH_UART_TransmitChar(*s++);
    }
}

void BLUETOOTH_SendChar(char c){
    BLUETOOTH_UART_TransmitChar(c);
}

void BLUETOOTH_SendByte(int byte){
    BLUETOOTH_UART_TransmitByte(byte);
}
