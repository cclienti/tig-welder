#include "ascii_fonts.h"
#include "led_matrix.h"
#include "unpack.h"
#include <xc.h>

// https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

#define REG_DECODE_MODE  0x09
#define REG_INTENSITY    0x0A
#define REG_SCAN_LIMIT   0x0B
#define REG_SHUTDOWN     0x0C
#define REG_DISPLAY_TEST 0x0F

#define LED_MATRIX_FONT_WIDTH 5


static unsigned char virtual_buffer[LED_MATRIX_NUM_MODULES*8];
static unsigned char physical_buffer[LED_MATRIX_NUM_MODULES*8];
static unsigned char vertical_flip = 0;
static unsigned char horizontal_flip = 1;
static unsigned char char_pos = 0;


static void spi_send(unsigned char data)
{
    LED_MATRIX_SPI_BUFFER = data;        
    while(!LED_MATRIX_SPI_DONE_FLAG);
    LED_MATRIX_SPI_DONE_FLAG = 0;
}

static void send_command(unsigned char reg, unsigned char value)
{
    LED_MATRIX_SPI_CSn = 0;
    for (unsigned char i=0; i<LED_MATRIX_NUM_MODULES; i++) {
        spi_send(reg); spi_send(value);
    }
    LED_MATRIX_SPI_CSn = 1;
}

void led_matrix_init(void)
{
    send_command(REG_DISPLAY_TEST, 0x00);
    send_command(REG_DECODE_MODE, 0x00);
    send_command(REG_SCAN_LIMIT, 0x07);
    send_command(REG_SHUTDOWN, 0x01);
}

void led_matrix_luminosity(unsigned char value)
{
    send_command(REG_INTENSITY, value >> 4);
}

void led_matrix_clear(void)
{
    for (unsigned char s=1; s<9; s++) {
        LED_MATRIX_SPI_CSn = 0;
        for (unsigned char i=0; i<LED_MATRIX_NUM_MODULES; i++) {
            spi_send(s); spi_send(0x00);
        }
        LED_MATRIX_SPI_CSn = 1;        
    }
}

void led_matrix_send_line(unsigned char digit, unsigned char data[], unsigned char len)
{
    LED_MATRIX_SPI_CSn = 0;
    for (unsigned char i = 0; i<len; i++) {
        spi_send(digit); 
        spi_send(data[i]);
    }
    LED_MATRIX_SPI_CSn = 1;
}

static void led_matrix_buffer_transpose(void)
{
    unsigned char a0, a1, a2, a3, a4, a5, a6, a7;
    unsigned char b0, b1, b2, b3, b4, b5, b6, b7;
    unsigned char *pdisplay;
    
    if (horizontal_flip) {
        pdisplay = virtual_buffer + sizeof(virtual_buffer)-1;
    }
    else {
        pdisplay = virtual_buffer;
    }

    for (unsigned char i=0; i<LED_MATRIX_NUM_MODULES; i++) {
        if (horizontal_flip) {
            a0 = *pdisplay--;
            a1 = *pdisplay--;
            a2 = *pdisplay--;
            a3 = *pdisplay--;
            a4 = *pdisplay--;
            a5 = *pdisplay--;
            a6 = *pdisplay--;
            a7 = *pdisplay--;
        }
        else {
            a0 = *pdisplay++;
            a1 = *pdisplay++;
            a2 = *pdisplay++;
            a3 = *pdisplay++;
            a4 = *pdisplay++;
            a5 = *pdisplay++;
            a6 = *pdisplay++;
            a7 = *pdisplay++;
        }
        
        b0 = unpack1_low( a0, a1);
        b1 = unpack1_low( a2, a3);
        b2 = unpack1_high(a0, a1);
        b3 = unpack1_high(a2, a3);
        b4 = unpack1_low( a4, a5);
        b5 = unpack1_low( a6, a7);
        b6 = unpack1_high(a4, a5);
        b7 = unpack1_high(a6, a7);

        a0 = unpack2_low( b0, b1);
        a1 = unpack2_low( b4, b5);            
        a2 = unpack2_high(b0, b1);
        a3 = unpack2_high(b4, b5);
        a4 = unpack2_low( b2, b3);
        a5 = unpack2_low( b6, b7);            
        a6 = unpack2_high(b2, b3);
        a7 = unpack2_high(b6, b7);

        physical_buffer[ 0 + i] = unpack4_low( a0, a1);
        physical_buffer[ 4 + i] = unpack4_high(a0, a1);
        physical_buffer[ 8 + i] = unpack4_low( a2, a3);
        physical_buffer[12 + i] = unpack4_high(a2, a3);
        physical_buffer[16 + i] = unpack4_low( a4, a5);
        physical_buffer[20 + i] = unpack4_high(a4, a5);
        physical_buffer[24 + i] = unpack4_low( a6, a7);
        physical_buffer[28 + i] = unpack4_high(a6, a7);
    }
}

void led_matrix_buffer_clear()
{
    char_pos = 0;
    for (int i=0; i<sizeof(virtual_buffer)/sizeof(virtual_buffer[0]); i++)
    {
        virtual_buffer[i] = 0;
    }
}

void led_matrix_buffer_send()
{
    led_matrix_buffer_transpose();
    unsigned char *pbuf = physical_buffer;

    if (vertical_flip) {
        for (unsigned char i = 8; i>=1; i--, pbuf += 4) {
            led_matrix_send_line(i, pbuf, 4);
        }
    }
    else {
        for (unsigned char i = 1; i<=8; i++, pbuf += 4) {
            led_matrix_send_line(i, pbuf, 4);
        }
    }
}

void led_matrix_putchar(unsigned char c)
{
    unsigned char *pdisplay = virtual_buffer + char_pos * LED_MATRIX_FONT_WIDTH;
    char_pos++;
    if (horizontal_flip) {
        for (unsigned char i=LED_MATRIX_FONT_WIDTH; i!=255;) {
            *pdisplay++ = misc_fixed_5x7[c-32][i--];
        }
    }
    else {
        for (unsigned int i=0; i<LED_MATRIX_FONT_WIDTH; i++) {
            *pdisplay++ = misc_fixed_5x7[c-32][i];
        }
    }
}

void led_matrix_demo(void)
{
    for(unsigned char i= 0; i<16; i++) {
        led_matrix_buffer_clear();
        led_matrix_buffer_send();
        for(int t=0; t<10000; t++) {
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
        }

        led_matrix_putchar('H');
        led_matrix_putchar('E');
        led_matrix_putchar('L');
        led_matrix_putchar('L');
        led_matrix_putchar('O');

        led_matrix_buffer_send();
        for(int t=0; t<30000; t++) {
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
        }
        
        led_matrix_buffer_clear();
        led_matrix_buffer_send();
        for(int t=0; t<10000; t++) {
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
        }

        led_matrix_putchar('W');
        led_matrix_putchar('O');
        led_matrix_putchar('R');
        led_matrix_putchar('L');
        led_matrix_putchar('D');
        led_matrix_putchar('!');
        led_matrix_buffer_send();
        for(int t=0; t<30000; t++) {
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");
        }
    }

}

