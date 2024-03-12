#include "bsp_init.h"
#include "roboTask.h"

/**
 * @brief 机器人初始化
 *
 */
void RobotInit(void)
{
    // 关闭中断,防止在初始化过程中发生中断
    // 请不要在初始化过程中使用中断和延时函数！
    // 若必须,则只允许使用DWT_Delay()
    __disable_irq();
    // BSP初始化
    BSPInit();

    // rtos创建任务
    OSTaskInit();

    __enable_irq();
}