#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED�˿ڶ���
#define LED0 		PFout(9)
#define LED1 		PFout(10)
#define LED0_ON 	GPIO_SetBits(GPIOF, GPIO_Pin_9)
#define LED1_ON 	GPIO_SetBits(GPIOF, GPIO_Pin_10)
#define LED0_OFF 	GPIO_ResetBits(GPIOF, GPIO_Pin_9)
#define LED1_OFF 	GPIO_ResetBits(GPIOF, GPIO_Pin_10)

void LED_Init(void);//��ʼ��		 				    
#endif
