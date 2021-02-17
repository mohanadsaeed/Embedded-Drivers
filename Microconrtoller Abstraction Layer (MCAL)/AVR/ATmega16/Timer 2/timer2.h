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
#define OVF_MODE
#define COMP_MODE
#define FAST_PWM_MODE

typedef enum
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_32,F_CPU_64,F_CPU_128,F_CPU_256,F_CPU_1024
}Timer2_Clock;

typedef enum
{
	OC2_DISCONNECT,OC2_TOGGLE,OC2_CLEAR=2,NON_INVERTNG=2,OC2_SET=3,INVERTING=3
}Timer2_Oc2Mode;

#ifdef OVF_MODE 
typedef struct
{
	Timer2_Clock clock;
	uint8 initialValue;
	Timer2_Oc2Mode oc2Mode;
}Timer2_ConfigTypeOvf;
#endif

#ifdef COMP_MODE
typedef struct
{
	Timer2_Clock clock;
	uint8 tick;
	Timer2_Oc2Mode oc2Mode;
}Timer2_ConfigTypeComp;
#endif

#ifdef FAST_PWM_MODE
typedef struct
{
	Timer2_Clock clock;
	uint8 initialValue;
	uint8 dutyCycle;
	Timer2_Oc2Mode oc2Mode;
}Timer2_ConfigTypePwm;
#endif

/* -----------------------------------------------------------------------------
 *                           Preprocessor                                      *
  -----------------------------------------------------------------------------*/
#define NULL_PTR (void *) 0
#define NUM_TO_CLEAR_6TH_BIT 0xBF
#define NUM_TO_CLEAR_3TH_BIT 0xF7
#define NUM_TO_CLEAR_LAST_7_BITS 0x01
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
#ifdef OVF_MODE
void TIMER2_initOvfMode(const Timer2_ConfigTypeOvf * Config_Ptr);
void TIMER2_setCallBackOvf(void(*a_ptr)(void));
#endif

#ifdef COMP_MODE
void TIMER2_initCompMode(const Timer2_ConfigTypeComp * Config_Ptr);
void TIMER2_setCallBackComp(void(*a_ptr)(void));
#endif

#ifdef FAST_PWM_MODE
void TIMER2_initPwmMode(const Timer2_ConfigTypePwm * Config_Ptr);
#endif

void TIMER2_deInit(void);
void TIMER2_startCount(const Timer2_Clock a_clock);
void TIMER2_stopCount(void);

#endif
