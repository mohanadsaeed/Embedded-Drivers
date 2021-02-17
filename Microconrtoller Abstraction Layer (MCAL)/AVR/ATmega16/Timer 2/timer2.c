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
ISR(TIMER2_OVF_vect){
	if(g_callBackPtrOvf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOvf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif

#ifdef COMP_MODE
ISR(TIMER2_COMP_vect){
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
void TIMER2_initOvfMode(const Timer2_ConfigTypeOvf * Config_Ptr){
	/*Initial value for timer 2*/
	TCNT2 = Config_Ptr -> initialValue;
	/*Overflow Interrupt Enable*/
	SET_BIT(TIMSK,TOIE2);
	/*Compare Interrupt Disable*/
	CLEAR_BIT(TIMSK,OCIE2);
	/*Timer 2 is clocked from the MC clock*/
	CLEAR_BIT(ASSR,AS2);

	if(Config_Ptr -> oc2Mode != OC2_DISCONNECT){
		/*Set OC2 pin as output*/
		SET_BIT(DDRD,PD7);
	}
	SET_BIT(TCCR2,FOC2);
	/*Normal Mode (Overflow Mode)*/
	CLEAR_BIT(TCCR2,WGM21);
	CLEAR_BIT(TCCR2,WGM20);
	/*OC2 Mode Selection*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc2Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);	
}

void TIMER2_setCallBackOvf(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrOvf = a_ptr;
}
#endif

#ifdef COMP_MODE
void TIMER2_initCompMode(const Timer2_ConfigTypeComp * Config_Ptr){
	/*Initial value for timer 2*/
	TCNT2=0;
	/*Compare Value*/
	OCR2 = Config_Ptr -> tick;
	/*Compare Interrupt Enable*/
	SET_BIT(TIMSK,OCIE2);
	/*Overflow Interrupt Disable*/
	CLEAR_BIT(TIMSK,TOIE2);
	/*Timer 2 is clocked from the MC clock*/
	CLEAR_BIT(ASSR,AS2);

	if(Config_Ptr -> oc2Mode != OC2_DISCONNECT){
		/*Set OC2 pin as output*/
		SET_BIT(DDRD,PD7);
	}
	else if(Config_Ptr -> oc2Mode == OC2_TOGGLE) {
		CLEAR_BIT(TIMSK,OCIE2);
	}
	SET_BIT(TCCR2,FOC2);
	/*Compare Mode (CTC)*/
	SET_BIT(TCCR2,WGM21);
	CLEAR_BIT(TCCR2,WGM20);
	/*OC2 Mode Selection*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc2Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);
}

void TIMER2_setCallBackComp(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrComp = a_ptr;
}
#endif

#ifdef FAST_PWM_MODE
void TIMER2_initPwmMode(const Timer2_ConfigTypePwm * Config_Ptr){
	TCNT2 = Config_Ptr -> initialValue; // Set Timer Initial Value to 0
	/*Timer 2 is clocked from the MC clock*/
	CLEAR_BIT(ASSR,AS2);

	/* configure the timer
	 * 1. Fast PWM mode FOC2=0
	 * 2. Fast PWM Mode WGM21=1 & WGM20=1
	 * 3. Clear OC2 when match occurs (non inverted mode) COM20=0 & COM21=1
	 * 4. clock 
	 */ 
	CLEAR_BIT(TCCR2,FOC2);
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);	
	/*OC2 Mode Selection (Inverting / Non-inverting)*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_4_5TH_BITS) |\
			((Config_Ptr -> oc2Mode & NUM_TO_CLEAR_LAST_6_BITS) << BIT4);
	/*Initialize Clock*/
	TCCR2 = (TCCR2 & NUM_TO_CLEAR_FIRST_3_BITS) |\
			(Config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);		
	OCR2  = Config_Ptr -> dutyCycle; 

	/*set PD7/OC2 as output pin --> pin where the PWM signal is generated from MC.*/
	SET_BIT(DDRD,PD7);
}
#endif

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
