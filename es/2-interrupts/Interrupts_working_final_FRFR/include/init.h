#ifndef INIT_H
#define INIT_H

#include "stm32f303xe.h"

void SystemClock_Config(void);
void GPIOx_Init(void);
void INTERRUPT_Init(void);

#endif