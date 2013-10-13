
#ifndef FIFO_H
#define FIFO_H

#include "stm32f4xx.h"

#define FIFO_LENGTH 1024


typedef struct {
  u8 data[FIFO_LENGTH];
  uint32_t head;
  uint32_t tail;
  uint32_t count;
} fifo_t;


void fifo_init(fifo_t *fifo);

s8 fifo_put(fifo_t *fifo, void *data,  uint32_t count);

s8 fifo_get(fifo_t *fifo, void *data, uint32_t count);

u8 fifo_count(fifo_t *fifo);

#endif
