#pragma once

#include <gd32f30x.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t port;
  uint32_t pin;
} GpioPin;

#define GPIO_PIN(Port, Pin)                                                    \
  ((GpioPin){.port = GPIO##Port, .pin = GPIO_PIN_##Pin})

void gpio_pin_init(GpioPin pin, uint32_t mode);
bool gpio_pin_read(GpioPin pin);
void gpio_pin_write(GpioPin pin, bool state);

typedef struct {
  uint32_t periph;
  uint8_t channel;
} AdcChannel;

#define ADC_CHANNEL(Peripheral, Channel)                                       \
  ((AdcChannel){.periph = ADC##Peripheral, .channel = ADC_CHANNEL_##Channel})

AdcChannel adc_for_gpio(GpioPin pin);
void adc_init(uint32_t adc_periph);
uint16_t adc_sample(AdcChannel);

typedef struct {
  AdcChannel adc;
  uint16_t val;
} Potmeter;

void potmeter_init(Potmeter *pot, GpioPin pin);
bool potmeter_poll(Potmeter *pot);

typedef struct {
  GpioPin pin;
  bool state;
} Button;

void button_init(Button *btn, GpioPin pin);
/// Returns true if the button value has changed
bool button_poll(Button *btn);

void led_init(GpioPin pin);
void led_set(GpioPin pin, bool state);
