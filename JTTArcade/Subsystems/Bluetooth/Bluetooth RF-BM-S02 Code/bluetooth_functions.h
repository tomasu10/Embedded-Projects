/*
 * bluetooth_functions.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#ifndef BLUETOOTH_FUNCTIONS_H_
#define BLUETOOTH_FUNCTIONS_H_

void BT_Init_Port();
void BT_ResetHigh();
void BT_ResetLow();
void BT_EnHigh();
void BT_EnLow();
int  BT_SleepRead();
int  BT_ConnectedRead();
void BT_BRTSHigh();
void BT_BRTSLow();
int  BT_BCTSRead();


#endif /* BLUETOOTH_FUNCTIONS_H_ */
