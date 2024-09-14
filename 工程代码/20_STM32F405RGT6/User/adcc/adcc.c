#include "adcc.h"

#include "buzzer/buzzer.h"

uint16_t ADC_Temperature_Value[10]; //ʵ�ʵ�ѹֵ
uint16_t ADC_Voltage_Value[10]; //ʵ���¶�ֵ

void ADC_Init(void){

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Temperature_Value[0], 10);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)&ADC_Voltage_Value[0], 10);
}


float Get_Temperature(void){
	
	uint8_t i;
	uint32_t res = 0;
	for(i=0;i<10;i++){
		res+=ADC_Temperature_Value[i];
	}
	res = res/10;
	return (float)(res*3.3f/4096-0.76f)/2.5f+25;
}

float Get_Voltage(void){
	
	uint8_t i;
	uint32_t res = 0;
	for(i=0;i<10;i++){
		res+=ADC_Voltage_Value[i];
	}
	res = res/10;
	return (float)(res)/4096*3.3f*11;
}

void ADC_Test(void){
	
	printf("Temperature: %.2f\n",Get_Temperature());
	printf("Voltage: %.2f\n",Get_Voltage());
}

/**
 * @brief	��ص������
 * @param	��
 * @retval	��
 */
void Voltage_Control(void)
{
	if(Get_Voltage() < 10.6)
	{
		BUZZER_On();
	}
}
