#define __EXIT_GLOBALS

#include "exit.h"
#include "tim.h"
#include <stdint.h>
#include "main.h"
#include "Delay.h"

/**
  *************************************************************************
  *@brief  按键外部中断发送函数
  *@author HZH
  *@date 2022/04/26
  *************************************************************************
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

    delay_ms(30);
//	HAL_Delay(20);
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

    if(GPIO_Pin == GPIO_PIN_0)
    {
        count_left++;

        if(count_left % 2 != 0)
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_1, 5);
            //	    delay_ms(100);
            HAL_Delay(100);
        }
        else
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_1, 20);
            HAL_Delay(100);
        }
    }

    if(GPIO_Pin == GPIO_PIN_4)
    {
        count_mid++;

        if(count_mid % 2 != 0)
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_2, 5);
            //	    delay_ms(100);
            HAL_Delay(100);
        }
        else
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_2, 20);
            HAL_Delay(100);
        }
    }

    if(GPIO_Pin == GPIO_PIN_5)
    {
        count_right++;

        if(count_right % 2 != 0)
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_3, 5);
            //	    delay_ms(100);
            HAL_Delay(100);
        }
        else
        {
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_3, 20);
            HAL_Delay(100);
        }
    }
}

/**
  *************************************************************************
  *@brief  蓝牙模块串口中断发送函数
  *@author HZH
  *@date 2022/04/26
  *************************************************************************
 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        if(Rxbuf == led_left_on)
        {
            count_left++;
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_1, 20);
            HAL_Delay(100);
        }
        else if(Rxbuf == led_left_off)
        {
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_1, 10);
            HAL_Delay(100);
        }

        if(Rxbuf == led_mid_on)
        {
            count_mid++;
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_2, 20);
            HAL_Delay(100);
        }
        else if(Rxbuf == led_mid_off)
        {
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_2, 10);
            HAL_Delay(100);
        }

        if(Rxbuf == led_right_on)
        {
            count_right++;
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_3, 20);
            HAL_Delay(100);
        }
        else if(Rxbuf == led_right_off)
        {
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
            __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_3, 10);
            HAL_Delay(100);
        }

        HAL_UART_Receive_IT(&huart2, &Rxbuf, 1);
//		HAL_UART_Receive_DMA(&huart2, &Rxbuf, 1);
    }
}


