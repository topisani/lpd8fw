#include "gd32f30x.h"
#include "systick.h"

volatile static uint32_t delay;

void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

void delay_1ms(uint32_t count)
{
    delay = count;

    while(0U != delay){
    }
}

void delay_decrement(void)
{
    if (0U != delay){
        delay--;
    }
}
