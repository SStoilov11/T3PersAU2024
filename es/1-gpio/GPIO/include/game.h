#ifndef GAME_H
#define GAME_H

#include "stm32f303xe.h"
#include <stdlib.h>

uint32_t getPlayerInput(void);
void blinkLED(uint32_t);
void checkGameEnd(uint32_t);
void simeon_says_game(void);
void Delay(uint32_t time_ms);


#endif 