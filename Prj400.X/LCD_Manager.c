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
    // Set port E as digital output
    ANSELE = 0x0000;
    TRISE = 0x0000;
    LATE = 0x0000;
    
    // Wake up LCD
    Time_delayMS(45); //Wait >40msec after power is applied
    PORTE = 0x30; //command 0x30 = Wake up 
    LCD_RS_SetLow(); //D/I=LOW : send instruction
    LCD_RW_SetLow(); //R/W=LOW: Write
    LCD_EN_SetHigh();
    LCD_EN_SetLow();
    Time_delayMS(5); //must wait 5ms, busy flag not available
    PORTE = 0x30; //command 0x30 = Wake up 
    LCD_RS_SetLow(); //D/I=LOW : send instruction
    LCD_RW_SetLow(); //R/W=LOW: Write
    LCD_EN_SetHigh();
    LCD_EN_SetLow();
    Time_delayMS(1); //must wait 160us, busy flag not available
    PORTE = 0x30; //command 0x30 = Wake up 
    LCD_RS_SetLow(); //D/I=LOW : send instruction
    LCD_RW_SetLow(); //R/W=LOW: Write
    LCD_EN_SetHigh();
    LCD_EN_SetLow();
    
    Time_delayMS(1); //must wait 160us, busy flag not available
    lcd_send_cmd(0x38); //Function set: 8-bit/2-line
    lcd_send_cmd(0x0c); //Display ON; 
    //lcd_send_cmd(0x10); //Set cursor
    lcd_send_cmd(0x06); //Entry mode set
    lcd_send_cmd(LCD_CLEAR); // Clear the LCD
    
    lcd_send_cmd(LCD_HOME); // Send LCD home
}

void lcd_send_cmd(uint8_t cmd) 
{
    PORTE = cmd; //put data on output Port
    LCD_RS_SetLow(); //D/I=LOW : send instruction
    LCD_RW_SetLow(); //R/W=LOW: Write
    LCD_EN_SetHigh();
    Time_delayMS(1); //enable pulse width>= 300ns
    LCD_EN_SetLow(); //Clock enable: falling edge
    lcd_wait_busy();
}

void lcd_write_char(char write)
{
    PORTE = write;//put data on output Port
    LCD_RS_SetHigh();//D/I=HIGH: send data
    LCD_RW_SetLow();//R/W=LOW : Write
    LCD_EN_SetHigh();
    Time_delayMS(1);//enable pulse width>= 300ns
    LCD_EN_SetLow();//Clock enable: falling edge
    lcd_wait_busy();
}

void lcd_write_str(char * str)
{
    char * c = str; 
    do
    {
        lcd_write_char(*c);
        c++;
    }while(*c);
}

void lcd_wait_busy()
{
    // Set register E data direction to input
    TRISE = 0x00ff;
    
    // Set RW to read
    LCD_RW_SetHigh();
    LCD_EN_SetHigh();
    do
    {
        continue;
    }while(PORTE & 0x80); // While PORTE bit 7 is high stay in loop
    LCD_EN_SetLow();
    
    // Set register E data direction to output
    TRISE = 0x0000;
}


void lcd_set_cursor(uint8_t cursor)
{
    // Set the base for the instruction to write to DDRAM as 0b10000000
    const uint8_t base_int = 0x80;
    
    // Select the line bit
    uint8_t line = 0x10 & cursor;
    // Select the position on the line
    uint8_t pos = 0x0f & cursor;
    
    // Make the complete command
    uint8_t cmd = base_int + (line ? 0x40 : 0x00) + pos;
    
    // Send the LCD command
    lcd_send_cmd(cmd);
}
