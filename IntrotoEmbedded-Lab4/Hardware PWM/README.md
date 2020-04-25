# Hardware PWM
Note:  The following explanation will include the HardwarePWM functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab4/Hardware%20PWM/PWM.gif)

## Explanation
Although the HardwarePWM required the use of one timer and two CCRx, just like the SoftwarePWM, it did not require timer interrupts. Instead, the Timer was output to one of the available pins
, in this case being the LED. This was done by implementing the PxSELx register. Using this register the timer's clock signal could be sent to the LED. A button interrupt was added
to vary the duty cycle of the LED. Like the SoftwarePWM, everytime a button was pressed the duty cycle increased by 10% until it reached 100%. Once it reached 100% the duty cycle reset back 
to 0%. The most important aspect of this section was determining exactly what SEL register had to be used for each processor. For example, on some boards the timers could not be output to
one of the LEDs so the datasheet for each Development board had to be checked to see what values could be output to each pin.
