/*
 * bluetooth.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Tanner
 */

#include "bluetooth.h"
#include "bluetooth_functions.h"
#include "bluetooth_uart.h"
#include "timer.h"

// Responses
// "TTM:OK\r\n\0" when connected or after TTM command sent
// "TTM:ERP\r\n\0" after a command if there is an error
// "TTM:DISCONNECT\r\n\0" when app disconnects
// "TTM:DISCONNECT FOR a TIMEOUT\r\n\0" if disconnection is abnormal
// "TTM:MACxxxxxxxxxx\r\n\0" response to TTM:MAC-?
#define BLE_TTM_OK 0
#define BLE_TTM_ERP 1
#define BLE_TTM_DISCONNECT 2
#define BLE_TTM_DISCONNECT_FOR_TIMEOUT 3
#define BLE_TTM_MAC_RECEIVED 4

// Commands
// "TTM:CIT-Xms" to set interval to X, where X = 20 (default) ,50,100,200,300,400,500,1000,1500, or 2000 ms (response is either TTM: TIMEOUT or TTM: OK)
// "TTM:REN-NAME" to set name where NAME is any 16 byte string (response is OK or ERP)
// "TTM:BPS-BAUD" where BAUD is 4800, 9600 (default), 19200, 38400, 57600, 115200 (response is TTM:BPS SET AFTER 2S...\r\n\0 or ERP)
// "TTM:MAC-?" get the MAC address
// "TTM:RST-SYSTEMRESET" soft reset
// "TTM:ADP-X" set broadcast cycle T = X * 100ms, where X is 2 (default), 5, 10, 15, 20, 25, 30, 40, or 50 (res OK or ERP)
// "TTM:ADD-DATA" add customized DATA to broadcast, DATA can be up to 16 bytes, setting to 0000000000000000 disabled (res OK or ERP)
// "TTM:PID-DATA" set product ID to DATA where DATA is two bytes, default is 0x0000
// "TTM:TPL-X" set transmission power setting to X where X is "+4", 0 (default), 6, or "-23"
// "TTM:CDL-Xms" set delay between when BCTS goes low and when the module starts transmitting to the processor, where X = 0(default),2,5,10,20,or 25

// default password is 000000
// default Baud is 9600 WRONG - experimental actual baud rate is 115200
// default connection interval is 20ms
// max transmission / interval is 80 bytes

struct {
    char mac[12];
    uint8_t connected;
    uint8_t initialized;
    void (*ConnectedCallback)(uint8_t);
    void (*TTM_OK_Callback)(void);
} ble;

void BLE_Reset();
void BLE_CorrectBaud();
void BLE_SetName(char* s);
void BLE_ProcessTTM(uint8_t TTM_code);


void BLE_Init(){

    BT_Init_Port();

    BT_ResetLow();                  // Hold bluetooth in Reset initially
    BT_EnHigh();                    // Set Enable high to set module into full sleep mode
    BT_BRTSHigh();                  // Set BRTS High Initially because nothing is being transmitted

    DelayMs(100);                   // Delay 100ms

    BT_ResetHigh();                  // Turn off bluetooth Reset to start setting up module

    BLUETOOTH_UART_Init(9600);       // Initialize bluetooth UART to 9600 baud
    ble.initialized = 0xA5;
    ble.ConnectedCallback = 0;
    ble.TTM_OK_Callback = 0;

    BT_EnLow();                     // Set enable to low to start bluetooth connection

    DelayMs(500);                   // Delay 500 ms

    BLE_CorrectBaud();              // Tell the bluetooth module to transmit in 115.2k baud

    DelayMs(100);

//    BLE_GetMAC();

//   DelayMs(100);

    BLE_SetName("JTT Arcade");

//    while(1){
//        DelayMs(1000);
//        BLE_Send("TTM:ADD-Hello");
//    }

}

void BLE_Reset(){
    BT_ResetLow();
    DelayMs(1000);
    BT_ResetHigh();
}

#define BLE_RX_IDLE 0
#define BLE_RX_T 1
#define BLE_RX_TT 2
#define BLE_RX_TTM 3
#define BLE_RX_MSG 4

#define BLE_MAX_TTM_LENGTH 32

