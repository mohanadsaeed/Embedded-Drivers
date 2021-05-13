#include "external_interrupts.h"

/* -----------------------------------------------------------------------------
 *                           Global Variables                                  *
-------------------------------------------------------------------------------*/

/* Global variables to hold the address of the call back function in the application */
#ifdef INTERRUPT0
static volatile void (*g_callBackPtrInt0)(void) = NULL_PTR;
#endif

#ifdef INTERRUPT1
static volatile void (*g_callBackPtrInt1)(void) = NULL_PTR;
#endif

#ifdef INTERRUPT2
static volatile void (*g_callBackPtrInt2)(void) = NULL_PTR;
#endif


/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/
#ifdef INTERRUPT0
ISR(INT0_vect){
	if(g_callBackPtrInt0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

#ifdef INTERRUPT1
ISR(INT1_vect){
	if(g_callBackPtrInt1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

#ifdef INTERRUPT2
ISR(INT2_vect){
	if(g_callBackPtrInt2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrInt2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/

#ifdef INTERRUPT0
/* Function to initialize interrupt registers*/
void INT0_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * Low level generates interrupt
	 * Logical change generates interrupt
	 * Falling edge generates interrupt
	 * Raising edge generates interrupt
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

/* Function to select the event at which the interrupt will be triggered*/
void INT0_setEvent(const Ei_InterruptEvent a_int0Event){
	/*
	 * insert the required event in MCUCR Register
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_FIRST_2_BITS) |\
			(a_int0Event & NUM_TO_CLEAR_LAST_6_BITS);
}

/* Function to save the of the call back function in a global variable*/
void INT0_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt0 = a_ptr;
}

/* Function to de initializa interrupts registers*/
void INT0_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT0);
}
#endif


#ifdef INTERRUPT1
void INT1_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * Low level generates interrupt
	 * Logical change generates interrupt
	 * Falling edge generates interrupt
	 * Raising edge generates interrupt
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

void INT1_setEvent(const Ei_InterruptEvent a_int1Event){
	/*
	 * insert the required event in MCUCR Register
	 */
	MCUCR = (MCUCR & NUM_TO_CLEAR_SECOND_2_BITS) |\
			((a_int1Event & NUM_TO_CLEAR_LAST_6_BITS) << BIT2);
}

void INT1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt1 = a_ptr;
}

void INT1_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT1);
}
#endif


#ifdef INTERRUPT2
void INT2_init(const Ei_ConfigType * Config_Ptr){
	/*Select when the interrupt occurs
	 * Falling edge generates interrupt
	 * Raising edge generates interrupt
	 */
	MCUCSR = (MCUCR & NUM_TO_CLEAR_6TH_BIT) |\
			((((Config_Ptr -> interruptevent)-2) & NUM_TO_CLEAR_LAST_6_BITS) << BIT6);

	//Configure INT2 pin as input
	CLEAR_BIT(DDRB,PB2);
	//Enable Internal Pull-up
	PORTB = (PORTB & NUM_TO_CLEAR_2ND_BIT) |\
			((Config_Ptr -> pullup & NUM_TO_CLEAR_LAST_7_BIT) << PB2);
	//Module Interrupt Enable
	SET_BIT(GICR,INT2);
}

void INT2_setEvent(const Ei_InterruptEvent a_int2Event){
	/*
	 * insert the required event in MCUCSR Register
	 */
	MCUCSR = (MCUCR & NUM_TO_CLEAR_6TH_BIT) |\
			((((a_int2Event)-2) & NUM_TO_CLEAR_LAST_6_BITS) << BIT6);
}

void INT2_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrInt2 = a_ptr;
}

void INT2_deInit(void){
	//Module Interrupt Disable
	CLEAR_BIT(GICR,INT2);
}
#endif
