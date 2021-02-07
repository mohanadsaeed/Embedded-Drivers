/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	avr_config.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	07/02/2021

[DESCRIPTION]  :	This file contains all avr libraries 
------------------------------------------------------------------------------------------*/

#ifndef MC_CONFIG_H
#define MC_CONFIG_H

#ifndef F_CPU
#define F_CPU 1000000UL  //1MHz Clock frequency
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif