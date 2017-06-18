/*
 *  draw_display.h
 *
  *  - Set of functions to display on the orbit and the serial UART terminal
 *   - Created on: 21/03/2017
 *   - Author: Robbie Day & Toby Baker
 */

#ifndef DRAW_DISPLAY_H_
#define DRAW_DISPLAY_H_

//*****************************************************************************
// Includes
//*****************************************************************************

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

//*****************************************************************************
// Function to initialise the LED display
//*****************************************************************************
void initDisplay (void);


//*****************************************************************************
// Function to display the frequency and duty cycle
//*****************************************************************************
void displayVals (float Yaw, float Alt, uint32_t Duty, uint32_t Tail);


//*****************************************************************************
// Function to send info to the UART
//*****************************************************************************
void UARTdisplay(float yaw_actual, float alt_actual, float yaw_desired, float alt_desired, uint32_t main_duty_ui32, uint32_t tail_duty_ui32, char* mode_string);

#endif /* DRAW_DISPLAY_H_ */
