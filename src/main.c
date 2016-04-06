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

void delay(volatile uint32_t c) {
	while (--c) {
		__NOP();
	}
}

void delayms(volatile uint32_t c) {
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
#ifdef WS0010_GRAPHICS
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	ws0010_Graphics_mode();
	ws0010_Draw_buffer(pictureVMK188);
    delayms(20000);
	ws0010_Character_mode();
	hd44780_init();
#else
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	hd44780_message_center(APP_NAME, 1);
	hd44780_message_center(APP_VERSION, 2);
    delayms(3000);
#endif

}


int main(void) {
	BootLoaderStart();
	firstInit();
    set_defaults_all(&Preset, &Calibration);
    if (!start_load_all(&Preset, &Calibration))
		   set_okIOzero();
	interface_init(Current_state.preset_name);
	calibration_init(Current_state.calibration_name);

    TIM4_init();//keyboard timer
    TIM6_init();//delay for temp messages
    TIM7_init(); //delay for MSC

	//Main loop
	while (1) {
		//Check note array to calculate velocity
		checkNoteArray(&Preset);
		checkSliders_events(Preset.sliders, Preset.AnalogMidiEnable);
		checkButtons_events(Preset.buttons, Preset.AnalogMidiEnable);
		receiveMidiData();
		sendMidiData();
	}
}

