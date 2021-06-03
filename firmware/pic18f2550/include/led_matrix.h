/* 
 * File:   led_matrix.h
 * Author: christophe
 *
 * Created on June 2, 2021, 8:10 AM
 */

#ifndef LED_MATRIX_H
#define	LED_MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
    
#ifndef LED_MATRIX_NUM_MODULES
#define LED_MATRIX_NUM_MODULES 4
#endif    
    
#ifndef LED_MATRIX_SPI_CSn
#define LED_MATRIX_SPI_CSn LATCbits.LATC6
#endif

#ifndef LED_MATRIX_SPI_BUFFER
#define LED_MATRIX_SPI_BUFFER SSPBUF
#endif
    
#ifndef LED_MATRIX_SPI_DONE_FLAG
#define LED_MATRIX_SPI_DONE_FLAG SSPIF
#endif
   
    

/**
 * Initialize the LED Matrix.
 */
void led_matrix_init(bool hflip, bool vflip, uint8_t luminosity);

/**
 * Change the luminosity.
 * 
 * @param value
 */
void led_matrix_luminosity(uint8_t value);

/**
 * Clear the device.
 */
void led_matrix_clear(void);

/**
 * Flip horizontally the display.
 * 
 * It will be applied to the next buffer fill/send
 */
void led_matrix_hflip(bool value);

/**
 * Flip vertically the display.
 * 
 * It will be applied to the next buffer fill/send
 */
void led_matrix_vflip(bool value);

/**
 * A Simple led display demo.
 */
void led_matrix_demo(void);

    
#ifdef	__cplusplus
}
#endif

#endif	/* LED_MATRIX_H */

