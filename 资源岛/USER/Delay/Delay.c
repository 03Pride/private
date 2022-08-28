#include "Delay.h"
#include <stdint.h>
#include "main.h"

/**
  *************************************************************************
  *@brief  ÑÓ³Ùº¯ÊýÎ¢Ãë¼¶
  *@author HZH
  *@date 2022/04/26
  *************************************************************************
 */

void delay1_us(uint32_t time)
{
//  time *= 10;
//	while(time)
//		time--;

    uint32_t startval, tickn, delays, wait;

    startval = SysTick->VAL;
    tickn = HAL_GetTick();
    //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
    delays = time * 72; //sysc / 1000 * udelay;

    if(delays > startval)
    {
        while(HAL_GetTick() == tickn)
        {

        }

        wait = 72000 + startval - delays;

        while(wait < SysTick->VAL)
        {

        }
    }
    else
    {
        wait = startval - delays;

        while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {

        }
    }

}

/**
  *************************************************************************
  *@brief  ÑÓ³Ùº¯ÊýºÁÃë¼¶
  *@author HZH
  *@date 2022/04/26
  *************************************************************************
 */
void delay_ms(uint16_t nms)
{
    uint32_t i;

    for(i = 0; i < nms; i++) delay1_us(1000);

}
