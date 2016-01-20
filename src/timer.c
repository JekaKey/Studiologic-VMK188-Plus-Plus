
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"


#include "timer.h"
#include "controls.h"
#include "midi.h"
#include "presets.h"
#include "keyboardscan.h"
#include "leds.h"


void TIM4_init(void){

	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructInit(&timer);
	timer.TIM_Prescaler = TIMER_PRESCALER - 1;
	timer.TIM_Period = TIMER_TIMPERIOD - 1;
	timer.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &timer);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);

}


void TIM4_IRQHandler() {

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		readKeyState();
		read_controls(Preset.sliders, Calibration.calibr);
		read_buttons_state();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}



void TIM6_init (uint32_t delay){//ms

	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);


	TIM_TimeBaseStructInit(&timer);
	timer.TIM_Prescaler = 24000 - 1;
	timer.TIM_Period = delay - 1;
	timer.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM6, &timer);

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

static uint8_t TIM6_is_finished=0;


void TIM6start (void){//used for temp messages
	TIM6_is_finished=0;
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}


void TIM6_DAC_IRQHandler() {
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
		if (TIM6_is_finished) {
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //clear interrupt bit
			TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM6, DISABLE);
			NVIC_DisableIRQ(TIM6_DAC_IRQn);
			send_message(MES_TIMER_END);
		} else {
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //clear interrupt bit
			TIM6_is_finished = 1;
		}
	}
}

void TIM7_init (uint32_t delay){//ms

	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseStructInit(&timer);
	timer.TIM_Prescaler = 2400 - 1;
	timer.TIM_Period = delay - 1;
	timer.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM7, &timer);

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

static uint8_t TIM7_is_finished=0;


void TIM7start (void){//used for temp messages
	TIM7_is_finished=0;
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM7, ENABLE);
	NVIC_EnableIRQ(TIM7_IRQn);
}


void TIM7_IRQHandler() {
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update); //clear interrupt bit
		if (TIM7_is_finished) {
			TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM7, DISABLE);
			NVIC_DisableIRQ(TIM7_IRQn);
			send_message(MES_MSCSTOP_TIMER_END);
		} else {
			TIM7_is_finished = 1;
		}
	}
}


