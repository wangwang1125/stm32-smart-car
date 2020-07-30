#ifndef __LCD12864_H
#define __LCD12864_H

#include "main.h"

void LCD_Send_Byte(uint8_t data);
void LCD_Write_Com(uint8_t cmd);
void LCD_Init(void);
void LCD_Write_Byte(uint8_t dat);
void send_text(char *s);
void LCD_display1(void);
void display(float x,float y,float ange);
void LCD12864_DlyMs(unsigned char  n_ms);

#endif
