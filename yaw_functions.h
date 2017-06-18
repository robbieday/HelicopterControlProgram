/*
 * yaw_functions.c
 *
 *	Set of functions for the continuous monitoring of yaw
 *  Created on: May 31, 2017
 *      Authors: Robbie Day & Toby Baker
 */


#ifndef YAW_FUNCTIONS_H_
#define YAW_FUNCTIONS_H_

//*******************************************************************
//    *    Includes
//*******************************************************************
#include <stdbool.h>
#include <stdint.h>

/************************************************************************
 *     Sends actual yaw to the main loop for use in control and display
 ************************************************************************/
float getYaw (void);

/************************************************************************
 *     The interrupt handler for the for the Yaw pin change interrupts.
 ************************************************************************/
void YawIntHandler (void);


#endif /* YAW_FUNCTIONS_H_ */
