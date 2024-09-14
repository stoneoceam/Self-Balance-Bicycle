#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "tim.h"

#include "./pid/pid.h"

typedef struct {
	int32_t tar_speed;	 //Ŀ��ת��
	int32_t lastCount;   //��һ�μ���ֵ
	int32_t totalCount;  //�ܼ���ֵ
	int16_t overflowNum; //�������
	int32_t cur_speed;   //���ת��
	uint8_t direct;		 //��ת����
	pid* vel_encoder;	 //�ٶȻ�
	pid* pitch_angle;	 //�ǶȻ�
	pid* pitch_gyro;	 //�Ǽ��ٶȻ�
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
