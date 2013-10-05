#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"

#define KEY_SWITCH_DELAY 1

/* Constants for velocity calculation*/



void readKeyState(void); 				//Считывание состояние клавиш
void checkNoteArray(void);
void delay(volatile uint32_t c);
