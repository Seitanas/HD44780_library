/*
 * File:   16x2lib.c
 * Author: Tadas Ustinavičius
 *
*/

#include "16x2lib.h"

void Delay5ms(void){
    __delay_ms(5);
}
void Delay100us(void){
    __delay_us(100);    
}
void ResetPins(void){
    /* resets all pins to 0: */
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    E = 0;
    RS = 0;    
}
void WriteSequence(void){
    /* pushes data to LCD memory: */
    E = 1;
    Delay100us();
    E = 0;
    Delay100us();
}
void WriteLCD(char value, int command_type, int single_pass){
    /* sends single data or command byte to LCD module
     * 4bit data bus 
     * value: a byte which will be sent to LCD module
     * command type: 0 - command byte, 1 - character byte
     * single_pass: only 4 least significant bits will be sent
     * LCD module.   
     */
    RS = command_type;
    if (!single_pass){
        /* emit 4 most significant bits to each of data pins: */
        D4 = (0x10 & value) >> 4;
        D5 = (0x20 & value) >> 5;
        D6 = (0x40 & value) >> 6;
        D7 = (0x80 & value) >> 7;
        WriteSequence();
    }
    /* emit 4 least significant bits to each of data pins: */
    D4 = 0x01 & value;
    D5 = (0x02 & value) >> 1;
    D6 = (0x04 & value) >> 2;
    D7 = (0x08 & value) >> 3;
    WriteSequence();
    ResetPins();
}
void ClearLCD(void){
    WriteLCD(0x01, IS_COMMAND, NORMAL); //clear display  
    Delay5ms();
}
void LCDInit(void){
    /*sets data and control pins as outputs: */
    D4_DIRECTION = 0;
    D5_DIRECTION = 0;
    D6_DIRECTION = 0;
    D7_DIRECTION = 0;
    E_DIRECTION = 0;
    RS_DIRECTION = 0;
    /* make sure all data and control pins are zeroed: */
    ResetPins();    
    /* wakeup call: */
    __delay_ms(1000);
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x02, IS_COMMAND, HALF_BYTE); // initialize 4bit mode
    /* end of wakeup call */
    
    /* setup sequence */
    WriteLCD(0x28, IS_COMMAND, NORMAL); // 2 lines, 5x7 dots
    WriteLCD(0x08, IS_COMMAND, NORMAL); // display off
    WriteLCD(0x0C, IS_COMMAND, NORMAL); // display on, no cursor, no blink
    WriteLCD(0x06, IS_COMMAND, NORMAL); // entry mode: increment cursor, no shift
    /* end of setup sequence */
    ClearLCD();
}
void SelectRow(int line_number){
    /* moves cursor to beginning of the first or second row: */
    if (line_number) // select second row
        WriteLCD(0xC0, IS_COMMAND, NORMAL);
    else // select first row
        WriteLCD(0x02, IS_COMMAND, NORMAL);
    Delay5ms();
    
}
void DisplayText(char *text, int line_number){
    /* cycle through a string of characters and send
     each character to LCD */
    SelectRow(line_number);
    int x=0;
    while (text[x]!='\0' && x<16){
        WriteLCD(text[x], IS_DATA, NORMAL);
        ++x;
    }
}