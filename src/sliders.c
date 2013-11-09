#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "presets.h"
#include "sliders.h"
#include "midi.h"
#include "usb_midi_io.h"

uint16_t ADC_convert(uint8_t adc_num) {
	uint16_t ADC_Val;
	switch (adc_num) {
	case 0:
		ADC_SoftwareStartConv(ADC1);
		while (ADC_GetSoftwareStartConvStatus(ADC1) != RESET) {
			ADC_Val = 0;
		}
		ADC_Val = ADC_GetConversionValue(ADC1);
		break;
	case 1:
		ADC_SoftwareStartConv(ADC2);
		while (ADC_GetSoftwareStartConvStatus(ADC2) != RESET) {
			ADC_Val = 0;
		}
		ADC_Val = ADC_GetConversionValue(ADC2);
		break;
	case 3:
		ADC_SoftwareStartConv(ADC3);
		while (ADC_GetSoftwareStartConvStatus(ADC3) != RESET) {
			ADC_Val = 0;
		}
		ADC_Val = ADC_GetConversionValue(ADC3);
		break;
	default:
		ADC_Val = 0;
		break;
	}
	return ADC_Val;
}


void ADC_init_all(void) {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	/* ADC Common configuration *************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInit(&ADC_CommonInitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	/* ADC1 regular channel 10 to 15 configuration ************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init(ADC2, &ADC_InitStructure);
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Init(ADC3, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_144Cycles);

	/* Enable ADC1 to ADC3*/
	ADC_Cmd(ADC2, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC3, ENABLE);

}

static Slider_type sliders[24];
static enum Sliders_read_status_type {
	next_mux, wait_mux, check_active, next_adc, read_data, check_value
} Sliders_read_status = check_active;

void sliders_init(void) {
	uint8_t i;
	sliders[SLIDER_EMPTY].active = 0;

	for (i = 0; i < 24; i++) {
		sliders[i].active = 1;
		sliders[i].reverse = 0;
		sliders[i].channel = i;
		sliders[i].min_in_value = SLIDER_S_MIN_IN;
		sliders[i].max_in_value = SLIDER_S_MAX_IN;
		sliders[i].min_out_value = SLIDER_S_MIN_OUT;
		sliders[i].max_out_value = SLIDER_S_MAX_OUT;

	}

	/*	for (i = 8; i < 16; i++) {
	 sliders[i].active = 0;
	 sliders[i].reverse = 0;
	 sliders[i].channel = i;
	 sliders[i].min_in_value = SLIDER_R_MIN_IN;
	 sliders[i].max_in_value = SLIDER_R_MAX_IN;
	 sliders[i].min_out_value = SLIDER_R_MIN_OUT;
	 sliders[i].max_out_value = SLIDER_R_MAX_OUT;

	 }
	 for (i = 17; i < 24; i++) {
	 sliders[i].active = 1;
	 sliders[i].reverse = 0;
	 sliders[i].channel = i;
	 sliders[i].min_in_value = SLIDER_R_MIN_IN;
	 sliders[i].max_in_value = SLIDER_R_MAX_IN;
	 sliders[i].min_out_value = SLIDER_R_MIN_OUT;
	 sliders[i].max_out_value = SLIDER_R_MAX_OUT;
	 }*/
	/*
	 sliders[SLIDER_S1].active = 0;
	 sliders[SLIDER_S1].reverse = 0;
	 sliders[SLIDER_S1].channel = 0;
	 sliders[SLIDER_S1].event = 7;
	 sliders[SLIDER_S1].min_in_value = SLIDER_S_MIN_IN;
	 sliders[SLIDER_S1].max_in_value = SLIDER_S_MAX_IN;
	 sliders[SLIDER_S1].min_out_value = SLIDER_S_MIN_OUT;
	 sliders[SLIDER_S1].max_out_value = SLIDER_S_MAX_OUT;

	 sliders[SLIDER_S2].active = 0;
	 sliders[SLIDER_S1].event = 7;

	 sliders[SLIDER_P2].active = 0;
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

	 sliders[SLIDER_P3].active = 0;
	 sliders[SLIDER_P3].reverse = 0;
	 sliders[SLIDER_P3].channel = 0;
	 sliders[SLIDER_P3].event = 66;
	 sliders[SLIDER_P3].min_in_value = SLIDER_P_MIN_IN;
	 sliders[SLIDER_P3].max_in_value = SLIDER_P_MAX_IN;
	 sliders[SLIDER_P3].min_out_value = SLIDER_P_MIN_OUT;
	 sliders[SLIDER_P3].max_out_value = SLIDER_P_MAX_OUT;

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
	 */
}

static uint16_t tick_counter = 0; //Counter of timer ticks
static uint8_t adc_counter = 0; //adc (multiplexor chip) number 0..2
static uint8_t mux_pin = 0; //Multiplexor pin number 0..7
static uint8_t slider_number; // Slider number from 0 to 23
static uint32_t ADC_sum = 0; //SUM of ADC measuring
uint16_t ADC_old_values[24] = { 0 };

void read_sliders() {
	uint16_t ADC_value;
	uint16_t ADC_change;
	uint8_t midi_value;
	switch (Sliders_read_status) {

	case check_active:
		if (sliders[slider_number].active) {
			Sliders_read_status = read_data;
			break;
		} else {
			Sliders_read_status = next_adc;
			break;
		}
	case read_data:

		ADC_sum += ADC_convert(adc_counter);
		tick_counter++;
		if (tick_counter >= SLIDERS_MEASURE_NUM) {
			tick_counter = 0;
			Sliders_read_status = check_value;
		}
		break;
	case check_value:
		ADC_value = ADC_sum / SLIDERS_MEASURE_NUM;
		ADC_sum = 0;
		if (ADC_value > ADC_old_values[slider_number]) {
			ADC_change = ADC_value - ADC_old_values[slider_number];
		} else {
			ADC_change = ADC_old_values[slider_number] - ADC_value;
		}
		if (ADC_change > SLIDERS_DELTA) {
			ADC_old_values[slider_number] = ADC_value;
			midi_value = ADC_value >> 5;
		} else {
			midi_value = ADC_old_values[slider_number] >> 5;
		}
		if (midi_value != sliders[slider_number].value) {
			sliders[slider_number].value = midi_value;
			sendControlChange(sliders[slider_number].event, midi_value,
					sliders[slider_number].channel);
			sendUSB_ControlChange(slider_number, midi_value, mux_pin);
		}
		tick_counter = 0;
		Sliders_read_status = next_adc;
		break;
	case next_adc:
		adc_counter++;
		if (adc_counter < 3) {
			slider_number++;
			Sliders_read_status = check_active;
			break;
		} else {
			adc_counter = 0;
			Sliders_read_status = next_mux;
			break;
		}
		break;
	case next_mux:
		mux_pin++;
		if (mux_pin > 7) {
			mux_pin = 0;
		}
		GPIOE->ODR = ~mux_pin; //next value to multipexors
		slider_number = mux_pin * 3;
		Sliders_read_status = wait_mux;
		break;
	case wait_mux:
		tick_counter++;
		if (tick_counter >= SLIDERS_MUX_DELAY) {
			tick_counter = 0;
			Sliders_read_status = check_active;
		}
		break;
	}
}

