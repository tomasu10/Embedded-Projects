#include <msp430.h>

int ByteCount = 0;    // Keeps track of bytes received
int Red,Green, Blue; //Hold the the duty cycle of each RBG node
int numOfBytes = 0; //The number of bytes remaining in the message

int Milestone1(void)
{
    // Red is pin 1.6, TA0CCR1
    // Blue is pin 2.4, TA1CCR2
    // Green is pin 2.1, TA1CCR1
    // RX (input) is pin 1.1
    // TX (output) is pin 1.2



        //GPIO and PWM Initializations
        P1OUT   &= 0x00;                            // P1OUT is set to 0
        P1DIR   &= 0x00;                            // Port 1 direction is set to 0
        P1DIR   |= 0x42;                            // Sets the LEDs as outputs

        P2OUT   &= 0x00;                            // P1OUT is set to 0
        P2DIR   &= 0x00;                            // Port 1 direction is set to 0
        P2DIR   |= 0x12;                            // Sets the LEDs as outputs

        P1SEL    = BIT6;                            // outputs TA0CCR1
        P1SEL2   = 0;                               // Set as out
        P2SEL    = BIT1 + BIT4;                     // outputs TA1CCR2 and TA1CCR1
        P2SEL2   = 0;                               // Set as out

        TA0CCR0  = 256;                             // Sets base CCR
        TA1CCR0  = 256;                             // Sets base CCR

        TA0CCTL1 = OUTMOD_7;
        TA1CCTL1 = OUTMOD_7;
        TA1CCTL2 = OUTMOD_7;

        TA0CTL   = TASSEL_2 + MC_1 + ID_2;                 // Starts timer 0
        TA1CTL   = TASSEL_2 + MC_1 + ID_2;                 // Starts timer 1

        //Initialize UART
        if (CALBC1_1MHZ==0xFF)                      // If calibration constant erased
          {
            while(1);                               // do not load, trap CPU!!
          }
          DCOCTL    = 0;                            // Select lowest DCOx and MODx settings
          BCSCTL1   = CALBC1_1MHZ;                  // Set DCO
          DCOCTL    = CALDCO_1MHZ;
          P1SEL    |= BIT1 + BIT2 + BIT5;           // P1.1 = RXD, P1.2=TXD
          P1SEL2   |= BIT1 + BIT2;                  // P1.1 = RXD, P1.2=TXD
          UCA0CTL1 |= UCSSEL_2;                     // SMCLK
          UCA0BR0   = 104;                          // 1MHz 9600
          UCA0BR1   = 0;                            // 1MHz 9600
          UCA0MCTL  = UCBRS0;                       // Modulation UCBRSx = 1
          UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
          IE2      |= UCA0RXIE;                     // Enable USCI_A0 RX interrupt

      __bis_SR_register(GIE);                       // Enter LPM0 w/ interrupt
}

//UART RX Buffer
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)

{
    while (!(IFG2&UCA0TXIFG));
    {
    if(ByteCount == 0)
    {
        numOfBytes = UCA0RXBUF;                     //Save number of Bytes left in message
        ByteCount++;
    }
    else if((ByteCount > 0) && ByteCount <= 3)      //could also use a switch case
    {
        switch(ByteCount)
            {
            case 1:
                Red =   UCA0RXBUF;
                TA0CCR1 = Red;                      // Sets CCR value to red
                ByteCount++;
                break;
            case 2:
                Green = UCA0RXBUF;
                TA1CCR1 = Green;                    // Sets CCR value to green
                ByteCount++;
                break;
            case 3:
                Blue =  UCA0RXBUF;
                TA1CCR2 = Blue;                     // Sets CCR value to blue
                ByteCount++;
                UCA0TXBUF = numOfBytes - 3;
                break;
            default:
                break;
            }
        }

    else if(ByteCount < numOfBytes )
        {
            UCA0TXBUF = UCA0RXBUF;                  //Transmit data to other processors
            ByteCount++;
        }
    else if(ByteCount == numOfBytes )
            {
                numOfBytes =0;                  //Reset Functionality
                ByteCount=0;
            }
    }
}
