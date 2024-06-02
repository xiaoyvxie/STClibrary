/**
 * @file 74HC138.h
 * @brief 74HC138多路选择器的驱动头文件
 *
 * 包含了74HC138的初始化函数以及输出控制函数。
 *
 * @defgroup 74HC138 74HC138多路选择器
 * @{
 */

#ifndef __74HC138_H
#define __74HC138_H

#include "general.h"
#include "bit_grinding.h" // 包含处理位操作的函数库


// 74HC138的使能引脚EA的开关定义
#define __74HC138_EA_Pin_Switch __off    // 默认关闭74HC138的EA管脚

//---设置74HC138的地址线端口---*/
#define __74HC138_A0 P10    // A0地址线
#define __74HC138_A1 P11    // A1地址线
#define __74HC138_A2 P12    // A2地址线

// 如果EA管脚开启
#if (__74HC138_EA_Pin_Switch == __on)
#define __74HC138_EA P13   // 74HC138的EA引脚
#endif

// 初始化74HC138
void __74HC138_Init (void);

// 如果EA管脚开启，可以切换74HC138的工作模式
#if (__74HC138_EA_Pin_Switch == __on)
void __74HC138_Switch (__bit Bit_num); // 改变EA引脚的状态
#endif

// 设置74HC138输出引脚
uint8_t __74HC138_Output (uint8_t __74HC138_num); // 控制指定引脚输出低电平

#endif /* __74HC138_H */

