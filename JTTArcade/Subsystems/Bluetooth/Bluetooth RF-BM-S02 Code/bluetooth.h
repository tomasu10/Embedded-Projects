/*
 * bluetooth.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stdint.h>

void BLE_Init();
void BLE_Reset();
void BLE_Receiver(char c);
void BLE_SoftReset(void);
void BLE_Send(uint8_t * msg);
void BLE_GetMAC(void);
void BLE_SetInvertal(uint16_t ms);
void BLE_CorrectBaud();
void BLE_SetName(char* s);


#endif /* BLUETOOTH_H_ */
