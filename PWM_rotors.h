/*
 * PWMRotors.h
 *
 *	Set of functions to initialise and set PWM signals
 *  Created on: May 27, 2017
 *      Author: Robbie Day & Toby Baker
 *
 ******************************************************************/

#ifndef PWM_ROTORS_H_
#define PWM_ROTORS_H_

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

/****************************************************
 * initialiseMainPWM
 * Inits for the main rotor
 ***************************************************/
void initialiseMainPWM(void);

/****************************************************
 * initialiseTailPWM
 * Inits for the tail rotor
 ***************************************************/
void initialiseTailPWM(void);

/****************************************************
*   Function for setting the main rotor PWM
 ***************************************************/
void setMainPWM (uint32_t ui32Duty);

/****************************************************
*   Function for setting up the main rotor PWM
 ***************************************************/
void MainRotorPWM (void);

/****************************************************
*   Function for setting the tail rotor PWM
 ***************************************************/
void setTailPWM (uint32_t ui32Duty);

/****************************************************
*   Function for setting the tail rotor PWM
 ***************************************************/
void TailRotorPWM (void);

#endif /* PWM_ROTORS_H_ */
