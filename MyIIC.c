#include "MyIIc.h"

void MyIIC_W_SCL(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

void MyIIC_W_SDA(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyIIC_R_SDA(void){
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}

void MyIIC_Init(void){
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
	//置高电平释放总线，使得SCL与SDA都是高电平则此时IIC为空闲状态
}

void MyIIC_Start(void){
	
	MyIIC_W_SDA(1);	//先拉高确保显示保证IIC协议的时钟线保持在高电位使得下一次拉低操作时由电压差
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(0);//先释放SDA是因为在重复启动时确保SDA是在高电平状态下
}

void MyIIC_Stop(void){
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(1);	
}

void MyIIC_SendByte(uint8_t Byte){
	
	uint8_t i;
	for(i=0;i<8;i++){
	MyIIC_W_SDA(Byte & 0x80>>i);//去除数据的最高位 
	MyIIC_W_SCL(1);//释放SCL从机读取写入的数据
	MyIIC_W_SCL(0);//拉低SCL再次发送下一位数据
	}
	
}

uint8_t MyIIC_ReceiveByte(void){
	uint8_t i,Byte = 0x00;
	MyIIC_W_SDA(1);	
	for(i =0;i<8;i++){
	MyIIC_W_SCL(1);
	if(MyIIC_R_SDA() == 1)
		Byte |= (0x80>>i); 
	MyIIC_W_SCL(0);
	}
	return Byte;
}


void MyIIC_SendAck(uint8_t AckBit){
	
	MyIIC_W_SDA(AckBit & 0x80);//去除数据的最高位 
	MyIIC_W_SCL(1);//释放SCL从机读取写入的数据
	MyIIC_W_SCL(0);//拉低SCL再次发送下一位数据

}

uint8_t MyIIC_ReceiveAck(void){
	uint8_t AckBit ;
	MyIIC_W_SDA(1);	
	MyIIC_W_SCL(1);
	AckBit = MyIIC_R_SDA();
	MyIIC_W_SCL(0);
	return AckBit;
}






