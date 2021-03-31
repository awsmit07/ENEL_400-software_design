/*
 * File:   LCD_Manager.c
 * Author: andy
 *
 * Created on March 31, 2021, 8:19 AM
 */


#include "xc.h"
#include "LCD_Manager.h"
#include "mcc_generated_files/tmr1.h"

void lcd_init()
{
    _RG8 = 0;
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
    _RG6 = 0; //D/I=LOW : send instruction
    _RG7 = 0; //R/W=LOW: Write
    _RG8 = 1; 
//    __delay_us(1);//enable pulse width>= 300ns
    _RG8 = 0; //Clock enable: falling edge
}

void lcd_write_char(char write)
{
    PORTE = write;//put data on output Port
    _RG6 = 1;//D/I=HIGH: send data
    _RG7 = 0;//R/W=LOW : Write
    _RG8 = 1;
//    __delay_us(1);//enable pulse width>= 300ns
    _RG8 = 0;//Clock enable: falling edge
}

void lcd_write_str(char * str)
{
    char * c = str; 
    for(*c; c++;)
    {
        lcd_write_char(*str);
    }
}
