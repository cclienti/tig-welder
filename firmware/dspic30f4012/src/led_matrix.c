#include "ascii_fonts.h"
#include "led_matrix.h"
#include "unpack.h"
#include <xc.h>

// https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

#define REG_DECODE_MODE       0x09
#define REG_INTENSITY         0x0A
#define REG_SCAN_LIMIT        0x0B
#define REG_SHUTDOWN          0x0C
#define REG_DISPLAY_TEST      0x0F

#define LED_MATRIX_FONT_WIDTH 5
#define LED_MATRIX_MAX_CHAR   (LED_MATRIX_NUM_MODULES*8 / LED_MATRIX_FONT_WIDTH)

#define ARRAY_SIZE(x)         (sizeof(x)/sizeof(x[0]))


static uint8_t virtual_buffer[LED_MATRIX_NUM_MODULES*8];
static uint8_t physical_buffer[LED_MATRIX_NUM_MODULES*8];
static uint8_t char_pos = 0;
static bool vertical_flip = false;
static bool horizontal_flip = false;


static void spi_send(uint8_t data)
{
    LED_MATRIX_SPI_SEND(data);
}

static void send_command(uint8_t reg, uint8_t value)
{
    LED_MATRIX_SPI_CSn = 0;
    for (uint8_t i=0; i<LED_MATRIX_NUM_MODULES; i++) {
        spi_send(reg); spi_send(value);
    }
    LED_MATRIX_SPI_CSn = 1;
}

static void led_matrix_send_line(uint8_t digit, uint8_t data[], uint8_t len)
{
    LED_MATRIX_SPI_CSn = 0;
    for (uint8_t i = 0; i<len; i++) {
        spi_send(digit);
        spi_send(data[i]);
    }
    LED_MATRIX_SPI_CSn = 1;
}

static void led_matrix_buffer_transpose(void)
{
    uint8_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;
    uint8_t *pdisplay;

    if (horizontal_flip) {
        pdisplay = virtual_buffer + ARRAY_SIZE(virtual_buffer)-1;
    }
    else {
        pdisplay = virtual_buffer;
    }

    for (uint8_t i=0; i<LED_MATRIX_NUM_MODULES; i++) {
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

void led_matrix_hflip(bool state)
{
    horizontal_flip = state;
}

void led_matrix_vflip(bool state)
{
    vertical_flip = state;
}

void led_matrix_init(bool hflip, bool vflip, uint8_t luminosity)
{
    send_command(REG_DISPLAY_TEST, 0x00);
    send_command(REG_DECODE_MODE, 0x00);
    send_command(REG_SCAN_LIMIT, 0x07);
    send_command(REG_SHUTDOWN, 0x01);
    led_matrix_luminosity(luminosity);
    led_matrix_hflip(hflip);
    led_matrix_vflip(vflip);
    led_matrix_clear();
    led_matrix_buffer_clear();
}

void led_matrix_luminosity(uint8_t value)
{
    send_command(REG_INTENSITY, value >> 4);
}

void led_matrix_test(bool enable)
{
    send_command(REG_DISPLAY_TEST, enable);
}

void led_matrix_clear(void)
{
    for (uint8_t s=1; s<9; s++) {
        LED_MATRIX_SPI_CSn = 0;
        for (uint8_t i=0; i<LED_MATRIX_NUM_MODULES; i++) {
            spi_send(s); spi_send(0x00);
        }
        LED_MATRIX_SPI_CSn = 1;
    }
}

void led_matrix_buffer_clear(void)
{
    led_matrix_setpos(0);
    for (uint8_t i=0; i<ARRAY_SIZE(virtual_buffer); i++)
    {
        virtual_buffer[i] = 0;
    }
}

void led_matrix_buffer_send(void)
{
    led_matrix_buffer_transpose();
    uint8_t *pbuf = physical_buffer;

    if (vertical_flip) {
        for (uint8_t i = 8; i>=1; i--, pbuf += 4) {
            led_matrix_send_line(i, pbuf, 4);
        }
    }
    else {
        for (uint8_t i = 1; i<=8; i++, pbuf += 4) {
            led_matrix_send_line(i, pbuf, 4);
        }
    }
}

void led_matrix_putchar(char c)
{
    uint8_t *pdisplay;

    if (char_pos >= LED_MATRIX_MAX_CHAR) {
        return;
    }

    pdisplay = virtual_buffer + char_pos * LED_MATRIX_FONT_WIDTH;
    char_pos++;

    if (horizontal_flip) {
        for (uint8_t i=LED_MATRIX_FONT_WIDTH; i!=255;) {
            *pdisplay++ = misc_fixed_5x7[c-24][i--];
        }
    }
    else {
        for (uint8_t i=0; i<LED_MATRIX_FONT_WIDTH; i++) {
            *pdisplay++ = misc_fixed_5x7[c-24][i];
        }
    }
}

void led_matrix_print(const char *str)
{
    while(*str != 0) {
        led_matrix_putchar(*str++);
    }
}

static uint16_t mul10_u16(uint16_t num) {
    return (uint16_t) (num << 3) + (uint16_t) (num << 1);
}

void led_matrix_print_u16(uint16_t num, char lead_char, uint8_t num_digits)
{
    char buf[5];
    char *pbuf;
    
    // Extract dedcimal digits
    for (uint8_t i=0; i<ARRAY_SIZE(buf); i++) {
        uint16_t tmp = num / 10;
        buf[i] = (char) (num - mul10_u16(tmp) + '0'); // avoid modulus operation
        num = tmp;
    }

    // Pad with the leading char and find the last_digit position
    uint8_t last_digit = ARRAY_SIZE(buf)-1;
    pbuf = buf + last_digit;
    while(last_digit > 0) {
        if (*pbuf != '0') {
            break;
        }
        *pbuf-- = lead_char;
        last_digit--;
    }

    // Remove unwanted decimal digits
    num_digits = num_digits == 0 ? 1 : num_digits;
    num_digits = num_digits > ARRAY_SIZE(buf) ? ARRAY_SIZE(buf)-1 : num_digits-1;
    last_digit = last_digit < num_digits ? num_digits : last_digit;
    
    // write the selected decimal digits in the buffer
    pbuf = buf + last_digit;
    for (uint8_t i=0; i<=last_digit; i++) {
        led_matrix_putchar(*pbuf--);
    }
}

void led_matrix_print_u16_dec1(uint16_t num, char lead_char, uint8_t num_digits)
{
    uint16_t tmp = num / 10;
    char dec = (char) (num - mul10_u16(tmp) + '0');
    led_matrix_print_u16(tmp, lead_char, num_digits);
    led_matrix_putchar('.');
    led_matrix_putchar(dec);
}

void led_matrix_setpos(uint8_t pos)
{
    if (pos >= LED_MATRIX_MAX_CHAR) {
        return;
    }
    char_pos = pos;
}
