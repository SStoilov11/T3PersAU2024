#include "stm32f303xe.h"
#include <stdlib.h>
#include "initialization.h"
#include "game.h"
//Simeon Says Game

int main(void)
{
    // Initialize system
    SystemClock_Config();
    GPIOx_Init();

    while (1)
    {
        // Start the game
        simeon_says_game();
    }
}

