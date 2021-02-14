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
#define BUTTON_PORT_DIR DDRA
#define BUTTON_PIN 5

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
/* -----------------------------------------------------------------------------*/
void BUTTON_init(void);
uint8 BUTTON_isPressed(void);
uint8 BUTTON_isReleased(void);
void BUTTON_PULL_UP_ACTIVATE(void);

#endif
