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
#include "mcc_generated_files/dac1.h"

#define DDS_CTR_REG 0x0000
#define DDS_CTR_REG_CONFIG 0x07ff
#define DDS_FRQI_LREG 0xc000
#define DDS_FRQI_UREG 0xd000
#define DDS_FN_REG 0x1000

#define POT_OFFSET_ADDRESS 0x003c
#define POT_SCALE_ADDRESS 0x003d
#define POT_SCALE_ORIGIN 115U

I2C1_MESSAGE_STATUS statusI2C;
SPI1_STATUS statusSPI;

uint8_t messageI2C[2];

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

void AnalogOutManager_setOffset(int8_t offset){
    
    messageI2C[0] = 0;
    messageI2C[1] = (uint16_t)(12+offset)*5.33;
    sendToPot(POT_OFFSET_ADDRESS,messageI2C,2);
}

void AnalogOutManager_setScale(uint16_t val){
    
    messageI2C[0] = 0;
    messageI2C[1] = val;
    sendToPot(POT_SCALE_ADDRESS,messageI2C,2);
}

void AnalogOutManager_initialize(void){
    
    statusI2C = I2C1_LOST_STATE;
    uint8_t message1[] = {0U,90U};
    uint8_t message2[] = {0U,81U,0};
    uint8_t rc[] = {0x0c,0,0};
    //uint8_t message[] = {0x00,0x00};
    uint8_t stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    I2C1_TRANSACTION_REQUEST_BLOCK rb = {.address=0x00ff,.length=0};
    I2C1_MasterTRBInsert(1,&rb,&statusI2C);
    stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    sendToPot(0x003d,message1,2);
    AnalogOutManager_setOffset(0);
    sendToDDS(DDS_CTR_REG_CONFIG);
    sendToDDS(DDS_FRQI_UREG|0x0000);
    sendToDDS(DDS_FRQI_LREG|0x00ff);
    while(statusI2C != I2C1_MESSAGE_PENDING);
    DDS_CTRL_SetHigh();
    stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    DDS_CTRL_SetLow();
    stime = TMR1_SoftwareCounterGet();
    while(TMR1_SoftwareCounterGet() - stime < 1);
    DDS_INT_SetHigh();
    DAC_SEL_SetHigh();
    DAC1_OutputSet(512U);
}
void AnalogOutManager_update(void){
    
    statusSPI = SPI1_StatusGet();
}
