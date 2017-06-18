/*******************************************************************
 *  buttons.c
 *
 *  - Set of functions to initialise buttons and deal with button pushes
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 ********************************************************************/
#include "buttons.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/tm4c123gh6pm.h"

// *******************************************************
// *    Globals
// *******************************************************
static bool but_state[NUM_BUTS];
static uint8_t but_count[NUM_BUTS];
static bool but_flag[NUM_BUTS];
static bool but_normal[NUM_BUTS];

// ****************************************************************
// *  Function to Initialise the variables and pins for the buttons
// ****************************************************************
void
initButtons (void)
{
	int i;

	// UP button (active HIGH)
    SysCtlPeripheralEnable (UP_BUT_PERIPH);
    GPIOPinTypeGPIOInput (UP_BUT_PORT_BASE, UP_BUT_PIN);
    GPIOPadConfigSet (UP_BUT_PORT_BASE, UP_BUT_PIN, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);
    but_normal[UP] = UP_BUT_NORMAL;

	// DOWN button (active HIGH)
    SysCtlPeripheralEnable (DOWN_BUT_PERIPH);
    GPIOPinTypeGPIOInput (DOWN_BUT_PORT_BASE, DOWN_BUT_PIN);
    GPIOPadConfigSet (DOWN_BUT_PORT_BASE, DOWN_BUT_PIN, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);
    but_normal[DOWN] = DOWN_BUT_NORMAL;

    // LEFT button (active LOW)
   SysCtlPeripheralEnable (LEFT_BUT_PERIPH);
   GPIOPinTypeGPIOInput (LEFT_BUT_PORT_BASE, LEFT_BUT_PIN);
   GPIOPadConfigSet (LEFT_BUT_PORT_BASE, LEFT_BUT_PIN, GPIO_STRENGTH_2MA,
	  GPIO_PIN_TYPE_STD_WPU);
   but_normal[LEFT] = LEFT_BUT_NORMAL;

   // RIGHT button (active LOW)
   SysCtlPeripheralEnable (RIGHT_BUT_PERIPH);
   //---Unlock PF0 for the right button:
   GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
   GPIO_PORTF_CR_R |= GPIO_PIN_0; //PF0 unlocked
   GPIO_PORTF_LOCK_R = GPIO_LOCK_M;
   GPIOPinTypeGPIOInput (RIGHT_BUT_PORT_BASE, RIGHT_BUT_PIN);
   GPIOPadConfigSet (RIGHT_BUT_PORT_BASE, RIGHT_BUT_PIN, GPIO_STRENGTH_2MA,
	  GPIO_PIN_TYPE_STD_WPU);
   but_normal[RIGHT] = RIGHT_BUT_NORMAL;


   // MODE button (active HIGH)
  SysCtlPeripheralEnable (MODE_BUT_PERIPH);
  GPIOPinTypeGPIOInput (MODE_BUT_PORT_BASE, MODE_BUT_PIN);
  GPIOPadConfigSet (MODE_BUT_PORT_BASE, MODE_BUT_PIN, GPIO_STRENGTH_2MA,
	  GPIO_PIN_TYPE_STD_WPD);
  but_normal[MODE] = MODE_BUT_NORMAL;

	for (i = 0; i < NUM_BUTS; i++)
	{
		but_state[i] = but_normal[i];
		but_count[i] = 0;
		but_flag[i] = false;
	}
}

// ************************************************************************
// A function that polls all the buttons and includes a debounce algorithm
// ************************************************************************
void
updateButtons (void)
{
	bool but_value[NUM_BUTS];
	int i;
	// Read the pins; true is HIGH, false is LOW
	but_value[UP] = (GPIOPinRead (UP_BUT_PORT_BASE, UP_BUT_PIN) == UP_BUT_PIN);
	but_value[DOWN] = (GPIOPinRead (DOWN_BUT_PORT_BASE, DOWN_BUT_PIN) == DOWN_BUT_PIN);
	but_value[LEFT] = (GPIOPinRead (LEFT_BUT_PORT_BASE, LEFT_BUT_PIN) == LEFT_BUT_PIN);
	but_value[RIGHT] = (GPIOPinRead (RIGHT_BUT_PORT_BASE, RIGHT_BUT_PIN) == RIGHT_BUT_PIN);
	but_value[MODE] = (GPIOPinRead (MODE_BUT_PORT_BASE, MODE_BUT_PIN) == MODE_BUT_PIN);

	// Iterate through the buttons, updating button variables as required
	for (i = 0; i < NUM_BUTS; i++)
	{
        if (but_value[i] != but_state[i])
        {
        	but_count[i]++;
        	if (but_count[i] >= NUM_BUT_POLLS)
        	{
        		but_state[i] = but_value[i];
        		but_flag[i] = true;	   // Reset by call to checkButton()
        		but_count[i] = 0;
        	}
        }
        else
        	but_count[i] = 0;
	}
}

// *******************************************************
// A function that returns the new button state.
// *******************************************************
uint8_t
checkButton (uint8_t butName)
{
	if (but_flag[butName])
	{
		but_flag[butName] = false;
		if (but_state[butName] == but_normal[butName])
			return RELEASED;
		else
			return PUSHED;
	}
	return NO_CHANGE;
}

// ******************************************************************
// A function that polls the buttons and alters the desired altitude
// ******************************************************************
float alt_button (float alt_desired)
{
	// UP button
	if ((checkButton (UP) == PUSHED) && (alt_desired < ALT_MAX))
	{
		alt_desired += ALT_STEP;
	}

	// DOWN button
	if ((checkButton (DOWN) == PUSHED) && (alt_desired > ALT_MIN))
	{
		alt_desired -=  ALT_STEP;
	}
	return (alt_desired);
}

// ******************************************************************
// A function that polls the buttons and alters the desired yaw
// ******************************************************************
float yaw_button (float yaw_desired)
{
	// LEFT button (CCW)
	if ((checkButton (LEFT) == PUSHED))
	{

		yaw_desired -= YAW_STEP;
	}

	// RIGHT button (CW)
	if ((checkButton (RIGHT) == PUSHED))
	{
		yaw_desired += YAW_STEP;
	}
	return (yaw_desired);
}
