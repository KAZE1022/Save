#include "IC.h"                  // Device header

void IC_Init(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//想用定时器的方式来控制引脚则用复用推挽输出的方式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//定时频率（CK_CNT_OV）=72M(CK_PSC)/(PSC+1)/(ARR+1)
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//ARR（自动重装）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//PSC(预分频)
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器才有目前通用定时器没有则赋值为0使其不工作
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	/*19行函数在单片机上电时会直接进入一次中断，以至于在实验中Num显示的时候是从1开始而不是0
		解决方案有两种，第一是比较直接但不能解决根本直接让Num显示时减1，
						第二是系统解决，在执行完TIM_TimeBaseInit函数后直接进行手动清除标志位的操作及在此后加入TIM_ClearFlag(TIMx, TIM_FLAG);
						手动清除使得在后面的中断为第一次执行中断。
	*/

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE); 
}

uint32_t IC_GetFreq(void){
	return 1000000 / (TIM_GetCapture1(TIM3)+1);
}
