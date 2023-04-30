#pragma once

#include "inputs.h"
#include <stdint.h>

#define POT1_PIN GPIO_PIN(C, 0)
#define POT2_PIN GPIO_PIN(C, 1)
#define POT3_PIN GPIO_PIN(C, 2)
#define POT4_PIN GPIO_PIN(C, 3)
#define POT5_PIN GPIO_PIN(A, 3)
#define POT6_PIN GPIO_PIN(A, 2)
#define POT7_PIN GPIO_PIN(A, 1)
#define POT8_PIN GPIO_PIN(A, 0)

#define PAD1_PIN GPIO_PIN(C, 4)
#define PAD2_PIN GPIO_PIN(C, 5)
#define PAD3_PIN GPIO_PIN(B, 0)
#define PAD4_PIN GPIO_PIN(B, 1)
#define PAD5_PIN GPIO_PIN(A, 7)
#define PAD6_PIN GPIO_PIN(A, 6)
#define PAD7_PIN GPIO_PIN(A, 5)
#define PAD8_PIN GPIO_PIN(A, 4)

#define BTN1_PIN GPIO_PIN(B, 5)
#define BTN2_PIN GPIO_PIN(B, 4)
#define BTN3_PIN GPIO_PIN(B, 6)
#define BTN4_PIN GPIO_PIN(B, 3)

#define BTN2_LED_PIN GPIO_PIN(C, 11)
#define BTN3_LED_PIN GPIO_PIN(C, 12)
#define BTN4_LED_PIN GPIO_PIN(C, 10)

#define WS2812B_PIN GPIO_PIN(B, 7)

#define USB_DM_PIN GPIO_PIN(A, 11)
#define USB_DP_PIN GPIO_PIN(A, 12)
