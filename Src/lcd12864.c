#include "lcd12864.h"
#define CS_L HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//GPIOA->BSRRL = GPIO_Pin_4;
#define CS_H HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//GPIOA->BSRRH = GPIO_Pin_4;

#define RW_L HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);//GPIOA->BSRRL = GPIO_Pin_5;
#define RW_H HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);//GPIOA->BSRRH = GPIO_Pin_5;

#define E_L HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);//GPIOA->BSRRL = GPIO_Pin_7;
#define E_H HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);//GPIOA->BSRRH = GPIO_Pin_7;



extern int32_t new_dis_1;
extern int32_t new_dis_2;
//PA4 CS , PA5 R/W , PA7 E
void Delay_us(__IO unsigned int nCount) //这里只是粗略的延时
{
	for(; nCount != 0; nCount--);
}
void LCD12864_DlyMs(unsigned char  n_ms)
{
    unsigned short i=15000;
    while(n_ms--)
        while(i--);
}
void LCD_Send_Byte(uint8_t dat)
{
	uint8_t i;
	CS_L;
	for(i=0;i<8;i++)
	{
		E_H;
		if((dat<<i)&0x80) 
		{	
			RW_L;
		}
		else 
		{
			RW_H;
		}
		
		E_L;
	}
	CS_H
	HAL_Delay(2);
}
// H 0,L 1
void LCD_Write_Com(uint8_t cmd)
{
	CS_L;
	LCD_Send_Byte(0xf8);           //?μ?÷ê?è??üá?
	LCD_Send_Byte(cmd&0xf0);
	LCD_Send_Byte((cmd<<4)&0xf0);
	CS_H
}

void LCD_Write_Byte(uint8_t dat)
{
	CS_L;
	LCD_Send_Byte(0xfa);          //ê?è?êy?Y ￡? ?°????11111￡?rw 0￡?rs 1
	LCD_Send_Byte(dat&0xf0);
	LCD_Send_Byte((dat<<4)&0xf0);
	CS_H
}

void LCD_Init()
{
	
	LCD_Write_Com(0x30);     //?ù±?2ù×÷??á?
	LCD_Write_Com(0x0c);     //??ê??a￡?1?1a±ê
	LCD_Write_Com(0x10);	 //éè??μ??·00H
	LCD_Write_Com(0x06);	 //ó?±êóòò?ò???
	LCD_Write_Com(0x01);	 //??3yòo?§??ê??úèY
}
void send_text(char *s)
{
	while(*s !='\0')
	{
		LCD_Write_Byte(*s);
		s++;
	}
}


