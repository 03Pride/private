/**
 * @file    us_tim.h
 * @author  ZZJ (WX:z1429881129)
 * @brief   微秒级计时/延时模块
 * @note    模块使用的定时器，需要通过设置预分频系数，
 *          使得其每1us改变一次
 * @version 1.0
 * @atten   目前模块对于溢出，时间计算中涉及的 ±1 的问题还未有严格的测试！
 * @date    2022-02-27
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef __US_CNT_H__
#define __US_CNT_H__

#include "stdint.h"
#include "stm32f4xx_hal.h"

/**
 * @brief 模块参数设置
 */
#define UST_PRECISION 1         //定时器精度，单位：us
#define UST_HTIM htim5          //使用的定时器句柄
#define UST_UST_TIM_CNT_SIZE 32 //定时器ARR寄存器位数,可通过查芯片手册时钟树获得

/**
 * @brief 在定时器溢出中断回调函数中加入下段代码，
 *          修改其中的定时器实例
 *          并在文件中包含此头文件
 */
/*
    if (htim->Instance == TIM5)
    {
        prv_ust.overflow_cnt++;
    }
*/

#if (UST_UST_TIM_CNT_SIZE == 32)
    #define UST_PERIOD 0xFFFFFFFF   //定时器溢出周期数值
    #define UST_TYPE uint32_t
#elif (UST_UST_TIM_CNT_SIZE == 16)
    #define UST_PERIOD 0xFFFF   //定时器溢出周期数值
    #define UST_TYPE uint16_t
#endif

/**
 * @brief 用户使用模块数据结构体类型
 */
typedef struct
{
    UST_TYPE last_tim;
    UST_TYPE last_cnt;
    
    UST_TYPE now_tim;
    UST_TYPE now_cnt;
    
    float dt; //单位：ms
    uint8_t interval_start_flag; //区间测时启动标志
}ust_t;

/**
 * @brief 模块内部变量类型
 */
typedef struct
{
    __IO UST_TYPE overflow_cnt; //当前定时器溢出次数
    __IO UST_TYPE predict_overflow_cnt; //预测延时结束时定时器溢出次数
    __IO UST_TYPE predict_tim; //预测延时结束时定时器的计数值
}prv_ust_t;

/**
 * @brief 模块内部变量外部声明
 */
extern prv_ust_t prv_ust;

/**
 * @brief 模块内部使用的定时器句柄外部声明
 */
extern TIM_HandleTypeDef UST_HTIM;

/**
 * @brief 启动定时器及其溢出中断
 */
void ust_tim_start(void);

/**
 * @brief 关闭定时器及其溢出中断
 */
void ust_tim_end(void);

/**
 * @brief 代码点执行周期测试
 * @note  在需要测试的代码处单独使用
 * @param ust 
 */
void ust_period_test(ust_t* ust);

/**
 * @brief 代码段执行区间计时开始
 *
 * @param ust 
 */
void ust_interval_test_start(ust_t* ust);

/**
 * @brief 码段执行区间计时结束
 * @note  若使用前未开始区间计时，则计得时间dt为-1
 * @param ust 
 */
void ust_interval_test_end(ust_t* ust);

/**
 * @brief us级延时函数
 * @param us 延时时间（us）
 */
void ust_delay(UST_TYPE us);

#endif
