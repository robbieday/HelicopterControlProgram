/*******************************************************************
 *  alt_ADC.c
 *
 *  - The set of functions to handle altitude ADC
 *  - Created on: 21/03/2017
 *  - Author: Robbie Day & Toby Baker
 *
 **/

#ifndef ALTADC_H_
#define ALTADC_H_

//*******************************************************************
//    *    Includes
//*******************************************************************/
#include <stdint.h>
#include <stdbool.h>

//***********************************************************
//   *  Function to initialise analog to digital conversion
//***********************************************************
void initAltADC (void);

//***********************************************************
// * Function to calculate the altitude and return it to main
//***********************************************************
float getAlt (void);

#endif /* ALTADC_H_ */
