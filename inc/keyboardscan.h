#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"

/*try to remove structures from the code  and increase speed*/
#define GPIOA_MODER GPIOA_BASE
#define GPIOA_ODR GPIOA_BASE+0x14
#define GPIOA_IDR GPIOA_BASE+0x10
#define GPIOB_BSRRH GPIOB_BASE+0x1A
#define GPIOB_BSRRL GPIOB_BASE+0x18
#define GPIOE_BSRRH GPIOE_BASE+0x1A
#define GPIOE_BSRRL GPIOE_BASE+0x18
#define GPIOC_BSRRH GPIOC_BASE+0x1A
#define GPIOC_BSRRL GPIOC_BASE+0x18
#define GPIOD_BSRRH GPIOD_BASE+0x1A
#define GPIOD_BSRRL GPIOD_BASE+0x18


#define KEY_SWITCH_DELAY 1

/* Constants for velocity calculation*/



void readKeyState(void); 				//Считывание состояние клавиш
void checkNoteArray(void);
void delay(volatile uint32_t c);
