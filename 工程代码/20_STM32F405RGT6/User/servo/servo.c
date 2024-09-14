#include "servo.h"

//����Ƶ��50hz
void SERVO_Init(void){
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	SERVO_Middle();
}

/**
 * @brief	����ˮƽ
 * @param	��
 * @retval	��
 */
void SERVO_Middle(void){

	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,150-1);
}

/**
 * @brief	��������б
 * @param	��бangel��
 * @retval	��
 */
void SERVO_Left(uint8_t angle){
	
	if(angle > 45) angle = 45;
	if(angle < 0 ) angle = 0;
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,10.0f/9.0f * (90-angle) + 49);
}

/**
 * @brief	��������б
 * @param	��бangel��
 * @retval	��
 */
void SERVO_Right(uint8_t angle){
	
	if(angle > 45) angle = 45;
	if(angle < 0 ) angle = 0;
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,10.0f/9.0f * (angle+90) + 49);
}
void SERVO_Test(void){
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,50-1); HAL_Delay(1000);//0��
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,100-1); HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,150-1); HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,200-1); HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,250-1); HAL_Delay(1000);
}
