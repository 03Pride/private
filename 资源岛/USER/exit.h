#ifndef  __EXIT_H_
#define	__EXIT_H_

#ifdef  __EXIT_GLOBALS
    #define __EXIT_EXT
#else
    #define __EXIT_EXT extern
#endif

#include <stdint.h>
#include "usart.h"

__EXIT_EXT int count_left, count_mid, count_right;
__EXIT_EXT uint8_t Rxbuf;
extern uint8_t led_left_on;
extern uint8_t led_left_off;
extern uint8_t led_mid_on;
extern uint8_t led_mid_off;
extern uint8_t led_right_on;
extern uint8_t led_right_off;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
