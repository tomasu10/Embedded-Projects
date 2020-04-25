### Jake Fraser and Tomas Uribe

## Lab Exercise 6: Sensing the World Around You
## High Power Control
## Relay and Mosfet Switching

## Relay Switch
In this section, two circuits were built in order to test the differences between two different types of switches. First, a MAD S 112 C relay was connected
appropriately to take in a square wave as an input, with a power resistor on the output to simulate a load.
Inside of the relay, there is an inductor that will have a voltage differential across it. This voltage differential consists of the square wave input and ground. 
The output pin (middle) will switch between the two outer pins (ground and 12 V) whenever the input is switched, which induces a current. 
Because the input is a square wave, the relay will switch between 12 V and ground whenever the square wave switches from 3.3 V to ground. This is incredibly useful, 
allowing the user to control the voltage of an output pin, based on an input at any specific time. Since there is no direct electrical connection between the input and the output,
 the current draw of the relay is 0 A. An oscilloscope screenshot of the output of the relay vs the input signal can be seen below.

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab6/High%20Power%20Control/scope_1.png)

At some point, the frequency will be so high that the relay will stop switching. This is because the input is switching so fast that 
the inductor cannot induce a current fast enough to switch the output. In this experiment, the maximum operating frequency of the relay was found to be 130 Hz. As seen below,
the output starts to become disfigured at its maximum operating frequency. 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab6/High%20Power%20Control/scope_2.png)

## MOSFET Switch
Next, a low side switch was created using a 2N7000 NMOS along with a 50 Ohm, 10 W power resistor. As an input, a square wave was 
used to switch between 12 V and ground. When the input square wave is high at 3.3 V, the output of the lowside switch will be 0 V, and when 
the input is low at 0 V, the output will be high at 12 V. Therefore, the output of the MOSFET is constantly switching between 0 and 12 V. 
The input vs output plot can be seen below.

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab6/High%20Power%20Control/scope_3.png)

From here, the maximum operating frequency of the low side switch was found by increasing the frequency of the input signal until 
the NMOS failed. This happened when the input was increased to approximately 200 Hz. This can be seen below, where the output signal is slightly disfigured. 

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab6/High%20Power%20Control/scope_4.png)

# Overall
Once the experiment was completed, the results were analyzed to see which switch is better in a situation which uses a microprocessor. 
 Since each type of switch draws no current, it is mostly up to maximum operating frequency. In this case, the low side switch has a higher maximum 
 operating frequency than the relay. Because of this, the low side switch is favorable in this situation.  
