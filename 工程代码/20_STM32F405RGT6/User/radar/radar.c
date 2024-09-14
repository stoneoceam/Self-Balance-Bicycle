#include "radar.h"

#include <string.h>

#include "led/led.h"
#include "buzzer/buzzer.h"
#include "motor/motor.h"
#include "servo/servo.h"
#include "bluetooth/bluetooth.h"

uint8_t Radar_Enable = 0;

uint8_t flag_north = 0,flag_east = 0,flag_south = 0,flag_west = 0;

uint8_t Radar_Recieve_Buff[Radar_Rec_DataLen] = {0};
uint16_t Radar_Data[60] = {0};//�״ｨͼ����,�ֱ���6��

int cur = 0;//���ݰ���ʼλ��
uint8_t Radar_Rx_flag = 0;
uint8_t Radar_temp_data = 0;

void Radar_Init(void)
{

	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	HAL_UART_Receive_IT(&huart1,Radar_Recieve_Buff,Radar_Rec_DataLen);
	
}

/**
 * @brief	�����״���
 * @param	��
 * @retval	��
 */
void Radar_Motor_On(void)
{
	//�״�������
	//	a5 5a 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 01 01 fa fb
	uint8_t buff[188] = {0}; 
	buff[0] = 0xa5; 
	buff[1] = 0x5a; 
	buff[2] = 0x55; 
	buff[188-4] = 0x01;
	buff[188-3] = 0x01;
	buff[188-2] = 0xfa;
	buff[188-1] = 0xfb;
	HAL_UART_Transmit(&huart1,buff,188,1000);
}

/**
 * @brief	�ر��״���
 * @param	��
 * @retval	��
 */
void Radar_Motor_Off(void)
{	
	//�״���ͣת
	//	a5 5a 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//	00 00 00 00 00 00 00 00 00 00 00 00 01 00 fa fb
	uint8_t buff[188] = {0}; 
	buff[0] = 0xa5; 
	buff[1] = 0x5a; 
	buff[2] = 0x55; 
	buff[188-4] = 0x01;
	buff[188-3] = 0x00;
	buff[188-2] = 0xfa;
	buff[188-1] = 0xfb;
	HAL_UART_Transmit(&huart1,buff,188,1000);
}

/**
 * @brief	�����ݰ�����У��
 * @param	dataΪ���ݰ�
 * @retval	1��֤ͨ��,0��֤��ͨ��
 */
uint8_t Radar_CheckData(uint8_t *data)
{
	uint8_t datasum = 0;   //У���

	int i;
	

	for(cur = 2; cur < Radar_Rec_DataLen; cur++){
		if(data[cur-2] == 0xA5 && data[cur-1] == 0x5A && data[cur] == 0x3A)
		{
			for(i = cur-2; i<(cur-2+57) && i<Radar_Rec_DataLen; i++)
			{
				datasum += data[i];	
			}
			if(datasum == data[i])	return 1;
			else return 0;
		}		
	}
	return 0;
}

/**
 * @brief	�Խ������ݰ����н���������뽨ͼ��������
 * @param	dataΪ�������ݰ�
 * @retval	��
 */	
void Radar_Get_Rec_Data(uint8_t *data)
{
	cur-=2;
	float start_angle = ((data[cur+5]<<8) + (data[cur+6]))/100.0; 
	float end_angle = ((data[cur+55]<<8) + (data[cur+56]))/100.0;
	
	float average_angle;//��һ֡���ݵ�ƽ���Ƕ�
	if(start_angle>end_angle) end_angle+=360;
	average_angle = (start_angle + end_angle)/2;
	if(average_angle >= 360) average_angle-=360;
	
	uint32_t average_distance = 0;//��һ֡���ݵ�ƽ������
	int i;
	for(i = 7;i<53;i+=3){
		average_distance += ((data[cur+i]<<8) + (data[cur+i+1]));
	}
	average_distance /= 16;
		
	Radar_Data[(int)(average_angle/6)] = average_distance;//��ͼ
	
}

