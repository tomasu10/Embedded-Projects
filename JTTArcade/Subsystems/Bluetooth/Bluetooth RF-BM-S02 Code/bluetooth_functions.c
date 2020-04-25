/*
 * BT.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#include "bluetooth_functions.h"
#include "hal_bluetooth.h"

void BT_Init_Port(){
    *bluetooth_control_dir |=  (BLUETOOTH_RESET | BLUETOOTH_EN);
    *bluetooth_control_dir &= ~(BLUETOOTH_SLEEP | BLUETOOTH_CONNECTED);

    *bluetooth_uart_dir |=  BLUETOOTH_BRTS;
    *bluetooth_uart_dir &= ~BLUETOOTH_BCTS;
}

void BT_ResetHigh(){
    *bluetooth_control_port_out |= BLUETOOTH_RESET;
}

void BT_ResetLow(){
    *bluetooth_control_port_out &= ~BLUETOOTH_RESET;
}

void BT_EnHigh(){
    *bluetooth_control_port_out |= BLUETOOTH_EN;
}

void BT_EnLow(){
    *bluetooth_control_port_out &= ~BLUETOOTH_EN;
}

int BT_SleepRead(){
    return (*bluetooth_control_port_out & BLUETOOTH_SLEEP);
}

int BT_ConnectedRead(){
    return (*bluetooth_control_port_out & BLUETOOTH_CONNECTED);
}

void BT_BRTSHigh(){
    *bluetooth_uart_port_out |= BLUETOOTH_BRTS;
}

void BT_BRTSLow(){
    *bluetooth_uart_port_out &= ~BLUETOOTH_BRTS;
}

int BT_BCTSRead(){
    return (*bluetooth_uart_port_out & BLUETOOTH_BCTS);
}


