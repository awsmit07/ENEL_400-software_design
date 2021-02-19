/*
 * File:   main.c
 * Author: amrit
 *
 * Created on February 18, 2021, 6:09 PM
 */


#include "xc.h"
#include "UART2.h"
#include "ChangeClk.h"
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled

int main(void) {
    NewClk(8); //8 MHZ clock for 9600 baud rate
     AD1PCFG = 0xFFFF; // Turn all analog pins as digital
     while(1)
     {
         uint16_t graph[] = {10,20,40,60,80};
         int i;
         for(i = 0; i < 5; i++)
         {
             Disp2Dec(graph[i]);
         }
         
         
     }
}
