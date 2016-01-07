#include "usbd_midi_msc_core.h"
#include "usb_dcd.h"
#include "usbd_conf.h"
#include "fifo.h"
#include "log.h"

/*********************************************
 MSC Device library callbacks
 *********************************************/
extern uint8_t  USBD_MSC_Init (void  *pdev, uint8_t cfgidx);
extern uint8_t  USBD_MSC_DeInit (void  *pdev, uint8_t cfgidx);
extern uint8_t  USBD_MSC_Setup (void  *pdev, USB_SETUP_REQ *req);
extern uint8_t  USBD_MSC_DataIn (void  *pdev, uint8_t epnum);
extern uint8_t  USBD_MSC_DataOut (void  *pdev,  uint8_t epnum);
extern uint8_t  *USBD_MSC_GetCfgDesc (uint8_t speed, uint16_t *length);
extern uint8_t  USBD_MSC_CfgDesc[USB_MSC_CONFIG_DESC_SIZ];


/*********************************************
 midi_MSC Device library callbacks
 *********************************************/
static uint8_t USBD_MIDI_MSC_Init(void *pdev, uint8_t cfgidx);
static uint8_t USBD_MIDI_MSC_DeInit(void *pdev, uint8_t cfgidx);
static uint8_t USBD_MIDI_MSC_Setup(void *pdev, USB_SETUP_REQ *req);
static uint8_t USBD_MIDI_MSC_EP0_RxReady(void *pdev);
static uint8_t USBD_MIDI_MSC_DataIn(void *pdev, uint8_t epnum);
static uint8_t USBD_MIDI_MSC_DataOut(void *pdev, uint8_t epnum);
static uint8_t USBD_MIDI_MSC_SOF(void *pdev);
static uint8_t USBD_MIDI_MSC_OUT_Incplt(void *pdev);
static uint8_t *USBD_MIDI_MSC_GetCfgDesc(uint8_t speed, uint16_t *length);

//FIFO32(128) midi_msc_usb_in; //FIFO buffer for 32-bit midi packets from a computer
volatile uint32_t USB_Tx_State; //USB endpoint ready flag



USBD_Class_cb_TypeDef midi_MSC_cb = {
		USBD_MIDI_MSC_Init,
		USBD_MIDI_MSC_DeInit,
		USBD_MIDI_MSC_Setup,
        /* Control Endpoints*/
        (void*) 0, /* EP0_TxSent */
        USBD_MIDI_MSC_EP0_RxReady,
        /* Class Specific Endpoints*/
        USBD_MIDI_MSC_DataIn,
        USBD_MIDI_MSC_DataOut,
        USBD_MIDI_MSC_SOF,
        (void*) 0, //IsoINIncomplete
        USBD_MIDI_MSC_OUT_Incplt, //IsoOUTIncomplete
        USBD_MIDI_MSC_GetCfgDesc //GetConfigDescriptor
		};



