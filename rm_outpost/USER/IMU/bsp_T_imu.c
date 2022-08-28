/**
	* @file bsp_T_imu.c
	* @version 1.0
	* @date 2020.1.4
  *
  * @brief  Taurus陀螺仪内测版
  *
  *	@author YY
  *
  */

#include "bsp_T_imu.h"
#include "bsp_can.h"
#include "usart.h"

Taurus_imu_data_t   imu_data; /* 陀螺仪数据 */

void T_imu_calcu(uint32_t can_id,uint8_t * CAN_Rx_data)
{
    switch(can_id)
    {
    case TIMU_PALSTANCE_ID:	//角速度 接收周期 3us
    {
        float 	palstance_buffer[2];
        memcpy(palstance_buffer,CAN_Rx_data,8);
        imu_data.wy = palstance_buffer[0];  //当陀螺仪水平旋转180度时需要加-号
        imu_data.wz = palstance_buffer[1];//单位LSB，/16.3835f/57.3f 之后变成 rad/s
        
    }
    break;
    case TIMU_ANGLE_ID: //角度 接收周期 1ms
    {
        float 	angle_buffer[2];
        memcpy(angle_buffer,CAN_Rx_data,8);
        imu_data.pitch = angle_buffer[0];  //当陀螺仪水平旋转180度时需要加-号
        imu_data.yaw   = angle_buffer[1];
    }
    break;
    }
}
