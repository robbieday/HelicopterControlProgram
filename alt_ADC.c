/*******************************************************************
 *  alt_ADC.c
 *
 *  - The set of functions to handle altitude ADC
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 */

//*******************************************************************
//    *    Includes
//*******************************************************************
#include "alt_ADC.h"
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
#include "buttons.h"
#include "Inits.h"
#include "PWM_rotors.h"

//*****************************************
//        *     Constants
//*****************************************
#define BUF_SIZE 100			// size of the circular buffer

//***********************************************************
//     *     Globals
//***********************************************************
uint32_t i = 0;
uint32_t j = 0;
uint32_t min_alt = 0;
uint32_t current_alt = 0;
uint32_t sum = 0;
uint32_t ADCValue[1];
uint32_t SETTLING_TIME = 100;
static circBuf_t g_inBuffer;
float alt_actual = 0;

//***********************************************************
//   *  Function to initialise analog to digital conversion
//***********************************************************
void initAltADC (void)
{
	freeCircBuf (&g_inBuffer);   // Initialise buffers and
	initCircBuf(&g_inBuffer, BUF_SIZE);

}

//***********************************************************
// * Function to calculate the altitude and return it to main
//***********************************************************
float getAlt (void)
{
	 // Start the ADC conversion.
	ADCProcessorTrigger(ADC0_BASE, 3);

	// Wait for conversion to be finish.
	while(!ADCIntStatus(ADC0_BASE, 3, false)) {}

	// Clear the ADC interrupt flag
	ADCIntClear(ADC0_BASE, 3);

	// Read ADC Value
	ADCSequenceDataGet(ADC0_BASE, 3, ADCValue);

	writeCircBuf (&g_inBuffer, ADCValue[0]); // Place it in the circular buffer (advancing write index)
	if (j < SETTLING_TIME) // Wait for ADC stability
	{
		j++; }      //increase j until ADC is stable
	if (j == SETTLING_TIME) // Calculate min_alt once ADC has settled
	{
		for (i = 0, sum = 0; i < BUF_SIZE; i++)
				sum += readCircBuf(&g_inBuffer);
		min_alt = (2 * sum + BUF_SIZE) / BUF_SIZE / 2;
		j++; }
	if (j == SETTLING_TIME+1) 		// Calculate running alt_actualitude
	{
		for (i = 0, sum = 0; i < BUF_SIZE; i++)
				sum += readCircBuf(&g_inBuffer);
		current_alt = (2 * sum + BUF_SIZE) / BUF_SIZE / 2;

		if (current_alt > min_alt)
			current_alt = min_alt;
		alt_actual = (min_alt - current_alt)/8;

		if (alt_actual > 100)
			alt_actual = 100;

		else if (alt_actual <= 0)
			alt_actual = 0;
	}
	return (alt_actual);
}
