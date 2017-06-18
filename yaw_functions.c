/*
 * yaw_functions.c
 *
 *	Set of functions for the continuous monitoring of yaw
 *  Created on: May 31, 2017
 *      Authors: Robbie Day & Toby Baker
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
#include "yaw_functions.h"

/*******************************************
 *      Phase Pins & States
 *******************************************/
//---Main Phases
#define YAW_PHASE_A		GPIO_PIN_0
#define YAW_PHASE_B		GPIO_PIN_1

uint8_t STATE_1 = 00;
uint8_t STATE_2 = 01;
uint8_t STATE_3 = 10;
uint8_t STATE_4 = 11;

//***********************************************************
//     *     Globals
//***********************************************************
float yawActual = 0;
uint8_t current_state = 00;
uint8_t prev_state = 00;
int32_t yaw = 0;


/************************************************************************
 *     Sends actual yaw to the main loop for use in control and display
 ************************************************************************/
float getYaw (void)
{
	return (yawActual);
}

/************************************************************************
 *     The interrupt handler for the for the Yaw pin change interrupts.
 ************************************************************************/
void
YawIntHandler (void)
{
	// Clear Pins
	GPIOIntClear (GPIO_PORTB_BASE, YAW_PHASE_A | YAW_PHASE_B);

	// Read state of pins
	uint8_t Yaw_A  = GPIOPinRead(GPIO_PORTB_BASE, YAW_PHASE_A);
	uint8_t Yaw_B  = GPIOPinRead(GPIO_PORTB_BASE, YAW_PHASE_B);


	if (!Yaw_A && !Yaw_B)
		current_state = STATE_1;

	if (!Yaw_A && Yaw_B)
		current_state = STATE_2;

	if (!Yaw_A && Yaw_B)
		current_state = STATE_3;

	if (Yaw_A && Yaw_B)
		current_state = STATE_4;


	//State change code to monitor yaw:
	//********************************************************
	if (prev_state == STATE_1) {
				if (current_state == STATE_2) {
						yaw++; }
				else if (current_state == STATE_4) {
						yaw--; }
	}

	if (prev_state == STATE_2) {
				if (current_state == STATE_3) {
						yaw++; }
				else if (current_state == STATE_1) {
						yaw--; }
	}

	if (prev_state == STATE_3) {
				if (current_state == STATE_4) {
						yaw++; }
				else if (current_state == STATE_2) {
						yaw--; }
	}

	if (prev_state == STATE_4) {
				if (current_state == STATE_1) {
						yaw++; }
				else if (current_state == STATE_3) {
						yaw--; }
	}
	prev_state = current_state; // Set states for next iteration

	yawActual = yaw*360.0/448.0;
}


