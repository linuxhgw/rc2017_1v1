#include <UpLib/STM32Lib/stm32f10x.h>
#include <UpLib/UP_Globle.h>
#include <UpLib/UP_System.h>
#include <UpLib/UP_Woody_ImageRecognition.h>
#include "string.h"

//
// Created by admin on 2017/8/2.
//
//

u32 sum;
int IsEnemy;
u8 lab;

char up[6] = {0x55, 0xAA, 0x06, 0x02, 0x04, 0x0B};
char UP_Woody_StartImageRecognition1[5] = {0x55, 0xAA, 0x05, 0x30, 0x34};

char green[13] = {0x55, 0xaa, 0x0D, 0x33, 0x00, 0xAF, 0x01, 0x5E, 0xA9, 0x00, 0xFF, 0x00, 0x15};

char blue[13] = {0x55, 0xAA, 0x0D, 0x33, 0x00, 0xFE, 0x00, 0x91, 0xC0, 0x0B, 0xFF, 0x00, 0x98};


void Color_Init(void) {

    for (lab = 0; lab < 6; lab++) {
        UP_USR232_Putc(up[lab]);
    }
    UP_delay_ms(200);
    for (lab = 0; lab < 5; lab++) {
        UP_USR232_Putc(UP_Woody_StartImageRecognition1[lab]);
    }
    UP_delay_ms(400);
    UP_Woody_Clear_ImageRecognize_Data();
    UP_delay_ms(DELAY_TIMES);


}


void Color_GreenDiscrimination(void) {
    for (int i = 0; i < 13; i++) {
        UP_UART5_Putc(green[i]);
    }
    UP_delay_ms(DELAY_TIMES);
}

void Color_BlueDiscrimination(void) {
    for (int i = 0; i < 13; i++) {
        UP_UART5_Putc(blue[i]);
    }
    UP_delay_ms(DELAY_TIMES);
}

void Color_Discrimination(void) {
    sum = UP_Woody_ImagePixel();
    if (sum > 20000) {
        IsEnemy = 1;
    } else {
        IsEnemy = 0;
    }
    UP_delay_ms(50);
}
