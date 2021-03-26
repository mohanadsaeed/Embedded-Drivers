/* -----------------------------------------------------------------------------
[FILE NAME]    :	dc_motor.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	20/02/2021

[DESCRIPTION]  :	DC Motor Driver
------------------------------------------------------------------------------*/

#include "dc_motor.h"
#include "timer0.h"

#ifdef TIMER0
Timer0_ConfigType timer0Config;
#endif

#ifdef TIMER2
Timer2_ConfigType timer2Config;
#endif

static void DCMOTOR_timerSetup(const Dcmotor_ConfigType * Motor_Ptr);

/* ----------------------------------------------------------------------------
 *                      Functions Definitions                                 *
------------------------------------------------------------------------------*/
void DCMOTOR_init(const Dcmotor_ConfigType * Motor_Ptr){
	DCMOTOR_timerSetup(Motor_Ptr);
	/* Configue motor pin as output*/
	SET_BIT(DCMOTOR_PORT_DIR,IN1);
	SET_BIT(DCMOTOR_PORT_DIR,IN2);
	/* Select the direction of rotation*/
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

static void DCMOTOR_timerSetup(const Dcmotor_ConfigType * Motor_Ptr){
	/* Setting the configurations of timer 0 to select PWM mode*/
#ifdef TIMER0
	timer0Config.initialValue = 0;
	timer0Config.mode = TIMER0_FAST_PWM;
	timer0Config.clock = TIMER0_F_CPU_8;
	timer0Config.dutyCycle = (uint8)(Motor_Ptr -> speedPercentage*TOP/100);
	timer0Config.oc0Mode = OC0_NON_INVERTNG;
	TIMER0_init(&timer0Config);
#endif

	/* Setting the configurations of timer 2 to select PWM mode*/
#ifdef TIMER2
	timer2Config.initialValue = 0;
	timer2Config.mode = TIMER2_FAST_PWM;
	timer2Config.initialValue = 0;
	timer2Config.clock = TIMER2_F_CPU_8;
	timer2Config.dutyCycle = (uint8)(Motor_Ptr -> speedPercentage*TOP/100);
	timer2Config.oc2Mode = OC2_NON_INVERTNG;
	TIMER2_init(&timer2Config);
#endif
};
