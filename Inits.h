/*
 * Inits.h
 *
 *  Set of functions to initialise ports, pins and timers
 *  Created on: May 11, 2017
 *      Author: Robbie Day & Toby Baker
 */
//*******************************************************************
//            Includes.
//*******************************************************************

#ifndef INITS_H_
#define INITS_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "circBufT.h"
#include "stdlib.h"
#include "stdio.h"
#include "OrbitOLEDInterface.h"
#include "draw_display.h"
#include "Inits.h"

//*****************************************************************************
// Function to monitor yaw.
//*****************************************************************************

/************************************************************************
 *     The function for pin initialisations, configuring and enabling
 ************************************************************************/
void initPins (void);

//********************************************************
// Initialisation for SysTick
//********************************************************
void initSysTick (void);

//********************************************************
// Decleration for yaw interupt handler function
//********************************************************
void YawIntHandler (void);

//********************************************************
// Decleration for system tick interupt handler function
//********************************************************
void SysTickIntHandler (void);

#endif /* INITS_H_ */
