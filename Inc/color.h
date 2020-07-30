#ifndef __COLOR_H
#define __COLOR_H
#include "main.h"
#include "gpio.h"
#include "car.h"
#include "lcd12864.h"
extern int Gray;
extern int g_flag;
extern float g_SF[3];
extern int g_count ;
extern int g_array[3];
void TSC_Init(void);
void TSC_FilterColor(int Level01,int Level02);
extern void TSC_Count(void);
void TSC_WB(int Level0,int Level1);
void TSC_Call(void);
int TCS3200_Distinguish(void);

#define TCS32_S0(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET)

#define TCS32_S1(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET)

#define TCS32_S2(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)
#define TCS32_S3(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)

#endif
