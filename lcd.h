#ifndef __1602A_H
#define __1602A_H

#include <stm32f10x.h>

#define LCD1_ADDRESS        0x4E
/*------------I2C DATA --> P0-P7 --> RS-RW-E-BL-P4-P5-P6-P7----------*/
#define RS_MASK							0x01
#define RW_MASK							0x02
#define EN_MASK 						0x04
#define BL_MASK							0x08
#define BF_MASK							0x08

#define CTRL_COMMAND_MODE		0x00
#define CTRL_DATA_MODE 			RS_MASK
#define CTRL_READ						RW_MASK
#define CTRL_WRITE					0x00
#define CTRL_BL_ON					BL_MASK
#define CTRL_BL_OFF					0x00
#define CTRL_BL_DEFAULT			BL_MASK
#define CTRL_EN							0x04


#define LCD_ROWS 						2
#define LCD_COLS						16

/*-------------DEFINE COMMANDS----------------------------------------*/
#define	LCD_CM_CLEAR								0x01

#define LCD_CM_RETURNHOME 					0x02  /*DDRAM AD=0, content changeless*/

#define LCD_CM_INPUTSET							0x04  /*set the moving direction of cursor*/
/*flags for INPUT SET*/
#define LCD_CM_INPUTSET_INCR				0x02
#define LCD_CM_INPUTSET_DECR				0x00
#define LCD_CM_INPUTSET_ENSHIFT			0x01
#define LCD_CM_INPUTSET_DISSHIFT		0x00
#define LCD_CM_INPUTSET_DEFAULT 		(LCD_CM_INPUTSET | LCD_CM_INPUTSET_INCR | LCD_CM_INPUTSET_DISSHIFT)

#define LCD_CM_DISPLAYSWITCH						0x08
/*flags for DISPHLAY SWITCH*/
#define LCD_CM_DISPLAYSWITCH_DISPON			0x04  /* DISPLAY ON*/
#define LCD_CM_DISPLAYSWITCH_CURSON			0x02  /* CURSOR ON*/
#define LCD_CM_DISPLAYSWITCH_BLINKON		0x01  /* BLINK ON*/
#define LCD_CM_DISPLAYSWITCH_DEFAULT		(LCD_CM_DISPLAYSWITCH | LCD_CM_DISPLAYSWITCH_DISPON)

#define LCD_CM_SHIFT							0x10
/*flags for SHIFT*/
#define LCD_CM_SHIFT_DISPLAY			0x08
#define LCD_CM_SHIFT_CURSOR				0x00
#define LCD_CM_SHIFT_RIGHT				0x40
#define LCD_CM_SHIFT_LEFT					0x00
#define LCD_CM_SHIFT_DEFAULT			(LCD_CM_SHIFT | LCD_CM_SHIFT_CURSOR | LCD_CM_SHIFT_RIGHT)

#define LCD_CM_FUNCTIONSET					0x20
/*flags for LCD_CM_FUNCTION SET*/
#define LCD_CM_FUNCTIONSET_8DL			0x10  /*Data length is 8*/
#define LCD_CM_FUNCTIONSET_4DL			0x00	/*Data length is 4*/
#define LCD_CM_FUNCTIONSET_2R				0x08	/*Number of display line is 2*/
#define LCD_CM_FUNCTIONSET_1R				0x00
#define LCD_CM_FUNCTIONSET_5x10			0x01	/*Display font type*/
#define LCD_CM_FUNCTIONSET_5x8			0x00
#define LCD_CM_FUNCTIONSET_DEFAULT	(LCD_CM_FUNCTIONSET | LCD_CM_FUNCTIONSET_4DL | LCD_CM_FUNCTIONSET_2R | LCD_CM_FUNCTIONSET_5x8)

#define LCD_CM_CGRAM_ADSET				0x40
#define LCD_CM_DDRAM_ADSET				0x80

/*--------------DEFINE BIT-LENGTH of DDRAM ADDRESS AND CGRAM ADDRESS---------*/
#define DDRAM_ADDR_LENGTH		7
#define CGRAM_ADDR_LENGTH		6

/*--------------FUNCTION-----------------------------------------------------*/
void LCD_1602A_WriteChar(uint8_t data, uint8_t mode);
void LCD_1602A_WriteString(char* string);
void LCD_1602A_SetCursor(uint8_t row, uint8_t col);
void LCD_1602A_Init(void);
void LCD_1602A_ClearScrean(void);

#endif
