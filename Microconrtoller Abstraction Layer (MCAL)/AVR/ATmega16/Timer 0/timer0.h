/* -----------------------------------------------------------------------------
[FILE NAME]    :	timer0.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	17/02/2021

[DESCRIPTION]  :	Header File to Timer 0 Driver  
--------------------------------------------------------------------------------*/

#ifndef TIMER0_H
#define TIMER0_H
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* -----------------------------------------------------------------------------
 *                         Types Declaration                                   *
 ------------------------------------------------------------------------------*/
//#define OVF_MODE
#define COMP_MODE
//#define FAST_PWM_MODE

typedef enum
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,\
	EXTERNAL_CLOCK_FALLING_EDGE,EXTERNAL_CLOCK_RISING_EDGE
}Timer0_Clock;

typedef enum
{
	OC0_DISCONNECT,OC0_TOGGLE,OC0_CLEAR=2,NON_INVERTNG=2,OC0_SET=3,INVERTING=3
}Timer0_Oc0Mode;

#ifdef OVF_MODE 
typedef struct
{
	Timer0_Clock clock;
	uint8 initialValue;
	Timer0_Oc0Mode oc0Mode;
}Timer0_ConfigTypeOvf;
#endif

#ifdef COMP_MODE
typedef struct
{
	Timer0_Clock clock;
	uint8 tick;
	Timer0_Oc0Mode oc0Mode;
}Timer0_ConfigTypeComp;
#endif

#ifdef FAST_PWM_MODE
typedef struct
{
	Timer0_Clock clock;
	uint8 initialValue;
	uint8 dutyCycle;
	Timer0_Oc0Mode oc0Mode;
}Timer0_ConfigTypePwm;
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
void TIMER0_initOvfMode(const Timer0_ConfigTypeOvf * Config_Ptr);
void TIMER0_setCallBackOvf(void(*a_ptr)(void));
#endif

#ifdef COMP_MODE
void TIMER0_initCompMode(const Timer0_ConfigTypeComp * Config_Ptr);
void TIMER0_setCallBackComp(void(*a_ptr)(void));
#endif

#ifdef FAST_PWM_MODE
void TIMER0_initPwmMode(const Timer0_ConfigTypePwm * Config_Ptr);
#endif

void TIMER0_deInit(void);
void TIMER0_startCount(const Timer0_Clock a_clock);
void TIMER0_stopCount(void);

#endif
