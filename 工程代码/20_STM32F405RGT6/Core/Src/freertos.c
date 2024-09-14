/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "./led/led.h"
#include "./oled/oled.h"
#include "./debug/debug.h"
#include "./adcc/adcc.h"
#include "./buzzer/buzzer.h"
#include "./servo/servo.h"
#include "./motor/motor.h"
#include "./mpu6050/mpu6050.h"
#include "./mpu6050/mpu6050_dmp.h"
#include "./mpu6050/mpu6050_imu.h"
#include "./bluetooth/bluetooth.h"
#include "./radar/radar.h"
#include "./control/control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for BalanceTask */
osThreadId_t BalanceTaskHandle;
const osThreadAttr_t BalanceTask_attributes = {
  .name = "BalanceTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for CommunicationTask */
osThreadId_t CommunicationTaskHandle;
const osThreadAttr_t CommunicationTask_attributes = {
  .name = "CommunicationTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for AvoidanceTask */
osThreadId_t AvoidanceTaskHandle;
const osThreadAttr_t AvoidanceTask_attributes = {
  .name = "AvoidanceTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartBalanceTask(void *argument);
void StartCommunicationTask(void *argument);
void StartAvoidanceTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of BalanceTask */
  BalanceTaskHandle = osThreadNew(StartBalanceTask, NULL, &BalanceTask_attributes);

  /* creation of CommunicationTask */
  CommunicationTaskHandle = osThreadNew(StartCommunicationTask, NULL, &CommunicationTask_attributes);

  /* creation of AvoidanceTask */
  AvoidanceTaskHandle = osThreadNew(StartAvoidanceTask, NULL, &AvoidanceTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	
	
	OLED_ShowString(0,0,(char*)"Voltage:",16,0); OLED_Showdecimal(64,0,Get_Voltage(),2,1,16, 0); OLED_ShowString(96,0,(char*)"V",16,0);
	OLED_ShowString(0,2,(char*)"Pitch:",16,0); OLED_Showdecimal(48,2,MPU6050_Data_DMP.Pitch,2,1,16,0);
	OLED_ShowString(0,4,(char*)"Yaw:",16,0); OLED_Showdecimal(32,4,MPU6050_Data_DMP.Yaw,2,1,16,0);  
	OLED_ShowString(0,6,(char*)"Speed:",16,0);OLED_Showdecimal(48,6,MotorA.cur_speed,3,1,16,0);
	
	Voltage_Control();
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartBalanceTask */
/**
* @brief Function implementing the BalanceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBalanceTask */
void StartBalanceTask(void *argument)
{
  /* USER CODE BEGIN StartBalanceTask */
  /* Infinite loop */
  for(;;)
  {
	
	//编码器速度采集  
	MotorA.totalCount = __HAL_TIM_GET_COUNTER(&htim4) + MotorA.overflowNum*65535 - MotorA.lastCount;
	MotorA.lastCount = __HAL_TIM_GET_COUNTER(&htim4) + MotorA.overflowNum*65535;
	MotorA.overflowNum = 0;
	MotorA.cur_speed = MotorA.totalCount; 

	MPU6050_DMP_Get_Data(&MPU6050_Data_DMP.Pitch, &MPU6050_Data_DMP.Roll, &MPU6050_Data_DMP.Yaw);
	MPU6050_Get_Acc(&MPU6050_Data_DMP.Acc);
	//MPU6050_Get_Acc(&MPU6050_Data_IMU.Acc);
	MPU6050_Get_Gyro(&MPU6050_Data_DMP.Gyro);
	//MPU6050_Get_Gyro(&MPU6050_Data_IMU.Gyro);

	//MPU6050_IMU_Get_Data(&MPU6050_Data_IMU.Pitch, &MPU6050_Data_IMU.Roll, 0.01f);

	//Control_1();
	Control_2();
	printf("%f\n",MPU6050_Data_DMP.Pitch);
	  
	
	
	osDelay(5);
  }
  /* USER CODE END StartBalanceTask */
}

/* USER CODE BEGIN Header_StartCommunicationTask */
/**
* @brief Function implementing the CommunicationTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCommunicationTask */
void StartCommunicationTask(void *argument)
{
  /* USER CODE BEGIN StartCommunicationTask */
  /* Infinite loop */
  for(;;)
  {
	  
//	 //Control_2_recieve 
//	if(Bluetooth_Rx_flag == 1){
//		
//		
//		Bluetooth_Recieve();
//		Bluetooth_Rx_flag = 0;
//	}
//	
//	
//	if(Bluetooth_Rec_Data.LedStatus == 1)
//		LED_Blue_On();
//	else
//		LED_Blue_Off();
//	Med_Angle = Bluetooth_Rec_Data.med_angle;
//	Vertical_Kp = Bluetooth_Rec_Data.vertical_kp;
//	Vertical_Kd = Bluetooth_Rec_Data.vertical_kd;
//	Velocity_Kp = Bluetooth_Rec_Data.velocity_kp;
//	Velocity_Ki = Bluetooth_Rec_Data.velocity_ki;
//	//----
//	//Control_2_send
//	Bluetooth_Send_Data.speed = (int)MotorA.tar_speed;
//	Bluetooth_Send_Data.pitch = MPU6050_Data_DMP.Pitch;
//	Bluetooth_Send_Data.y = MPU6050_Data_DMP.Gyro.y;
//  Bluetooth_Send();
//	//-------------
	
	Bluetooth_Control();

	
	
    osDelay(50);
  }
  /* USER CODE END StartCommunicationTask */
}

/* USER CODE BEGIN Header_StartAvoidanceTask */
/**
* @brief Function implementing the AvoidanceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAvoidanceTask */
void StartAvoidanceTask(void *argument)
{
  /* USER CODE BEGIN StartAvoidanceTask */
  /* Infinite loop */
  for(;;)
  {
	
	Radar_Control();

    osDelay(10);
  }
  /* USER CODE END StartAvoidanceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */


/* USER CODE END Application */

