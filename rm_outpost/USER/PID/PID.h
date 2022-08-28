#ifndef __PID_H
#define __PID_H

#ifdef  __PID_GLOBALS 
#define __PID_EXT  
#else
#define __PID_EXT extern
#endif

#include "bsp_can.h"

#define LIMIT(x,min,max) (x)=(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

/* 前哨站6020 参数整定 */

#define PID_OUTPOST_SPD_P  10.0f
#define PID_OUTPOST_SPD_I  0.9f
#define PID_OUTPOST_SPD_D  55.0f

/* 陀螺仪转速定量为 rad/min */
#define SET_OUTPOST  24//6.5
#define GET_OUTPOST  moto_yaw.speed_rpm
//#define GET_OUTPOST  imu_data.wy

typedef struct _pid{
    float SetSpeed;            //定义设定速度
    float ActualSpeed;        //定义实际值
	float out_voltage;
	float out_integral;
    float err;                //定义偏差值
    float err_last;            //定义最上前的偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数	
	float out;
	float maxout;
	float maxintegral;
}PID;

__PID_EXT PID speed_pid,pout;
__PID_EXT float out;
__PID_EXT uint32_t number;
void PID_init(PID *pid, float P, float I, float D, float maxout, float maxintegral);
float PID_speed_realize(PID *pid,float set,float get);

#endif
