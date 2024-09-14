#ifndef _PID_H_
#define _PID_H_

typedef struct {

	float err;
    float err_last;
    float expect;
    float feedback;
    float kp;
    float ki;
    float kd;
    float integral;
    float integral_max;
    float out;
    float out_max; 
}pid;

float PID_Control(pid *PID);
void PID_Integral_Clear(pid *PID);


#endif
