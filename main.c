#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "LED.h"
#include "Buzzer.h"
#include "Key.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Delay.h"
#include "Serial.h"

#define Limite_Page_Up 5 //限幅最大页
#define SetPage Limite_Page_Up-3      //设置功能在限幅倒数第二页进行设置功能
#define SetPageData Limite_Page_Up-2 // 设置的参数在限幅的最后一页显示设置数据
#define Auto_Page Limite_Page_Up-1

int8_t KeyNum,SetKey=0,Reset_Data;
int8_t Page;
int16_t Set_Num_Up,Set_Num_Down;
int i;

unsigned char RxData[8]={'R','U','N','I','N','G','!','!'};
uint8_t Serial_RxData;

unsigned char Woring[8]={'R','U','N','I','N','G','!','!'};
unsigned char Cover[8]={1,' ','C','O','V','E','R','!'};


struct MPU6050
{
    int16_t AX;
    int16_t AY;
    int16_t AZ;
    
    int16_t GX;
    int16_t GY;
    int16_t GZ;
    
    
}MPU;


void Choose_Page()//按键选择页码
{

 KeyNum = Get_KeyNum();
     if(KeyNum == 1)
      {
         Page++;
         OLED_Clear();
            if(Page>Limite_Page_Up-1)
            {   
                 Page = 0;     
                 OLED_Clear();
            }
      }
       if(KeyNum == 2)
        {
             Page--;
             OLED_Clear();
                if(Page <0)
                {
                     Page = Limite_Page_Up-1; 
                     OLED_Clear();
                }
        }
    
}

void Meal_1()//显示及速度
{
        OLED_ShowString(1,5,"Page One");
         OLED_ShowString(2,1,"AX:");
         OLED_ShowString(3,1,"AY:");
         OLED_ShowString(4,1,"AZ:");
         OLED_ShowSignedNum(2,4,MPU.AX,5);
         OLED_ShowSignedNum(3,4,MPU.AY,5);
         OLED_ShowSignedNum(4,4,MPU.AZ,5); 
}
void Meal_2()//显示角度
{
        OLED_ShowString(1,5,"Page Tow");
        OLED_ShowString(2,1,"GX:");
        OLED_ShowString(3,1,"GY:");
        OLED_ShowString(4,1,"GZ:");
        OLED_ShowSignedNum(2,4,MPU.GX,5);
        OLED_ShowSignedNum(3,4,MPU.GY,5);
        OLED_ShowSignedNum(4,4,MPU.GZ,5); 
}

void Set_Page()
{
        OLED_ShowString(1,1,"please set Groy!");
        OLED_ShowString(2,1,"please change");
        SetKey = Get_KeyNum();
        if(SetKey == 3)
        {
            OLED_ShowString(2,1,"                ");
            OLED_ShowString(3,1,"                ");
            OLED_ShowString(4,1,"                ");
            MPU6050_GetData(&MPU.AX,&MPU.AY,&MPU.AZ,&MPU.GX,&MPU.GY,&MPU.GZ);
            OLED_ShowString(2,1,"AX:");
            OLED_ShowString(3,1,"STE:");
            OLED_ShowNum(2,4,MPU.AX,5);
            Delay_ms(500);
            Set_Num_Up = MPU.AX;
            Delay_ms(500);
            OLED_ShowNum(3,5,Set_Num_Up,5);
            Delay_ms(500);
            OLED_Clear();
            OLED_ShowString(1,1,"Wait");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(1,5,".");
            Delay_ms(500);
            OLED_ShowString(1,5,"..");
                Delay_ms(500);
            OLED_ShowString(1,5,"...");
                Delay_ms(500);
            OLED_ShowString(1,5,"   ");
                Delay_ms(500);
            }
            OLED_ShowString(2,1,"Seting");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(2,7,".");
            Delay_ms(500);  
            OLED_ShowString(2,7,"..");
            Delay_ms(500);  
            OLED_ShowString(2,7,"...");
            Delay_ms(500);  
            OLED_ShowString(2,7,"   ");
            Delay_ms(500);
            }
            OLED_Clear();
            OLED_ShowString(2,1,"STEN:");
            OLED_ShowNum(2,6,Set_Num_Up,5);
            OLED_ShowString(3,1,"2 Countine");
            OLED_ShowString(4,1,"3 RESET");
        }
        if(SetKey == 2){
            OLED_ShowString(2,1,"                ");
            OLED_ShowString(3,1,"                ");
            OLED_ShowString(4,1,"                ");
            MPU6050_GetData(&MPU.AX,&MPU.AY,&MPU.AZ,&MPU.GX,&MPU.GY,&MPU.GZ);
            OLED_ShowString(2,1,"AX:");
            OLED_ShowString(3,1,"STE:");
            OLED_ShowNum(2,4,MPU.AX,5);
            Delay_ms(500);
            Set_Num_Down = MPU.AX;
            Delay_ms(500);
            OLED_ShowNum(3,5,Set_Num_Down,5);
            Delay_ms(500);
            OLED_Clear();
       OLED_ShowString(1,1,"Wait");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(1,5,".");
            Delay_ms(500);
            OLED_ShowString(1,5,"..");
                Delay_ms(500);
            OLED_ShowString(1,5,"...");
                Delay_ms(500);
            OLED_ShowString(1,5,"   ");
                Delay_ms(500);
            }
       OLED_ShowString(2,1,"Seting");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(2,7,".");
            Delay_ms(500);  
            OLED_ShowString(2,7,"..");
            Delay_ms(500);  
            OLED_ShowString(2,7,"...");
            Delay_ms(500);  
            OLED_ShowString(2,7,"   ");
            Delay_ms(500);
            }
            OLED_Clear();
            OLED_ShowString(1,1,"STEN:");
            OLED_ShowNum(1,6,Set_Num_Down,5);
            OLED_ShowString(2,1,"1 EXIT");
            OLED_ShowString(3,1,"3 RESET");
        }
        if(SetKey == 1)
         {
            OLED_Clear();
            OLED_ShowString(1,1,"SET COMPLETE!!!");
            Delay_s(1);
            Page++;
            OLED_Clear();
         }
}


