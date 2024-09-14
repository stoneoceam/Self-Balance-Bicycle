#include "motor.h"
#include <stdlib.h>
//驱动频率20000hz
//编码器测速频率100hz
motor MotorA;
motor MotorB;

void MOTOR_Init(){
	
	//无刷电机初始化
	HAL_GPIO_WritePin(A_EN_GPIO_Port,A_EN_Pin,GPIO_PIN_SET);//使能电机
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//开启pwm输出
	MotorA.direct=0; MotorA.lastCount=0; MotorA.overflowNum=0; MotorA.tar_speed=0; MotorA.totalCount=0;
	
	//N20电机初始化
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_SET);//使能TB6612
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//开启pwm输出
	MotorB.direct=0; MotorB.lastCount=0; MotorB.overflowNum=0; MotorB.tar_speed=0; MotorB.totalCount=0;
	
	//编码器初始化
	HAL_TIM_Base_Start_IT(&htim6);//10ms定时器
	
	HAL_TIM_Encoder_Start_IT(&htim4,TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start_IT(&htim5,TIM_CHANNEL_1 | TIM_CHANNEL_2);
	__HAL_TIM_SET_COUNTER(&htim4,0);
	__HAL_TIM_SET_COUNTER(&htim5,0);
	
	//PID控制
	MotorA.vel_encoder = (pid*)malloc(sizeof(pid));//PI
	MotorA.vel_encoder->kp = 0.00001;
	MotorA.vel_encoder->ki = 0;
	MotorA.vel_encoder->kd = 0;
	MotorA.vel_encoder->integral_max = 2000;
	MotorA.vel_encoder->out_max = 95;
	
	MotorA.pitch_angle = (pid*)malloc(sizeof(pid));//PD
	MotorA.pitch_angle->kp = 0.00001;
	MotorA.pitch_angle->ki = 0;
	MotorA.pitch_angle->kd = 0;
	MotorA.pitch_angle->integral_max = 2000;
	MotorA.pitch_angle->out_max = 95;
	
	MotorA.pitch_gyro = (pid*)malloc(sizeof(pid));//PI
	MotorA.pitch_gyro->kp = 0.12;
	MotorA.pitch_gyro->ki = 0;
	MotorA.pitch_gyro->kd = 0;
	MotorA.pitch_gyro->integral_max = 2000;
	MotorA.pitch_gyro->out_max = 95;
	
	MotorB.vel_encoder = (pid*)malloc(sizeof(pid));
	MotorB.vel_encoder->kp = 0;
	MotorB.vel_encoder->ki = 0;
	MotorB.vel_encoder->kd = 0;
	MotorB.vel_encoder->integral_max = 1000;
	MotorB.vel_encoder->out_max = 80;
	
	MotorB.pitch_angle = (pid*)malloc(sizeof(pid));
	MotorB.pitch_angle->kp = 0;
	MotorB.pitch_angle->ki = 0;
	MotorB.pitch_angle->kd = 0;
	MotorB.pitch_angle->integral_max = 1000;
	MotorB.pitch_angle->out_max = 80;
	
	MotorB.pitch_gyro = (pid*)malloc(sizeof(pid));
	MotorB.pitch_gyro->kp = 0;
	MotorB.pitch_gyro->ki = 0;
	MotorB.pitch_gyro->kd = 0;
	MotorB.pitch_gyro->integral_max = 1000;
	MotorB.pitch_gyro->out_max = 80;
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：k   -99 <= k <= 99
返回  值：无
**************************************************************************/
void Set_PwmA(int k)//赋值给PWM寄存器
{
	int pwmA_abs;
	
	if(k>0) {
		MotorA.direct = 0;
		MotorA_0();
	}
	else{
		MotorA.direct = 1;		
		MotorA_1();
	}
	pwmA_abs = myabs(k);
	if(pwmA_abs>4199) pwmA_abs =4199;
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,pwmA_abs);
}
void Set_PwmB(int k)//赋值给PWM寄存器
{
	int pwmB_abs;
	if(k>0) {
		MotorB.direct = 0;
		MotorB_0();
	}
	else {    
		MotorB.direct = 1;
		MotorB_1();
	}
	pwmB_abs = myabs(k);
	if(pwmB_abs>999) pwmB_abs = 999;
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,pwmB_abs);
}

void MotorA_0(void){
		HAL_GPIO_WritePin(A_DIR_GPIO_Port,A_DIR_Pin,GPIO_PIN_SET);//正转
}

void MotorA_1(void){
		HAL_GPIO_WritePin(A_DIR_GPIO_Port,A_DIR_Pin,GPIO_PIN_RESET);//反转
}

void MotorB_0(void){
		HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//即01，正转
}

void MotorB_1(void){
		HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);//即10，反转
}

void MotorA_Emergency_Stop(void){
	HAL_GPIO_WritePin(A_EN_GPIO_Port,A_EN_Pin,GPIO_PIN_RESET);//使能电机
}

int32_t Get_MotorA_Speed(void){
	return MotorA.cur_speed;
}
int32_t Get_MotorB_Speed(void){
	return MotorB.cur_speed;
}

/*
*	函数功能：取绝对值
*	入口参数：int
*	返回值：无 unsingned int
*/
int myabs(int num)
{
	int temp;
	if(num<0)	temp=-num;
	else temp =num;
	return temp;
}

void MOTOR_Test(int16_t i){//取值只能在 -99---+99

	Set_PwmA(i);
	Set_PwmB(i);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM14) {
		HAL_IncTick();
	}
	if(htim == &htim4){
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4)){ //判断CR1的DIR位
			MotorA.overflowNum--; //减计数
		}
		else{
			MotorA.overflowNum++; //增计数
		}
	}
	if(htim == &htim5){
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5)){ //判断CR1的DIR位
			MotorB.overflowNum--; //减计数
		}
		else{
			MotorB.overflowNum++; //增计数
		}
	}
	else if(htim == &htim6){ //10ms中断计数一次
//		MotorA.totalCount = __HAL_TIM_GET_COUNTER(&htim4) + MotorA.overflowNum*65535 - MotorA.lastCount;
//		MotorA.lastCount = __HAL_TIM_GET_COUNTER(&htim4) + MotorA.overflowNum*65535;
//		MotorA.overflowNum = 0;
//		MotorA.cur_speed = MotorA.totalCount;
		//MotorA.cur_speed = (int32_t)(MotorA.totalCount * 100.0f / 4 /100*60);
		
		MotorB.totalCount = __HAL_TIM_GET_COUNTER(&htim5) + MotorB.overflowNum*65535 - MotorB.lastCount;
		MotorB.lastCount = __HAL_TIM_GET_COUNTER(&htim5) + MotorB.overflowNum*65535;
		MotorB.overflowNum = 0;
		MotorB.cur_speed = MotorB.totalCount;
		//MotorB.cur_speed = -(int32_t)(MotorB.totalCount * 100.0f / 4 /7*60);
	}
}
