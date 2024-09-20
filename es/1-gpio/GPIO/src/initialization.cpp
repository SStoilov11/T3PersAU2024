#include "initialization.h"

void GPIOx_Init(void)
{
    // Enable GPIOB and GPIOC clocks
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

    // Configure PB3 (RedLED) as output
    GPIOB->MODER &= ~GPIO_MODER_MODER3;   // Reset mode bits for PB3
    GPIOB->MODER |= (0b01 << GPIO_MODER_MODER3_Pos); // Set PB3 as output

    // Configure PB4 (GreenLED) as output
    GPIOB->MODER &= ~GPIO_MODER_MODER4;   // Reset mode bits for PB4
    GPIOB->MODER |= (0b01 << GPIO_MODER_MODER4_Pos); // Set PB4 as output

    // Configure PB5 (BlueLED) as output
    GPIOB->MODER &= ~GPIO_MODER_MODER5;   // Reset mode bits for PB5
    GPIOB->MODER |= (GPIO_MODER_MODER5_0); // Set PB5 as output

    // Configure PC13 as input (Button) with pull-down resistor
    GPIOC->MODER &= ~GPIO_MODER_MODER13;  // Set PC13 as input
    GPIOC->PUPDR |= (0b01 << GPIO_PUPDR_PUPDR13_Pos); // Pull-down for Button
}   


// Configure the system clock to 72 MHz. This means the APB1 peripheral clock and also the USART2 will be clocked at 36 MHz.
void SystemClock_Config(void)
{
    // Configure Flash latency for 48 < HCLK ≤ 72 MHz, see datasheet. Do this before setting the system clock to 72 MHz.
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // Enable the HSI (internal high-speed) oscillator
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY))
        ; // Wait until HSI is ready

    // Set the APB1 prescaler to 2
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Set the PLL SRC to HSI and PREDIV to /1
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;

    // Set PLL multiplier to 9 (8 MHz * 9 = 72 MHz)
    RCC->CFGR &= ~RCC_CFGR_PLLMUL;
    RCC->CFGR |= RCC_CFGR_PLLMUL9;

    // Enable the PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ; // Wait until PLL is ready

    // Select PLL as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ; // Wait until PLL becomes the system clock

    // Update the system core clock variable
    SystemCoreClockUpdate();
}
