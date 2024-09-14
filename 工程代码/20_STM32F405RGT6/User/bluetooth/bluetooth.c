#include "bluetooth.h"

#include "motor/motor.h"
#include "servo/servo.h"
#include "adcc/adcc.h"
#include "mpu6050/mpu6050_dmp.h"
#include "radar/radar.h"

bluetooth_rec_data Bluetooth_Rec_Data = {0};
bluetooth_send_data Bluetooth_Send_Data = {0};

uint8_t Bluetooth_Recieve_Buff[Bluetooth_Rec_DataLen] = {0};	//���ݽ��ջ�����
uint8_t Bluetooth_Send_Buff[Bluetooth_Send_DataLen] = {0};       //���ݷ��ͻ�����

uint8_t Bluetooth_Rx_flag = 0;


/**
 * @brief 	shortתbyte
 * @param	targetΪָ����Ҫ����Ĳ�����buffΪд���byte���飬positionΪд���λ��
 * @retval	��
 */
void Short_To_Byte(short *target, uint8_t *buff, uint8_t position){
	
	uint8_t *ptr = (uint8_t *)target;
	buff[position] = ptr[0];
	buff[position + 1] = ptr[1];
}

/**
 * @brief	byteתshort
 * @param	buffΪ��ת��byte���飬positionΪ��ʼת��λ��
 * @retval	short���
 */
short Byte_to_Short(uint8_t *buff, uint8_t position){
	
	short res;
	res = buff[position] & 0xFF;
	res |= ((buff[position+1] << 8) & 0xFF00);
	return res;
}

/**
 * @brief 	intתbyte
 * @param	targetΪָ����Ҫ����Ĳ�����buffΪд���byte���飬positionΪд���λ��
 * @retval	��
 */
void Int_To_Byte(int *target, uint8_t *buff, uint8_t position){
	
	uint8_t *ptr = (uint8_t *)target;
	buff[position] = ptr[0];
	buff[position+1] = ptr[1];
	buff[position+2] = ptr[2];
	buff[position+3] = ptr[3];

}

/**
 * @brief	byteתint
 * @param	buffΪ��ת��byte���飬positionΪ��ʼת��λ��
 * @retval	short���
 */
int Byte_to_Int(uint8_t *buff, uint8_t position){

	int res;
	res = buff[position] & 0xFF;
	res |= ((buff[position + 1] << 8) & 0xFF00);
	res |= ((buff[position + 2] << 16) & 0xFF0000);
	res |= ((buff[position + 3] << 24) & 0xFF000000);
	return res;
}

/**
 * @brief 	floatתbyte
 * @param	targetΪָ����Ҫ����Ĳ�����buffΪд���byte���飬positionΪд���λ��
 * @retval	��
 */
void Float_To_Byte(float *target, uint8_t *buff, uint8_t position){
	
	uint8_t *ptr = (uint8_t *)target;
	buff[position] = ptr[0];
	buff[position+1] = ptr[1];
	buff[position+2] = ptr[2];
	buff[position+3] = ptr[3];
}

/**
 * @brief	byteתfloat
 * @param	buffΪ��ת��byte���飬positionΪ��ʼת��λ��
 * @retval	short���
 */
float Byte_to_Float(uint8_t *buff, uint8_t position){

	int res;//������������������������������������
	res = buff[position] & 0xFF;
	res |= ((buff[position + 1] << 8) & 0xFF00);
	res |= ((buff[position + 2] << 16) & 0xFF0000);
	res |= ((buff[position + 3] << 24) & 0xFF000000);
	return *(float*)&res;
	
}


/**
 * @brief	����ģ���ʼ��
 * @param
 * @retval
 */
void Bluetooth_Init(void){
	
	__HAL_UART_ENABLE_IT(&huart4,UART_IT_RXNE);
	HAL_UART_Receive_IT(&huart4,Bluetooth_Recieve_Buff,Bluetooth_Rec_DataLen);

}

/**
 * @brief	�����ݰ�����У��
 * @param	dataΪ���ݰ�
 * @retval	1��֤ͨ��,0��֤��ͨ��
 */
uint8_t Bluetooth_CheckData(uint8_t *data){
	
	uint8_t datasum = 0;   //У���
	uint8_t data_len = Bluetooth_Rec_DataLen;
	int i;
	if(data[0] == 0xA5 && data[data_len-1] == 0x5A){
		for(i = 1; i < data_len-2; i++){
			datasum += data[i];			
		}
		if(datasum == data[data_len-2])	return 1;
	}
	return 0;
}


/**
* @brief	�����������ݰ�(���Ͳ�ͬ��������Ҫ�޸ı�����)----------------------------
* @param	MCU��Ҫ���͵�����
 * @retval	��
 */
