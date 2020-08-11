/*
 * lcdspi.c
 *
 *  Created on: Dec 14, 2017
 *      Author: Tanner
 */

#include "driverlib.h"
#include "lcdspi.h"

void LCDSPI_Init(int command){

    //Set P5.7 as an output pin.
    /*

     * Select Port 5
     * Set Pin 7 as output
     */
    GPIO_setAsOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN7
    );
    //Set P5.7 as Output Low.
    /*

    * Select Port 5
    * Set Pin 7 to output Low.
    */
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P5,
        GPIO_PIN7
    );


    // Configure SPI pins
    // Configure Pins for UCA0CLK

    /*

    * Select Port 5
    * Set Pin 6 to input Primary Module Function, (UCA2CLK).
    */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN6,
        GPIO_PRIMARY_MODULE_FUNCTION
    );
    // Configure Pins for UCA2SIMO
    //Set P1.6, P1.7 as Primary Module Function Input.
    /*

    * Select Port 5
    * Set Pin 4 to input Primary Module Function, (UCA2SIMO).
    */
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN4,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();
    if(command){

        //Initialize Master
        EUSCI_A_SPI_initMasterParam param = {0};
        param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_ACLK;
        param.clockSourceFrequency = CS_getACLK();
        param.desiredSpiClock = 500000;
        param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
        param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;//EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
        param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
        param.spiMode = EUSCI_A_SPI_3PIN;
        EUSCI_A_SPI_initMaster(EUSCI_A2_BASE, &param);

    }
    else{

        //Initialize Master
        EUSCI_A_SPI_initMasterParam param = {0};
        param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_ACLK;
        param.clockSourceFrequency = CS_getACLK();
        param.desiredSpiClock = 500000;
        param.msbFirst = EUSCI_A_SPI_LSB_FIRST;
        param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;//EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
        param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
        param.spiMode = EUSCI_A_SPI_3PIN;
        EUSCI_A_SPI_initMaster(EUSCI_A2_BASE, &param);

    }
    //Enable SPI module
    EUSCI_A_SPI_enable(EUSCI_A2_BASE);

    EUSCI_A_SPI_clearInterrupt(EUSCI_A2_BASE,
            EUSCI_A_SPI_RECEIVE_INTERRUPT
            );

    //Wait for slave to initialize
    __delay_cycles(100);

}

void LCDSPI_Transmit(unsigned char d){

    //USCI_B0 TX buffer ready?
    while (!EUSCI_A_SPI_getInterruptStatus(EUSCI_A2_BASE,
              EUSCI_A_SPI_TRANSMIT_INTERRUPT)) ;

    //Transmit Data to slave
    EUSCI_A_SPI_transmitData(EUSCI_A2_BASE, d);

}


