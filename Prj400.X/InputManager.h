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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/pin_manager.h"

typedef struct {
    uint8_t valA :1;
    uint8_t isCW :1;
    uint8_t valSW :1;
}InputManager_RotVals;

typedef struct {
    InputManager_RotVals s_pastVals;
    InputManager_RotVals s_currVals;
    int16_t turnCount;
}InputManager_Rot;

typedef union{
    struct {
        uint8_t flagROT0 :1;
        uint8_t flagROT0_press :1;
        uint8_t flagROT1 :1;
        uint8_t flagROT1_press :1;
    };
    uint8_t reg;
}CN_Flags;

extern CN_Flags CN_flags;

void InputManager_initialize(void);
void InputManager_updateRots(void);
void InputManager_awkRotFlags(void);
InputManager_Rot* InputManager_getRot0(void);
InputManager_Rot* InputManager_getRot1(void);
void InputManager_clearCounts(void);

#endif	/* XC_HEADER_TEMPLATE_H */

