#include <msp430.h> 

void setPWM(unsigned int duty);
void setUpPWM();
void pwmUARTInterrupt(int bufInput);
void setUpUART();
void setUpADC();
void ADC10Interrupt();
void timerA1Interrupt();
void setUpTimerA0();
void setDutyCycle(int volt);

int voltBuf[8];
int voltBuf_index = 0;
long outVolt = 0;
double newVolt = 0;
long error = 0;
int setPoint = 0;


int count = 0;

int k = 1; //Must be readjusted
int goalout = 4;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    setUpPWM();
    setUpUART();
    setUpADC();
    setUpTimerA0();
    setPoint = (goalout*1024)/9.9;
    setPoint /= 10;

    __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled

    while(1){

    }
}


void setUpPWM(){
    P2DIR |= BIT1;                            // P2.1 output
    P2SEL |= BIT1;                            // P2.1 for TA0 CCR1 Output Capture
    P2SEL2 = 0;                               // Select default function for P1.6 (see table 19 in general datasheet)
    TA1CCR0 = 100;                             // PWM Freq=10000Hz
    TA1CCTL1 = OUTMOD_3;                         // CCR1 reset/set: set on at CCR0, off at CCR1 capture (see table 12-2 in specific datasheet)
    TA1CCR1 = 50;                               // CCR1 50% PWM duty cycle
    TA1CTL = TASSEL_2 + MC_1 + ID_0;                  // SMCLK, up mode, 1MhZ
}

void setUpUART(){
    if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
    {
      while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 |= BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 104;                            // 1MHz 9600
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

}

void setUpADC(){
    ADC10CTL1 = INCH_7 + SHS_1;               // P1.7, TA1 trigger sample start
    ADC10AE0 = 0x80;                          // P1.7 ADC10 option select

}

void setUpTimerA0(){
    TA0CCTL0 = CCIE;                           // Enable interrupt
    TA0CCR0 = 6550;                           // PWM Period
    TA0CCTL1 = OUTMOD_3;                       // TACCR1 set/reset
    TA0CCR1 = 781;                               // TACCR1 PWM Duty Cycle
    TA0CTL = TASSEL_2 + MC_1 + ID_3;                  // ACLK, up mode
}


void pwmUARTInterrupt(int bufInput){ //Must determine a new value of k!
    goalout = bufInput;
    setPoint = (goalout*1024)/9.9;
    setPoint /= 10;
    UCA0TXBUF = setPoint;

}

void ADC10Interrupt(){
    long reading = 0;
    ADC10CTL0 &= ~ENC;                        // ADC10 disabled
    ADC10CTL0 = 0;                            // ADC10, Vref disabled completely
    reading = ADC10MEM / 10;
    error = setPoint - reading;
    TA1CCR1 = TA1CCR1 + (1 * error);

    count++;
    if(count>500)
    {
        if(error <0){
            TA1CCR1++;
        }
        else if (error> 0){
           TA1CCR1--;
        }
        else{
            count = 0;
        }
        count =0;
    }
}

void timerA0Interrupt(){
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON + ADC10IE;
    ADC10CTL0 |= ENC;                         // ADC10 enable set
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
    pwmUARTInterrupt(UCA0RXBUF);
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)

{
    ADC10Interrupt();
}
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)

{
    timerA0Interrupt();
}
