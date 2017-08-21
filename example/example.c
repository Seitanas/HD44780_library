/*
 * Author: Tadas Ustinavičius
 */




// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include "16x2lib.h"

void main(void) {
    CMCON = 0x07; // comparators off
    LCDInit(); // init LCD display
    while(1){
        DisplayText("hello", FIRST_LINE);
        DisplayText("world", SECOND_LINE);
        __delay_ms(1000);
        ClearLCD();
        DisplayText("world", FIRST_LINE);
        DisplayText("hello", SECOND_LINE);
        __delay_ms(1000);
        ClearLCD();
    }  
}
