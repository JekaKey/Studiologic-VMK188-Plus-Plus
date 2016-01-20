#ifndef __TIMER_H
#define __TIMER_H

#define TIMER_PRESCALER 84
#define TIMER_TIMPERIOD 20

typedef struct
{
	uint32_t period;
    uint32_t old;
} timer_counter_t;


void checkTimer(timer_counter_t * counter, uint8_t mes);
void setTimerMs(timer_counter_t * counter, uint16_t value);
void TIM4_init(void);

#endif //__TIMER_H
