#include "usb_midi_io.h"
#include "usb_dcd.h"
#include "midi.h"
#include "fifo.h"
#include "usbd_core.h"


extern USB_OTG_CORE_HANDLE USB_OTG_dev;
//static uint8_t USB_TxBufferBusy;
//static uint8_t USB_RxBufferBusy;
static uint8_t USB_transferPossible=0;


FIFO32(128) USB_midi_packets_in;

void USB_MIDI_ChangeConnectionState(uint8_t connected){
	FIFO_FLUSH(USB_midi_packets_in);
	if (connected){
//		USB_TxBufferBusy=0;
	    USB_transferPossible=1;
	}else{
//		USB_TxBufferBusy=1;
	    USB_transferPossible=0;
	}
}



void usb_midi_refresh(void){
	uint32_t buf[128];
	uint8_t count=FIFO_COUNT(USB_midi_packets_in);
	if (count && USB_transferPossible){
	    for (uint8_t i=0; i<count; i++){
	    	buf[i]=FIFO_FRONT(USB_midi_packets_in);
	    	FIFO_POP(USB_midi_packets_in);
	    }
		DCD_EP_Tx(&USB_OTG_dev, MIDI_IN_EP, (uint8_t*)buf, count<<2);
	}
}

//void usb_midi_DataSend(uint8_t* Buf, uint32_t Len) {
//	volatile uint32_t timeout = 100000;
//	while (USB_Tx_State && timeout) {
//		timeout--;
//	}
//	if (timeout) {
//		USB_Tx_State = 1;
//		DCD_EP_Tx(&USB_OTG_dev, MIDI_IN_EP, Buf, Len);
//	}
//}


void usb_midi_DataSend(uint8_t* Buf, uint32_t Len) {
	    uint32_t packedge;
	    uint32_t len=Len>>2;
	    for(uint32_t i=0; i<len; i++){
	       packedge=*(uint32_t*)Buf;
	       FIFO_PUSH(USB_midi_packets_in, packedge);
	       Buf+=4;
	    }
}

