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
 */
__code uint8_t LED_TUBE_NUMBER[10] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,
    0x4F/*3*/,0x66/*4*/,0x6D/*5*/,
    0x7D/*6*/,0x07/*7*/,0x7F/*8*/,
    0x6F/*9*/
};


/* 初始化函数组 */

/**
 * @brief 初始化LED管驱动模块
 *
 * 此函数负责配置和启动LED管的硬件驱动层，确保其处于预期的初始状态。
 *
 * @note 本函数执行过程中无需外部输入，亦不返回执行结果。
 */
void LED_tube_Init (void) {
    // 检查`LED_TUBE_YIN_AND_YANG`配置，以确定LED管脚初始逻辑电平
    #if(LED_TUBE_YIN_AND_YANG == 0)
        LED_TUBE_PIN_SET = ~LETR_BLANK; // 置所有LED管脚为高电平（假设高电平为不点亮状态）
    #else
        LED_TUBE_PIN_SET = LETR_BLANK; // 置所有LED管脚为低电平（假设低电平为点亮状态）
    #endif
    // 特定于74HC138驱动芯片的初始化逻辑
    #if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
        __74HC138_Init(); // 调用74HC138的初始化函数
    #endif
}

// =====================================================================================================================

/* 显示函数组 */

#if (LED_TUBE_SHOW_BIT_function_Switch == __on)
/**
 * @brief 数码管显示数字
 * 该函数用于驱动数码管显示一个数字.
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字。这个数字应该在数码管能够显示的范围内。
 */
void LED_tube_show_bit(uint8_t LED_TUBE_SHOW_NUM) {
    #if(LED_TUBE_YIN_AND_YANG == 0)
        // 如果未定义LED_TUBE_YIN_AND_YANG或其值为0，则不反转数字位的输出
        LED_TUBE_PIN_SET = ~LED_TUBE_NUMBER[LED_TUBE_SHOW_NUM];
    #else
        // 如果定义了LED_TUBE_YIN_AND_YANG且其值不为0，则反转数字位的输出
        LED_TUBE_PIN_SET = LED_TUBE_NUMBER[LED_TUBE_SHOW_NUM];
    #endif
}
#endif

// ---------------------------------------------------------------------------------------------------------------------

#if (LED_TUBE_SHOW_SET_BIT_function_Switch == __on)
/**
 * @brief 设置数码管组显示一位数字
 * 
 * 本函数用于在数码管组上显示一个数字的特定位.
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字。
 * @param n 指定要显示的位，决定哪个数码管位显示数字。
 */
void LED_tube_show_set_bit(uint8_t LED_TUBE_SHOW_NUM, uint8_t n) {
    #if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
        // 当使用74HC138驱动芯片且启用了EA引脚开关时，切换74HC138的状态。
        #if (__74HC138_EA_Pin_Switch == __on)
            __74HC138_Switch();
        #endif
        // 设置74HC138的输出位，以驱动对应的数码管位显示。
        __74HC138_Output(n);
    #endif
    // 显示传入数字的指定位。
    LED_tube_show_bit(LED_TUBE_SHOW_NUM);
}
#endif 

// ---------------------------------------------------------------------------------------------------------------------

#if(LED_TUBE_SHOW_LETTER_function_Switch == __on)
/**
 * 控制数码管组管显示字母
 * 
 * 该函数用于根据输入的字母代码，在数码管组管上显示相应的字符。
 * 
 * @param LED_TUBE_SHOW_LETTER 待显示的字母的编码。
 * @param n  指定要显示的位，决定哪个数码管位显示数字。
 */
void LED_tube_show_letter(uint8_t LED_TUBE_SHOW_LETTER, uint8_t n)
{
    // 如果使用74HC138驱动芯片
    #if(LED_TUBY_DRIVER_CHIP == LED_TUBY__74HC138)
        // 如果启用了74HC138的使能引脚切换
        #if(__74HC138_EA_Pin_Switch == __on)
            // 开启或关闭74HC138的使能引脚
            __74HC138_Switch();
        #endif
        // 输出数字代码到74HC138驱动芯片
        __74HC138_Output(n);
    #endif
    // 根据LED_TUBE_YIN_AND_YANG的定义，决定是正常显示还是反转显示LED管的位
    #if(LED_TUBE_YIN_AND_YANG == 0)
        // 如果未定义LED_TUBE_YIN_AND_YANG或其值为0，则不反转数字位的输出
        LED_TUBE_PIN_SET = ~LED_TUBE_SHOW_LETTER;
    #else
        // 如果定义了LED_TUBE_YIN_AND_YANG且其值不为0，则反转数字位的输出
        LED_TUBE_PIN_SET = LED_TUBE_SHOW_LETTER;
    #endif
}

#endif

// ---------------------------------------------------------------------------------------------------------------------

#if (LED_TUBE_SHOW_SET_function_Switch == __on)
/**
 * 设置LED管显示数字。
 * 
 * 此函数运用扫描，通过指定的LED管数组展示一个无符号短整数形式的数字或字符。
 * 它逐位处理输入数字，并利用`STA_LED_TUBE_NUM`静态变量管理显示位置，实现滚动显示效果。
 * `num_bit`参数允许跳过前若干位LED管，以支持在更复杂的显示模式中定位显示起始点。
 * 
 * @param LED_TUBE_SHOW_NUM 要显示的数字，以无符号短整数形式给出，取值范围0至65535。
 * @param num_bit           控制显示起始位置的调整量，无符号字节型，与LED管的循环显示机制配合使用。
 */
void LED_tube_show_set(uint16_t LED_TUBE_SHOW_NUM, uint8_t num_bit) {
    static uint8_t STA_LED_TUBE_NUM; 
    // 分解当前需显示的数字位，并针对`STA_LED_TUBE_NUM`指定的位置设置LED管显示状态。
    LED_tube_show_set_bit(Integer_splitting(LED_TUBE_SHOW_NUM, 7 - STA_LED_TUBE_NUM), STA_LED_TUBE_NUM);
    // 执行去残影操作，确保LED管显示清晰，通过显示空白字符实现。
    LED_tube_show_letter(LETR_BLANK, STA_LED_TUBE_NUM);
    // 更新显示位置计数器，准备处理下一位数字。
    STA_LED_TUBE_NUM++;
    // 当计数器超过LED管的最大有效位置时（即完成一轮显示），依据`num_bit`重置计数器，
    // 实现显示内容的循环往复。
    if (STA_LED_TUBE_NUM > 7) {
        STA_LED_TUBE_NUM = 8 - num_bit;
    }
}
#endif



// 动画


