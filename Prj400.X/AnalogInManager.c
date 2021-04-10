/*
 * File:   AnalogInManager.c
 * Author: andy
 *
 * Created on April 10, 2021, 1:26 PM
 */


#include "xc.h"
#include "AnalogInManager.h"
#include "spi_manager.h"

void analog_in_initialize(void)
{
    return;
}


void pga0_set_gain(uint8_t gain)
{
    uint16_t data = PGA_GAIN_REG | gain;
    spi_out(data, cs_pga0);
}


void pga1_set_gain(uint8_t gain)
{
    uint16_t data = PGA_GAIN_REG | gain;
    spi_out(data, cs_pga1);
}


void pga0_set_channel(uint8_t chan)
{
    uint16_t data = PGA_CHAN_REG | chan;
    spi_out(data, cs_pga0);
}


void pga1_set_channel(uint8_t chan)
{
    uint16_t data = PGA_CHAN_REG | chan;
    spi_out(data, cs_pga1);
}


void trig_set_dac_a(uint16_t level)
{
    spi_out(DAC_A_REG | level, cs_trig);
}

void trig_set_dac_b(uint16_t level)
{
    spi_out(DAC_B_REG | level, cs_trig);
}


void offset_set_dac_a(uint16_t level)
{
    spi_out(DAC_A_REG | level, cs_offset);
}


void offset_set_dac_b(uint16_t level)
{
    spi_out(DAC_B_REG | level, cs_offset);
}
