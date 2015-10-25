#ifndef FILTER__H
#define FILTER__H


#include "stm32f4xx.h"


#define M_PI 3.14159265358979323846


#define STOPPER 0                                      /* Smaller than any datum */
#define NULL_POINTER 0                                      /* Smaller than any datum */
#define MEDIAN_FILTER_SIZE    (21)


#define NUMBER_OF_BUFFERS 24

struct pair
{
  struct pair *point;                              /* Pointers forming list linked in sorted order */
  uint16_t  value;                                   /* Values to sort */
};


typedef struct {
   struct pair buffer[MEDIAN_FILTER_SIZE];
   struct pair *datpoint;               /* Pointers into circular buffer of data */
   struct pair small;          /* Chain stopper */
   struct pair big;                /* Pointer to head (largest) of linked list.*/
}filter_storage_t;

uint16_t median(uint16_t* a);
void median_filter_init(void);
uint16_t median_filter(uint16_t value, filter_storage_t * buff);

#endif //FILTER__H

