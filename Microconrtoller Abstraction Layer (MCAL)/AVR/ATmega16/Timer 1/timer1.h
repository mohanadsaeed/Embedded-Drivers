/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer1.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	18/02/2021

[DESCRIPTION]  :	Header File to Timer 1 Driver  
--------------------------------------------------------------------------------*/

#ifndef TIMER1_H
#define TIMER1_H
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/

typedef enum 
{
	TIMER1_OVF,TIMER1_CTC=4,TIMER1_FAST_PWM_8_BIT=5,TIMER1_FAST_PWM_9_BIT=6,\
	TIMER1_FAST_PWM_10_BIT=7,TIMER1_FAST_PWM_ICR1=14,TIMER1_FAST_PWM_OCR1A=15
}Timer1_ModeOfOperation;
/*Any mode which uses ICR1 register cannot be used besides Input Capture Unit*/

typedef enum
{
	TIMER1_NO_CLOCK,TIMER1_F_CPU_1,TIMER1_F_CPU_8,TIMER1_F_CPU_64,\
	TIMER1_F_CPU_256,TIMER1_F_CPU_1024,TIMER1_EXTERNAL_CLOCK_FALLING_EDGE,\
	TIMER1_EXTERNAL_CLOCK_RISING_EDGE
}Timer1_Clock;

typedef enum
{
	OC1_A_DISCONNECT,OC1_A_TOGGLE,OC01_A_CLEAR=2,OC1_A_NON_INVERTNG=2,\
	OC1_A_SET=3,OC1_A_INVERTING=3
}Timer1_Oc1AMode;

typedef enum
{
	OC1_B_DISCONNECT,OC1_B_TOGGLE,OC1_B_CLEAR=2,OC1_B_NON_INVERTNG=2,\
	OC1_B_SET=3,OC1_B_INVERTING=3
}Timer1_Oc1BMode;

typedef enum
{
	OC1_A,OC1_B,OC1_A_B
}Timer1_channels;

typedef struct
{
	uint16 initialValue;
	uint16 tick;
	uint16 top;
	uint16 dutyCycleA;
	uint16 dutyCycleB;
	Timer1_Clock clock;
	Timer1_Oc1AMode oc1AMode;
	Timer1_Oc1BMode oc1BMode;
	Timer1_ModeOfOperation mode;
}Timer1_ConfigType;

/* -----------------------------------------------------------------------------
 *                           Preprocessor                                      *
  -----------------------------------------------------------------------------*/
#define NULL_PTR (void *) 0
#define NUM_TO_CLEAR_FIRST_2_BITS 0xFC
#define NUM_TO_CLEAR_LAST_6_BITS 0x03
#define NUM_TO_CLEAR_3_4TH_BITS 0xE7
#define NUM_TO_CLEAR_FIRST_2_BITS_LAST_4_BITS 0x0C
#define NUM_TO_CLEAR_LAST_2_BITS 0x3F
#define NUM_TO_CLEAR_4_5TH_BITS 0xCF
#define NUM_TO_CLEAR_FIRST_3_BITS 0xF8
#define NUM_TO_CLEAR_LAST_5_BITS 0X07

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
  -----------------------------------------------------------------------------*/  
void TIMER1_init(const Timer1_ConfigType * Config_Ptr);
void TIMER1_setCallBack(void(*a_ptr)(void),const Timer1_ModeOfOperation mode);
void TIMER1_deInit(void);
void TIMER1_startCount(const Timer1_Clock a_clock);
void TIMER1_stopCount(void);
void TIMER1_changeDutyCyle(uint16 duty,Timer1_channels channel);

#endif
