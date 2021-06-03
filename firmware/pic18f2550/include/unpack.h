/* 
 * File:   unpack.h
 * Author: christophe
 *
 * Created on June 2, 2021, 1:12 PM
 */

#ifndef UNPACK_H
#define	UNPACK_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack1_high(unsigned char x, unsigned char y);

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack1_low(unsigned char x, unsigned char y);

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack2_high(unsigned char x, unsigned char y);

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack2_low(unsigned char x, unsigned char y);

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack4_high(unsigned char x, unsigned char y);

/**
 * 
 * @param x
 * @param y
 * @return 
 */
unsigned char unpack4_low(unsigned char x, unsigned char y);


#ifdef	__cplusplus
}
#endif

#endif	/* UNPACK_H */

