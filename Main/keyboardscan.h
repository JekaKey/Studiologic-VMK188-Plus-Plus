#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"

#define KEY_SWITCH_DELAY 40 //это тот самый delay при этом значении и более медленном таймере играет, но иногда виснет

void readKeyState(void); 				//Считывание состояние клавиш
uint8_t getVelocity(uint16_t tickNum); 	//Расчет velocity исходя из количества тиков
void checkNoteArray(void);
