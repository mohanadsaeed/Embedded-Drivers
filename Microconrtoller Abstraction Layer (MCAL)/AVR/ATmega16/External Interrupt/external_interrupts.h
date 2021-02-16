/* -----------------------------------------------------------------------------
[FILE NAME]    :	external_interrupts.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	16/02/2021

[DESCRIPTION]  :	Header File to External Interrupts Driver  
--------------------------------------------------------------------------------*/

#ifndef EXTERNAL_INTERRUPTS_H
#define EXTERNAL_INTERRUPTS_H

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/
 typedef enum
{
	LOW_LEVEL,LOGICAL_CHANGE,FALLING_EDGE,RISING_EDGE
}Ei_InterruptEvent;

typedef enum
{
	DEACTIVATE,ACTIVATE
}Ei_PullUp;

typedef struct
{
	Ei_InterruptEvent interruptevent;
	Ei_PullUp pullup;
}Ei_ConfigType;

 
/* -----------------------------------------------------------------------------
 *                           Preprocessor                                      *
  -----------------------------------------------------------------------------*/
  #define NUM_TO_CLEAR_FIRST_2_BITS 0xFC
  #define NUM_TO_CLEAR_LAST_6_BITS 0x2
  #define NUM_TO_CLEAR_SECOND_2_BITS 0xF3
  #define BIT2 2 
  #define NUM_TO_CLEAR_6TH_BITS 0xBF
  #define BIT6 6
  
/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
  -----------------------------------------------------------------------------*/
void INT0_init(const Ei_ConfigType * Config_Ptr);
void INT1_init(const Ei_ConfigType * Config_Ptr);
void INT2_init(const Ei_ConfigType * Config_Ptr);
void INT0_setEvent(const Ei_InterruptEvent a_int0Event);
void INT1_setEvent(const Ei_InterruptEvent a_int1Event);
void INT2_setEvent(const Ei_InterruptEvent a_int2Event);
void INT0_setCallBack(void(*a_ptr)(void));
void INT1_setCallBack(void(*a_ptr)(void));
void INT2_setCallBack(void(*a_ptr)(void));
void INT0_deInit(void);
void INT1_deInit(void);
void INT2_deInit(void);

#endif