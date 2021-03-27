#include "led.h"
#include "stm32f0xx.h"

LED_STATUS led_sta;
void led_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN ;

    GPIOA->MODER &= ~GPIO_MODER_MODER7;
    GPIOA->OTYPER |= GPIO_OTYPER_OT_7;
    GPIOA->PUPDR &= 0xFFFFCFFF;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7;
    GPIOA->BSRR |= GPIO_BSRR_BR_7;
}
void led_Ctl(LED_STATUS status)
{
    switch(status)
    {
        case ON:
            GPIOA->ODR |= GPIO_ODR_7;
            break;
        case OFF:
            GPIOA->ODR &= ~(GPIO_ODR_7);
            break;
        
        default:
            GPIOA->BSRR |= GPIO_BSRR_BR_7;
            break;
    }
}
