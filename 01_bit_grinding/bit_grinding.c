#include "bit_grinding.h"


#if (setBit_function_Switch  == __on)
/**
 * @brief 设置指定位置的位为1
 *
 * 将给定的8位无符号整数 num 的第 n 位设置为1.
 *
 * @param num 8位无符号整数指针，指向要修改的值
 * @param n 位位置（从0开始计数，有效范围0-7）
 */
void setBit (uint8_t* num, uint8_t n) {
    *num |= (1 << n);
}
#endif


#if (clearBit_function_Switch  == __on)
/**
 * @brief 清除指定位置的位
 *
 * 该函数通过按位与操作清除给定8位整数num的第n位，将其设置为0。
 *
 * @param num 无符号8位整数的指针。
 * @param n 要清除的位的位置，范围必须是0到7。
 *          （确保n在有效范围内以避免意外行为）
 */
void clearBit (uint8_t* num, uint8_t n) {
    *num &= ~(1 << n); // 清除第n位
}
#endif


#if (toggleBit_function_Switch  == __on)
/**
 * @brief 切换二进制位的状态
 *
 * 该函数通过按位异或操作切换给定8位整数num的第n位。
 *
 * @param num 无符号8位整数的指针。
 * @param n 要切换的位的位置，范围必须是0到7。
 *          （确保n在有效范围内以避免意外行为）
 */
void toggleBit (uint8_t* num, uint8_t n) {
    *num ^= (1 << n); // 使用按位异或操作，切换第n位的状态
}
#endif


#if (checkBit_function_Switch  == __on)
/**
 * @brief 检查指定位置的位是否为1
 *
 * 使用按位与操作，检查给定8位整数num的第n位是否为1。
 *
 * @param num 无符号8位整数的指针。
 * @param n 要检查的位的位置，范围必须是0到7。
 *          （确保n在有效范围内以避免意外行为）
 *
 * @return 如果第n位为1，返回非零值（通常为1）；否则返回0。
 */
uint8_t checkBit (uint8_t* num, uint8_t n) {
    return (*num & (1 << n)) != 0; // 使用按位与操作，检查第n位是否为1
}
#endif


#if (shift_low_function_Switch  == __on)
/**
 * @brief 将十六进制数的低四位移动到高四位
 *
 * 将给定的8位十六进制数的低四位通过左移操作移动到高四位。
 *
 * @param hex 一个无符号8位整数，代表十六进制数
 *
 * @return 移位后的新8位整数，其中原来的低四位移动到了高四位
 */
uint8_t shift_low (uint8_t hex) {
    return (hex << 4);
}
#endif

#if (shift_high_function_Switch  == __on)
/**
 * @brief 将无符号8位整数的高四位移至低四位
 *
 * 将给定的无符号8位整数（常用于表示十六进制值）的高四位移动到低四位的位置，
 * 并确保结果只包含0-15的值，对应十六进制的低四位。
 *
 * @param hex 一个无符号8位整数
 *
 * @return 移动后的低四位值，范围在0到15之间
 */
uint8_t shift_high (uint8_t hex) {
    // 右移操作将高四位移动到低四位的位置，并使用位与操作确保结果为0-15之间的值
    return (hex >> 4) & 0x0f;
}
#endif


#if (SQUARE_function_Switch  == __on)
/**
 * 计算给定数字的乘方。
 *
 * @param num 底数，类型为 uint32_t。
 * @param exponent 指数，非负整数，类型为 uint8_t。
 * @return 计算结果，如果底数为0且指数为正，则返回0；如果指数为0，则返回1。
 */
uint32_t square (uint16_t num, uint8_t exponent) {
    if (num == 0 && exponent > 0) {
        return 0;
    }
    if (exponent == 0) {
        return 1;
    }

    uint32_t result = 1;
    for (uint8_t i = 0; i < exponent; ++i) {
        result *= num;
        // 检查结果是否溢出，虽然在此场景下不太可能达到千万级别后才溢出
        // 但根据实际需求，你可能需要添加适当的溢出检查逻辑
    }
    return result;
}
#endif


#if (INTEGER_SPLITTING_function_Switch  == __on)
/**
 * 将一个大整数拆分为数字数组中的一个元素
 *
 * 该函数将一个大整数（num）拆分成为由各个十进制数字组成的一维数组中的某一位数字。
 * 具体而言，它计算 num 除以 10 的 n 次方再取余 10 所得的值，并将这个值返回。
 *
 * @param num 需要拆分的大整数。
 * @param n 指定将拆分得到的数字的位置（从0开始计数）。
 * @return 返回 num 在其十进制表示中第 n+1 位的数字。
 */
uint8_t Integer_splitting (uint32_t num, uint8_t n) {
    // 确保n在有效范围内，避免除以0
    if (n > 9) {
        return 0; // 或者根据实际情况处理错误情况，比如返回-1表示错误
    }

    // 计算10的n次方
    uint32_t power_of_ten = square(10, n);

    // 计算并返回结果
    return (num / power_of_ten) % 10;
}
#endif


#if (CHECK_BIT_function_Switch  == __on)
/**
 * 检查一个长整型数的位数。
 * @param num 需要检查位数的长整型数。
 * @return 返回数num的位数。
 */
uint8_t check_bit (uint32_t num) {
    uint8_t n = 0; // 初始化计数器n为0
    while (num !=0) { // 当num不为0时，继续循环
        n ++; // 每次循环，计数器n自增1
        num /= 10; // 将num除以10，以便逐位检查
    }
    return n; // 返回计数器n的值，即num的位数
}
#endif