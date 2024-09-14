#include "pid.h"

float PID_Control(pid *PID){

	PID->err = PID->expect - PID->feedback;
	
	PID->integral += PID->err;
	//积分限幅
	if(PID->integral > PID->integral_max) PID->integral = PID->integral_max;
	if(PID->integral < -PID->integral_max) PID->integral = -PID->integral_max;
	//pid运算
	PID->out = PID->kp * PID->err + 
			   PID->ki * PID->integral + 
			   PID->kd * (PID->err - PID->err_last);
	
	PID->err_last = PID->err;
	//输出限幅
	if(PID->out > PID->out_max) PID->out = PID->out_max;
	if(PID->out < -PID->out_max) PID->out = -PID->out_max;
	return PID->out;
}

void PID_Integral_Clear(pid *PID){
	PID->integral = 0.0f;
}

