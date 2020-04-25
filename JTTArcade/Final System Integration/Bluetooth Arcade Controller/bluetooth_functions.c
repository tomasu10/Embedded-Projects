/*
 * BT.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#include "bluetooth_functions.h"
#include "hal_bluetooth.h"

void BT_Init_Port(){
    *bluetooth_control_dir |=  (BLUETOOTH_NEWDISCOVERY | BLUETOOTH_FACTORYRESET
                              | BLUETOOTH_CONNECTADDRESS | BLUETOOTH_9600BAUD);
//    *bluetooth_control_dir &=  ~BLUETOOTH_FACTORYRESET;

    *bluetooth_uart_dir |=  BLUETOOTH_BRTS;
    *bluetooth_uart_dir &= ~BLUETOOTH_BCTS;
}

void BT_NewDiscovery_TurnOn(){
    *bluetooth_control_port_out |= BLUETOOTH_NEWDISCOVERY;
}

void BT_NewDiscovery_TurnOff(){
    *bluetooth_control_port_out &= ~BLUETOOTH_NEWDISCOVERY;
}

void BT_FactoryReset_TurnOn(){
    *bluetooth_control_port_out |= BLUETOOTH_FACTORYRESET;
}

void BT_FactoryReset_TurnOff(){
    *bluetooth_control_port_out &= ~BLUETOOTH_FACTORYRESET;
}

void BT_ConnectAddress_TurnOn(){
    *bluetooth_control_port_out |= BLUETOOTH_CONNECTADDRESS;
}

void BT_ConnectAddress_TurnOff(){
    *bluetooth_control_port_out &= ~BLUETOOTH_CONNECTADDRESS;
}

void BT_9600Baud_TurnOn(){
    *bluetooth_control_port_out |= BLUETOOTH_9600BAUD;
}

void BT_9600Baud_TurnOff(){
    *bluetooth_control_port_out &= ~BLUETOOTH_9600BAUD;
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


