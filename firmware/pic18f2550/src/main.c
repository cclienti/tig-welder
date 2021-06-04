/*
 * File:   main.c
 * Author: christophe
 *
 * Created on May 30, 2021, 11:09 PM
 */

// PIC18F2550 Configuration Bit Settings

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


#include "led_matrix.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * Helpers to set/get ports
 */
#define PEDAL_SWITCH   PORTBbits.RB4
#define LED_RED        LATBbits.LATB2
#define LED_YELLOW     LATBbits.LATB3
#define ARC_RELAY      LATCbits.LATC0
#define PUMP_SOLENOID  LATCbits.LATC1
#define HF_RELAY       LATCbits.LATC2

#define PEDAL_RELEASED ((PEDAL_SWITCH != 0) && (PEDAL_SWITCH != 0) && (PEDAL_SWITCH != 0))
#define PEDAL_PRESSED  ((PEDAL_SWITCH == 0) && (PEDAL_SWITCH == 0) && (PEDAL_SWITCH == 0))

/**
 * Welding Constants
 */
# define PRE_FLOW_TIME   5  // 0.5s
# define POST_FLOW_TIME 60  // 6.0s

/**
 * Configure the clock to 8Mhz
 */
void wait_stable_clock(void)
{
    OSCCONbits.IRCF = 7;  // 8Mhz Internal Oscillator
    while (!OSCCONbits.IOFS); // Wait for a stable clock
}

/**
 * Initialize in/out ports
 */
void init(void)
{
    wait_stable_clock();

    // Disable Analog inputs
    ADCON1bits.PCFG = 0xf;

    // SPI
    TRISBbits.TRISB0 = 1;  // SPI SDI input
    TRISBbits.TRISB1 = 0;  // SPI SCK output
    TRISCbits.TRISC7 = 0;  // SPI SDO output
    LATCbits.LATC6 = 1;    // SPI /CS default to 1
    TRISCbits.TRISC6 = 0;  // SPI /CS input
    SSPCON1bits.SSPM = 0;  // SPI MASTER Fosc/4 => 2Mhz SPI speed
    SSPCON1bits.CKP = 1;   // SPI Idle state for clock is a low level
    SSPCON1bits.SSPEN = 1; // SPI Enable

    // Inputs
    TRISBbits.TRISB4 = 1;  // Pedal switch

    // Outputs
    LED_RED = 0;
    TRISBbits.TRISB2 = 0;  // Red LED

    LED_YELLOW = 0;
    TRISBbits.TRISB3 = 0;  // Yellow LED

    ARC_RELAY = 0;
    TRISCbits.TRISC0 = 0;  // ARC relay

    PUMP_SOLENOID = 0;
    TRISCbits.TRISC1 = 0;  // Pump solenoid

    HF_RELAY = 0;
    TRISCbits.TRISC2 = 0;  // HF relay
}


/**
 * Start the timer to wait for n tenth of seconds
 * @param n, tenth of seconds, max 80
 */
void start_tenth_chrono(uint16_t n)
{
    // FOSC/4 = 2'000'000
    // Prescaler = 256
    // Timer tick = 256/2'000'000 = 0.000128s
    // 1/10s corresponds to 0.1/0.000128 = 781.25
    T0CON = 0;
    uint16_t value = 65535 - (n>>2) - n*781;
    TMR0H = value >> 8;
    TMR0L = value & 0xff;
    T0CON = 0x87;
}

/**
 * Check if the chrono is ended (timer overflow)
 * @return 1 if ended, else 0
 */
uint8_t is_chrono_ended(void)
{
    if (!TMR0IF) {
        return 0;
    }

    T0CON = 0;
    TMR0IF = 0;
    return 1;
}

/**
 * FSM States
 */
enum States {
    IDLE,
    PRE_FLOW_START, PRE_FLOW_WAIT,
    HF_START,
    WELDING,
    POST_FLOW_START, POST_FLOW_WAIT
};

/**
 * Main entry point
 */
void main(void)
{
    init();

    led_matrix_init(true, false, 64);

    led_matrix_buffer_clear();
    led_matrix_print("PR=");
    led_matrix_setpos(3);
    led_matrix_print_u16_dec1(32, '0', 1);
    led_matrix_buffer_send();

    //led_matrix_demo();

    enum States state = IDLE;
    while (1) {
        uint8_t pedal_pressed = PEDAL_PRESSED;
        uint8_t pedal_released = !pedal_pressed;
        uint8_t chrono_ended = is_chrono_ended();

        switch(state) {
        case IDLE:
            LED_RED = 0;
            LED_YELLOW = 0;
            ARC_RELAY = 0;
            PUMP_SOLENOID = 0;
            HF_RELAY = 0;
            if (pedal_pressed) {
                state = PRE_FLOW_START;
            }
            break;

        case PRE_FLOW_START:
            LED_RED = 0;
            LED_YELLOW = 1;
            ARC_RELAY = 0;
            PUMP_SOLENOID = 1;
            HF_RELAY = 0;
            state = PRE_FLOW_WAIT;
            start_tenth_chrono(PRE_FLOW_TIME);
            break;

        case PRE_FLOW_WAIT:
            LED_RED = 0;
            LED_YELLOW = 1;
            ARC_RELAY = 0;
            PUMP_SOLENOID = 1;
            HF_RELAY = 0;
            if (chrono_ended) {
                state = HF_START;
            }
            break;

        case HF_START:
            LED_RED = 1;
            LED_YELLOW = 1;
            ARC_RELAY = 1;
            PUMP_SOLENOID = 1;
            HF_RELAY = 1;
            if (pedal_released) {
                state = WELDING;
            }
            break;

        case WELDING:
            LED_RED = 1;
            LED_YELLOW = 1;
            ARC_RELAY = 1;
            PUMP_SOLENOID = 1;
            HF_RELAY = 0;
            if (pedal_pressed) {
                state = POST_FLOW_START;
            }
            break;

        case POST_FLOW_START:
            LED_RED = 0;
            LED_YELLOW = 1;
            ARC_RELAY = 0;
            PUMP_SOLENOID = 1;
            HF_RELAY = 0;
            state = POST_FLOW_WAIT;
            start_tenth_chrono(POST_FLOW_TIME);
            break;

        case POST_FLOW_WAIT:
            LED_RED = 0;
            LED_YELLOW = 1;
            ARC_RELAY = 0;
            PUMP_SOLENOID = 1;
            HF_RELAY = 0;
            if (chrono_ended) {
                state = IDLE;
            }
            break;
        }

    }
}
