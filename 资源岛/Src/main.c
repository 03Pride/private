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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "choose.h"
#include "put.h"
#include "exit.h"
#include "Delay.h"
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
//int count_left, count_mid, count_right;
uint8_t led_left_on ='0';
uint8_t led_left_off ='1';
uint8_t led_mid_on ='2';
uint8_t led_mid_off ='3';
uint8_t led_right_on ='4';
uint8_t led_right_off ='5';
//uint8_t Rxbuf;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT((TIM_HandleTypeDef *)&htim1);
  HAL_UART_Receive_IT(&huart2,&Rxbuf,1);     //¿ªÆôÖÐ¶Ï
  HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_1);
  HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_2);
  HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_2, 21);
//            HAL_Delay(100);
//	  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{				
//		
//	delay_ms(30);
////	HAL_Delay(20);
//	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
//	if(GPIO_Pin == GPIO_PIN_0){
//		count_left++;
//		if(count_left%2!=0){
//		   __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,5);
//		//	    delay_ms(100);
//				HAL_Delay(100);
//		}
//		else {
//			  __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,20);
//				HAL_Delay(100);
//		}
//	}
//	if(GPIO_Pin == GPIO_PIN_4){
//		count_mid++;
//		if(count_mid%2!=0){
//		   __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,5);
//		//	    delay_ms(100);
//				HAL_Delay(100);
//		}
//		else {
//			  __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,20);
//				HAL_Delay(100);
//		}
//	}
//	if(GPIO_Pin == GPIO_PIN_5){
//		count_right++;
//		if(count_right%2!=0){
//		   __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,5);
//		//	    delay_ms(100);
//				HAL_Delay(100);
//		}
//		else {
//			  __HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,20);
//				HAL_Delay(100);
//		}
//	}	
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART2)	
//	{
//		if(Rxbuf == led_left_on){
//			count_left++;
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,20);
//			HAL_Delay(100);
//		}else if(Rxbuf == led_left_off){
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,5);
//			HAL_Delay(100);
//		}
//		if(Rxbuf == led_mid_on){
//			count_mid++;
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,20);
//			HAL_Delay(100);
//		}else if(Rxbuf == led_mid_off){
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,5);
//			HAL_Delay(100);
//		}
//		if(Rxbuf == led_right_on){
//			count_right++;
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,20);
//			HAL_Delay(100);
//		}else if(Rxbuf == led_right_off){
//			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//			__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,5);
//			HAL_Delay(100);
//		}
//		HAL_UART_Receive_IT(&huart2,&Rxbuf,1);		
//	}
//}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
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
