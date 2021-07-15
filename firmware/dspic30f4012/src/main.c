/*
 * File:   main.c
 * Author: christophe
 *
 * Created on July 14, 2021, 5:36 PM
 */

// DSPIC30F4012 Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FPR = XT_PLL16           // Primary Oscillator Mode (XT w/PLL 16x)
#pragma config FOS = PRI                // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)
// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)
// FBORPOR
#pragma config FPWRT = PWRT_OFF          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_OFF          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)
// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


#include "led_matrix.h"
#include <xc.h>


#define GAZ_SOLENOID_DIR        TRISEbits.TRISE5
#define GAZ_SOLENOID            LATEbits.LATE5

#define HF_SPARK_DIR            TRISEbits.TRISE4
#define HF_SPARK                LATEbits.LATE4

#define ROT_SWITCH_DIR          TRISBbits.TRISB3
#define ROT_SWITCH              PORTBbits.RB3

#define ROT_A_DIR               TRISBbits.TRISB4
#define ROT_A                   PORTBbits.RB4

#define ROT_B_DIR               TRISBbits.TRISB5
#define ROT_B                   PORTBbits.RB5


/**
 * Configure the clock to 8Mhz
 */
void wait_stable_clock(void)
{
    while (!OSCCONbits.LOCK); // Wait for a stable clock
}

/**
 * Initialize in/out ports
 */
void init(void)
{
    wait_stable_clock();

    // SPI
    TRISEbits.TRISE8 = 0;    // SPI SCK OUT
    TRISFbits.TRISF3 = 0;    // SPI SDO OUT
    LATDbits.LATD0 = 1;      // SPI /CS default to 1
    TRISDbits.TRISD0 = 0;    // SPI /CS OUT
    SPI1CONbits.SSEN = 0;    // /CS pin not controlled by the module
    SPI1CONbits.CKP = 0;     // SPI Idle state for clock is a low level
    SPI1CONbits.CKE = 1;     // SPI Idle state for clock is a low level
    SPI1CONbits.MSTEN = 1;   // SPI Master
    SPI1CONbits.PPRE = 2;    // SPI Primary prescale 4:1
    SPI1CONbits.SPRE = 2;    // SPI Secondary prescale 6:1 => 1Mhz (Fosc=96Mhz)
    SPI1CONbits.MODE16 = 0;  // SPI 8-bit mode
    SPI1CONbits.DISSDO = 0;  // SPI SDO controlled by the module
    SPI1CONbits.FRMEN = 0;   // SPI Frame mode disabled
    SPI1STATbits.SPIEN = 1;  // SPI Enable
    
    // QEI
    ROT_SWITCH_DIR = 1;
    ADPCFGbits.PCFG3 = 1;  // INDX as digital input
    ADPCFGbits.PCFG4 = 1;  // QEA as digital input
    ADPCFGbits.PCFG5 = 1;  // QEB as digital input
    QEICONbits.QEIM = 0;       // Disable QEI Module
    QEICONbits.CNTERR = 0;     // Clear any count errors
    QEICONbits.QEISIDL = 0;    // Continue operation during sleep
    QEICONbits.SWPAB = 0;      // QEA and QEB not swapped
    QEICONbits.PCDOUT = 0;     // Normal I/O pin operation
    DFLTCONbits.CEID = 1;      // Count error interrupts disabled
    DFLTCONbits.QEOUT = 1;     // Digital filters output enabled for QEn pins
    DFLTCONbits.QECK = 7;      // 1:256 clock divide for digital filter for QEn
    POSCNT = 0;                // Reset position counter
    MAXCNT = 0xffff;
    QEICONbits.QEIM = 5;       // X4 mode with position counter reset by MAXCNT
    
    // GAZ Solenoid
    GAZ_SOLENOID = 0;
    GAZ_SOLENOID_DIR = 0;

    /*
    // Inputs
    TRISBbits.TRISB4 = 1;  // Pedal switch
    TRISAbits.TRISA3 = 1;  // Btn1
    TRISAbits.TRISA4 = 1;  // Btn2
    TRISAbits.TRISA5 = 1;  // Btn3

    // Outputs
    LED_RED = 0;
    TRISBbits.TRISB2 = 0;  // Red LED

    LED_YELLOW = 0;
    TRISBbits.TRISB3 = 0;  // Yellow LED

    ARC_RELAY = 0;
    TRISCbits.TRISC0 = 0;  // ARC relay
    */
    /*
    HF_RELAY = 0;
    TRISCbits.TRISC2 = 0;  // HF relay
    */
}



int main(void) {
    init();

    led_matrix_init(true, false, 16);
    
    while(1) {
        static uint16_t prevcnt = 0;
        if (ROT_SWITCH == 0) {
            POSCNT=-1;
        }
        if (prevcnt != POSCNT) {
            prevcnt = POSCNT;
            led_matrix_buffer_clear();
            led_matrix_print_u16(prevcnt/2, ' ', 5);
            led_matrix_buffer_send();
        }
    }
    return 0;
}
