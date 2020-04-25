/**
 * main.c
 */

#include "pmm.h"
#include "wdt_a.h"
#include "bluetooth_uart.h"
#include "bluetooth.h"

int main(void)
{
    // stop watchdog

    WDT_A_hold(WDT_A_BASE);

    __enable_interrupt();

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    BLE_Init();

    while(1);

//    BLUETOOTH_UART_Init(115200);
//    BLUETOOTH_UART_SendString("Hello");
	
//	BLE_RESET = 0; // hold bluetooth in reset
//    BLE_ENABLE = 1;
//    BLE_RTS = 1; // ~RTS
//
//    UART_Init(UART3_CH);
//    UART_Init(UART4_CH);
//
//    BLE_RESET = 1;
//    SEEBlue_Init();
//    BLE_ENABLE = 0;
//
//    DelayMs(500);
//    BLE_CorrectBaud();
//    DelayMs(100);
//    BLE_GetMAC();
//    DelayMs(100);
//    //BLE_GetMAC();
//    BLE_SetName("LEDGlowV2");

	return 0;
}
