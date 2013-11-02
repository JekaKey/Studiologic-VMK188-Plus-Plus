#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "sliders.h"
#include "midi.h"
#include "usb_midi_io.h"

FlagStatus ADC_GetFlagStatus1(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

	/* Check the status of the specified ADC flag */
	if ((ADCx->SR & ADC_FLAG) != (uint8_t) RESET) {
		/* ADC_FLAG is set */
		bitstatus = SET;
	} else {
		/* ADC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ADC_FLAG status */
	return bitstatus;
}

uint16_t readADC(uint8_t channel, uint8_t index) {
	switch (index) {
	case 0:
		ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_28Cycles);
		//Start
		ADC_SoftwareStartConv(ADC1);
		//Wait while a voltage is converting to a value
		while (((ADC1->SR & ADC_FLAG_EOC) == RESET)) {
			__NOP();
		}
		//Reset status
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
		//Return a result
		return ADC_GetConversionValue(ADC1);
		break;
	case 1:
		ADC_RegularChannelConfig(ADC2, channel, 1, ADC_SampleTime_28Cycles);
		//Start
		ADC_SoftwareStartConv(ADC2);
		//Wait while a voltage is converting to a value
		while (((ADC2->SR & ADC_FLAG_EOC) == RESET)) {
			__NOP();
		}
		//Reset status
		ADC_ClearFlag(ADC2, ADC_FLAG_EOC);
		//Return a result
		return ADC_GetConversionValue(ADC2);
		break;
	case 2:
		ADC_RegularChannelConfig(ADC3, channel, 1, ADC_SampleTime_28Cycles);
		//Start
		ADC_SoftwareStartConv(ADC3);
		//Wait while a voltage is converting to a value
		while (((ADC3->SR & ADC_FLAG_EOC) == RESET)) {
			__NOP();
		}
		//Reset status
		ADC_ClearFlag(ADC3, ADC_FLAG_EOC);
		//Return a result
		return ADC_GetConversionValue(ADC3);
		break;
	}
}

/**DocID022945 Rev 4 29/33
 AN4073 Averaging of N-X ADC samples: source code
 * @brief Sort the N ADC samples
 * @param ADC samples to be sorted
 * @param Numbre of ADC samples to be sorted
 * @retval None
 */
void Sort_tab(uint16_t tab[], uint8_t lenght) {
	uint8_t l = 0x00, exchange = 0x01;
	uint16_t tmp = 0x00;
	/* Sort tab */
	while (exchange == 1) {
		exchange = 0;
		for (l = 0; l < lenght - 1; l++) {
			if (tab[l] > tab[l + 1]) {
				tmp = tab[l];
				tab[l] = tab[l + 1];
				tab[l + 1] = tmp;
				exchange = 1;
			}
		}
	}
}

/**
 * @brief Get the average of N-X ADC samples
 * @param Numbre of ADC samples to be averaged
 * @param Numbre of ADC samples to be averaged
 * @retval The average value
 */

uint16_t ADC_last[3];

uint16_t ADC_GetSample(uint16_t delta, uint8_t index) {
	uint16_t adc_sample, adc_change;
	adc_sample = readADC(ADC_Channel_11, index);
	if (adc_sample > ADC_last[index]) {
		adc_change = adc_sample - ADC_last[index];
	} else {
		adc_change = ADC_last[index] - adc_sample;
	}
	if (adc_change > delta) {
		ADC_last[index] = adc_sample;
		return adc_sample >> 5;
	} else {
		return ADC_last[index] >> 5;
	}
}