void BLE_Receiver(char c) {
    static char msg[BLE_MAX_TTM_LENGTH];
    static uint8_t msg_i = 0;
    static uint8_t rx_state = BLE_RX_IDLE;
    uint8_t i;
    // if pass through mode then send data to SEEBlue module
    if(ble.connected) {
        // [start byte 35][msg length][msg_index][crap][checksum]
        //if(c == SEEBLUE_START_BYTE) ble.connected = 2;
        //SEEBlue_Receiver(c);
    // otherwise look for TTM message
    }else {
        switch (rx_state) {
            case BLE_RX_IDLE: if(c == 'T') rx_state = BLE_RX_T; break;
            case BLE_RX_T: rx_state = (c == 'T') ? BLE_RX_TT : BLE_RX_IDLE; break;
            case BLE_RX_TT: rx_state = (c == 'M') ? BLE_RX_TTM : BLE_RX_IDLE; break;
            case BLE_RX_TTM: rx_state = (c == ':') ? BLE_RX_MSG : BLE_RX_IDLE; break;
            case BLE_RX_MSG:
                if(c == 0) {
                    // process message
                    if(msg[0]=='O' && msg[1]=='K') {
                        BLE_ProcessTTM(BLE_TTM_OK);
                    }else if(msg[0]=='M' && msg[1]=='A' && msg[2]=='C') {
                        for(i=0; i<12; i++) ble.mac[i] = msg[i+3];
                        BLE_ProcessTTM(BLE_TTM_MAC_RECEIVED);
                    }
                    msg_i = 0;
                    rx_state = BLE_RX_IDLE;
                }else {
                    msg[msg_i++] = c;
                    if(msg_i >= BLE_MAX_TTM_LENGTH) {
                        msg_i = 0;
                        rx_state = BLE_RX_IDLE;
                    }
                }
                break;
            default: rx_state = BLE_RX_IDLE;
        }
    }
}

void BLE_ProcessTTM(uint8_t TTM_code) {
    switch(TTM_code) {
        case BLE_TTM_OK:
            if(ble.TTM_OK_Callback) ble.TTM_OK_Callback();
            break;
        case BLE_TTM_ERP: break;
        case BLE_TTM_DISCONNECT: break;
        case BLE_TTM_DISCONNECT_FOR_TIMEOUT: break;
        case BLE_TTM_MAC_RECEIVED: break;
        default: break;
    }
}

void BLE_SetTTM_Callback(void (*callback)(void)) {
    ble.TTM_OK_Callback = callback;
}

void BLE_SoftReset(void) {
    BLUETOOTH_UART_SendString("TTM:RST-SYSTEMRESET");
}

void BLE_Send(uint8_t * msg) {
    BT_BRTSLow();
    DelayMs(15);
    BLUETOOTH_UART_SendString((char*)msg);
    DelayMs(5);
    BT_BRTSHigh();
}

void BLE_GetMAC(void) {
    BT_BRTSLow();
    DelayMs(15);
    BLUETOOTH_UART_SendString("TTM:MAC-?");
    //UART_WriteByte(BLE_UART, 0);
    DelayMs(5);
    BT_BRTSHigh();
}

void BLE_SleepCallback(uint8_t sleep) {

}

void BLE_ConnectedCallback(uint8_t connected) {
    if(connected == 0) {
        if(ble.connected == 0) {
            ble.connected = 1;
        }
    }else {
        ble.connected = 0;
    }
}

// "TTM:CIT-Xms" to set interval to X, where X = 20 (default) ,50,100,200,300,400,500,1000,1500, or 2000 ms (response is either TTM: TIMEOUT or TTM: OK)
void BLE_SetInvertal(uint16_t ms) {
    // make sure ms is a valid interval value
    if(ms < 35) ms = 20;
    else if(ms < 75) ms = 50;
    else if(ms < 150) ms = 100;
    else if(ms < 250) ms = 200;
    else if(ms < 350) ms = 300;
    else if(ms < 450) ms = 400;
    else if(ms < 750) ms = 500;
    else if(ms < 1250) ms = 1000;
    else if(ms < 1750) ms = 1500;
    else ms = 2000;
    BLUETOOTH_UART_SendString("TTM:CIT-%dms\r\n\0");
}

void BLE_ConnectionCallback(void(*fn)(uint8_t)) {
    ble.ConnectedCallback = fn;
}

void BLE_CorrectBaud(){
    BLUETOOTH_UART_Init(9600);                  // Initialize bluetooth UART to 9600 baud
    BT_BRTSLow();                               // Set BRTS Low to end transmit
    DelayMs(15);
    BLUETOOTH_UART_SendString("TTM:BPS-115200");
    DelayMs(5);
    BT_BRTSHigh();                              // Set BRTS High to end transmit
    DelayMs(1500);
    BLUETOOTH_UART_Init(115200);                // Initialize bluetooth UART to 115200 baud
}

void BLE_SetName(char* s){
    BT_BRTSLow();                               // Set BRTS Low to end transmit
    DelayMs(15);
    BLUETOOTH_UART_SendString("TTM:REN-");    // Send Change name command
    BLUETOOTH_UART_SendString(s);              // Send name
    DelayMs(5);
    BT_BRTSHigh();                              // Set BRTS High to end transmit
}

