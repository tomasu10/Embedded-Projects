/*
 * bluetooth.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stdint.h>

void BLUETOOTH_Init();
void BLUETOOTH_SendString(char* s);
void BLUETOOTH_SendChar(char c);
void BLUETOOTH_SendByte(int byte);

#endif /* BLUETOOTH_H_ */
