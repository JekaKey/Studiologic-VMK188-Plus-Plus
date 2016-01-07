#ifndef __USB_MIDI_CORE_H_
#define __USB_MIDI_CORE_H_

#include "usbd_ioreq.h"
#include "usbd_req.h"


/*Midi device standard constants*/

/*MS Class-Specific Interface Descriptor Subtypes*/
#define MS_DESCRIPTOR_UNDEFINED    0x00
#define MS_HEADER                  0x01
#define MIDI_IN_JACK               0x02
#define MIDI_OUT_JACK              0x03
#define ELEMENT                    0x04

/*MS Class-Specific Endpoint Descriptor Subtypes*/
#define DESCRIPTOR_UNDEFINED       0x00
#define MS_GENERAL                 0x01

/*MIDI IN and OUT Jack type Value*/
#define JACK_TYPE_UNDEFINED        0x00
#define EMBEDDED                   0x01
#define EXTERNAL                   0x02

/*Descriptors defines*/


#define MIDI_CLASS_SPECIFIC_DESC_SIZE   7+6+9+9+5+9+5
#define MIDI_CONFIG_DESC_SIZE 			9+9+9+9 + MIDI_CLASS_SPECIFIC_DESC_SIZE //Full size of interface descriptors
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_DEVICE_CLASS_AUDIO                  0x01
#define USB_DEVICE_SUBCLASS_MIDISTREAMING       0x03


#define midi_data_in_pack_size 128
#define midi_data_out_pack_size 128

extern USBD_Class_cb_TypeDef midi_cb;

/*********************************************
 midi Device library callbacks
 *********************************************/
uint8_t USBD_MIDI_Init(void *pdev, uint8_t cfgidx);
uint8_t USBD_MIDI_DeInit(void *pdev, uint8_t cfgidx);
uint8_t USBD_MIDI_Setup(void *pdev, USB_SETUP_REQ *req);
uint8_t USBD_MIDI_EP0_RxReady(void *pdev);
uint8_t USBD_MIDI_DataIn(void *pdev, uint8_t epnum);
uint8_t USBD_MIDI_DataOut(void *pdev, uint8_t epnum);
uint8_t USBD_MIDI_SOF(void *pdev);
uint8_t USBD_MIDI_OUT_Incplt(void *pdev);
uint8_t *USBD_MIDI_GetCfgDesc(uint8_t speed, uint16_t *length);

#endif //__USB_MIDI_CORE_H_
