### Jake Fraser and Tomas Uribe

## Lab Exercise 5: Sensing the World Around You
## Visualizing Data
## ADC12 on the MSP430FR6989

## Function
This program uses the ADC12 on the MSP430FR6989 to take in values from a sensor and display them on the on board LCD screen.
Using the analog to digital converter on the MSP430, real world data is collected through the sensors and 
displayed to the user through an LCD driver. The sensors used in this experiment include a temperature sensor, 
a photoresistor, and a phototransistor. Each of these sensors will output a certain voltage depending on data collected in real time.
From there, the ADC12 on the MSP430 will take this value as an input and output it as a 12 bit hexadecimal value. In this case, the value is converted to a decimal value,
 and displayed to the user on an LCD.

## How it works
 To start out, the program initializes the ADC12 ports as well as any registers used for the ADC12. The lines of code that configure these values can be seen below.

    P8DIR  |= BIT7;
    P8SEL1 |= BIT7;                         // Configure P1.1 for ADC
    P8SEL0 |= BIT7;

    // Configure ADC12
    ADC12CTL0   = ADC12SHT0_2 | ADC12ON;      // Sampling time, S&H=16, ADC12 on
    ADC12CTL1   = ADC12SHP;                   // Use sampling timer
    ADC12CTL2  |= ADC12RES_2;                 // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_4;                // A4 ADC input select; Vref=AVCC
    ADC12IER0  |= ADC12IE0;                   // Enable ADC conv complete interrupt

In this code, the sampling timer is initialized for the ADC12, the reference voltage is set to 3.3 V, and the ADC interrupt is initialized. 
 Next, the program utilizes the LCD driver to set the initial values for each LCD segment. After all of the LCD values are set, the rest of the initializatins for the LCD are set, referencing the LCDDriver.h and LCDDriver.c files when necessary.
 When the ADC12 recieves a value, the ADC12 interrupt is entered. While there, the code runs through
 a case statement which decides what values and characters will be displayed on the LCD. When the CCR value is reached with the timer, the timer interrupt is entered, where the 
 ADC is re-enabled. 
 

## Usage
In order to use this program, start off by constructing a sensor circuit. This circuit can be any sensor from a temperature sensor to a light sensor, to a motion sensor.
 In this case, three different sensors were tested, including a temperature sensor, a photoresistor, and a phototransistor. 
In order to use the LCD, it is important to reference the LCD driver at the beginning of the program. Since this is done in the Sensors.c file, the user should not have to worry about.
Therefore, the only thing the user needs to do is reference the Sensors.c file in the main.c file. This main file will be uploaded to the MSP430. Use Pin P8.7 as the sensor output, and the program should keep track of everything else.
 The end product should consist of the user watching the current voltage output of the sensor being displayed on the LCD.
 
## Demonstration
The following section will highlight the voltage readings over UART taken from the photoresistor, temperature sensor, and phototransistor respectively

Photoresistor 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Visualizing%20Data/Photoresistor%20GIF.gif)

Temperature Sensor 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Visualizing%20Data/Temperature%20Sensor%20GIF.gif)

Phototransistor 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Visualizing%20Data/Phototransistor%20GIF.gif)
