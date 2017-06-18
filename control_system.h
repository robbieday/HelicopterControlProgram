/*******************************************************************
 *  control_system.h
 *
 *  - Set of functions containing the PID controllers for yaw and altitude
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 ********************************************************************/


#ifndef CONTROL_SYSTEM_H_
#define CONTROL_SYSTEM_H_

#include <stdbool.h>
#include <stdint.h>

// Define the max/min PWM values
#define PWM_DUTY_MIN    2
#define PWM_DUTY_MAX    98

//***********************************************************
//     *     Control Functions
//***********************************************************
uint32_t alt_control (float alt_desired, float alt_actual);

uint32_t yaw_control (float yaw_desired, float yaw_actual);

#endif /* CONTROL_SYSTEM_H_ */
