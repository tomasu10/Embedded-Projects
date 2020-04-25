/*
 * hal_bluetooth.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Tanner
 */

#ifndef HAL_BLUETOOTH_H_
#define HAL_BLUETOOTH_H_

#include "msp430fr5994.h"

#define BLUETOOTH_NEWDISCOVERY      BIT0    // P3.0 (5994 Pin 04) (RF-BM-S02 module: P2.2)
#define BLUETOOTH_FACTORYRESET      BIT1    // P3.1 (5994 Pin 05) (RF-BM-S02 module: P2.1)
#define BLUETOOTH_CONNECTADDRESS    BIT2    // P3.2 (5994 Pin 06) (RF-BM-S02 module: RES )
#define BLUETOOTH_9600BAUD          BIT3    // P3.3 (5994 Pin 07) (RF-BM-S02 module: P2.0)
#define BLUETOOTH_RX                BIT0    // P6.0 (5994 Pin 08) (RF-BM-S02 module: P0.2)
#define BLUETOOTH_TX                BIT1    // P6.1 (5994 Pin 09) (RF-BM-S02 module: P0.3)
#define BLUETOOTH_BCTS              BIT2    // P6.2 (5994 Pin 10) (RF-BM-S02 module: P0.4)
#define BLUETOOTH_BRTS              BIT3    // P6.3 (5994 Pin 11) (RF-BM-S02 module: P0.5)
#define BLUETOOTH_RESET             BIT7    // P1.2 (5994 Pin 12) (RF-BM-S02 module: P1.2)

volatile unsigned char * bluetooth_control_dir      =     &P3DIR;
volatile unsigned char * bluetooth_uart_dir         =     &P6DIR;

volatile unsigned char * bluetooth_control_port_out =     &P3OUT;
volatile unsigned char * bluetooth_uart_port_out    =     &P6OUT;

volatile unsigned char * bluetooth_control_port_in  =     &P3IN;
volatile unsigned char * bluetooth_uart_port_in     =     &P6IN;



#endif /* HAL_BLUETOOTH_H_ */
