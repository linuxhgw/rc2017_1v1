//
// Created by admin、 on 2017/8/6.
//


#include "common.h"
#include "../UpLib/UP_System.h"

#include "ServoMove.h"


u8 OS_arm_servo_list[4] = {3, 4, 5, 6};//电机编号
u8 OS_hand_motor_list[4] = {7, 8, 9, 10};//手臂编号
s16 OS_hand_motor_speed[4] = {0, 0, 0, 0};//速度


//初始化
void OS_Init() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UP_CDS_SetMode(OS_arm_servo_list[i], CDS_SEVMODE);
        UP_CDS_SetMode(OS_hand_motor_list[i], CDS_MOTOMODE);
    }
}

//前手臂up
void OS_FrontArmUp() {
    UP_CDS_SetAngle(OS_arm_servo_list[0], 250, 512);
    UP_CDS_SetAngle(OS_arm_servo_list[1], 750, 512);
}

//前手臂down
void OS_FrontArmDown() {
    UP_CDS_SetAngle(OS_arm_servo_list[0], 750, 512);
    UP_CDS_SetAngle(OS_arm_servo_list[1], 250, 512);
}

//后手臂up
void OS_BackArmUp() {
    UP_CDS_SetAngle(OS_arm_servo_list[2], 750, 512);
    UP_CDS_SetAngle(OS_arm_servo_list[3], 250, 512);
}

//后手臂down
void OS_BackArmDown() {
    UP_CDS_SetAngle(OS_arm_servo_list[2], 250, 512);
    UP_CDS_SetAngle(OS_arm_servo_list[3], 750, 512);
}


//动作
void OS_PreAction() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        OS_hand_motor_speed[i] = 0;
    }
    UP_CDS_Set4MotoSpeed(OS_hand_motor_list, OS_hand_motor_speed);
    OS_FrontArmUp();
    OS_BackArmUp();
}


void OS_ForAction(){
    OS_hand_motor_speed[0] =-MOTOR_SPEED;
    OS_hand_motor_speed[1] = MOTOR_SPEED;
    UP_CDS_Set4MotoSpeed(OS_hand_motor_list, OS_hand_motor_speed);//电机速度初始化设置
    OS_FrontArmDown();
    OS_BackArmDown();
}

void OnStage(){
    OS_PreAction();
    SM_ServoMove(650, 650); //上坡，调整方向
    UP_delay_ms(2500);
    SM_ServoMove(500, 500);
    UP_delay_ms(500);
    SM_ServoMove(350,350);
    UP_delay_ms(300);
    SM_ServoMove(0, 0);
    OS_ForAction();

}