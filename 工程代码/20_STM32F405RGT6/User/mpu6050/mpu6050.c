#include "mpu6050.h"

/**
* @brief д�Ĵ����������ṩ���ϲ�Ľӿ�
* @param slave_addr: �ӻ���ַ
* @param reg_addr: �Ĵ�����ַ
* @param len��д��ĳ���
* @param data_ptr: ָ��Ҫд�������
* @retval ����Ϊ 0��������Ϊ�� 0
*/
HAL_StatusTypeDef Sensors_I2C_WriteRegister(uint16_t slave_addr, uint16_t reg_addr, uint16_t len, uint8_t *data_ptr){
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c3, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data_ptr,len, 1000);
	if(status != HAL_OK){
		
	}
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
	
	}
	/* ��� SENSOR �Ƿ����������һ�ζ�д���� */
	while (HAL_I2C_IsDeviceReady(&hi2c3, slave_addr, 10, 1000) == HAL_TIMEOUT);
	/* �ȴ�������� */
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
	
	}
	return status;
}

/**
* @brief ���Ĵ����������ṩ���ϲ�Ľӿ�
* @param slave_addr: �ӻ���ַ
* @param reg_addr: �Ĵ�����ַ
* @param len��Ҫ��ȡ�ĳ���
* @param data_ptr: ָ��Ҫ�洢���ݵ�ָ��
* @retval ����Ϊ 0��������Ϊ�� 0
*/
HAL_StatusTypeDef Sensors_I2C_ReadRegister(uint16_t slave_addr, uint16_t reg_addr, uint16_t len, uint8_t *data_ptr){
	HAL_StatusTypeDef status = HAL_OK;
	status =HAL_I2C_Mem_Read(&hi2c3, slave_addr ,reg_addr,I2C_MEMADD_SIZE_8BIT, data_ptr, len, 1000);
	if (status != HAL_OK) {/* ���ͨѶ״̬ */

	}
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
		
	}
	/* ��� SENSOR �Ƿ����������һ�ζ�д���� */
	while (HAL_I2C_IsDeviceReady(&hi2c3, slave_addr, 10, 1000) == HAL_TIMEOUT);
	/* �ȴ�������� */
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
		
	}
	return status;
}

/**
	* @brief д���ݵ� MPU6050 �Ĵ���
	* @param reg_add: �Ĵ�����ַ
	* @param reg_data: Ҫд�������
	* @retval
	*/
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat){
	Sensors_I2C_WriteRegister(MPU6050_ADDRESS,reg_add,1,&reg_dat);
}

/**
	* @brief �� MPU6050 �Ĵ�����ȡ����
	* @param reg_add: �Ĵ�����ַ
	* @param Read���洢���ݵĻ�����
	* @param num��Ҫ��ȡ��������
	* @retval
	*/
void MPU6050_ReadData(uint8_t reg_add,uint8_t* Read,uint8_t num){
	Sensors_I2C_ReadRegister(MPU6050_ADDRESS,reg_add,num,Read);
}

/**
	* @brief ��ʼ�� MPU6050 оƬ
	* @param
	* @retval
	*/
void MPU6050_Init(void){
	//�ڳ�ʼ��֮ǰҪ��ʱһ��ʱ�䣬��û����ʱ����ϵ�����ϵ����ݿ��ܻ����
	HAL_Delay(100);
	MPU6050_WriteReg(MPU_PWR_MGMT1_REG,0x80);//��λMPU6050
	HAL_Delay(100);
	MPU6050_WriteReg(MPU_PWR_MGMT1_REG, 0x00);//����MPU6050 
	MPU6050_Set_Gyro_Fsr(3);//�����Ǵ�����,��2000dps
	MPU6050_Set_Accel_Fsr(0);//���ٶȴ�����,��2g
	MPU6050_Set_Rate(200);//���ò�����50Hz
	MPU6050_WriteReg(MPU_INT_EN_REG,0X01);//ʹ�������ж�
	MPU6050_WriteReg(MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
	MPU6050_WriteReg(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU6050_WriteReg(MPU_INTBP_CFG_REG,0X80);//INT���ŵ͵�ƽ��Ч
	
	uint8_t res;
	res = MPU6050_Get_ID();
	

}

/**
	* @brief ��ȡ MPU6050 �� ID
	* @param
	* @retval �������� 1���쳣���� 0
	*/
uint8_t MPU6050_Get_ID(void){
	uint8_t Re = 0;
	MPU6050_ReadData(WHO_AM_I,&Re,1); //��������ַ
	if (Re != 0x68) {
		printf("��ⲻ�� MPU6050 ģ�飬����ģ���뿪����Ľ���,------%d\r\n",Re);
		return 0;
	} else {
		MPU6050_WriteReg(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU6050_WriteReg(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU6050_Set_Rate(200);						//���ò�����Ϊ100Hz
		printf("MPU6050 ID = 0x%x\r\n",Re);
		return 1;
	}
}

//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU6050_Set_Gyro_Fsr(uint8_t fsr)
{
	MPU6050_WriteReg(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}

//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU6050_Set_Accel_Fsr(uint8_t fsr)
{
	MPU6050_WriteReg(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}

//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU6050_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	MPU6050_WriteReg(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU6050_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	MPU6050_WriteReg(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	MPU6050_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

/**
	* @brief ��ȡ MPU6050 �ĽǼ��ٶ�����
	* @param
	* @retval
	*/
void MPU6050_Get_Acc(acc *Acc){
	uint8_t buf[6];
	MPU6050_ReadData(MPU_ACCEL_XOUTH_REG, buf, 6);
	Acc->x = (buf[0] << 8) | buf[1];
	Acc->y = (buf[2] << 8) | buf[3];
	Acc->z = (buf[4] << 8) | buf[5];
}

/**
	* @brief ��ȡ MPU6050 �Ľ��ٶ�����
	* @param
	* @retval
	*/
void MPU6050_Get_Gyro(gyro *Gyro){
	uint8_t buf[6];
	MPU6050_ReadData(MPU_GYRO_XOUTH_REG,buf,6);
	Gyro->x = (buf[0] << 8) | buf[1];
	Gyro->y = (buf[2] << 8) | buf[3];
	Gyro->z = (buf[4] << 8) | buf[5];
}


/**
	* @brief ��ȡ MPU6050 ���¶����ݣ�ת�������϶�
	* @param
	* @retval
	*/
void MPU6050_Get_Temp(float *Temperature){
	int16_t temp3;
	uint8_t buf[2];
	MPU6050_ReadData(MPU_TEMP_OUTH_REG,buf,2); //��ȡ�¶�ֵ
	temp3= (buf[0] << 8) | buf[1];
	*Temperature= ((float)temp3/340) + 36.53f;
}




