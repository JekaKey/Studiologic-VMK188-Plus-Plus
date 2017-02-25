#ifndef __USB_MIDI_IO_H
#define __USB_MIDI_IO_H

#include "stm32f4xx.h"

void usb_midi_DataSend(uint8_t* Buf, uint32_t Len);
void usb_fifo_init(void);
void usb_midi_refresh(void);
void USB_MIDI_ChangeConnectionState(uint8_t connected);
 
#endif //__USB_MIDI_IO_H
