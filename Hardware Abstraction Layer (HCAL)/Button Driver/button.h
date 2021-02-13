/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	button.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	11/02/2021

[DESCRIPTION]  :	Header File for Button Driver  
------------------------------------------------------------------------------------------*/
#ifndef BUTTON_H
#define BUTTON_H

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/* -----------------------------------------------------------------------------
 *                      Preprocessor Macros                                    *
 ------------------------------------------------------------------------------*/

/* Button Configuration */
#define PULL_UP

/* Button Port Configurations */
#define BUTTON_PORT_IN PINA
#define BUTTON_PORT_OUT PORTA
#define BUTTON_PIN 5

#define BUTTON_IS_PRESSED /
	#ifdef PULL_UP /
		BIT_IS_CLEAR(BUTTON_PORT_IN,BUTTON_PIN) /
	#endif /
	/
	#ifdef PULL_DOWN /
		BIT_IS_SET(BUTTON_PORTIN,BUTTON_PIN) /
	#endif /
	
#define BUTTON_IS_RELEASED /
	#ifdef PULL_UP /
		BIT_IS_SET(BUTTON_PORTIN,BUTTON_PIN) /
	#endif /
	/
	#ifdef PULL_DOWN /
		BIT_IS_CLEAR(BUTTON_PORT_IN,BUTTON_PIN) /
	#endif /
	
#define BUTTON_PULL_UP_ACTIVATE SET_BIT(BUTTON_PORT_OUT,BUTTON_PIN)



/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
/* -----------------------------------------------------------------------------

/*
 * Function responsible for getting if the button is pressed or not
 */
uint8 BUTTON_isPressed(void);

/*
 * Function responsible for getting if the button is released or not
 */
uint8 BUTTON_isReleased(void);

#endif
