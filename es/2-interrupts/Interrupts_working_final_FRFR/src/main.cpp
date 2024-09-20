#include "init.h"

extern "C" void EXTI9_5_IRQHandler(void)
{
    // Reset interrupt flag
    EXTI->PR = EXTI_PR_PR7;  

    // Toggle the LED
    GPIOA->ODR ^= GPIO_ODR_8;
}

extern "C" void EXTI15_10_IRQHandler(void)
{
    
    // Reset interrupt flag
    EXTI->PR = EXTI_PR_PR10;  

    // Toggle the LED
    GPIOB->ODR ^= GPIO_ODR_6;
}

int main(void){
    GPIOx_Init();
    SystemClock_Config();
    INTERRUPT_Init();
    while(1){
        // if ((GPIOA->IDR & (GPIO_IDR_7))){
        //     GPIOA->ODR |= (GPIO_ODR_8);
        // } else {
        //     GPIOA->ODR &= ~(GPIO_ODR_8);
        // }

        // if ((GPIOB->IDR & (GPIO_IDR_10))){
        //     GPIOB->ODR |= (GPIO_ODR_6);
        // } else {
        //     GPIOB->ODR &= ~(GPIO_ODR_6);
        // }

        // if(!(GPIOC->IDR & GPIO_IDR_13)){
        //     GPIOA->ODR |= (GPIO_ODR_8);
        //     GPIOB->ODR |= (GPIO_ODR_6);
        // } else {
        //     GPIOA->ODR &= ~(GPIO_ODR_8);
        //     GPIOB->ODR &= ~(GPIO_ODR_6);
        // }
    }

}