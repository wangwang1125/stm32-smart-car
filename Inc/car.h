#ifndef __CAR_H_
#define __CAR_H_
#include "main.h"
#include "gpio.h"
#include "tim.h"
 
//

#define	L_S1	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET)
#define	L_R1	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET)
 
//
#define	L_S2	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET)
#define	L_R2	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)
 
//

#define	L_S3	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET)
#define	L_R3	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET)
 
//
#define	L_S4	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)
#define	L_R4	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET)


 
void go(void);
void right(void);
void left(void);
void car(void);
void stop();
void color_judge(int color);
void color_end(int color);
void car_back(void);
#endif
