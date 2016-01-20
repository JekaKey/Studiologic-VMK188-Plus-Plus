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
void TIM6_init (uint32_t delay);
void TIM7_init (uint32_t delay);
void TIM7start (void);
void TIM6start (void);

#endif //__TIMER_H
