/* -----------------------------------------------------------------------------
[FILE NAME]    :	external_eeprom.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	01/03/2021

[DESCRIPTION]  :	Header File for External EEPROM Driver
------------------------------------------------------------------------------*/


#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPROM_H

#include "std_types.h"

/* ----------------------------------------------------------------------------
 *                      Preprocessor Macros                                   *
  ----------------------------------------------------------------------------*/
#define ERROR 0
#define SUCCESS 1

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
 
#endif 
