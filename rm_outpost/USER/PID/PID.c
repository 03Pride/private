#define __PID_GLOBALS

#include "pid.h"
#include "bsp_can.h"

/**
  * @brief  init PID param
  * @param  None
  */
void PID_init(PID *pid, float P, float I, float D, float maxout, float maxintegral){
	pid->Kp=P;
	pid->Ki=I;
	pid->Kd=D;
	
//	if(number%2 == 0){
	pid->maxout = maxout;
	pid->maxintegral = maxintegral;
//	}
//	else{
//	pid->maxout = -maxout;
//	pid->maxintegral = -maxintegral;	
//	}
}
	
float PID_speed_realize(PID *pid,float set,float get){
	pid->ActualSpeed = get;
	
	if(number%2 == 0){
		pid->SetSpeed = set;
	}
	else{
		pid->SetSpeed = -set;
	}
	
//	pid->SetSpeed = set;
//	pid->ActualSpeed = get;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	
	pid->out_integral += pid->err ;
	LIMIT(pid->out_integral ,-pid->maxintegral,pid->maxintegral);
		/* ¿¹»ı·Ö±¥ºÍ */
//	if(pid->out > pid->maxout){
//		if(pid->err <= 0){
//			pid->out_integral += pid->err;
//		}
//	}
//	else if(pid->out < -pid->maxout){
//		if(pid->err>=0){
//			pid->out_integral += pid->err;
//		}
//	}
//	else{
//		pid->out_integral += pid->err;
//	}
	pid->out = pid->Kp*pid->err + pid->Ki*pid->out_integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
//	out = speed_pid.out;
	LIMIT(pid->out,-pid->maxout,pid->maxout);
	return pid->out;
}	
	
