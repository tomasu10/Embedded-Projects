# Software PWM
Note:  The following explanation will include the SoftwarePWM functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab4/Software%20PWM/PWM.gif)

## Explanation
The SoftwarePWM was implemented by using one timer that triggered two timer interrupts. This was done by declaring two CCRX registers (CCR0 and CCR1). CCR0 and CCR1 were both set to 1000 and 500 respectively
to begin at a 50% duty cycle. CCR0 determined the period of the cycle while CCR1 was used to determine how long the LED would be on compared to how long it would be off. The duty cycle 
was changed using the button. Every time the button was pressed the duty cycle increased by 10%. Once the duty cycle reached 100% it was reset to 0%. This was done within the PortX interrupt 
by simply using a conditional statement to see if CCR1 equaled 1000 (Period of cycle). If CCR1 did equal 1000, meaning that there was a 100% duty cycle then CCR1 was reset to 0. If CCR1 was below
1000 it incremented by 100. As for the two timer interrupts, the one triggered by CCR0 turned the LED on while the one triggered by CCR1 turned it off. Since CCR1 increased every time the
button was pressed this caused the duty cycle to effectively change.
