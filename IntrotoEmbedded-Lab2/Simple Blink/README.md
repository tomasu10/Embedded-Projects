# Simple Blink
Note:  The following explanation will include the SimpleBlink functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab2/Simple%20Blink/Simple%20Blink.gif)

## Explanation
As its title suggests, implementing SimpleBlink in code is quite simple. The most essential 
part of coding SimpleBlink successfully is making sure the the direction and output of the desired port is assigned 
correctly. For example, the LEDs for the MSP430G2553 are found on P1.0 and P1.6. This means that P1DIR had to equal 0x41 in order
to make those two pins outputs. In addition, if you want the LEDs to initally be on you must assign P1OUT to 0x41 as well. 
The other processors would start the same except their respective LED pins would have to be used. As for making the LEDs blink, this 
is done in an infinite while loop that toggles the LEDs. A for loop delay was also added to account for debouncing.
