#include "LED_tube.h"

/**
 * 定义一个LED管显示字符的数组。
 * 数组中的每个元素代表一个14段LED管（7段加一个小数点）显示的字符编码。
 * 数组索引与字符对应如下：
 * 0 - '0' (0x3F)
 * 1 - '1' (0x06)
 * 2 - '2' (0x5B)
 * ...
 * 9 - '9' (0x6F)
 * 10 - 'A' (0x77)
 * ...
 * 15 - 'F' (0x71)
 * 16 - 空格 ' ' (0x00)
 * 17 - 小数点 '.' (0x80)
 */
__code uint8_t LED_TUBE_ARRAY[18] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,
    0x4F/*3*/,0x66/*4*/,0x6D/*5*/,
    0x7D/*6*/,0x07/*7*/,0x7F/*8*/,
    0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,
    0x71/*F*/,0x00/* */,0x80/*.*/
};





//初始化
/**
 * @brief 初始化LED管驱动模块
 *
 * 此函数负责配置和启动LED管的硬件驱动层，确保其处于预期的初始状态。
 * 根据宏定义`LED_TUBE_YIN_AND_YANG`的设定，决定所有LED管脚的初始电平。
 * 另外，若选用74HC138作为LED驱动芯片（通过`LED_TUBY_DRIVER_CHIP`宏定义识别），则会自动调用该芯片的初始化函数。
 *
 * @note 本函数执行过程中无需外部输入，亦不返回执行结果。
 */
void LED_tube_Init (void) {
    // 检查`LED_TUBE_YIN_AND_YANG`配置，以确定LED管脚初始逻辑电平
    #if(LED_TUBE_YIN_AND_YANG == 0)
        LED_TUBE_PIN_SET = ~0x00; // 置所有LED管脚为高电平（假设高电平为不点亮状态）
    #else
        LED_TUBE_PIN_SET = 0x00; // 置所有LED管脚为低电平（假设低电平为点亮状态）
    #endif
    
    // 特定于74HC138驱动芯片的初始化逻辑
    #if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
        __74HC138_Init (); // 调用74HC138的初始化函数
    #endif
}


//显示函数
#if (LED_TUBE_SHOW_BIT_function_Switch == __on)
/**
 * @brief 数码管显示数字
 * 该函数用于驱动数码管显示一个数字。根据配置，它会将对应的数字位反转或不反转输出到数码管的位线上。
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字。这个数字应该在数码管能够显示的范围内。
 */
void LED_tube_show_bit (uint8_t LED_TUBE_SHOW_NUM) {
    #if(LED_TUBE_YIN_AND_YANG == 0)
    // 如果未定义LED_TUBE_YIN_AND_YANG或其值为0，则不反转数字位的输出
    LED_TUBE_PIN_SET = ~LED_TUBE_ARRAY[LED_TUBE_SHOW_NUM];
    #else
    // 如果定义了LED_TUBE_YIN_AND_YANG且其值不为0，则反转数字位的输出
    LED_TUBE_PIN_SET = LED_TUBE_ARRAY[LED_TUBE_SHOW_NUM];
    #endif
}
#endif


#if (LED_TUBE_SHOW_SET_BIT_function_Switch == __on)
/**
 * @brief 数码管组一位显示
 * 
 * 本函数用于驱动数码管显示一个数字的某一位。函数依赖于特定的驱动芯片和配置，
 * 仅当配置为使用74HC138驱动芯片且启用了74HC138的使能引脚开关时才有效。
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字。这个数字应该在数码管能够显示的范围内。
 * @param n 要显示的位数。指定位数的具体显示内容。
 */
void LED_tube_show_set_bit (uint8_t LED_TUBE_SHOW_NUM, uint8_t n) {
    
    #if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
    // 当使用74HC138驱动芯片且启用了EA引脚开关时，切换74HC138的状态。
    #if (__74HC138_EA_Pin_Switch == __on)
    __74HC138_Switch ();
    #endif
    // 设置74HC138的输出位，以驱动对应的数码管位显示。
    __74HC138_Output (n);
    // 显示传入数字的指定位。
    LED_tube_show_bit (LED_TUBE_SHOW_NUM);
    #endif
}
#endif 


#if (LED_TUBE_SHOW_SET_function_Switch == __on)
/**
 * 设置LED管显示数字。
 * 
 * 该函数用于通过一系列LED管显示一个给定的数字或字符。具体实现是将输入的数字
 * 拆分，并逐位地设置LED管的显示状态，n_1参数主要是表达显示到第几位LED管。
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字或字符，采用无符号长整型表示。
 * @param n_1               一个调整参数，用于在显示循环中跳过前面的几位LED管。
 *                          当n达到8时，会利用该参数重新调整n的值。
 * 
 * @note 该函数不返回任何值。
 */
void LED_tube_show_set (uint32_t LED_TUBE_SHOW_NUM, uint8_t n_1) {
    static uint8_t n; 
    // 将输入数字按位拆分，并设置LED管的显示状态。
    LED_tube_show_set_bit (Integer_splitting(LED_TUBE_SHOW_NUM, 7-n), n);
    // 固定设置第16位，这可能与系统的LED管布局有关。
    LED_tube_show_set_bit (16, n);
    n++; // 准备处理下一位数字。
    // 如果n达到8，为了循环显示，会根据n_1的值重新调整n的取值。
    if (n == 8) {
        n = 8 - n_1;
    }
}
#endif

