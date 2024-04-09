#include "Buzzer.h"


void Buzzer_Init(void){
    
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_1);
    
}

void Buzzer_ON(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}

void Buzzer_OFF(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

void Buzzer_Groy10(void)
{
    int i;
    for(i=0;i<5;i++)
    {
        Buzzer_ON();
        Delay_ms(5);
        Buzzer_OFF();
        Delay_ms(3);
        Buzzer_ON();
        Delay_ms(1);
        Buzzer_OFF();
        Delay_ms(1);
        Buzzer_ON();
        Delay_ms(10);
    }

}



