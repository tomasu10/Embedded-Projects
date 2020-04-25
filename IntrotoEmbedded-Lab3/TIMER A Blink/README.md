# TIMER A Blink
Note:  The following explanation will include the TimerABlink functionality for all processors since the logic does not vary between the MSP430s.

## Explanation
This portion of Lab 3 introduced the use of Timers and Timer Interrupts. Like Lab2:MultipleBlinks, the code written for this section blinked the two LEDs at different rates.
When a Timer is enabled it is able to run off multiple clocks and multiple modes. SMCLK and Continuous mode was used for this section. In order to actually trigger the timer interrupts, CCRx values had to be set.
For example, for the MSP430G2553 CCR1 and CCR2 were use in order to trigger two interrupts. This allowed the green and red LEDs to blink at two different times by assigning one to CCR1 and CCR2 respectively.
It is also important to note that within the interrupt the register TA0IV had to be used. The reason for this is because TA0IV allows you to access CCR1 and CCR2. In code, this 
can be done in a switch case that uses both case 2 and 4 (Bits of TA0IV that hold CCR1 and 2 respectively). By implementing a switch case in the interrupt, the corresponding LEDs were toggled and furthermore
the value of the CCRx register was added to itself to account for an offset. The offset was important because without it the capture/compare registers  would not trigger at their intended value since the clock
was in continous mode.