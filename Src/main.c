/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
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

/* USER CODE BEGIN PV */
uint8_t	txDataBuffer[8],rxDataBuffer0[8],rxDataBuffer1[8];
uint16_t txId = 0x200;
uint32_t txMailbox;
CAN_TxHeaderTypeDef	txHeader;	//�洢���ͽ��պ�
CAN_RxHeaderTypeDef	rxHeader0,rxHeader1;
bool pa0Pressed = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void CAN_ConfigFilter();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */
  CAN_ConfigFilter();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET && !pa0Pressed){	//������
		pa0Pressed = true;
		txHeader.StdId = txId;		//����ID��
		txHeader.IDE = CAN_ID_STD;	//ѡ��Ϊ��׼֡
		txHeader.RTR = CAN_RTR_DATA;	//ѡ��Ϊ����֡
		txHeader.DLC = 8;
		*((uint32_t*)(txDataBuffer)) = HAL_GetTick();
		if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 0){
			HAL_CAN_AddTxMessage(&hcan1,&txHeader,txDataBuffer,&txMailbox);		//�ж���ǰ�Ƿ��п�������
		}
	  }
	  else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_SET && pa0Pressed){	//�½���
		  pa0Pressed = false;
	  }
	  HAL_Delay(100);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//���ù�����
void CAN_ConfigFilter(){
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;	//���ù�����
	sFilterConfig.FilterBank = 0;	//��������ţ�CAN1��0-13��CAN2��14-27��������ѡ��0�Ź�����
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;	//ѡ���������
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	//����
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//32λ
	sFilterConfig.FilterIdHigh = 0x00;
	sFilterConfig.FilterIdLow = 0x00;
	sFilterConfig.FilterMaskIdHigh = 0x00;
	sFilterConfig.FilterMaskIdLow = 0x00;
	sFilterConfig.SlaveStartFilterBank = 14; //��ֵ
	
	if(HAL_CAN_ConfigFilter(&hcan1,&sFilterConfig))	//����can1�Ĺ�����0�ĸ������
	{	
		
		Error_Handler();	//������ô��������˺���
	}
	
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;	//���ù�����
	sFilterConfig.FilterBank = 14;	//��������ţ�CAN1��0-13��CAN2��14-27��������ѡ��14�Ź�����
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;	//ѡ��FIFO0��������
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;	//�б�
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;	//16λ
	sFilterConfig.FilterIdHigh = 0x201<<5;
	sFilterConfig.FilterIdLow = 0x202<<5;
	sFilterConfig.FilterMaskIdHigh = 0x203<<5;
	sFilterConfig.FilterMaskIdLow = 0x204<<5;
	sFilterConfig.SlaveStartFilterBank = 14; //��ֵ
	
	if(HAL_CAN_ConfigFilter(&hcan2,&sFilterConfig))	//����can2�Ĺ�����14�������
	{	
		
		Error_Handler();	//������ô��������˺���
	}
	
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;	//���ù�����
	sFilterConfig.FilterBank = 15;	//��������ţ�CAN1��0-13��CAN2��14-27��������ѡ��15�Ź�����
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO1;	//ѡ��FIFO1��������
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	//����
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;	//16λ
	sFilterConfig.FilterIdHigh = 0x201<<5;
	sFilterConfig.FilterMaskIdHigh = 0x7F0<<5;	//����0x200~0x20F��ID
	sFilterConfig.FilterIdLow = 0x000<<5;
	sFilterConfig.FilterMaskIdLow = 0xFFFF<<5;
	sFilterConfig.SlaveStartFilterBank = 14; //��ֵ
	
	if(HAL_CAN_ConfigFilter(&hcan2,&sFilterConfig))	//����can2�Ĺ�����15�������
	{	
		
		Error_Handler();	//������ô��������˺���
	}
	
	if(HAL_CAN_Start(&hcan1) != HAL_OK){	//��ʽ����can1
		Error_Handler();
	}
	
	if(HAL_CAN_Start(&hcan2) != HAL_OK){	//��ʽ����can2
		Error_Handler();
	}
	
	if(HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK){
		Error_Handler();
	}
	
	if(HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK){
		Error_Handler();
	}
}
//CAN2 FIFO0�ж�
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	if(hcan == &hcan2){
		HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO0,&rxHeader0,rxDataBuffer0);
	}
}
//CAN2 FIFO1�ж�
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan){
	if(hcan == &hcan2){
		HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO1,&rxHeader1,rxDataBuffer1);
	}
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
