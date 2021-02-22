/* -----------------------------------------------------------------------------
[FILE NAME]    :	spi.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	22/02/2021

[DESCRIPTION]  :	SPI Driver
------------------------------------------------------------------------------*/

#include "spi.h"

#ifdef INTERRUPT_MODE
/* ----------------------------------------------------------------------------
 *                          Global Variables                                  *
------------------------------------------------------------------------------*/
volatile uint8  g_spiReceivedData;


/* ----------------------------------------------------------------------------
 *                          ISR's Definitions                                 *
	------------------------------------------------------------------------------*/
ISR(SPI_STC_vect){
	g_spiReceivedData = SPDR;
}
#endif

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
------------------------------------------------------------------------------*/
void SPI_initMaster(const Spi_ConfigType * Config_Ptr)
{
	/*------- Configure SPI Master Pins --------
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output 
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ------------------------------------------*/
	DDRB |= (1<<PB4) | (1<<PB5)| (1<<PB7);
	DDRB &= ~(1<<PB6);
	/* enable SPI + enable Master + Data order MSB first*/
	SPCR = (1<<SPE) | (1<<MSTR);
#ifdef INTERRUPT_MODE
	SET_BIT(SPCR,SPIE);
#endif
	/* Insert first 2 bits of the clock in SPR0 & SPR1*/
	SPCR = (SPCR & NUM_TO_CLEAR_FIRST_2_BITS)|\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_6_BITS);
	/* Select Clock Polarity */
	SPCR = (SPCR & NUM_TO_CLEAR_3RD_BIT) |\
			((Config_Ptr -> polarity & NUM_TO_CLEAR_LAST_7_BITS)<<3);
	/* Select Clock Phase*/
	SPCR = (SPCR & NUM_TO_CLEAR_2ND_BIT) |\
			((Config_Ptr -> phase & NUM_TO_CLEAR_LAST_7_BITS)<<2);
	/* Disable double mode */
	CLEAR_BIT(SPSR,SPI2X);
}

void SPI_initSlave(const Spi_ConfigType * Config_Ptr)
{
	/*------- Configure SPI Master Pins --------
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ------------------------------------------*/
	CLEAR_BIT(DDRB,PB4);
	CLEAR_BIT(DDRB,PB5);
	SET_BIT(DDRB,PB6);
	CLEAR_BIT(DDRB,PB7);
	/* enable SPI + disable Master + Data order MSB first*/
	SPCR = (1<<SPE);
#ifdef INTERRUPT_MODE
	SET_BIT(SPCR,SPIE);
#endif
	/* Insert first 2 bits of the clock in SPR0 & SPR1*/
	SPCR = (SPCR & NUM_TO_CLEAR_FIRST_2_BITS)|\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_6_BITS);
	/* Select Clock Polarity */
	SPCR = (SPCR & NUM_TO_CLEAR_3RD_BIT) |\
			((Config_Ptr -> polarity & NUM_TO_CLEAR_LAST_7_BITS)<<3);
	/* Select Clock Phase*/
	SPCR = (SPCR & NUM_TO_CLEAR_2ND_BIT) |\
			((Config_Ptr -> phase & NUM_TO_CLEAR_LAST_7_BITS)<<2);
	/* Disable double mode */
	CLEAR_BIT(SPSR,SPI2X);
}

void SPI_sendByte(const uint8 data) 
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

void SPI_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
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
uint8 SPI_receiveByte(void)
{
	/*wait until SPI interrupt flag=1(data is receive correctly)*/
	while(BIT_IS_CLEAR(SPSR,SPIF)){}
	/* return the received byte from SPI data register */
	return SPDR;
}

void SPI_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = SPI_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_receiveByte();
	}
	Str[i] = '\0';
}
#endif
