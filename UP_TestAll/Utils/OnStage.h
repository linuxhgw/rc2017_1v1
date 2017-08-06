//
// Created by admin、 on 2017/8/6.
//

#include <UpLib/STM32Lib/stm32f10x.h>

#ifndef RC2017_1V1_ONSTAGE_H
#define RC2017_1V1_ONSTAGE_H

#endif //RC2017_1V1_ONSTAGE_H


extern u8 OS_arm_servo_list[4];//电机编号
extern u8 OS_hand_motor_list[4];//手臂编号
extern s16 OS_hand_motor_speed[4];//速度

void OS_Init();

void OS_FrontArmUp();

void OS_FrontArmDown();

void OS_BackArmUp();

void OS_BackArmDown();

void OS_PreAction();

void OS_ForAction();

void OnStage();