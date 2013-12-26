#include "sysex_events.h"



void sysex_parse_event() {

	/***
	 * Disassemble array
	 * First 2 byte - command
	 * Then 1 byte - data size, max 255 byte
	 * Then data
	 */

	volatile uint16_t command = (sysexArray.buf[sysexArray.tail] << 8) | (sysexArray.buf[sysexArray.tail + 1]);
	sysexArray.tail += 2;
	sysex_run_command(command);

	//Clean array
	FIFO_FLUSH(sysexArray);

}

void sysex_run_command(uint16_t command) {

	switch (command) {
		case 1:
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			break;
		case 2:
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			break;
		case 3:
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			break;
		case 4:
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			break;
		default:
			//Send sysex command not found
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			break;
	}

}

