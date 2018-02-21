#ifndef LCD__H_
#define LCD__H_
/***************************************************************************************************/
#include "lcdconfig.h"
/***************************************************************************************************/
//LCD gotoxy returns
#define LOCATION_NOT_FOUND			0
#define LOCATION_FOUND_AND_SET		1

#define NUMBER_OUT_LCD_BOUNDRIES	0

#define SUCCESS						1
/***************************************************************************************************/
//LCD LINES
#define LINE_1						0
#define LINE_2						1
//LCD Positions
#define POS_1						0
#define POS_2						1
#define POS_3						2
#define POS_4						3
#define POS_5						4
#define POS_6						5
#define POS_7						6
#define POS_8						7
#define POS_9						8
#define POS_10						9
#define POS_11						10
#define POS_12						11
#define POS_13						12
#define POS_14						13
#define POS_15						14
#define POS_16						15
/****************************************************************************************************/
//LCD instructions
#define LCD_CLEAR_DISPLAY			0x01          // replace all characters with ASCII 'space'
#define LCD_HOME					0x02          // return cursor to first position on first line
#define LCD_ENTRYMODE				0x06          // shift cursor from left to right on read/write
#define LCD_DISPLAYOFF				0x08          // turn display off
#define LCD_DISPLAYON				0x0C          // display on, cursor off, don't blink character
#define LCD_FUNCTION_RESET			0x30          // reset the LCD
#define LCD_FUNCTION_SET_4BIT		0x28          // 4-bit data, 2-line display, 5 x 7 font
#define LCD_SET_CURSOR				0x80          // set cursor position
#define LCD_SHOW_CURSOR				0x0F		  //show cursor position
/****************************************************************************************************/
//Function Prototypes
void vLCDWriteCharacter(char Data);
void vLCDWriteString(char *string);
void vLCDInit(void);
void vLCDClearDisplay(void);
char cLCDGotoXY(char pos, char line);
char cLCDShowInt(char x, char Y, uint32_t Num, char Len);
char cLCDShowFloat(char x_position, char y_position, float number, char decimal_Len, char fraction_len);
 
#endif   /*__LCD__H_*/