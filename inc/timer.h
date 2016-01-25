#ifndef __TIMER_H
#define __TIMER_H

#define TIMER_PRESCALER 84
#define TIMER_TIMPERIOD 20

typedef struct
{
	uint32_t period;
    uint32_t old;
} timer_counter_t;


void TIM4_init(void);
void TIM6_init (void);
void TIM7_init (void);
void TIM6start (uint32_t delay, uint8_t mes);//ms
void TIM7start (uint32_t delay, uint8_t mes);//ms

#endif //__TIMER_H
