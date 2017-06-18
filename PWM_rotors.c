/*
 * PWMRotors.c
 *
 *	Set of functions to initialise and set PWM signals
 *  Created on: May 27, 2017
 *      Author: Robbie Day & Toby Baker
 *
 ******************************************************************/

//*******************************************************************
//    *    Includes
//*******************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h" //Needed for pin configure
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

/*******************************************
 *      PWM config details.
 *******************************************/
#define PWM_RATE_HZ  200
#define PWM_START_PC  10
#define PWM_DIVIDER_CODE  SYSCTL_PWMDIV_2
#define PWM_DIVIDER  2

/*******************************************
 *      PWM Hardware Details.
 *******************************************/
//---Main Rotor PWM: M0PWM7,PC5, J4-05
#define PWM_MAIN_BASE			PWM0_BASE
#define PWM_MAIN_GEN			PWM_GEN_3	//covers outputs 6 and 7
#define PWM_MAIN_OUTNUM			PWM_OUT_7
#define PWM_MAIN_OUTBIT			PWM_OUT_7_BIT
#define PWM_MAIN_PERIPH_PWM		SYSCTL_PERIPH_PWM0	//module 0
#define PWM_MAIN_PERIPH_GPIO	SYSCTL_PERIPH_GPIOC
#define PWM_MAIN_GPIO_BASE		GPIO_PORTC_BASE
#define PWM_MAIN_GPIO_CONFIG	GPIO_PC5_M0PWM7
#define PWM_MAIN_GPIO_PIN		GPIO_PIN_5

//---Tail Rotor PWM: M1PWM5,PF5, J3-10
#define PWM_TAIL_BASE			PWM1_BASE
#define PWM_TAIL_GEN			PWM_GEN_2
#define PWM_TAIL_OUTNUM			PWM_OUT_5
#define PWM_TAIL_OUTBIT			PWM_OUT_5_BIT
#define PWM_TAIL_PERIPH_PWM		SYSCTL_PERIPH_PWM1
#define PWM_TAIL_PERIPH_GPIO	SYSCTL_PERIPH_GPIOF
#define PWM_TAIL_GPIO_BASE		GPIO_PORTF_BASE
#define PWM_TAIL_GPIO_CONFIG	GPIO_PF1_M1PWM5
#define PWM_TAIL_GPIO_PIN		GPIO_PIN_1


/****************************************************
 * initialisePWM
 * Inits for the main rotor
 ***************************************************/
void initialiseMainPWM(void)
{
    // Calculate the PWM period corresponding to PWM_RATE_HZ.
    uint32_t ui32Period = SysCtlClockGet() / PWM_DIVIDER / PWM_RATE_HZ;

    // Enable Main PWM Peripheral
    SysCtlPeripheralEnable(PWM_MAIN_PERIPH_PWM);

    GPIOPinConfigure(PWM_MAIN_GPIO_CONFIG);
    GPIOPinTypePWM(PWM_MAIN_GPIO_BASE, PWM_MAIN_GPIO_PIN);

    PWMGenConfigure(PWM_MAIN_BASE, PWM_MAIN_GEN,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_MAIN_BASE, PWM_MAIN_GEN, ui32Period);

    // Set the pulse width for PWM_START_PC % duty cycle.
    PWMPulseWidthSet(PWM_MAIN_BASE, PWM_MAIN_OUTNUM, ui32Period * PWM_START_PC / 100);

    // Enable Main PWM Generation
    PWMGenEnable(PWM_MAIN_BASE, PWM_MAIN_GEN);

    // Disable the output.  Repeat this call with 'true' to turn O/P on.
    PWMOutputState(PWM_MAIN_BASE, PWM_MAIN_OUTBIT, false);
}

/****************************************************
 * initialiseTailPWM
 * Inits for the tail rotor
 ***************************************************/
