/* -----------------------------------------------------------------------------
[FILE NAME]    :	dc_motor.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	20/02/2021

[DESCRIPTION]  :	Header File for DC Motor Driver
------------------------------------------------------------------------------*/

#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "timer0.h"

/* ----------------------------------------------------------------------------
 *                         Timer Stucture Definition                          *
 -----------------------------------------------------------------------------*/

typedef enum{
	CW,CCW
}Dcmotor_rotDir;

typedef struct{
	uint8 speedPercentage;
	Dcmotor_rotDir rotationDirection;
}Dcmotor_ConfigType;

/* ----------------------------------------------------------------------------
 *                      Preprocessor Macros                                   *
  ----------------------------------------------------------------------------*/
#define TIMER0
#define TOP 255
/* DC Motor HW Pins */
#define DCMOTOR_PORT PORTB
#define DCMOTOR_PORT_DIR DDRB
#define IN1 PB0
#define IN2 PB1


/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/
#ifdef TIMER0
void DCMOTOR_init(const Dcmotor_ConfigType * Motor_Ptr,\
		Timer0_ConfigType * Timer_Ptr);
#endif

#ifdef TIMER2
void DCMOTOR_init(const Dcmotor_ConfigType * Motor_Ptr,\
		Timer2_ConfigType * Timer_Ptr);
#endif
void DCMOTOR_revertRotationDirection(void);
void DCMOTOR_changeRotationDirection(Dcmotor_rotDir direction);
void DCMOTOR_stop(void);
void DCMOTOR_changeSpeed(uint8 percentage);

#endif
