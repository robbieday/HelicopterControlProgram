/*******************************************************************
 *  control_system.c
 *
 *  - Set of functions containing the PID controllers for yaw and altitude
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 ********************************************************************/

//*******************************************************************
//    *    Includes
//*******************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "control_system.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

//***********************************************************
//     *     Globals
//***********************************************************
float dt = 0.005;   // The loop time constant

// Altitude gains
float AltKp = 0.3;
float AltKi = 0.01;
float AltKd = 0;

// Yaw gains
float YawKp = 0.4;
float YawKi = 0.01;
float YawKd = 0;

// The altitude associated varaibles
float alt_desired = 0;
float alt_error = 0;
float integral_alt_error = 0;
float derivitive_alt_error = 0;
float prev_alt_error = 0;
float main_duty = 0;

// The yaw associated varaibles
float yaw_desired = 0;
float yaw_error = 0;
float integral_yaw_error = 0;
float derivitive_yaw_error = 0;
float prev_yaw_error = 0;
float tail_duty = 0;

// Duty cycle ints - sent to main loop
uint32_t main_duty_u32 = 0;
uint32_t tail_duty_u32 = 0;

//***********************************************************
//     *     Control Functions
//***********************************************************

uint32_t alt_control (float alt_desired, float alt_actual)
{
	// PID Altitude Controller
	alt_error = alt_desired - alt_actual;
	integral_alt_error += alt_error;
	derivitive_alt_error = alt_error - prev_alt_error;
	main_duty = (AltKp * alt_error) + (AltKi * integral_alt_error * dt) + (AltKd * derivitive_alt_error/dt);
	prev_alt_error = alt_error;

	// Check that PID has not exceeded the max/min values
	if (main_duty > PWM_DUTY_MAX)
	{
		main_duty = PWM_DUTY_MAX;
	}
	if (main_duty < PWM_DUTY_MIN)
	{
		main_duty = PWM_DUTY_MIN;
	}

	main_duty_u32 = main_duty + 0.5;

	return (main_duty_u32); // Return calculated duty cycle for the PWM
}


uint32_t yaw_control (float yaw_desired, float yaw_actual)
{

	// PID Yaw Controller
	yaw_error = yaw_desired - yaw_actual;
	integral_yaw_error += yaw_error;
	derivitive_yaw_error = yaw_error - prev_yaw_error;
	tail_duty = YawKp * yaw_error + (YawKi * integral_yaw_error * dt) + (YawKd * derivitive_yaw_error/dt);
	prev_yaw_error = yaw_error;

	// Check that PID has not exceeded the max/min values
	if (tail_duty > PWM_DUTY_MAX)
	{
		tail_duty = PWM_DUTY_MAX;
	}
	if (tail_duty < PWM_DUTY_MIN)
	{
		tail_duty = PWM_DUTY_MIN;
	}

	tail_duty_u32 = tail_duty + 0.5;

	return(tail_duty_u32); // Return calculated duty cycle for the PWM
}
