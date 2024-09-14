#ifndef _SERVO_H_
#define _SERVO_H_

#include "tim.h"

extern TIM_HandleTypeDef htim9;

/*
³µ°Ñ×ËÌ¬
------- PWM:150-1

\
 \
  \
   \
    \	PWM:100-1
	
	/
   /
  /
 /
/		PWM:200-1


*/


void SERVO_Init(void);
void SERVO_Middle(void);
void SERVO_Left(uint8_t angle);
void SERVO_Right(uint8_t angle);
void SERVO_Test(void);

#endif
