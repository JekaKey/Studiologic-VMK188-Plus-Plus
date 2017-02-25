
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"


#include "timer.h"
#include "controls.h"
#include "midi.h"
#include "presets.h"
#include "keyboardscan.h"
#include "usb_midi_io.h"


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


static uint32_t USB_counter=0;

void TIM4_IRQHandler() {

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		readKeyState();
		USB_counter++;
		if (USB_counter>1000/TIMER_TIMPERIOD){
			   usb_midi_refresh();
			   USB_counter=0;
		}
		read_controls(Preset.sliders, Calibration.calibr);
		read_buttons_state();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}



void TIM6_init (){

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // Enable TIM6 clock
	TIM6->PSC = 41999; // Set prescaler to 41999
	TIM6->CR1 |= TIM_CR1_OPM; // One pulse mode
	TIM6->EGR |= TIM_EGR_UG; // Force update
	TIM6->SR &= ~TIM_SR_UIF; // Clear the update flag
	TIM6->DIER |= TIM_DIER_UIE; // Enable interrupt on update event
	NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ

}

static uint8_t TIM6_message;


void TIM6start (uint32_t delay, uint8_t mes){//ms ~30 seconds maximum
	TIM6_message=mes;
	TIM6->ARR = delay<<1; // Set auto-reload to 5999
	TIM6->CR1 |= TIM_CR1_CEN; // Enable TIM6 counter
}


void TIM6_DAC_IRQHandler() {
    if((TIM6->SR & TIM_SR_UIF) != 0){                      // If update flag is set
     send_message(TIM6_message);
     TIM6->SR &= ~TIM_SR_UIF;                            // Interrupt has been handled
    }
}

void TIM7_init (){

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; // Enable TIM6 clock
	TIM7->PSC = 41999; // Set prescaler to 41999
	TIM7->CR1 |= TIM_CR1_OPM; // One pulse mode
	TIM7->EGR |= TIM_EGR_UG; // Force update
	TIM7->SR &= ~TIM_SR_UIF; // Clear the update flag
	TIM7->DIER |= TIM_DIER_UIE; // Enable interrupt on update event
	NVIC_EnableIRQ(TIM7_IRQn); // Enable TIM6 IRQ

}

static uint8_t TIM7_message;


void TIM7start (uint32_t delay, uint8_t mes){//ms ~30 seconds maximum
	TIM7_message=mes;
	TIM7->ARR = delay<<1; // Set auto-reload to 5999
	TIM7->CR1 |= TIM_CR1_CEN; // Enable TIM6 counter
}


void TIM7_IRQHandler() {
    if((TIM7->SR & TIM_SR_UIF) != 0){                      // If update flag is set
     send_message(TIM7_message);
     TIM7->SR &= ~TIM_SR_UIF;                            // Interrupt has been handled
    }
}


