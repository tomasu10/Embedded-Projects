### Jake Fraser and Tomas Uribe

# Lab Exercise 5: Sensing the World Around You
## PCB Design
### MSP430FR2311 Breakout

## Function
This printed circuit board is to be used as a breakout for the MSP430FR2311 microprocessor. This board has no purpose other than the
 fact that it is a basically a breadboard usable version of the MSP430FR2311. Using pin headers, bulk and bypass capacitors, along with a pull up resistor,
 as its reset circuitry, using this board allows the user to place and program this processor directly onto a breadboard. This will allow for 
 a multitude of projects and research to be conducted, using this board for mostly testing purposes, and not on a final product. The PCB can be seen below 
 
![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/PCB%20Design/Front.PNG)

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab5/PCB%20Design/Back.PNG)

## How it works
 When placed on a breadboard, the test, reset, power, and ground pins can be connected directly to the development board version of this processor. When
 doing so, the processor can be programmed through the computer, onto the launchpad, and then onto the breakout. This allows for ease of access to the processor
 when ding testing, debugging, and prototyping. 

## Bill of Materials
In order to build this printed circuit board, a few build materials must be acquired. Bulk and bypass capacitors and a resistor are all used in reset and support circuitry. 
 Appropriate values can be seen below. Pin headers are used to connect to the breadboard and for easy access to each pin of the processor. 

-U2: MSP430FR2311

-C1: 10 uF Capacitor, surface mount (CAP_0805) 

-C2: 100 nF Capacitor, surface mount (CAP_0805)

-C3: 100 nF Capacitor, surface mount (CAP_0805)

-R1: 47k Ohm resistor, surface mount (RES_0805)

-J3: 8 through hole pin header

-J4: 8 through hole pin header
