//
// Created by admin on 2017/7/26.
//

#include "UpLib/UP_System.h"
#include "common.h"
#include "Utils/Grayscale4Sensor.h"
#include "Utils/ServoMove.h"
#include "Utils/ColorDiscrimination.h"
#include "Utils/OnStage.h"
//#include "Utils/CheckState.h"
//#include "Utils/UserAction01.h"


#ifdef DEBUG_ON
//then the program is in debug mode
#endif


u8 GLOBAL_SENSOR_LIST[8] = {0, 1, 2, 3, 4, 5, 6};
u8 CS_IRSensorList[3];
char  UP_Woody_StartImageRecognition1[5];


const int kG4S_SensorData[4][G4S_SENSOR_DATA_LENGTH] = {{3540, 3500, 3400, 3240},
                                                        {3450, 3420, 3220, 3100},
                                                        {3460, 3400, 3270, 3000},
                                                        {3400, 3320, 3170, 2950}};


void init() {
    G4S_GrayScaleSensorList[0] = GLOBAL_SENSOR_LIST[0];
    G4S_GrayScaleSensorList[1] = GLOBAL_SENSOR_LIST[1];
    G4S_GrayScaleSensorList[2] = GLOBAL_SENSOR_LIST[2];
    G4S_GrayScaleSensorList[3] = GLOBAL_SENSOR_LIST[3];
    CS_IRSensorList[0] = GLOBAL_SENSOR_LIST[4];
    CS_IRSensorList[1] = GLOBAL_SENSOR_LIST[5];
    CS_IRSensorList[2] = GLOBAL_SENSOR_LIST[6];
    SM_Init();
    OS_Init();
    ColorDiscrimination_Init();
    CD_BlueDiscrimination();
    UP_delay_ms(200);

}

int main(void) {

#ifdef DEBUG_ON
    UP_Bluetooth_EnableIT();
#endif

    UP_Timer_EnableIT(0, 5000);//5ms
    UP_Timer_SetHadler(0, G4S_UpdateGrayScaleSensor);
    UP_Woody_Init();
    UP_System_Init();
    UP_delay_ms(100);

    init();



    while (!(UP_ADC_GetIO(CS_IRSensorList[2]) == 0));

    OnStage();


   G4S_enable(ENABLE);


    while (1) {
        if (G4S_next_direction==DIRECTION_NONE) {
            CD_DiscriminationEnemy();
            if (UP_ADC_GetIO(CS_IRSensorList[0]) == 0) {
                if (IsEnemy == 1) {
                    continue;
                } else if(IsEnemy == 0)
                {
                    G4S_enable(DISABLE);
                    SM_Move(DIRECTION_FORWARD, 700);
                    UP_delay_ms(100);
                    G4S_enable(ENABLE);
                }
            } else if (UP_ADC_GetIO(CS_IRSensorList[1]) == 0) {
                SM_Spin(DIRECTION_LEFT,500);
                UP_delay_ms(500);
            } else {
            }

        }
    }
}

