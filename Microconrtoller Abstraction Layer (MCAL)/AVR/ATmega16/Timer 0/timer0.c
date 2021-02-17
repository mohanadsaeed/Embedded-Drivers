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
#ifdef OVF_MODE
static volatile void (*g_callBackPtrOvf)(void) = NULL_PTR;
#endif

#ifdef COMP_MODE
static volatile void (*g_callBackPtrComp)(void) = NULL_PTR;
#endif

/* -----------------------------------------------------------------------------
 *                       Interrupt Service Routines                            *
 ------------------------------------------------------------------------------*/
#ifdef OVF_MODE
ISR(TIMER0_OVF_vect){
	if(g_callBackPtrOvf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOvf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

#ifdef COMP_MODE
ISR(TIMER0_COMP_vect){
	if(g_callBackPtrComp != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrComp)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

/* -----------------------------------------------------------------------------
 *                      Functions Definitions                                  *
 ------------------------------------------------------------------------------*/
#ifdef OVF_MODE
void TIMER0_initOvfMode(const Timer0_ConfigTypeOvf * Config_Ptr){
	/*Initial value for timer 0*/
	TCNT0 = Config_Ptr -> initialValue;
	/*Overflow Interrupt Enable*/
	SET_BIT(TIMSK,TOIE0);
	/*Compare Interrupt Disable*/
	CLEAR_BIT(TIMSK,OCIE0);

	if(Config_Ptr -> oc0Mode != OC0_DISCONNECT){
		/*Set OC0 pin as output*/
		SET_BIT(DDRB,PB3);
	}
	SET_BIT(TCCR0,FOC0);
	/*Normal Mode (Overflow Mode)*/
	CLEAR_BIT(TCCR0,WGM01);
	CLEAR_BIT(TCCR0,WGM00);
	/*OC0 Mode Selection*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc0Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);	
}

void TIMER0_setCallBackOvf(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrOvf = a_ptr;
}
#endif

#ifdef COMP_MODE
void TIMER0_initCompMode(const Timer0_ConfigTypeComp * Config_Ptr){
	/*Initial value for timer 0*/
	TCNT0=0;
	/*Compare Value*/
	OCR0 = Config_Ptr -> tick;
	/*Compare Interrupt Enable*/
	SET_BIT(TIMSK,OCIE0);
	/*Overflow Interrupt Disable*/
	CLEAR_BIT(TIMSK,TOIE0);

	if(Config_Ptr -> oc0Mode != OC0_DISCONNECT){
		/*Set OC0 pin as output*/
		SET_BIT(DDRB,PB3);
	}
	else if(Config_Ptr -> oc0Mode == OC0_TOGGLE) {
		CLEAR_BIT(TIMSK,OCIE0);
	}
	SET_BIT(TCCR0,FOC0);
	/*Compare Mode (CTC)*/
	SET_BIT(TCCR0,WGM01);
	CLEAR_BIT(TCCR0,WGM00);
	/*OC0 Mode Selection*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc0Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);
}

void TIMER0_setCallBackComp(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrComp = a_ptr;
}
#endif

#ifdef FAST_PWM_MODE
void TIMER0_initPwmMode(const Timer0_ConfigTypePwm * Config_Ptr){
	TCNT0 = Config_Ptr -> initialValue; // Set Timer Initial Value to 0

	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock 
	 */ 
	CLEAR_BIT(TCCR0,FOC0);
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);	
	/*OC0 Mode Selection (Inverting / Non-inverting)*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc0Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR0 = (TCCR0 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);		
	OCR0  = Config_Ptr -> dutyCycle; 

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	SET_BIT(DDRB,PB3);
}
#endif

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
