#include "usb_midi_usr.h"
#include "usbd_midi_core.h"
#include "usbd_midi_msc_core.h"
#include "usbd_midi_desc.h"
//#include "usb_fifo.h"
#include "usb_midi_io.h"
#include "usb_init.h"
#include "usb_dcd.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE     USB_OTG_dev __ALIGN_END;

/*Should be called in Main to initialize usb port.*/

extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

uint8_t USBdisk_active=0;


void usb_temp_disconnect(void){
	DCD_DevDisconnect(&USB_OTG_dev);
}

void usb_deinit(void){

}

void usb_midi_cb(void){
	USBD_change_cb(&USB_OTG_dev, &midi_cb);
}

void usb_midi_MSC_cb(void){
	USBD_change_cb(&USB_OTG_dev, &midi_MSC_cb);
}


void usb_midi_init(void) {
USBD_Init(&USB_OTG_dev,
        USB_OTG_FS_CORE_ID,
        &midi_Descriptor,
        &midi_cb,
        &MS_Usr_cb);
}

void usb_midi_MSC_init(void) {
USBD_Init(&USB_OTG_dev, 
        USB_OTG_FS_CORE_ID, 
        &midi_Descriptor, 
        &midi_MSC_cb,
        &MS_Usr_cb);
}



/*Handler services wake up interrupt. Should be tested  */
void OTG_FS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}


/*The main USB IRQ handler*/

void OTG_FS_IRQHandler(void) {
	USBD_OTG_ISR_Handler(&USB_OTG_dev);
}

