#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"

#define KEY_SWITCH_DELAY 5

void readKeyState(void); 				//Считывание состояние клавиш
uint8_t getVelocity(uint16_t tickNum); 	//Расчет velocity исходя из количества тиков
void checkNoteArray(void);
void Delay(__IO uint32_t nCount);
