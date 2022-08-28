/**
 * @file ubf.h
 * @brief 实时更新环形缓冲器
 * @note 使用方法见 .c文件下方
 * 
 * @author ZZJ (WX:z1429881129)
 * @version 1.0 2022-02-25 For the first time to submit
 *          1.1 2022-03-04 Add the function to clear the buffer
 * @date 2022-02-25
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __UPDATE_BUFFER_H__
#define __UPDATE_BUFFER_H__

#include "stdint.h"

/**
 * @brief 缓冲器指针变量类型
 */
typedef struct _ubf_t* ubf_t;

/**
 * @brief 创建缓冲器
 * 
 * @param num 数据单元个数
 * @param size 数据单元占字节数 
 * @return ubf_t 缓存器指针
 */
ubf_t ubf_create(uint32_t num, uint32_t size);

/**
 * @brief 删除缓存器，释放内存
 * 
 * @param ubf 待删除的缓存器指针
 */
void ubf_delete(ubf_t ubf);

/**
 * @brief 投喂数据
 * 
 * @param ubf 缓存器指针
 * @param pdata 数据指针
 * @return uint8_t 
 */
uint8_t ubf_input(ubf_t ubf, const void* pdata);

/**
 * @brief 获取 k 时刻的数据
 * 
 * @param ubf 缓存器指针
 * @param k 时刻索引，k∈[0, num-1]
 * @return void* 返回数据指针
 */
void* ubf_get(ubf_t ubf, uint32_t k);

/**
 * @brief 清空缓存区
 * 
 * @param ubf 缓存器指针
 */
void ubf_clear(ubf_t ubf);
#endif