/* USB midi device Configuration Descriptor */
static uint8_t USBD_MIDI_MSC_CfgDesc[MIDI_MSC_CONFIG_DESC_SIZE] = {
/* Configuration 1 */
        0x09, /* bLength */
        USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
        MIDI_MSC_CONFIG_DESC_SIZE, //LOBYTE(MIDI_MSC_CONFIG_DESC_SIZE),        /* wTotalLength  */
		0x00, //HIBYTE(MIDI_MSC_CONFIG_DESC_SIZE),
		0x03, /* bNumInterfaces: two interfaces*/
		0x01, /* bConfigurationValue: ID of this configuration */
		0x00, /* iConfiguration: Unused*/
		0x80, /* bmAttributes  = bus powered */
		0x32, /* bMaxPower = 100 mA*/
		/* 09 byte*/

		// B.3.1 Standard AC Interface Descriptor
		/* Audio Control standard */
		0x09, /* sizeof(usbDescrInterface): length of descriptor in bytes */
		0x04, /* interface descriptor type */
		MIDI_INTERFACE0, /* index of this interface */
		0x00, /* alternate setting for this interface */
		0x00, /* endpoints excl 0: number of endpoint descriptors to follow */
		0x01, /* AUDIO */
		0x01, /* AUDIO_Control*/
		0x00, /* Unused*/
		0x00, /* string index for interface : Unused*/

		// B.3.2 Class-specific AC Interface Descriptor
		/* AudioControl   Class-Specific descriptor */
		0x09, /* sizeof(usbDescrCDC_HeaderFn): length of descriptor in bytes */
		0x24, /* descriptor type */
		0x01, /* this is header functional descriptor */
		0x0, 0x01, /* bcdADC: revision 1.0*/
		0x09, 0x00, /* wTotalLength : Total size of class specific descriptors.*/
		0x01, /*Number of streaming interfaces. */
		0x01, /*MIDIStreaming interface 1 belongs to this AudioControl interface. */

		// B.4 MIDIStreaming Interface Descriptors

		// B.4.1 Standard MS Interface Descriptor
		/* PreenFM Standard interface descriptor */
		0x09, /* bLength */
		0x04, /* bDescriptorType: Interface descriptor */
		MIDI_INTERFACE1, /* bInterfaceNumber: Index of this interface. */
		0x00, /* bAlternateSetting: Index of this alternate setting. */
		0x02, /* bNumEndpoints: 2 endpoints */
		USB_DEVICE_CLASS_AUDIO, /* bInterfaceClass */
		USB_DEVICE_SUBCLASS_MIDISTREAMING, /* bInterfaceSubClass : MIDIStreaming*/
		0x00, /* InterfaceProtocol: NOT USED */
		0x00, /* iInterface : NOT USED*/
		/* 09 byte*/

		// B.4.2 Class-specific MS Interface Descriptor
		/* MS Class-Specific descriptor */
		0x07, /* length of descriptor in bytes */
		0x24, /* descriptor type: CS_INTERFACE descriptor. */
		0x01, /* header functional descriptor */
		0x0, 0x01, /* bcdADC: Revision of this class specification. */
		/*CLASS_SPECIFIC_DESC_SIZE*/0x32, 0, /* wTotalLength : 7+6+9+6+9+9+5+9+5*/

		// B.4.3 MIDI IN Jack Descriptor

		// Midi in Jack Descriptor (Embedded)
		0x06, /* bLength */
		0x24, /* descriptor type */
		0x02, /* MIDI_IN_JACK desc subtype */
		0x01, /* EMBEDDED bJackType */
		0x01, /* bJackID: ID of this Jack*/
		0x00, /* UNUSED */

		// Table B4.4
		// Midi Out Jack Descriptor (Embedded)
		0x09, /* length of descriptor in bytes */
		0x24, /* descriptor type: CS_INTERFACE descriptor. */
		0x03, /* MIDI_OUT_JACK descriptor */
		0x01, /* EMBEDDED bJackType */
		0x02, /* bJackID ID of this Jack*/
		0x01, /* No of input pins */
		0x02, /* ID of the Entity to which this Pin is connected. */
		0x01, /* Output Pin number of the Entity to which this Input Pin is connected. */
		0X00, /* iJack : UNUSED */

		// ===== B.5 Bulk OUT Endpoint Descriptors
		//B.5.1 Standard Bulk OUT Endpoint Descriptor
		0x09, /* bLenght */
		0x05, /* bDescriptorType = endpoint */
		MIDI_OUT_EP, /* bEndpointAddress OUT endpoint number 1 */
		0x02, /* bmAttributes: 2:Bulk, 3:Interrupt endpoint */
		0x40, 0X00, /* wMaxPacketSize 64 bytes per packet. */
		0x00, /* bIntervall in ms : ignored for bulk*/
		0x00, /* bRefresh Unused */
		0x00, /* bSyncAddress Unused */

		// B.5.2 Class-specific MS Bulk OUT Endpoint Descriptor
		0x05, /* bLength of descriptor in bytes */
		0x25, /* bDescriptorType */
		0x01, /* bDescriptorSubtype : GENERAL */
		0x01, /* bNumEmbMIDIJack  */
		0x01, /* baAssocJackID (0) ID of the Embedded MIDI IN Jack. */

		//B.6 Bulk IN Endpoint Descriptors
		//B.6.1 Standard Bulk IN Endpoint Descriptor
		0x09, /* bLenght */
		0x05, /* bDescriptorType = endpoint */
		MIDI_IN_EP, /* bEndpointAddress IN endpoint number 1 */
		0X02, /* bmAttributes: 2: Bulk, 3: Interrupt endpoint */
		0x40, 0X00, /* wMaxPacketSize */
		0X00, /* bIntervall in ms */
		0X00, /* bRefresh */
		0X00, /* bSyncAddress */

		// B.6.2 Class-specific MS Bulk IN Endpoint Descriptor
		0X05, /* bLength of descriptor in bytes */
		0X25, /* bDescriptorType */
		0x01, /* bDescriptorSubtype */
		0X01, /* bNumEmbMIDIJack (0) */
		0X02, /* baAssocJackID (0) ID of the Embedded MIDI OUT Jack	*/

   	    /********************  Mass Storage interface ********************/
	    0x09,   /* bLength: Interface Descriptor size */
	    0x04,   /* bDescriptorType: *//* interface descriptor type */
	    MSC_INTERFACE,   /* bInterfaceNumber: Interface Number*/
	    0x00,   /* bAlternateSetting: Alternate setting */
	    0x02,   /* bNumEndpoints*/
	    0x08,   /* bInterfaceClass: MSC Class */
	    0x06,   /* bInterfaceSubClass : SCSI transparent*/
	    0x50,   /* nInterfaceProtocol */
	    0x05,          /* iInterface: */
	    /********************  Mass Storage Endpoints ********************/
	    0x07,   /*Endpoint descriptor length = 7*/
	    0x05,   /*Endpoint descriptor type */
	    MSC_IN_EP,   /*Endpoint address (IN, address 1) */
	    0x02,   /*Bulk endpoint type */
	    LOBYTE(MSC_MAX_PACKET),
	    HIBYTE(MSC_MAX_PACKET),
	    0x00,   /*Polling interval in milliseconds */

	    0x07,   /*Endpoint descriptor length = 7 */
	    0x05,   /*Endpoint descriptor type */
	    MSC_OUT_EP,   /*Endpoint address (OUT, address 1) */
	    0x02,   /*Bulk endpoint type */
	    LOBYTE(MSC_MAX_PACKET),
	    HIBYTE(MSC_MAX_PACKET),
	    0x00     /*Polling interval in milliseconds*/
        //9+7+7

};


