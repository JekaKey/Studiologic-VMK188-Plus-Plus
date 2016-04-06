
#include "presets.h"
#include "keyboardscan.h"
#include "usb_midi_io.h"
#include "fifo.h"
#include "controls.h"


FIFO8(128) midiMessagesArray; //Array for midi messages buffer
FIFO8(8) notes; //Array for current note
FIFO16(8) durations; //Array for duration for current note

uint8_t keySeek = 0;
uint8_t curNoteSeek=0;

static uint8_t lastState[11] = { 0 };



static uint16_t duration_note[88] = { 0 };
static uint16_t lastState_key[88] = { 0 };


static int16_t curNote;
static uint16_t duration;


/*new global block*

static uint32_t note_timer_start [88];
static uint32_t timer_counter=0;
static uint8_t Chunk = 0;
static uint8_t Sensors1=0;
static gpioPins_t gpioPins[22] =  {{ GPIOC, GPIO_Pin_5 },  { GPIOC, GPIO_Pin_4 },     //1
		                           { GPIOB, GPIO_Pin_1 },  { GPIOB, GPIO_Pin_0 },     //2
		                           { GPIOE, GPIO_Pin_8 },  { GPIOB, GPIO_Pin_2 },     //3
		                           { GPIOE, GPIO_Pin_10 }, { GPIOE, GPIO_Pin_9 },     //4
		                           { GPIOE, GPIO_Pin_12 }, { GPIOE, GPIO_Pin_11 },    //5
		                           { GPIOE, GPIO_Pin_14 }, { GPIOE, GPIO_Pin_13 },    //6
		                           { GPIOB, GPIO_Pin_10 }, { GPIOE, GPIO_Pin_15 },    //7
		                           { GPIOB, GPIO_Pin_12 }, { GPIOB, GPIO_Pin_11 },    //8
		                           { GPIOB, GPIO_Pin_14 }, { GPIOB, GPIO_Pin_13 },    //9
		                           { GPIOD, GPIO_Pin_9 },  { GPIOB, GPIO_Pin_15 },    //10
		                           { GPIOD, GPIO_Pin_8 },  { GPIOD, GPIO_Pin_10 }};   //11

*****************************************************/





void checkNoteArray(presetType* preset) {
	uint16_t vel;
	uint8_t channel;

	if (FIFO_COUNT(notes) != 0) {
		curNote = FIFO_FRONT(notes);
		duration = FIFO_FRONT(durations);

		FIFO_POP(durations);
		FIFO_POP(notes);

		uint8_t noteOn = (curNote & 0x80) == 0;
		curNote = curNote & 0x7F;
		curNote += NOTE_SHIFT;

		if (keySeek) {
			send_message(MES_KEY_SEEK);
			curNoteSeek=curNote;
			return;
		}

		if (preset->SplitActive && curNote < preset->SplitKey) {
			channel = preset->SplitChannel - 1;
			curNote += preset->SplitOctShift * 12;
		} else {
			channel = preset->MidiChannel - 1;
			curNote += preset->OctaveShift * 12;
		}

		if (channel > 15)
			channel = 0;

		curNote += preset->Transpose;
		if (curNote < 0 || curNote > 127)
			return;

		if (noteOn) {
			vel = getVelocity_on(duration, note_color(curNote));
			//Send High Res Preffix
			if (vel&0xFF80) {
				if (preset->HighResEnable){
					sendControlChange(0x58, (uint8_t)(vel & 0x7F), channel, preset->AnalogMidiEnable);
				}
				sendNoteOn(curNote, vel>>7, channel, preset->AnalogMidiEnable);
			}else{
				if (preset->SlowKeySound)
					sendNoteOn(curNote, 1, channel, preset->AnalogMidiEnable);
			}
		} else {
			sendNoteOff(curNote, getVelocity_off(duration, note_color(curNote)>>7),
					channel, preset->AnalogMidiEnable);
		}

	}
}



/*The array of structures for all 11 key blocks GPIO pins*/
#ifdef VMK188
static gpio_pins_type gpio_pins[11] = { { GPIOC, GPIO_Pin_5, GPIOC, GPIO_Pin_4 }, { GPIOB, GPIO_Pin_1, GPIOB, GPIO_Pin_0 }, { GPIOE, GPIO_Pin_8, GPIOB, GPIO_Pin_2 }, { GPIOE, GPIO_Pin_10, GPIOE, GPIO_Pin_9 }, { GPIOE, GPIO_Pin_12, GPIOE, GPIO_Pin_11 }, { GPIOE, GPIO_Pin_14, GPIOE, GPIO_Pin_13 }, { GPIOB, GPIO_Pin_10, GPIOE, GPIO_Pin_15 }, { GPIOB, GPIO_Pin_12, GPIOB, GPIO_Pin_11 }, { GPIOB, GPIO_Pin_14, GPIOB, GPIO_Pin_13 }, { GPIOD, GPIO_Pin_9, GPIOB, GPIO_Pin_15 }, { GPIOD, GPIO_Pin_8, GPIOD,
		GPIO_Pin_10 } };
#endif

