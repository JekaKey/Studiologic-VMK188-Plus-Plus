#define STM32F40XX

#include "keyboardscan.h"
#include "usb_midi_io.h"

#if defined NOCYCLES
/* Last state key send in chunk */
uint8_t lastState1 = 0x00;
uint8_t lastState2 = 0x00;
uint8_t lastState3 = 0x00;
uint8_t lastState4 = 0x00;
uint8_t lastState5 = 0x00;
uint8_t lastState6 = 0x00;
uint8_t lastState7 = 0x00;
uint8_t lastState8 = 0x00;
uint8_t lastState9 = 0x00;
uint8_t lastState10 = 0x00;
uint8_t lastState11 = 0x00;
#endif

#if defined SEMICYCLES
/* Last state key send in chunk */
uint8_t lastState1 = 0x00;
uint8_t lastState2 = 0x00;
uint8_t lastState3 = 0x00;
uint8_t lastState4 = 0x00;
uint8_t lastState5 = 0x00;
uint8_t lastState6 = 0x00;
uint8_t lastState7 = 0x00;
uint8_t lastState8 = 0x00;
uint8_t lastState9 = 0x00;
uint8_t lastState10 = 0x00;
uint8_t lastState11 = 0x00;
#endif

#if defined FULLCYCLES_STRUCT
static uint8_t lastState[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#endif

#if defined FULLCYCLES_CASE
static uint8_t lastState[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

#if defined NOCYCLES
uint16_t lastState_key1 = 0x0;
uint16_t lastState_key2 = 0x0;
uint16_t lastState_key3 = 0x0;
uint16_t lastState_key4 = 0x0;
uint16_t lastState_key5 = 0x0;
uint16_t lastState_key6 = 0x0;
uint16_t lastState_key7 = 0x0;
uint16_t lastState_key8 = 0x0;
uint16_t lastState_key9 = 0x0;
uint16_t lastState_key10 = 0x0;
uint16_t lastState_key11 = 0x0;
uint16_t lastState_key12 = 0x0;
uint16_t lastState_key13 = 0x0;
uint16_t lastState_key14 = 0x0;
uint16_t lastState_key15 = 0x0;
uint16_t lastState_key16 = 0x0;
uint16_t lastState_key17 = 0x0;
uint16_t lastState_key18 = 0x0;
uint16_t lastState_key19 = 0x0;
uint16_t lastState_key20 = 0x0;
uint16_t lastState_key21 = 0x0;
uint16_t lastState_key22 = 0x0;
uint16_t lastState_key23 = 0x0;
uint16_t lastState_key24 = 0x0;
uint16_t lastState_key25 = 0x0;
uint16_t lastState_key26 = 0x0;
uint16_t lastState_key27 = 0x0;
uint16_t lastState_key28 = 0x0;
uint16_t lastState_key29 = 0x0;
uint16_t lastState_key30 = 0x0;
uint16_t lastState_key31 = 0x0;
uint16_t lastState_key32 = 0x0;
uint16_t lastState_key33 = 0x0;
uint16_t lastState_key34 = 0x0;
uint16_t lastState_key35 = 0x0;
uint16_t lastState_key36 = 0x0;
uint16_t lastState_key37 = 0x0;
uint16_t lastState_key38 = 0x0;
uint16_t lastState_key39 = 0x0;
uint16_t lastState_key40 = 0x0;
uint16_t lastState_key41 = 0x0;
uint16_t lastState_key42 = 0x0;
uint16_t lastState_key43 = 0x0;
uint16_t lastState_key44 = 0x0;
uint16_t lastState_key45 = 0x0;
uint16_t lastState_key46 = 0x0;
uint16_t lastState_key47 = 0x0;
uint16_t lastState_key48 = 0x0;
uint16_t lastState_key49 = 0x0;
uint16_t lastState_key50 = 0x0;
uint16_t lastState_key51 = 0x0;
uint16_t lastState_key52 = 0x0;
uint16_t lastState_key53 = 0x0;
uint16_t lastState_key54 = 0x0;
uint16_t lastState_key55 = 0x0;
uint16_t lastState_key56 = 0x0;
uint16_t lastState_key57 = 0x0;
uint16_t lastState_key58 = 0x0;
uint16_t lastState_key59 = 0x0;
uint16_t lastState_key60 = 0x0;
uint16_t lastState_key61 = 0x0;
uint16_t lastState_key62 = 0x0;
uint16_t lastState_key63 = 0x0;
uint16_t lastState_key64 = 0x0;
uint16_t lastState_key65 = 0x0;
uint16_t lastState_key66 = 0x0;
uint16_t lastState_key67 = 0x0;
uint16_t lastState_key68 = 0x0;
uint16_t lastState_key69 = 0x0;
uint16_t lastState_key70 = 0x0;
uint16_t lastState_key71 = 0x0;
uint16_t lastState_key72 = 0x0;
uint16_t lastState_key73 = 0x0;
uint16_t lastState_key74 = 0x0;
uint16_t lastState_key75 = 0x0;
uint16_t lastState_key76 = 0x0;
uint16_t lastState_key77 = 0x0;
uint16_t lastState_key78 = 0x0;
uint16_t lastState_key79 = 0x0;
uint16_t lastState_key80 = 0x0;
uint16_t lastState_key81 = 0x0;
uint16_t lastState_key82 = 0x0;
uint16_t lastState_key83 = 0x0;
uint16_t lastState_key84 = 0x0;
uint16_t lastState_key85 = 0x0;
uint16_t lastState_key86 = 0x0;
uint16_t lastState_key87 = 0x0;
uint16_t lastState_key88 = 0x0;
uint16_t duration_note1 = 0x0;
uint16_t duration_note2 = 0x0;
uint16_t duration_note3 = 0x0;
uint16_t duration_note4 = 0x0;
uint16_t duration_note5 = 0x0;
uint16_t duration_note6 = 0x0;
uint16_t duration_note7 = 0x0;
uint16_t duration_note8 = 0x0;
uint16_t duration_note9 = 0x0;
uint16_t duration_note10 = 0x0;
uint16_t duration_note11 = 0x0;
uint16_t duration_note12 = 0x0;
uint16_t duration_note13 = 0x0;
uint16_t duration_note14 = 0x0;
uint16_t duration_note15 = 0x0;
uint16_t duration_note16 = 0x0;
uint16_t duration_note17 = 0x0;
uint16_t duration_note18 = 0x0;
uint16_t duration_note19 = 0x0;
uint16_t duration_note20 = 0x0;
uint16_t duration_note21 = 0x0;
uint16_t duration_note22 = 0x0;
uint16_t duration_note23 = 0x0;
uint16_t duration_note24 = 0x0;
uint16_t duration_note25 = 0x0;
uint16_t duration_note26 = 0x0;
uint16_t duration_note27 = 0x0;
uint16_t duration_note28 = 0x0;
uint16_t duration_note29 = 0x0;
uint16_t duration_note30 = 0x0;
uint16_t duration_note31 = 0x0;
uint16_t duration_note32 = 0x0;
uint16_t duration_note33 = 0x0;
uint16_t duration_note34 = 0x0;
uint16_t duration_note35 = 0x0;
uint16_t duration_note36 = 0x0;
uint16_t duration_note37 = 0x0;
uint16_t duration_note38 = 0x0;
uint16_t duration_note39 = 0x0;
uint16_t duration_note40 = 0x0;
uint16_t duration_note41 = 0x0;
uint16_t duration_note42 = 0x0;
uint16_t duration_note43 = 0x0;
uint16_t duration_note44 = 0x0;
uint16_t duration_note45 = 0x0;
uint16_t duration_note46 = 0x0;
uint16_t duration_note47 = 0x0;
uint16_t duration_note48 = 0x0;
uint16_t duration_note49 = 0x0;
uint16_t duration_note50 = 0x0;
uint16_t duration_note51 = 0x0;
uint16_t duration_note52 = 0x0;
uint16_t duration_note53 = 0x0;
uint16_t duration_note54 = 0x0;
uint16_t duration_note55 = 0x0;
uint16_t duration_note56 = 0x0;
uint16_t duration_note57 = 0x0;
uint16_t duration_note58 = 0x0;
uint16_t duration_note59 = 0x0;
uint16_t duration_note60 = 0x0;
uint16_t duration_note61 = 0x0;
uint16_t duration_note62 = 0x0;
uint16_t duration_note63 = 0x0;
uint16_t duration_note64 = 0x0;
uint16_t duration_note65 = 0x0;
uint16_t duration_note66 = 0x0;
uint16_t duration_note67 = 0x0;
uint16_t duration_note68 = 0x0;
uint16_t duration_note69 = 0x0;
uint16_t duration_note70 = 0x0;
uint16_t duration_note71 = 0x0;
uint16_t duration_note72 = 0x0;
uint16_t duration_note73 = 0x0;
uint16_t duration_note74 = 0x0;
uint16_t duration_note75 = 0x0;
uint16_t duration_note76 = 0x0;
uint16_t duration_note77 = 0x0;
uint16_t duration_note78 = 0x0;
uint16_t duration_note79 = 0x0;
uint16_t duration_note80 = 0x0;
uint16_t duration_note81 = 0x0;
uint16_t duration_note82 = 0x0;
uint16_t duration_note83 = 0x0;
uint16_t duration_note84 = 0x0;
uint16_t duration_note85 = 0x0;
uint16_t duration_note86 = 0x0;
uint16_t duration_note87 = 0x0;
uint16_t duration_note88 = 0x0;
#endif

#if defined  SEMICYCLES
uint16_t duration_note[88] =
{	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,};
uint16_t lastState_key[88] =
{	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,};

#endif

#if defined  FULLCYCLES_CASE
uint16_t duration_note[88] =
{	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,};
uint16_t lastState_key[88] =
{	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,};

#endif

#if defined  FULLCYCLES_STRUCT
uint16_t duration_note[88] =
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, };
uint16_t lastState_key[88] =
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, };

#endif

static uint8_t curNote;
static uint16_t duration;

uint8_t UseHighRes = 1;
uint8_t MidiChannel = 0;

/**
 * Расчет velocity и запись в midi буффер
 */

word vel_test = 0;
void checkNoteArray(void) {
	//Проверяем буффер считанных клавиш с длительностями
	word vel;
	if (FIFO_COUNT(notes) != 0) {

		curNote = FIFO_FRONT(notes);
		duration = FIFO_FRONT(durations);

		FIFO_POP(durations);
		FIFO_POP(notes);

		if ((curNote & 0x80) == 0) {
			vel = getVelocity_on(duration, note_color(curNote));
			if (UseHighRes) {
				/*Send High Res Preffix*/
				sendControlChange(0x58, (byte) (vel & 0x7F), MidiChannel); //to midi
				sendUSB_ControlChange(0x58, (byte) (vel & 0x7F), MidiChannel); //to usb
			}
			sendNoteOn(curNote, vel, MidiChannel); //to midi
			sendUSB_NoteOn(curNote, vel, MidiChannel); // to usb
		} else {
			sendNoteOff(curNote & 0x7F,
					getVelocity_off(duration, note_color(curNote)),
					MidiChannel); //to midi
			sendUSB_NoteOff(curNote & 0x7F,
					getVelocity_off(duration, note_color(curNote)),
					MidiChannel); //to usb
		}

	}
}

#if defined FULLCYCLES_STRUCT

/*The array of structures for all 11 key blocks GPIO pins*/
 gpio_pins_type gpio_pins[11] = { { GPIOE, GPIO_Pin_15, GPIOE, GPIO_Pin_14 }, {
		GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10 }, { GPIOB, GPIO_Pin_13, GPIOB,
		GPIO_Pin_12 }, { GPIOB, GPIO_Pin_15, GPIOB, GPIO_Pin_14 }, { GPIOD,
		GPIO_Pin_9, GPIOD, GPIO_Pin_8 },
		{ GPIOC, GPIO_Pin_4, GPIOC, GPIO_Pin_5 }, { GPIOB, GPIO_Pin_0, GPIOB,
				GPIO_Pin_1 }, { GPIOE, GPIO_Pin_7, GPIOB, GPIO_Pin_2 }, { GPIOE,
				GPIO_Pin_9, GPIOE, GPIO_Pin_8 }, { GPIOE, GPIO_Pin_12, GPIOE,
				GPIO_Pin_10 }, { GPIOE, GPIO_Pin_11, GPIOE, GPIO_Pin_13 } };

