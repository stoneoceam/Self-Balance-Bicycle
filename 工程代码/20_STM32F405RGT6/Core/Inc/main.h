/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOC
#define B_ENCODER_A_Pin GPIO_PIN_0
#define B_ENCODER_A_GPIO_Port GPIOA
#define B_ENCODER_B_Pin GPIO_PIN_1
#define B_ENCODER_B_GPIO_Port GPIOA
#define Servo_1_Pin GPIO_PIN_2
#define Servo_1_GPIO_Port GPIOA
#define Servo_2_Pin GPIO_PIN_3
#define Servo_2_GPIO_Port GPIOA
#define STBY_Pin GPIO_PIN_4
#define STBY_GPIO_Port GPIOA
#define PWM_A_Pin GPIO_PIN_5
#define PWM_A_GPIO_Port GPIOA
#define PWM_B_Pin GPIO_PIN_6
#define PWM_B_GPIO_Port GPIOA
#define BIN1_Pin GPIO_PIN_7
#define BIN1_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_4
#define BIN2_GPIO_Port GPIOC
#define Voltage_Pin GPIO_PIN_5
#define Voltage_GPIO_Port GPIOC
#define USB_TX_Pin GPIO_PIN_10
#define USB_TX_GPIO_Port GPIOB
#define USB_RX_Pin GPIO_PIN_11
#define USB_RX_GPIO_Port GPIOB
#define LED_Blue_Pin GPIO_PIN_12
#define LED_Blue_GPIO_Port GPIOB
#define LED_Green_Pin GPIO_PIN_13
#define LED_Green_GPIO_Port GPIOB
#define LED_Red_Pin GPIO_PIN_14
#define LED_Red_GPIO_Port GPIOB
#define CAMERA_TX_Pin GPIO_PIN_6
#define CAMERA_TX_GPIO_Port GPIOC
#define CAMERA_RX_Pin GPIO_PIN_7
#define CAMERA_RX_GPIO_Port GPIOC
#define INT_Pin GPIO_PIN_8
#define INT_GPIO_Port GPIOC
#define INT_EXTI_IRQn EXTI9_5_IRQn
#define MPU6050_SDA_Pin GPIO_PIN_9
#define MPU6050_SDA_GPIO_Port GPIOC
#define MPU6050_SCL_Pin GPIO_PIN_8
#define MPU6050_SCL_GPIO_Port GPIOA
#define RADAR_TX_Pin GPIO_PIN_9
#define RADAR_TX_GPIO_Port GPIOA
#define RADAR_RX_Pin GPIO_PIN_10
#define RADAR_RX_GPIO_Port GPIOA
#define BLUETOOTH_TX_Pin GPIO_PIN_10
#define BLUETOOTH_TX_GPIO_Port GPIOC
#define BLUETOOTH_RX_Pin GPIO_PIN_11
#define BLUETOOTH_RX_GPIO_Port GPIOC
#define A_DIR_Pin GPIO_PIN_4
#define A_DIR_GPIO_Port GPIOB
#define A_EN_Pin GPIO_PIN_5
#define A_EN_GPIO_Port GPIOB
#define A_ENCODER_B_Pin GPIO_PIN_6
#define A_ENCODER_B_GPIO_Port GPIOB
#define A_ENCODER_A_Pin GPIO_PIN_7
#define A_ENCODER_A_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
