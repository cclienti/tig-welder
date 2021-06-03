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

#include <stdint.h>

/**
 * Interleave bits of the x and y nibbles (MSBs)
 * 
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack1_high(uint8_t x, uint8_t y);

/**
 * Interleave bits of the x and y nibbles (LSBs)
 * 
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack1_low(uint8_t x, uint8_t y);

/**
 * Interleave pair of bits of the x and y nibbles (MSBs)
 * 
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack2_high(uint8_t x, uint8_t y);

/**
 * Interleave pair of bits of the x and y nibbles (LSBs)
 * 
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack2_low(uint8_t x, uint8_t y);

/**
 * Interleave x and y high nibbles (MSBs)
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack4_high(uint8_t x, uint8_t y);

/**
 * Interleave x and y high nibbles (LSBs)
 * 
 * @param x
 * @param y
 * @return 
 */
uint8_t unpack4_low(uint8_t x, uint8_t y);


#ifdef	__cplusplus
}
#endif

#endif	/* UNPACK_H */

