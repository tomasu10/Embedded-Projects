# Button Blink
Note:  The following explanation will include the ButtonBlink functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/RU09342/lab-2-blinking-leds-uribet6/blob/master/Button%20Blink/Button%20Blink.gif)

## Explanation
This portion required the implementation of the PxIN and PxREN registers. Since the button is identified as an input its direction had to be set to a 0 in the PxDIR register. Additionally, a pullup 
resistor had to accompany the button using the PxREN register. This allowed the button to go back to a logic level of 1 after the button was depressed (Button is inverted). Once the direction had been set and 
a pullup resistor was assigned to the button, the blink was accomplished by checking the value of PxIN with a conditional statement. For example, for the MSP430G2553, the button was on P1.3 (0x08). With this 
information the P1IN register could be anded with 0x08 in order to see if the button was not pressed. If this conditional statement proved to be true then that meant the button was depressed and the LEDs would turn off.
However, if it was false then that would indicated that the button was pressed and the LEDs would turn on. At the end of loop a for lopp was implemented to account for button bouncing

## Extra Work
The following section was chosen as extra work for Lab2.

This portion was implemented simlarily to ButtonBlink. The main difference is that additional logic had to be used in order to identfy which LED was on. This was done by once again using the PxIN register to determine 
when the button was pressed and depressed. If the button was not pressed then a varible called prevInState was set to a 1. This variable was then used in other if statements that were used to determine which LED was on. For
example, if the green LED was on and prevInState =1 then the red LED would turn on, the green LED would turn off, and prevInState would be set to 0. The purpose of prevInState was to prevent the processor from executing the same line of 
code during another iteration of the infinite while loop while the button was still pressed. Since the proccessor is able to process things at over a million times per second, the prevInState had
to be used in order to prevent the LEDs from toggling multiple times while the button was pressed.