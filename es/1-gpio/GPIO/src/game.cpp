#include "game.h"
#include "initialization.h"

// Function to count button presses
uint32_t getPlayerInput(void)
{
    uint32_t pressCount = 0;
    uint32_t timeLimit = 5000;  // 5 seconds time window for input
    uint32_t elapsedTime = 0;

    while (elapsedTime < timeLimit)
    {
        // Check if button is pressed (PC13 pulled low)
        if ((GPIOC->IDR & (1 << BUTTON_PIN)) == 0)
        {
            pressCount++;
            while ((GPIOC->IDR & (1 << BUTTON_PIN)) == 0);  // Wait for release
            Delay(100);  // Debounce delay
        }
        Delay(1);  // Increment elapsed time
        elapsedTime++;
    }

    return pressCount;
}

// Simple delay function, should not be used in serious applications.
    void Delay(uint32_t time_ms)
    {
        volatile uint32_t i, j;

        for (i = 0; i < time_ms; i++)
            for (j = 0; j < 2000; j++)
                ; // Adjust this loop for shorter or longer delays
    }


void blinkLED(uint32_t blinkCount){

        // Blink all three colors for the sequence
        for (uint32_t i = 0; i < blinkCount; i++)
        {
            GPIOB->ODR |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN);  // Turn on RGB LED (all colors)
            Delay(500);
            GPIOB->ODR &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN));  // Turn off RGB LED
            Delay(500);
        }
}

void checkGameEnd(uint32_t blinkCount){

    // Get player input (button presses)
        uint32_t playerInput = getPlayerInput();

        // Check if player input matches blink count
        if (playerInput == blinkCount)
        {
            // Player wins, light up Green (D5)
            GPIOB->ODR |= (1 << GREEN_PIN);  // Turn on Green LED
            Delay(2000);                     // Keep it lit for 2 seconds
            GPIOB->ODR &= ~(1 << GREEN_PIN); // Turn off Green LED
        }
        else
        {
            // Player loses, light up Red (D3)
            GPIOB->ODR |= (1 << RED_PIN);    // Turn on Red LED
            Delay(2000);                     // Keep it lit for 2 seconds
            GPIOB->ODR &= ~(1 << RED_PIN);   // Turn off Red LED
        }
}

void simeon_says_game(){
    // Blocking delay between First and every other round
    Delay(2000);

    // Generate a random number (1-5) of LED blinks
    uint32_t blinkCount = (rand() % 5) + 1;

    // Call the blinkLED function to begin the light sequence
    blinkLED(blinkCount);

    // Call the checkGameEnd function to check the Win/Lose conditions
    checkGameEnd(blinkCount);
}