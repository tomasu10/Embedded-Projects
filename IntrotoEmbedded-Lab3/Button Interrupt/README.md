# Button Interrupt
Note:  The following explantion will include the ButtonInterrupt functionality for all processors since the logic does not vary between the MSP430s.

## Explanation
The previous lab focused on using polling to continously check the value of PxIN to see if the button had been pressed. However, that results in the processor spending a lot of time
checking something that has not changed. For this reason, interrupts were used in the following section. This was done by implementing the PxIE which enables the interrupt and PxIES which set
the edge of the interrupt. For example, for the MSP430G2553, P1IE and P1IES were both set to BIT3 because that value correlates to the button. Simply put, since these two registers were assigned to the
button, whenever the button changed from a value of 1 to 0 the P1IES would trigger an interrupt since it was set from hi-to-lo. Within the button interrupt, the only logic that was used was to toggle the LEDs.
Once the LEDs toggled, a for loop would run to handle debouncing and then the interrupt would be cleared using the P1IFG register. This register is very important as the processor will not exit the interrupt if 
the interrupt flag is not cleared.

## Extra Work
This section was implemented on the MSP430FR5994. An extra button was added to turn on/off an LED. Each button controlled one LED and was able to function independent of the other button.
This was done by using the P5IFG register to identify which button triggered the interrupt. A conditional statement checked to see which flag was raised by checking the value of P5IFG.
If P5.6 fired the interrupt then the red LED would trigger and if P5.5 fired the interrupt then the green LED would toggle.