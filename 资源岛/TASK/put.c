#include "put.h"
#include "cmsis_os.h"
#include "choose.h"
#include "tim.h"

osEvent event;
//extern int put,number;
void put_down_Task (void const * argument){
	uint32_t mode_wake_time = osKernelSysTick();
	  for(;;)
	  {
		HAL_TIM_Base_Start_IT((TIM_HandleTypeDef *)&htim1);
		HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_1);
		HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_2);
		HAL_TIM_PWM_Start((TIM_HandleTypeDef *)&htim1, (uint32_t) TIM_CHANNEL_3);		  
		event = osSignalWait(SEND1,osWaitForever);
		  if (event.status == osEventSignal)
		  {
			   if (event.value.signals & SEND1)
			   {
				   if(number == 1){
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,put);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,0);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,0);
				   }
				   else if(number == 2){
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,0);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,put);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,0);
				   }	
				   else if(number == 3){
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,0);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,0);
					__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,put);
				   } 
					else{
						__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_1,0);
						__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_2,0);
						__HAL_TIM_SetCompare (&htim1,TIM_CHANNEL_3,0);
					}	
			   }
		  }
//		osDelay(1);
	  }

}
