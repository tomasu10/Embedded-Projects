
### Jake Fraser and Tomas Uribe

## Lab Exercise 5: Sensing the World Around You
## Sensors and Signal Conditioning 
## ADC10 on the MSP430G2553

## Function
Using the analog to digital converter on the MSP430G2553 developments board, real world data is collected through sensors and 
displayed to the user through UART serial communication. The sensors used in this experiment include a temperature sensor, 
a photoresistor, and a phototransistor. Each of these sensors will output a certain voltage depending on data collected in real time.
From there, the ADC10 on the MSP430 will take this value as an input and output it as a 10 bit hexadecimal value. In this case, the 
value is displayed through UART to the user. 

## How it works
When the code is first ran, the ADC initializations are set. This allows the ADC10 to take an input 
through P1.7. The code for these initializations can be seen below.

  ADC10CTL1 = INCH_7 + SHS_1;               // P1.7, TA1 trigger sample start
  ADC10AE0 = 0x80;                          // P1.7 ADC10 option select

From there a timer is set to update the value in the UART transmitting buffer at a rate of 1 MHz. Once the timer settings 
are initialized, the UART settings are initialized and the Rx and Tx pins are set. When a value is recieved through the ADC, the program
 enters the ADC10 interrupt. Here, the ADC is disabled, the data is added to an array, and the array is sent to the user through UART. The processor then checks to see
 if the value being collected is greater than 1FF. If so, an LED on the dev board will turn on. When the CCR value for the timer is reached,
 the timer interrupt is entered and the ADC is enabled again. This enables the processor to easily keep track of the current value
 being taken in by the ADC. 

## Usage
In order to use this program, start off by constructing a sensor circuit. This circuit can be any sensor from a temperature sensor to a light sensor, to a motion sensor.
 In this case, three different sensors were tested, including a temperature sensor, a photoresistor, and a phototransistor. 
The code must be referenced in a main.c file which will be uploaded to the MSP430. Use Pin P1.7 as the sensor output, and the program should keep track of everything else.
 The end product should consist of the user watching values scroll by on any UART interface which represent the current output of the sensor. 
 The user can watch the values change as the they manipulate the sensor using real world actions. 
 
## Circuit 
 
The Circuit used for this lab can be seen below 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Sensors%20and%20Signal%20Conditioning/All%20three%20circuits.jpg)

## Demonstration

The following section will highlight the voltage readings over UART taken from the photoresistor, temperature sensor, and phototransistor respectively

Photoresistor 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Sensors%20and%20Signal%20Conditioning/Photoresistor%20GIF.gif)

Temperature Sensor
 
![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Sensors%20and%20Signal%20Conditioning/Temperature%20Sensor%20GIF.gif)

Phototransistor 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/Sensors%20and%20Signal%20Conditioning/Phototransistor%20GIF.gif)
 
 
