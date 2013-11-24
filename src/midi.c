#include "midi.h"
#include "presets.h"
#include "usb_midi_io.h"

uint8_t message_buff[4];


extern FIFO8(128) midiMessagesArray; //Array for midi messages buffer
extern FIFO8(8) notes; //Array for current note
extern FIFO16(8) durations; //Array for duration for current note




void sendNoteOn(byte NoteNumber, word Velocity, byte Channel) {
	message_buff[0] = 0x09; //USB-MIDI NoteOn prefix
	message_buff[1] = NoteOn ^ Channel;
	message_buff[2] = NoteNumber;
	message_buff[3] = (uint8_t)(Velocity >> 7);
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, NoteOn ^ Channel);
	FIFO_PUSH(midiMessagesArray, NoteNumber);
	FIFO_PUSH(midiMessagesArray, (byte)(Velocity>>7));
}

void sendNoteOff(byte NoteNumber, word Velocity, byte Channel) {
	message_buff[0] = 0x08;  //USB-MIDI NoteOff prefix
	message_buff[1] = NoteOff ^ Channel;
	message_buff[2] = NoteNumber;
	message_buff[3] = (uint8_t)(Velocity >> 7);
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, NoteOff ^ Channel);
	FIFO_PUSH(midiMessagesArray, NoteNumber);
	FIFO_PUSH(midiMessagesArray, (byte)(Velocity>>7));
}

void sendControlChange(byte ControlNumber, byte ControlValue, byte Channel) {
	message_buff[0] = 0x0B;  //USB-MIDI CC prefix
	message_buff[1] = ControlChange ^ Channel;
	message_buff[2] = ControlNumber;
	message_buff[3] = ControlValue;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, ControlChange ^ Channel);
	FIFO_PUSH(midiMessagesArray, ControlNumber);
	FIFO_PUSH(midiMessagesArray, ControlValue);
}

void sendPitchBend(byte Value, byte Channel){
	message_buff[0] = 0x0E; //USB-MIDI Pitch prefix
	message_buff[1] = PitchBend ^ Channel;
	message_buff[2] = 0;
	message_buff[3] = Value;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, PitchBend ^ Channel);
	FIFO_PUSH(midiMessagesArray, 0);
	FIFO_PUSH(midiMessagesArray, Value);
}

void sendAfterTouch(byte Preasure, byte Channel){
	message_buff[0] = 0x0D; //USB-MIDI AfterTouch prefix
	message_buff[1] = AfterTouchChannel ^ Channel;
	message_buff[2] = Preasure;
	message_buff[3] = 0;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, AfterTouchChannel ^ Channel);
	FIFO_PUSH(midiMessagesArray, Preasure);
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
