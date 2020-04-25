///*
// * touchpad.c
// *
// *  Created on: Dec 10, 2017
// *      Author: tomas
// */
//#include <msp430.h>
//#define VCNL4200_ADDRESS 0x74;
//int     RX_Byte_Ctr;        // Coutner to make sure all of the information is received
//char    height[2],          // Creates an array to store height data
//        *pointer;           // Creates a pointer to access the array
//void RDYInit();
//void i2cInit();
//
//int touchpad(void)
//{
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
//    PM5CTL0 &= ~LOCKLPM5;
//
//    RDYInit();
//    i2cInit();
//
//}
//
//void RDYInit()
//{
//    P8OUT &= 0x00;                    // Shut Port 1 Down
//    P8DIR |= BIT0;                    // Port 1 direction set
//    P8IE  |= BIT0;                    // P1 interrupt enabled
//    P8IES &= ~BIT0;                   // P1 lo/hi edge
//    P8IFG &= ~BIT0;                   // P1 IFG cleared
//    __bis_SR_register(GIE);
//}
//
//void i2cInit(void){
//        P7SEL0 |= BIT0 | BIT1;
//        P7SEL1 &= ~(BIT0 | BIT1);
//    UCB2CTLW0 |= UCSWRST;   // Enters reset state, USCI stops operation
//    UCB2TBCNT = 0x02;       // Expecting to receive 2 bytes of data
//    UCB2CTLW1 |= UCASTP_2;  // Sends stop bit when UCTBCNT is reached
//    UCB2I2CSA = VCNL4200_ADDRESS;           // Sets slave address
//    UCB2CTLW0 |= UCMST      // Master Mode
//              |  UCMODE_3   // I2C Mode
//              |  UCMST | UCSSEL__SMCLK;    // Synchronus Mode
//    UCB2BRW    = 0x000A;    // SMCLK/10
//    UCB2CTLW0 &= ~UCSWRST;  // Exits reset mode, USCI enters operation
//    UCB2IE    |= UCTXIE0    // Data received interrupt enable
//              |  UCRXIE0    // Data ready to transmit interrupt enable
//             |  UCNACKIE;  // NACK interrupt enable
//}
//
//void I2CWrite()
//{
//
//    UCB2TXBUF = 0x00;                       // Send the first byte of the register address for gestures
//    __delay_cycles(100);
//
//
//
//   UCB2TXBUF = 0x0D;                       // Send the second byte of the register address for gestures
//
//   __delay_cycles(100);
//
//
//}
//
//void I2CRead()
//{
//    if (RX_Byte_Ctr){                       // Checks if there is more data to be received
//       *pointer = UCB2RXBUF;               // Loads the data array
//       pointer++;                          // Increments the pointer
//       RX_Byte_Ctr--;                      // Decrement TX byte counter
//   }
//
//
//}
//
//// Port 8 interrupt service routine
//#pragma vector=PORT8_VECTOR
//__interrupt void Port_8(void)
//{
//        I2CRead();
//}
//
//
//#pragma vector = USCI_B2_VECTOR
//__interrupt void USCI_B2_ISR(void) {
//    switch(__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG)) {
//        case USCI_I2C_UCNACKIFG:                    // NACK Interrupt
//            UCB2CTL1 |= UCTXSTT;                    // I2C start condition
//        break;
//
//        case USCI_I2C_UCRXIFG0:                     // I2C RX Interrupt
//
//        break;
//
//        case USCI_I2C_UCTXIFG0:                     // I2C TX Interrupt
//            I2CWrite();
//        break;
//
//        default: break;
//}   }
