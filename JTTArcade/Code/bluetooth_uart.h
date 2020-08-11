/*
 * bluetooth_uart.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Tanner
 */

#ifndef BLUETOOTH_UART_H_
#define BLUETOOTH_UART_H_

void BLUETOOTH_UART_Init();
void BLUETOOTH_UART_TransmitChar(char s);
void BLUETOOTH_UART_TransmitByte(int byte);


#endif /* BLUETOOTH_UART_H_ */