#ifdef VMK176
static gpio_pins_type gpio_pins[10] = { { GPIOC, GPIO_Pin_5, GPIOC, GPIO_Pin_4 }, { GPIOB, GPIO_Pin_1, GPIOB, GPIO_Pin_0 }, { GPIOE, GPIO_Pin_8, GPIOB, GPIO_Pin_2 }, { GPIOE, GPIO_Pin_10, GPIOE, GPIO_Pin_9 },/* { GPIOE, GPIO_Pin_12, GPIOE, GPIO_Pin_11 },*/ { GPIOE, GPIO_Pin_14, GPIOE, GPIO_Pin_13 }, { GPIOB, GPIO_Pin_10, GPIOE, GPIO_Pin_15 }, { GPIOB, GPIO_Pin_12, GPIOB, GPIO_Pin_11 }, { GPIOB, GPIO_Pin_14, GPIOB, GPIO_Pin_13 }, { GPIOD, GPIO_Pin_9, GPIOB, GPIO_Pin_15 }, { GPIOD, GPIO_Pin_8, GPIOD,
		GPIO_Pin_10 } };
#endif


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


/*
void readKeyChunk() {
	uint8_t d,i,j, chunk8;
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select
	d = ~GPIOA->IDR; //Read port state first contact
	gpioPins[Chunk].gpio->BSRRL = gpioPins[Chunk].num; //Pin to 1
	GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
	GPIOA->ODR = 0x00FF; //High level on PA0-7;
	GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

	if (Chunk & 0x1) { //second sensor
		chunk8 = (Chunk-1) << 2;
		for (i = 0; i <= 7; i++) {
			j = i + chunk8;
			if (Sensors1 & k[i]) { // Key #i  in current chunk first sensor
				if (d & k[i]) { // Key #i in current chunk second sensor
					if (!lastState_key[j]) { //second sensor was not pressed before
						FIFO_PUSH(notes, j); //send noteon
						FIFO_PUSH(durations, (uint16_t)(timer_counter-note_timer_start[j]));
						lastState_key[j] = 0x1; //remember key is pressed
						note_timer_start[j]=timer_counter;
					}
				}
			} else { //first sensor was not pressed
				if (lastState_key[j]) { //key was pressed before
					FIFO_PUSH(notes, j+0x80); //send note off
					FIFO_PUSH(durations, (uint16_t)(timer_counter-note_timer_start[j]));
					lastState_key[j] = 0x0;
				}
				note_timer_start[j] = timer_counter;
			}
		}
		if (Chunk >= 21)
			Chunk = 0;
		else
			Chunk++;
	} else { //first sensor
		Sensors1 = d; //remember first sensors state
		if (d) { //one or more first sensors active
			lastState[Chunk>>1]=d;
			Chunk++; //need to look second sensors, in this case we don't need to check a maximum value
		} else { //chunk is depressed
			if (lastState[Chunk >> 1]) { //something was pressed before so it is just depressed
				chunk8 = Chunk << 2;
				for (i = 0; i <= 7; i++) {
					j = i + chunk8;
					if (lastState_key[j]) { //this key was pressed before
						FIFO_PUSH(notes, j+0x80); //send noteoff
						FIFO_PUSH(durations, (uint16_t)(timer_counter-note_timer_start[j])); //send time
						lastState_key[j] = 0x0; //no this key is not pressed
					}
				}
			}
			lastState[Chunk>>1]=0; //all chunk was depressed
			if (Chunk >= 20)//we don't need to check second sensor, because full chunk is depressed
				Chunk = 0; //go to the first chunk
			else
				Chunk += 2; //go to the next chunk
		}
	}
	gpioPins[Chunk].gpio->BSRRH = gpioPins[Chunk].num; //activate next chunk
	timer_counter++;
}

*/
void readKeyState(void) {

	uint8_t d1, d2, i, j, chunk, chunk8;
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select

	for (chunk = 0; chunk <= NUMBER_OF_CHUNKS; chunk++) {
		gpio_pins[chunk].first->BSRRH = gpio_pins[chunk].first_num; //Pin to zero
		chunk8 = chunk << 3;
		key_delay();
		d1 = ~GPIOA->IDR; //Read port state first contact
		gpio_pins[chunk].first->BSRRL = gpio_pins[chunk].first_num; //Pin to 1

		GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
		GPIOA->ODR = 0x00FF; //High level on PA0-7;
		GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

		if (d1) {//One or more keys in the chunk is pressed
			gpio_pins[chunk].second->BSRRH = gpio_pins[chunk].second_num;
			key_delay();
			d2 = ~GPIOA->IDR; //Read port state second contact
			gpio_pins[chunk].second->BSRRL = gpio_pins[chunk].second_num;

			GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
			GPIOA->ODR = 0x00FF; //High level on PA0-7;
			GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

			for (i = 0; i <= 7; i++) {
				j = i + chunk8;
				if (d1 & k[i]) { // Key 0 in current chunk first sensor
					if (d2 & k[i]) { // Key 0 in current chunk second sensor
						if (lastState_key[j]) {
						} else {
							FIFO_PUSH(notes, j);
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
						FIFO_PUSH(notes, j+0x80);
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
				chunk8 = chunk <<3;
				for (i = 0; i <= 7; i++) {
					j = i + chunk8;
					if (lastState_key[j]) {
						FIFO_PUSH(notes, j+0x80);
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

