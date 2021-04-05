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
 * File:   LCD_Manager.h
 * Author: Andy Smit
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_MANAGER_H
#define	LCD_MANAGER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02

/*
 * lcd_init
 * 
 * Sends commands to the LCD to initialize the LCD display. Called at 
 * initialization.
 * 
 * Parameters: None
 * Returns: None
 */
void lcd_init();


/*
 * lcd_send_cmd
 * 
 * Sends a command to the LCD. 
 * 
 * param: 8bit 
 */
void lcd_send_cmd(uint8_t cmd);


/*
 * lcd_write_char
 * 
 * Writes a char at the current cursor location.
 * 
 * param: Character to write to the LCD
 * 
 */
void lcd_write_char(char write);


/*
 * lcd_write_str
 * 
 * Writes a string to the LCD
 * 
 * param: character pointer to a proper C string to write to the LCD. 
 * returns: none
 */
void lcd_write_str(char * str);


/*
 * lcd_wait_busy
 * 
 * Check if the LCD is currently busy and waits for it to finish.
 * 
 * param: none
 * return: none
 */
void lcd_wait_busy();


/*
 * lcd_set_cursor
 * 
 * Sets the cursor position on the LCD
 * 
 * param: uint8_t cursor. Bits 0:3 specify the position on the line. 
 * Bit 4 specifies the bottom line if bit4 == 1.
 */
void lcd_set_cursor(uint8_t cursor);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

