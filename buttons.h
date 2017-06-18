/*******************************************************************
 *  buttons.c
 *
 *  - Set of functions to initialise buttons and deal with button pushes
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 ********************************************************************/
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
// Constants
//*****************************************************************************
enum butNames {UP = 0, DOWN, LEFT, RIGHT, MODE, NUM_BUTS};
enum butStates {RELEASED = 0, PUSHED, NO_CHANGE};
// UP button
#define UP_BUT_PERIPH  SYSCTL_PERIPH_GPIOE
#define UP_BUT_PORT_BASE  GPIO_PORTE_BASE
#define UP_BUT_PIN  GPIO_PIN_0
#define UP_BUT_NORMAL  false
// DOWN button
#define DOWN_BUT_PERIPH  SYSCTL_PERIPH_GPIOD
#define DOWN_BUT_PORT_BASE  GPIO_PORTD_BASE
#define DOWN_BUT_PIN  GPIO_PIN_2
#define DOWN_BUT_NORMAL  false
// LEFT button
#define LEFT_BUT_PERIPH  SYSCTL_PERIPH_GPIOF
#define LEFT_BUT_PORT_BASE  GPIO_PORTF_BASE
#define LEFT_BUT_PIN  GPIO_PIN_4
#define LEFT_BUT_NORMAL  true
// RIGHT button
#define RIGHT_BUT_PERIPH  SYSCTL_PERIPH_GPIOF
#define RIGHT_BUT_PORT_BASE  GPIO_PORTF_BASE
#define RIGHT_BUT_PIN  GPIO_PIN_0
#define RIGHT_BUT_NORMAL  true
// MODE button
#define MODE_BUT_PERIPH  SYSCTL_PERIPH_GPIOA
#define MODE_BUT_PORT_BASE  GPIO_PORTA_BASE
#define MODE_BUT_PIN  GPIO_PIN_7
#define MODE_BUT_NORMAL  false
// Limit/Step Constants
#define ALT_MAX         100
#define ALT_MIN         0
#define ALT_STEP        10
#define YAW_STEP        15
#define NUM_BUT_POLLS 3


// ****************************************************************
// Function to Initialise the variables and pins for the buttons
// ****************************************************************
void initButtons (void);

// ************************************************************************
// A function that polls all the buttons and includes a debounce algorithm
// ************************************************************************
void updateButtons (void);

// *******************************************************
// A function that returns the new button state.
// *******************************************************
uint8_t checkButton (uint8_t butName);

// ******************************************************************
// A function that polls the buttons and alters the desired altitude
// ******************************************************************
float alt_button (float alt_desired);

// ******************************************************************
// A function that polls the buttons and alters the desired yaw
// ******************************************************************
float yaw_button (float yaw_desired);

#endif /*BUTTONS_H_*/
