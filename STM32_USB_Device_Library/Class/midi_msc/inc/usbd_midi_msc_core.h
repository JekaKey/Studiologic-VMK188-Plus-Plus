#ifndef __USB_MIDI_MSC_CORE_H_
#define __USB_MIDI_MSC_CORE_H_


#include "usbd_ioreq.h"
#include "usbd_req.h"
#include "USBD_MIDI_core.h"
#include "usbd_MSC_core.h"

#define MIDI_INTERFACE0 0x0
#define MIDI_INTERFACE1 0x1
#define MSC_INTERFACE 0x2



#define MSC_CLASS_SPECIFIC_DESC_SIZE    9+7+7
#define MIDI_MSC_CONFIG_DESC_SIZE       9+9+9+9 + MIDI_CLASS_SPECIFIC_DESC_SIZE + MSC_CLASS_SPECIFIC_DESC_SIZE
#define USB_MIDI_MSC_CONFIG_DESC_SIZE 100

extern USBD_Class_cb_TypeDef midi_MSC_cb;

#endif
