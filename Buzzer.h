#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer_Groy10(void);

#endif


