#include "stm32f4xx.h"
#include "usbd_def.h"
#include "usb_core.h"

extern USBD_DEVICE midi_Descriptor;


#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05
#define USB_SIZ_DEVICE_DESC                     18
#define USB_SIZ_STRING_LANGID                   4


#define USBD_VID                     0x03EB
#define USBD_PID                     0x2304

#define USBD_LANGID_STRING            0x409
#define USBD_MANUFACTURER_STRING      "Studiologic"

#ifdef VMK188

#define USBD_PRODUCT_HS_STRING        "VMK188++"
#define USBD_SERIALNUMBER_HS_STRING   "00000000011B"

#define USBD_PRODUCT_FS_STRING        "VMK188++"
#define USBD_SERIALNUMBER_FS_STRING   "00000000011C"

#define USBD_CONFIGURATION_HS_STRING  "VMK188++ Config HS"
#define USBD_INTERFACE_HS_STRING      "VMK188++ Interface HS"

#define USBD_CONFIGURATION_FS_STRING  "VMK188++ Config FS"
#define USBD_INTERFACE_FS_STRING      "VMK188++ Interface FS"

#else

#define USBD_PRODUCT_HS_STRING        "VMK176++"
#define USBD_SERIALNUMBER_HS_STRING   "00000000011B"

#define USBD_PRODUCT_FS_STRING        "VMK176++"
#define USBD_SERIALNUMBER_FS_STRING   "00000000011C"

#define USBD_CONFIGURATION_HS_STRING  "VMK176++ Config HS"
#define USBD_INTERFACE_HS_STRING      "VMK176++ Interface HS"

#define USBD_CONFIGURATION_FS_STRING  "VMK176++ Config FS"
#define USBD_INTERFACE_FS_STRING      "VMK176++ Interface FS"

#endif

extern  uint8_t USBD_DeviceDesc  [USB_SIZ_DEVICE_DESC];
extern  uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ];
extern  uint8_t USBD_OtherSpeedCfgDesc[USB_LEN_CFG_DESC]; 
extern  uint8_t USBD_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];
extern  uint8_t USBD_LangIDDesc[USB_SIZ_STRING_LANGID];
extern  USBD_DEVICE midi_Descriptor;



uint8_t *     USBD_USR_DeviceDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_LangIDStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ManufacturerStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ProductStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_SerialStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_ConfigStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_InterfaceStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_USR_USRStringDesc (uint8_t speed, uint8_t idx , uint16_t *length);  
  



