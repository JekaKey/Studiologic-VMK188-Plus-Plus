#include "sysex_events.h"
#include "presets.h"

FIFO8(128) sysexArray;

void sysex_parse_event() {

	/***
	 * Disassemble array
	 * First 2 byte - command
	 * Then 1 byte - data size, max 255 byte
	 * Then data
	 */

	volatile uint16_t command = (sysexArray.buf[sysexArray.tail + 1] << 8) | (sysexArray.buf[sysexArray.tail]);
	sysexArray.tail += 2;
	sysex_run_command(command);

	//Clean array
	FIFO_FLUSH(sysexArray);

}

void sysex_run_command(uint16_t command) {
	uint8_t mass[10];

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
		case 100:
			memory_page_to_buffer(1, 10);
			memory_page_to_buffer(2, 11);
			break;
		case 101:
			FIFO_POP(sysexArray);
			mass[0] = FIFO_FRONT(sysexArray);
			FIFO_POP(sysexArray);
			mass[1] = FIFO_FRONT(sysexArray);
			FIFO_POP(sysexArray);
			mass[2] = FIFO_FRONT(sysexArray);
			FIFO_POP(sysexArray);

			memory_send_8bit_to_buffer(mass[0], mass[1], mass[2]);
			break;
		case 102:
			memory_buffer_to_page(1, 10);
			memory_buffer_to_page(2, 11);
			break;
		case 103:

			break;
		case 104:

			break;
		default:
			//Send sysex command not found
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			break;
	}

}

