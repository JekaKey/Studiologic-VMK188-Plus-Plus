#include "midi.h"

void sendNoteOn(byte NoteNumber, word Velocity, byte Channel) {
	FIFO_PUSH(midiMessagesArray, NoteOn ^ Channel);
	FIFO_PUSH(midiMessagesArray, NoteNumber);
	FIFO_PUSH(midiMessagesArray, (byte)(Velocity>>7));
}

void sendNoteOff(byte NoteNumber, word Velocity, byte Channel) {
	FIFO_PUSH(midiMessagesArray, NoteOff ^ Channel);
	FIFO_PUSH(midiMessagesArray, NoteNumber);
	FIFO_PUSH(midiMessagesArray, (byte)(Velocity>>7));
}

void sendControlChange(byte ControlNumber, byte ControlValue, byte Channel) {
	FIFO_PUSH(midiMessagesArray, ControlChange ^ Channel);
	FIFO_PUSH(midiMessagesArray, ControlNumber);
	FIFO_PUSH(midiMessagesArray, ControlValue);
}

/**
 * Send midi data over USART
 */
void sendMidiData(void) {

	uint8_t test;

	test = FIFO_COUNT(midiMessagesArray);
	if (test != 0) {
		if ((USART1->SR & 0x00000040)) {
			USART_SendData(USART1, FIFO_FRONT(midiMessagesArray));
			FIFO_POP(midiMessagesArray);

		}
	}
}
