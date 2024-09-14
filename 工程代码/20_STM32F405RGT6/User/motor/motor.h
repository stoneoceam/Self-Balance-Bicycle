#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "tim.h"

#include "./pid/pid.h"

typedef struct {
	int32_t tar_speed;	 //目标转速
	int32_t lastCount;   //上一次计数值
	int32_t totalCount;  //总计数值
	int16_t overflowNum; //溢出次数
	int32_t cur_speed;   //电机转速
	uint8_t direct;		 //旋转方向
	pid* vel_encoder;	 //速度环
	pid* pitch_angle;	 //角度环
	pid* pitch_gyro;	 //角加速度环
}motor;

extern motor MotorA;
extern motor MotorB;

void MOTOR_Init(void);
void Set_PwmA(int k);
void Set_PwmB(int k);
void MotorA_0(void);
void MotorA_1(void);
void MotorB_0(void);
void MotorB_1(void);
void MotorA_Emergency_Stop(void);
int myabs(int num);
int32_t Get_MotorA_Speed(void);
int32_t Get_MotorB_Speed(void);
void MOTOR_Test(int16_t i);
extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
