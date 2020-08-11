/*
 * bluetooth_uart.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Tanner
 */

#include "msp430fr5994.h"
#include "eusci_a_uart.h"
#include "gpio.h"
#include "pmm.h"
#include "cs.h"
#include "wdt_a.h"
#include "bluetooth_uart.h"
#include "bluetooth.h"

uint16_t i;
uint8_t TXData = 0;
uint8_t RXData[100] = {0};
uint8_t check = 0;

void BLUETOOTH_UART_Init(int baudrate){

    // Configure UART pins
    //Set P6.0 and P6.1 as Secondary Module Function Input.
    /*

    * Select Port 2d
    * Set Pin 0, 1 to input Secondary Module Function, (UCA3TXD/UCA3SIMO, UCA3RXD/UCA3SOMI).
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P6,
    GPIO_PIN0 + GPIO_PIN1,
    GPIO_PRIMARY_MODULE_FUNCTION
    );

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    EUSCI_A_UART_initParam param = {0};
    if(baudrate == 9600){
        //  Configure UART 9600 Baud
        param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
        param.clockPrescalar = 3;
        param.firstModReg = 0;
        param.secondModReg = 0x92;
        param.parity = EUSCI_A_UART_NO_PARITY;
        param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
        param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
        param.uartMode = EUSCI_A_UART_MODE;
        param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    }
    else{
        // Configure UART 115200 Baud
        param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
        param.clockPrescalar = 8;
        param.firstModReg = 0;
        param.secondModReg = 0xD6;
        param.parity = EUSCI_A_UART_NO_PARITY;
        param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
        param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
        param.uartMode = EUSCI_A_UART_MODE;
        param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    }

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A3_BASE, &param)) {
        return;
    }

    EUSCI_A_UART_enable(EUSCI_A3_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A3_BASE,
      EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Enable USCI_A3 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A3_BASE,
      EUSCI_A_UART_RECEIVE_INTERRUPT);                     // Enable interrupt

//    while (1)
//    {
//        TXData = TXData+1;                      // Increment TX data
//        // Load data onto buffer
//        EUSCI_A_UART_transmitData(EUSCI_A3_BASE,
//                           TXData);
//        while(check != 1);
//        check = 0;
//    }
}

void BLUETOOTH_UART_TransmitChar(char s){
    TXData = s;
    EUSCI_A_UART_transmitData(EUSCI_A3_BASE, TXData);
    while(!(EUSCI_A_UART_getInterruptStatus(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_COMPLETE_INTERRUPT_FLAG)));
}

void BLUETOOTH_UART_TransmitByte(int byte){
    TXData = byte;
    EUSCI_A_UART_transmitData(EUSCI_A3_BASE, TXData);
    while(!(EUSCI_A_UART_getInterruptStatus(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_COMPLETE_INTERRUPT_FLAG)));
}


//******************************************************************************
//
//This is the USCI_A3 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A3_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A3_VECTOR)))
#endif
void USCI_A3_ISR(void)
{
  switch(__even_in_range(UCA3IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
        RXData[i++] = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
        //BLE_Receiver(EUSCI_A_UART_receiveData(EUSCI_A3_BASE));
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
  }
}
