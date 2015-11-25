#define STM32F40XX

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"
#include "presets.h"

#ifdef VMK188
#define NUMBER_OF_CHUNKS 10
#define NOTE_SHIFT 21
#endif

#ifdef VMK176
#define NUMBER_OF_CHUNKS 9
#define NOTE_SHIFT 28
#endif


/*The structure describes GPIO pins for one keyboard 8-keys block*/
typedef struct {
	GPIO_TypeDef * first;
	uint16_t first_num;
	GPIO_TypeDef * second;
	uint16_t second_num;
} gpio_pins_type;

typedef struct {
	GPIO_TypeDef * gpio;
	uint16_t num;
} gpioPins_t;

void readKeyChunk();
void readKeyState(void); //Read state of all 88 keys and send info to FIFO
void checkNoteArray(presetType* preset);
void delay(volatile uint32_t c);
void key_delay(void) __attribute__((optimize(0)));
