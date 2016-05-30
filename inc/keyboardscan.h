#ifndef __KEYBOARDSCAN
#define __KEYBOARDSCAN

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"
#include "presets.h"

#ifdef VMK188
#define NUMBER_OF_CHUNKS 10
#define NUMBER_OF_KEYS 88
#define NOTE_SHIFT 21
#endif

#ifdef VMK176
#define NUMBER_OF_CHUNKS 9
#define NUMBER_OF_KEYS 76
#define NOTE_SHIFT 28
#endif


/*The structure describes GPIO pins for one keyboard 8-keys block*/
typedef struct {
	GPIO_TypeDef * first;
	GPIO_TypeDef * second;
	uint16_t first_num;
	uint16_t second_num;
} __attribute__ ((aligned (32))) gpio_pins_type;

typedef struct {
	GPIO_TypeDef * gpio;
	uint16_t num;
} __attribute__ ((aligned (32))) gpioPins_t;

typedef struct {
	uint32_t delay;
	uint8_t vel;
	uint8_t channel;
	uint8_t count;
} __attribute__ ((aligned (32))) noteOffStore_t;


//void readKeyChunk();
void readKeyState(); //Read state of all 88 keys and send info to FIFO
void checkNoteArray();
void noteOffStoreInit(void);
void delay(volatile uint32_t c);
void key_delay1(void) __attribute__((optimize(0)));
void key_delay2(void) __attribute__((optimize(0)));

#endif //__KEYBOARDSCAN