uint16_t ADC_GetSampleAvgNDeleteX(uint8_t N, uint8_t X) {
	uint32_t avg_sample = 0x00;
	uint16_t adc_sample[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t index = 0x00;
	for (index = 0x00; index < N; index++) {
		/* ADC start conv */
		//        ADC_SoftwareStartConv(ADC1);
		/* Wait end of conversion */
		//        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		/* Store ADC samples */
		// adc_sample[index] = ADC_GetConversionValue(ADC1);
		adc_sample[index] = readADC1(ADC_Channel_11);
	}
	/* Sort the N-X ADC samples */
	Sort_tab(adc_sample, N);
	/* Add the N ADC samples */
	for (index = X / 2; index < N - X / 2; index++) {
		avg_sample += adc_sample[index];
	}
	/* Compute the average of N-X ADC sample */
	avg_sample /= N - X;
	/* Return average value */
	return avg_sample;
}

uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min,
		uint8_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void init_ADC() {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef adc_init;

	/*ADC1*/
	/* ADC clock enabled*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/*ADC reset*/
	ADC_DeInit();

	/*ADCs work independently*/
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;

	/*scan conversion turned on*/
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	/*Do not use long conversion*/
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

	/*start programm based conversion, don't use the trigger*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
	/*12 bit conversion, the result in the 12 low bits*/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	/*Initialization*/
	ADC_CommonInit(&adc_init);

	ADC_Init(ADC1, &ADC_InitStructure);
	/*Switch on ADC*/
	ADC_Cmd(ADC1, ENABLE);

	/*ADC2*/
	/* ADC clock enabled*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	/*ADC reset*/
	ADC_DeInit();

	/*ADCs work independently*/
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;

	/*scan conversion turned on*/
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	/*Do not use long conversion*/
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

	/*start programm based conversion, don't use the trigger*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
	/*12 bit conversion, the result in the 12 low bits*/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	/*Initialization*/
	ADC_CommonInit(&adc_init);

	ADC_Init(ADC2, &ADC_InitStructure);
	/*Switch on ADC*/
	ADC_Cmd(ADC2, ENABLE);

	/*ADC3*/
	/* ADC clock enabled*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	/*ADC reset*/
	ADC_DeInit();

	/*ADCs work independently*/
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;

	/*scan conversion turned on*/
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	/*Do not use long conversion*/
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

	/*start programm based conversion, don't use the trigger*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
	/*12 bit conversion, the result in the 12 low bits*/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	/*Initialization*/
	ADC_CommonInit(&adc_init);

	ADC_Init(ADC3, &ADC_InitStructure);
	/*Switch on ADC*/
	ADC_Cmd(ADC3, ENABLE);

}

static void mux_switch(uint8_t value) { //Switch multiplexors to next ring state
	switch (value) {
	case 0:
		GPIOE->BSRRL = GPIO_Pin_0;
		GPIOE->BSRRL = GPIO_Pin_1;
		GPIOE->BSRRL = GPIO_Pin_2;
		break;
	case 1:
		GPIOE->BSRRH = GPIO_Pin_0;
	case 2:
		GPIOE->BSRRL = GPIO_Pin_0;
		GPIOE->BSRRH = GPIO_Pin_1;
	case 3:
		GPIOE->BSRRH = GPIO_Pin_0;
	case 4:
		GPIOE->BSRRL = GPIO_Pin_0;
		GPIOE->BSRRL = GPIO_Pin_1;
		GPIOE->BSRRH = GPIO_Pin_2;
		break;
	case 5:
		GPIOE->BSRRH = GPIO_Pin_0;
		break;
	case 6:
		GPIOE->BSRRL = GPIO_Pin_0;
		GPIOE->BSRRH = GPIO_Pin_1;
		break;
	case 7:
		GPIOE->BSRRH = GPIO_Pin_0;
	}
}

Slider_type sliders[24];

void init_sliders(void) {
	uint8_t i;

	sliders[SLIDER_EMPTY].active = 0;

	for(i=0;i<8;i++){
		sliders[i].active = 0;
		sliders[i].reverse = 0;
		sliders[i].channel = 0;
		sliders[i].min_in_value = SLIDER_S_MIN_IN;
		sliders[i].max_in_value = SLIDER_S_MAX_IN;
		sliders[i].min_out_value = SLIDER_S_MIN_OUT;
		sliders[i].max_out_value = SLIDER_S_MAX_OUT;

	}

	for(i=9;i<16;i++){
		sliders[i].active = 0;
		sliders[i].reverse = 0;
		sliders[i].channel = 0;
		sliders[i].min_in_value = SLIDER_R_MIN_IN;
		sliders[i].max_in_value = SLIDER_R_MAX_IN;
		sliders[i].min_out_value = SLIDER_R_MIN_OUT;
		sliders[i].max_out_value = SLIDER_R_MAX_OUT;

	}

	sliders[SLIDER_S1].active = 0;
	sliders[SLIDER_S1].reverse = 0;
	sliders[SLIDER_S1].channel = 0;
	sliders[SLIDER_S1].event = 7;
	sliders[SLIDER_S1].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S1].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S1].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S1].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_P2].active = 1;
	sliders[SLIDER_P2].reverse = 0;
	sliders[SLIDER_P2].channel = 0;
	sliders[SLIDER_P2].event = 64;
	sliders[SLIDER_P2].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P2].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P2].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P2].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P1].active = 0;
	sliders[SLIDER_P1].reverse = 0;
	sliders[SLIDER_P1].channel = 0;
	sliders[SLIDER_P1].event = 65;
	sliders[SLIDER_P1].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P1].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P1].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P1].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P1].active = 0;
	sliders[SLIDER_P1].reverse = 0;
	sliders[SLIDER_P1].channel = 0;
	sliders[SLIDER_P1].event = 66;
	sliders[SLIDER_P1].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P1].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P1].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P1].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_PITCH].active = 0;
	sliders[SLIDER_PITCH].reverse = 0;
	sliders[SLIDER_PITCH].channel = 0;
	sliders[SLIDER_PITCH].event = 66;
	sliders[SLIDER_PITCH].min_in_value = SLIDER_PITCH_MIN_IN;
	sliders[SLIDER_PITCH].max_in_value = SLIDER_PITCH_MAX_IN;
	sliders[SLIDER_PITCH].min_out_value = SLIDER_PITCH_MIN_OUT;
	sliders[SLIDER_PITCH].max_out_value = SLIDER_PITCH_MAX_OUT;

	sliders[SLIDER_MOD].active = 0;
	sliders[SLIDER_MOD].reverse = 0;
	sliders[SLIDER_MOD].channel = 0;
	sliders[SLIDER_MOD].event = 1;
	sliders[SLIDER_MOD].min_in_value = SLIDER_MOD_MIN_IN;
	sliders[SLIDER_MOD].max_in_value = SLIDER_MOD_MAX_IN;
	sliders[SLIDER_MOD].min_out_value = SLIDER_MOD_MIN_OUT;
	sliders[SLIDER_MOD].max_out_value = SLIDER_MOD_MAX_OUT;

	sliders[SLIDER_AT].active = 0;
	sliders[SLIDER_AT].reverse = 0;
	sliders[SLIDER_AT].channel = 0;
	sliders[SLIDER_AT].event = 66;
	sliders[SLIDER_AT].min_in_value = SLIDER_AT_MIN_IN;
	sliders[SLIDER_AT].max_in_value = SLIDER_AT_MAX_IN;
	sliders[SLIDER_AT].min_out_value = SLIDER_AT_MIN_OUT;
	sliders[SLIDER_AT].max_out_value = SLIDER_AT_MAX_OUT;



}

static uint16_t adc_counter = 0; //adc (multiplexor chip) number 0..2
static uint16_t mux_counter = 0; //Multiplexor pin number 0..7
static uint16_t ticks_counter = 0; // timer interrupts ticks counter

void read_sliders() {
	uint16_t slider_number; // Slider number from 0 to 23;
	uint16_t adc_value;
	ticks_counter++;
	if (ticks_counter > SLIDERS_TICKS_FACTOR) { // Only one per SLIDERS_TICKS_FACTOR
		ticks_counter = 0;
		if (adc_counter > 2) {
			adc_counter = 0;
			mux_switch(mux_counter);
			mux_counter++;
			if (mux_counter > 7) {
				mux_counter = 0;
			}
		} else {
			slider_number = mux_counter * 3 + adc_counter;
			if (sliders[slider_number].active) {
				adc_value = ADC_GetSample(SLIDERS_DELTA, adc_counter);
				if (adc_value != sliders[slider_number].value) {
					__NOP();
					sliders[slider_number].value = adc_value;
					sendControlChange(sliders[slider_number].event, adc_value,
							0);
					sendUSB_ControlChange(sliders[slider_number].event,
							adc_value, 0);
				}
			}
			adc_counter++;
		}
	}

}

