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


void string2usb (char * s){

	usb_midi_DataTx((uint8_t *)s, strlen(s));
}
