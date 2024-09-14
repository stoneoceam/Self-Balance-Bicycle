#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <cstdint>

typedef struct{
    int Angle;
    int Speed;
    float Voltage;
    //.....
}bluetooth_rec_data;


typedef struct{

    uint8_t Dir_On;
    uint8_t Dir_Down;
    uint8_t Dir_Left;
    uint8_t Dir_Right;
    int Angle;
    int Speed;
    //....
}bluetooth_send_data;

#define Bluetooth_Rec_DataLen	15
#define Bluetooth_Send_DataLen	15

bool Bluetooth_CheckData(uint8_t *data);



#endif // BLUETOOTH_H