static uint8_t USBD_MIDI_MSC_Init(void *pdev, uint8_t cfgidx) {
	USBD_MIDI_Init(pdev, cfgidx);
	USBD_MSC_Init(pdev, cfgidx);
	PRINTF("     USBD_MIDI_MSC_Init finished\n");
	return USBD_OK;
}


static uint8_t USBD_MIDI_MSC_DeInit(void *pdev, uint8_t cfgidx) {
	USBD_MIDI_DeInit(pdev, cfgidx);
	USBD_MSC_DeInit(pdev, cfgidx);
	PRINTF("     USBD_MIDI_MSC_DeInit finished\n");
	return USBD_OK;
}

static uint8_t USBD_MIDI_MSC_Setup(void *pdev, USB_SETUP_REQ *req) {
	{
	  PRINTF("     USBD_MIDI_MSC_Setup, req->wIndex: %d \n",req->wIndex);
	  switch (req->bmRequest & USB_REQ_RECIPIENT_MASK)
	  {
	  case USB_REQ_RECIPIENT_INTERFACE:
	    if (req->wIndex == MSC_INTERFACE)
	    {
	      return (USBD_MSC_Setup (pdev, req));
	    }
	    else
	    {
	      return (USBD_MIDI_Setup(pdev, req));
	    }

	  case USB_REQ_RECIPIENT_ENDPOINT:
	    if (req->wIndex == MIDI_IN_EP)
	    {
	      return (USBD_MIDI_Setup (pdev, req));
	    }
	    else
	    {
	      return (USBD_MSC_Setup(pdev, req));
	    }
	  }
	  return USBD_OK;
	}
}
static uint8_t USBD_MIDI_MSC_EP0_RxReady(void *pdev) {
	return 0;
}

static uint8_t USBD_MIDI_MSC_DataIn(void *pdev, uint8_t epnum) {

	/*DataIN can be for MSC or MIDI */
	  PRINTF("     USBD_MIDI_MSC_DataIn, epnum: %d \n",epnum);

	if (epnum == (MSC_IN_EP & ~0x80)) {
		return (USBD_MSC_DataIn(pdev, epnum));
	} else {
		return (USBD_MIDI_DataIn(pdev, epnum));
	}
}


static uint8_t USBD_MIDI_MSC_DataOut(void *pdev, uint8_t epnum) {

	/*DataOut can be for MSC or MIDI */
	  PRINTF("     USBD_MIDI_MSC_DataOut, epnum: %d \n",epnum);

	if (epnum == MSC_OUT_EP) {
		return (USBD_MSC_DataOut(pdev, epnum));
	} else {
		return (USBD_MIDI_DataOut(pdev, epnum));
	}
}

static uint8_t USBD_MIDI_MSC_SOF(void *pdev) {
	return USBD_OK;
}

static uint8_t USBD_MIDI_MSC_OUT_Incplt(void *pdev) {
	return USBD_OK;
}
static uint8_t *USBD_MIDI_MSC_GetCfgDesc(uint8_t speed, uint16_t *length) {
	*length = sizeof(USBD_MIDI_MSC_CfgDesc);
	return USBD_MIDI_MSC_CfgDesc;
}
