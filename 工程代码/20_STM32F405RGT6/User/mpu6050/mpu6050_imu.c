#include "mpu6050_imu.h"

#include <math.h>

mpu6050_data MPU6050_Data_IMU = {0};

const float M_PI = 3.1415926535;
const float RtA = 57.2957795f;
const float AtR = 0.0174532925f;
const float Gyro_G = 0.03051756f*2;	  	//�����ǳ�ʼ������+-2000��ÿ����1 / (65536 / 4000) = 0.03051756*2		
const float Gyro_Gr = 0.0005326f*2;     //������ÿ��,ת������ÿ���� 2*0.03051756	 * 0.0174533f = 0.0005326*2

static float NormAcc;

/* ��Ԫ��ϵ�� */
typedef volatile struct {
  float q0;
  float q1;
  float q2;
  float q3;
} Quaternion;
Quaternion NumQ = {1, 0, 0, 0};

/* �����ǻ������ */
struct V{
	float x;
	float y;
	float z;
};	
volatile struct V GyroIntegError = {0};

/* ��Ԫ���ⷨ��ʼ�� */
void MPU6050_IMU_Init(void)
{
	NumQ.q0 = 1;
	NumQ.q1 = 0;
	NumQ.q2 = 0;
	NumQ.q3 = 0;	
	GyroIntegError.x = 0;
	GyroIntegError.y = 0;
	GyroIntegError.z = 0;
}

void MPU6050_IMU_Get_Data(float *pitch, float *roll, float dt) 
{		
	volatile struct V Gravity,Acc,Gyro,AccGravity;

	static  float KpDef = 0.5f ;
	static  float KiDef = 0.0001f;
//static  float KiDef = 0.00001f;
	
	float q0_t,q1_t,q2_t,q3_t;
  //float NormAcc;	
	float NormQuat; 
	float HalfTime = dt * 0.5f;

	//��ȡ��Ч��ת�����е��������� 
	Gravity.x = 2*(NumQ.q1 * NumQ.q3 - NumQ.q0 * NumQ.q2);								
	Gravity.y = 2*(NumQ.q0 * NumQ.q1 + NumQ.q2 * NumQ.q3);						  
	Gravity.z = 1-2*(NumQ.q1 * NumQ.q1 + NumQ.q2 * NumQ.q2);	
	// ���ٶȹ�һ��
	NormAcc = 1/sqrt(squa(MPU6050_Data_IMU.Acc.x)+ squa(MPU6050_Data_IMU.Acc.y) +squa(MPU6050_Data_IMU.Acc.z));
	
	Acc.x = MPU6050_Data_IMU.Acc.x * NormAcc;
	Acc.y = MPU6050_Data_IMU.Acc.y * NormAcc;
	Acc.z = MPU6050_Data_IMU.Acc.z * NormAcc;
	
 	//������˵ó���ֵ
	AccGravity.x = (Acc.y * Gravity.z - Acc.z * Gravity.y);
	AccGravity.y = (Acc.z * Gravity.x - Acc.x * Gravity.z);
	AccGravity.z = (Acc.x * Gravity.y - Acc.y * Gravity.x);
	
	//�������ٶȻ��ֲ������ٶȵĲ���ֵ
	GyroIntegError.x += AccGravity.x * KiDef;
	GyroIntegError.y += AccGravity.y * KiDef;
	GyroIntegError.z += AccGravity.z * KiDef;
	
	//���ٶ��ںϼ��ٶȻ��ֲ���ֵ
	Gyro.x = MPU6050_Data_IMU.Gyro.x * Gyro_Gr + KpDef * AccGravity.x  +  GyroIntegError.x;//������
	Gyro.y = MPU6050_Data_IMU.Gyro.y * Gyro_Gr + KpDef * AccGravity.y  +  GyroIntegError.y;
	Gyro.z = MPU6050_Data_IMU.Gyro.z * Gyro_Gr + KpDef * AccGravity.z  +  GyroIntegError.z;
	
	// һ�����������, ������Ԫ��
	q0_t = (-NumQ.q1*Gyro.x - NumQ.q2*Gyro.y - NumQ.q3*Gyro.z) * HalfTime;
	q1_t = ( NumQ.q0*Gyro.x - NumQ.q3*Gyro.y + NumQ.q2*Gyro.z) * HalfTime;
	q2_t = ( NumQ.q3*Gyro.x + NumQ.q0*Gyro.y - NumQ.q1*Gyro.z) * HalfTime;
	q3_t = (-NumQ.q2*Gyro.x + NumQ.q1*Gyro.y + NumQ.q0*Gyro.z) * HalfTime;
	
	NumQ.q0 += q0_t;
	NumQ.q1 += q1_t;
	NumQ.q2 += q2_t;
	NumQ.q3 += q3_t;
	// ��Ԫ����һ��
	NormQuat = 1/sqrt(squa(NumQ.q0) + squa(NumQ.q1) + squa(NumQ.q2) + squa(NumQ.q3));
	NumQ.q0 *= NormQuat;
	NumQ.q1 *= NormQuat;
	NumQ.q2 *= NormQuat;
	NumQ.q3 *= NormQuat;	
	
	// ��Ԫ��תŷ����
		
	*pitch = asin(2 * NumQ.q0 *NumQ.q2 - 2 * NumQ.q1 * NumQ.q3) * RtA;						

	*roll = atan2(2 * NumQ.q2 *NumQ.q3 + 2 * NumQ.q0 * NumQ.q1, 1 - 2 * NumQ.q1 *NumQ.q1 - 2 * NumQ.q2 * NumQ.q2) * RtA;				
	
}
