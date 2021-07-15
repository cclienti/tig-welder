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
#define LED_MATRIX_SPI_CSn LATDbits.LATD0
#endif

#ifndef LED_MATRIX_SPI_SEND
#define LED_MATRIX_SPI_SEND(SPI_BYTE)     \
    IFS0bits.SPI1IF = 0;                  \
    SPI1STATbits.SPIROV = 0;              \
    SPI1BUF = SPI_BYTE;                   \
    while(IFS0bits.SPI1IF == 0)
#endif    
  

/**
 * Initialize the LED Matrix.
 * 
 * @param hflip, horizontal flip
 * @param vflip, vertical flip
 * @param luminosity, min:0 and max:255
 */
void led_matrix_init(bool hflip, bool vflip, uint8_t luminosity);

/**
 * Change the luminosity.
 * 
 * @param value, min:0 and max:255
 */
void led_matrix_luminosity(uint8_t value);

/**
 * Enable or disable test mode
 * 
 * @param enable, enable/disable test mode
 */
void led_matrix_test(bool enable);

/**
 * Clear the device.
 */
void led_matrix_clear(void);

/**
 * Flip horizontally the display.
 * 
 * It will be applied to the next buffer fill/send
 * 
 * @param value, horizontal flip enable
 */
void led_matrix_hflip(bool value);

/**
 * Flip vertically the display.
 * 
 * It will be applied to the next buffer fill/send
 * 
 * @param value, vertical flip enable
 */
void led_matrix_vflip(bool value);

/**
 * Clear the virtual buffer
 */
void led_matrix_buffer_clear(void);

/**
 * Send the buffer content to the matrix display
 */
void led_matrix_buffer_send(void);

/**
 * Write a character in the buffer at the current cursor position.
 * 
 * @param c, char to send in the buffer
 */
void led_matrix_putchar(char c);

/**
 * Print the string in the buffer at the current position
 */
void led_matrix_print(const char *str);

/**
 * Print the short int number in the buffer at current cursor position.
 * 
 * @param num, number to display
 * @param lead_char, example ' ' or '0'
 * @param num_digits
 */

void led_matrix_print_u16(uint16_t num,
                          char lead_char, uint8_t num_digits);

/**
 * Print the short int number coded at tenth in the buffer at the current position.
 * 
 * The representation is (num/10).(num%10)
 * 
 * @param num, number to display
 * @param lead_char, example ' ' or '0'
 * @param num_digits, related to the integer part.
 */
void led_matrix_print_u16_dec1(uint16_t num, char lead_char, uint8_t num_digits);

/**
 * Change the cursor position.
 * 
 * @param pos
 */
void led_matrix_setpos(uint8_t pos);

    
#ifdef	__cplusplus
}
#endif

#endif	/* LED_MATRIX_H */

