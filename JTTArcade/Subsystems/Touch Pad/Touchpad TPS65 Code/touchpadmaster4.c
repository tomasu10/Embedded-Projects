///*
//// * touchpadmaster4.c
//// *
//// *  Created on: Dec 5, 2017
//// *      Author: tomas
//// */
////
//#include <msp430fr5994.h>
//
//#define TPS65I2CAddress 0x74;
//void I2CInit(void);
//int ReadGestures(void);
//
//void touchpadmaster4(){
//    P7SEL0 |= BIT0 | BIT1;
//    P7SEL1 &= ~(BIT0 | BIT1);
//    I2CInit();
//
//
//    ReadGestures();
//
//}
//
//void I2CInit()
//{
//    UCB2CTLW0 |= UCSWRST;                   // Software reset enabled
//    UCB2CTLW0 |= UCMODE_3 | UCMST | UCSYNC; // I2C mode, Master mode, sync
//    UCB2BRW = 0x0009;                          // baudrate = SMCLK / 8
//    UCB2CTLW0 &= ~UCSWRST;                  // clear reset register
//    UCB2CTLW1 |= UCASTP_0;                  // Automatic stop generated
//
//    UCB2IE |= UCTXIE|UCRXIE;
//
//    // after UCB0TBCNT is reached
//    //UCB2BRW = 0x0008;                       // baudrate = SMCLK / 8
//    UCB2CTL1 &= ~UCSWRST;
//}
//
//int ReadGestures()
//{
//    int Data1, Data2;
//    UCB2CTL1 &= ~UCSWRST;
//    //UCB2CTLW1 |= UCASTP_2;                   // automatic STOP assertion
//
//    UCB2I2CSA = TPS65I2CAddress;            // Set I2C Slave Address
//
//    UCB2CTLW0 |= UCTXSTT| UCTR;             // Start Condition with "Transmit Mode"
//    while (!(UCB2IFG & UCTXIFG0));          // Wait until we can transmit
//    UCB2TXBUF = 0x06;                       // Send the first byte of the register address for gestures
//    while (!(UCB2IFG & UCTXIFG0));          // Wait until we can transmit
//    UCB0TXBUF = 0xB7;                       // Send the second byte of the register address for gestures
//    while (!(UCB2IFG & UCTXIFG0));          // Waiting for an ACK
//    UCB2CTL0 |= UCTXSTT + ~UCTR;            // Send Restart Condition and change into Receiver Mode
//    UCB2TBCNT = 0x02;                       // Set Byte Count to Stop after 1 Byte Received
//    while (!(UCB2IFG & UCRXIFG0));          // Wait until a byte has been received
//    Data1 = UCB2RXBUF;                      // Save Received Byte
//    while (!(UCB2IFG & UCRXIFG0));          // Wait until next byte has been received
//    Data2 = UCB2RXBUF;                      // Save Received Byte
//    return (Data1 << 8 + Data2);            // Send back both bytes as an int
//}
//
//
