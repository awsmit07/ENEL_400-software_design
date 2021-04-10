/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: AnalogInManager.h
 * Author: Andy Smit
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ANALOG_IN_MANAGER_H
#define	ANALOG_IN_MANAGER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define PGA_GAIN_REG 0x2000
#define PGA_CHAN_REG 0x2100
#define DAC_A_REG 0x1000
#define DAC_B_REG 0x9000


void analog_in_initialize(void);


/*
 * Set the gain of the PGA for input channel 1
 * 
 * Parameters: gain: Code for the gain. See table below
 * 000: 1
 * 001: 2
 * 010: 4
 * 011: 5
 * 100: 8
 * 101: 10
 * 110: 16
 * 111: 32
 */
void pga0_set_gain(uint8_t gain);

/*
 * Set the gain of the PGA for input channel 2
 * 
 * Parameters: gain: Code for the gain. See table below
 * 000: 1
 * 001: 2
 * 010: 4
 * 011: 5
 * 100: 8
 * 101: 10
 * 110: 16
 * 111: 32
 */
void pga1_set_gain(uint8_t gain);

/*
 * Set the channel the PGA is receiving input from for input 1
 * 
 * Parameter: chan: The channel. 0 for 1x gain, 1 for 10x gain
 */
void pga0_set_channel(uint8_t chan);

/*
 * Set the channel the PGA is receiving input from for input 2
 * 
 * Parameter: chan: The channel. 0 for 1x gain, 1 for 10x gain
 */
void pga1_set_channel(uint8_t chan);

/* 
 * Set the trigger level for input channel 1.
 * 
 * Parameter: level: The voltage times 1000 the dac should be set to. 
 * Example: level = 1650 produces an output voltage of 1.650V
 */
void trig_set_dac_a(uint16_t level);

/* 
 * Set the trigger level for input channel 2.
 * 
 * Parameter: level: The voltage times 1000 the dac should be set to. 
 * Example: level = 1650 produces an output voltage of 1.650V
 */
void trig_set_dac_b(uint16_t level);

/* 
 * Set the offset level for input channel 1.
 * 
 * Parameter: level: The voltage times 1000 the dac should be set to. 
 * Example: level = 1650 produces an output voltage of 1.650V
 */
void offset_set_dac_a(uint16_t level);

/* 
 * Set the offset level for input channel 2.
 * 
 * Parameter: level: The voltage times 1000 the dac should be set to. 
 * Example: level = 1650 produces an output voltage of 1.650V
 */
void offset_set_dac_b(uint16_t level);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

