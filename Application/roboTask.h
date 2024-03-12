/**
 * @file roboTask.h
 * @author Bi Kaixiang (wexhicy@gmail.com)
 * @brief 机器人RTOS任务
 * @version 0.1
 * @date 2024-01-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "ins_task.h"

osThreadId insTaskHandle;

void StartINSTASK(void const *argument);

/**
 * @brief 初始化机器人RTOS任务，所有外加的RTOS任务都在这里初始化
 *
 */
void OSTaskInit(void)
{
    osThreadDef(instask, StartINSTASK, osPriorityRealtime, 0, 1024);
    insTaskHandle = osThreadCreate(osThread(instask), NULL); // 由于是阻塞读取传感器,为姿态解算设置较高优先级,确保以1khz的频率执行
}

__attribute__((noreturn)) void StartINSTASK(void const *argument)
{
    INS_Init();                                  // 确保BMI088被正确初始化.
    for (;;) {
        // 1kHz
        INS_Task();
        osDelay(1);
    }
}
