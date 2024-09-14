#include "control.h"

#include "motor/motor.h"
#include "mpu6050/mpu6050_dmp.h"
#include "servo/servo.h"



//control_1------------------
/**
 * @brief	三级PID调节
 * @param
 * @retval
 */
void PIDS_Control(motor* Motor) {

	//外环速度控制器
	Motor->vel_encoder->expect = Motor->tar_speed;
	Motor->vel_encoder->feedback = Motor->cur_speed;
	PID_Control(Motor->vel_encoder);

	//中环角度控制器
	Motor->pitch_angle->expect = Motor->vel_encoder->out;
	Motor->pitch_angle->feedback = (-MPU6050_Data_DMP.Pitch);
	PID_Control(Motor->pitch_angle);

	//内环角加速度控制器
	Motor->pitch_gyro->expect = Motor->pitch_angle->out;
	Motor->pitch_gyro->feedback = -MPU6050_Data_DMP.Gyro.y;
	PID_Control(Motor->pitch_gyro);


}

/**
 * @brief	检测小车是否倒下
 * @param	angle：输入的参考角度值
 * @retval	1：倒下 2：未倒下
 */
uint8_t Will_Falldown(float angle) {

	if (angle > 20.0f || angle < -20.0f)	return 1;
	else
		return 0;
}

/**
 * @brief	控制器输出
 * @param
 * @retval
 */
void Control_1(void) {

	MotorA.tar_speed = 0.0f;
	PIDS_Control(&MotorA);

	if (Will_Falldown(MPU6050_Data_DMP.Pitch) == 1) {

		MotorA.tar_speed = 0;

		PID_Integral_Clear(MotorA.vel_encoder);
		PID_Integral_Clear(MotorA.pitch_angle);
		PID_Integral_Clear(MotorA.pitch_gyro);
	}
	else if ((MPU6050_Data_DMP.Gyro.y >= 50 || MPU6050_Data_DMP.Gyro.y <= -50) && (MPU6050_Data_DMP.Gyro.y <= 2000 || MPU6050_Data_DMP.Gyro.y >= -2000) && (MPU6050_Data_DMP.Pitch < 15.0f || MPU6050_Data_DMP.Pitch > -15.0f)) {

		Set_PwmA((int)MotorA.pitch_gyro->out);
	}

	//PIDS_Control(&MotorB);
	//Set_PwmB((int)MotorB.vel_encoder->out);	
}

//control_2--------------

float Med_Angle = -0.5;	                                //机械中值---在这里修改你的机械中值即可。
float Vertical_Kp = -900, Vertical_Kd = 8;                  //直立环KP、KD
float Velocity_Kp = 50, Velocity_Ki =  0.25;                  //速度环KP、KI

//float Med_Angle = -0.5;	                                //机械中值---在这里修改你的机械中值即可。
//float Vertical_Kp = -820, Vertical_Kd = 10;                  //直立环KP、KD
//float Velocity_Kp = 51, Velocity_Ki =  0.26;                  //速度环KP、KI

/*********************
直立环PD控制器：Kp*Ek+Kd*Ek_D
入口：期望角度、真实角度、真实角速度
出口：直立环输出
*********************/
int Vertical(float Med, float Angle, float gyro_x)
{
	int PWM_out1;
	
	
	static float gyro_Err,gyro_Last,gyro_Out;
	float a = 0.7;
	gyro_Err = gyro_x;
	gyro_Out = (1-a)*gyro_Err+a*gyro_Last;
	gyro_Last = gyro_Out;
	
	static float angle_Err,angle_Last,angle_Out;
	float b = 0.7;
	angle_Err = Angle;
	angle_Out = (1-b)*angle_Err+b*angle_Last;
	angle_Last = angle_Out;
	
	PWM_out1 = Vertical_Kp * (Med - angle_Out) + Vertical_Kd * (gyro_Out);
	return PWM_out1;
}

/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
int Velocity(int Encoder_motor)
{
	static int Encoder_S, EnC_Err_Lowout_last, PWM_out2, Encoder_Err, EnC_Err_Lowout;
	float a = 0.7;

	Encoder_Err = Encoder_motor;	                             //1.计算速度偏差

	//2.对速度偏差进行低通滤波:low_out=(1-a)*Ek+a*low_out_last
	EnC_Err_Lowout = (1 - a) * Encoder_Err + a * EnC_Err_Lowout_last; //使得波形更加平滑，滤除高频干扰，防止速度突变。
	EnC_Err_Lowout_last = EnC_Err_Lowout;                     //防止速度过大的影响直立环的正常工作。

	Encoder_S += EnC_Err_Lowout;                                               //3.对速度偏差积分，积分出位移
	Encoder_S = Encoder_S > 10000 ? 10000 : (Encoder_S < (-10000) ? (-10000) : Encoder_S);//4.积分限幅

	PWM_out2 = Velocity_Kp * EnC_Err_Lowout + Velocity_Ki * Encoder_S;	            //5.速度环控制输出计算
	return PWM_out2;
}

void Control_2(void)
{
	int pwm = Vertical(Med_Angle, MPU6050_Data_DMP.Pitch, MPU6050_Data_DMP.Gyro.y) + Velocity(MotorA.cur_speed);
	if (pwm > 4000) pwm = 4000;
	if (pwm < -4000) pwm = -4000;
	MotorA.tar_speed = pwm;
	Set_PwmA(pwm);
	if(MPU6050_Data_DMP.Pitch>30||MPU6050_Data_DMP.Pitch<-30){	SERVO_Middle();MotorA_Emergency_Stop();}
}

