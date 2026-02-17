/* lcd_i2c.h */
#ifndef LCD_I2C_H
#define LCD_I2C_H
#include "main.h"
#define SLAVE_ADDRESS_LCD 0x4E // 0x27 << 1
void LCD_Init(void);
void LCD_Send_Cmd(char cmd);
void LCD_Send_Data(char data);
void LCD_Send_String(char *str);
void LCD_Clear(void);
#endif
