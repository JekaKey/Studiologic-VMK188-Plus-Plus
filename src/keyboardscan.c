
#include "presets.h"
#include "keyboardscan.h"
#include "usb_midi_io.h"
#include "fifo.h"
#include "controls.h"
#include "log.h"

FIFO8(128) midiMessagesArray; //Array for midi messages buffer
FIFO8(8) notes; //Array for current note
FIFO16(8) durations; //Array for duration for current note

uint8_t keySeek = 0;
uint8_t curNoteSeek=0;

static volatile uint32_t timerCounter = 0;

static uint8_t __attribute__ ((aligned (32))) lastState[16] = { 0 };



static uint16_t __attribute__ ((aligned (32))) duration_note[88] = { 0 };
static uint16_t __attribute__ ((aligned (32))) lastState_key[88] = { 0 };


//static int16_t curNote;
//static uint16_t duration;


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

static noteOffStore_t noteOffStore[128];
static uint8_t noteOffIndex = 0;

void noteOffStoreInit(void) {
	for (uint8_t i = 0; i < 128; i++){
		noteOffStore[i].delay = 0xFFFFFFFF;
		noteOffStore[i].count = 0x0;
	}
}

void checkNoteArray(presetType* preset) {
	uint8_t channel;
	int16_t curKey, curNote;
	uint16_t duration;
    uint16_t delay1=preset->NoteOffDelay1;
    uint16_t delay127=preset->NoteOffDelay127;
	noteOffStore_t* noteOff = &noteOffStore[noteOffIndex]; //save base address
	if ((~(noteOff->delay)) && (timerCounter - (noteOff->delay) > ((delay1-delay127)/(noteOff->vel)+delay127) * (1000 / TIMER_TIMPERIOD))) {
		for (uint8_t n=noteOff->count; n; n--)
		    sendNoteOff(noteOffIndex, noteOff->vel, noteOff->channel, preset->AnalogMidiEnable);
		noteOff->count=0;
		noteOff->delay = 0xFFFFFFFF;
	}
	if (++noteOffIndex > 127) // cycled step to next note
		noteOffIndex = 0;

	if (FIFO_COUNT(notes)) {
		curKey = FIFO_FRONT(notes);
		duration = FIFO_FRONT(durations);

		FIFO_POP(durations);
		FIFO_POP(notes);

		uint8_t noteOn = !(curKey & 0x80);
		curKey &= 0x7F;
		curKey +=NOTE_SHIFT;
		curNote = curKey;

		if (keySeek) {
			send_message(MES_KEY_SEEK);
			curNoteSeek = curKey;
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
			uint16_t vel = getVelocity_on(duration, note_color(curKey));
			//Send High Res Preffix
			if (vel & 0x3F80) {
				if (preset->HighResEnable) {
					sendControlChange(0x58, (uint8_t)(vel & 0x7F), channel,
							preset->AnalogMidiEnable);
				}
				sendNoteOn(curNote, (uint8_t)(vel >> 7), channel, preset->AnalogMidiEnable);
				noteOffStore[curNote].delay = 0xFFFFFFFF;
				noteOffStore[curNote].count++;
			} else {
				if (preset->SlowKeySound) {
					sendNoteOn(curNote, 1, channel, preset->AnalogMidiEnable);
					noteOffStore[curNote].delay = 0xFFFFFFFF;
					noteOffStore[curNote].count++;
				}
			}
		} else {
			noteOffStore[curNote].delay = timerCounter;
			noteOffStore[curNote].vel = (uint8_t)(getVelocity_off(duration, note_color(noteOffIndex)) >> 7);
			noteOffStore[curNote].channel = channel;
		}

	}
}



/*
void checkNoteArray(presetType* preset) {
	uint16_t vel;
	uint8_t channel;
	int16_t curNote;
	uint16_t duration;

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
			vel=getVelocity_off(duration, note_color(curNote));
			sendNoteOff(curNote, vel>>7,
					channel, preset->AnalogMidiEnable);
		}

	}
}

*/

/*The array of structures for all 11 key blocks GPIO pins*/
#ifdef VMK188
static gpio_pins_type gpio_pins[11] = { { GPIOC, GPIOC, GPIO_Pin_5, GPIO_Pin_4 },
										{ GPIOB, GPIOB, GPIO_Pin_1, GPIO_Pin_0 },
										{ GPIOE, GPIOB, GPIO_Pin_8, GPIO_Pin_2 },
										{ GPIOE, GPIOE, GPIO_Pin_10, GPIO_Pin_9 },
										{ GPIOE, GPIOE, GPIO_Pin_12, GPIO_Pin_11 },
										{ GPIOE, GPIOE, GPIO_Pin_14, GPIO_Pin_13 },
										{ GPIOB, GPIOE, GPIO_Pin_10, GPIO_Pin_15 },
										{ GPIOB, GPIOB, GPIO_Pin_12, GPIO_Pin_11 },
										{ GPIOB, GPIOB, GPIO_Pin_14, GPIO_Pin_13 },
										{ GPIOD, GPIOB, GPIO_Pin_9, GPIO_Pin_15 },
										{ GPIOD, GPIOD, GPIO_Pin_8, GPIO_Pin_10 } };
#endif



#ifdef VMK176

