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
#include "stm32_ub_fatfs.h"


#include "leds.h"

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


//	Start key scan timer
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}



int main(void) {


	firstInit();
    FIL myFile;   // Filehandler


/*test SD*/
    // Init vom FATFS-System
    UB_Fatfs_Init();
  	 LED_light(4) ;

    // Check ob Medium eingelegt ist
    if(UB_Fatfs_CheckMedia(MMC_0)==FATFS_OK) {
   	 LED_light(1) ;

  	// Media mounten
      if(UB_Fatfs_Mount(MMC_0)==FATFS_OK) {
    	 LED_light(2) ;
        // File zum schreiben im root neu anlegen
        if(UB_Fatfs_OpenFile(&myFile, "0:/vmk188pp.txt", F_WR_CLEAR)==FATFS_OK) {
       	 LED_light(7) ;

      	// ein paar Textzeilen in das File schreiben
          UB_Fatfs_WriteString(&myFile,"Test1");
          UB_Fatfs_WriteString(&myFile,"test2");
          UB_Fatfs_WriteString(&myFile,"test3");
          // File schliessen
          UB_Fatfs_CloseFile(&myFile);
        }
        // Media unmounten
     	  UB_Fatfs_UnMount(MMC_0);
      }
    }



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

