#include "LED.h"

void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

void LED_ON(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
void LED_OFF(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}



