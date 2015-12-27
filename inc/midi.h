#ifndef MIDI_H
#define MIDI_H

#if defined MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "fifo.h"
#include "velocity.h"

#define OK_SYSEX 0xF704F004;

#define MMC_STOP 0x01
#define MMC_PLAY 0x02
#define MMC_FF 0x04
#define MMC_RW 0x05
#define MMC_REC 0x06


/*! Enumeration of MIDI types */
enum kMIDIType {
	NoteOff = 0x80, ///< Note Off
	NoteOn = 0x90, ///< Note On
	HiresPrefix1 = 0xB0, ///<Hi res Prefix
	HiresPrefix2 = 0x58, ///<Hi res Prefix
	AfterTouchPoly = 0xA0, ///< Polyphonic AfterTouch
	ControlChange = 0xB0, ///< Control Change / Channel Mode
	ProgramChange = 0xC0, ///< Program Change
	AfterTouchChannel = 0xD0, ///< Channel (monophonic) AfterTouch
	PitchBend = 0xE0, ///< Pitch Bend
	SystemExclusive = 0xF0, ///< System Exclusive
	TimeCodeQuarterFrame = 0xF1, ///< System Common - MIDI Time Code Quarter Frame
	SongPosition = 0xF2, ///< System Common - Song Position Pointer
	SongSelect = 0xF3, ///< System Common - Song Select
	TuneRequest = 0xF6, ///< System Common - Tune Request
	Clock = 0xF8, ///< System Real Time - Timing Clock
	Start = 0xFA, ///< System Real Time - Start
	Continue = 0xFB, ///< System Real Time - Continue
	Stop = 0xFC, ///< System Real Time - Stop
	ActiveSensing = 0xFE, ///< System Real Time - Active Sensing
	SystemReset = 0xFF, ///< System Real Time - System Reset
	InvalidType = 0x00 ///< For notifying errors
};

void sendNoteOn(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel, uint8_t analog);
void sendNoteOff(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel,  uint8_t analog);

void sendProgramChange(uint8_t ProgramNumber, uint8_t Channel,  uint8_t analog);
void sendControlChange(uint8_t ControlNumber, uint8_t ControlValue, uint8_t Channel,  uint8_t analog);
void sendPitchBend(uint16_t Value, uint8_t Channel,  uint8_t analog);
void sendPolyPressure(uint8_t NoteNumber, uint8_t Pressure, uint8_t Channel,  uint8_t analog);
void sendAfterTouch(uint8_t Pressure, uint8_t Channel,  uint8_t analog);
void sendPanic(uint8_t analog);

void sendMMC(uint8_t Value, uint8_t analog);

void sendMidiData(void); //Send one midi message per run from buffer array
void receiveMidiData(void);

#endif //MIDI_H
