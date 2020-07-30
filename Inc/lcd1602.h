#ifndef __LCD1602_H_
#define __LCD1602_H_
#include "main.h"
#include "gpio.h"
 
//1602指令/数据 引脚

#define	LCD_RS_Set()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)
#define	LCD_RS_Clr()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)
 
//1602读写引脚
#define	LCD_RW_Set()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)
#define	LCD_RW_Clr()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)
 
//1602使能引脚
#define	LCD_EN_Set()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET)
#define	LCD_EN_Clr()	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET)
 
//1602数据端口	PD4~7

 
#define u8  unsigned char 
 

void GPIO_Configuration(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

void GPIO_Write(u8 cmd);
#endif
