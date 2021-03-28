/* 
 * File:   Utils.h
 * Author: Colton
 *
 * Created on March 18, 2021, 12:41 PM
 */

#ifndef UTILS_H
#define	UTILS_H

//r - register or flags variable
//o - starting index to read of write from (inclusive)
//b - binary mask to read or clear
#define __set_bits(r,o,b) (r |= ((b)<<(o)))
#define __clear_bits(r,o,b) (r &= (~((b)<<(o))))
#define __read_bits(r,o,b) (r & ((b)<<(o)))
#define __is_flag(r,b) (__read_bits(r,0,b) == b)
#define __ack_flag(r,b) __clear_bits(r,0,b)

#endif	/* UTILS_H */

