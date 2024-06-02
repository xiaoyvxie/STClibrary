/**
 * @file LED_Tube.h
 * 文件头定义了LED管显示控制的配置与函数声明。
 *
 * 本文件主要涉及LED管的驱动模式选择（阴极/阳极）、
 * 选用的驱动芯片（如74HC138）以及引脚配置，并根据配置条件编译
 * 相关驱动代码。同时，定义了初始化函数和显示控制的条件编译函数声明。
 */

#ifndef __LED_TUBE_H
#define __LED_TUBE_H

#include "general.h" // 包含基础通用定义

// LED驱动模式定义
#define LED_TUBE_YIN 0 // 阴极驱动模式
#define LED_TUBE_YANG 1 // 阳极驱动模式

// 选择驱动芯片类型
#define LED_TUBY__74HC138 0 // 使用74HC138作为驱动芯片

// 设置默认为阳极驱动
#define LED_TUBE_YIN_AND_YANG LED_TUBE_YANG

// 选定驱动芯片
#define LED_TUBY_DRIVER_CHIP LED_TUBY__74HC138

// LED管引脚配置
#define LED_TUBE_PIN_SET P0

// 条件编译以包含特定芯片的驱动头文件
#if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
#include "__74H138.h" // 针对74HC138的驱动头文件
#endif

// 外部声明的LED管显示数组
extern __code uint8_t LED_TUBE_ARRAY[18];

// LED管初始化函数声明
void LED_tube_Init (void);

// 显示控制函数声明，根据宏定义启用
#define LED_TUBE_SHOW_BIT_function_Switch  __on
#if (LED_TUBE_SHOW_BIT_function_Switch == __on)
void LED_tube_show_bit (uint8_t LED_TUBE_SHOW_NUM);
#endif

#define LED_TUBE_SHOW_SET_BIT_function_Switch  __on
#if (LED_TUBE_SHOW_SET_BIT_function_Switch == __on)
void LED_tube_show_set_bit (uint8_t LED_TUBE_SHOW_NUM, uint8_t n);
#endif

#define LED_TUBE_SHOW_SET_function_Switch  __on
#if (LED_TUBE_SHOW_SET_function_Switch == __on)
void LED_tube_show_set (uint32_t LED_TUBE_SHOW_NUM, uint8_t n_1);
#endif

#endif // __LED_TUBE_H