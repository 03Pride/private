#include "choose.h"
#include "cmsis_os.h"
#include "put.h"
#include <stdlib.h>
//#include <time.h>

int circle=0,put=20;
int number;
extern osThreadId put_downHandle;
void choose_Task (void const * argument){
	uint32_t mode_wake_time = osKernelSysTick();
	  for(;;)
	  {
		circle++;
		if(circle>=3000){
//			srand((unsigned)time(NULL));
			number=rand()%3+1;
			put=0;
			circle=0;
		}
		osSignalSet(put_downHandle, SEND1);
		osDelayUntil(&mode_wake_time,1);
//		osDelay(1);
	  }
}
