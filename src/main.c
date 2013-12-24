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

uint8_t count;
uint16_t i;

extern FIFO32(128) midi_usb_in;
extern FIFO16(128) control_events;

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
	SPI1_init();
	USART1_init();
	usb_init(); //Init everything for midiUSB

	//Software init
	preset_load();
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
	GPIOB->ODR |= 0xFC07; // B0-B2, B10-B15
	GPIOC->ODR |= 0x38; // C3-C5
	GPIOD->ODR |= 0x300; // D8-D9
	GPIOE->ODR |= 0xFF80; // E7-E15

//	Start key scan timer
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}

/**********************************************/

void btoa(uint8_t value, char* buffer) {
	buffer += 2;
	*buffer = 0;
	*--buffer = value % 10 + 48;
	*--buffer = value / 10 + 48;
}
/***************************************************************************/
/*Function for the testing of buttons, encoders, and the display*/

int encoder_counter = 0;

void checkContol_events(void) {
	uint8_t test;
	uint16_t event;
	char st[10];

	test = FIFO_COUNT(control_events);
	if (test != 0) {
		event = FIFO_FRONT(control_events);
		FIFO_POP(control_events);
		hd44780_goto(1, 1);
		if ((event & 0x00FF) == 0x00FF) {
			if (event == 0x01FF) {
				encoder_counter++;
				if (encoder_counter > 99)
					encoder_counter = 0;
				hd44780_write_string("Encoder right ");
				btoa((uint8_t)(encoder_counter), st);
				hd44780_write_string(st);
			} else {
				encoder_counter--;
				if (encoder_counter < 0)
					encoder_counter = 99;
				hd44780_write_string("Encoder left  ");
				btoa((uint8_t)(encoder_counter), st);
				hd44780_write_string(st);
			}
		} else {
			hd44780_write_string("Butt ");
			btoa((uint8_t)(event & 0x00FF), st);
			hd44780_write_string(st);
			if ((event & 0xFF00) == 0) {
				hd44780_write_string(" down     ");
//				sendControlChange(22, (byte) (event & 0x00FF), 1);
			} else {
				hd44780_write_string("  up      ");
//				sendControlChange(23, (byte) (event & 0x00FF), 1);
			}
		}
	}

}

int main(void) {

	GPIO_SetBits(GPIOD, GPIO_Pin_10);

	firstInit();

	GPIO_SetBits(GPIOD, GPIO_Pin_15); //Test blue led

	//Main loop
	while (1) {

		//Check note array to calculate velocity
		checkNoteArray();

		//Send/receive midi data
		receiveMidiData();
		sendMidiData();

		checkContol_events();

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

		// GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		readKeyState();
		read_controls();
	}

}

