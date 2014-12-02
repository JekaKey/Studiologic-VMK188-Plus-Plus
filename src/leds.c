#include "leds.h"
#include "stm32f4xx_gpio.h"
#include "usb_midi_io.h"
#include <string.h>

void LED_light(uint8_t pattern){
	if (pattern&1){
		GPIO_SetBits(GPIOC, GPIO_Pin_13); //Light the green led
	}else{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13); //Light the green led
	}

	if (pattern&2){
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //Light the green led
	}else{
		GPIO_ResetBits(GPIOC, GPIO_Pin_14); //Light the green led
	}

	if (pattern&4){
		GPIO_SetBits(GPIOC, GPIO_Pin_15); //Light the green led
	}else{
		GPIO_ResetBits(GPIOC, GPIO_Pin_15); //Light the green led
	}
}

static uint8_t controlLED2_state=0;
static uint8_t controlLED1_state=0;



void controlLEDs_enable(uint8_t enable){
	if (enable && (controlLED1_state||controlLED2_state)) {
		GPIO_SetBits(GPIOB, GPIO_Pin_7); // LEDs base to the VCC potential;
	} else {
		GPIO_ResetBits(GPIOB, GPIO_Pin_7); // LEDs base to the ground potential;
	}
}



void controlLEDs_switch (void){
	if (controlLED1_state) {
		GPIO_SetBits(GPIOE, GPIO_Pin_0);
	}else{
		GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	}
	if (controlLED2_state) {
		GPIO_SetBits(GPIOE, GPIO_Pin_1);
	}else{
		GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	}
}


void controlLED1on(uint8_t on){
	controlLED1_state=on;
	controlLEDs_enable(controlLED1_state || controlLED2_state);
}

void controlLED2on(uint8_t on){
	controlLED2_state=on;
	controlLEDs_enable(controlLED1_state || controlLED2_state);
}
