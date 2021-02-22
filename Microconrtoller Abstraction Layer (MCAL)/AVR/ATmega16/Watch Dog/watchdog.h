/* -----------------------------------------------------------------------------
[FILE NAME]    :	watchdog.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	16/02/2021

[DESCRIPTION]  :	Header File to Watchdog Timer Driver  
--------------------------------------------------------------------------------*/

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/
 typedef enum
{
	t_16_3_ms,t_32_5_ms,t_65_ms,t_0_13_s,t_0_26_s,t_0_52_s,t_1_s,t_2_1_s
}Wdt_time;
 
/* -----------------------------------------------------------------------------
 *                           Preprocessor                                      *
  -----------------------------------------------------------------------------*/
  #define NUM_TO_CLEAR_FIRST_3_BITS 0xF8
  #define NUM_TO_CLEAR_LAST_5_BITS 0x07
  #define NUM_TO_CLEAR_FIRST_5_BITS 0xE0
  
/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
  -----------------------------------------------------------------------------*/
/* function to enable Watchdog timer.*/
void WDT_ON(Wdt_time a_time);

/* function to disable Watchdog timer.*/
void WDT_OFF(void);


#endif
