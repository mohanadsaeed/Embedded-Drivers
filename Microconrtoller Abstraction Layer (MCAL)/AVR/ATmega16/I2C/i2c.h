/* -----------------------------------------------------------------------------
[FILE NAME]    :	i2c.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	01/03/2021

[DESCRIPTION]  :	Header File for I2C Driver
------------------------------------------------------------------------------*/ 


#ifndef I2C_H
#define I2C_H

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/
typedef enum
{
	TWI_100_Kb_S=100000,TWI_400_Kb_S=400000,TWI_1_Mb_s=1000000,\
	TWI_3_4_Mb_s=3400000
}Twi_Speed;

typedef enum
{
	TWI_1,TWI_4,TWI_16,TWI_64
}Twi_Prescalar;

typedef struct
{
	Twi_Speed speed;
	Twi_Prescalar prescalar;
	uint8 address;
}Twi_ConfigType;

/* ----------------------------------------------------------------------------
 *                      Preprocessor Macros                                   *
  ----------------------------------------------------------------------------*/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/
void TWI_init(const Twi_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);


#endif
