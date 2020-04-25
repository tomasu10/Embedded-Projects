# Button Based Delay
Note:  The following explanation will include the ButtonBasedDelay functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab3/Button%20Based%20Delay/Button%20Based%20Delay.gif)

## Explanation
This portion of the lab called for the use of both port and timer interrupts. Two timers were actually used in this implementation. One timer (lets call it TimerA) was used to trigger the timer interrupts while
the other was used as a counter whenever the button was pressed (TimerB). NOTE: The names Timer A and TimerB do not refelct the actual timer names that were used in code. TimerB was used to keep track of the amount
of time that the button was pressed. This time was then stored into the CCRX of Timer A which consequently triggered an interrupt whenever the timer reached the duration of the button press. However, the majority of the logic 
was handled in the Portx interrupt. In this interrupt one main thing had to be done in order to save the value of TimerB in TimerA's CCRx. Within the Portx interrupt the interrupt edge had to be flipped.
This caused the interrupt to trigger again once the button was depressed, allowing the value of TimerB to be saved into TimerA. The edge flip was simply used as a way of knowing when the button was pressed or depressed. When the button was
depressed and the interrupt triggered and the value of TimerB was stored into TimerA, the edge was once again flipped to allow the interrupt to fire when the button was pressed again. This logic worked as a loop, constantly flipping edges
depending on if the button was pressed or not.
