/*
 * File:   16x2lib.c
 * Author: Tadas Ustinavičius
 *
  */



#include "16x2lib.h"

void Delay5ms(void){
    __delay_ms(5);
}
void ResetPins(void){
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    E = 0;
    RS = 0;    
}
void WriteSequence(void){
    E = 1;
    __delay_us(100);
    E = 0;
    __delay_us(100);
}
void WriteLCD(char value, int command_type, int single_pass){ 
    RS = command_type;
    if (!single_pass){
        /*emit 4 most significant bits to each of data pins: */
        D4 = (0x10 & value) >> 4;
        D5 = (0x20 & value) >> 5;
        D6 = (0x40 & value) >> 6;
        D7 = (0x80 & value) >> 7;
        WriteSequence();
    }
    /* emit 4 least significant bits to each of data pins:*/
    D4 = 0x01 & value;
    D5 = (0x02 & value) >> 1;
    D6 = (0x04 & value) >> 2;
    D7 = (0x08 & value) >> 3;
    WriteSequence();
    ResetPins();
}
void ClearLCD(void){
    WriteLCD(0x01, IS_COMMAND, NORMAL); //clear display  
    WriteLCD(0x00, IS_COMMAND, NORMAL);
    Delay5ms();
}
void LCDInit(void){
    D4_DIRECTION = 0;
    D5_DIRECTION = 0;
    D6_DIRECTION = 0;
    D7_DIRECTION = 0;
    E_DIRECTION = 0;
    RS_DIRECTION = 0;
    ResetPins();    
    /* wakeup call: */
    __delay_ms(1000);
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x03, IS_COMMAND, HALF_BYTE);
    Delay5ms();
    WriteLCD(0x02, IS_COMMAND, HALF_BYTE); //initialize 4bit mode
    /* end of wakeup call */
    WriteLCD(0x28, IS_COMMAND, NORMAL); //2 lines, 5x7 dots
    WriteLCD(0x08, IS_COMMAND, NORMAL); //display off
    WriteLCD(0x0C, IS_COMMAND, NORMAL); //display on, no cursor, no blink
    WriteLCD(0x06, IS_COMMAND, NORMAL); //entry mode: increment cursor, no shift
    ClearLCD();
}
void SelectLine(int line_number){
    if (line_number)
        WriteLCD(0xC0, IS_COMMAND, NORMAL);
    else
        WriteLCD(0x02, IS_COMMAND, NORMAL);
    Delay5ms();
    
}
void DisplayText(char *text, int line_number){
    SelectLine(line_number);
    int x=0;
    while (text[x]!='\0' && x<16){
        WriteLCD(text[x], IS_DATA, NORMAL);
        ++x;
    }
}