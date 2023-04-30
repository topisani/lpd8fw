#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{
    /* configure systick */
    systick_config();
    
    /* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("\r\nCK_SYS is %d", rcu_clock_freq_get(CK_SYS));
    printf("\r\nCK_AHB is %d", rcu_clock_freq_get(CK_AHB));
    printf("\r\nCK_APB1 is %d", rcu_clock_freq_get(CK_APB1));
    printf("\r\nCK_APB2 is %d", rcu_clock_freq_get(CK_APB2));
    
    while (1){
        // if(RESET == gd_eval_key_state_get(KEY_WAKEUP)){
        //     gd_eval_led_on(LED3);
        //     delay_1ms(500);
        //     gd_eval_led_off(LED3);
        //     gd_eval_led_toggle(LED4);
        // }
    }
}
