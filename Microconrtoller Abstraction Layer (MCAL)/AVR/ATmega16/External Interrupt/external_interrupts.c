#include "external_interrupts.h"

/* -----------------------------------------------------------------------------
 *                           Global Variables                                  *
-------------------------------------------------------------------------------*/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrInt0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrInt1)(void) = NULL_PTR;
static volatile void (*g_callBackPtrInt2)(void) = NULL_PTR;


/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/

ISR(INT0_vect){
	if(g_callBackPtrInt0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(INT1_vect){
	if(g_callBackPtrInt1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(INT2_vect){
	if(g_callBackPtrInt2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/

void INT0_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * 	n=0: Falling edge generates interrupt
	 * 	n=1: Raising edge generates interrupt
	 * 	n=2: Low level generates interrupt
	 * 	n=3: Logical change generates interrupt
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_FIRST_2_BITS) |\
			(Config_Ptr -> interruptevent & NUM_TO_CLEAR_LAST_6_BITS);

	//Configure INT0 pin as input
	CLEAR_BIT(DDRD,PD2);
	//Enable Internal Pull-up
	PORTD = (PORTD & NUM_TO_CLEAR_2ND_BIT) |\
			((Config_Ptr -> pullup & NUM_TO_CLEAR_LAST_7_BIT) << PD2);
	//Module Interrupt Enable
	SET_BIT(GICR,INT0);
}

void INT1_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * 	n=0: Falling edge generates interrupt
	 * 	n=1: Rising edge generates interrupt
	 * 	n=2: Low level generates interrupt
	 * 	n=3: Logical change generates interrupt
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_SECOND_2_BITS) |\
			((Config_Ptr -> interruptevent & NUM_TO_CLEAR_LAST_6_BITS) << BIT2);

	//Configure INT1 pin as input
	CLEAR_BIT(DDRD,PD3);
	//Enable Internal Pull-up
	PORTD = (PORTD & NUM_TO_CLEAR_3RD_BIT) |\
			((Config_Ptr -> pullup & NUM_TO_CLEAR_LAST_7_BIT) << PD3);
	//Module Interrupt Enable
	SET_BIT(GICR,INT1);
}

void INT2_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * 	n=0: Falling edge generates interrupt
	 * 	n=1: Rising edge generates interrupt
	 */
	MCUCSR = (MCUCR & NUM_TO_CLEAR_6TH_BITS) |\
			((((Config_Ptr -> interruptevent)-2) & NUM_TO_CLEAR_LAST_6_BITS) << BIT6);

	//Configure INT2 pin as input
	CLEAR_BIT(DDRB,PB2);
	//Enable Internal Pull-up
	PORTB = (PORTB & NUM_TO_CLEAR_2ND_BIT) |\
			((Config_Ptr -> pullup & NUM_TO_CLEAR_LAST_7_BIT) << PB2);
	//Module Interrupt Enable
	SET_BIT(GICR,INT2);
}

void INT0_setEvent(const Ei_InterruptEvent a_int0Event){
	/*
	 * insert the required event in MCUCR Register
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_FIRST_2_BITS) |\
			(a_int0Event & NUM_TO_CLEAR_LAST_6_BITS);
}

void INT1_setEvent(const Ei_InterruptEvent a_int1Event){
	/*
	 * insert the required event in MCUCR Register
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_SECOND_2_BITS) |\
			((a_int1Event & NUM_TO_CLEAR_LAST_6_BITS) << BIT2);
}

void INT2_setEvent(const Ei_InterruptEvent a_int2Event){
	/*
	 * insert the required event in MCUCSR Register
	 */
	MCUCSR = (MCUCR & NUM_TO_CLEAR_6TH_BITS) |\
			((((a_int2Event)-2) & NUM_TO_CLEAR_LAST_6_BITS) << BIT6);
}

void INT0_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt0 = a_ptr;
}

void INT1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt1 = a_ptr;
}

void INT2_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt2 = a_ptr;
}

void INT0_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT0);
}

void INT1_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT1);
}

void INT2_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT2);
}

