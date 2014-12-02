#ifndef LEDS_H
#define LEDS_H

#include "stm32f4xx.h"

/*Fuctions for debug LEDs */

#define LED1 1
#define LED2 2
#define LED3 4
void LED_light(uint8_t pattern);

/*Fuctions for conrtol LEDs */


void controlLEDs_switch (void);
void controlLEDs_enable(uint8_t enable);
void controlLED1on(uint8_t on);
void controlLED2on(uint8_t on);

#endif
