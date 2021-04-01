/*
 * File:   LCD_Manager.c
 * Author: andy
 *
 * Created on March 31, 2021, 8:19 AM
 */


#include "xc.h"
#include "LCD_Manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"

void lcd_init()
{
    ANSELE = 0x0000;
    TRISE = 0x0000;
    LATE = 0x0000;
    
    LCD_RS_SetLow();
    Time_delayMS(45); //Wait >40msec after power is applied
    lcd_send_cmd(0x30); //command 0x30 = Wake up 
    Time_delayMS(5); //must wait 5ms, busy flag not available
    lcd_send_cmd(0x30); //command 0x30 = Wake up #2
    Time_delayMS(1); //must wait 160us, busy flag not available
    lcd_send_cmd(0x30); //command 0x30 = Wake up #3
    Time_delayMS(1); //must wait 160us, busy flag not available
    lcd_send_cmd(0x38); //Function set: 8-bit/2-line
    lcd_send_cmd(0x10); //Set cursor
    lcd_send_cmd(0x0c); //Display ON; Cursor ON
    lcd_send_cmd(0x06); //Entry mode set
}

void lcd_send_cmd(uint8_t cmd) 
{
    PORTE = cmd; //put data on output Port
    LCD_RS_SetLow(); //D/I=LOW : send instruction
    LCD_RW_SetLow(); //R/W=LOW: Write
    LCD_EN_SetHigh();
    Time_delayMS(1); //enable pulse width>= 300ns
    LCD_EN_SetLow(); //Clock enable: falling edge
}

void lcd_write_char(char write)
{
    PORTE = write;//put data on output Port
    LCD_RS_SetHigh();//D/I=HIGH: send data
    LCD_RW_SetLow();//R/W=LOW : Write
    LCD_EN_SetHigh();
    Time_delayMS(1);//enable pulse width>= 300ns
    LCD_EN_SetLow();//Clock enable: falling edge
}

void lcd_write_str(char * str)
{
    char * c = str; 
    for(*c; c++;)
    {
        lcd_write_char(*c);
    }
}
