#include "buzzer.h"

void BUZZER_Init(void){
	
	BUZZER_Off();
	
}

void BUZZER_Off(void){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
}

void BUZZER_On(void){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
}

void BUZZER_Test(void){
	BUZZER_On(); HAL_Delay(1000); BUZZER_Off();
}
