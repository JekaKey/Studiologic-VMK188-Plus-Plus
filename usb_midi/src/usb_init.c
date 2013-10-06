#include "usb_midi_usr.h"
#include "usbd_midi_core.h"
#include "usbd_midi_desc.h"
//#include "usb_fifo.h"
#include "usb_midi_io.h"
#include "usb_init.h"

USB_OTG_CORE_HANDLE     USB_OTG_dev;

/*Should be called in Main to init usb port.*/

extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

void usb_init(void) {


//usb_fifo_init();	

USBD_Init(&USB_OTG_dev, 
        USB_OTG_FS_CORE_ID, 
        &midi_Descriptor, 
        &midi_cb, 
        &MS_Usr_cb);
}






/*The main USB IRQ handler*/

void OTG_FS_IRQHandler(void) {
	USBD_OTG_ISR_Handler(&USB_OTG_dev);
}

