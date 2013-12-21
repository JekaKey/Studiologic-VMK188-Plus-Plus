#define STM32F40XX
#ifndef SYSEXEVENT_H
#define SYSEXEVENT_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "fifo.h"
#include "presets.h"

void sysex_parse_event(void);
void sysex_run_command(uint16_t command);

#endif //SYSEXEVENT_H
