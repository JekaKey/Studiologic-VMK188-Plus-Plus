#include "usb_fifo.h"
#include <stm32f4xx.h>

s8 fifo_put(fifo_t *fifo, void *data,  uint32_t count)
{
	uint32_t i;
  if ((FIFO_LENGTH - fifo->count) < count)                      
    return -1;                                                  
  for (i = 0; i < count; i++)               
  {
    fifo->data[fifo->tail++] =((u8*) data)[i];                  
    fifo->count++;                                             
    if (fifo->tail == FIFO_LENGTH)                              
    {
      fifo->tail=0;                                           
    }                                                         
  }
  return 0;                                                    
}

s8 fifo_get(fifo_t *fifo, void *data,  uint32_t count)
{
	uint32_t i;
  if (fifo->count < count)                                     
    return -1;                                                  
  for (i = 0; i < count; i++)               
  {
    ((u8*)data)[i] = fifo->data[fifo->head++];                
    fifo->count--;                                            
    if (fifo->head == FIFO_LENGTH)                             
    {
      fifo->head=0;                                            
    }
  }
  return 0;
}

u8 fifo_count(fifo_t *fifo)
{
  return fifo->count;
}

void fifo_init(fifo_t *fifo)
{
  fifo->head = fifo->tail = fifo->count = 0;
}
