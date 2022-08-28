/*******************************************************************************
 * @file    DataScope_DP.c
 * @author  ZZJ
 * @date    2022.1.31
 * @brief   MiniBalance �� VOFA+ ������λ����������
 *          ʹ�÷�����
 *              0. Ĭ��ʹ��F4ϵ�У�������Ҫ�޸�.h�ļ��а�����ͷ�ļ�
 *              1. �� DataScope_DP.h ѡ��ʹ�õ���λ����������Ҫ�޸�ʾ����ͨ����
 *                 ���У���ʹ�� MiniBalance�������ͨ����Ĭ��10
 *              2. �ڡ�Private includes������ �����ⲿ��������ͷ�ļ�
 *              3. �ڡ�Private variables�����������ⲿ����
 *              4. �ڡ�Private user code������ע���û�����,�磺
 *                  DataScope_Get_Channel_Data(JY901_data.Gyro_a_x);
 *                  DataScope_Get_Channel_Data(JY901_data.Gyro_a_y);
 *                  DataScope_Get_Channel_Data(JY901_data.Gyro_a_z);
 *              5. ����ִ�� DataWave(UART_HandleTypeDef* huart)
 *                 ��������һ���Խ�ע�����ݵ�ǰֵ˳�򷢳�
 *                  
 * @attention   ֻ���޸�.h�ļ��еĺ궨��ʹ��ļ��� BEGIN �� END ֮��Ĵ���
 *              ע�����˳�������λ���е�ͨ��˳��
 * @note
 *          ��ʹ�� MiniBalance ��λ��������Ҫ���з�Ƶ���ͣ����⿨��
 *          ��ʹ�� VOFA+ ��λ������λ������Ҫʹ�� Justfloat Э��
 *******************************************************************************
 */
#include "DataScope_DP.h"
#include "PID.h"
/* ����ʾ����ͨ���� */
#ifndef MINIBALANCE
    #define DATASCOPE_MAX_SEND_NUM MAX_SEND_NUM //ʹ���û���������ͨ����
#else
    #define DATASCOPE_MAX_SEND_NUM 10 //Ĭ��10��ͨ��
#endif

/* �������ֵ���� */
#ifndef ABS
    #define ABS(x)		((x>0)? (x): (-(x)))
#endif

/* ʾ�������ݽṹ�� */
struct _DataTypedfef_t
{
    unsigned char OutPut_Buffer[4*DATASCOPE_MAX_SEND_NUM+4];//���ڷ��ͻ�����
    unsigned char Send_Count;//������Ҫ���͵����ݸ���
    unsigned char Data_Num;//��������
} CK;

//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

//����˵������������ͨ���ĵ����ȸ�������д�뷢�ͻ�����
//Data��ͨ������
void DataScope_Get_Channel_Data(float Data)
{
    CK.Data_Num++;
    if (CK.Data_Num > DATASCOPE_MAX_SEND_NUM)
        return;  //ͨ�������������ͨ��������ִ�к���
    else
    {
    #ifdef MINIBALANCE
        Float2Byte(&Data,CK.OutPut_Buffer,( (CK.Data_Num-1) * 4 +1 ) );  //����֡ͷ
    #else  //VOFA
        Float2Byte(&Data,CK.OutPut_Buffer,( (CK.Data_Num-1) * 4) );
    #endif
    }
}

//����˵������������ȷʶ���֡��ʽ
//Channel_Number����Ҫ���͵�ͨ������
//���ط��ͻ��������ݸ���
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
    if ( (Channel_Number > DATASCOPE_MAX_SEND_NUM) || (Channel_Number == 0) )
    {
        return 0;    //ͨ����������10�����0��ֱ����������ִ�к���
    }
    else
    {
    #ifdef MINIBALANCE
        CK.OutPut_Buffer[0] = '$';  //֡ͷ
        uint8_t temp_cnt = Channel_Number*4+1;
        CK.OutPut_Buffer[temp_cnt]  =  temp_cnt;  //֡β
        return (temp_cnt+1);  //����һ�����ݰ����ֽ���
    #else  //VOFA+
        uint8_t temp_cnt = Channel_Number*4+4;
        CK.OutPut_Buffer[4*Channel_Number + 0] = 0x00;
        CK.OutPut_Buffer[4*Channel_Number + 1] = 0x00;
        CK.OutPut_Buffer[4*Channel_Number + 2] = 0x80;
        CK.OutPut_Buffer[4*Channel_Number + 3] = 0x7f;
        return temp_cnt;  //����һ�����ݰ����ֽ���
    #endif
    }
}

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h"
#include "bsp_can.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */


//����˵������λ��ͨ�����ڴ�ӡ���ݲ���
//����˵�������ڵ��ô˺���
void DataWave(UART_HandleTypeDef* huart)
{
/* Private user code ---------------------------------------------------------*/
    /* USER CODE BEGIN 0 */
//   DataScope_Get_Channel_Data(moto_yaw.speed_rpm );
	 DataScope_Get_Channel_Data(moto_chassis[1].speed_rpm );
	 DataScope_Get_Channel_Data(speed_pid.SetSpeed );
    /* USER CODE END */

    CK.Send_Count = DataScope_Data_Generate(CK.Data_Num);
    for( uint8_t cnt = 0; cnt < CK.Send_Count; cnt++)
    {
        while((huart->Instance->SR&0X40)==0);
        huart->Instance->DR = CK.OutPut_Buffer[cnt];
    }
    CK.Data_Num=0;
    CK.Send_Count = 0;
}