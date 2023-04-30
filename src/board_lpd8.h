#pragma once

#include <stdint.h>
#include <gd32f30x.h>

typedef struct {
  uint32_t port;
  uint32_t pin;
  rcu_periph_enum clock;
} GpioPin;

#define GPIO_PIN(Port, Pin) ((GpioPin) { .port = GPIO##Port, .pin = GPIO_PIN_##Pin, .clock = RCU_GPIO##Port })

#define PROGRAM_LED_PIN GPIO_PIN(C, 11)
