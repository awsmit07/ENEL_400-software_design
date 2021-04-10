/*
 * File:   spi_manager.c
 * Author: andy
 *
 * Created on April 10, 2021, 10:27 AM
 */


#include "xc.h"
#include "mcc_generated_files/pin_manager.h"
#include "spi_manager.h"
#include "mcc_generated_files/tmr1.h"

void spi_init(void)
{
    // Set all chip selects high
    N_DDS_CS_SetHigh();
    N_PGA0_CS_SetHigh();
    N_PGA1_CS_SetHigh();
    N_OFFSET_CS_SetHigh();
    N_TRIG_CS_SetHigh();

    
    // Set SPI CLK and DAT high
    SPI_DAT_SetHigh();
    SPI_CLK_SetHigh();
}


void spi_out(uint16_t data, uint8_t cs)
{
    // Select the correct device
    switch (cs)
    {
        case 0x0:
            N_DDS_CS_SetLow();
            spi_out_falling(data);
        
        case 0x1:
            N_PGA0_CS_SetLow();
            spi_out_rising(data);
            
        case 0x2:
            N_PGA1_CS_SetLow();
            spi_out_rising(data);
            
        case 0x3:
            N_OFFSET_CS_SetLow();
            spi_out_rising(data);
            
        case 0x4:
            N_TRIG_CS_SetLow();
            spi_out_rising(data);
    }
    
    // Reset CS
    N_DDS_CS_SetHigh();
    N_PGA0_CS_SetHigh();
    N_PGA1_CS_SetHigh();
    N_OFFSET_CS_SetHigh();
    N_TRIG_CS_SetHigh();
}


void spi_out_rising(uint16_t data)
{
    int8_t i=0;
    for(i = 0; i < 16; i++)
    {
        SPI_CLK_SetLow();
        uint16_t data_write = (data << i) & 0x8000;
        if(data_write)
        {
            SPI_DAT_SetHigh();
        }
        else
        {
            SPI_DAT_SetLow();
        }
                
        // Set Clock high writing to registers on Rising edge.
        SPI_CLK_SetHigh();
    }
    SPI_CLK_SetHigh();
}


void spi_out_falling(uint16_t data)
{
    int i;
    for(i = 0; i < 16; i++)
    {
        SPI_CLK_SetHigh();
        uint16_t data_write = (data << i) & 0x8000;
        if(data_write)
        {
            SPI_DAT_SetHigh();
        }
        else
        {
            SPI_DAT_SetLow();
        }
        
        // TODO: Set delay when we have a Time_delayus ability.
        //Time_delayMS(1);
                
        // Set Clock low writing to registers on falling edge.
        SPI_CLK_SetLow();
        
        //Time_delayMS(1);
    }
    SPI_CLK_SetHigh();
}

