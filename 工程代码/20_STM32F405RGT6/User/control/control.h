#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "main.h"

#include "./motor/motor.h"

//control_1----------
void PIDS_Control(motor* Motor);
uint8_t Will_Falldown(float angle);
void Control_1(void);

//control_2-----------
int Vertical(float Med,float Angle,float gyro_x);
int Velocity (int Encoder_motor);
void Control_2(void);

extern float Med_Angle,Vertical_Kp,Vertical_Kd,Velocity_Kp,Velocity_Ki;


#endif
