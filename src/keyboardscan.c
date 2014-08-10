#define STM32F40XX

#include "presets.h"
#include "keyboardscan.h"
#include "usb_midi_io.h"
#include "fifo.h"


FIFO8(128) midiMessagesArray; //Array for midi messages buffer
FIFO8(8) notes; //Array for current note
FIFO16(8) durations; //Array for duration for current note




static uint8_t lastState[11] = { 0 };



uint16_t duration_note[88] = { 0 };
uint16_t lastState_key[88] = { 0 };


static uint8_t curNote;
static uint16_t duration;

uint8_t UseHighRes = 1;
uint8_t MidiChannel = 0;



word vel_test = 0;
void checkNoteArray(void) {
	word vel;
	if (FIFO_COUNT(notes) != 0) {

		curNote = FIFO_FRONT(notes);
		duration = FIFO_FRONT(durations);

		FIFO_POP(durations);
		FIFO_POP(notes);

		if ((curNote & 0x80) == 0) {
			vel = getVelocity_on(duration, note_color(curNote));
			if (preset.HighResEnable) {
				/*Send High Res Preffix*/
				sendControlChange(0x58, (byte) (vel & 0x7F), preset.MidiChannel); //to midi
			}
			sendNoteOn(curNote, vel, preset.MidiChannel); //to midi
		} else {
			sendNoteOff(curNote & 0x7F, getVelocity_off(duration, note_color(curNote)), preset.MidiChannel); //to midi
		}

	}
}



/*The array of structures for all 11 key blocks GPIO pins*/
gpio_pins_type gpio_pins[11] = { { GPIOC, GPIO_Pin_5, GPIOC, GPIO_Pin_4 }, { GPIOB, GPIO_Pin_1, GPIOB, GPIO_Pin_0 }, { GPIOE, GPIO_Pin_8, GPIOB, GPIO_Pin_2 }, { GPIOE, GPIO_Pin_10, GPIOE, GPIO_Pin_9 }, { GPIOE, GPIO_Pin_12, GPIOE, GPIO_Pin_11 }, { GPIOE, GPIO_Pin_14, GPIOE, GPIO_Pin_13 }, { GPIOB, GPIO_Pin_10, GPIOE, GPIO_Pin_15 }, { GPIOB, GPIO_Pin_12, GPIOB, GPIO_Pin_11 }, { GPIOB, GPIO_Pin_14, GPIOB, GPIO_Pin_13 }, { GPIOD, GPIO_Pin_9, GPIOB, GPIO_Pin_15 }, { GPIOD, GPIO_Pin_8, GPIOD,
		GPIO_Pin_10 } };

/*Delay should be more long for full cycles code. The reason is unrecognized....*/
void key_delay(void) {
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

void readKeyState(void) {

	uint8_t d1, d2, i, j, chunk, chunk8;
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select

	for (chunk = 0; chunk <= 10; chunk++) {
		gpio_pins[chunk].first->BSRRH = gpio_pins[chunk].first_num; //Pin to zero
		chunk8 = chunk * 8;
		key_delay();
		d1 = ~GPIOA->IDR; //Read port state first contact
		gpio_pins[chunk].first->BSRRL = gpio_pins[chunk].first_num; //Pin to 1

		GPIOA->MODER |= 0x00005555; //PA0-7 Will be Output
		GPIOA->ODR = 0x00FF; //High level on PA0-7;
		GPIOA->MODER &= 0xFFFF0000; //PA0-7 Will be Input

		if (d1) {
			gpio_pins[chunk].second->BSRRH = gpio_pins[chunk].second_num;
			key_delay();
			d2 = ~GPIOA->IDR; //Read port state second contact
			gpio_pins[chunk].second->BSRRL = gpio_pins[chunk].second_num;

			GPIOA->MODER |= 0x00005555; //PA0-7 Will be Output
			GPIOA->ODR = 0x00FF; //High level on PA0-7;
			GPIOA->MODER &= 0xFFFF0000; //PA0-7 Will be Input

			for (i = 0; i <= 7; i++) {
				j = i + chunk8;
				if (d1 & k[i]) { // Key 0 in current chunk first sensor
					if (d2 & k[i]) { // Key 0 in current chunk second sensor
						if (lastState_key[j]) {
						} else {
							FIFO_PUSH(notes, j+21);
							FIFO_PUSH(durations, duration_note[j]);
							lastState_key[j] = 0x1;
							duration_note[j] = 0x0;
						}
					} else {
						if (duration_note[j] < 0xFFFF)
							duration_note[j]++;
					}

				} else {
					if (lastState_key[j]) {
						FIFO_PUSH(notes, j+149);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x0;
						duration_note[j] = 0x0;
					} else {
						duration_note[j] = 0x0;
					}
				}
			}
		} else {
			d2 = 0x0;
			if (lastState[chunk]) {
				chunk8 = chunk * 8;
				for (i = 0; i <= 7; i++) {
					j = i + chunk8;
					if (lastState_key[j]) {
						FIFO_PUSH(notes, j+149);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x0;
					}
					duration_note[j] = 0x0;
				}
			}
		}
		lastState[chunk] = d1;
	}

}

