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
 * Initialize the LED Matrix
 */
void led_matrix_init(void);

/**
 * 
 * @param value
 */
void led_matrix_luminosity(unsigned char value);

/**
 * 
 */
void led_matrix_clear(void);

/**
 * 
 * @param data
 * @param len
 */
void led_matrix_send(unsigned char data[], unsigned char len);

/**
 * 
 */
void led_matrix_demo(void);

    
#ifdef	__cplusplus
}
#endif

#endif	/* LED_MATRIX_H */

