/*
 *  draw_display.c
 *
  *  - Set of functions to display on the orbit and the serial UART terminal
 *   - Created on: 21/03/2017
 *   - Author: Robbie Day & Toby Baker
 */

//*******************************************************************
// Includes
//*******************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "stdio.h"
#include "stdlib.h"
#include "OrbitOLEDInterface.h"
#include "circBufT.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"

//*****************************************************************************
// Function to initialise the LED display
//*****************************************************************************
void
initDisplay (void)
{
  // intialise the Orbit OLED display
    OLEDInitialise ();
}

//*****************************************************************************
// Function to display values on the orbit
//*****************************************************************************
void
displayVals (float Yaw, float Alt, uint32_t Duty, uint32_t Tail)
{

	uint32_t ui32Yaw = Yaw + 0.5;
	uint32_t ui32Alt = Alt + 0.5;

    /* Create char array variables to be drawn
    *   Syntax: char "Variable Name"[Length of char to be drawn, max width = 17)]
    */

    char yaw[17];
    char alt[17];
    char duty[17];
    char tail[17];

    /* Create strings to draw using sprintf,
    *   Syntax: sprintf ("Text + Any Format Specifiers For Data", *DATA*);
    */
    sprintf (yaw, "Yaw = %d deg    ", ui32Yaw);
    sprintf (alt, "Alt = %d %c   ",  ui32Alt, 0x25);
    sprintf (duty, "Main = %d %c   ",  Duty, 0x25);
    sprintf (tail, "Tail = %d %c   ",  Tail, 0x25);


    /* Draw strings to the LED interface
    *   Syntax:  OLEDStringDraw ("Variable Name", *Left_Alignment (0-17)*, * Distance From Top (0-3)* );
    */
    OLEDStringDraw (yaw, 0, 0);
    OLEDStringDraw (alt, 0, 1);
    OLEDStringDraw (duty, 0, 2);
    OLEDStringDraw (tail, 0, 3);

}

//*****************************************************************************
// Function to send info to the UART
//*****************************************************************************
void
UARTdisplay(float yaw_actual, float alt_actual, float yaw_desired, float alt_desired, uint32_t main_duty_ui32, uint32_t tail_duty_ui32, char* mode_string)
{
		// Convert the required variables from floats to ints
		uint32_t alt_desired_ui32 = alt_desired + 0.5;
		uint32_t alt_actual_ui32 = alt_actual + 0.5;
		uint32_t yaw_desired_ui32 = yaw_desired + 0.5;
		uint32_t yaw_actual_ui32 = yaw_actual + 0.5;

		// Print to the serial UART terminal
		UARTprintf("Altitude: %2d [%2d]\n", alt_actual_ui32, alt_desired_ui32);
		UARTprintf("Yaw: %2d [%2d]\n", yaw_actual_ui32, yaw_desired_ui32);
		UARTprintf("Main: %2d\n", main_duty_ui32);
		UARTprintf("Tail: %2d\n", tail_duty_ui32);
		UARTprintf("Mode: %s\n", mode_string);
}


