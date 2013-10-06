#include <stm32f4xx.h>



void sendUSB_NoteOn(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel);
void sendUSB_NoteOff(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel);
void sendUSB_ControlChange(uint8_t ControlNumber, uint8_t ControlValue, uint8_t Channel); 
void usb_fifo_init(void);
 
