/*******************************************************************/
#define STM32F40XX

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

#include "leds.h"
#include "log.h"

extern presetType Preset;
extern currentStateType Current_state;
extern calibrationType Calibration;


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
//	USART1_init();
	USART6_init();
	usb_init(); //Init everything for midiUSB

	ADC_init_all(); //ADC init
//	velocity_init();

	//Display
	delayms(400);
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
#ifdef VMK188
	hd44780_write_string("     VMK188++");
#else
	hd44780_write_string("     VMK176++");
#endif
}



//	Start key scan timer
static void Timer_init(void){
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);
}




int main(void) {
	firstInit();
    LED_light(2);
	set_defaults_all(&Preset, &Calibration);
    LED_light(4);
    delayms(2000);
	start_load_all(&Preset, &Calibration);
	interface_init(Current_state.preset_name);
	calibration_init(Current_state.calibration_name);
    LED_light(6);

    Timer_init();

	//Main loop
	while (1) {

		//Check note array to calculate velocity
		checkNoteArray(&Preset);

		//Send/receive midi data
		receiveMidiData();
		sendMidiData();
		checkSliders_events(Preset.sliders);
		head_buttons_handler();

	}
}

/**
 Timer 4 interrupt
 **/

void TIM4_IRQHandler() {

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {

		//TODO: Rewrite this w/o SPL
		//Clear interrupt bit

//		readKeyChunk();
		readKeyState();
		read_controls(Preset.sliders, Calibration.calibr);
		read_buttons_state();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}

}

