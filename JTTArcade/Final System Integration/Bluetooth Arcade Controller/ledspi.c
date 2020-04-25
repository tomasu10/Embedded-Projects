#include "driverlib.h"

void LEDSPI_Transmit(int data);
void LEDSPI_Init();


void LEDSPI_Transmit(int data){
        //USCI_B0 TX buffer ready?
        while (!EUSCI_B_SPI_getInterruptStatus(EUSCI_B1_BASE,
                  EUSCI_B_SPI_TRANSMIT_INTERRUPT)) ;

        //Transmit Data to slave
        EUSCI_B_SPI_transmitData(EUSCI_B1_BASE, data);
}

void LEDSPI_Init(){

    volatile uint16_t i;

    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    //Set P1.0 as an output pin.
    /*

     * Select Port 1
     * Set Pin 0 as output
     */
    GPIO_setAsOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN3
    );
    //Set P1.0 as Output Low.
    /*

    * Select Port 1
    * Set Pin 0 to output Low.
    */
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P3,
        GPIO_PIN3
    );

   /*
    * Select Port 5
    * Set Pin 2 to input Secondary Module Function, (UCB0CLK).
    */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN2,
        GPIO_PRIMARY_MODULE_FUNCTION
    );
    // Configure Pins for UCB0TXD/UCB0SIMO, UCB0RXD/UCB0SOMI
    //Set P1.6, P1.7 as Secondary Module Function Input.
    /*

    * Select Port 1
    * Set Pin 6, 7 to input Secondary Module Function, (UCB0TXD/UCB0SIMO, UCB0RXD/UCB0SOMI).
    */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN0 + GPIO_PIN1,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    //Initialize Master
    EUSCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_B_SPI_CLOCKSOURCE_ACLK;
    param.clockSourceFrequency = CS_getACLK();
    param.desiredSpiClock = 500000;
    param.msbFirst = EUSCI_B_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;//EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
    param.spiMode = EUSCI_B_SPI_3PIN;
    EUSCI_B_SPI_initMaster(EUSCI_B1_BASE, &param);

    //Enable SPI module
    EUSCI_B_SPI_enable(EUSCI_B1_BASE);

    EUSCI_B_SPI_clearInterrupt(EUSCI_B1_BASE,
            EUSCI_B_SPI_RECEIVE_INTERRUPT
            );

    //Wait for slave to initialize
    __delay_cycles(100);

}
