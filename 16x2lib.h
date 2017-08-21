#include <xc.h>

#define _XTAL_FREQ 20000000 /* clock speed in Hz */

/* define pins, which will be connected to LCD module.
 * If you change default values, please note, that you need to change
 * TRISxx also (for example if RS pin will be connected to RA2 pin,
 * configuration should look like this:
 * #define E RA2
 * #define E_DIRECTION TRISA2
 * 
 */
#define D4 RB0
#define D4_DIRECTION TRISB0

#define D5 RB1
#define D5_DIRECTION TRISB1

#define D6 RB2
#define D6_DIRECTION TRISB2

#define D7 RB3
#define D7_DIRECTION TRISB3

#define RS RB4
#define RS_DIRECTION TRISB4

#define E  RB5
#define E_DIRECTION TRISB5



/*Do not change values below*/
#define IS_COMMAND 0
#define IS_DATA 1
#define NORMAL 0
#define HALF_BYTE 1
#define FIRST_LINE 0 
#define SECOND_LINE 1

void LCDInit(void);
void DisplayText(char text[16], int line_number);
void ClearLCD(void);