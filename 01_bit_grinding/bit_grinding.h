/**
 * @file bit_grinding.h
 * @brief 位操作工具函数头文件
 *
 * 提供了一系列用于位操作的实用函数，包括设置、清除、切换位，检查位，位移位以及整数拆分等操作.
 *
 * @defgroup BitGrinding 位操作工具
 * @{
 */

#ifndef __BIT_GRINDING_H
#define __BIT_GRINDING_H 

#include "general.h"


#define setBit_function_Switch  __on
#if (setBit_function_Switch  == __on)
void setBit (uint8_t* num, uint8_t n);
#endif

#define clearBit_function_Switch  __on
#if (clearBit_function_Switch  == __on)
void clearBit (uint8_t* num, uint8_t n);
#endif

#define toggleBit_function_Switch  __on
#if (toggleBit_function_Switch  == __on) 
void toggleBit (uint8_t* num, uint8_t n);
#endif

#define checkBit_function_Switch  __on
#if (checkBit_function_Switch  == __on)
uint8_t checkBit (uint8_t* num, uint8_t n);
#endif

#define shift_low_function_Switch  __on
#if (shift_low_function_Switch  == __on)
uint8_t shift_low (uint8_t hex);
#endif

#define shift_high_function_Switch  __on
#if (shift_high_function_Switch  == __on)
uint8_t shift_high (uint8_t hex);
#endif


#define SQUARE_function_Switch  __on
#if (SQUARE_function_Switch  == __on)
uint32_t square (uint16_t num, uint8_t exponent);
#endif

#define INTEGER_SPLITTING_function_Switch  __on
#if (INTEGER_SPLITTING_function_Switch  == __on)
uint8_t Integer_splitting (uint32_t num, uint8_t n);
#endif


#define CHECK_BIT_function_Switch  __on
#if (CHECK_BIT_function_Switch  == __on)
uint8_t check_bit (uint32_t num);
#endif


#endif
