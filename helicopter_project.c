/*******************************************************************
 *  helicopter_project.c
 *
 *  - The main program for the ENCE361 helicopter project
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 */

//*******************************************************************
//    *    Includes
//*******************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "circBufT.h"
#include "stdlib.h"
#include "stdio.h"
#include "OrbitOLEDInterface.h"
#include "draw_display.h"
#include "driverlib/pwm.h"
#include "alt_ADC.h"
#include "buttons.h"
#include "Inits.h"
#include "PWM_rotors.h"
#include "control_system.h"
#include "yaw_functions.h"

//************************************************************************
//        *     Constants
//************************************************************************
#define LANDED           0				// Landed state
#define TAKEOFF          1				// Takeoff state
#define FLYING           2				// Flying state
#define REFERENCE        GPIO_PIN_4		// Reference GPIO pin
#define STARTING_HEIGHT  10;		    // Heli starting desired height

//*****************************************************************************************
//        *      Globals
//*****************************************************************************************

uint32_t milliseconds_passed = 0;	// Milliseconds passed, calculated using systick

//************************************************************************
//     *    The interrupt handler for the SysTick interrupt.
//************************************************************************
void
SysTickIntHandler (void)
{
	milliseconds_passed++;  // systick it running at 100Hz therefore every interupt occurs every 1 millisecond
}


//************************************************************************************
//      *     Main Program
//************************************************************************************

int main(void)

{
    //    *  Initialisations
    //**************************************

	initPins();    	 	// Initialise yaw/alititude pins.

	initDisplay(); 		// Initialise the display functions

	initSysTick ();		// Initialise System Ticks for scheduling

	initAltADC ();		// Initialise the ADC for altitude

	MainRotorPWM ();	// Initialise the main rotor PWM

	TailRotorPWM (); 	// Initialise the tail rotor PWM

    initButtons ();		// Initialise the buttons

    // Local strings for state display
    char *flying = "FLYING";
    char *takeoff = "TAKE OFF";
    char *landed = "LANDED";
    char *mode_string = landed;

    // Local Variables
    float alt_desired = 0;
    float yaw_desired = 0;
    float yaw_actual = 0;
    float alt_actual = 0;
    uint32_t main_duty_ui32 = 0;
    uint32_t tail_duty_ui32 = 0;
    uint32_t heli_state = LANDED;
	uint8_t butState;

	IntMasterEnable (); // Enable interupts

    //*****************************************************************************
    //    *   Main Loop
	//
	//		- loops forever, continuously monitoring yaw and altitude
	//		  and using this feedback to control the helicopter.
    //*****************************************************************************

    while(1)
    {

        //    *  State machine to determine what tasks the helicopter should be executing
        //*********************************************************************************

    	// In the landed state, do nothing until the the mode switch is flicked to on
    	if (heli_state == LANDED)
    	{
    		butState = checkButton (MODE);
    		switch (butState)
    		{
    		case PUSHED:
    				mode_string = takeoff;
    				heli_state = TAKEOFF;  // Set the state to takeoff after the switch had been turned on
    		}
    	}

    	// In the flying state, find the reference, then reset the yaw and move to flying state when reached.
    	// - Don't allow button pushes while taking off
		else if (heli_state == TAKEOFF)
    	{
			// Set the duty cycles for finding the reference
			main_duty_ui32 = 15;
			tail_duty_ui32 = 25;

			GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, REFERENCE);
			if (GPIOPinRead(GPIO_PORTC_BASE, REFERENCE) == 0) // Checking button state
			{
				heli_state = FLYING; // Set the state to flying when reference has been reached
				mode_string = flying;
				yaw_actual = 0;      // Reset yaw and altitude
				yaw_desired = 0;
				alt_desired = 0;
			}
    	}

    	// In the flying state, continuously poll for button pushes and if the switch has been set to landing position (released)
    	else if (heli_state == FLYING)
		{
			updateButtons ();
			alt_desired =  alt_button (alt_desired);
		    yaw_desired =  yaw_button (yaw_desired);
			butState = checkButton (MODE);
			switch (butState)
			{
			case RELEASED:
				heli_state = LANDED;
				mode_string = landed;
				alt_desired = 0;
				yaw_desired = 0;
			}
		}

    	//    *  These tasks occur every loop to keep the various variables up to date
    	//*********************************************************************************
		alt_actual = getAlt(); // Get the actual altitude from the ADC
		yaw_actual = getYaw(); // Get the actaul yaw from the yaw interupt handler

		setMainPWM (main_duty_ui32); // Set the ouput PWM for the main rotor
		setTailPWM (tail_duty_ui32); // Set the ouput PWM for the tail rotor

		main_duty_ui32 = alt_control(alt_desired, alt_actual); // Use a PID controller to calculate the required main rotor duty cycle:
		tail_duty_ui32 = yaw_control(yaw_desired, yaw_actual); // Use a PID controller to calculate the required tail rotor duty cycle:


    	//    *  These tasks utilise SysTick (100Hz) to schedule how often they occur
    	//*********************************************************************************
		// Update the UART every 250 milliseconds (4 times a second)
		if (milliseconds_passed == 250)
		{
			UARTdisplay(yaw_actual, alt_actual, yaw_desired, alt_desired, main_duty_ui32, tail_duty_ui32, mode_string);
		}
		// Update the Orbit display every 500 milliseconds
		if (milliseconds_passed == 500)
		{
			displayVals (yaw_actual, alt_actual, main_duty_ui32, tail_duty_ui32);
			milliseconds_passed = 0;
		}
    }
}

