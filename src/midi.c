#include <string.h>
#include "presets.h"
#include "usb_midi_io.h"
#include "sysex_events.h"
#include "midi.h"
#include "log.h"


uint8_t message_buff[4];

extern FIFO8(128) midiMessagesArray; //Array for midi messages buffer
extern FIFO8(128) sysexArray;
extern FIFO8(8) notes; //Array for current note
extern FIFO16(8) durations; //Array for duration for current note
extern FIFO32(128) midi_usb_in;

void sendNoteOn(uint8_t NoteNumber, uint8_t Velocity, uint8_t Channel, uint8_t analog) {
	message_buff[0] = 0x09; //USB-MIDI NoteOn prefix
	message_buff[1] = NoteOn ^ Channel;
	message_buff[2] = NoteNumber;
	message_buff[3] = Velocity;
	usb_midi_DataSend(message_buff, 4);

	if (analog) {
		FIFO_PUSH(midiMessagesArray, NoteOn ^ Channel);
		FIFO_PUSH(midiMessagesArray, NoteNumber);
		FIFO_PUSH(midiMessagesArray, Velocity);
	}

}

void sendNoteOff(uint8_t NoteNumber, uint8_t Velocity, uint8_t Channel, uint8_t analog) {
	message_buff[0] = 0x08; //USB-MIDI NoteOff prefix
	message_buff[1] = NoteOff ^ Channel;
	message_buff[2] = NoteNumber;
	message_buff[3] = Velocity;
	usb_midi_DataSend(message_buff, 4);

	if (analog) {
		FIFO_PUSH(midiMessagesArray, NoteOff ^ Channel);
		FIFO_PUSH(midiMessagesArray, NoteNumber);
		FIFO_PUSH(midiMessagesArray, Velocity);
	}
}

void sendControlChange(uint8_t ControlNumber, uint8_t ControlValue, uint8_t Channel, uint8_t analog) {
	message_buff[0] = 0x0B; //USB-MIDI CC prefix
	message_buff[1] = ControlChange ^ Channel;
	message_buff[2] = ControlNumber;
	message_buff[3] = ControlValue;
	usb_midi_DataSend(message_buff, 4);

	if (analog) {
		FIFO_PUSH(midiMessagesArray, ControlChange ^ Channel);
		FIFO_PUSH(midiMessagesArray, ControlNumber);
		FIFO_PUSH(midiMessagesArray, ControlValue);
	}
}

void sendPitchBend(uint16_t Value, uint8_t Channel, uint8_t analog) {
	uint8_t ValueL = Value & 0x7F;
	uint8_t ValueM = Value >> 7;

	message_buff[0] = 0x0E; //USB-MIDI Pitch prefix
	message_buff[1] = PitchBend ^ Channel;
	message_buff[2] = ValueL;
	message_buff[3] = ValueM;
	usb_midi_DataSend(message_buff, 4);

	if (analog) {
		FIFO_PUSH(midiMessagesArray, PitchBend ^ Channel);
		FIFO_PUSH(midiMessagesArray, ValueL);
		FIFO_PUSH(midiMessagesArray, ValueM);
	}
}

void sendAfterTouch(uint8_t Preasure, uint8_t Channel, uint8_t analog) {
	message_buff[0] = 0x0D; //USB-MIDI AfterTouch prefix
	message_buff[1] = AfterTouchChannel ^ Channel;
	message_buff[2] = Preasure;
	message_buff[3] = 0;
	usb_midi_DataSend(message_buff, 4);
	if (analog) {
		FIFO_PUSH(midiMessagesArray, AfterTouchChannel ^ Channel);
		FIFO_PUSH(midiMessagesArray, Preasure);
	}
}

void sendPanic(presetType *pr){
	sendControlChange(120, 0, pr->MidiChannel-1, pr->AnalogMidiEnable);
	if (pr->SplitActive)
	    sendControlChange(120, 0, pr->SplitChannel-1, pr->AnalogMidiEnable);
}

void sendPanicAll(uint8_t analog) {
	for (uint8_t i = 0; i < 16; i++)
		sendControlChange(120, 0, i, analog);
}

void sendMMC(uint8_t Value, uint8_t analog) {
	uint8_t buff[8];
	buff[0] = 0x04;
	buff[1] = 0xF0;
	buff[2] = 0x7F;
	buff[3] = 0x7F;
	buff[4] = 0x07;
	buff[5] = 0x06;
	buff[6] = Value;
	buff[7] = 0xF7;

	usb_midi_DataSend(buff, 8);

	if (analog) {
		for (uint8_t i = 1; i <= 3; i++)
			FIFO_PUSH(midiMessagesArray, buff[i]);
		for (uint8_t i = 5; i <= 7; i++)
			FIFO_PUSH(midiMessagesArray, buff[i]);
	}
}

void sendMidiData(void) {

	uint8_t test;

	test = FIFO_COUNT(midiMessagesArray);
	if (test) {
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
		PRINTF("MIDI: %lu\n", midiMessage);

		//add only sysex messages into sysexArray
		if ((midiMessage & 0xF) == 0x4) {

			FIFO_PUSH(sysexArray, ((midiMessage&0xF000000)>>20)|((midiMessage&0xF0000)>>16));
			//TODO: create midi sysex function

			//Send receive sysex ok message
			midipacket = 0x0100F004;
			usb_midi_DataSend((uint8_t*)(&midipacket), 4);
			midipacket = 0x0000F705;
			usb_midi_DataSend((uint8_t*)(&midipacket), 4);
		} else if ((midiMessage & 0xF) == 0x5 || (midiMessage & 0xF) == 0x6 || (midiMessage & 0xF) == 0x7) {

			//Find and run sysex command
			sysex_parse_event();

			//Send receive sysex ok message
			midipacket = 0x0100F004;
			usb_midi_DataSend((uint8_t*)(&midipacket), 4);
			midipacket = 0x0000F705;
			usb_midi_DataSend((uint8_t*)(&midipacket), 4);

		}

		FIFO_POP(midi_usb_in);

	}

}
