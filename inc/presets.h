#ifndef PRESETS__H
#define PRESETS__H

#include "stm32f4xx.h"

struct preset {
	uint8_t Id;				//
	uint8_t MidiChannel; 	//0-16
	uint8_t HighResEnable;	//0-1
};

void preset_load(uint8_t preset_id);
void preset_save(uint8_t preset_id);
void preset_save_current();

#endif //PRESETS__H
