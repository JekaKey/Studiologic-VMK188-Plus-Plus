#include "stm32f4xx.h"
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

uint16_t readADC1(uint8_t channel) {
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_28Cycles);
	//Р вЂ™Р’В Р В Р вЂ¦Р В Р’В°Р РЋРІР‚РЋР В РЎвЂ�Р В Р вЂ¦Р В Р’В°Р В Р’ВµР В РЎпїЅР вЂ™Р’В Р РЋР вЂљР В Р’В°Р В Р’В±Р В РЎвЂўР РЋРІР‚С™Р РЋРЎвЂњ
	ADC_SoftwareStartConv(ADC1);
	//Р вЂ™Р’В Р В Р’В¶Р В РўвЂ�Р РЋРІР‚пїЅР В РЎпїЅР вЂ™Р’В Р В РЎвЂ”Р В РЎвЂўР В РЎвЂќР В Р’В°Р вЂ™Р’В Р В РЎвЂ”Р РЋР вЂљР В Р’ВµР В РЎвЂўР В Р’В±Р РЋР вЂљР В Р’В°Р В Р’В·Р РЋРЎвЂњР В Р’ВµР РЋРІР‚С™Р РЋР С“Р РЋР РЏР вЂ™Р’В Р В Р вЂ¦Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР РЋР РЏР В Р’В¶Р В Р’ВµР В Р вЂ¦Р В РЎвЂ�Р В Р’ВµР вЂ™Р’В Р В Р вЂ Р вЂ™Р’В Р В РЎвЂќР В РЎвЂўР В РўвЂ�
	while (((ADC1->SR & ADC_FLAG_EOC) == RESET)) {
		__NOP();
	}
	//Р вЂ™Р’В Р В РЎвЂўР РЋРІР‚РЋР В РЎвЂ�Р РЋРІР‚В°Р В Р’В°Р В Р’ВµР В РЎпїЅР вЂ™Р’В Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р РЋРІР‚С™Р РЋРЎвЂњР РЋР С“
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC); //Р В РІР‚СњР В РЎвЂўР В Р’В±Р В Р’В°Р В Р вЂ Р В РЎвЂ�Р В Р’В»Р вЂ™Р’В Р В Р вЂ Р вЂ™Р’В Р В РЎвЂќР В Р’В°Р РЋРІР‚РЋР В Р’ВµР РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В Р’ВµР вЂ™Р’В Р РЋРІР‚С™Р В Р’ВµР РЋР С“Р РЋРІР‚С™Р В Р’В°
	//Р вЂ™Р’В Р В Р вЂ Р В РЎвЂўР В Р’В·Р В Р вЂ Р РЋР вЂљР В Р’В°Р РЋРІР‚В°Р В Р’В°Р В Р’ВµР В РЎпїЅР вЂ™Р’В Р РЋР вЂљР В Р’ВµР В Р’В·Р РЋРЎвЂњР В Р’В»Р РЋР Р‰Р РЋРІР‚С™Р В Р’В°Р РЋРІР‚С™
	return ADC_GetConversionValue(ADC1);
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

uint16_t ADC_last;

