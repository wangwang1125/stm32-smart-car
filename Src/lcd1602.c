/*
        1602.C文件
	1602采用四线传输
*/
#include "lcd1602.h"

 
/* 检测液晶忙不忙 */

 
/*向1602写入一字节命令,cmd-待写入命令 */
//写入指令PA4-7 RS-0  RW-0
void LCD1602_Write_Cmd(u8 cmd)
{
//	LCD1602_Wait_Ready();  //判断忙不忙
	HAL_Delay(15);
	LCD_RS_Clr();   
	LCD_RW_Clr();
//	GPIO_Write(cmd);  //先传高四位
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,cmd&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,(cmd<<1)&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,(cmd<<2)&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,(cmd<<3)&0x80);
	HAL_Delay(1);
	LCD_EN_Set();
	HAL_Delay(5);
	LCD_EN_Clr();
	
//	GPIO_Write(cmd<<4); //低四位左移到高四位
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,cmd&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,(cmd<<1)&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,(cmd<<2)&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,(cmd<<3)&0x08);
	
	HAL_Delay(1);
	LCD_EN_Set();
	HAL_Delay(5);
	LCD_EN_Clr();
}
 
/* 向1602写入一字节数据*/
void LCD1602_Write_Dat(u8 dat)
{
	HAL_Delay(15);
	LCD_RS_Set();   //1
	LCD_RW_Clr();   //0
	
//	GPIO_Write(dat);   //先传高四位
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,dat&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,(dat<<1)&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,(dat<<2)&0x80);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,(dat<<3)&0x80);
	HAL_Delay(1);
	LCD_EN_Set();  
	HAL_Delay(5);
	LCD_EN_Clr();
	
//	GPIO_Write(dat<<4); //低四位左移到高四位
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,dat&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,(dat<<1)&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,(dat<<2)&0x08);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,(dat<<3)&0x08);
	HAL_Delay(1);
	LCD_EN_Set();
	HAL_Delay(5);	
	LCD_EN_Clr();
	
}
 
/*清屏*/
void LCD1602_ClearScreen(void)
{
	LCD1602_Write_Cmd(0x01);
	
}
 
/* 设置RAM其实地址,即光标位置,（X,Y）对应屏幕上的字符坐标 */
void LCD1602_Set_Cursor(u8 x, u8 y)
{
	u8 addr;
	
	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_Cmd(addr | 0x80);
}
 
/* 在液晶上显示字符串,（X,Y）-对应屏幕上的其实坐标，str-字符串指针 */
void LCD1602_Show_Str(u8 x, u8 y, u8 *str)
{
	LCD1602_Set_Cursor(x, y);
	while(*str != '\0')
	{
		LCD1602_Write_Dat(*str++);
	}
}
 
/* 初始化液晶 */
void LCD1602_Init(void)
{
	LCD1602_Write_Cmd(0x32);	 //将8位总线转为4位总线
	LCD1602_Write_Cmd(0x28);	//16*2显示，5*7点阵，4位数据口
	LCD1602_Write_Cmd(0x0C);	//开显示，光标关闭
	HAL_Delay(10);
	LCD1602_Write_Cmd(0x06);	//文字不动，地址自动+1
	HAL_Delay(10);
	LCD1602_Write_Cmd(0x01);	//清屏
}

void GPIO_Write(u8 cmd)
{
	for(int i=0;i<4;i++)
	{
		if((cmd<<i)&0x80)
			HAL_GPIO_WritePin(GPIOA,1<(i+1),GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOA,1<(i+1),GPIO_PIN_RESET);
	}

}
