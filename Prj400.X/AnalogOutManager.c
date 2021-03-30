/*
 * File:   AnalogOutManager.c
 * Author: Colton
 *
 * Created on March 27, 2021, 1:34 PM
 */


#include "xc.h"
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/tmr1.h"

I2C1_MESSAGE_STATUS status;

void sendToPot(uint16_t potAddress, uint8_t* p_data, uint8_t numOfData){
    
    while(status == I2C1_MESSAGE_PENDING);
    status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(p_data,numOfData,potAddress,&status);
}

void readFromPot(uint16_t potAddress, uint8_t* p_data, uint8_t numOfData)
{
    while(status == I2C1_MESSAGE_PENDING);
    I2C1_MasterRead(p_data,numOfData,potAddress,&status);
}

void AnalogOutManager_initialize(void){
    
    status = I2C1_LOST_STATE;
    uint8_t message[] = {0x00,0x33,0};
    uint8_t rc[] = {0x0c,0,0};
    
    //uint8_t message[] = {0x00,0x00};
    uint8_t stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    I2C1_TRANSACTION_REQUEST_BLOCK rb = {.address=0x00ff,.length=0};
    I2C1_MasterTRBInsert(1,&rb,&status);
    sendToPot(0x003d,message,2);
    while(status != I2C1_MESSAGE_PENDING);
}
void AnalogOutManager_update(void){
    
}
