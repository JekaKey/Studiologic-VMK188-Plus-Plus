
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"


#include "timer.h"
#include "controls.h"

volatile uint32_t timerTicks = 0;



void checkTimer(timer_counter_t * counter, uint8_t mes) {
	if (counter->period && timerTicks - counter->old >= counter->period) {
		send_message(mes);
		counter->period = 0;
	}
}

void setTimerMs (timer_counter_t * counter, uint16_t value){
	counter->period = value * 1000 / TIMER_TIMPERIOD;
	counter->old = timerTicks;
}

