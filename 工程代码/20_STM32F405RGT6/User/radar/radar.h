#ifndef _RADAR_H_
#define _RADAR_H_

#include "main.h" //HAL库文件声明


extern UART_HandleTypeDef huart1;//声明USART1的HAL库结构体

extern int cur;

#define Radar_Rec_DataLen	58*2


extern uint8_t Radar_Recieve_Buff[Radar_Rec_DataLen];
extern uint16_t Radar_Data[60];

void Radar_Init(void);
void Radar_Motor_On(void);
void Radar_Motor_Off(void);

uint8_t Radar_CheckData(uint8_t *data);

void Radar_Get_Rec_Data(uint8_t *data);
void Radar_Recieve(void);

void Radar_Control(void);

uint16_t fund_min(uint16_t a,uint16_t b,uint16_t c,uint16_t d,uint16_t e,uint16_t f,uint16_t g,uint16_t h);

extern uint8_t Radar_Rx_flag;
extern uint8_t Radar_temp_data;

extern uint8_t flag_north,flag_east,flag_south,flag_west;

extern uint8_t Radar_Enable;

#endif
