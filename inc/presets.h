#ifndef PRESETS__H
#define PRESETS__H

#include "stm32f4xx.h"

typedef struct {
	uint8_t Id;				//
	uint8_t MidiChannel; 	//0-16
	uint8_t HighResEnable;	//bool

} presetType;

extern presetType preset;
presetType preset;

void preset_load();
void preset_save();
void preset_save_current();

#endif //PRESETS__H