/**
 * @brief	�״����ݽ���
 * @param	��
 * @retval	��
 */
void Radar_Recieve(void)
{
	//���պ�����stm32f4xx_it.c��
	if(Radar_CheckData(Radar_Recieve_Buff))
	{
		Radar_Get_Rec_Data(Radar_Recieve_Buff);
	}
}

/**
 * @brief	�״��Զ�����
 * @param	��
 * @retval	��
 */
void Radar_Control(void)
{
	static uint8_t state = 0;//״̬λ
	static uint8_t crc_sum = 0;//У���
	if(Radar_Rx_flag == 1)
	{
		Radar_Recieve();
		Radar_Rx_flag = 0;
	}
	
	//��ͷ����Ϊ��
	//�� Radar_Data[56],Radar_Data[57],Radar_Data[58],Radar_Data[59],Radar_Data[0],Radar_Data[1],Radar_Data[2],Radar_Data[3]
	//�� Radar_Data[11],Radar_Data[12],Radar_Data[13],Radar_Data[14],Radar_Data[15],Radar_Data[16],Radar_Data[17],Radar_Data[18]
	//�� Radar_Data[26],Radar_Data[27],Radar_Data[28],Radar_Data[29],Radar_Data[30],Radar_Data[31],Radar_Data[32],Radar_Data[33]
	//�� Radar_Data[41],Radar_Data[42],Radar_Data[43],Radar_Data[44],Radar_Data[45],Radar_Data[46],Radar_Data[47],Radar_Data[48]
	
	short a = fund_min(Radar_Data[56],Radar_Data[57],Radar_Data[58],Radar_Data[59],Radar_Data[0],Radar_Data[1],Radar_Data[2],Radar_Data[3]);
	short b = fund_min(Radar_Data[11],Radar_Data[12],Radar_Data[13],Radar_Data[14],Radar_Data[15],Radar_Data[16],Radar_Data[17],Radar_Data[18]);
	short c = fund_min(Radar_Data[26],Radar_Data[27],Radar_Data[28],Radar_Data[29],Radar_Data[30],Radar_Data[31],Radar_Data[32],Radar_Data[33]);
	short d = fund_min(Radar_Data[41],Radar_Data[42],Radar_Data[43],Radar_Data[44],Radar_Data[45],Radar_Data[46],Radar_Data[47],Radar_Data[48]);
	if(a > 250) 
		flag_north = 1;//������
	else 
		flag_north = 0;//������
	if(b > 150) 
		flag_east = 1;//������
	else 
		flag_east = 0;//������
	if(c > 150) 
		flag_south = 1;//������
	else 
		flag_south = 0;//������
	if(d > 150) 
		flag_west = 1;//������
	else 
		flag_west = 0;//������
		
	if(Radar_Enable == 1)
	{	
		if(flag_north){
			SERVO_Middle();
			Set_PwmB(600);
		}
		else if(flag_east && flag_west)
		{
			if((Radar_Data[14]/2 + Radar_Data[5]/2) > (Radar_Data[44]/2 + Radar_Data[45]/2))
			{
				SERVO_Right(30);
				Set_PwmB(400);
			}
			else
			{
				SERVO_Left(30);
				Set_PwmB(400);
			}
		}
		else if(flag_east && (!flag_west))
		{
			SERVO_Right(30);
			Set_PwmB(400);
		}
		else if((!flag_east) && flag_west)
		{
			SERVO_Left(30);
			Set_PwmB(400);
		}
		else
		{
			LED_Blue_On();
		}
	}
}

/**
 * @brief	Ѱ��8�����е���Сֵ
 * @param	8����
 * @retval	��С���Ǹ�����ֵ
 */
uint16_t fund_min(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f,uint16_t g,uint16_t h)
{
	uint16_t res  = a;
	if(b<res) res = b;
	if(c<res) res = c;
	if(d<res) res = d;
	if(e<res) res = e;
	if(f<res) res = f;
	if(g<res) res = g;
	if(h<res) res = h;
	return res;
}