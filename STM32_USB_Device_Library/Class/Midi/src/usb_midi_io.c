#include "usb_midi_io.h"
#include "usb_dcd.h"
#include "midi.h"

extern USB_OTG_CORE_HANDLE USB_OTG_dev;

void usb_midi_DataTx(uint8_t* Buf, uint32_t Len) {
	DCD_EP_Tx(&USB_OTG_dev, 0x81, Buf, 4);
}

