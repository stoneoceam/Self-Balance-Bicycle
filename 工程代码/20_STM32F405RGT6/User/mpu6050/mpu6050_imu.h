#ifndef _MPU6050_IMU_H_
#define _MPU6050_IMU_H_

#include "stm32f4xx.h"
#include "mpu6050.h"



#define squa( Sq )        (((float)Sq)*((float)Sq))

void MPU6050_IMU_Init(void);
void MPU6050_IMU_Get_Data(float *pitch, float *roll, float dt);


extern mpu6050_data MPU6050_Data_IMU;

#endif
