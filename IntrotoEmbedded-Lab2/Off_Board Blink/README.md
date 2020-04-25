# Off Board Blink
This section of the lab was implemented using only the MSP430G2553 because it has a removable processor. No new code was written. Instead, the code for Simple Blink was implemented.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab2/Off_Board%20Blink/Offboard%20Blink.gif)

## Circuitry 
The circuit was constructed with 3 capacitors. The bulk and bypass capacitors were used to prevent a voltage spike or drop. Since the voltage supplied by the power supply is not always constant the bulk and bypass capacitors make sure that the voltage going to the Vcc pin of the processor remains regulated. The other capacitor in parallel with the reset button is used simliarly to the bulk and bypass. When the button is pressed Vcc is given to the RST pin on the processor. The capacitor holds a charge after the button is depressed to make sure that the RST pin gets Vcc long enough to actually reset the program. The high side PMOS switch was used to increase the current output by the processor from 6mA to the required 20mA to light the LED.

![alt text](https://github.com/tomasu10/Embedded-Systems-Projects-/blob/master/IntrotoEmbedded-Lab2/Off_Board%20Blink/Circuit.PNG)
