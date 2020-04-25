#include <msp430f5529.h>


/**
 * main.c
 */

void setUpPWM();
void OutputInit();

void setPWM8bit(unsigned int voltage);
void OutputSet(int voltage);

void CreateTriangleWaves();
void CreateStepFunction();

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	    // Stop watchdog timer
	
	setUpPWM();                     // Initialize PWM DAC
	OutputInit();                   // Initialize R2R DAC

	//CreateStepFunction();
	CreateTriangleWaves();

	return 0;
}

void CreateStepFunction(){
    int i = 0;                      // Index for counter
    int i2 = 0;

    while(1){
        for(i = 0; i < 256; i=i+16){   // Increment index until 256 (8 bit 0xFF) is reached
            setPWM8bit(i);          // Set PWM DAC to incrementing index
            OutputSet(i);           // Set R2R DAC to incrementing index
            for(i2 = 0; i2 < 1000; i2++);
        }
        for(i = 255; i >= 0; i=i-16){  // Decrement index until 0 (8 bit 0x00) is reached
            setPWM8bit(i);          // Set PWM DAC to decrementing index
            OutputSet(i);           // Set R2R DAC to decrementing index
            for(i2 = 0; i2 < 1000; i2++);
        }
    }
}

void CreateTriangleWaves(){

    int i = 0;                      // Index for counter

    while(1){
        for(i = 0; i < 256; i++){   // Increment index until 256 (8 bit 0xFF) is reached
            setPWM8bit(i);          // Set PWM DAC to incrementing index
            OutputSet(i);           // Set R2R DAC to incrementing index
        }
        for(i = 255; i >= 0; i--){  // Decrement index until 0 (8 bit 0x00) is reached
            setPWM8bit(i);          // Set PWM DAC to decrementing index
            OutputSet(i);           // Set R2R DAC to decrementing index
        }
    }
}

void setUpPWM(){
    P1DIR |= BIT2;                            // P1.6 output
    P1SEL |= BIT2;                            // P1.6 for TA0 CCR1 Output Capture
    //P1SEL2 = 0;                               // Select default function for P1.6 (see table 19 in general datasheet)
    TA0CCR0 = 1000;                             // PWM Freq=1000Hz
    TA0CCTL1 = OUTMOD_7;                         // CCR1 reset/set: set on at CCR0, off at CCR1 capture (see table 12-2 in specific datasheet)
    TA0CCR1 = 500;                               // CCR1 50% PWM duty cycle
    TA0CTL = TASSEL_2 + MC_1;                  // SMCLK, up mode, 1MhZ
}

void setPWM8bit(unsigned int bitDuty){
    if(bitDuty>255){
        bitDuty = 255;
    }
    bitDuty *=125;								
    bitDuty = bitDuty >>5;						//Converts a 0-255 scale to 0-1000 scale
    TA0CCR1 = bitDuty;
}

void OutputInit(){

       P6DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;
       P7DIR |= BIT0;
       P3DIR |= BIT5 + BIT6;

}

void OutputSet(int values){

    int bit0 = values & BIT0;				//Masks bits of input into corresponding variables
    int bit1 = values & BIT1;
    int bit2 = values & BIT2;
    int bit3 = values & BIT3;
    int bit4 = values & BIT4;
    int bit5 = values & BIT5;
    int bit6 = values & BIT6;
    int bit7 = values & BIT7;

    if(bit0){								//Each variable, corresponding to the bit of input is sent to its own pin. 
        P6OUT |= BIT0;			
    }
    else{
        P6OUT&= ~BIT0;
    }
    if(bit1){
            P6OUT |= BIT1;
        }
        else{
            P6OUT&= ~BIT1;
        }
    if(bit2){
            P6OUT |= BIT2;
        }
        else{
            P6OUT&= ~BIT2;
        }
    if(bit3){
            P6OUT |= BIT3;
        }
        else{
            P6OUT&= ~BIT3;
        }
    if(bit4){
            P6OUT |= BIT4;
        }
        else{
            P6OUT&= ~BIT4;
        }
    if(bit5){
            P7OUT |= BIT0;
        }
        else{
            P7OUT&= ~BIT0;
        }
    if(bit6){
            P3OUT |= BIT6;
        }
        else{
            P3OUT&= ~BIT6;
        }
    if(bit7){
            P3OUT |= BIT5;
        }
        else{
            P3OUT&= ~BIT5;
        }

}