void initialiseTailPWM(void)
{

    // Calculate the PWM period corresponding to PWM_RATE_HZ.
    uint32_t ui32Period = SysCtlClockGet() / PWM_DIVIDER / PWM_RATE_HZ;

    //Enable Tail PWM Peripheral
    SysCtlPeripheralEnable(PWM_TAIL_PERIPH_PWM);

	GPIOPinConfigure(PWM_TAIL_GPIO_CONFIG);
	GPIOPinTypePWM(PWM_TAIL_GPIO_BASE, PWM_TAIL_GPIO_PIN);

	PWMGenConfigure(PWM_TAIL_BASE, PWM_TAIL_GEN,
					PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_TAIL_BASE, PWM_TAIL_GEN, ui32Period);

	// Set the pulse width for PWM_START_PC % duty cycle.
	PWMPulseWidthSet(PWM_TAIL_BASE, PWM_TAIL_OUTNUM, ui32Period * PWM_START_PC / 100);

    // Enable Tail PWM Generation
	PWMGenEnable(PWM_TAIL_BASE, PWM_TAIL_GEN);

	// Disable the output.  Repeat this call with 'true' to turn O/P on.
	PWMOutputState(PWM_TAIL_BASE, PWM_TAIL_OUTBIT, false);

}

/****************************************************
*   Function for setting the main rotor PWM
 ***************************************************/
void
setMainPWM (uint32_t ui32Duty)
{
	uint32_t ui32Freq = 200;

    // Calculate the PWM period corresponding to the freq.
    uint32_t ui32Period = SysCtlClockGet() / PWM_DIVIDER / ui32Freq;

    PWMGenPeriodSet(PWM_MAIN_BASE, PWM_MAIN_GEN, ui32Period);
    PWMPulseWidthSet(PWM_MAIN_BASE, PWM_MAIN_OUTNUM,
        ui32Period * ui32Duty / 100);
}

/****************************************************
*   Function for setting up the main rotor PWM
 ***************************************************/
void
MainRotorPWM(void)
{
    // Set the PWM clock rate to 10 MHz (which means 80 Hz min rate)
    SysCtlPWMClockSet(PWM_DIVIDER_CODE);

    // As a precaution, make sure that the peripherals used are reset
    SysCtlPeripheralReset(PWM_MAIN_PERIPH_GPIO); //Used for PWM output
    SysCtlPeripheralReset(PWM_MAIN_PERIPH_PWM);  //Main Rotor PWM

    initialiseMainPWM ();

    PWMOutputState(PWM_MAIN_BASE, PWM_MAIN_OUTBIT, true);
}

/****************************************************
*   Function for setting the tail rotor PWM
 ***************************************************/
void
setTailPWM (uint32_t ui32Duty)
{
	uint32_t ui32Freq = 200;

    // Calculate the PWM period corresponding to the freq.
    uint32_t ui32Period = SysCtlClockGet() / PWM_DIVIDER / ui32Freq;

    PWMGenPeriodSet(PWM_TAIL_BASE, PWM_TAIL_GEN, ui32Period);
    PWMPulseWidthSet(PWM_TAIL_BASE, PWM_TAIL_OUTNUM,
        ui32Period * ui32Duty / 100);
}

/****************************************************
*   Function for setting up the tail rotor PWM
 ***************************************************/
void
TailRotorPWM(void)
{
    // Set the PWM clock rate to 10 MHz (which means 80 Hz min rate)
    SysCtlPWMClockSet(PWM_DIVIDER_CODE);

    // As a precaution, make sure that the peripherals used are reset
    SysCtlPeripheralReset(PWM_TAIL_PERIPH_GPIO); //Used for PWM output
    SysCtlPeripheralReset(PWM_TAIL_PERIPH_PWM);  //Main Rotor PWM

    initialiseTailPWM ();

    PWMOutputState(PWM_TAIL_BASE, PWM_TAIL_OUTBIT, true);
}

