#include "init.h"

/*
PIN CONFIGURATION
Button0 - PA7
Button1 - PB10
LED0 - PB6
LED1 - PA8
*/
void INTERRUPT_Init(void){
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enable the system configuration controller clock

    //Configure SYSCFG_EXTICR2 to select port A pin 7
    SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI7_PA; // Select port A pin 7
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI7_PA;
    EXTI->RTSR |= EXTI_RTSR_TR7; // Set rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR7; // Enable interrupt request from line 7
    NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable EXTI4 interrupt

    //Configure SYSCFG_EXTICR3 to select port B pin 10
    SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI10_PB; // Select port B pin 10
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PB;
    EXTI->RTSR |= EXTI_RTSR_TR10; // Set rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR10; // Enable interrupt request from line 10
    NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable EXTI15_10 interrupt
    
}
void GPIOx_Init(void){
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //Enable GPIOA clock 
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //Enable GPIOB clock 
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //Enable GPIOC clock
 
    //Set PB6(LED0) as output
    GPIOB->MODER &= ~GPIO_MODER_MODER6; //Reset bits
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODER6_Pos; //Set bits for output mode
    //Set PA8(LED1) as output
    GPIOA->MODER &= ~GPIO_MODER_MODER8; //Reset bits
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODER8_Pos; //Set bits for output mode

    //Set PA7(B0) as input
    GPIOA->MODER &= ~GPIO_MODER_MODER7; //Reset bits
    //Set PB10(B1) as input
    GPIOB->MODER &= ~GPIO_MODER_MODER10; //Reset bits
    //Set PC13 as input
    GPIOC->MODER &= ~GPIO_MODER_MODER13; //Reset bits
    GPIOC->PUPDR |= 0b01 << GPIO_PUPDR_PUPDR13_Pos; //Enable the pull-up resistor
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

