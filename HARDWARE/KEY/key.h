#ifndef __KEY_H
#define __KEY_H
#include "stm32f4xx.h"

#define KEY 	PBin(8)
 
/*定义需要的GPIO引脚,KEY1代表电路图中的引脚1，依此类推*/
#define KEY1_PORT 			GPIOF
#define KEY1_GPIO_Pin		GPIO_Pin_0
#define KEY1_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY2_PORT 			GPIOF
#define KEY2_GPIO_Pin		GPIO_Pin_1
#define KEY2_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY3_PORT 			GPIOF 
#define KEY3_GPIO_Pin		GPIO_Pin_2
#define KEY3_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY4_PORT 			GPIOF 
#define KEY4_GPIO_Pin		GPIO_Pin_3
#define KEY4_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY5_PORT 			GPIOF 
#define KEY5_GPIO_Pin		GPIO_Pin_4
#define KEY5_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY6_PORT 			GPIOF 
#define KEY6_GPIO_Pin		GPIO_Pin_5
#define KEY6_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY7_PORT 			GPIOF 
#define KEY7_GPIO_Pin		GPIO_Pin_6
#define KEY7_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY8_PORT 			GPIOF 
#define KEY8_GPIO_Pin		GPIO_Pin_7
#define KEY8_GPIO_CLK		RCC_AHB1Periph_GPIOF
 
#define KEY_ON 	1
#define KEY_OFF 0
 
/*所有按键的代码值*/
#define KS1_CODE	0x18
#define KS2_CODE	0x14
#define KS3_CODE	0x12
#define KS4_CODE	0x11
#define KS5_CODE	0x28
#define KS6_CODE	0x24
#define KS7_CODE	0x22
#define KS8_CODE	0x21
#define KS9_CODE	0x48
#define KS10_CODE	0x44
#define KS11_CODE	0x42
#define KS12_CODE	0x41
#define KS13_CODE	0x88
#define KS14_CODE	0x84
#define KS15_CODE	0x82
#define KS16_CODE	0x81

#define NUM7_KEY	KS1_CODE
#define NUM8_KEY	KS2_CODE
#define NUM9_KEY	KS3_CODE
#define BACK_KEY	KS4_CODE
#define NUM4_KEY	KS5_CODE
#define NUM5_KEY	KS6_CODE
#define NUM6_KEY	KS7_CODE
#define DEL_KEY		KS8_CODE
#define NUM1_KEY	KS9_CODE
#define NUM2_KEY	KS10_CODE
#define NUM3_KEY	KS11_CODE
#define UNIT_KEY	KS12_CODE
#define POINT_KEY	KS13_CODE
#define NUM0_KEY	KS14_CODE
#define ENTER_KEY	KS15_CODE
#define MODE_KEY	KS16_CODE
 
void KEY_Init(void);

void KEY1_4_GPIO_Input_Config(void);
void KEY5_8_GPIO_Input_Config(void);
void KEY1_4_GPIO_Output_Config(void);
void KEY5_8_GPIO_Output_Config(void);

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

void set_key1_4_Bits(void);
uint8_t read_key1_4_Bits(void);

void set_key5_8_Bits(void);
uint8_t read_key5_8_Bits(void);

#endif
