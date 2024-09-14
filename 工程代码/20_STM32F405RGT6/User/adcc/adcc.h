#ifndef _ADCC_H_
#define _ADCC_H_

#include "main.h"
#include "adc.h"
#include "./debug/debug.h"

	
void ADC_Init(void);
float Get_Temperature(void);
float Get_Voltage(void);
void ADC_Test(void);
void Voltage_Control(void);

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

#endif
