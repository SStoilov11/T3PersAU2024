#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "stm32f3xx.h"
#include <stdlib.h>

#define RED_PIN    3   // D3 -> PB3 (Red)
#define GREEN_PIN  5   // D5 -> PB4 (Green)
#define BLUE_PIN   4   // D4 -> PB5 (Blue)
#define BUTTON_PIN 13  // User button -> PC13

void SystemClock_Config(void);
void GPIOx_Init(void);

#endif