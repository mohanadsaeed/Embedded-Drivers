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
typedef enum
{
	OVF,CTC=2,FAST_PWM=3
}Timer0_ModeOfOperation;

typedef enum
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,\
	EXTERNAL_CLOCK_FALLING_EDGE,EXTERNAL_CLOCK_RISING_EDGE
}Timer0_Clock;

typedef enum
{
	OC0_DISCONNECT,OC0_TOGGLE,OC0_CLEAR=2,OC0_NON_INVERTNG=2,\
	OC0_SET=3,OC0_INVERTING=3
}Timer0_Oc0Mode;

typedef struct
{
	uint8 initialValue;
	uint8 dutyCycle;
	uint8 tick;
	Timer0_Clock clock;
	Timer0_Oc0Mode oc0Mode;
	Timer0_ModeOfOperation mode;
}Timer0_ConfigType;

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
void TIMER0_init(const Timer0_ConfigType * Config_Ptr);
void TIMER0_setCallBack(void(*a_ptr)(void),const Timer0_ModeOfOperation);
void TIMER0_deInit(void);
void TIMER0_startCount(const Timer0_Clock a_clock);
void TIMER0_stopCount(void);
void TIMER0_changeDutyCycle(uint8 duty);
#endif