void Set_PageData()
{
        OLED_ShowString(1,1,"U:");
        OLED_ShowNum(1,3,Set_Num_Up,5);
        OLED_ShowString(2,1,"D:");
        OLED_ShowNum(2,3,Set_Num_Down,5);
        OLED_ShowString(3,1,"2 RESET");
        OLED_ShowString(4,1,"1 Next Page");
        Reset_Data = KeyNum;
        if(Reset_Data == 2)
        {
            Page --;
        }
        if(Reset_Data == 1)
        {
            Page ++;
        }
}

void Auto_Mode()
{
        OLED_Clear();
        OLED_ShowString(1,1,"normal operation");
        if(MPU.AX>Set_Num_Up ||MPU.AX<Set_Num_Down) //如果高于或低于设置的倾斜角开始预警
        {
            OLED_ShowString(2,1,"Woring!!");
            Buzzer_Groy10();                        //蜂鸣器工作
            OLED_ShowString(3,1,"Sending");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(3,7,".");
            Delay_ms(50);
            OLED_ShowString(3,7,"..");
            Delay_ms(50);
            OLED_ShowString(3,7,"...");
            Delay_ms(50);
            OLED_ShowString(3,7,"   ");
            Delay_ms(50);
            }
           Serial_SendArray(Woring,8);
            Delay_ms(500);
        }
        if(MPU.AX - Set_Num_Up >100||MPU.AX - Set_Num_Down <100
            )//||MPU.AX - Set_Num_Up <100||MPU.AX - Set_Num_Down >100
        {
            OLED_Clear();
            OLED_ShowString(1,1,"normal operation");
            OLED_ShowString(2,1,"Cover the body");
            Buzzer_Groy10();                      //蜂鸣器工作
            OLED_ShowString(3,1,"Sending");
            for(i=0;i<2;i++)
            {
            OLED_ShowString(3,7,".");
            Delay_ms(50);
            OLED_ShowString(3,7,"..");
            Delay_ms(50);
            OLED_ShowString(3,7,"...");
            Delay_ms(50);
            OLED_ShowString(3,7,"   ");
            Delay_ms(50);
            }
            Serial_SendArray(&Cover[0],8);
            Delay_ms(500);
        }
}
    

int main()//Smog模块监测天然气，光照，温度传感器
{
    Key_Init();
    OLED_Init();
    MPU6050_Init();
    Serial_Init();
    
	while(1)
	{
        Choose_Page();
        MPU6050_GetData(&MPU.AX,&MPU.AY,&MPU.AZ,&MPU.GX,&MPU.GY,&MPU.GZ);
        if(Page == 0)
       {  
           Meal_1();
        }
        if(Page == 1)
        {
            Meal_2();
        } 
        if(Page == SetPage)
        {
            Set_Page();
        }
        if(Page == SetPageData)
         {
           Set_PageData();
         }
     
         if(KeyNum == 4)
        {
            Page = Auto_Page;
            
        }
        if(Page == Auto_Page)
        {
             MPU6050_GetData(&MPU.AX,&MPU.AY,&MPU.AZ,&MPU.GX,&MPU.GY,&MPU.GZ);
             Auto_Mode();
            if(KeyNum == 1)
            {
                OLED_Clear();
                Page =0;
            }
        }
        if(Page == 1)
        {
            OLED_Clear();
        }
     
    }return 0;
    
}