void Bluetooth_Creat_SendData(void){

	uint8_t datasum = 0;
	Bluetooth_Send_Buff[0] = 0xA5;
	Bluetooth_Send_Buff[Bluetooth_Send_DataLen-1] = 0x5A;
	
	//�ڴ˶�����ҪMCU���͵�����----------
	
//	//Control_2_send----------------
//	Short_To_Btye(&Bluetooth_Send_Data.y, Bluetooth_Send_Buff, 1);
//	Int_To_Btye(&Bluetooth_Send_Data.speed, Bluetooth_Send_Buff, 1 + 2);
//	Float_To_Btye(&Bluetooth_Send_Data.pitch, Bluetooth_Send_Buff, 1 + 2 + 4);
//	//-----------------------------
	
	//Bluetooth_Control_send----------
	Bluetooth_Send_Buff[1] = Bluetooth_Send_Data.Flag_north;
	Bluetooth_Send_Buff[1+1] = Bluetooth_Send_Data.Flag_east;
	Bluetooth_Send_Buff[1+1+1] = Bluetooth_Send_Data.Flag_south;
	Bluetooth_Send_Buff[1+1+1+1] = Bluetooth_Send_Data.Flag_west;
	Int_To_Byte(&Bluetooth_Send_Data.Angle,Bluetooth_Send_Buff,1 + 1 + 1 + 1 + 1);
	Int_To_Byte(&Bluetooth_Send_Data.Speed,Bluetooth_Send_Buff,1 + 1 + 1 + 1 + 1 + 4);
	Float_To_Byte(&Bluetooth_Send_Data.Voltage,Bluetooth_Send_Buff,1 + 1 + 1 + 1 + 1 + 4 + 4);
	Float_To_Byte(&MPU6050_Data_DMP.Pitch,Bluetooth_Send_Buff,1 + 1 + 1 + 1 + 1 + 4 + 4 + 4);
	
	//----------------------------------
	
	int i;
	for(i=1;i<Bluetooth_Send_DataLen-2;i++){
		datasum += Bluetooth_Send_Buff[i];
	}
	Bluetooth_Send_Buff[Bluetooth_Send_DataLen-2] = (datasum&0xff);//д��У��λ
}

/**
* @brief	����ģ�鷢������
 * @param	��
 * @retval	��
 */
void Bluetooth_Send(void){
	
	Bluetooth_Creat_SendData();
	HAL_UART_Transmit(&huart4,Bluetooth_Send_Buff,Bluetooth_Send_DataLen,1000);
	while(HAL_UART_GetState(&huart4) == SET);

}

/**
 * @brief	�Խ������ݰ����н��(���ղ�ͬ��������Ҫ�޸ı�����)------------------------------
 * @param	dataΪ�������ݰ�
 * @retval	��
 */	
void Bluetooth_Get_Rec_Data(uint8_t *data){
	
	//�ڴ˶�����ҪMCU���յ�����----------
	
//	//Control_2_recieve----------------
//	Bluetooth_Rec_Data.LedStatus = data[1];
//	Bluetooth_Rec_Data.med_angle = Btye_to_Float(data,1+1);
//	Bluetooth_Rec_Data.vertical_kp = Btye_to_Float(data,1+1+4);
//	Bluetooth_Rec_Data.vertical_kd = Btye_to_Float(data,1+1+4+4);
//	Bluetooth_Rec_Data.velocity_kp = Btye_to_Float(data,1+1+4+4+4);
//	Bluetooth_Rec_Data.velocity_ki = Btye_to_Float(data,1+1+4+4+4+4);
//	//---------------------------------
	
	//Bluetooth_Control_recieve----------
	Bluetooth_Rec_Data.Radar_Enable = data[1];
	Bluetooth_Rec_Data.Dir_On = data[1+1];
	Bluetooth_Rec_Data.Dir_Down = data[1+1+1];
	Bluetooth_Rec_Data.Dir_Left = data[1+1+1+1];
	Bluetooth_Rec_Data.Dir_Right = data[1+1+1+1+1];
	Bluetooth_Rec_Data.Angle = Byte_to_Int(data,1+1+1+1+1+1);
	Bluetooth_Rec_Data.Speed = Byte_to_Int(data,1+1+1+1+1+1+4);
	//----------------------------------
}

/**
 * @brief	����ģ�����
 * @param	��
 * @retval	��
 */
void Bluetooth_Recieve(void){

	//���պ�����stm32f4xx_it.c��
	if(Bluetooth_CheckData(Bluetooth_Recieve_Buff)){
		Bluetooth_Get_Rec_Data(Bluetooth_Recieve_Buff);
	}

}

/**
 * @brief	��������
 * @param	��
 * @retval	��
 */
void Bluetooth_Control(void)
{	

	static int Speed = 200;
	static int Angle = 0;
	
	if(Bluetooth_Rx_flag == 1)
	{
		Bluetooth_Recieve();
		Bluetooth_Rx_flag = 0;
	}
	
	Radar_Enable = Bluetooth_Rec_Data.Radar_Enable;
	uint8_t Dir_On = Bluetooth_Rec_Data.Dir_On;
	uint8_t Dir_Down = Bluetooth_Rec_Data.Dir_Down;
    uint8_t Dir_Left = Bluetooth_Rec_Data.Dir_Left;
	uint8_t Dir_Right = Bluetooth_Rec_Data.Dir_Right;
	Speed = Bluetooth_Rec_Data.Speed;
	Angle = Bluetooth_Rec_Data.Angle;
	
	if(Radar_Enable == 0)
	{	
		if(Dir_On)
			Set_PwmB(Speed);
		else if(Dir_Down)
			Set_PwmB(-Speed);
		else
			Set_PwmB(0);

		if(Dir_Left)
		{
			SERVO_Left(Angle);
		}
		else if(Dir_Right)
		{
			SERVO_Right(Angle);
		}
	}
	
	Bluetooth_Send_Data.Flag_north = flag_north;
	Bluetooth_Send_Data.Flag_east = flag_east;
	Bluetooth_Send_Data.Flag_south = flag_south;
	Bluetooth_Send_Data.Flag_west = flag_west;
	Bluetooth_Send_Data.Angle = Angle;
	Bluetooth_Send_Data.Speed = Speed;
	Bluetooth_Send_Data.Voltage = Get_Voltage();
	Bluetooth_Send();
}
