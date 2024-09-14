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
uint16_t Radar_Data[60] = {0};//雷达建图数据,分辨率6度

int cur = 0;//数据包起始位置
uint8_t Radar_Rx_flag = 0;
uint8_t Radar_temp_data = 0;

void Radar_Init(void)
{

	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	HAL_UART_Receive_IT(&huart1,Radar_Recieve_Buff,Radar_Rec_DataLen);
	
}

/**
 * @brief	开启雷达电机
 * @param	无
 * @retval	无
 */
void Radar_Motor_On(void)
{
	//雷达电机开启
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
 * @brief	关闭雷达电机
 * @param	无
 * @retval	无
 */
void Radar_Motor_Off(void)
{	
	//雷达电机停转
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
 * @brief	对数据包进行校验
 * @param	data为数据包
 * @retval	1验证通过,0验证不通过
 */
uint8_t Radar_CheckData(uint8_t *data)
{
	uint8_t datasum = 0;   //校验和

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
 * @brief	对接收数据包经行解包，并存入建图数据组中
 * @param	data为接收数据包
 * @retval	无
 */	
void Radar_Get_Rec_Data(uint8_t *data)
{
	cur-=2;
	float start_angle = ((data[cur+5]<<8) + (data[cur+6]))/100.0; 
	float end_angle = ((data[cur+55]<<8) + (data[cur+56]))/100.0;
	
	float average_angle;//这一帧数据的平均角度
	if(start_angle>end_angle) end_angle+=360;
	average_angle = (start_angle + end_angle)/2;
	if(average_angle >= 360) average_angle-=360;
	
	uint32_t average_distance = 0;//这一帧数据的平均距离
	int i;
	for(i = 7;i<53;i+=3){
		average_distance += ((data[cur+i]<<8) + (data[cur+i+1]));
	}
	average_distance /= 16;
		
	Radar_Data[(int)(average_angle/6)] = average_distance;//建图
	
}

/**
 * @brief	雷达数据接收
 * @param	无
 * @retval	无
 */
void Radar_Recieve(void)
{
	//接收函数在stm32f4xx_it.c中
	if(Radar_CheckData(Radar_Recieve_Buff))
	{
		Radar_Get_Rec_Data(Radar_Recieve_Buff);
	}
}

/**
 * @brief	雷达自动避障
 * @param	无
 * @retval	无
 */
void Radar_Control(void)
{
	static uint8_t state = 0;//状态位
	static uint8_t crc_sum = 0;//校验和
	if(Radar_Rx_flag == 1)
	{
		Radar_Recieve();
		Radar_Rx_flag = 0;
	}
	
	//车头方向为北
	//北 Radar_Data[56],Radar_Data[57],Radar_Data[58],Radar_Data[59],Radar_Data[0],Radar_Data[1],Radar_Data[2],Radar_Data[3]
	//东 Radar_Data[11],Radar_Data[12],Radar_Data[13],Radar_Data[14],Radar_Data[15],Radar_Data[16],Radar_Data[17],Radar_Data[18]
	//南 Radar_Data[26],Radar_Data[27],Radar_Data[28],Radar_Data[29],Radar_Data[30],Radar_Data[31],Radar_Data[32],Radar_Data[33]
	//西 Radar_Data[41],Radar_Data[42],Radar_Data[43],Radar_Data[44],Radar_Data[45],Radar_Data[46],Radar_Data[47],Radar_Data[48]
	
	short a = fund_min(Radar_Data[56],Radar_Data[57],Radar_Data[58],Radar_Data[59],Radar_Data[0],Radar_Data[1],Radar_Data[2],Radar_Data[3]);
	short b = fund_min(Radar_Data[11],Radar_Data[12],Radar_Data[13],Radar_Data[14],Radar_Data[15],Radar_Data[16],Radar_Data[17],Radar_Data[18]);
	short c = fund_min(Radar_Data[26],Radar_Data[27],Radar_Data[28],Radar_Data[29],Radar_Data[30],Radar_Data[31],Radar_Data[32],Radar_Data[33]);
	short d = fund_min(Radar_Data[41],Radar_Data[42],Radar_Data[43],Radar_Data[44],Radar_Data[45],Radar_Data[46],Radar_Data[47],Radar_Data[48]);
	if(a > 250) 
		flag_north = 1;//无阻塞
	else 
		flag_north = 0;//有阻塞
	if(b > 150) 
		flag_east = 1;//无阻塞
	else 
		flag_east = 0;//有阻塞
	if(c > 150) 
		flag_south = 1;//无阻塞
	else 
		flag_south = 0;//有阻塞
	if(d > 150) 
		flag_west = 1;//无阻塞
	else 
		flag_west = 0;//有阻塞
		
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
 * @brief	寻找8个数中的最小值
 * @param	8个数
 * @retval	最小的那个数的值
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