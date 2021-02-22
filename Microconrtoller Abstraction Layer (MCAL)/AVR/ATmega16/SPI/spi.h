/* -----------------------------------------------------------------------------
[FILE NAME]    :	spi.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	22/02/2021

[DESCRIPTION]  :	Header File for SPI Driver
------------------------------------------------------------------------------*/

#ifndef SPI_H
#define SPI_H

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/

typedef enum{
	SPI_F_CPU_4,SPI_F_CPU_16,SPI_F_CPU_64,SPI_F_CPU_128
}Spi_Clock;

typedef enum{
	SPI_RISING_LEADING_EDGE,SPI_FALLING_LEADING_EDGE
}Spi_ClockPolarity;

typedef enum{
	SPI_SAMPLING_LEADING_EDGE,SPI_SETUP_LEADINGEDGE
}Spi_ClockPhase;

typedef struct{
	Spi_Clock clock;
	Spi_ClockPolarity polarity;
	Spi_ClockPhase phase;
}Spi_ConfigType;

/* -----------------------------------------------------------------------------
 *                      Preprocessor Macros                                    *
 ------------------------------------------------------------------------------*/
#define POLLING_MODE
#define NUM_TO_CLEAR_FIRST_2_BITS  0xFC
#define NUM_TO_CLEAR_LAST_6_BITS 0x03
#define NUM_TO_CLEAR_3RD_BIT 0xF7
#define NUM_TO_CLEAR_LAST_7_BITS 0X01
#define NUM_TO_CLEAR_2ND_BIT 0xFB

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
------------------------------------------------------------------------------*/
void SPI_initMaster(const Spi_ConfigType * Config_Ptr);
void SPI_initSlave(const Spi_ConfigType * Config_Ptr);
void SPI_sendByte(const uint8 data);
void SPI_sendString(const uint8 *Str);


#ifdef POLLING_MODE
uint8 SPI_receiveByte(void);
void SPI_receiveString(uint8 *Str); // Receive until #
#endif

#endif
