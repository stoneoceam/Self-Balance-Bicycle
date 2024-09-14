#include "led.h"

void LED_Red_On(void){
	HAL_GPIO_WritePin(LED_Red_GPIO_Port,LED_Red_Pin,GPIO_PIN_RESET);
}
void LED_Red_Off(void){
	HAL_GPIO_WritePin(LED_Red_GPIO_Port,LED_Red_Pin,GPIO_PIN_SET);
}
void LED_Green_On(void){
	HAL_GPIO_WritePin(LED_Green_GPIO_Port,LED_Green_Pin,GPIO_PIN_RESET);
}
void LED_Green_Off(void){
	HAL_GPIO_WritePin(LED_Green_GPIO_Port,LED_Green_Pin,GPIO_PIN_SET);
}
void LED_Blue_On(void){
	HAL_GPIO_WritePin(LED_Blue_GPIO_Port,LED_Blue_Pin,GPIO_PIN_RESET);
}
void LED_Blue_Off(void){
	HAL_GPIO_WritePin(LED_Blue_GPIO_Port,LED_Blue_Pin,GPIO_PIN_SET);
}
void LED_All_On(void){
	LED_Red_On();
	LED_Green_On();
	LED_Blue_On();
}
void LED_All_Off(void){
	LED_Red_Off();
	LED_Green_Off();
	LED_Blue_Off();
}
void LED_Init(void){
	LED_All_Off();
}

void LED_Test(void){
	LED_Red_On(); HAL_Delay(1000); LED_Red_Off();
	LED_Green_On();	HAL_Delay(1000); LED_Green_Off();
	LED_Blue_On(); HAL_Delay(1000); LED_Blue_Off();
}
