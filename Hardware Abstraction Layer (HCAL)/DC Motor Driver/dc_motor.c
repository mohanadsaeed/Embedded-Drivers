/* -----------------------------------------------------------------------------
[FILE NAME]    :	dc_motor.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	20/02/2021

[DESCRIPTION]  :	DC Motor Driver
------------------------------------------------------------------------------*/

#include "dc_motor.h"

/* ----------------------------------------------------------------------------
 *                      Functions Definitions                                 *
------------------------------------------------------------------------------*/
#ifdef TIMER0
void DCMOTOR_init(const Dcmotor_ConfigType * Motor_Ptr,\
		Timer0_ConfigType * Timer_Ptr){
#endif

#ifdef TIMER2
	void DCMOTOR_init(const Dcmotor_ConfigType * Motor_Ptr,\
			Timer2_ConfigType * Timer_Ptr){
#endif
		Timer_Ptr -> initialValue = 0;
#ifdef TIMER0
		Timer_Ptr -> mode = TIMER0_FAST_PWM;
		Timer_Ptr -> clock = TIMER0_F_CPU_8;
		Timer_Ptr -> dutyCycle = (uint8)(Motor_Ptr -> speedPercentage*TOP/100);
		Timer_Ptr -> oc0Mode = OC0_NON_INVERTNG;
		TIMER0_init(Timer_Ptr);
#endif

#ifdef TIMER2
		Timer_Ptr -> mode = TIMER2_FAST_PWM;
		Timer_Ptr -> initialValue = 0;
		Timer_Ptr -> clock = TIMER2_F_CPU_8;
		Timer_Ptr -> dutyCycle = (uint8)(Motor_Ptr -> speedPercentage*TOP/100);
		Timer_Ptr -> oc2Mode = OC2_NON_INVERTNG;
		TIMER2_init(Timer_Ptr);
#endif
		SET_BIT(DCMOTOR_PORT_DIR,IN1);
		SET_BIT(DCMOTOR_PORT_DIR,IN2);
		switch (Motor_Ptr -> rotationDirection){
		case CW:
			SET_BIT(DCMOTOR_PORT,IN2);
			CLEAR_BIT(DCMOTOR_PORT,IN1);
			break;
		case CCW:
			SET_BIT(DCMOTOR_PORT,IN1);
			CLEAR_BIT(DCMOTOR_PORT,IN2);
		}

	}

	void DCMOTOR_revertRotationDirection(void){
		DCMOTOR_PORT ^= ((1<<IN1)|(1<<IN2));
	}

	void DCMOTOR_changeRotationDirection(Dcmotor_rotDir direction){
		switch (direction){
		case CW:
			SET_BIT(DCMOTOR_PORT,IN2);
			CLEAR_BIT(DCMOTOR_PORT,IN1);
			break;
		case CCW:
			SET_BIT(DCMOTOR_PORT,IN1);
			CLEAR_BIT(DCMOTOR_PORT,IN2);
		}
	}

	void DCMOTOR_stop(void){
		CLEAR_BIT(DCMOTOR_PORT,IN1);
		CLEAR_BIT(DCMOTOR_PORT,IN2);
	}

	void DCMOTOR_changeSpeed(uint8 percentage){
#ifdef TIMER0
		TIMER0_changeDutyCycle((uint8)(percentage*TOP/100));
#endif

#ifdef TIMER2
		TIMER2_changeDutyCycle((uint8)(percentage*TOP/100));
#endif
	}
