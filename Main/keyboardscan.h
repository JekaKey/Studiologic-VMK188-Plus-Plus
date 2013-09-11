#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"

#define KEY_SWITCH_DELAY 1

/* Constants for velocity calculation*/

#define tick_factor_white 11000
#define min_ticks_white tick_factor_white / 127
#define max_ticks_white tick_factor_white*2

#define tick_factor_black 8000
#define min_ticks_black tick_factor_black / 127
#define max_ticks_black tick_factor_black*2

#define tick_factor_white_off tick_factor_white *2
#define min_ticks_white_off tick_factor_white_off / 127
#define max_ticks_white_off tick_factor_white_off*2

#define tick_factor_black_off tick_factor_black *2
#define min_ticks_black_off tick_factor_black_off / 127
#define max_ticks_black_off tick_factor_black_off*2




void readKeyState(void); 				//Считывание состояние клавиш
uint8_t getVelocity_on(uint16_t tickNum, uint16_t black ); 	//Расчет velocity исходя из количества тиков
uint8_t getVelocity_off(uint16_t tickNum, uint16_t black ); 	//Расчет velocity исходя из количества тиков
void checkNoteArray(void);
void Delay(__IO uint32_t nCount);
