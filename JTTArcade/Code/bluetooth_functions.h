/*
 * bluetooth_functions.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#ifndef BLUETOOTH_FUNCTIONS_H_
#define BLUETOOTH_FUNCTIONS_H_

void BT_Init_Port();
void BT_NewDiscovery_TurnOn();
void BT_NewDiscovery_TurnOff();
void BT_FactoryReset_TurnOn();
void BT_FactoryReset_TurnOff();
void BT_ConnectAddress_TurnOn();
void BT_ConnectAddress_TurnOff();
void BT_9600Baud_TurnOn();
void BT_9600Baud_TurnOff();
void BT_BRTSHigh();
void BT_BRTSLow();
int  BT_BCTSRead();


#endif /* BLUETOOTH_FUNCTIONS_H_ */
