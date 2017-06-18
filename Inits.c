/*
 * Inits.c
 *
 *  Set of functions to initialise ports, pins and timers
 *  Created on: May 11, 2017
 *      Author: Robbie Day & Toby Baker
 */
/*******************************************************************
*       Includes.
*******************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uartstdio.h"
#include "utils/ustdlib.h"
#include "circBufT.h"
#include "stdlib.h"
#include "stdio.h"
#include "OrbitOLEDInterface.h"
#include "draw_display.h"
#include "Inits.h"
#include "yaw_functions.h"

/*******************************************************************
*      Contants
*******************************************************************/
#define BUF_SIZE 10				// size of the circular buffer
#define BAUD_RATE 9600			// the Baud rate of the UART
#define UART_CLK_FREQ 16000000  // The UART clock freq. See p.12 of TI migration guide, spma050a
#define DELAY_ MS(ms) SysCtlDelay(SysCtlClockGet() / (3000 / ms)) //delay function
#define SYSTICK_RATE_HZ  100    // System tick rate
#define PWM_DIVIDER_CODE  SYSCTL_PWMDIV_4 // Set the PWM divider code

/************************************************************************
 *     The function for pin initialisations, configuring and enabling
 ************************************************************************/
void
initPins (void)
{
    // Set the clocking to run at 20 MHz (200 MHz / 10) using the PLL.
    SysCtlClockSet(SYSCTL_SYSDIV_10|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	// PERIPHERAL ENABLES
	//*********************************************

    // Enable the port used for input = Port A
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA);

    // Enable the port used for input = Port B
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA);

    // Enable the port used for input = Port C
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOC);

    // Enable the port used for input = Port D
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOD);

    // Enable the port used for input = Port E
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Enable the port used for input = Port F
    SysCtlPeripheralReset (SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);

    // ADC0 needs to be enabled for use of the converter.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	// YAW PHASE PINS
	//*********************************************

    // Register the handler into vector table
    GPIOIntRegister(GPIO_PORTB_BASE, YawIntHandler);

    // Configure the pin used:  input on PB0 (J1-03)
    GPIOPinTypeGPIOInput (GPIO_PORTB_BASE, GPIO_PIN_0);
    GPIOPadConfigSet (GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);

    // Configure the pin used:  input on PB1 (J1-04)
    GPIOPinTypeGPIOInput (GPIO_PORTB_BASE, GPIO_PIN_1);
    GPIOPadConfigSet (GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPD);

    // Set up the pin change interrupt (both edges)
    GPIOIntTypeSet (GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_BOTH_EDGES);
    GPIOIntTypeSet (GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_BOTH_EDGES);

    // Enable the pin change interrupt
    GPIOIntEnable (GPIO_PORTB_BASE, GPIO_PIN_0);
    // Enable the pin change interrupt
    GPIOIntEnable (GPIO_PORTB_BASE, GPIO_PIN_1);

    SysCtlPWMClockSet(PWM_DIVIDER_CODE);

	// ALTITUDE PIN
	//*********************************************

    // Register Handler into the int vector table
    //ADCIntRegister(GPIO_PORTE_BASE, 3, ADCIntHandler);

    // Choosing analog ADC function for PIN_4(PE4).
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);

    // Enable the ADC sequencer
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    // Configure the ADC sequencer for input channel 9.
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);

    // Enable sample sequence 3 for use.
    ADCSequenceEnable(ADC0_BASE, 3);

    // Clear interrupt status flag.
    ADCIntClear(ADC0_BASE, 3);

	// Enable GPIO port A which is used for UART0 pins.

	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);

	// Enable UART0 so that we can configure the clock.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	// Use the internal 16MHz oscillator as the UART clock source.
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	// Select the alternate (UART) function for these pins.
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Initialize the UART for console I/O.
	UARTStdioConfig(0, BAUD_RATE, UART_CLK_FREQ);

    // Configure the pin used:  input on PC4 (J1-03)
    GPIOPinTypeGPIOInput (GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPadConfigSet (GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPU);
}

//********************************************************
// Initialisation for SysTick
//********************************************************
void
initSysTick (void)
{

    // Set up the period for the SysTick timer.  The SysTick timer period is
    // set as a function of the system clock.
    SysTickPeriodSet (SysCtlClockGet () / SYSTICK_RATE_HZ);

    // Register the interrupt handler
    SysTickIntRegister (SysTickIntHandler);

    // Enable interrupt and device
    SysTickIntEnable ();
    SysTickEnable ();
}
