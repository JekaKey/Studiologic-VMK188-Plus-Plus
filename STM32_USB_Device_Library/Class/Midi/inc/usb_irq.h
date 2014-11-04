#include "usb_dcd_int.h"



#ifdef USE_USB_OTG_HS
void OTG_HS_IRQHandler(void) {
	USBH_OTG_ISR_Handler(&usbOTGHost);
}
#endif

#ifdef USE_USB_OTG_FS
void OTG_FS_IRQHandler(void) {
	USBD_OTG_ISR_Handler(&usbOTGDevice);
}
#endif
