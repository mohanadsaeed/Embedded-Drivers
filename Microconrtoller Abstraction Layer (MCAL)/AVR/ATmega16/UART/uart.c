/* -----------------------------------------------------------------------------
[FILE NAME]    :	UART.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	19/02/2021

[DESCRIPTION]  :	UART Driver
------------------------------------------------------------------------------*/

#include "UART.h"

#ifdef INTERRUPT_MODE
/* ----------------------------------------------------------------------------
 *                          Global Variables                                  *
------------------------------------------------------------------------------*/
volatile uint8  g_uartReceivedData;

/* ----------------------------------------------------------------------------
 *                          ISR's Definitions                                 *
	------------------------------------------------------------------------------*/
ISR(USART_RXC_vect){
	g_uartReceivedData = UDR;
}
#endif

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
------------------------------------------------------------------------------*/
void UART_init(const Uart_ConfigType * Config_Ptr)
{
	/*Calculating Baud-rate pre-scaler*/
	uint16 ubrr=(F_CPU/((Config_Ptr -> baudRate)*8UL))-1;
	/* U2X = 1 for double transmission speed */
	SET_BIT(UCSRA,U2X);
	CLEAR_BIT(UCSRA,MPCM);

	/*-------------------------- UCSRB Description ----------------------------
	 * RXCIE = 0 Disable UART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable UART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable UART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ------------------------------------------------------------------------*/
	UCSRB = (1<<RXEN) | (1<<TXEN);

#ifdef INTERRUPT_MODE
	SET_BIT(UCSRB,RXCIE);
#endif
	UCSRB = (UCSRB & NUM_TO_CLEAR_2ND_BIT) |\
			(Config_Ptr -> dataBits & NUM_TO_CLEAR_FIRST_2_BITS_LAST_5_BITS);

	/*-------------------------- UCSRC Description ----------------------------
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ------------------------------------------------------------------------*/
	SET_BIT(UCSRC,URSEL);
	CLEAR_BIT(UCSRC,UMSEL);
	UCSRC = (UCSRC & NUM_TO_CLEAR_1ST_2ND_BITS) |\
			((Config_Ptr -> dataBits & NUM_TO_CLEAR_LAST_6_BITS)<<1);
	UCSRC = (UCSRC & NUM_TO_CLEAR_4TH_5TH_BITS) |\
			((Config_Ptr -> parityType & NUM_TO_CLEAR_LAST_6_BITS)<<4);
	if (Config_Ptr -> stopBits == UART_2_BIT){
		SET_BIT(UCSRC,USBS);
	}
	else{
		CLEAR_BIT(UCSRC,USBS);
	}
	CLEAR_BIT(UCSRC,UCPOL);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr>>8;
	UBRRL = ubrr;
}

void UART_sendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
	/*---------------------- Another Method ---------------------------
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	-----------------------------------------------------------------*/
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/*---------------------- Another Method ---------------------------
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	-----------------------------------------------------------------*/
}

#ifdef POLLING_MODE
uint8 UART_receiveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR;
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
#endif
