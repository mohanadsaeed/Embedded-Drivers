/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer0.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	17/02/2021

[DESCRIPTION]  :	Timer 0 Driver  
--------------------------------------------------------------------------------*/

#include "timer0.h"

/* -----------------------------------------------------------------------------
 *                           Global Variables                                  *
-------------------------------------------------------------------------------*/
static volatile void (*g_callBackPtrOvf)(void) = NULL_PTR;
static volatile void (*g_callBackPtrComp)(void) = NULL_PTR;

/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/
ISR(TIMER0_OVF_vect){
	if(g_callBackPtrOvf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOvf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect){
	if(g_callBackPtrComp != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrComp)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/
void TIMER0_init(const Timer0_ConfigType * Config_Ptr){
	/*Initial value for timer 0*/
	TCNT0 = Config_Ptr -> initialValue;
	switch (Config_Ptr -> mode){
	case TIMER0_OVF:
		/*Overflow Interrupt Enable*/
		SET_BIT(TIMSK,TOIE0);
		/*Compare Interrupt Disable*/
		CLEAR_BIT(TIMSK,OCIE0);
		/*Enable Force Compare Mode*/
		SET_BIT(TCCR0,FOC0);
		break;
	case TIMER0_CTC:
		/*Initial value for timer 0*/
		TCNT0=0;
		/*Compare Interrupt Enable*/
		SET_BIT(TIMSK,OCIE0);
		/*Overflow Interrupt Disable*/
		CLEAR_BIT(TIMSK,TOIE0);
		/*Enable Force Compare Mode*/
		SET_BIT(TCCR0,FOC0);
		/*Compare Value*/
		OCR0 = Config_Ptr -> tick;
		break;

	case TIMER0_FAST_PWM:
		/*Disable all Interrupts*/
		CLEAR_BIT(TIMSK,OCIE0);
		CLEAR_BIT(TIMSK,TOIE0);
		/*Disable Force Compare Mode*/
		CLEAR_BIT(TCCR0,FOC0);
		OCR0 = Config_Ptr -> dutyCycle;

	}

	/*Select Mode of Operation*/
	/*Insert first bit of mode into WGM00 Bit*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_6TH_BIT) |\
			((Config_Ptr -> mode & NUM_TO_CLEAR_LAST_7_BITS)<<BIT6);
	/*Insert second bit of mode into WGM10 Bit*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_3TH_BIT) |\
			((Config_Ptr -> mode & NUM_TO_CLEAR_FIRST_BIT_LAST_6_BITS)<<BIT2);

	/*Select OC0 Mode*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_4_5TH_BITS)|\
			((Config_Ptr -> oc0Mode & NUM_TO_CLEAR_LAST_6_BITS)<<BIT4);

	/*Initialize Clock*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);

	if(Config_Ptr -> oc0Mode != OC0_DISCONNECT){
		/*Set OC0 pin as output*/
		CLEAR_BIT(TIMSK,OCIE0);
		/*Set OC0 as output pin*/
		SET_BIT(DDRB,PB3);
	}
}

void TIMER0_setCallBack(void(*a_ptr)(void),Timer0_ModeOfOperation mode){
	/* Save the address of the Call back function in a global variable */
	switch (mode){
	case TIMER0_OVF:
		g_callBackPtrOvf = a_ptr;
		break;
	case TIMER0_CTC:
		g_callBackPtrComp = a_ptr;
	}
}

void TIMER0_deInit(void){
	TCCR0=0;
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);
}

void TIMER0_startCount(const Timer0_Clock a_clock){
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(a_clock & NUM_TO_CLEAR_LAST_5_BITS);
}

void TIMER0_stopCount(void){
	TCCR0 &= NUM_TO_CLEAR_FIRST_3_BITS;
}

void TIMER0_changeDutyCycle(uint8 duty){
	OCR0 = duty;
}
