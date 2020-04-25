/*
 * touchpadmaster6.c
 *
 *  Created on: Dec 14, 2017
 *      Author: tomas
 */


#include <msp430.h>
#define VCNL4200_ADDRESS 0x74;
int     RX_Byte_Ctr;        // Coutner to make sure all of the information is received
char    height[4],          // Creates an array to store height data
        *pointer;           // Creates a pointer to access the array

int ifTransmit =1;
int ifRecieve =1;



void i2cInit(void){
        P7SEL0 |= BIT0 | BIT1;
        P7SEL1 &= ~(BIT0 | BIT1);
    UCB2CTLW0 |= UCSWRST;   // Enters reset state, USCI stops operation
    UCB2TBCNT = 0x04;       // Expecting to receive 4 bytes of data
    UCB2CTLW1 |= UCASTP_2;  // Sends stop bit when UCTBCNT is reached
    //UCB2I2CSA = VCNL4200_ADDRESS;           // Sets slave address
    UCB2CTLW0 |= UCMST      // Master Mode
              |  UCMODE_3   // I2C Mode
              |  UCMST | UCSSEL__SMCLK;    // Synchronus Mode
    UCB2BRW    = 0x0009;    // SMCLK/10
    UCB2CTLW0 &= ~UCSWRST;  // Exits reset mode, USCI enters operation
    UCB2IE    |= UCTXIE0    // Data received interrupt enable
              |  UCRXIE0    // Data ready to transmit interrupt enable
             |  UCNACKIE;  // NACK interrupt enable
}
void RDYInit(void)
{
    P8OUT &= 0x00;                    // Shut Port 1 Down
    P8DIR |= BIT0;                    // Port 1 direction set
    P8IE  |= BIT0;                    // P1 interrupt enabled
    P8IES &= ~BIT0;                   // P1 lo/hi edge
    P8IFG &= ~BIT0;                   // P1 IFG cleared
    __bis_SR_register(GIE);
}




void getHeight(void){

    pointer = height;                       // Sets the pointer to the height array

    RX_Byte_Ctr = 4;
    UCB2I2CSA = VCNL4200_ADDRESS;           // Sets slave address

    if(ifTransmit){
    UCB2CTL1 |= UCTR                        // Enables TX Mode
             |  UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
    }
    if(ifRecieve){
    UCB2CTL1 &= ~UCTR;                      // Enters RX Mode
    UCB2CTL1 |= UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
    }

}


void touchpadmaster6(void){
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    i2cInit();
    RDYInit();
    while(1){
    getHeight();
    }
    }



// Port 8 interrupt service routine
#pragma vector=PORT8_VECTOR
__interrupt void Port_8(void)
{
       getHeight();
       P8IFG &= ~BIT0;                     // P5.6 IFG cleared
}

#pragma vector = USCI_B2_VECTOR
__interrupt void USCI_B2_ISR(void) {
    switch(__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG)) {
        case USCI_I2C_UCNACKIFG:                    // NACK Interrupt
            UCB2CTL1 |= UCTXSTT;                    // I2C start condition
        break;

        case USCI_I2C_UCRXIFG0:                     // I2C RX Interrupt
            if (RX_Byte_Ctr){                       // Checks if there is more data to be received
                *pointer = UCB2RXBUF;               // Loads the data array
                pointer++;                          // Increments the pointer
                RX_Byte_Ctr--;                      // Decrement TX byte counter
            } else {
                ifRecieve =0;
                __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
            }
        break;

        case USCI_I2C_UCTXIFG0:                     // I2C TX Interrupt

             UCB2TXBUF = 0x00;                       // Send the first byte of the register address for gestures
             __delay_cycles(100);

            __bic_SR_register_on_exit(LPM0_bits);   // Exits Low-Power mode

            UCB2TXBUF = 0x12;                       // Send the second byte of the register address for gestures

            __delay_cycles(2000);

            ifTransmit =0;
            __bic_SR_register_on_exit(LPM0_bits);   // Exits Low-Power mode
        break;

        default: break;
}   }

