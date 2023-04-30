#include "board_lpd8.h"
#include "gd32f30x.h"
#include "systick.h"
#include <SEGGER_RTT.h>
#include <stdio.h>

int main(void) {
  /* configure systick */
  systick_config();

  /* print out the clock frequency of system, AHB, APB1 and APB2 */
  printf("\r\nCK_SYS is %d", rcu_clock_freq_get(CK_SYS));
  printf("\r\nCK_AHB is %d", rcu_clock_freq_get(CK_AHB));
  printf("\r\nCK_APB1 is %d", rcu_clock_freq_get(CK_APB1));
  printf("\r\nCK_APB2 is %d", rcu_clock_freq_get(CK_APB2));
  
  rcu_periph_clock_enable(PROGRAM_LED_PIN.clock);

  gpio_init(PROGRAM_LED_PIN.port, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,
            PROGRAM_LED_PIN.pin);
            
  

  while (1) {
    gpio_bit_set(PROGRAM_LED_PIN.port, PROGRAM_LED_PIN.pin);
    delay_1ms(500);
    gpio_bit_reset(PROGRAM_LED_PIN.port, PROGRAM_LED_PIN.pin);
    delay_1ms(500);
  }
}
