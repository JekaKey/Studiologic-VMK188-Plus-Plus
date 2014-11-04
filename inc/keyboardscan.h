#define STM32F40XX


/*Different variants of the code for best speed search*/

//#define NOCYCLES // The code doesn't use any cycles
//#define SEMICYCLES // Cycle (8) is  only inside each keyboard block
#define FULLCYCLES_STRUCT //Double cycle (11)*(8) GPIO pins are addressing via big structure.
//#define FULLCYCLES_CASE  //Double cycle (11)*(8) GPIO pins are addressing in "switch" operator.

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "fifo.h"
#include "midi.h"
#include "presets.h"

#if defined FULLCYCLES_STRUCT

/*The structure describes GPIO pins for one keyboard 8-keys block*/
typedef struct {
	GPIO_TypeDef * first;
	uint16_t first_num;
	GPIO_TypeDef * second;
	uint16_t second_num;
} gpio_pins_type;
#endif

void readKeyState(void); //Read state of all 88 keys and send info to FIFO
void checkNoteArray(presetType* preset);
void delay(volatile uint32_t c);
void key_delay(void) __attribute__((optimize(0)));
