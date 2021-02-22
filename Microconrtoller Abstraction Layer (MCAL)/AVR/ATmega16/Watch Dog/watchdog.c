/* -----------------------------------------------------------------------------
[FILE NAME]    :	watchdog.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	16/02/2021

[DESCRIPTION]  :	Watchdog Timer Driver  
--------------------------------------------------------------------------------*/

#include "watchdog.h"

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/

/* function to enable Watchdog timer.*/
void WDT_ON(Wdt_time a_time){
	// Watchdog timer enables with timeout period 2.1 second.
	SET_BIT(WDTCR,WDE);
	CLEAR_BIT(WDTCR,WDTOE);
	WDTCR = (WDTCR & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(a_time & NUM_TO_CLEAR_LAST_5_BITS);
}

/* function to disable Watchdog timer.*/
void WDT_OFF(void){
	// Set the WDTOE & WDE bits in the same operation
	SET_BIT(WDTCR,WDTOE);
	SET_BIT(WDTCR,WDE);
	// Wait 4 cycles before clear the WDE bit
	_delay_us(4);
	WDTCR &= NUM_TO_CLEAR_FIRST_5_BITS;
}
