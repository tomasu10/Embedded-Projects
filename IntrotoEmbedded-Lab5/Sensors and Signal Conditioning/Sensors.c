/*
 * Photoresistor.c
 *
 *  Created on: Oct 25, 2017
 *      Author: tomas
 */
#include<msp430g2553.h>
int temp =0;
unsigned char uartSend( unsigned char *pucData, unsigned char ucLength )
{
  while(ucLength--)
  {
    // Wait for TX buffer to be ready for new data
      while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?

    // Push data to TX buffer
    UCA0TXBUF = *pucData; // Assigning the value pointed to by pucData to register UCA1TXBUF

    // Update variables
        //ucLength--;
        pucData++;
  }
  while(UCA0STAT & UCBUSY);
}

int Sensors(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  ADC10CTL1 = INCH_7 + SHS_1;               // P1.7, TA1 trigger sample start
  ADC10AE0 = 0x80;                          // P1.7 ADC10 option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TACCTL0 = CCIE;                           // Enable interrupt
  TACCR0 = 4096-1;                            // PWM Period
  TACCTL1 = OUTMOD_3;                       // TACCR1 set/reset
  TACCR1 = 32;                               // TACCR1 PWM Duty Cycle
  TACTL = TASSEL_1 +MC_1+ID_3;                  // ACLK, up mode

          //Initialize UART
         if (CALBC1_1MHZ==0xFF)                      // If calibration constant erased
           {
             while(1);                               // do not load, trap CPU!!
           }
           DCOCTL    = 0;                            // Select lowest DCOx and MODx settings
           BCSCTL1   = CALBC1_1MHZ;                  // Set DCO
           DCOCTL    = CALDCO_1MHZ;
           P1SEL    |= BIT1 + BIT2;                  // P1.1 = RXD, P1.2=TXD
           P1SEL2   |= BIT1 + BIT2;                  // P1.1 = RXD, P1.2=TXD
           UCA0CTL1 |= UCSSEL_2;                     // SMCLK
           UCA0BR0   = 104;                          // 1MHz 9600
           UCA0BR1   = 0;                            // 1MHz 9600
           UCA0MCTL  = UCBRS0;                       // Modulation UCBRSx = 1
           UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
           IE2      |= UCA0RXIE;                     // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  //ADC10CTL0 &= ~ENC;                        // ADC10 disabled
  //ADC10CTL0 = 0;                            // ADC10, Vref disabled completely
    temp = ADC10MEM;

    unsigned char dataArray[2] = {temp>>8, temp}; // Variable dataArray is now an unsigned char pointer (the type accepted by the function)
    uartSend(dataArray, 2);

  if (ADC10MEM < 0x1FF)                      // ADC10MEM = A7 > 0.2V?
   P1OUT &= ~0x01;                         // Clear P1.0 LED off
  else
    P1OUT |= 0x01;                          // Set P1.0 LED on

    ADC10CTL0 &= ~ENC;                        // ADC10 disabled
    ADC10CTL0 = 0;                            // ADC10, Vref disabled completely
}
 //Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE;
  ADC10CTL0 |= ENC;                         // ADC10 enable set
}
