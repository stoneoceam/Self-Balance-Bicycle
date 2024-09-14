#include "mpu6050.h"

/**
* @brief 写寄存器，这是提供给上层的接口
* @param slave_addr: 从机地址
* @param reg_addr: 寄存器地址
* @param len：写入的长度
* @param data_ptr: 指向要写入的数据
* @retval 正常为 0，不正常为非 0
*/
HAL_StatusTypeDef Sensors_I2C_WriteRegister(uint16_t slave_addr, uint16_t reg_addr, uint16_t len, uint8_t *data_ptr){
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c3, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data_ptr,len, 1000);
	if(status != HAL_OK){
		
	}
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
	
	}
	/* 检查 SENSOR 是否就绪进行下一次读写操作 */
	while (HAL_I2C_IsDeviceReady(&hi2c3, slave_addr, 10, 1000) == HAL_TIMEOUT);
	/* 等待传输结束 */
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
	
	}
	return status;
}

/**
* @brief 读寄存器，这是提供给上层的接口
* @param slave_addr: 从机地址
* @param reg_addr: 寄存器地址
* @param len：要读取的长度
* @param data_ptr: 指向要存储数据的指针
* @retval 正常为 0，不正常为非 0
*/
HAL_StatusTypeDef Sensors_I2C_ReadRegister(uint16_t slave_addr, uint16_t reg_addr, uint16_t len, uint8_t *data_ptr){
	HAL_StatusTypeDef status = HAL_OK;
	status =HAL_I2C_Mem_Read(&hi2c3, slave_addr ,reg_addr,I2C_MEMADD_SIZE_8BIT, data_ptr, len, 1000);
	if (status != HAL_OK) {/* 检查通讯状态 */

	}
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
		
	}
	/* 检查 SENSOR 是否就绪进行下一次读写操作 */
	while (HAL_I2C_IsDeviceReady(&hi2c3, slave_addr, 10, 1000) == HAL_TIMEOUT);
	/* 等待传输结束 */
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY) {
		
	}
	return status;
}

/**
	* @brief 写数据到 MPU6050 寄存器
	* @param reg_add: 寄存器地址
	* @param reg_data: 要写入的数据
	* @retval
	*/
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat){
	Sensors_I2C_WriteRegister(MPU6050_ADDRESS,reg_add,1,&reg_dat);
}

/**
	* @brief 从 MPU6050 寄存器读取数据
	* @param reg_add: 寄存器地址
	* @param Read：存储数据的缓冲区
	* @param num：要读取的数据量
	* @retval
	*/
void MPU6050_ReadData(uint8_t reg_add,uint8_t* Read,uint8_t num){
	Sensors_I2C_ReadRegister(MPU6050_ADDRESS,reg_add,num,Read);
}

/**
	* @brief 初始化 MPU6050 芯片
	* @param
	* @retval
	*/
void MPU6050_Init(void){
	//在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
	HAL_Delay(100);
	MPU6050_WriteReg(MPU_PWR_MGMT1_REG,0x80);//复位MPU6050
	HAL_Delay(100);
	MPU6050_WriteReg(MPU_PWR_MGMT1_REG, 0x00);//唤醒MPU6050 
	MPU6050_Set_Gyro_Fsr(3);//陀螺仪传感器,±2000dps
	MPU6050_Set_Accel_Fsr(0);//加速度传感器,±2g
	MPU6050_Set_Rate(200);//设置采样率50Hz
	MPU6050_WriteReg(MPU_INT_EN_REG,0X01);//使能所有中断
	MPU6050_WriteReg(MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
	MPU6050_WriteReg(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU6050_WriteReg(MPU_INTBP_CFG_REG,0X80);//INT引脚低电平有效
	
	uint8_t res;
	res = MPU6050_Get_ID();
	

}

/**
	* @brief 读取 MPU6050 的 ID
	* @param
	* @retval 正常返回 1，异常返回 0
	*/
uint8_t MPU6050_Get_ID(void){
	uint8_t Re = 0;
	MPU6050_ReadData(WHO_AM_I,&Re,1); //读器件地址
	if (Re != 0x68) {
		printf("检测不到 MPU6050 模块，请检查模块与开发板的接线,------%d\r\n",Re);
		return 0;
	} else {
		MPU6050_WriteReg(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU6050_WriteReg(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU6050_Set_Rate(200);						//设置采样率为100Hz
		printf("MPU6050 ID = 0x%x\r\n",Re);
		return 1;
	}
}

//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
void MPU6050_Set_Gyro_Fsr(uint8_t fsr)
{
	MPU6050_WriteReg(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}

//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
void MPU6050_Set_Accel_Fsr(uint8_t fsr)
{
	MPU6050_WriteReg(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void MPU6050_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	MPU6050_WriteReg(MPU_CFG_REG,data);//设置数字低通滤波器  
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void MPU6050_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	MPU6050_WriteReg(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	MPU6050_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

/**
	* @brief 读取 MPU6050 的角加速度数据
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
	* @brief 读取 MPU6050 的角速度数据
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
	* @brief 读取 MPU6050 的温度数据，转化成摄氏度
	* @param
	* @retval
	*/
void MPU6050_Get_Temp(float *Temperature){
	int16_t temp3;
	uint8_t buf[2];
	MPU6050_ReadData(MPU_TEMP_OUTH_REG,buf,2); //读取温度值
	temp3= (buf[0] << 8) | buf[1];
	*Temperature= ((float)temp3/340) + 36.53f;
}




