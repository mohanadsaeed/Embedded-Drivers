/* -----------------------------------------------------------------------------
[FILE NAME]    :	adc.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	14/02/2021

[DESCRIPTION]  :	Header File for ADC Driver
------------------------------------------------------------------------------*/

#ifndef ADC_H
#define ADC_H

/* -----------------------------------------------------------------------------
 *                           Includes                                          *
 ------------------------------------------------------------------------------*/
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/* -----------------------------------------------------------------------------
 *                           ENUM & Structures                                          *
 ------------------------------------------------------------------------------*/
typedef enum
{
	ADC_F_CPU_1,ADC_F_CPU_2,ADC_F_CPU_4,ADC_F_CPU_8,ADC_F_CPU_16,ADC_F_CPU_32,\
	ADC_F_CPU_64,ADC_F_CPU_128
}Adc_Clock;

typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC0_ADC0_10x,ADC1_ADC0_10x,\
	ADC0_ADC0_200x,ADC1_ADC0_200x,ADC2_ADC2_10x,ADC3_ADC2_10x,ADC2_ADC2_200x,\
	ADC3_ADC2_200x,ADC0_ADC1,ADC1_ADC1,ADC2_ADC1,ADC3_ADC1,ADC4_ADC1,ADC5_ADC1,\
	ADC6_ADC1,ADC7_ADC1,ADC0_ADC2,ADC1_ADC_2,ADC2_ADC2,ADC3_ADC2,ADC4_ADC2
}Adc_ChannelNumber;

typedef enum
{
	FREE_RUNNING_MODE,ANALOG_COMPARATOR,EXTERNAL_INTERRUPT_REQUEST0,\
	TIMER0_COMPARE_MATCH,TIME0_OVERFLOW,TIME1_COMPARE_MATCH_B,TIME1_OVERFLOW,\
	TIME1_CAPTURE_EVENT
}Adc_TriggerSource;

typedef struct
{
	Adc_Clock clock;
	Adc_ChannelNumber channelnumber;
	Adc_TriggerSource triggersource;
}Adc_ConfigType;

/* -----------------------------------------------------------------------------
 *                      Preprocessor Macros                                    *
 ------------------------------------------------------------------------------*/
#define INTERRUPT_MODE
#define NUM_TO_CLEAR_FIRST_3_BITS 0xF8
#define NUM_TO_CLEAR_LAST_3_BITS 0x1F
#define NUM_TO_CLEAR_LAST_5_BITS 0x07
#define NUM_TO_CLEAR_FIRST_5_BITS 0xE0

 
 /* -----------------------------------------------------------------------------
 *                      Functions Declaration                                   *
------------------------------------------------------------------------------*/
void ADC_init(const Adc_ConfigType * config_Ptr);
#ifdef INTERRUPT_MODE
void ADC_readChannel(Adc_ChannelNumber channel);
#endif
#ifdef POLLING_MODE
uint16 ADC_readChannel(Adc_ChannelNumber channel);
#endif


#endif
