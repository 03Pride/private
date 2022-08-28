/**
	* @file bsp_T_imu.c
	* @version 1.0
	* @date 2020.1.4
  *
  * @brief  Taurus�������ڲ��
  *
  *	@author YY
  *
  */

#include "bsp_T_imu.h"
#include "bsp_can.h"
#include "usart.h"

Taurus_imu_data_t   imu_data; /* ���������� */

void T_imu_calcu(uint32_t can_id,uint8_t * CAN_Rx_data)
{
    switch(can_id)
    {
    case TIMU_PALSTANCE_ID:	//���ٶ� �������� 3us
    {
        float 	palstance_buffer[2];
        memcpy(palstance_buffer,CAN_Rx_data,8);
        imu_data.wy = palstance_buffer[0];  //��������ˮƽ��ת180��ʱ��Ҫ��-��
        imu_data.wz = palstance_buffer[1];//��λLSB��/16.3835f/57.3f ֮���� rad/s
        
    }
    break;
    case TIMU_ANGLE_ID: //�Ƕ� �������� 1ms
    {
        float 	angle_buffer[2];
        memcpy(angle_buffer,CAN_Rx_data,8);
        imu_data.pitch = angle_buffer[0];  //��������ˮƽ��ת180��ʱ��Ҫ��-��
        imu_data.yaw   = angle_buffer[1];
    }
    break;
    }
}
