#ifndef PRESETS__H
#define PRESETS__H

#include "stm32f4xx.h"

typedef struct {
	uint8_t Id; //
	uint8_t MidiChannel; //0-16
	uint8_t HighResEnable; //bool

} presetType;

extern presetType preset;
presetType preset;

void preset_load(void);
void preset_save(void);
void preset_save_current(void);

void memory_start(void);
void memory_stop(void);

uint8_t memory_transfer_data(uint8_t data);

void memory_send_command(uint8_t opcode, uint8_t adress_byte1, uint8_t adress_byte2, uint8_t adress_byte3);
void memory_buffer_to_page(uint8_t buffer, uint16_t target_number_page);
void memory_page_to_buffer(uint8_t buffer, uint16_t target_number_page);
void memory_read_buffer(uint8_t buffer, uint8_t from_byte);

uint8_t memory_ready_status(void);
void memory_wait_ready(void);

#endif //PRESETS__H
