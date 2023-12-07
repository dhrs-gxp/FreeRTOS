#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA,GPIOE时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //KEY0 KEY1 KEY2对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
} 


void KEY1_4_GPIO_Input_Config(void)
{
	GPIO_InitTypeDef Init_Structure;
    RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK
    |KEY3_GPIO_CLK|KEY4_GPIO_CLK,ENABLE);
	
	Init_Structure.GPIO_Mode = GPIO_Mode_IN;
	Init_Structure.GPIO_PuPd = GPIO_PuPd_DOWN;	//这里务必设置成下拉模式
	
	Init_Structure.GPIO_Pin = KEY1_GPIO_Pin;
	GPIO_Init(KEY1_PORT,&Init_Structure);
	
	Init_Structure.GPIO_Pin = KEY2_GPIO_Pin;
	GPIO_Init(KEY2_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY3_GPIO_Pin;
	GPIO_Init(KEY3_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY4_GPIO_Pin;
	GPIO_Init(KEY4_PORT,&Init_Structure);
}
 
void KEY5_8_GPIO_Input_Config(void)
{
	GPIO_InitTypeDef Init_Structure;
	RCC_AHB1PeriphClockCmd(KEY5_GPIO_CLK|KEY6_GPIO_CLK
	|KEY7_GPIO_CLK|KEY8_GPIO_CLK,ENABLE);
	
	Init_Structure.GPIO_Mode = GPIO_Mode_IN;
	Init_Structure.GPIO_PuPd = GPIO_PuPd_DOWN; //这里务必设置成下拉模式
 
	Init_Structure.GPIO_Pin = KEY5_GPIO_Pin;
	GPIO_Init(KEY5_PORT,&Init_Structure);
	
	Init_Structure.GPIO_Pin = KEY6_GPIO_Pin;
	GPIO_Init(KEY6_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY7_GPIO_Pin;
	GPIO_Init(KEY7_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY8_GPIO_Pin;
	GPIO_Init(KEY8_PORT,&Init_Structure);
}
 
void KEY1_4_GPIO_Output_Config(void)
{
	GPIO_InitTypeDef Init_Structure;
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK
	|KEY3_GPIO_CLK|KEY4_GPIO_CLK,ENABLE);
	
	Init_Structure.GPIO_Mode = GPIO_Mode_OUT;
	Init_Structure.GPIO_OType = GPIO_OType_PP;
	Init_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	Init_Structure.GPIO_Speed = GPIO_Speed_25MHz;
	
	Init_Structure.GPIO_Pin = KEY1_GPIO_Pin;
	GPIO_Init(KEY1_PORT,&Init_Structure);
	
	Init_Structure.GPIO_Pin = KEY2_GPIO_Pin;
	GPIO_Init(KEY2_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY3_GPIO_Pin;
	GPIO_Init(KEY3_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY4_GPIO_Pin;
	GPIO_Init(KEY4_PORT,&Init_Structure);
}
 
void KEY5_8_GPIO_Output_Config(void)
{
	GPIO_InitTypeDef Init_Structure;
	RCC_AHB1PeriphClockCmd(KEY5_GPIO_CLK|KEY6_GPIO_CLK
	|KEY7_GPIO_CLK|KEY8_GPIO_CLK,ENABLE);
	
	Init_Structure.GPIO_Mode = GPIO_Mode_OUT;
	Init_Structure.GPIO_OType = GPIO_OType_PP;
	Init_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	Init_Structure.GPIO_Speed = GPIO_Speed_25MHz;
	
	Init_Structure.GPIO_Pin = KEY5_GPIO_Pin;
	GPIO_Init(KEY5_PORT,&Init_Structure);
	
	Init_Structure.GPIO_Pin = KEY6_GPIO_Pin;
	GPIO_Init(KEY6_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY7_GPIO_Pin;
	GPIO_Init(KEY7_PORT,&Init_Structure);
 
	Init_Structure.GPIO_Pin = KEY8_GPIO_Pin;
	GPIO_Init(KEY8_PORT,&Init_Structure);
}
 
/**
  * @brief 读取KEY的GPIO引脚状态（这个函数这里没用到，但为了保持完整性还是贴出来）
  * @param GPIO,Pin
  * @retval 引脚状态
  */
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)== KEY_ON)
	{
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)== KEY_ON)
			return KEY_ON;
	}
	return KEY_OFF;
}
/**
  * @brief 给1234引脚置高电平
  * @param void
  * @retval void
  */
void set_key1_4_Bits(void)
{
	GPIO_SetBits(KEY1_PORT,KEY1_GPIO_Pin);
	GPIO_SetBits(KEY2_PORT,KEY2_GPIO_Pin);
	GPIO_SetBits(KEY3_PORT,KEY3_GPIO_Pin);
	GPIO_SetBits(KEY4_PORT,KEY4_GPIO_Pin);
}
 
/**
  * @brief 读取1234引脚电平并存到temp低四位
  * @param void
  * @retval 返回4个引脚电平状态
  */
u8 read_key1_4_Bits(void)
{
	u8 k1=0,k2=0,k3=0,k4=0,temp = 0;
	k1 = GPIO_ReadInputDataBit(KEY1_PORT,KEY1_GPIO_Pin);
	temp |= k1;
	
	k2 = GPIO_ReadInputDataBit(KEY2_PORT,KEY2_GPIO_Pin);
	k2<<=1;
	temp |= k2;
	
	k3 = GPIO_ReadInputDataBit(KEY3_PORT,KEY3_GPIO_Pin);
	k3<<=2;
	temp |= k3;
	
	k4 = GPIO_ReadInputDataBit(KEY4_PORT,KEY4_GPIO_Pin);
	k4<<=3;
	temp |= k4;
	return temp;
}
 
/**
  * @brief 给5678引脚置高电平
  * @param void
  * @retval void
  */
void set_key5_8_Bits(void)
{
	GPIO_SetBits(KEY5_PORT,KEY5_GPIO_Pin);
	GPIO_SetBits(KEY6_PORT,KEY6_GPIO_Pin);
	GPIO_SetBits(KEY7_PORT,KEY7_GPIO_Pin);
	GPIO_SetBits(KEY8_PORT,KEY8_GPIO_Pin);
}
 
/**
  * @brief 读取5678引脚电平并存到temp高四位
  * @param void
  * @retval 返回4个引脚电平状态
  */
u8 read_key5_8_Bits(void)
{
	u8 k5=0,k6=0,k7=0,k8=0,temp = 0;
	k5 = GPIO_ReadInputDataBit(KEY5_PORT,KEY5_GPIO_Pin);
	k5<<=4;
	temp |= k5;
	
	k6 = GPIO_ReadInputDataBit(KEY6_PORT,KEY6_GPIO_Pin);
	k6<<=5;
	temp |= k6;
	
	k7 = GPIO_ReadInputDataBit(KEY7_PORT,KEY7_GPIO_Pin);
	k7<<=6;
	temp |= k7;
	
	k8 = GPIO_ReadInputDataBit(KEY8_PORT,KEY8_GPIO_Pin);
	k8<<=7;
	temp |= k8;
	
	return temp;
}
