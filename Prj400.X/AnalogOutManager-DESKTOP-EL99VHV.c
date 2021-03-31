/*
 * File:   AnalogOutManager.c
 * Author: Colton
 *
 * Created on March 27, 2021, 1:34 PM
 */


#include "xc.h"
#include "mcc_generated_files/i2c1.h"

I2C1_MESSAGE_STATUS status;

void sendToPot(uint16_t potAddress, uint8_t* p_data, uint8_t numOfData){
    
    while(status == I2C1_MESSAGE_PENDING);
    status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(p_data,numOfData,potAddress,&status);
}

void AnalogOutManager_initialize(void){
    
    status = I2C1_LOST_STATE;
    uint8_t message1[] = {0x00,0x33};
    sendToPot(0x5c,message1,2);
    while(status != I2C1_MESSAGE_COMPLETE);
}
void AnalogOutManager_update(void){
    
}
