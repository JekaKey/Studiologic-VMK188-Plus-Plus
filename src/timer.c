
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

//	Start key scan timer
void TIM4_init(void){

	TIM_TimeBaseInitTypeDef timer;

	TIM_TimeBaseStructInit(&timer);
	timer.TIM_Prescaler = TIMER_PRESCALER - 1;
	timer.TIM_Period = TIMER_TIMPERIOD - 1;
	timer.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &timer);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}

