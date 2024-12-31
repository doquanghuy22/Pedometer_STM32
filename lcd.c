#include "lcd.h"
#include "stm32f10x_i2c.h"
#include "systick.h"
#include "i2c.h"
#include <stm32f10x.h>

void LCD_1602A_WriteChar(uint8_t data, uint8_t mode) {
    uint8_t Data_H;
    uint8_t Data_L;
    
    Data_H = data & 0xF0;
    Data_L = (data<<4) & 0xF0;
    Data_H |= CTRL_BL_DEFAULT | mode; 
    Data_L |= CTRL_BL_DEFAULT | mode; 
    
    Data_H |= CTRL_EN;
    I2C_Write(LCD1_ADDRESS, Data_H);
    Data_H &= ~CTRL_EN;
    I2C_Write(LCD1_ADDRESS, Data_H);
    Data_L |= CTRL_EN;
    I2C_Write(LCD1_ADDRESS, Data_L);
    Data_L &= ~CTRL_EN;
    I2C_Write(LCD1_ADDRESS, Data_L);
}

void LCD_1602A_WriteString(char* string) {
    while(*string) LCD_1602A_WriteChar(*string++, CTRL_DATA_MODE);
}

void LCD_1602A_SetCursor(uint8_t row, uint8_t col) {
		uint8_t ddram_addr;
    if(row >= LCD_ROWS || col >= LCD_COLS) {
        return;
    }
    
    /* Khai báo bi?n tru?c khi s? d?ng */
    ddram_addr = row * 0x40 + col;
    
    LCD_1602A_WriteChar(LCD_CM_DDRAM_ADSET|ddram_addr, CTRL_COMMAND_MODE);
    hal_delay(1);
}

void LCD_1602A_Init(void) {        
    /* Kh?i t?o màn hình LCD */
    hal_delay(16);
    LCD_1602A_WriteChar(0x30, CTRL_COMMAND_MODE);
    hal_delay(5);
    LCD_1602A_WriteChar(0x30, CTRL_COMMAND_MODE);
    hal_delay(1);
    LCD_1602A_WriteChar(0x32, CTRL_COMMAND_MODE);
    LCD_1602A_WriteChar(0x20, CTRL_COMMAND_MODE);

    LCD_1602A_WriteChar(LCD_CM_FUNCTIONSET_DEFAULT, CTRL_COMMAND_MODE);
    /*LCD_1602A_WriteChar(lcd, 0x80, CTRL_COMMAND_MODE); // display off*/
    LCD_1602A_WriteChar(LCD_CM_INPUTSET_DEFAULT, CTRL_COMMAND_MODE); /* 4DL, 2N, 5x8s */
    LCD_1602A_WriteChar(LCD_CM_DISPLAYSWITCH_DEFAULT, CTRL_COMMAND_MODE); /* display on, no cursor, no blink */
    LCD_1602A_WriteChar(LCD_CM_CLEAR, CTRL_COMMAND_MODE); /* display clear */
    hal_delay(2); /* c?n kho?ng 1.64s d? xóa màn hình */
}

void LCD_1602A_ClearScrean(void) {
    LCD_1602A_WriteChar(LCD_CM_CLEAR, CTRL_COMMAND_MODE);
    hal_delay(2); /* c?n kho?ng 1.64s d? xóa màn hình */
}
