/* 
 * File:   OW400PCB.h
 * Author: Colton
 *
 * Created on March 24, 2021, 11:50 AM
 */

#ifndef OW400PCB_H
#define	OW400PCB_H

#include <xc.h>

#define CONFIG_TRISD 0x0814
#define CONFIG_TRISF 0x0034
#define CONFIG_TRISE 0x0000

#define LAT_CS_DDS LATDbits.LATD0//CS0 or pin 46
#define LAT_CS_PGA0 LATDbits.LATD6//CS1 or pin 54
#define LAT_CS_PGA1 LATDbits.LATD7//CS2 or pin 55
#define LAT_CS_AIOFFSET LATFbits.LATF0//CS3 or pin 58
#define LAT_CS_SCOPETRIG LATFbits.LATF1//CS4 or pin 59

#define LAT_LED LATDbits.LATD5//pin 53

#endif	/* OW400PCB_H */

