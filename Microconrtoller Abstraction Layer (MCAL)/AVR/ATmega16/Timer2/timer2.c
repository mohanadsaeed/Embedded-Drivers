/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer2.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	17/02/2021

[DESCRIPTION]  :	Timer 2 Driver  
--------------------------------------------------------------------------------*/

#include "timer2.h"

/* -----------------------------------------------------------------------------
 *                           Global Variables                                  *
-------------------------------------------------------------------------------*/
static volatile void (*g_callBackPtrOvf)(void) = NULL_PTR;
static volatile void (*g_callBackPtrComp)(void) = NULL_PTR;

/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/
ISR(TIMER2_OVF_vect){
	if(g_callBackPtrOvf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOvf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_COMP_vect){
	if(g_callBackPtrComp != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrComp)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/
void TIMER2_init(const Timer2_ConfigType * Config_Ptr){
	/*Initial value for timer 0*/
	TCNT2 = Config_Ptr -> initialValue;
	/*Timer 2 is clocked from the MC clock*/
	CLEAR_BIT(ASSR,AS2);
	switch (Config_Ptr -> mode){
	case TIMER2_OVF:
		/*Overflow Interrupt Enable*/
		SET_BIT(TIMSK,TOIE2);
		/*Compare Interrupt Disable*/
		CLEAR_BIT(TIMSK,OCIE2);
		/*Enable Force Compare Mode*/
		SET_BIT(TCCR2,FOC2);
		break;
	case TIMER2_CTC:
		/*Initial value for timer 2*/
		TCNT2=0;
		/*Compare Interrupt Enable*/
		SET_BIT(TIMSK,OCIE2);
		/*Overflow Interrupt Disable*/
		CLEAR_BIT(TIMSK,TOIE2);
		/*Enable Force Compare Mode*/
		SET_BIT(TCCR2,FOC2);
		/*Compare Value*/
		OCR2 = Config_Ptr -> tick;
		break;

	case TIMER2_FAST_PWM:
		/*Disable all Interrupts*/
		CLEAR_BIT(TIMSK,OCIE2);
		CLEAR_BIT(TIMSK,TOIE2);
		/*Disable Force Compare Mode*/
		CLEAR_BIT(TCCR2,FOC2);
		OCR2 = Config_Ptr -> dutyCycle;

	}

	/*Select Mode of Operation*/
	/*Insert first bit of mode into WGM02 Bit*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_6TH_BIT) |\
			((Config_Ptr -> mode & NUM_TO_CLEAR_LAST_7_BITS)<<BIT6);
	/*Insert second bit of mode into WGM12 Bit*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_3TH_BIT) |\
			((Config_Ptr -> mode & NUM_TO_CLEAR_FIRST_BIT_LAST_6_BITS)<<BIT2);

	/*Select OC2 Mode*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_4_5TH_BITS)|\
			((Config_Ptr -> oc2Mode & NUM_TO_CLEAR_LAST_6_BITS)<<BIT4);

	/*Initialize Clock*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);

	if(Config_Ptr -> oc2Mode != OC2_DISCONNECT){
		/*Set OC2 pin as output*/
		CLEAR_BIT(TIMSK,OCIE2);
		/*Set OC2 pin as output*/
		SET_BIT(DDRD,PD7);

	}
}

void TIMER2_setCallBack(void(*a_ptr)(void),Timer2_ModeOfOperation mode){
	/* Save the address of the Call back function in a global variable */
	switch (mode){
	case TIMER2_OVF:
		g_callBackPtrOvf = a_ptr;
		break;
	case TIMER2_CTC:
		g_callBackPtrComp = a_ptr;
	}
}

void TIMER2_deInit(void){
	TCCR2=0;
	CLEAR_BIT(TIMSK,TOIE2);
	CLEAR_BIT(TIMSK,OCIE2);
}

void TIMER2_startCount(const Timer2_Clock a_clock){
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(a_clock & NUM_TO_CLEAR_LAST_5_BITS);
}

void TIMER2_stopCount(void){
	TCCR2 &= NUM_TO_CLEAR_FIRST_3_BITS;
}

void TIMER2_changeDutyCycle(uint8 duty){
	OCR2 = duty;
}
