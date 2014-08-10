/*******************************************************************/
#define STM32F40XX

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define MAIN

#include "presets.h"
#include "fifo.h"
#include "keyboardscan.h"
#include "midi.h"
#include "hd44780.h"
#include "usb_init.h"
#include "controls.h"
#include "gpio_config.h"
#include "usb_midi_io.h"
#include "menu.h"

uint8_t count;
uint16_t i;

void delay(volatile uint32_t c) {
	while (--c) {
		__NOP();
	}
}

void delayms(volatile uint32_t c) {
	c++;
	while (--c) {
		delay(23080);
	}
}

/**
 * First init
 */
void firstInit() {

	//Hardware init
	GPIO_init();
//	SPI1_init();
	USART1_init();
	usb_init(); //Init everything for midiUSB

	//Software init
//	preset_load();
	count = 100;
	ADC_init_all(); //ADC init
	velocity_init();
	sliders_init();

	//Display
	delayms(400);
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);

	hd44780_write_string("     VMK188++");

	//TODO: move to gpio init module
	//First port init, all for high
//	GPIOB->ODR |= 0xFC07; // B0-B2, B10-B15
//	GPIOC->ODR |= 0x38; // C3-C5
//	GPIOD->ODR |= 0x300; // D8-D9
//	GPIOE->ODR |= 0xFF80; // E7-E15

//	Start key scan timer
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}

int main(void) {


	firstInit();

//	GPIO_SetBits(GPIOC, GPIO_Pin_13); //Light the green led
//	GPIO_SetBits(GPIOC, GPIO_Pin_14); //Light the blue led
	GPIO_SetBits(GPIOC, GPIO_Pin_15); //Light the red led

	//Main loop
	while (1) {

		//Check note array to calculate velocity
		checkNoteArray();

		//Send/receive midi data
		receiveMidiData();
		sendMidiData();
		checkSliders_events();
		checkControl_events();

	}
}

/**
 Timer 4 interrupt
 **/

void TIM4_IRQHandler() {

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {

		//TODO: Rewrite this w/o SPL
		//Clear interrupt bit
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

		readKeyState();
		read_controls();
	}

}

