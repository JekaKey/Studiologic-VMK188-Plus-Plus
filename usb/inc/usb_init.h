#ifndef __USB_INIT__
#define __USB_INIT__
#include "usb_dcd_int.h"

extern uint8_t USBdisk_active;
void usb_midi_MSC_init(void);
void usb_midi_init(void);
void usb_temp_disconnect(void);
void usb_deinit(void);
void usb_midi_cb(void);
void usb_midi_MSC_cb(void);


#endif //__USB_INIT__

