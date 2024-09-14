#include "bluetooth.h"

bool Bluetooth_CheckData(uint8_t *data){

    uint8_t datasum = 0;   //校验和
    uint8_t data_len = Bluetooth_Rec_DataLen;
    int i;
    if(data[0] == 0xA5 && data[data_len-1] == 0x5A){
        for(i = 1; i < data_len-2; i++){
            datasum += data[i];
        }
        if(datasum == data[data_len-2])	return 1;
    }
    return 0;
}
