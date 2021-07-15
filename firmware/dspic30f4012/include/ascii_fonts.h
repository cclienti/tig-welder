/* 
 * File:   ascii_fonts.h
 * Author: christophe
 *
 * Created on June 2, 2021, 7:23 PM
 */

#ifndef ASCII_FONTS_H
#define	ASCII_FONTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
/**
 * ASCII table shifted by 32. From "SPACE" (32d) to "~" (126d).
 * 
 * Eight user chars are available between 24d and 31d.
 */    
extern uint8_t misc_fixed_5x7[][5];



#ifdef	__cplusplus
}
#endif

#endif	/* ASCII_FONTS_H */

