### Jake Fraser and Tomas Uribe

## Lab Exercise 6: Sensing the World Around You
# Open Loop Control System 

# Processor Selection 
The processor selected for this portion of the lab was the MSP430G2553 for its versatility and furthermore, its replacability. Since the processor on the G2 can be removed and replaced, this was seen as a very favorable attribute as the processor was likely to get damaged using such high voltages.

# Open Loop Control Circuit
The circuit that was designed for this portion of the lab was built using three OPA548s to amplify a 3.3V input. Since the voltage regulator, temperature sensor, and fan all had different operational voltages the 3 OpAmps were used to provided each component with the voltage necessary to function. In order to properly operate the fan, a MosFet switch was implemented using a 2N7000 NMOS. By using this method the fan was able to simulate the duty cycle of the PWM signal that was applied to the gate of the NMOS. This signal continuously turned the NMOS on and off allowing the fan to function at a speed that correlated to the duty cycle of the PWM. As for the voltage regulator, a 27 ohm power resistor was attached to its output as a load in order to allow it to heat up faster. The temperature sensor was then used to read the temperature around the voltage regulator in order to allow the user to read the temperature of the regulator through UART. The circuit used for the open loop control system can be seen below.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Open%20Loop%20Systems/OpenLoopCircuit.jpg)


# Code Functionality 
The main function of the software for the open loop control system was to produce a PWM signal with a duty cycle depending on the desired temperature set by the user. Through UART,the user was able to send a desired temperature to the MSP430G2553. Within the code, the received temperature was then passed to a function called setDutyCycle which correlated the given temperature to an appropriate duty cycle. This duty cycle was then used in a function called setPWM which was used to set the capture compare register that was output to the NMOS switch, controlling the fan. In order to correctly model the data an excel spreadsheet was made comparing the duty cycle of the PWM and the temperature read by the temperature sensor. The data can be seen below. 

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Open%20Loop%20Systems/TempvsDutyCycle.JPG)

This data was then split up into 2 different data sets and then independently linearized. The temperature regions that were detemined by the graph above were 76C-31C and 30C-20C. Each produced a line of best fit of y = -0.8367x + 62.693 and y = -4.9013x + 187.28 respectively. This process allowed the processor to determine at what duty cycle the PWM had to be set, depending on the temperature that the analog to digital converter read. Ultimately, the linearization of data was what caused the fan to change speeds in order to let the voltage regulator reach the temperature assigned by the user. The two figures below depict the lines of best fit of the 76C-31C and 30C-20C temperature regions respectively.

76C-31C

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Open%20Loop%20Systems/temp76-31.JPG)

30C-20C

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Open%20Loop%20Systems/temp23-20.JPG)

In order to visualize the temperature values read by the temperature sensor, its output was connected to an oscilloscope. The results below show the temperature dropping from 58C to a desired temperature of 40C.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab6/Open%20Loop%20Systems/temp58-40.gif)
