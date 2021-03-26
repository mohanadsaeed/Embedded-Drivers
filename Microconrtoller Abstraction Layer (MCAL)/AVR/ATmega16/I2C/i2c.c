/* -----------------------------------------------------------------------------
[FILE NAME]    :	i2c.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	01/03/2021

[DESCRIPTION]  :	I2C Driver
------------------------------------------------------------------------------*/

#include "i2c.h"

void TWI_init(const Twi_ConfigType * Config_Ptr)
{
	sint8 twbrValue = (float)(((F_CPU/Config_Ptr->speed)-16)/(2*Config_Ptr->prescalar));
	TWBR = twbrValue;
	TWSR = Config_Ptr->prescalar;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
	TWAR = Config_Ptr->address;

	TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
