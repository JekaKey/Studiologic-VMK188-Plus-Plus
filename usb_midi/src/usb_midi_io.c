//#include "usb_fifo.h"
#include "usb_midi_io.h"
#include "usb_dcd.h"
#include "midi.h"
                      



//fifo_t usb_fifo_buff; //Midi IO interface buffer
uint8_t message_buff[4];
extern USB_OTG_CORE_HANDLE     USB_OTG_dev;


void usb_fifo_init(void){
//	fifo_init(&usb_fifo_buff);
}



static void usb_midi_DataTx (uint8_t* Buf, uint32_t Len) 
{
	 DCD_EP_Tx (&USB_OTG_dev, 0x81, Buf, 4);
}





void sendUSB_NoteOn(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel){
	
   message_buff[0]=0x09;
   message_buff[1]=NoteOn ^ Channel;    
   message_buff[2]=NoteNumber;          
   message_buff[3]=(uint8_t)(Velocity>>7);
	 usb_midi_DataTx (message_buff, 4);	
}


void sendUSB_NoteOff(uint8_t NoteNumber, uint16_t Velocity, uint8_t Channel){
	
   message_buff[0]=0x08;
   message_buff[1]=NoteOff ^ Channel;    
   message_buff[2]=NoteNumber;          
   message_buff[3]=(uint8_t)(Velocity>>7);
	 usb_midi_DataTx (message_buff, 4);	
}


void sendUSB_ControlChange(uint8_t ControlNumber, uint8_t ControlValue, uint8_t Channel) {
	
   message_buff[0]=0x0B;
   message_buff[1]=ControlChange ^ Channel;    
   message_buff[2]=ControlNumber;          
   message_buff[3]=ControlValue;
	 usb_midi_DataTx (message_buff, 4);		
	
 }


