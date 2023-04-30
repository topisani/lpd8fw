#include "inputs.h"
#include "systick.h"
#include <stdlib.h>

void gpio_pin_init(GpioPin pin, uint32_t mode) {
  gpio_init(pin.port, mode, GPIO_OSPEED_10MHZ, pin.pin);
}
bool gpio_pin_read(GpioPin pin) {

  return gpio_input_bit_get(pin.port, pin.pin) == SET;
}

void gpio_pin_write(GpioPin pin, bool state) {
  gpio_bit_write(pin.port, pin.pin, state);
}

void adc_init(uint32_t adc_periph) {
  adc_mode_config(ADC_MODE_FREE);

  adc_data_alignment_config(adc_periph, ADC_DATAALIGN_RIGHT);
  adc_channel_length_config(adc_periph, ADC_REGULAR_CHANNEL, 1U);

  adc_external_trigger_source_config(adc_periph, ADC_REGULAR_CHANNEL,
                                     ADC0_1_2_EXTTRIG_REGULAR_NONE);
  adc_external_trigger_config(adc_periph, ADC_REGULAR_CHANNEL, ENABLE);

  adc_enable(adc_periph);
  delay_1ms(1U);
  adc_calibration_enable(adc_periph);
}

uint16_t adc_sample(AdcChannel adc) {

  /* ADC regular channel config */
  adc_regular_channel_config(adc.periph, 0U, adc.channel,
                             ADC_SAMPLETIME_239POINT5);
  /* ADC software trigger enable */
  adc_software_trigger_enable(adc.periph, ADC_REGULAR_CHANNEL);

  /* wait the end of conversion flag */
  while (!adc_flag_get(adc.periph, ADC_FLAG_EOC))
    ;
  /* clear the end of conversion flag */
  adc_flag_clear(adc.periph, ADC_FLAG_EOC);
  return (adc_regular_data_read(adc.periph));
}

AdcChannel adc_for_gpio(GpioPin pin) {
  // clang-format off
  switch (pin.port) {
    case GPIOA: {
      switch (pin.pin) {
        case GPIO_PIN_0: return ADC_CHANNEL(0, 0);
        case GPIO_PIN_1: return ADC_CHANNEL(0, 1);
        case GPIO_PIN_2: return ADC_CHANNEL(0, 2);
        case GPIO_PIN_3: return ADC_CHANNEL(0, 3);
        case GPIO_PIN_4: return ADC_CHANNEL(0, 4);
        case GPIO_PIN_5: return ADC_CHANNEL(0, 5);
        case GPIO_PIN_6: return ADC_CHANNEL(0, 6);
        case GPIO_PIN_7: return ADC_CHANNEL(0, 7);
      }
    } break;
    case GPIOB: {
      switch (pin.pin) {
        case GPIO_PIN_0: return ADC_CHANNEL(0, 8);
        case GPIO_PIN_1: return ADC_CHANNEL(0, 9);
      }
    } break;
    case GPIOC: {
      switch (pin.pin) {
        case GPIO_PIN_0: return ADC_CHANNEL(0, 10);
        case GPIO_PIN_1: return ADC_CHANNEL(0, 11);
        case GPIO_PIN_2: return ADC_CHANNEL(0, 12);
        case GPIO_PIN_3: return ADC_CHANNEL(0, 13);
        case GPIO_PIN_4: return ADC_CHANNEL(0, 14);
        case GPIO_PIN_5: return ADC_CHANNEL(0, 15);
      }
    } break;
    
    default: break;
  }
  // clang-format on
  return (AdcChannel){0, 0};
}

void potmeter_init(Potmeter *pot, GpioPin pin) {
  gpio_pin_init(pin, GPIO_MODE_AIN);
  pot->adc = adc_for_gpio(pin);
}

bool potmeter_poll(Potmeter *pot) {
  uint16_t new_val = adc_sample(pot->adc);
  if (abs((int)new_val - ((int)pot->val)) > 16) {
    pot->val = new_val;
    return true;
  }
  return false;
}

void button_init(Button *btn, GpioPin pin) {
  btn->pin = pin;
  gpio_pin_init(pin, GPIO_MODE_IPU);
}

bool button_poll(Button *btn) {
  bool new_state = !gpio_pin_read(btn->pin);
  if (new_state != btn->state) {
    btn->state = new_state;
    return true;
  }
  return false;
}

void led_init(GpioPin pin) {
  gpio_pin_init(pin, GPIO_MODE_OUT_PP);
  gpio_pin_write(pin, true);
}

void led_set(GpioPin pin, bool state) { gpio_pin_write(pin, !state); }

