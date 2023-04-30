#include "board_lpd8.h"
#include "gd32f30x.h"
#include "systick.h"
#include <SEGGER_RTT.h>
#include <stdio.h>

static void rcu_config();

static void pots_init();
static void pots_poll();
static Potmeter pots[8] = {0};
static Potmeter pads[8] = {0};

int main(void) {
  rcu_config();
  systick_config();
  adc_init(ADC0);
  // adc_init(ADC2);

  /* print out the clock frequency of system, AHB, APB1 and APB2 */
  printf("CK_SYS is %d\n", rcu_clock_freq_get(CK_SYS));
  printf("CK_AHB is %d\n", rcu_clock_freq_get(CK_AHB));
  printf("CK_APB1 is %d\n", rcu_clock_freq_get(CK_APB1));
  printf("CK_APB2 is %d\n", rcu_clock_freq_get(CK_APB2));

  gpio_init(PROGRAM_LED_PIN.port, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ,
            PROGRAM_LED_PIN.pin);

  pots_init();

  while (1) {
    pots_poll();
  }
}

static void rcu_config() {
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_GPIOC);
  rcu_periph_clock_enable(RCU_GPIOD);
  rcu_periph_clock_enable(RCU_ADC0);
  rcu_periph_clock_enable(RCU_ADC1);
  rcu_periph_clock_enable(RCU_ADC2);

  rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV6);
}

static void pots_init() {
  potmeter_init(&pots[0], POT1_PIN);
  potmeter_init(&pots[1], POT2_PIN);
  potmeter_init(&pots[2], POT3_PIN);
  potmeter_init(&pots[3], POT4_PIN);
  potmeter_init(&pots[4], POT5_PIN);
  potmeter_init(&pots[5], POT6_PIN);
  potmeter_init(&pots[6], POT7_PIN);
  potmeter_init(&pots[7], POT8_PIN);
  
  potmeter_init(&pads[0], PAD1_PIN);
  potmeter_init(&pads[1], PAD2_PIN);
  potmeter_init(&pads[2], PAD3_PIN);
  potmeter_init(&pads[3], PAD4_PIN);
  potmeter_init(&pads[4], PAD5_PIN);
  potmeter_init(&pads[5], PAD6_PIN);
  potmeter_init(&pads[6], PAD7_PIN);
  potmeter_init(&pads[7], PAD8_PIN);
}

static void pots_poll() {
  for (int i = 0; i < 8; i++) {
    if (potmeter_poll(&pots[i])) {
      printf("POT%d: %d\n", i + 1, pots[i].val);
    }
  }
  
  for (int i = 0; i < 8; i++) {
    if (potmeter_poll(&pads[i])) {
      printf("PAD%d: %d\n", i + 1, pads[i].val);
    }
  }
}
