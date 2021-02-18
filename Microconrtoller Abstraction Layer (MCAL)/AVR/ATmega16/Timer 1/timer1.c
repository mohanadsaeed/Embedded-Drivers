/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer1.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	18/02/2021

[DESCRIPTION]  :	Timer 1 Driver  
--------------------------------------------------------------------------------*/

#include "timer1.h"

/* -----------------------------------------------------------------------------
 *                           Global Variables                                  *
-------------------------------------------------------------------------------*/
static volatile void (*g_callBackPtrOvf)(void) = NULL_PTR;
static volatile void (*g_callBackPtrCompA)(void) = NULL_PTR;
static volatile void (*g_callBackPtrCompB)(void) = NULL_PTR;


/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/
ISR(TIMER1_OVF_vect){
	if(g_callBackPtrOvf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOvf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtrCompA != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrCompA)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPB_vect){
	if(g_callBackPtrCompB != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrCompB)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/
void TIMER1_init(const Timer1_ConfigType * Config_Ptr){
	/*Initial value for timer 1*/
	TCNT1 = Config_Ptr -> initialValue;
	switch (Config_Ptr -> mode){
	case TIMER1_OVF:
		/*Overflow Interrupt Enable*/
		SET_BIT(TIMSK,TOIE1);
		/*Disable Other Modes Interrupts*/
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,OCIE1B);
		/*Enable Force Output Compare*/
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);
		break;

	case TIMER1_CTC:
		/*Compare Interrupt Enable*/
		SET_BIT(TIMSK,OCIE1A);
		/*Disable Other Modes Interrupts*/
		CLEAR_BIT(TIMSK,TOIE1);
		CLEAR_BIT(TIMSK,OCIE1B);
		/*Enable Force Output Compare*/
		SET_BIT(TCCR1A,FOC1A);
		CLEAR_BIT(TCCR1A,FOC1B);
		/*Set Compare Value*/
		OCR1A = Config_Ptr -> tick;
		break;

	case TIMER1_FAST_PWM_OCR1A:
		/*Disable All Interrupts*/
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,OCIE1B);
		CLEAR_BIT(TIMSK,TOIE1);
		/*DisableForce Output Compare*/
		CLEAR_BIT(TCCR1A,FOC1A);
		CLEAR_BIT(TCCR1A,FOC1B);
		/*Set Top Value*/
		OCR1A = Config_Ptr -> top;
		/*Set Compare Value*/
		OCR1B = Config_Ptr -> dutyCycleB;
		break;

	case TIMER1_FAST_PWM_ICR1:
		/*Disable All Interrupts*/
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,OCIE1B);
		CLEAR_BIT(TIMSK,TOIE1);
		/*DisableForce Output Compare*/
		CLEAR_BIT(TCCR1A,FOC1A);
		CLEAR_BIT(TCCR1A,FOC1B);
		/*Set Top Value*/
		ICR1 = Config_Ptr -> top;
		/*Set Compare Value*/
		OCR1A = Config_Ptr -> dutyCycleA;
		OCR1B = Config_Ptr -> dutyCycleB;
		break;

	default:
		/*Disable All Interrupts*/
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,OCIE1B);
		CLEAR_BIT(TIMSK,TOIE1);
		/*DisableForce Output Compare*/
		CLEAR_BIT(TCCR1A,FOC1A);
		CLEAR_BIT(TCCR1A,FOC1B);
		/*Set Compare Value*/
		OCR1A = Config_Ptr -> dutyCycleA;
		OCR1B = Config_Ptr -> dutyCycleB;
	}

	/*Select Mode*/
	TCCR1A = (TCCR1A & NUM_TO_CLEAR_FIRST_2_BITS) |\
			(Config_Ptr -> mode & NUM_TO_CLEAR_LAST_6_BITS);
	TCCR1B = (TCCR1B & NUM_TO_CLEAR_3_4TH_BITS) |\
			((Config_Ptr -> mode & NUM_TO_CLEAR_FIRST_2_BITS_LAST_4_BITS)<<1);
	/*OC1A Mode Selection*/
	TCCR1A = (TCCR1A & NUM_TO_CLEAR_LAST_2_BITS) |\
			((Config_Ptr -> oc1AMode & NUM_TO_CLEAR_LAST_6_BITS)<<6);
	/*OC1B Mode Selection*/
	TCCR1A = (TCCR1A & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc1BMode & NUM_TO_CLEAR_LAST_6_BITS)<<4);
	/*Initialize Clock*/
	TCCR1B = (TCCR1B & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);	

	if(Config_Ptr -> oc1AMode != OC1_A_DISCONNECT){
		CLEAR_BIT(TIMSK,OCIE1A);
		CLEAR_BIT(TIMSK,TOIE1);
		/*OC1A as output*/
		DDRD |= (1<<PD5);
	}
	else if(Config_Ptr -> oc1BMode != OC1_B_DISCONNECT){
		CLEAR_BIT(TIMSK,OCIE1B);
		CLEAR_BIT(TIMSK,TOIE1);
		/*OC1B as output*/
		DDRD |= (1<<PD4);
	}
}

void TIMER1_setCallBack(void(*a_ptr)(void),const Timer1_ModeOfOperation mode){
	/* Save the address of the Call back function in a global variable */
	switch (mode){
	case TIMER1_OVF:
		g_callBackPtrOvf = a_ptr;
		break;
	case TIMER1_CTC:
		g_callBackPtrCompA = a_ptr;
		break;
	}
}

void TIMER1_deInit(void){
	TCCR1A=0;
	TCCR1B=0;
	/*Disable All Interrupts*/
	CLEAR_BIT(TIMSK,OCIE1A);
	CLEAR_BIT(TIMSK,OCIE1B);
	CLEAR_BIT(TIMSK,TOIE1);}

void TIMER1_startCount(const Timer1_Clock a_clock){
	/*Initialize Clock*/
	TCCR1B = (TCCR1B & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(a_clock & NUM_TO_CLEAR_LAST_5_BITS);
}

void TIMER1_stopCount(void){
	TCCR1B &= NUM_TO_CLEAR_FIRST_3_BITS;
}

void TIMER1_changeDutyCyle(uint16 duty,Timer1_channels channel){
	switch (channel){
	case OC1_A:
		OCR1A = duty;
		break;
	case OC1_B:
		OCR1B = duty;
		break;
	case OC1_A_B:
		OCR1A = duty;
		OCR1B = duty;
	}
}