uint16_t ADC_GetSample(uint16_t delta) {
	uint16_t adc_sample, adc_change;
	adc_sample = readADC1(ADC_Channel_11);
	if (adc_sample > ADC_last) {
		adc_change = adc_sample - ADC_last;
	} else {
		adc_change = ADC_last - adc_sample;
	}
	if (adc_change > delta) {
		ADC_last = adc_sample;
		return adc_sample >> 5;
	} else {
		return ADC_last >> 5;
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
	/* Р РЋР вЂљР В Р’В°Р В Р’В·Р РЋР вЂљР В Р’ВµР РЋРІвЂљВ¬Р В Р’В°Р В Р’ВµР В РЎпїЅ Р РЋРІР‚С™Р В Р’В°Р В РЎвЂќР РЋРІР‚С™Р В РЎвЂ�Р РЋР вЂљР В РЎвЂўР В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ AР В Р’В¦Р В РЎСџ1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Р РЋР С“Р В Р’В±Р РЋР вЂљР В Р’В°Р РЋР С“Р РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В Р вЂ¦Р В Р’В°Р РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р В РЎвЂќР В РЎвЂ� Р В РЎвЂ™Р В Р’В¦Р В РЎСџ */
	ADC_DeInit();

	/* Р В РЎвЂ™Р В Р’В¦Р В РЎСџ Р РЋР вЂљР В Р’В°Р В Р’В±Р В РЎвЂўР РЋРІР‚С™Р В Р’В°Р РЋР вЂ№Р РЋРІР‚С™ Р В Р вЂ¦Р В Р’ВµР В Р’В·Р В Р’В°Р В Р вЂ Р В РЎвЂ�Р РЋР С“Р В РЎвЂ�Р В РЎпїЅР В РЎвЂў */
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2;

	/* Р В Р вЂ Р РЋРІР‚в„–Р В РЎвЂќР В Р’В»Р РЋР вЂ№Р РЋРІР‚РЋР В Р’В°Р В Р’ВµР В РЎпїЅ scan conversion */
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	/* Р В РЎСљР В Р’Вµ Р В РўвЂ�Р В Р’ВµР В Р’В»Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р РЋРІР‚С™Р В Р’ВµР В Р’В»Р РЋР Р‰Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р РЋР вЂљР В Р’ВµР В РЎвЂўР В Р’В±Р РЋР вЂљР В Р’В°Р В Р’В·Р В РЎвЂўР В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ */
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

	/* Р В РЎСљР В Р’В°Р РЋРІР‚РЋР В РЎвЂ�Р В Р вЂ¦Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РЎвЂ”Р РЋР вЂљР В Р’ВµР В РЎвЂўР В Р’В±Р РЋР вЂљР В Р’В°Р В Р’В·Р В РЎвЂўР В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР В РЎвЂ“Р РЋР вЂљР В Р’В°Р В РЎпїЅР В РЎпїЅР В Р вЂ¦Р В РЎвЂў, Р В Р’В° Р В Р вЂ¦Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р РЋР С“Р РЋР вЂљР В Р’В°Р В Р’В±Р В Р’В°Р РЋРІР‚С™Р РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р РЋР вЂ№ Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂ�Р В РЎвЂ“Р В Р’ВµР РЋР вЂљР В Р’В° */
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
	/* 12 Р В Р’В±Р В РЎвЂ�Р РЋРІР‚С™Р В Р вЂ¦Р В РЎвЂўР В Р’Вµ Р В РЎвЂ”Р РЋР вЂљР В Р’ВµР В РЎвЂўР В Р’В±Р РЋР вЂљР В Р’В°Р В Р’В·Р В РЎвЂўР В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ. Р РЋР вЂљР В Р’ВµР В Р’В·Р РЋРЎвЂњР В Р’В»Р РЋР Р‰Р РЋРІР‚С™Р В Р’В°Р РЋРІР‚С™ Р В Р вЂ  12 Р В РЎпїЅР В Р’В»Р В Р’В°Р В РўвЂ�Р РЋРІвЂљВ¬Р В РЎвЂ�Р РЋРІР‚В¦ Р РЋР вЂљР В Р’В°Р В Р’В·Р РЋР вЂљР РЋР РЏР В РўвЂ�Р В Р’В°Р РЋРІР‚В¦ Р РЋР вЂљР В Р’ВµР В Р’В·Р РЋРЎвЂњР В Р’В»Р РЋР Р‰Р РЋРІР‚С™Р В Р’В°Р РЋРІР‚С™Р В Р’В° */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	/* Р В РЎвЂ�Р В Р вЂ¦Р В РЎвЂ�Р РЋРІР‚В Р В РЎвЂ�Р В Р’В°Р В Р’В»Р В РЎвЂ�Р В Р’В·Р В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р РЋР РЏ */
	ADC_CommonInit(&adc_init);

	ADC_Init(ADC1, &ADC_InitStructure);
	/* Р В РІР‚в„ўР В РЎвЂќР В Р’В»Р РЋР вЂ№Р РЋРІР‚РЋР В Р’В°Р В Р’ВµР В РЎпїЅ Р В РЎвЂ™Р В Р’В¦Р В РЎСџ1 */
	ADC_Cmd(ADC1, ENABLE);

}

Slider sliders;

uint16_t ticks_counter = 0x0000;

void read_sliders() {
	uint32_t i;
	ticks_counter++;
	if (ticks_counter > 1000) { // Only one per 1000
		ticks_counter = 0;
		i = ADC_GetSample(0x20);
		if (i != sliders.value) {
			__NOP();
			sliders.value = i;
			sendControlChange(64, i, 0);
			sendUSB_ControlChange(64, i, 0);
		}
	}

}

