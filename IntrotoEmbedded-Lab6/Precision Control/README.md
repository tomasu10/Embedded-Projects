### Jake Fraser and Tomas Uribe

## Lab Exercise 6: Sensing the World Around You
# Precision Control
# PWM and R2R Ladder

## PWM Part 2
The code for the PWM was implemented using a hardware approach. Using one CCR to determine the frequency and another to determine the duty cycle, 
a PWM signal could be output to a pin. The PWM then was able to convert a digital voltage into an analog reading. 
This analog voltage could then be read from the pin that the PWM is output to. To test this code a triangle wave was coded and then 
implemented to see the range of voltages that the PWM could output. In order to get a clean output, the signal was put through a passive lowpass filter, with a cutoff frequency of 500 Hz. 
The triangle wave produced by the PWM can be seen below compared to a similar wave produced by a function generator
 
![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Precision%20Control/scope_6.png)

## R2R DAC
To implement the R2R DAC, the circuit seen below was used. 

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Precision%20Control/R2R.jpg)

This circuit was able to take individual bits of a digital signal at each node of the circuit and then output an equivalent analog voltage. 
Depending on which bits in the input are set to 0 and 1, the output voltage will have a corresponding stepped voltage between 0 and Vref minus the value of the minimal step, corresponding to bit 0.
Since there is 8 nodes on the circuit the digital signal could vary from 0-255.
A digital voltage signal was output to independent pins by masking the desired signal 8 different times to save the values of each bit into separate variables. These variables were called bit0-bit7 and represented their respective bit of the digital signal. 
The variables were then output to pins and connected to their respective node on the R2R circuit. To test the range, a step function was created to visualize an increasing voltage on the output of the R2R circuit. This step function was 
created on the MSP430G2553, and can be seen in the figure below. 

![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-jake-n-tomas/blob/master/Precision%20Control/R2R%20STEPFUNC1.png)

Next, the triangle wave was generated from the  R2R ladder network. This was done by simply incrementing the number that was sent to the R2R within a for loop.
 However, in this case, the output had a phase shift of about 90 degrees. The output of this circuit versus a triangle produced by a function generator can be seen below.

![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-jake-n-tomas/blob/master/Precision%20Control/scope_5.png)

## Bill of Materials
#R2R Ladder
-1k Ohm resistors

-2k Ohm resistors

#Passive Lowpass Filter for PWM
-3k Ohm resistor 

-100 nF capacitor