/*Delay should be more long for full cycles code. The reason is unrecognized....*/
volatile static key_delay(void) {
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
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };//array with values for key select

	for (chunk = 0; chunk <= 10; chunk++) {
		gpio_pins[chunk].first->BSRRH = gpio_pins[chunk].first_num; //Pin to zero
		key_delay();
		d1 = ~GPIOA->IDR; //Read port state first contact
		gpio_pins[chunk].first->BSRRL = gpio_pins[chunk].first_num; //Pin to 1

		GPIOA->MODER |= 0x00005555; //PA0-8 Will be Output
		GPIOA->ODR = 0x00FF; //High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000; //PA0-8 Will be Input

		if (d1) {
			gpio_pins[chunk].second->BSRRH = gpio_pins[chunk].second_num;
			key_delay();
			d2 = ~GPIOA->IDR; //Read port state second contact
			gpio_pins[chunk].second->BSRRL = gpio_pins[chunk].second_num;

			GPIOA->MODER |= 0x00005555; //PA0-8 Will be Output
			GPIOA->ODR = 0x00FF; //High level on PA0-8;
			GPIOA->MODER &= 0xFFFF0000; //PA0-8 Will be Input

			chunk8 = chunk * 8;
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
#endif

#if defined FULLCYCLES_CASE
static void key_delay(void) {
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();

}

void readKeyState(void) {

	uint8_t d1, d2, i, j, chunk, chunk8;
	uint8_t k[8] = {1, 2, 4, 8, 16, 32, 64, 128};

	for (chunk = 0; chunk <= 10; chunk++) {
		switch (chunk) {
			case 0:
			GPIOE->BSRRH = GPIO_Pin_15; //Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOE->BSRRL = GPIO_Pin_15;//Pin to 1
			break;
			case 1:
			GPIOB->BSRRH = GPIO_Pin_11;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOB->BSRRL = GPIO_Pin_11;//Pin to 1
			break;
			case 2:
			GPIOB->BSRRH = GPIO_Pin_13;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOB->BSRRL = GPIO_Pin_13;//Pin to 1
			break;
			case 3:
			GPIOB->BSRRH = GPIO_Pin_15;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOB->BSRRL = GPIO_Pin_15;//Pin to 1
			break;
			case 4:
			GPIOD->BSRRH = GPIO_Pin_9;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOD->BSRRL = GPIO_Pin_9;//Pin to 1
			break;
			case 5:
			GPIOC->BSRRH = GPIO_Pin_4;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOC->BSRRL = GPIO_Pin_4;//Pin to 1
			break;
			case 6:
			GPIOB->BSRRH = GPIO_Pin_0;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOB->BSRRL = GPIO_Pin_0;//Pin to 1
			break;
			case 7:
			GPIOE->BSRRH = GPIO_Pin_7;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOE->BSRRL = GPIO_Pin_7;//Pin to 1
			break;
			case 8:
			GPIOE->BSRRH = GPIO_Pin_9;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOE->BSRRL = GPIO_Pin_9;//Pin to 1
			break;
			case 9:
			GPIOE->BSRRH = GPIO_Pin_12;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOE->BSRRL = GPIO_Pin_12;//Pin to 1
			break;
			case 10:
			GPIOE->BSRRH = GPIO_Pin_11;//Pin to zero
			key_delay();
			d1 = ~GPIOA->IDR;//Read port state first contact
			GPIOE->BSRRL = GPIO_Pin_11;//Pin to 1
			break;
		}

		GPIOA->MODER |= 0x00005555; //PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		if (d1) {
			switch (chunk) {
				case 0:
				GPIOE->BSRRH = GPIO_Pin_14;
				key_delay();
				d2 = ~GPIOA->IDR; //Read port state second contact
				GPIOE->BSRRL = GPIO_Pin_14;
				break;
				case 1:
				GPIOB->BSRRH = GPIO_Pin_10;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOB->BSRRL = GPIO_Pin_10;
				break;
				case 2:
				GPIOB->BSRRH = GPIO_Pin_12;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOB->BSRRL = GPIO_Pin_12;
				break;
				case 3:
				GPIOB->BSRRH = GPIO_Pin_14;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOB->BSRRL = GPIO_Pin_14;
				break;
				case 4:
				GPIOD->BSRRH = GPIO_Pin_8;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOD->BSRRL = GPIO_Pin_8;
				break;
				case 5:
				GPIOC->BSRRH = GPIO_Pin_5;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOC->BSRRL = GPIO_Pin_5;
				break;
				case 6:
				GPIOB->BSRRH = GPIO_Pin_1;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOB->BSRRL = GPIO_Pin_1;
				break;
				case 7:
				GPIOB->BSRRH = GPIO_Pin_2;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOB->BSRRL = GPIO_Pin_2;
				break;
				case 8:
				GPIOE->BSRRH = GPIO_Pin_8;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOE->BSRRL = GPIO_Pin_8;
				break;
				case 9:
				GPIOE->BSRRH = GPIO_Pin_10;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOE->BSRRL = GPIO_Pin_10;
				break;
				case 10:
				GPIOE->BSRRH = GPIO_Pin_13;
				key_delay();
				d2 = ~GPIOA->IDR;//Read port state second contact
				GPIOE->BSRRL = GPIO_Pin_13;
				break;
			}

			GPIOA->MODER |= 0x00005555; //PA0-8 Will be Output
			GPIOA->ODR = 0x00FF;//High level on PA0-8;
			GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

			chunk8 = chunk * 8;
			for (i = 0; i <= 7; i++) {
				j = i + chunk8;
				if (d1 & k[i]) { // Key 0 in current chunk first sensor
					if (d2 & k[i]) { // Key 0 in current chunk second sensor
						if (lastState_key[j]) {
						} else {
							FIFO_PUSH( notes, j+21);
							FIFO_PUSH( durations, duration_note[j]);
							lastState_key[j] = 0x1;
							duration_note[j] = 0x0;
						}
					} else {
						if (duration_note[j] < 0xFFFF)
						duration_note[j]++;
					}

				} else {
					if (lastState_key[j]) {
						FIFO_PUSH( notes, j+149);
						FIFO_PUSH( durations, duration_note[j]);
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
						FIFO_PUSH( notes, j+149);
						FIFO_PUSH( durations, duration_note[j]);
						lastState_key[j] = 0x0;
					}
					duration_note[j] = 0x0;
				}
			}
		}
		lastState[chunk] = d1;
	}
}
#endif

#if defined SEMICYCLES

static void key_delay(void)
{
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();

}

void readKeyState(void)
{

	uint8_t d1, d2, i, j;
	uint8_t k [8]=
	{	1,2,4,8,16,32,64,128};

	/* 1 chunk */

	GPIOE->BSRRH = GPIO_Pin_15; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_15;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOE->BSRRH = GPIO_Pin_14;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_14;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+0;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+21);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+149);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState1)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+0;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+149);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState1 = d1;
	/* 2 chunk */

	GPIOB->BSRRH = GPIO_Pin_11; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_11;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOB->BSRRH = GPIO_Pin_10;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_10;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+8;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+29);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+157);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState2)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+8;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+157);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState2 = d1;
	/* 3 chunk */

	GPIOB->BSRRH = GPIO_Pin_13; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_13;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOB->BSRRH = GPIO_Pin_12;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_12;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+16;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+37);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+165);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState3)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+16;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+165);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState3 = d1;
	/* 4 chunk */

	GPIOB->BSRRH = GPIO_Pin_15; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_15;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOB->BSRRH = GPIO_Pin_14;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_14;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+24;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+45);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+173);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState4)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+24;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+173);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState4 = d1;
	/* 5 chunk */

	GPIOD->BSRRH = GPIO_Pin_9; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOD->BSRRL = GPIO_Pin_9;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOD->BSRRH = GPIO_Pin_8;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOD->BSRRL = GPIO_Pin_8;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+32;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+53);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+181);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState5)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+32;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+181);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState5 = d1;
	/* 6 chunk */

	GPIOC->BSRRH = GPIO_Pin_4; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOC->BSRRL = GPIO_Pin_4;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOC->BSRRH = GPIO_Pin_5;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOC->BSRRL = GPIO_Pin_5;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+40;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+61);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+189);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState6)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+40;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+189);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState6 = d1;
	/* 7 chunk */

	GPIOB->BSRRH = GPIO_Pin_0; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_0;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOB->BSRRH = GPIO_Pin_1;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_1;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+48;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+69);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+197);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState7)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+48;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+197);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState7 = d1;
	/* 8 chunk */

	GPIOE->BSRRH = GPIO_Pin_7; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_7;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOB->BSRRH = GPIO_Pin_2;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_2;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+56;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+77);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+205);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState8)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+56;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+205);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState8 = d1;
	/* 9 chunk */

	GPIOE->BSRRH = GPIO_Pin_9; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_9;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOE->BSRRH = GPIO_Pin_8;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_8;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+64;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+85);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+213);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState9)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+64;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+213);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState9 = d1;
	/* 10 chunk */

	GPIOE->BSRRH = GPIO_Pin_12; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_12;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOE->BSRRH = GPIO_Pin_10;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_10;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+72;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+93);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+221);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState10)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+72;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+221);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState10 = d1;
	/* 11 chunk */

	GPIOE->BSRRH = GPIO_Pin_11; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_11;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1)
	{

		GPIOE->BSRRH = GPIO_Pin_13;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_13;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		for (i = 0; i <= 7; i++)
		{
			j=i+80;
			if (d1 & k[i])
			{ // Key 0 in current chunk first sensor
				if (d2 & k[i])
				{ // Key 0 in current chunk second sensor
					if (lastState_key[j])
					{
					}
					else
					{
						FIFO_PUSH(notes,i+101);
						FIFO_PUSH(durations, duration_note[j]);
						lastState_key[j] = 0x1;
						duration_note[j] = 0x0;
					}
				}
				else
				{
					if(duration_note[j] <0xFFFF) duration_note[j]++;
				}

			}
			else
			{
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+229);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
					duration_note[j] = 0x0;
				}
				else
				{
					duration_note[j] = 0x0;
				}
			}
		}
	}
	else
	{
		d2 = 0x0;
		if (lastState11)
		{
			for (i = 0; i <= 7; i++)
			{
				j=i+80;
				if (lastState_key[j])
				{
					FIFO_PUSH(notes,i+229);
					FIFO_PUSH(durations, duration_note[j]);
					lastState_key[j] = 0x0;
				}
				duration_note[j]= 0x0;
			}
		}
	}
	lastState11 = d1;

}
#endif

#if defined NOCYCLES
static void key_delay(void) {
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();

}

