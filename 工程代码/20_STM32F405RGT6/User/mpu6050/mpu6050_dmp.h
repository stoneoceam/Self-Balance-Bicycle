#ifndef _MPU6050_DMP_H__
#define _MPU6050_DMP_H__

#include "stm32f4xx.h"
#include "mpu6050.h"
#include <stdio.h>
#include <i2c.h>




int fputcc(int ch);
int get_tick_count(unsigned long *count);
 
uint8_t MPU6050_DMP_Init(void);
uint8_t MPU6050_DMP_Get_Data(float *pitch,float *roll,float *yaw);
 


void usart1_send_char(uint8_t c);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);


extern mpu6050_data MPU6050_Data_DMP;

#endif
