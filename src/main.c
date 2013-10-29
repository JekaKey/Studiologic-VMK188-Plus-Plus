/*******************************************************************/
#define STM32F40XX

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define MAIN

#include "fifo.h"
#include "keyboardscan.h"
#include "midi.h"
#include "hd44780.h"
#include "usb_init.h"
#include "sliders.h"
#include "gpio_config.h"

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

uint8_t SPI1_send(uint8_t data) {

	SPI1->DR = data; // write data to be transmitted to the SPI data register
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE))
		; // wait until transmit complete
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE))
		;
	// wait until receive complete
	while (SPI1->SR & SPI_I2S_FLAG_BSY)
		;
	// wait until SPI is not busy anymore
	return SPI1->DR; // return received data from SPI data register
}

uint8_t Memory_Read_Status(void) {
	uint8_t temp;

	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	SPI1_send(0xD7);
	temp = SPI1_send(0x00);
	GPIO_SetBits(GPIOD, GPIO_Pin_15);

	return temp;
}

/**
 * First init
 */
void firstInit() {

	GPIO_init();
	SPI1_init();
	USART1_init();
	count = 100;
	init_ADC(); //ADC init
	velocity_init();
	usb_init(); //Init everything for midiUSB

	//TODO: move to gpio init module
	//First port init, all for high
	GPIOB->BSRRL = 0xFC07; // B0-B2, B10-B15
	GPIOC->BSRRL = 0x38; // C3-C5
	GPIOD->BSRRL = 0x300; // D8-D9
	GPIOE->BSRRL = 0xFF80; // E7-E15


	//Start key scan timer
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}


int main(void) {

	uint8_t MEM_status;

	firstInit();
	GPIO_SetBits(GPIOD, GPIO_Pin_10);
	delayms(5000);

	delayms(400);
	hd44780_init();
	hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_ON,
			HD44780_DISP_BLINK_OFF);

	hd44780_write_string("FATARMINATOR");
	hd44780_goto(2, 4);
	hd44780_write_string("PROJECT  v0.1");

	// Test memory
	do {
		MEM_status = Memory_Read_Status();
	} while (!(MEM_status & 0x80));

	GPIO_SetBits(GPIOD, GPIO_Pin_15); //Test blue led

	//Main loop
	while (1) {

		//Check note array to calculate velocity
		checkNoteArray();

		//Send midi data
		sendMidiData();

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
		read_sliders();
	}

}
