/*******************************************************************/

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define MAIN

#include "main.h"
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

#include "ff.h"
#include "sd_fatfs.h"
#include "diskio.h"

#include "leds.h"
#include "log.h"

#include "bootloader.h"


extern uint8_t okIO;//if this flag is zero all I/O operations will be canceled.
extern timer_counter_t temp_msg_timer_counter; //defined in menu.c
extern timer_counter_t MSC_stop_timer_counter;

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
static void firstInit(void) {

	//Hardware init
	GPIO_init();
	USART1_init();//midi
	USART6_init();//debug
	usb_midi_init(); //Init everything for midiUSB

	ADC_init_all(); //ADC init
	SD_DMA_activate();
	//Display
	delayms(400);
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	hd44780_message_center(APP_NAME, 1);
	hd44780_message_center(APP_VERSION, 2);

}






int main(void) {
	BootLoaderStart();
	firstInit();
    set_defaults_all(&Preset, &Calibration);
    delayms(3000);
    if (!start_load_all(&Preset, &Calibration))
		   set_okIOzero();
	interface_init(Current_state.preset_name);
	calibration_init(Current_state.calibration_name);

    TIM4_init();//keyboard timer
    TIM6_init(1500);//delay for temp messages
    TIM7_init(200); //delay for MSC

	//Main loop
	while (1) {

		//Check note array to calculate velocity
		checkNoteArray(&Preset);

		//TODO: why presets in arguments?
		checkSliders_events(Preset.sliders, Preset.AnalogMidiEnable);
		checkButtons_events(Preset.buttons, Preset.AnalogMidiEnable);
		//Send/receive midi data
		receiveMidiData();
		sendMidiData();
	}
}