void readKeyState(void) {

	uint8_t d1, d2;

	/* 1 chunk */

	GPIOE->BSRRH = GPIO_Pin_15; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_15;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOE->BSRRH = GPIO_Pin_14;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_14;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*1 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key1) {
				} else {
					FIFO_PUSH(notes, 21);
					FIFO_PUSH(durations, duration_note1);
					lastState_key1 = 0x1;
					duration_note1 = 0x0;
				}
			} else {
				if (duration_note1 < 0xFFFF)
				duration_note1++;
			}

		} else {
			if (lastState_key1) {
				FIFO_PUSH(notes, 149);
				FIFO_PUSH(durations, duration_note1);
				lastState_key1 = 0x0;
				duration_note1 = 0x0;
			} else {
				duration_note1 = 0x0;
			}
		}
		/*2 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key2) {
				} else {
					FIFO_PUSH(notes, 22);
					FIFO_PUSH(durations, duration_note2);
					lastState_key2 = 0x1;
					duration_note2 = 0x0;
				}
			} else {
				if (duration_note2 < 0xFFFF)
				duration_note2++;
			}

		} else {
			if (lastState_key2) {
				FIFO_PUSH(notes, 150);
				FIFO_PUSH(durations, duration_note2);
				lastState_key2 = 0x0;
				duration_note2 = 0x0;
			} else {
				duration_note2 = 0x0;
			}
		}
		/*3 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key3) {
				} else {
					FIFO_PUSH(notes, 23);
					FIFO_PUSH(durations, duration_note3);
					lastState_key3 = 0x1;
					duration_note3 = 0x0;
				}
			} else {
				if (duration_note3 < 0xFFFF)
				duration_note3++;
			}

		} else {
			if (lastState_key3) {
				FIFO_PUSH(notes, 151);
				FIFO_PUSH(durations, duration_note3);
				lastState_key3 = 0x0;
				duration_note3 = 0x0;
			} else {
				duration_note3 = 0x0;
			}
		}
		/*4 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key4) {
				} else {
					FIFO_PUSH(notes, 24);
					FIFO_PUSH(durations, duration_note4);
					lastState_key4 = 0x1;
					duration_note4 = 0x0;
				}
			} else {
				if (duration_note4 < 0xFFFF)
				duration_note4++;
			}

		} else {
			if (lastState_key4) {
				FIFO_PUSH(notes, 152);
				FIFO_PUSH(durations, duration_note4);
				lastState_key4 = 0x0;
				duration_note4 = 0x0;
			} else {
				duration_note4 = 0x0;
			}
		}
		/*5 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key5) {
				} else {
					FIFO_PUSH(notes, 25);
					FIFO_PUSH(durations, duration_note5);
					lastState_key5 = 0x1;
					duration_note5 = 0x0;
				}
			} else {
				if (duration_note5 < 0xFFFF)
				duration_note5++;
			}

		} else {
			if (lastState_key5) {
				FIFO_PUSH(notes, 153);
				FIFO_PUSH(durations, duration_note5);
				lastState_key5 = 0x0;
				duration_note5 = 0x0;
			} else {
				duration_note5 = 0x0;
			}
		}
		/*6 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key6) {
				} else {
					FIFO_PUSH(notes, 26);
					FIFO_PUSH(durations, duration_note6);
					lastState_key6 = 0x1;
					duration_note6 = 0x0;
				}
			} else {
				if (duration_note6 < 0xFFFF)
				duration_note6++;
			}

		} else {
			if (lastState_key6) {
				FIFO_PUSH(notes, 154);
				FIFO_PUSH(durations, duration_note6);
				lastState_key6 = 0x0;
				duration_note6 = 0x0;
			} else {
				duration_note6 = 0x0;
			}
		}
		/*7 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key7) {
				} else {
					FIFO_PUSH(notes, 27);
					FIFO_PUSH(durations, duration_note7);
					lastState_key7 = 0x1;
					duration_note7 = 0x0;
				}
			} else {
				if (duration_note7 < 0xFFFF)
				duration_note7++;
			}

		} else {
			if (lastState_key7) {
				FIFO_PUSH(notes, 155);
				FIFO_PUSH(durations, duration_note7);
				lastState_key7 = 0x0;
				duration_note7 = 0x0;
			} else {
				duration_note7 = 0x0;
			}
		}
		/*8 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key8) {
				} else {
					FIFO_PUSH(notes, 28);
					FIFO_PUSH(durations, duration_note8);
					lastState_key8 = 0x1;
					duration_note8 = 0x0;
				}
			} else {
				if (duration_note8 < 0xFFFF)
				duration_note8++;
			}

		} else {
			if (lastState_key8) {
				FIFO_PUSH(notes, 156);
				FIFO_PUSH(durations, duration_note8);
				lastState_key8 = 0x0;
				duration_note8 = 0x0;
			} else {
				duration_note8 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState1) {
			if (lastState_key1) {
				FIFO_PUSH(notes, 149);
				FIFO_PUSH(durations, duration_note1);
				lastState_key1 = 0x0;
			}
			if (lastState_key2) {
				FIFO_PUSH(notes, 150);
				FIFO_PUSH(durations, duration_note2);
				lastState_key2 = 0x0;
			}
			if (lastState_key3) {
				FIFO_PUSH(notes, 151);
				FIFO_PUSH(durations, duration_note3);
				lastState_key3 = 0x0;
			}
			if (lastState_key4) {
				FIFO_PUSH(notes, 152);
				FIFO_PUSH(durations, duration_note4);
				lastState_key4 = 0x0;
			}
			if (lastState_key5) {
				FIFO_PUSH(notes, 153);
				FIFO_PUSH(durations, duration_note5);
				lastState_key5 = 0x0;
			}
			if (lastState_key6) {
				FIFO_PUSH(notes, 154);
				FIFO_PUSH(durations, duration_note6);
				lastState_key6 = 0x0;
			}
			if (lastState_key7) {
				FIFO_PUSH(notes, 155);
				FIFO_PUSH(durations, duration_note7);
				lastState_key7 = 0x0;
			}
			if (lastState_key8) {
				FIFO_PUSH(notes, 156);
				FIFO_PUSH(durations, duration_note8);
				lastState_key8 = 0x0;
			}
			duration_note1 = 0x0;
			duration_note2 = 0x0;
			duration_note3 = 0x0;
			duration_note4 = 0x0;
			duration_note5 = 0x0;
			duration_note6 = 0x0;
			duration_note7 = 0x0;
			duration_note8 = 0x0;
		}
	}
	lastState1 = d1;
	/* 2 chunk */

	GPIOB->BSRRH = GPIO_Pin_11; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_11;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOB->BSRRH = GPIO_Pin_10;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_10;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*9 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key9) {
				} else {
					FIFO_PUSH(notes, 29);
					FIFO_PUSH(durations, duration_note9);
					lastState_key9 = 0x1;
					duration_note9 = 0x0;
				}
			} else {
				if (duration_note9 < 0xFFFF)
				duration_note9++;
			}

		} else {
			if (lastState_key9) {
				FIFO_PUSH(notes, 157);
				FIFO_PUSH(durations, duration_note9);
				lastState_key9 = 0x0;
				duration_note9 = 0x0;
			} else {
				duration_note9 = 0x0;
			}
		}
		/*10 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key10) {
				} else {
					FIFO_PUSH(notes, 30);
					FIFO_PUSH(durations, duration_note10);
					lastState_key10 = 0x1;
					duration_note10 = 0x0;
				}
			} else {
				if (duration_note10 < 0xFFFF)
				duration_note10++;
			}

		} else {
			if (lastState_key10) {
				FIFO_PUSH(notes, 158);
				FIFO_PUSH(durations, duration_note10);
				lastState_key10 = 0x0;
				duration_note10 = 0x0;
			} else {
				duration_note10 = 0x0;
			}
		}
		/*11 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key11) {
				} else {
					FIFO_PUSH(notes, 31);
					FIFO_PUSH(durations, duration_note11);
					lastState_key11 = 0x1;
					duration_note11 = 0x0;
				}
			} else {
				if (duration_note11 < 0xFFFF)
				duration_note11++;
			}

		} else {
			if (lastState_key11) {
				FIFO_PUSH(notes, 159);
				FIFO_PUSH(durations, duration_note11);
				lastState_key11 = 0x0;
				duration_note11 = 0x0;
			} else {
				duration_note11 = 0x0;
			}
		}
		/*12 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key12) {
				} else {
					FIFO_PUSH(notes, 32);
					FIFO_PUSH(durations, duration_note12);
					lastState_key12 = 0x1;
					duration_note12 = 0x0;
				}
			} else {
				if (duration_note12 < 0xFFFF)
				duration_note12++;
			}

		} else {
			if (lastState_key12) {
				FIFO_PUSH(notes, 160);
				FIFO_PUSH(durations, duration_note12);
				lastState_key12 = 0x0;
				duration_note12 = 0x0;
			} else {
				duration_note12 = 0x0;
			}
		}
		/*13 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key13) {
				} else {
					FIFO_PUSH(notes, 33);
					FIFO_PUSH(durations, duration_note13);
					lastState_key13 = 0x1;
					duration_note13 = 0x0;
				}
			} else {
				if (duration_note13 < 0xFFFF)
				duration_note13++;
			}

		} else {
			if (lastState_key13) {
				FIFO_PUSH(notes, 161);
				FIFO_PUSH(durations, duration_note13);
				lastState_key13 = 0x0;
				duration_note13 = 0x0;
			} else {
				duration_note13 = 0x0;
			}
		}
		/*14 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key14) {
				} else {
					FIFO_PUSH(notes, 34);
					FIFO_PUSH(durations, duration_note14);
					lastState_key14 = 0x1;
					duration_note14 = 0x0;
				}
			} else {
				if (duration_note14 < 0xFFFF)
				duration_note14++;
			}

		} else {
			if (lastState_key14) {
				FIFO_PUSH(notes, 162);
				FIFO_PUSH(durations, duration_note14);
				lastState_key14 = 0x0;
				duration_note14 = 0x0;
			} else {
				duration_note14 = 0x0;
			}
		}
		/*15 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key15) {
				} else {
					FIFO_PUSH(notes, 35);
					FIFO_PUSH(durations, duration_note15);
					lastState_key15 = 0x1;
					duration_note15 = 0x0;
				}
			} else {
				if (duration_note15 < 0xFFFF)
				duration_note15++;
			}

		} else {
			if (lastState_key15) {
				FIFO_PUSH(notes, 163);
				FIFO_PUSH(durations, duration_note15);
				lastState_key15 = 0x0;
				duration_note15 = 0x0;
			} else {
				duration_note15 = 0x0;
			}
		}
		/*16 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key16) {
				} else {
					FIFO_PUSH(notes, 36);
					FIFO_PUSH(durations, duration_note16);
					lastState_key16 = 0x1;
					duration_note16 = 0x0;
				}
			} else {
				if (duration_note16 < 0xFFFF)
				duration_note16++;
			}

		} else {
			if (lastState_key16) {
				FIFO_PUSH(notes, 164);
				FIFO_PUSH(durations, duration_note16);
				lastState_key16 = 0x0;
				duration_note16 = 0x0;
			} else {
				duration_note16 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState2) {
			if (lastState_key9) {
				FIFO_PUSH(notes, 157);
				FIFO_PUSH(durations, duration_note9);
				lastState_key9 = 0x0;
			}
			if (lastState_key10) {
				FIFO_PUSH(notes, 158);
				FIFO_PUSH(durations, duration_note10);
				lastState_key10 = 0x0;
			}
			if (lastState_key11) {
				FIFO_PUSH(notes, 159);
				FIFO_PUSH(durations, duration_note11);
				lastState_key11 = 0x0;
			}
			if (lastState_key12) {
				FIFO_PUSH(notes, 160);
				FIFO_PUSH(durations, duration_note12);
				lastState_key12 = 0x0;
			}
			if (lastState_key13) {
				FIFO_PUSH(notes, 161);
				FIFO_PUSH(durations, duration_note13);
				lastState_key13 = 0x0;
			}
			if (lastState_key14) {
				FIFO_PUSH(notes, 162);
				FIFO_PUSH(durations, duration_note14);
				lastState_key14 = 0x0;
			}
			if (lastState_key15) {
				FIFO_PUSH(notes, 163);
				FIFO_PUSH(durations, duration_note15);
				lastState_key15 = 0x0;
			}
			if (lastState_key16) {
				FIFO_PUSH(notes, 164);
				FIFO_PUSH(durations, duration_note16);
				lastState_key16 = 0x0;
			}
			duration_note9 = 0x0;
			duration_note10 = 0x0;
			duration_note11 = 0x0;
			duration_note12 = 0x0;
			duration_note13 = 0x0;
			duration_note14 = 0x0;
			duration_note15 = 0x0;
			duration_note16 = 0x0;
		}
	}
	lastState2 = d1;
	/* 3 chunk */

	GPIOB->BSRRH = GPIO_Pin_13; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_13;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOB->BSRRH = GPIO_Pin_12;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_12;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*17 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key17) {
				} else {
					FIFO_PUSH(notes, 37);
					FIFO_PUSH(durations, duration_note17);
					lastState_key17 = 0x1;
					duration_note17 = 0x0;
				}
			} else {
				if (duration_note17 < 0xFFFF)
				duration_note17++;
			}

		} else {
			if (lastState_key17) {
				FIFO_PUSH(notes, 165);
				FIFO_PUSH(durations, duration_note17);
				lastState_key17 = 0x0;
				duration_note17 = 0x0;
			} else {
				duration_note17 = 0x0;
			}
		}
		/*18 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key18) {
				} else {
					FIFO_PUSH(notes, 38);
					FIFO_PUSH(durations, duration_note18);
					lastState_key18 = 0x1;
					duration_note18 = 0x0;
				}
			} else {
				if (duration_note18 < 0xFFFF)
				duration_note18++;
			}

		} else {
			if (lastState_key18) {
				FIFO_PUSH(notes, 166);
				FIFO_PUSH(durations, duration_note18);
				lastState_key18 = 0x0;
				duration_note18 = 0x0;
			} else {
				duration_note18 = 0x0;
			}
		}
		/*19 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key19) {
				} else {
					FIFO_PUSH(notes, 39);
					FIFO_PUSH(durations, duration_note19);
					lastState_key19 = 0x1;
					duration_note19 = 0x0;
				}
			} else {
				if (duration_note19 < 0xFFFF)
				duration_note19++;
			}

		} else {
			if (lastState_key19) {
				FIFO_PUSH(notes, 167);
				FIFO_PUSH(durations, duration_note19);
				lastState_key19 = 0x0;
				duration_note19 = 0x0;
			} else {
				duration_note19 = 0x0;
			}
		}
		/*20 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key20) {
				} else {
					FIFO_PUSH(notes, 40);
					FIFO_PUSH(durations, duration_note20);
					lastState_key20 = 0x1;
					duration_note20 = 0x0;
				}
			} else {
				if (duration_note20 < 0xFFFF)
				duration_note20++;
			}

		} else {
			if (lastState_key20) {
				FIFO_PUSH(notes, 168);
				FIFO_PUSH(durations, duration_note20);
				lastState_key20 = 0x0;
				duration_note20 = 0x0;
			} else {
				duration_note20 = 0x0;
			}
		}
		/*21 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key21) {
				} else {
					FIFO_PUSH(notes, 41);
					FIFO_PUSH(durations, duration_note21);
					lastState_key21 = 0x1;
					duration_note21 = 0x0;
				}
			} else {
				if (duration_note21 < 0xFFFF)
				duration_note21++;
			}

		} else {
			if (lastState_key21) {
				FIFO_PUSH(notes, 169);
				FIFO_PUSH(durations, duration_note21);
				lastState_key21 = 0x0;
				duration_note21 = 0x0;
			} else {
				duration_note21 = 0x0;
			}
		}
		/*22 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key22) {
				} else {
					FIFO_PUSH(notes, 42);
					FIFO_PUSH(durations, duration_note22);
					lastState_key22 = 0x1;
					duration_note22 = 0x0;
				}
			} else {
				if (duration_note22 < 0xFFFF)
				duration_note22++;
			}

		} else {
			if (lastState_key22) {
				FIFO_PUSH(notes, 170);
				FIFO_PUSH(durations, duration_note22);
				lastState_key22 = 0x0;
				duration_note22 = 0x0;
			} else {
				duration_note22 = 0x0;
			}
		}
		/*23 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key23) {
				} else {
					FIFO_PUSH(notes, 43);
					FIFO_PUSH(durations, duration_note23);
					lastState_key23 = 0x1;
					duration_note23 = 0x0;
				}
			} else {
				if (duration_note23 < 0xFFFF)
				duration_note23++;
			}

		} else {
			if (lastState_key23) {
				FIFO_PUSH(notes, 171);
				FIFO_PUSH(durations, duration_note23);
				lastState_key23 = 0x0;
				duration_note23 = 0x0;
			} else {
				duration_note23 = 0x0;
			}
		}
		/*24 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key24) {
				} else {
					FIFO_PUSH(notes, 44);
					FIFO_PUSH(durations, duration_note24);
					lastState_key24 = 0x1;
					duration_note24 = 0x0;
				}
			} else {
				if (duration_note24 < 0xFFFF)
				duration_note24++;
			}

		} else {
			if (lastState_key24) {
				FIFO_PUSH(notes, 172);
				FIFO_PUSH(durations, duration_note24);
				lastState_key24 = 0x0;
				duration_note24 = 0x0;
			} else {
				duration_note24 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState3) {
			if (lastState_key17) {
				FIFO_PUSH(notes, 165);
				FIFO_PUSH(durations, duration_note17);
				lastState_key17 = 0x0;
			}
			if (lastState_key18) {
				FIFO_PUSH(notes, 166);
				FIFO_PUSH(durations, duration_note18);
				lastState_key18 = 0x0;
			}
			if (lastState_key19) {
				FIFO_PUSH(notes, 167);
				FIFO_PUSH(durations, duration_note19);
				lastState_key19 = 0x0;
			}
			if (lastState_key20) {
				FIFO_PUSH(notes, 168);
				FIFO_PUSH(durations, duration_note20);
				lastState_key20 = 0x0;
			}
			if (lastState_key21) {
				FIFO_PUSH(notes, 169);
				FIFO_PUSH(durations, duration_note21);
				lastState_key21 = 0x0;
			}
			if (lastState_key22) {
				FIFO_PUSH(notes, 170);
				FIFO_PUSH(durations, duration_note22);
				lastState_key22 = 0x0;
			}
			if (lastState_key23) {
				FIFO_PUSH(notes, 171);
				FIFO_PUSH(durations, duration_note23);
				lastState_key23 = 0x0;
			}
			if (lastState_key24) {
				FIFO_PUSH(notes, 172);
				FIFO_PUSH(durations, duration_note24);
				lastState_key24 = 0x0;
			}
			duration_note17 = 0x0;
			duration_note18 = 0x0;
			duration_note19 = 0x0;
			duration_note20 = 0x0;
			duration_note21 = 0x0;
			duration_note22 = 0x0;
			duration_note23 = 0x0;
			duration_note24 = 0x0;
		}
	}
	lastState3 = d1;
	/* 4 chunk */

	GPIOB->BSRRH = GPIO_Pin_15; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_15;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOB->BSRRH = GPIO_Pin_14;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_14;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*25 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key25) {
				} else {
					FIFO_PUSH(notes, 45);
					FIFO_PUSH(durations, duration_note25);
					lastState_key25 = 0x1;
					duration_note25 = 0x0;
				}
			} else {
				if (duration_note25 < 0xFFFF)
				duration_note25++;
			}

		} else {
			if (lastState_key25) {
				FIFO_PUSH(notes, 173);
				FIFO_PUSH(durations, duration_note25);
				lastState_key25 = 0x0;
				duration_note25 = 0x0;
			} else {
				duration_note25 = 0x0;
			}
		}
		/*26 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key26) {
				} else {
					FIFO_PUSH(notes, 46);
					FIFO_PUSH(durations, duration_note26);
					lastState_key26 = 0x1;
					duration_note26 = 0x0;
				}
			} else {
				if (duration_note26 < 0xFFFF)
				duration_note26++;
			}

		} else {
			if (lastState_key26) {
				FIFO_PUSH(notes, 174);
				FIFO_PUSH(durations, duration_note26);
				lastState_key26 = 0x0;
				duration_note26 = 0x0;
			} else {
				duration_note26 = 0x0;
			}
		}
		/*27 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key27) {
				} else {
					FIFO_PUSH(notes, 47);
					FIFO_PUSH(durations, duration_note27);
					lastState_key27 = 0x1;
					duration_note27 = 0x0;
				}
			} else {
				if (duration_note27 < 0xFFFF)
				duration_note27++;
			}

		} else {
			if (lastState_key27) {
				FIFO_PUSH(notes, 175);
				FIFO_PUSH(durations, duration_note27);
				lastState_key27 = 0x0;
				duration_note27 = 0x0;
			} else {
				duration_note27 = 0x0;
			}
		}
		/*28 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key28) {
				} else {
					FIFO_PUSH(notes, 48);
					FIFO_PUSH(durations, duration_note28);
					lastState_key28 = 0x1;
					duration_note28 = 0x0;
				}
			} else {
				if (duration_note28 < 0xFFFF)
				duration_note28++;
			}

		} else {
			if (lastState_key28) {
				FIFO_PUSH(notes, 176);
				FIFO_PUSH(durations, duration_note28);
				lastState_key28 = 0x0;
				duration_note28 = 0x0;
			} else {
				duration_note28 = 0x0;
			}
		}
		/*29 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key29) {
				} else {
					FIFO_PUSH(notes, 49);
					FIFO_PUSH(durations, duration_note29);
					lastState_key29 = 0x1;
					duration_note29 = 0x0;
				}
			} else {
				if (duration_note29 < 0xFFFF)
				duration_note29++;
			}

		} else {
			if (lastState_key29) {
				FIFO_PUSH(notes, 177);
				FIFO_PUSH(durations, duration_note29);
				lastState_key29 = 0x0;
				duration_note29 = 0x0;
			} else {
				duration_note29 = 0x0;
			}
		}
		/*30 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key30) {
				} else {
					FIFO_PUSH(notes, 50);
					FIFO_PUSH(durations, duration_note30);
					lastState_key30 = 0x1;
					duration_note30 = 0x0;
				}
			} else {
				if (duration_note30 < 0xFFFF)
				duration_note30++;
			}

		} else {
			if (lastState_key30) {
				FIFO_PUSH(notes, 178);
				FIFO_PUSH(durations, duration_note30);
				lastState_key30 = 0x0;
				duration_note30 = 0x0;
			} else {
				duration_note30 = 0x0;
			}
		}
		/*31 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key31) {
				} else {
					FIFO_PUSH(notes, 51);
					FIFO_PUSH(durations, duration_note31);
					lastState_key31 = 0x1;
					duration_note31 = 0x0;
				}
			} else {
				if (duration_note31 < 0xFFFF)
				duration_note31++;
			}

		} else {
			if (lastState_key31) {
				FIFO_PUSH(notes, 179);
				FIFO_PUSH(durations, duration_note31);
				lastState_key31 = 0x0;
				duration_note31 = 0x0;
			} else {
				duration_note31 = 0x0;
			}
		}
		/*32 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key32) {
				} else {
					FIFO_PUSH(notes, 52);
					FIFO_PUSH(durations, duration_note32);
					lastState_key32 = 0x1;
					duration_note32 = 0x0;
				}
			} else {
				if (duration_note32 < 0xFFFF)
				duration_note32++;
			}

		} else {
			if (lastState_key32) {
				FIFO_PUSH(notes, 180);
				FIFO_PUSH(durations, duration_note32);
				lastState_key32 = 0x0;
				duration_note32 = 0x0;
			} else {
				duration_note32 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState4) {
			if (lastState_key25) {
				FIFO_PUSH(notes, 173);
				FIFO_PUSH(durations, duration_note25);
				lastState_key25 = 0x0;
			}
			if (lastState_key26) {
				FIFO_PUSH(notes, 174);
				FIFO_PUSH(durations, duration_note26);
				lastState_key26 = 0x0;
			}
			if (lastState_key27) {
				FIFO_PUSH(notes, 175);
				FIFO_PUSH(durations, duration_note27);
				lastState_key27 = 0x0;
			}
			if (lastState_key28) {
				FIFO_PUSH(notes, 176);
				FIFO_PUSH(durations, duration_note28);
				lastState_key28 = 0x0;
			}
			if (lastState_key29) {
				FIFO_PUSH(notes, 177);
				FIFO_PUSH(durations, duration_note29);
				lastState_key29 = 0x0;
			}
			if (lastState_key30) {
				FIFO_PUSH(notes, 178);
				FIFO_PUSH(durations, duration_note30);
				lastState_key30 = 0x0;
			}
			if (lastState_key31) {
				FIFO_PUSH(notes, 179);
				FIFO_PUSH(durations, duration_note31);
				lastState_key31 = 0x0;
			}
			if (lastState_key32) {
				FIFO_PUSH(notes, 180);
				FIFO_PUSH(durations, duration_note32);
				lastState_key32 = 0x0;
			}
			duration_note25 = 0x0;
			duration_note26 = 0x0;
			duration_note27 = 0x0;
			duration_note28 = 0x0;
			duration_note29 = 0x0;
			duration_note30 = 0x0;
			duration_note31 = 0x0;
			duration_note32 = 0x0;
		}
	}
	lastState4 = d1;
	/* 5 chunk */

	GPIOD->BSRRH = GPIO_Pin_9; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOD->BSRRL = GPIO_Pin_9;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOD->BSRRH = GPIO_Pin_8;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOD->BSRRL = GPIO_Pin_8;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*33 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key33) {
				} else {
					FIFO_PUSH(notes, 53);
					FIFO_PUSH(durations, duration_note33);
					lastState_key33 = 0x1;
					duration_note33 = 0x0;
				}
			} else {
				if (duration_note33 < 0xFFFF)
				duration_note33++;
			}

		} else {
			if (lastState_key33) {
				FIFO_PUSH(notes, 181);
				FIFO_PUSH(durations, duration_note33);
				lastState_key33 = 0x0;
				duration_note33 = 0x0;
			} else {
				duration_note33 = 0x0;
			}
		}
		/*34 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key34) {
				} else {
					FIFO_PUSH(notes, 54);
					FIFO_PUSH(durations, duration_note34);
					lastState_key34 = 0x1;
					duration_note34 = 0x0;
				}
			} else {
				if (duration_note34 < 0xFFFF)
				duration_note34++;
			}

		} else {
			if (lastState_key34) {
				FIFO_PUSH(notes, 182);
				FIFO_PUSH(durations, duration_note34);
				lastState_key34 = 0x0;
				duration_note34 = 0x0;
			} else {
				duration_note34 = 0x0;
			}
		}
		/*35 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key35) {
				} else {
					FIFO_PUSH(notes, 55);
					FIFO_PUSH(durations, duration_note35);
					lastState_key35 = 0x1;
					duration_note35 = 0x0;
				}
			} else {
				if (duration_note35 < 0xFFFF)
				duration_note35++;
			}

		} else {
			if (lastState_key35) {
				FIFO_PUSH(notes, 183);
				FIFO_PUSH(durations, duration_note35);
				lastState_key35 = 0x0;
				duration_note35 = 0x0;
			} else {
				duration_note35 = 0x0;
			}
		}
		/*36 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key36) {
				} else {
					FIFO_PUSH(notes, 56);
					FIFO_PUSH(durations, duration_note36);
					lastState_key36 = 0x1;
					duration_note36 = 0x0;
				}
			} else {
				if (duration_note36 < 0xFFFF)
				duration_note36++;
			}

		} else {
			if (lastState_key36) {
				FIFO_PUSH(notes, 184);
				FIFO_PUSH(durations, duration_note36);
				lastState_key36 = 0x0;
				duration_note36 = 0x0;
			} else {
				duration_note36 = 0x0;
			}
		}
		/*37 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key37) {
				} else {
					FIFO_PUSH(notes, 57);
					FIFO_PUSH(durations, duration_note37);
					lastState_key37 = 0x1;
					duration_note37 = 0x0;
				}
			} else {
				if (duration_note37 < 0xFFFF)
				duration_note37++;
			}

		} else {
			if (lastState_key37) {
				FIFO_PUSH(notes, 185);
				FIFO_PUSH(durations, duration_note37);
				lastState_key37 = 0x0;
				duration_note37 = 0x0;
			} else {
				duration_note37 = 0x0;
			}
		}
		/*38 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key38) {
				} else {
					FIFO_PUSH(notes, 58);
					FIFO_PUSH(durations, duration_note38);
					lastState_key38 = 0x1;
					duration_note38 = 0x0;
				}
			} else {
				if (duration_note38 < 0xFFFF)
				duration_note38++;
			}

		} else {
			if (lastState_key38) {
				FIFO_PUSH(notes, 186);
				FIFO_PUSH(durations, duration_note38);
				lastState_key38 = 0x0;
				duration_note38 = 0x0;
			} else {
				duration_note38 = 0x0;
			}
		}
		/*39 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key39) {
				} else {
					FIFO_PUSH(notes, 59);
					FIFO_PUSH(durations, duration_note39);
					lastState_key39 = 0x1;
					duration_note39 = 0x0;
				}
			} else {
				if (duration_note39 < 0xFFFF)
				duration_note39++;
			}

		} else {
			if (lastState_key39) {
				FIFO_PUSH(notes, 187);
				FIFO_PUSH(durations, duration_note39);
				lastState_key39 = 0x0;
				duration_note39 = 0x0;
			} else {
				duration_note39 = 0x0;
			}
		}
		/*40 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key40) {
				} else {
					FIFO_PUSH(notes, 60);
					FIFO_PUSH(durations, duration_note40);
					lastState_key40 = 0x1;
					duration_note40 = 0x0;
				}
			} else {
				if (duration_note40 < 0xFFFF)
				duration_note40++;
			}

		} else {
			if (lastState_key40) {
				FIFO_PUSH(notes, 188);
				FIFO_PUSH(durations, duration_note40);
				lastState_key40 = 0x0;
				duration_note40 = 0x0;
			} else {
				duration_note40 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState5) {
			if (lastState_key33) {
				FIFO_PUSH(notes, 181);
				FIFO_PUSH(durations, duration_note33);
				lastState_key33 = 0x0;
			}
			if (lastState_key34) {
				FIFO_PUSH(notes, 182);
				FIFO_PUSH(durations, duration_note34);
				lastState_key34 = 0x0;
			}
			if (lastState_key35) {
				FIFO_PUSH(notes, 183);
				FIFO_PUSH(durations, duration_note35);
				lastState_key35 = 0x0;
			}
			if (lastState_key36) {
				FIFO_PUSH(notes, 184);
				FIFO_PUSH(durations, duration_note36);
				lastState_key36 = 0x0;
			}
			if (lastState_key37) {
				FIFO_PUSH(notes, 185);
				FIFO_PUSH(durations, duration_note37);
				lastState_key37 = 0x0;
			}
			if (lastState_key38) {
				FIFO_PUSH(notes, 186);
				FIFO_PUSH(durations, duration_note38);
				lastState_key38 = 0x0;
			}
			if (lastState_key39) {
				FIFO_PUSH(notes, 187);
				FIFO_PUSH(durations, duration_note39);
				lastState_key39 = 0x0;
			}
			if (lastState_key40) {
				FIFO_PUSH(notes, 188);
				FIFO_PUSH(durations, duration_note40);
				lastState_key40 = 0x0;
			}
			duration_note33 = 0x0;
			duration_note34 = 0x0;
			duration_note35 = 0x0;
			duration_note36 = 0x0;
			duration_note37 = 0x0;
			duration_note38 = 0x0;
			duration_note39 = 0x0;
			duration_note40 = 0x0;
		}
	}
	lastState5 = d1;
	/* 6 chunk */

	GPIOC->BSRRH = GPIO_Pin_4; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOC->BSRRL = GPIO_Pin_4;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOC->BSRRH = GPIO_Pin_5;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOC->BSRRL = GPIO_Pin_5;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*41 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key41) {
				} else {
					FIFO_PUSH(notes, 61);
					FIFO_PUSH(durations, duration_note41);
					lastState_key41 = 0x1;
					duration_note41 = 0x0;
				}
			} else {
				if (duration_note41 < 0xFFFF)
				duration_note41++;
			}

		} else {
			if (lastState_key41) {
				FIFO_PUSH(notes, 189);
				FIFO_PUSH(durations, duration_note41);
				lastState_key41 = 0x0;
				duration_note41 = 0x0;
			} else {
				duration_note41 = 0x0;
			}
		}
		/*42 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key42) {
				} else {
					FIFO_PUSH(notes, 62);
					FIFO_PUSH(durations, duration_note42);
					lastState_key42 = 0x1;
					duration_note42 = 0x0;
				}
			} else {
				if (duration_note42 < 0xFFFF)
				duration_note42++;
			}

		} else {
			if (lastState_key42) {
				FIFO_PUSH(notes, 190);
				FIFO_PUSH(durations, duration_note42);
				lastState_key42 = 0x0;
				duration_note42 = 0x0;
			} else {
				duration_note42 = 0x0;
			}
		}
		/*43 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key43) {
				} else {
					FIFO_PUSH(notes, 63);
					FIFO_PUSH(durations, duration_note43);
					lastState_key43 = 0x1;
					duration_note43 = 0x0;
				}
			} else {
				if (duration_note43 < 0xFFFF)
				duration_note43++;
			}

		} else {
			if (lastState_key43) {
				FIFO_PUSH(notes, 191);
				FIFO_PUSH(durations, duration_note43);
				lastState_key43 = 0x0;
				duration_note43 = 0x0;
			} else {
				duration_note43 = 0x0;
			}
		}
		/*44 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key44) {
				} else {
					FIFO_PUSH(notes, 64);
					FIFO_PUSH(durations, duration_note44);
					lastState_key44 = 0x1;
					duration_note44 = 0x0;
				}
			} else {
				if (duration_note44 < 0xFFFF)
				duration_note44++;
			}

		} else {
			if (lastState_key44) {
				FIFO_PUSH(notes, 192);
				FIFO_PUSH(durations, duration_note44);
				lastState_key44 = 0x0;
				duration_note44 = 0x0;
			} else {
				duration_note44 = 0x0;
			}
		}
		/*45 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key45) {
				} else {
					FIFO_PUSH(notes, 65);
					FIFO_PUSH(durations, duration_note45);
					lastState_key45 = 0x1;
					duration_note45 = 0x0;
				}
			} else {
				if (duration_note45 < 0xFFFF)
				duration_note45++;
			}

		} else {
			if (lastState_key45) {
				FIFO_PUSH(notes, 193);
				FIFO_PUSH(durations, duration_note45);
				lastState_key45 = 0x0;
				duration_note45 = 0x0;
			} else {
				duration_note45 = 0x0;
			}
		}
		/*46 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key46) {
				} else {
					FIFO_PUSH(notes, 66);
					FIFO_PUSH(durations, duration_note46);
					lastState_key46 = 0x1;
					duration_note46 = 0x0;
				}
			} else {
				if (duration_note46 < 0xFFFF)
				duration_note46++;
			}

		} else {
			if (lastState_key46) {
				FIFO_PUSH(notes, 194);
				FIFO_PUSH(durations, duration_note46);
				lastState_key46 = 0x0;
				duration_note46 = 0x0;
			} else {
				duration_note46 = 0x0;
			}
		}
		/*47 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key47) {
				} else {
					FIFO_PUSH(notes, 67);
					FIFO_PUSH(durations, duration_note47);
					lastState_key47 = 0x1;
					duration_note47 = 0x0;
				}
			} else {
				if (duration_note47 < 0xFFFF)
				duration_note47++;
			}

		} else {
			if (lastState_key47) {
				FIFO_PUSH(notes, 195);
				FIFO_PUSH(durations, duration_note47);
				lastState_key47 = 0x0;
				duration_note47 = 0x0;
			} else {
				duration_note47 = 0x0;
			}
		}
		/*48 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key48) {
				} else {
					FIFO_PUSH(notes, 68);
					FIFO_PUSH(durations, duration_note48);
					lastState_key48 = 0x1;
					duration_note48 = 0x0;
				}
			} else {
				if (duration_note48 < 0xFFFF)
				duration_note48++;
			}

		} else {
			if (lastState_key48) {
				FIFO_PUSH(notes, 196);
				FIFO_PUSH(durations, duration_note48);
				lastState_key48 = 0x0;
				duration_note48 = 0x0;
			} else {
				duration_note48 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState6) {
			if (lastState_key41) {
				FIFO_PUSH(notes, 189);
				FIFO_PUSH(durations, duration_note41);
				lastState_key41 = 0x0;
			}
			if (lastState_key42) {
				FIFO_PUSH(notes, 190);
				FIFO_PUSH(durations, duration_note42);
				lastState_key42 = 0x0;
			}
			if (lastState_key43) {
				FIFO_PUSH(notes, 191);
				FIFO_PUSH(durations, duration_note43);
				lastState_key43 = 0x0;
			}
			if (lastState_key44) {
				FIFO_PUSH(notes, 192);
				FIFO_PUSH(durations, duration_note44);
				lastState_key44 = 0x0;
			}
			if (lastState_key45) {
				FIFO_PUSH(notes, 193);
				FIFO_PUSH(durations, duration_note45);
				lastState_key45 = 0x0;
			}
			if (lastState_key46) {
				FIFO_PUSH(notes, 194);
				FIFO_PUSH(durations, duration_note46);
				lastState_key46 = 0x0;
			}
			if (lastState_key47) {
				FIFO_PUSH(notes, 195);
				FIFO_PUSH(durations, duration_note47);
				lastState_key47 = 0x0;
			}
			if (lastState_key48) {
				FIFO_PUSH(notes, 196);
				FIFO_PUSH(durations, duration_note48);
				lastState_key48 = 0x0;
			}
			duration_note41 = 0x0;
			duration_note42 = 0x0;
			duration_note43 = 0x0;
			duration_note44 = 0x0;
			duration_note45 = 0x0;
			duration_note46 = 0x0;
			duration_note47 = 0x0;
			duration_note48 = 0x0;
		}
	}
	lastState6 = d1;
	/* 7 chunk */

	GPIOB->BSRRH = GPIO_Pin_0; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOB->BSRRL = GPIO_Pin_0;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOB->BSRRH = GPIO_Pin_1;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_1;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*49 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key49) {
				} else {
					FIFO_PUSH(notes, 69);
					FIFO_PUSH(durations, duration_note49);
					lastState_key49 = 0x1;
					duration_note49 = 0x0;
				}
			} else {
				if (duration_note49 < 0xFFFF)
				duration_note49++;
			}

		} else {
			if (lastState_key49) {
				FIFO_PUSH(notes, 197);
				FIFO_PUSH(durations, duration_note49);
				lastState_key49 = 0x0;
				duration_note49 = 0x0;
			} else {
				duration_note49 = 0x0;
			}
		}
		/*50 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key50) {
				} else {
					FIFO_PUSH(notes, 70);
					FIFO_PUSH(durations, duration_note50);
					lastState_key50 = 0x1;
					duration_note50 = 0x0;
				}
			} else {
				if (duration_note50 < 0xFFFF)
				duration_note50++;
			}

		} else {
			if (lastState_key50) {
				FIFO_PUSH(notes, 198);
				FIFO_PUSH(durations, duration_note50);
				lastState_key50 = 0x0;
				duration_note50 = 0x0;
			} else {
				duration_note50 = 0x0;
			}
		}
		/*51 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key51) {
				} else {
					FIFO_PUSH(notes, 71);
					FIFO_PUSH(durations, duration_note51);
					lastState_key51 = 0x1;
					duration_note51 = 0x0;
				}
			} else {
				if (duration_note51 < 0xFFFF)
				duration_note51++;
			}

		} else {
			if (lastState_key51) {
				FIFO_PUSH(notes, 199);
				FIFO_PUSH(durations, duration_note51);
				lastState_key51 = 0x0;
				duration_note51 = 0x0;
			} else {
				duration_note51 = 0x0;
			}
		}
		/*52 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key52) {
				} else {
					FIFO_PUSH(notes, 72);
					FIFO_PUSH(durations, duration_note52);
					lastState_key52 = 0x1;
					duration_note52 = 0x0;
				}
			} else {
				if (duration_note52 < 0xFFFF)
				duration_note52++;
			}

		} else {
			if (lastState_key52) {
				FIFO_PUSH(notes, 200);
				FIFO_PUSH(durations, duration_note52);
				lastState_key52 = 0x0;
				duration_note52 = 0x0;
			} else {
				duration_note52 = 0x0;
			}
		}
		/*53 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key53) {
				} else {
					FIFO_PUSH(notes, 73);
					FIFO_PUSH(durations, duration_note53);
					lastState_key53 = 0x1;
					duration_note53 = 0x0;
				}
			} else {
				if (duration_note53 < 0xFFFF)
				duration_note53++;
			}

		} else {
			if (lastState_key53) {
				FIFO_PUSH(notes, 201);
				FIFO_PUSH(durations, duration_note53);
				lastState_key53 = 0x0;
				duration_note53 = 0x0;
			} else {
				duration_note53 = 0x0;
			}
		}
		/*54 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key54) {
				} else {
					FIFO_PUSH(notes, 74);
					FIFO_PUSH(durations, duration_note54);
					lastState_key54 = 0x1;
					duration_note54 = 0x0;
				}
			} else {
				if (duration_note54 < 0xFFFF)
				duration_note54++;
			}

		} else {
			if (lastState_key54) {
				FIFO_PUSH(notes, 202);
				FIFO_PUSH(durations, duration_note54);
				lastState_key54 = 0x0;
				duration_note54 = 0x0;
			} else {
				duration_note54 = 0x0;
			}
		}
		/*55 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key55) {
				} else {
					FIFO_PUSH(notes, 75);
					FIFO_PUSH(durations, duration_note55);
					lastState_key55 = 0x1;
					duration_note55 = 0x0;
				}
			} else {
				if (duration_note55 < 0xFFFF)
				duration_note55++;
			}

		} else {
			if (lastState_key55) {
				FIFO_PUSH(notes, 203);
				FIFO_PUSH(durations, duration_note55);
				lastState_key55 = 0x0;
				duration_note55 = 0x0;
			} else {
				duration_note55 = 0x0;
			}
		}
		/*56 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key56) {
				} else {
					FIFO_PUSH(notes, 76);
					FIFO_PUSH(durations, duration_note56);
					lastState_key56 = 0x1;
					duration_note56 = 0x0;
				}
			} else {
				if (duration_note56 < 0xFFFF)
				duration_note56++;
			}

		} else {
			if (lastState_key56) {
				FIFO_PUSH(notes, 204);
				FIFO_PUSH(durations, duration_note56);
				lastState_key56 = 0x0;
				duration_note56 = 0x0;
			} else {
				duration_note56 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState7) {
			if (lastState_key49) {
				FIFO_PUSH(notes, 197);
				FIFO_PUSH(durations, duration_note49);
				lastState_key49 = 0x0;
			}
			if (lastState_key50) {
				FIFO_PUSH(notes, 198);
				FIFO_PUSH(durations, duration_note50);
				lastState_key50 = 0x0;
			}
			if (lastState_key51) {
				FIFO_PUSH(notes, 199);
				FIFO_PUSH(durations, duration_note51);
				lastState_key51 = 0x0;
			}
			if (lastState_key52) {
				FIFO_PUSH(notes, 200);
				FIFO_PUSH(durations, duration_note52);
				lastState_key52 = 0x0;
			}
			if (lastState_key53) {
				FIFO_PUSH(notes, 201);
				FIFO_PUSH(durations, duration_note53);
				lastState_key53 = 0x0;
			}
			if (lastState_key54) {
				FIFO_PUSH(notes, 202);
				FIFO_PUSH(durations, duration_note54);
				lastState_key54 = 0x0;
			}
			if (lastState_key55) {
				FIFO_PUSH(notes, 203);
				FIFO_PUSH(durations, duration_note55);
				lastState_key55 = 0x0;
			}
			if (lastState_key56) {
				FIFO_PUSH(notes, 204);
				FIFO_PUSH(durations, duration_note56);
				lastState_key56 = 0x0;
			}
			duration_note49 = 0x0;
			duration_note50 = 0x0;
			duration_note51 = 0x0;
			duration_note52 = 0x0;
			duration_note53 = 0x0;
			duration_note54 = 0x0;
			duration_note55 = 0x0;
			duration_note56 = 0x0;
		}
	}
	lastState7 = d1;
	/* 8 chunk */

	GPIOE->BSRRH = GPIO_Pin_7; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_7;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOB->BSRRH = GPIO_Pin_2;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOB->BSRRL = GPIO_Pin_2;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*57 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key57) {
				} else {
					FIFO_PUSH(notes, 77);
					FIFO_PUSH(durations, duration_note57);
					lastState_key57 = 0x1;
					duration_note57 = 0x0;
				}
			} else {
				if (duration_note57 < 0xFFFF)
				duration_note57++;
			}

		} else {
			if (lastState_key57) {
				FIFO_PUSH(notes, 205);
				FIFO_PUSH(durations, duration_note57);
				lastState_key57 = 0x0;
				duration_note57 = 0x0;
			} else {
				duration_note57 = 0x0;
			}
		}
		/*58 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key58) {
				} else {
					FIFO_PUSH(notes, 78);
					FIFO_PUSH(durations, duration_note58);
					lastState_key58 = 0x1;
					duration_note58 = 0x0;
				}
			} else {
				if (duration_note58 < 0xFFFF)
				duration_note58++;
			}

		} else {
			if (lastState_key58) {
				FIFO_PUSH(notes, 206);
				FIFO_PUSH(durations, duration_note58);
				lastState_key58 = 0x0;
				duration_note58 = 0x0;
			} else {
				duration_note58 = 0x0;
			}
		}
		/*59 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key59) {
				} else {
					FIFO_PUSH(notes, 79);
					FIFO_PUSH(durations, duration_note59);
					lastState_key59 = 0x1;
					duration_note59 = 0x0;
				}
			} else {
				if (duration_note59 < 0xFFFF)
				duration_note59++;
			}

		} else {
			if (lastState_key59) {
				FIFO_PUSH(notes, 207);
				FIFO_PUSH(durations, duration_note59);
				lastState_key59 = 0x0;
				duration_note59 = 0x0;
			} else {
				duration_note59 = 0x0;
			}
		}
		/*60 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key60) {
				} else {
					FIFO_PUSH(notes, 80);
					FIFO_PUSH(durations, duration_note60);
					lastState_key60 = 0x1;
					duration_note60 = 0x0;
				}
			} else {
				if (duration_note60 < 0xFFFF)
				duration_note60++;
			}

		} else {
			if (lastState_key60) {
				FIFO_PUSH(notes, 208);
				FIFO_PUSH(durations, duration_note60);
				lastState_key60 = 0x0;
				duration_note60 = 0x0;
			} else {
				duration_note60 = 0x0;
			}
		}
		/*61 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key61) {
				} else {
					FIFO_PUSH(notes, 81);
					FIFO_PUSH(durations, duration_note61);
					lastState_key61 = 0x1;
					duration_note61 = 0x0;
				}
			} else {
				if (duration_note61 < 0xFFFF)
				duration_note61++;
			}

		} else {
			if (lastState_key61) {
				FIFO_PUSH(notes, 209);
				FIFO_PUSH(durations, duration_note61);
				lastState_key61 = 0x0;
				duration_note61 = 0x0;
			} else {
				duration_note61 = 0x0;
			}
		}
		/*62 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key62) {
				} else {
					FIFO_PUSH(notes, 82);
					FIFO_PUSH(durations, duration_note62);
					lastState_key62 = 0x1;
					duration_note62 = 0x0;
				}
			} else {
				if (duration_note62 < 0xFFFF)
				duration_note62++;
			}

		} else {
			if (lastState_key62) {
				FIFO_PUSH(notes, 210);
				FIFO_PUSH(durations, duration_note62);
				lastState_key62 = 0x0;
				duration_note62 = 0x0;
			} else {
				duration_note62 = 0x0;
			}
		}
		/*63 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key63) {
				} else {
					FIFO_PUSH(notes, 83);
					FIFO_PUSH(durations, duration_note63);
					lastState_key63 = 0x1;
					duration_note63 = 0x0;
				}
			} else {
				if (duration_note63 < 0xFFFF)
				duration_note63++;
			}

		} else {
			if (lastState_key63) {
				FIFO_PUSH(notes, 211);
				FIFO_PUSH(durations, duration_note63);
				lastState_key63 = 0x0;
				duration_note63 = 0x0;
			} else {
				duration_note63 = 0x0;
			}
		}
		/*64 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key64) {
				} else {
					FIFO_PUSH(notes, 84);
					FIFO_PUSH(durations, duration_note64);
					lastState_key64 = 0x1;
					duration_note64 = 0x0;
				}
			} else {
				if (duration_note64 < 0xFFFF)
				duration_note64++;
			}

		} else {
			if (lastState_key64) {
				FIFO_PUSH(notes, 212);
				FIFO_PUSH(durations, duration_note64);
				lastState_key64 = 0x0;
				duration_note64 = 0x0;
			} else {
				duration_note64 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState8) {
			if (lastState_key57) {
				FIFO_PUSH(notes, 205);
				FIFO_PUSH(durations, duration_note57);
				lastState_key57 = 0x0;
			}
			if (lastState_key58) {
				FIFO_PUSH(notes, 206);
				FIFO_PUSH(durations, duration_note58);
				lastState_key58 = 0x0;
			}
			if (lastState_key59) {
				FIFO_PUSH(notes, 207);
				FIFO_PUSH(durations, duration_note59);
				lastState_key59 = 0x0;
			}
			if (lastState_key60) {
				FIFO_PUSH(notes, 208);
				FIFO_PUSH(durations, duration_note60);
				lastState_key60 = 0x0;
			}
			if (lastState_key61) {
				FIFO_PUSH(notes, 209);
				FIFO_PUSH(durations, duration_note61);
				lastState_key61 = 0x0;
			}
			if (lastState_key62) {
				FIFO_PUSH(notes, 210);
				FIFO_PUSH(durations, duration_note62);
				lastState_key62 = 0x0;
			}
			if (lastState_key63) {
				FIFO_PUSH(notes, 211);
				FIFO_PUSH(durations, duration_note63);
				lastState_key63 = 0x0;
			}
			if (lastState_key64) {
				FIFO_PUSH(notes, 212);
				FIFO_PUSH(durations, duration_note64);
				lastState_key64 = 0x0;
			}
			duration_note57 = 0x0;
			duration_note58 = 0x0;
			duration_note59 = 0x0;
			duration_note60 = 0x0;
			duration_note61 = 0x0;
			duration_note62 = 0x0;
			duration_note63 = 0x0;
			duration_note64 = 0x0;
		}
	}
	lastState8 = d1;
	/* 9 chunk */

	GPIOE->BSRRH = GPIO_Pin_9; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_9;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOE->BSRRH = GPIO_Pin_8;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_8;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*65 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key65) {
				} else {
					FIFO_PUSH(notes, 85);
					FIFO_PUSH(durations, duration_note65);
					lastState_key65 = 0x1;
					duration_note65 = 0x0;
				}
			} else {
				if (duration_note65 < 0xFFFF)
				duration_note65++;
			}

		} else {
			if (lastState_key65) {
				FIFO_PUSH(notes, 213);
				FIFO_PUSH(durations, duration_note65);
				lastState_key65 = 0x0;
				duration_note65 = 0x0;
			} else {
				duration_note65 = 0x0;
			}
		}
		/*66 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key66) {
				} else {
					FIFO_PUSH(notes, 86);
					FIFO_PUSH(durations, duration_note66);
					lastState_key66 = 0x1;
					duration_note66 = 0x0;
				}
			} else {
				if (duration_note66 < 0xFFFF)
				duration_note66++;
			}

		} else {
			if (lastState_key66) {
				FIFO_PUSH(notes, 214);
				FIFO_PUSH(durations, duration_note66);
				lastState_key66 = 0x0;
				duration_note66 = 0x0;
			} else {
				duration_note66 = 0x0;
			}
		}
		/*67 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key67) {
				} else {
					FIFO_PUSH(notes, 87);
					FIFO_PUSH(durations, duration_note67);
					lastState_key67 = 0x1;
					duration_note67 = 0x0;
				}
			} else {
				if (duration_note67 < 0xFFFF)
				duration_note67++;
			}

		} else {
			if (lastState_key67) {
				FIFO_PUSH(notes, 215);
				FIFO_PUSH(durations, duration_note67);
				lastState_key67 = 0x0;
				duration_note67 = 0x0;
			} else {
				duration_note67 = 0x0;
			}
		}
		/*68 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key68) {
				} else {
					FIFO_PUSH(notes, 88);
					FIFO_PUSH(durations, duration_note68);
					lastState_key68 = 0x1;
					duration_note68 = 0x0;
				}
			} else {
				if (duration_note68 < 0xFFFF)
				duration_note68++;
			}

		} else {
			if (lastState_key68) {
				FIFO_PUSH(notes, 216);
				FIFO_PUSH(durations, duration_note68);
				lastState_key68 = 0x0;
				duration_note68 = 0x0;
			} else {
				duration_note68 = 0x0;
			}
		}
		/*69 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key69) {
				} else {
					FIFO_PUSH(notes, 89);
					FIFO_PUSH(durations, duration_note69);
					lastState_key69 = 0x1;
					duration_note69 = 0x0;
				}
			} else {
				if (duration_note69 < 0xFFFF)
				duration_note69++;
			}

		} else {
			if (lastState_key69) {
				FIFO_PUSH(notes, 217);
				FIFO_PUSH(durations, duration_note69);
				lastState_key69 = 0x0;
				duration_note69 = 0x0;
			} else {
				duration_note69 = 0x0;
			}
		}
		/*70 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key70) {
				} else {
					FIFO_PUSH(notes, 90);
					FIFO_PUSH(durations, duration_note70);
					lastState_key70 = 0x1;
					duration_note70 = 0x0;
				}
			} else {
				if (duration_note70 < 0xFFFF)
				duration_note70++;
			}

		} else {
			if (lastState_key70) {
				FIFO_PUSH(notes, 218);
				FIFO_PUSH(durations, duration_note70);
				lastState_key70 = 0x0;
				duration_note70 = 0x0;
			} else {
				duration_note70 = 0x0;
			}
		}
		/*71 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key71) {
				} else {
					FIFO_PUSH(notes, 91);
					FIFO_PUSH(durations, duration_note71);
					lastState_key71 = 0x1;
					duration_note71 = 0x0;
				}
			} else {
				if (duration_note71 < 0xFFFF)
				duration_note71++;
			}

		} else {
			if (lastState_key71) {
				FIFO_PUSH(notes, 219);
				FIFO_PUSH(durations, duration_note71);
				lastState_key71 = 0x0;
				duration_note71 = 0x0;
			} else {
				duration_note71 = 0x0;
			}
		}
		/*72 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key72) {
				} else {
					FIFO_PUSH(notes, 92);
					FIFO_PUSH(durations, duration_note72);
					lastState_key72 = 0x1;
					duration_note72 = 0x0;
				}
			} else {
				if (duration_note72 < 0xFFFF)
				duration_note72++;
			}

		} else {
			if (lastState_key72) {
				FIFO_PUSH(notes, 220);
				FIFO_PUSH(durations, duration_note72);
				lastState_key72 = 0x0;
				duration_note72 = 0x0;
			} else {
				duration_note72 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState9) {
			if (lastState_key65) {
				FIFO_PUSH(notes, 213);
				FIFO_PUSH(durations, duration_note65);
				lastState_key65 = 0x0;
			}
			if (lastState_key66) {
				FIFO_PUSH(notes, 214);
				FIFO_PUSH(durations, duration_note66);
				lastState_key66 = 0x0;
			}
			if (lastState_key67) {
				FIFO_PUSH(notes, 215);
				FIFO_PUSH(durations, duration_note67);
				lastState_key67 = 0x0;
			}
			if (lastState_key68) {
				FIFO_PUSH(notes, 216);
				FIFO_PUSH(durations, duration_note68);
				lastState_key68 = 0x0;
			}
			if (lastState_key69) {
				FIFO_PUSH(notes, 217);
				FIFO_PUSH(durations, duration_note69);
				lastState_key69 = 0x0;
			}
			if (lastState_key70) {
				FIFO_PUSH(notes, 218);
				FIFO_PUSH(durations, duration_note70);
				lastState_key70 = 0x0;
			}
			if (lastState_key71) {
				FIFO_PUSH(notes, 219);
				FIFO_PUSH(durations, duration_note71);
				lastState_key71 = 0x0;
			}
			if (lastState_key72) {
				FIFO_PUSH(notes, 220);
				FIFO_PUSH(durations, duration_note72);
				lastState_key72 = 0x0;
			}
			duration_note65 = 0x0;
			duration_note66 = 0x0;
			duration_note67 = 0x0;
			duration_note68 = 0x0;
			duration_note69 = 0x0;
			duration_note70 = 0x0;
			duration_note71 = 0x0;
			duration_note72 = 0x0;
		}
	}
	lastState9 = d1;
	/* 10 chunk */

	GPIOE->BSRRH = GPIO_Pin_12; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_12;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOE->BSRRH = GPIO_Pin_10;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_10;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*73 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key73) {
				} else {
					FIFO_PUSH(notes, 93);
					FIFO_PUSH(durations, duration_note73);
					lastState_key73 = 0x1;
					duration_note73 = 0x0;
				}
			} else {
				if (duration_note73 < 0xFFFF)
				duration_note73++;
			}

		} else {
			if (lastState_key73) {
				FIFO_PUSH(notes, 221);
				FIFO_PUSH(durations, duration_note73);
				lastState_key73 = 0x0;
				duration_note73 = 0x0;
			} else {
				duration_note73 = 0x0;
			}
		}
		/*74 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key74) {
				} else {
					FIFO_PUSH(notes, 94);
					FIFO_PUSH(durations, duration_note74);
					lastState_key74 = 0x1;
					duration_note74 = 0x0;
				}
			} else {
				if (duration_note74 < 0xFFFF)
				duration_note74++;
			}

		} else {
			if (lastState_key74) {
				FIFO_PUSH(notes, 222);
				FIFO_PUSH(durations, duration_note74);
				lastState_key74 = 0x0;
				duration_note74 = 0x0;
			} else {
				duration_note74 = 0x0;
			}
		}
		/*75 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key75) {
				} else {
					FIFO_PUSH(notes, 95);
					FIFO_PUSH(durations, duration_note75);
					lastState_key75 = 0x1;
					duration_note75 = 0x0;
				}
			} else {
				if (duration_note75 < 0xFFFF)
				duration_note75++;
			}

		} else {
			if (lastState_key75) {
				FIFO_PUSH(notes, 223);
				FIFO_PUSH(durations, duration_note75);
				lastState_key75 = 0x0;
				duration_note75 = 0x0;
			} else {
				duration_note75 = 0x0;
			}
		}
		/*76 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key76) {
				} else {
					FIFO_PUSH(notes, 96);
					FIFO_PUSH(durations, duration_note76);
					lastState_key76 = 0x1;
					duration_note76 = 0x0;
				}
			} else {
				if (duration_note76 < 0xFFFF)
				duration_note76++;
			}

		} else {
			if (lastState_key76) {
				FIFO_PUSH(notes, 224);
				FIFO_PUSH(durations, duration_note76);
				lastState_key76 = 0x0;
				duration_note76 = 0x0;
			} else {
				duration_note76 = 0x0;
			}
		}
		/*77 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key77) {
				} else {
					FIFO_PUSH(notes, 97);
					FIFO_PUSH(durations, duration_note77);
					lastState_key77 = 0x1;
					duration_note77 = 0x0;
				}
			} else {
				if (duration_note77 < 0xFFFF)
				duration_note77++;
			}

		} else {
			if (lastState_key77) {
				FIFO_PUSH(notes, 225);
				FIFO_PUSH(durations, duration_note77);
				lastState_key77 = 0x0;
				duration_note77 = 0x0;
			} else {
				duration_note77 = 0x0;
			}
		}
		/*78 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key78) {
				} else {
					FIFO_PUSH(notes, 98);
					FIFO_PUSH(durations, duration_note78);
					lastState_key78 = 0x1;
					duration_note78 = 0x0;
				}
			} else {
				if (duration_note78 < 0xFFFF)
				duration_note78++;
			}

		} else {
			if (lastState_key78) {
				FIFO_PUSH(notes, 226);
				FIFO_PUSH(durations, duration_note78);
				lastState_key78 = 0x0;
				duration_note78 = 0x0;
			} else {
				duration_note78 = 0x0;
			}
		}
		/*79 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key79) {
				} else {
					FIFO_PUSH(notes, 99);
					FIFO_PUSH(durations, duration_note79);
					lastState_key79 = 0x1;
					duration_note79 = 0x0;
				}
			} else {
				if (duration_note79 < 0xFFFF)
				duration_note79++;
			}

		} else {
			if (lastState_key79) {
				FIFO_PUSH(notes, 227);
				FIFO_PUSH(durations, duration_note79);
				lastState_key79 = 0x0;
				duration_note79 = 0x0;
			} else {
				duration_note79 = 0x0;
			}
		}
		/*80 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key80) {
				} else {
					FIFO_PUSH(notes, 100);
					FIFO_PUSH(durations, duration_note80);
					lastState_key80 = 0x1;
					duration_note80 = 0x0;
				}
			} else {
				if (duration_note80 < 0xFFFF)
				duration_note80++;
			}

		} else {
			if (lastState_key80) {
				FIFO_PUSH(notes, 228);
				FIFO_PUSH(durations, duration_note80);
				lastState_key80 = 0x0;
				duration_note80 = 0x0;
			} else {
				duration_note80 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState10) {
			if (lastState_key73) {
				FIFO_PUSH(notes, 221);
				FIFO_PUSH(durations, duration_note73);
				lastState_key73 = 0x0;
			}
			if (lastState_key74) {
				FIFO_PUSH(notes, 222);
				FIFO_PUSH(durations, duration_note74);
				lastState_key74 = 0x0;
			}
			if (lastState_key75) {
				FIFO_PUSH(notes, 223);
				FIFO_PUSH(durations, duration_note75);
				lastState_key75 = 0x0;
			}
			if (lastState_key76) {
				FIFO_PUSH(notes, 224);
				FIFO_PUSH(durations, duration_note76);
				lastState_key76 = 0x0;
			}
			if (lastState_key77) {
				FIFO_PUSH(notes, 225);
				FIFO_PUSH(durations, duration_note77);
				lastState_key77 = 0x0;
			}
			if (lastState_key78) {
				FIFO_PUSH(notes, 226);
				FIFO_PUSH(durations, duration_note78);
				lastState_key78 = 0x0;
			}
			if (lastState_key79) {
				FIFO_PUSH(notes, 227);
				FIFO_PUSH(durations, duration_note79);
				lastState_key79 = 0x0;
			}
			if (lastState_key80) {
				FIFO_PUSH(notes, 228);
				FIFO_PUSH(durations, duration_note80);
				lastState_key80 = 0x0;
			}
			duration_note73 = 0x0;
			duration_note74 = 0x0;
			duration_note75 = 0x0;
			duration_note76 = 0x0;
			duration_note77 = 0x0;
			duration_note78 = 0x0;
			duration_note79 = 0x0;
			duration_note80 = 0x0;
		}
	}
	lastState10 = d1;
	/* 11 chunk */

	GPIOE->BSRRH = GPIO_Pin_11; //Pin to zero
	key_delay();
	d1 = ~GPIOA->IDR;//Read port state first contact
	GPIOE->BSRRL = GPIO_Pin_11;//Pin to 1

	GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
	GPIOA->ODR = 0x00FF;//High level on PA0-8;
	GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

	if (d1) {

		GPIOE->BSRRH = GPIO_Pin_13;
		key_delay();
		d2 = ~GPIOA->IDR; //Read port state second contact
		GPIOE->BSRRL = GPIO_Pin_13;

		GPIOA->MODER |= 0x00005555;//PA0-8 Will be Output
		GPIOA->ODR = 0x00FF;//High level on PA0-8;
		GPIOA->MODER &= 0xFFFF0000;//PA0-8 Will be Input

		/*81 key */

		if (d1 & 0x01) { // Key 1 in current chunk first sensor
			if (d2 & 0x01) { // Key 1 in current chunk second sensor
				if (lastState_key81) {
				} else {
					FIFO_PUSH(notes, 101);
					FIFO_PUSH(durations, duration_note81);
					lastState_key81 = 0x1;
					duration_note81 = 0x0;
				}
			} else {
				if (duration_note81 < 0xFFFF)
				duration_note81++;
			}

		} else {
			if (lastState_key81) {
				FIFO_PUSH(notes, 229);
				FIFO_PUSH(durations, duration_note81);
				lastState_key81 = 0x0;
				duration_note81 = 0x0;
			} else {
				duration_note81 = 0x0;
			}
		}
		/*82 key */

		if (d1 & 0x02) { // Key 2 in current chunk first sensor
			if (d2 & 0x02) { // Key 2 in current chunk second sensor
				if (lastState_key82) {
				} else {
					FIFO_PUSH(notes, 102);
					FIFO_PUSH(durations, duration_note82);
					lastState_key82 = 0x1;
					duration_note82 = 0x0;
				}
			} else {
				if (duration_note82 < 0xFFFF)
				duration_note82++;
			}

		} else {
			if (lastState_key82) {
				FIFO_PUSH(notes, 230);
				FIFO_PUSH(durations, duration_note82);
				lastState_key82 = 0x0;
				duration_note82 = 0x0;
			} else {
				duration_note82 = 0x0;
			}
		}
		/*83 key */

		if (d1 & 0x04) { // Key 3 in current chunk first sensor
			if (d2 & 0x04) { // Key 3 in current chunk second sensor
				if (lastState_key83) {
				} else {
					FIFO_PUSH(notes, 103);
					FIFO_PUSH(durations, duration_note83);
					lastState_key83 = 0x1;
					duration_note83 = 0x0;
				}
			} else {
				if (duration_note83 < 0xFFFF)
				duration_note83++;
			}

		} else {
			if (lastState_key83) {
				FIFO_PUSH(notes, 231);
				FIFO_PUSH(durations, duration_note83);
				lastState_key83 = 0x0;
				duration_note83 = 0x0;
			} else {
				duration_note83 = 0x0;
			}
		}
		/*84 key */

		if (d1 & 0x08) { // Key 4 in current chunk first sensor
			if (d2 & 0x08) { // Key 4 in current chunk second sensor
				if (lastState_key84) {
				} else {
					FIFO_PUSH(notes, 104);
					FIFO_PUSH(durations, duration_note84);
					lastState_key84 = 0x1;
					duration_note84 = 0x0;
				}
			} else {
				if (duration_note84 < 0xFFFF)
				duration_note84++;
			}

		} else {
			if (lastState_key84) {
				FIFO_PUSH(notes, 232);
				FIFO_PUSH(durations, duration_note84);
				lastState_key84 = 0x0;
				duration_note84 = 0x0;
			} else {
				duration_note84 = 0x0;
			}
		}
		/*85 key */

		if (d1 & 0x10) { // Key 5 in current chunk first sensor
			if (d2 & 0x10) { // Key 5 in current chunk second sensor
				if (lastState_key85) {
				} else {
					FIFO_PUSH(notes, 105);
					FIFO_PUSH(durations, duration_note85);
					lastState_key85 = 0x1;
					duration_note85 = 0x0;
				}
			} else {
				if (duration_note85 < 0xFFFF)
				duration_note85++;
			}

		} else {
			if (lastState_key85) {
				FIFO_PUSH(notes, 233);
				FIFO_PUSH(durations, duration_note85);
				lastState_key85 = 0x0;
				duration_note85 = 0x0;
			} else {
				duration_note85 = 0x0;
			}
		}
		/*86 key */

		if (d1 & 0x20) { // Key 6 in current chunk first sensor
			if (d2 & 0x20) { // Key 6 in current chunk second sensor
				if (lastState_key86) {
				} else {
					FIFO_PUSH(notes, 106);
					FIFO_PUSH(durations, duration_note86);
					lastState_key86 = 0x1;
					duration_note86 = 0x0;
				}
			} else {
				if (duration_note86 < 0xFFFF)
				duration_note86++;
			}

		} else {
			if (lastState_key86) {
				FIFO_PUSH(notes, 234);
				FIFO_PUSH(durations, duration_note86);
				lastState_key86 = 0x0;
				duration_note86 = 0x0;
			} else {
				duration_note86 = 0x0;
			}
		}
		/*87 key */

		if (d1 & 0x40) { // Key 7 in current chunk first sensor
			if (d2 & 0x40) { // Key 7 in current chunk second sensor
				if (lastState_key87) {
				} else {
					FIFO_PUSH(notes, 107);
					FIFO_PUSH(durations, duration_note87);
					lastState_key87 = 0x1;
					duration_note87 = 0x0;
				}
			} else {
				if (duration_note87 < 0xFFFF)
				duration_note87++;
			}

		} else {
			if (lastState_key87) {
				FIFO_PUSH(notes, 235);
				FIFO_PUSH(durations, duration_note87);
				lastState_key87 = 0x0;
				duration_note87 = 0x0;
			} else {
				duration_note87 = 0x0;
			}
		}
		/*88 key */

		if (d1 & 0x80) { // Key 8 in current chunk first sensor
			if (d2 & 0x80) { // Key 8 in current chunk second sensor
				if (lastState_key88) {
				} else {
					FIFO_PUSH(notes, 108);
					FIFO_PUSH(durations, duration_note88);
					lastState_key88 = 0x1;
					duration_note88 = 0x0;
				}
			} else {
				if (duration_note88 < 0xFFFF)
				duration_note88++;
			}

		} else {
			if (lastState_key88) {
				FIFO_PUSH(notes, 236);
				FIFO_PUSH(durations, duration_note88);
				lastState_key88 = 0x0;
				duration_note88 = 0x0;
			} else {
				duration_note88 = 0x0;
			}
		}
	} else {
		d2 = 0x0;
		if (lastState11) {
			if (lastState_key81) {
				FIFO_PUSH(notes, 229);
				FIFO_PUSH(durations, duration_note81);
				lastState_key81 = 0x0;
			}
			if (lastState_key82) {
				FIFO_PUSH(notes, 230);
				FIFO_PUSH(durations, duration_note82);
				lastState_key82 = 0x0;
			}
			if (lastState_key83) {
				FIFO_PUSH(notes, 231);
				FIFO_PUSH(durations, duration_note83);
				lastState_key83 = 0x0;
			}
			if (lastState_key84) {
				FIFO_PUSH(notes, 232);
				FIFO_PUSH(durations, duration_note84);
				lastState_key84 = 0x0;
			}
			if (lastState_key85) {
				FIFO_PUSH(notes, 233);
				FIFO_PUSH(durations, duration_note85);
				lastState_key85 = 0x0;
			}
			if (lastState_key86) {
				FIFO_PUSH(notes, 234);
				FIFO_PUSH(durations, duration_note86);
				lastState_key86 = 0x0;
			}
			if (lastState_key87) {
				FIFO_PUSH(notes, 235);
				FIFO_PUSH(durations, duration_note87);
				lastState_key87 = 0x0;
			}
			if (lastState_key88) {
				FIFO_PUSH(notes, 236);
				FIFO_PUSH(durations, duration_note88);
				lastState_key88 = 0x0;
			}
			duration_note81 = 0x0;
			duration_note82 = 0x0;
			duration_note83 = 0x0;
			duration_note84 = 0x0;
			duration_note85 = 0x0;
			duration_note86 = 0x0;
			duration_note87 = 0x0;
			duration_note88 = 0x0;
		}
	}
	lastState11 = d1;

}
#endif
