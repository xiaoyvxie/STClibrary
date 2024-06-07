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
extern __code uint8_t LED_TUBE_ARRAY[10];

/**
 * 定义LED管显字母对应的编码。
 * 该枚举类型用于将字母或特殊符号映射到对应的LED管显示码。
 * 每个字母或符号都由其在LED显示器上的图形编码表示。
 */
__code enum LED_TUBE_LETTER {
    LETR_A = 0x77,  /* 字母A的显示码 */
    LETR_B = 0x7C,  /* 字母B的显示码 */
    LETR_C = 0x39,  /* 字母C的显示码 */
    LETR_D = 0x5E,  /* 字母D的显示码 */
    LETR_E = 0x79,  /* 字母E的显示码 */
    LETR_F = 0x71,  /* 字母F的显示码 */
    LETR_BLANK  = 0x00,  /* 空白的显示码，用于表示LED管不亮 */
    LETR_DOT = 0x80  /* 点的显示码，用于表示LED管上的小点 */
};

// LED管初始化函数声明
void LED_tube_Init (void);

// 显示控制函数声明，根据宏定义启用
#define LED_TUBE_SHOW_BIT_function_Switch  __on
#if (LED_TUBE_SHOW_BIT_function_Switch == __on)
void LED_tube_show_bit(uint8_t LED_TUBE_SHOW_NUM);
#endif

#define LED_TUBE_SHOW_SET_BIT_function_Switch  __on
#if (LED_TUBE_SHOW_SET_BIT_function_Switch == __on)
void LED_tube_show_set_bit(uint8_t LED_TUBE_SHOW_NUM, uint8_t n);
#endif

#define LED_TUBE_SHOW_LETTER_function_Switch  __on
#if (LED_TUBE_SHOW_LETTER_function_Switch == __on)
void LED_tube_show_letter(uint8_t LED_TUBE_SHOW_LETTER, uint8_t n);
#endif

#define LED_TUBE_SHOW_SET_function_Switch  __on
#if (LED_TUBE_SHOW_SET_function_Switch == __on)
void LED_tube_show_set(uint16_t LED_TUBE_SHOW_NUM, uint8_t num_bit);
#endif

#endif // __LED_TUBE_H