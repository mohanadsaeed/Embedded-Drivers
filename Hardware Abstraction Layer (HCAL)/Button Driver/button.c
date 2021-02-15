/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	button.c

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	11/02/2021

[DESCRIPTION]  :	Button Driver  
------------------------------------------------------------------------------------------*/

#incldue "button.h"

void BUTTON_init(void){
	CLEAR_BIT(BUTTON_PORT_DIR,BUTTON_PIN)
}

 uint8 BUTTON_IS_PRESSED(void){
	#ifdef PULL_UP 
		BIT_IS_CLEAR(BUTTON_PORT_IN,BUTTON_PIN); 
	#endif 

	#ifdef PULL_DOWN 
		BIT_IS_SET(BUTTON_PORTIN,BUTTON_PIN);
	#endif 
 }
 
 uint8 BUTTON_IS_RELEASED(void){
	#ifdef PULL_UP
		BIT_IS_SET(BUTTON_PORTIN,BUTTON_PIN);
	#endif 
	
	#ifdef PULL_DOWN 
		BIT_IS_CLEAR(BUTTON_PORT_IN,BUTTON_PIN);
	#endif 
 }
 
 void BUTTON_PULL_UP_ACTIVATE(void){
	 SET_BIT(BUTTON_PORT_OUT,BUTTON_PIN);
 }
