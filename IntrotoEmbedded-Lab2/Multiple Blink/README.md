# Multiple Blink
Note:  The following explanation will include the MultipleBlink functionality for all processors since the logic does not vary between the MSP430s.

![alt text](https://github.com/tomasu10/Embedded-Projects/blob/master/IntrotoEmbedded-Lab2/Multiple%20Blink/Multiple%20Blink.gif)

## Explanation
For this section of the lab, conditional statements had to be used inside of an infinite loop. Just like SimpleBlink the Direction and 
Output of the desired LED pins had to be set for each processor. The conditional statements were
used to see if a variable called counter equaled a multiple of 500 or 1600 for the red and green LEDs repectively. This was done by using
the modulo operator to see if the result was 0. If the counter was indeed a multiple of 500 or 1600 the respective LED would toggle. This effectively toggled the two LEDs at two different speeds.