static gpio_pins_type gpio_pins[11] = { { GPIOC, GPIOC, GPIO_Pin_5, GPIO_Pin_4 },
										{ GPIOB, GPIOB, GPIO_Pin_1, GPIO_Pin_0 },
										{ GPIOE, GPIOB, GPIO_Pin_8, GPIO_Pin_2 },
										{ GPIOE, GPIOE, GPIO_Pin_10, GPIO_Pin_9 },
										/*{ GPIOE, GPIOE, GPIO_Pin_12, GPIO_Pin_11 },*/
										{ GPIOE, GPIOE, GPIO_Pin_14, GPIO_Pin_13 },
										{ GPIOB, GPIOE, GPIO_Pin_10, GPIO_Pin_15 },
										{ GPIOB, GPIOB, GPIO_Pin_12, GPIO_Pin_11 },
										{ GPIOB, GPIOB, GPIO_Pin_14, GPIO_Pin_13 },
										{ GPIOD, GPIOB, GPIO_Pin_9, GPIO_Pin_15 },
										{ GPIOD, GPIOD, GPIO_Pin_8, GPIO_Pin_10 } };

#endif





/*
void readKeyChunk() {
	uint8_t d,i,j, chunk8;
	d = ~GPIOA->IDR; //Read port state first contact
	gpioPins[Chunk].gpio->BSRRL = gpioPins[Chunk].num; //Pin to 1
	GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
	GPIOA->ODR = 0x00FF; //High level on PA0-7;
	GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

	if (Chunk & 0x1) { //second sensor
		chunk8 = (Chunk-1) << 2;
		for (uint8_t i = 0, j=chunk8; i <= 7; i++, j++) {
			if (Sensors1 & (1<<i)) { // Key #i  in current chunk first sensor
				if (d & (1<<i)) { // Key #i in current chunk second sensor
					if (!lastState_key[j]) { //second sensor was not pressed before
						FIFO_PUSH(notes, j); //send noteon
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1; //remember key is pressed
						duration_note[j]=0x0;
					}
				}
			} else { //first sensor was not pressed
				if (lastState_key[j]) { //key was pressed before
					FIFO_PUSH(notes, j+0x80); //send note off
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]=0x0;
			}
		}
		if (Chunk >= (NUMBER_OF_CHUNKS+1)*2-1)
			Chunk = 0;
		else
			Chunk++;
	} else { //first sensor
		Sensors1 = d; //remember first sensors state
		if (d) { //one or more first sensors active
			lastState[Chunk>>1]=d;
		} else { //chunk is depressed
			if (lastState[Chunk >> 1]) { //something was pressed before so it is just depressed
				chunk8 = Chunk << 2;
				for (uint8_t i = 0, j=chunk8; i <= 7; i++, j++) {
					if (lastState_key[j]) { //this key was pressed before
						FIFO_PUSH(notes, j+0x80); //send noteoff
						FIFO_PUSH(durations, duration_note[j]); //send time
						lastState_key[j] = 0x0; //no this key is not pressed
					}
				}
			}
			lastState[Chunk>>1]=0; //all chunk was depressed
		}
		Chunk++; //need to look second sensors, in this case we don't need to check a maximum value
	}
	gpioPins[Chunk].gpio->BSRRH = gpioPins[Chunk].num; //activate next chunk
}

*/


void  key_delay1(void) {
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
}


void  key_delay2(void) {
	__NOP();
	__NOP();
	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
}


void readKeyState(void)  {
	timerCounter++;
	for (uint8_t chunk = 0; chunk <= NUMBER_OF_CHUNKS; chunk++) {
		gpio_pins[chunk].first->BSRRH = gpio_pins[chunk].first_num; //Pin to zero
		uint8_t chunk8 = chunk << 3;
		key_delay1();
		uint8_t d1 = ~GPIOA->IDR; //Read port state first contact
		gpio_pins[chunk].first->BSRRL = gpio_pins[chunk].first_num; //Pin to 1

		GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
		GPIOA->ODR = 0x00FF; //High level on PA0-7;
		GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

		if (d1) {//One or more keys in the chunk is pressed
			gpio_pins[chunk].second->BSRRH = gpio_pins[chunk].second_num;
			for (uint8_t i = 0, j = chunk8; i < 8; i++, j++) { //useful calculation instead of long delay
				if (lastState_key[j]) {
					if (!(d1 & (0x01 << i))) {
						FIFO_PUSH(notes, j|0x80);//note off
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x0;
						duration_note[j] = 0x0;
					}
				}
			}
			//key_delay2(); //Probably it is not necessary
			uint8_t d2 = ~GPIOA->IDR; //Read port state second contact
			gpio_pins[chunk].second->BSRRL = gpio_pins[chunk].second_num;

			GPIOA->MODER |= 0x00005555; //PA0-7 Switch to Output
			GPIOA->ODR = 0x00FF; //High level on PA0-7;
			GPIOA->MODER &= 0xFFFF0000; //PA0-7 Switch to Input

			for (uint8_t i = 0, j=chunk8; i < 8; i++, j++) {
				if (d1 & (0x01<<i)) { // Key 0 in current chunk first sensor
					if (d2 & (0x01<<i)) { // Key 0 in current chunk second sensor
						if (!lastState_key[j]) {
							FIFO_PUSH(notes, j);//note on
							FIFO_PUSH(durations, duration_note[j]);
							lastState_key[j] = 0x1;
							duration_note[j] = 0x0;
						}
					} else {
						if (~(duration_note[j]))
							duration_note[j]++;
					}
				}
			}
		} else {
			if (lastState[chunk]) {
				for (uint8_t j=chunk8; j <= chunk8+7; j++) {
					if (lastState_key[j]) {
						FIFO_PUSH(notes, j|0x80);
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
