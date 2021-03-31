/*
 * File:   AnalogOutManager.c
 * Author: Colton
 *
 * Created on March 27, 2021, 1:34 PM
 */


#include "xc.h"
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"

#define DDS_CTR_REG 0x0000
#define DDS_CTR_REG_CONFIG 0x07df

I2C1_MESSAGE_STATUS statusI2C;
SPI1_STATUS statusSPI;

void sendToPot(uint16_t potAddress, uint8_t* p_data, uint8_t numOfData){
    
    while(statusI2C == I2C1_MESSAGE_PENDING);
    statusI2C = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(p_data,numOfData,potAddress,&statusI2C);
}

void readFromPot(uint16_t potAddress, uint8_t* p_data, uint8_t numOfData)
{
    while(statusI2C == I2C1_MESSAGE_PENDING);
    I2C1_MasterRead(p_data,numOfData,potAddress,&statusI2C);
}

void __attribute__ (( interrupt, no_auto_psv )) _SPI1Interrupt ( void ){
    
    IFS0bits.SPI1IF = 0;
}

void sendToDDS(uint16_t data){
    
    SPI1_Exchange16bit(data);
}

void AnalogOutManager_initialize(void){
    
    statusI2C = I2C1_LOST_STATE;
    uint8_t message1[] = {0x00,0x7f,0};
    uint8_t message2[] = {0x00,0x3f,0};
    uint8_t rc[] = {0x0c,0,0};
    DDS_CTRL_SetHigh();
    //uint8_t message[] = {0x00,0x00};
    uint8_t stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    DDS_CTRL_SetLow();
    I2C1_TRANSACTION_REQUEST_BLOCK rb = {.address=0x00ff,.length=0};
    I2C1_MasterTRBInsert(1,&rb,&statusI2C);
    stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    sendToPot(0x003d,message1,2);
    sendToPot(0x003c,message2,2);
    while(statusI2C != I2C1_MESSAGE_PENDING);
    sendToDDS(DDS_CTR_REG_CONFIG);
}
void AnalogOutManager_update(void){
    
    statusSPI = SPI1_StatusGet();
}
