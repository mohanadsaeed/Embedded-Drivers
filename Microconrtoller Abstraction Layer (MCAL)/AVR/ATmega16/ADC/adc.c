/* -----------------------------------------------------------------------------
[FILE NAME]    :	adc.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	14/02/2021

[DESCRIPTION]  :	ADC Driver
------------------------------------------------------------------------------*/

#include "adc.h"

#ifdef INTERRUPT_MODE
/* -----------------------------------------------------------------------------
 *                          Global Variables                                   *
------------------------------------------------------------------------------*/

volatile uint16  g_adcResult = 0;

/* -----------------------------------------------------------------------------
 *                          ISR's Definitions                                  *
------------------------------------------------------------------------------*/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
#endif

void ADC_init(const Adc_ConfigType * config_Ptr){
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input
	 * this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADPS2:0 pre-scalar value should be assigned as the config_Ptr to be
	 * configurable
	 */
	SET_BIT(ADCSRA,ADEN);
	CLEAR_BIT(ADCSRA,ADATE);
	CLEAR_BIT(ADCSRA,ADSC);

#ifdef INTERRUPT_MODE
	SET_BIT(ADCSRA,ADIE);
	#ifdef AUTO_TRIGGER_MODE
		SET_BIT(ADCSRA,ADATE);
		SFIOR = (SFIOR & NUM_TO_CLEAR_LAST_3_BITS) |\
				((config_Ptr -> triggersource & NUM_TO_CLEAR_LAST_5_BITS)<<5);
	#endif
#endif

#ifdef POLLING_MODE
	CLEAR_BIT(ADCSRA,ADIE);
#endif

	ADCSRA = (ADCSRA & NUM_TO_CLEAR_FIRST_3_BITS) | \
			(config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);

}

#ifdef INTERRUPT_MODE
void ADC_readChannel(const Adc_ChannelNumber channel){
	ADMUX = (ADMUX & NUM_TO_CLEAR_FIRST_5_BITS) | \
			(channel & NUM_TO_CLEAR_LAST_5_BITS);
	SET_BIT(ADCSRA,ADSC);		/* start conversion write '1' to ADSC */
}
#endif

#ifdef POLLING_MODE
uint16 ADC_readChannel(Adc_ChannelNumber channel){
	ADMUX = (ADMUX & NUM_TO_CLEAR_FIRST_5_BITS) | \
			(channel & NUM_TO_CLEAR_LAST_5_BITS);
	SET_BIT(ADCSRA,ADSC);		/* start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* wait for conversion to complete ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* clear ADIF by write '1' to it :) */
	return ADC; /* return the data register */
}
#endif

