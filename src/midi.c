#include "presets.h"
#include "usb_midi_io.h"
#include "sysex_events.h"
#include "midi.h"


uint8_t message_buff[4];

extern FIFO8(128) midiMessagesArray; //Array for midi messages buffer
extern FIFO8(128) sysexArray;
extern FIFO8(8) notes; //Array for current note
extern FIFO16(8) durations; //Array for duration for current note
extern FIFO32(128) midi_usb_in;

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
	message_buff[0] = 0x08; //USB-MIDI NoteOff prefix
	message_buff[1] = NoteOff ^ Channel;
	message_buff[2] = NoteNumber;
	message_buff[3] = (uint8_t)(Velocity >> 7);
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, NoteOff ^ Channel);
	FIFO_PUSH(midiMessagesArray, NoteNumber);
	FIFO_PUSH(midiMessagesArray, (byte)(Velocity>>7));
}

void sendControlChange(byte ControlNumber, byte ControlValue, byte Channel) {
	message_buff[0] = 0x0B; //USB-MIDI CC prefix
	message_buff[1] = ControlChange ^ Channel;
	message_buff[2] = ControlNumber;
	message_buff[3] = ControlValue;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, ControlChange ^ Channel);
	FIFO_PUSH(midiMessagesArray, ControlNumber);
	FIFO_PUSH(midiMessagesArray, ControlValue);
}

void sendPitchBend(byte Value, byte Channel) {
	message_buff[0] = 0x0E; //USB-MIDI Pitch prefix
	message_buff[1] = PitchBend ^ Channel;
	message_buff[2] = 0;
	message_buff[3] = Value;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, PitchBend ^ Channel);
	FIFO_PUSH(midiMessagesArray, 0);
	FIFO_PUSH(midiMessagesArray, Value);
}

void sendAfterTouch(byte Preasure, byte Channel) {
	message_buff[0] = 0x0D; //USB-MIDI AfterTouch prefix
	message_buff[1] = AfterTouchChannel ^ Channel;
	message_buff[2] = Preasure;
	message_buff[3] = 0;
	usb_midi_DataTx(message_buff, 4);

	FIFO_PUSH(midiMessagesArray, AfterTouchChannel ^ Channel);
	FIFO_PUSH(midiMessagesArray, Preasure);
}

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

void receiveMidiData(void) {

	if (FIFO_COUNT(midi_usb_in) != 0) {

		uint32_t midipacket;
		uint32_t midiMessage = FIFO_FRONT(midi_usb_in);

		//add only sysex messages into sysexArray
		if ((midiMessage & 0xF) == 0x4) {

			FIFO_PUSH(sysexArray, ((midiMessage&0xF000000)>>24)|((midiMessage&0xFF0000)>>12));
			//TODO: create midi sysex function

			//Send receive sysex ok message
			midipacket = 0x0100F004;
			usb_midi_DataTx(&midipacket, 4);
			midipacket = 0x0000F705;
			usb_midi_DataTx(&midipacket, 4);
		} else if ((midiMessage & 0xF) == 0x5 || (midiMessage & 0xF) == 0x6 || (midiMessage & 0xF) == 0x7) {

			//Find and run sysex command
			sysex_parse_event();
			//Send receive sysex ok message
			midipacket = 0x0100F004;
			usb_midi_DataTx(&midipacket, 4);
			midipacket = 0x0000F705;
			usb_midi_DataTx(&midipacket, 4);

		}

		FIFO_POP(midi_usb_in);

	}

}
