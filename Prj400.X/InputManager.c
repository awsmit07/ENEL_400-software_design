/*
 * File:   InputManager.c
 * Author: Colton
 *
 * Created on March 25, 2021, 6:59 PM
 */


#include "InputManager.h"
#include "mcc_generated_files/pin_manager.h"

static void updateRot(InputManager_Rot* r);

static InputManager_Rot s_rot0, s_rot1;

InputManager_Rot* InputManager_getRot0(void){return &s_rot0;};
InputManager_Rot* InputManager_getRot1(void){return &s_rot1;};

CN_Flags CN_flags;

static void CN_handler(void){
    
    //uint8_t a1 = ROT0_A_GetValue(), a2 = s_rot0.s_currVals.valA, b1 = ROT0_SW_GetValue(), b2 = s_rot0.s_currVals.valSW;;
    if((s_rot0.s_currVals.valA != ROT0_A_GetValue()) && ROT0_A_GetValue() == 1)
    {
        s_rot0.s_currVals.isCW = !ROT0_B_GetValue();
        
        CN_flags.flagROT0 = 1;
    }
    else if(s_rot0.s_currVals.valSW == ROT0_SW_GetValue())
    {
        s_rot0.s_currVals.valSW = !ROT0_SW_GetValue();
        
        CN_flags.flagROT0_press = 1;
    }
    else if((s_rot1.s_currVals.valA != ROT1_A_GetValue() && ROT1_A_GetValue() == 1))
    {
        s_rot1.s_currVals.isCW = !ROT1_B_GetValue();
        
        CN_flags.flagROT1 = 1;
    }
    else if(s_rot1.s_currVals.valSW == ROT1_SW_GetValue())
    {
        s_rot1.s_currVals.valSW = !ROT1_SW_GetValue();
        
        CN_flags.flagROT1_press = 1;
    }
    s_rot0.s_currVals.valA = ROT0_A_GetValue();
    s_rot1.s_currVals.valA = ROT1_A_GetValue();
}

void InputManager_initialize(){
    
    CN_SetInterruptHandler(&CN_handler);
    
    s_rot0.s_currVals.valA = ROT0_A_GetValue();
    s_rot0.s_currVals.valSW = !ROT0_SW_GetValue();
    s_rot1.s_currVals.valA = ROT1_A_GetValue();
    s_rot1.s_currVals.valSW = !ROT1_SW_GetValue();
    
    InputManager_updateRots();
}

void InputManager_updateRots(void){
    if(CN_flags.flagROT0)
    {
        updateRot(&s_rot0);
    }
    if(CN_flags.flagROT1)
    {
        updateRot(&s_rot1);
    }
}

void InputManager_awkRotFlags(void){
    CN_flags.flagROT0 = 0;
    CN_flags.flagROT0_press = 0;
    CN_flags.flagROT1 = 0;
    CN_flags.flagROT1_press = 0;
}

void InputManager_clearCounts(void){
    
    s_rot0.turnCount = 0;
    s_rot1.turnCount = 0;
}

static void updateRot(InputManager_Rot* r){
    
//    if(r->s_currVals.isCW != r->s_pastVals.isCW)
//    {
//        r->s_pastVals.isCW = r->s_currVals.isCW;
//    }
    if(r->s_currVals.isCW)
    {
        r->turnCount++;
    }
    else
    {
        r->turnCount--;
    }
    r->s_pastVals = r->s_currVals;
}