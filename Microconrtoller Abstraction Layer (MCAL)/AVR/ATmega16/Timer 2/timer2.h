/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer2.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	17/02/2021

[DESCRIPTION]  :	Header File to Timer 2 Driver  
--------------------------------------------------------------------------------*/

#ifndef TIMER2_H
#define TIMER2_H
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/
typedef enum
{
	TIMER2_OVF,TIMER2_CTC=2,TIMER2_FAST_PWM=3
}Timer2_ModeOfOperation;


typedef enum
{
	TIMER2_NO_CLOCK,TIMER2_F_CPU_1,TIMER2_F_CPU_8,TIMER2_F_CPU_32,\
	TIMER2_F_CPU_64,TIMER2_F_CPU_128,TIMER2_F_CPU_256,TIMER2_F_CPU_1024
}Timer2_Clock;

typedef enum
{
	OC2_DISCONNECT,OC2_TOGGLE,OC2_CLEAR=2,OC2_NON_INVERTNG=2,\
	OC2_SET=3,OC2_INVERTING=3
}Timer2_Oc2Mode;

typedef struct
{
	uint8 initialValue;
	uint8 dutyCycle;
	uint8 tick;
	Timer2_Clock clock;
	Timer2_Oc2Mode oc2Mode;
	Timer2_ModeOfOperation mode;
}Timer2_ConfigType;

/* -----------------------------------------------------------------------------
 *                           Preprocessor                                      *
  -----------------------------------------------------------------------------*/
#define NULL_PTR (void *) 0
#define NUM_TO_CLEAR_6TH_BIT 0xBF
#define NUM_TO_CLEAR_LAST_7_BITS 0x01
#define NUM_TO_CLEAR_3TH_BIT 0xF7
#define NUM_TO_CLEAR_FIRST_BIT_LAST_6_BITS 0x02
#define NUM_TO_CLEAR_4_5TH_BITS 0xCF
#define NUM_TO_CLEAR_LAST_6_BITS 0x03
#define NUM_TO_CLEAR_FIRST_3_BITS 0xF8
#define NUM_TO_CLEAR_LAST_5_BITS 0X07
#define BIT6 6
#define BIT2 2 
#define BIT4 4

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
  -----------------------------------------------------------------------------*/  
void TIMER2_init(const Timer2_ConfigType * Config_Ptr);
void TIMER2_setCallBack(void(*a_ptr)(void),const Timer2_ModeOfOperation);
void TIMER2_deInit(void);
void TIMER2_startCount(const Timer2_Clock a_clock);
void TIMER2_stopCount(void);
void TIMER2_changeDutyCycle(uint8 duty);

#endif