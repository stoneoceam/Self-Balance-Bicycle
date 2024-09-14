#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "main.h" //HAL库文件声明
#include <stdlib.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart4;//声明USART4的HAL库结构体
extern UART_HandleTypeDef huart3;

////Control_2--------------
//typedef struct{
//	
//	uint8_t LedStatus;
//	float med_angle;
//	float vertical_kp;
//	float vertical_kd;
//	float velocity_kp;
//	float velocity_ki;
//	//.....
//}bluetooth_rec_data;

//typedef struct{
//	int32_t speed;
//	float pitch; 
//	short y;
//	//.....
//}bluetooth_send_data;

//#define Bluetooth_Rec_DataLen	24
//#define Bluetooth_Send_DataLen	13
////--------------------

//Bluetooth_Control-------------------
typedef struct{
	
	bool Radar_Enable;
	uint8_t Dir_On;
	uint8_t Dir_Down;
	uint8_t Dir_Left;
	uint8_t Dir_Right;
	int Angle;
	int Speed;
	//.....
}bluetooth_rec_data;

typedef struct{
	uint8_t Flag_north;
	uint8_t Flag_east;
	uint8_t Flag_south;
	uint8_t Flag_west;
	int Angle;
	int Speed;
	float Voltage;
	float Pitch;
	//.....
}bluetooth_send_data;

#define Bluetooth_Rec_DataLen	16
#define Bluetooth_Send_DataLen	23
//-------------------------------------

void Short_To_Byte(short *target, uint8_t *buff, uint8_t position);
short Byte_to_Short(uint8_t *buff, uint8_t position);
void Int_To_Byte(int *target, uint8_t *buff, uint8_t position);
int Byte_to_Int(uint8_t *buff, uint8_t position);
void Float_To_Byte(float *target, uint8_t *buff, uint8_t position);
float Byte_to_Float(uint8_t *buff, uint8_t position);

void Bluetooth_Init(void);
uint8_t Bluetooth_CheckData(uint8_t *data);

void Bluetooth_Creat_SendData(void);
void Bluetooth_Send(void);

void Bluetooth_Get_Rec_Data(uint8_t *data);
void Bluetooth_Recieve(void);


void Bluetooth_Control(void);

extern bluetooth_rec_data Bluetooth_Rec_Data;
extern bluetooth_send_data Bluetooth_Send_Data;
extern uint8_t Bluetooth_Recieve_Buff[Bluetooth_Rec_DataLen];
extern uint8_t Bluetooth_Send_Buff[Bluetooth_Send_DataLen];

extern uint8_t Bluetooth_Rx_flag;


#endif

