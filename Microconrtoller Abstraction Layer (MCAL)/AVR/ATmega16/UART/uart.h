/* -----------------------------------------------------------------------------
[FILE NAME]    :	UART.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	19/02/2021

[DESCRIPTION]  :	Header File for UART Driver
------------------------------------------------------------------------------*/

#ifndef UART_H
#define UART_H

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/

typedef enum{
	UART_5_BIT,UART_6_BIT,UART_7_BIT,UART_8_BIT
}Uart_DataBits;

typedef enum{
	UART_DISABLE_PARITY,UART_EVEN_PARITY,UART_ODD_PARITY
}Uart_ParityType;

typedef enum{
	UART_1_BIT,UART_2_BIT
}Uart_StopBits;

typedef struct{
	uint16 baudRate;
	Uart_DataBits dataBits;
	Uart_ParityType parityType;
	Uart_StopBits stopBits;
}Uart_ConfigType;

/* -----------------------------------------------------------------------------
 *                      Preprocessor Macros                                    *
 ------------------------------------------------------------------------------*/
#define INTERRUPT_MODE
#define NUM_TO_CLEAR_2ND_BIT 0xFB
#define NUM_TO_CLEAR_FIRST_2_BITS_LAST_5_BITS 0x04
#define NUM_TO_CLEAR_1ST_2ND_BITS 0xF9
#define NUM_TO_CLEAR_LAST_6_BITS 0x03
#define NUM_TO_CLEAR_LAST_5_BITS 0x07
#define NUM_TO_CLEAR_4TH_5TH_BITS 0xCF

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
------------------------------------------------------------------------------*/
void UART_init(const Uart_ConfigType * Config_Ptr);

void UART_sendByte(const uint8 data);
void UART_sendString(const uint8 *Str);


#ifdef POLLING_MODE
uint8 UART_receiveByte(void);
void UART_receiveString(uint8 *Str); // Receive until #
#endif

#endif
