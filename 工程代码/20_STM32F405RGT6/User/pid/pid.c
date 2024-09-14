#include "pid.h"

float PID_Control(pid *PID){

	PID->err = PID->expect - PID->feedback;
	
	PID->integral += PID->err;
	//�����޷�
	if(PID->integral > PID->integral_max) PID->integral = PID->integral_max;
	if(PID->integral < -PID->integral_max) PID->integral = -PID->integral_max;
	//pid����
	PID->out = PID->kp * PID->err + 
			   PID->ki * PID->integral + 
			   PID->kd * (PID->err - PID->err_last);
	
	PID->err_last = PID->err;
	//����޷�
	if(PID->out > PID->out_max) PID->out = PID->out_max;
	if(PID->out < -PID->out_max) PID->out = -PID->out_max;
	return PID->out;
}

void PID_Integral_Clear(pid *PID){
	PID->integral = 0.0f;
}

