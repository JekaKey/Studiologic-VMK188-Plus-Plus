#include "usb_midi_io.h"
#include "usb_dcd.h"
#include "midi.h"
#include "fifo.h"
#include "usbd_core.h"


extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern volatile uint32_t USB_Tx_State;

void usb_midi_DataSend(uint8_t* Buf, uint32_t Len) {
	while (USB_Tx_State){}
	USB_Tx_State=1;
	DCD_EP_Tx(&USB_OTG_dev, MIDI_IN_EP, Buf, Len);
}

