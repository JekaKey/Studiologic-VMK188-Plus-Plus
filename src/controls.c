//#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include <string.h>
#include "presets.h"
#include "controls.h"
#include "midi.h"
#include "usb_midi_io.h"
#include "fifo.h"
#include "hd44780.h"
#include "leds.h"

/*Array of slider names by slider number with fixed values, should be in flash memory*/
const char slider_names[][MAX_ATTR_SIZE] = { ATTR_R2, ATTR_S8, ATTR_P2, ATTR_R3, ATTR_S2,
		ATTR_P1, ATTR_R4, ATTR_S6, ATTR_EY, ATTR_R1, ATTR_S3, ATTR_P3, ATTR_R8,
		ATTR_S7, ATTR_S1, ATTR_R5, ATTR_S5, ATTR_AT, ATTR_R7, ATTR_S9, ATTR_MO,
		ATTR_R6, ATTR_S4, ATTR_PI };
const char button_names[][MAX_ATTR_SIZE] = { ATTR_BLF, ATTR_BRT, ATTR_BRC, ATTR_BPL,
		ATTR_BST, ATTR_B1, ATTR_B2, ATTR_B3, ATTR_B4, ATTR_B5, ATTR_B6, ATTR_B7,
		ATTR_B8 };


FIFO8(128) control_events;
FIFO16(128) sliders_events;

void ADC_init_all(void) {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	/* ADC Common configuration *************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);

	ADC_DeInit();

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Init(ADC2, &ADC_InitStructure);
	ADC_Init(ADC3, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_144Cycles);

	/* Enable ADC1 to ADC3*/
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	ADC_Cmd(ADC3, ENABLE);

}


static enum controls_read_status_type {
	next_mux, wait_mux, read_data, check_value, read_buttons, check_button, next_buttons_chunk, read_encoders
} controls_read_status = read_data;

void slider_init_struct(Slider_type* sliders, Calibration_slider_type* sliders_calibr) {
	if (sliders->reverse) {
		sliders->a = (double) (sliders->max_out_value - sliders->min_out_value) / (double) ((int) (sliders_calibr->min_in_value) - (int) (sliders_calibr->max_in_value));
		sliders->b = (double) (sliders->min_out_value) - (double) (sliders_calibr->max_in_value) * sliders->a;
	} else {
		sliders->a = (double) (sliders->max_out_value - sliders->min_out_value) / (double) (sliders_calibr->max_in_value - sliders_calibr->min_in_value);
		sliders->b = (double) (sliders->min_out_value) - (double) (sliders_calibr->min_in_value) * sliders->a;
	}
}

/*
 Set default values in an array of calibration structures.
 */

void sliders_calibr_set_defaults(Calibration_slider_type* sliders_calibr) {
	sliders_calibr[SLIDER_EMPTY].min_in_value = SLIDER_S_MIN_IN; //One slider is absent physically
	sliders_calibr[SLIDER_EMPTY].max_in_value = SLIDER_S_MAX_IN; //and initialized by any correct data
	sliders_calibr[SLIDER_EMPTY].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S1].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S1].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S1].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S2].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S2].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S2].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S3].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S3].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S3].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S4].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S4].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S4].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S5].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S5].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S5].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S6].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S6].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S6].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S7].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S7].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S7].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S8].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S8].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S8].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_S9].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S9].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S9].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R1].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R1].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R1].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R2].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R2].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R2].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R3].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R3].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R3].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R4].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R4].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R4].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R5].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R5].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R5].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R6].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R6].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R6].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R7].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R7].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R7].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_R8].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R8].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R8].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_P1].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P1].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P1].delta = SLIDERS_DELTA_P;

	sliders_calibr[SLIDER_P2].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P2].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P2].delta = SLIDERS_DELTA_P;

	sliders_calibr[SLIDER_P3].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P3].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P3].delta = SLIDERS_DELTA_P;

	sliders_calibr[SLIDER_PITCH].min_in_value = SLIDER_PITCH_MIN_IN;
	sliders_calibr[SLIDER_PITCH].max_in_value = SLIDER_PITCH_MAX_IN;
	sliders_calibr[SLIDER_PITCH].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_MOD].min_in_value = SLIDER_MOD_MIN_IN;
	sliders_calibr[SLIDER_MOD].max_in_value = SLIDER_MOD_MAX_IN;
	sliders_calibr[SLIDER_MOD].delta = SLIDERS_DELTA_S;

	sliders_calibr[SLIDER_AT].min_in_value = SLIDER_AT_MIN_IN;
	sliders_calibr[SLIDER_AT].max_in_value = SLIDER_AT_MAX_IN;
	sliders_calibr[SLIDER_AT].delta = SLIDERS_DELTA_AT;
}

/*
 Set default values in an array of sliders with address "sliders" using an array of calibrations
 the size of addressed array must be equal SLIDERS_AMOUNT
 */
void sliders_set_defaults(Slider_type* sliders, Calibration_slider_type* sliders_calibr) {

	sliders[SLIDER_EMPTY].active = 0;    //One slider is absent physically
	sliders[SLIDER_EMPTY].reverse = 0;
	sliders[SLIDER_EMPTY].channel = 0;
	sliders[SLIDER_EMPTY].event = 7;
	sliders[SLIDER_EMPTY].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_EMPTY].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S1].active = 1;
	sliders[SLIDER_S1].reverse = 0;
	sliders[SLIDER_S1].channel = 0;
	sliders[SLIDER_S1].event = 7;
	sliders[SLIDER_S1].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S1].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S2].active = 0;
	sliders[SLIDER_S2].reverse = 0;
	sliders[SLIDER_S2].channel = 0;
	sliders[SLIDER_S2].event = 22;
	sliders[SLIDER_S2].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S2].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S3].active = 0;
	sliders[SLIDER_S3].reverse = 0;
	sliders[SLIDER_S3].channel = 0;
	sliders[SLIDER_S3].event = 23;
	sliders[SLIDER_S3].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S3].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S4].active = 0;
	sliders[SLIDER_S4].reverse = 0;
	sliders[SLIDER_S4].channel = 0;
	sliders[SLIDER_S4].event = 24;
	sliders[SLIDER_S4].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S4].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S5].active = 0;
	sliders[SLIDER_S5].reverse = 0;
	sliders[SLIDER_S5].channel = 0;
	sliders[SLIDER_S5].event = 25;
	sliders[SLIDER_S5].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S5].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S6].active = 0;
	sliders[SLIDER_S6].reverse = 0;
	sliders[SLIDER_S6].channel = 0;
	sliders[SLIDER_S6].event = 26;
	sliders[SLIDER_S6].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S6].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S7].active = 0;
	sliders[SLIDER_S7].reverse = 0;
	sliders[SLIDER_S7].channel = 0;
	sliders[SLIDER_S7].event = 27;
	sliders[SLIDER_S7].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S7].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S8].active = 0;
	sliders[SLIDER_S8].reverse = 0;
	sliders[SLIDER_S8].channel = 0;
	sliders[SLIDER_S8].event = 28;
	sliders[SLIDER_S8].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S8].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_S9].active = 0;
	sliders[SLIDER_S9].reverse = 0;
	sliders[SLIDER_S9].channel = 0;
	sliders[SLIDER_S9].event = 29;
	sliders[SLIDER_S9].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S9].max_out_value = SLIDER_S_MAX_OUT;

	sliders[SLIDER_R1].active = 0;
	sliders[SLIDER_R1].reverse = 0;
	sliders[SLIDER_R1].channel = 0;
	sliders[SLIDER_R1].event = 71;
	sliders[SLIDER_R1].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R1].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R2].active = 0;
	sliders[SLIDER_R2].reverse = 0;
	sliders[SLIDER_R2].channel = 0;
	sliders[SLIDER_R2].event = 72;
	sliders[SLIDER_R2].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R2].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R3].active = 0;
	sliders[SLIDER_R3].reverse = 0;
	sliders[SLIDER_R3].channel = 0;
	sliders[SLIDER_R3].event = 73;
	sliders[SLIDER_R3].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R3].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R4].active = 0;
	sliders[SLIDER_R4].reverse = 0;
	sliders[SLIDER_R4].channel = 0;
	sliders[SLIDER_R4].event = 74;
	sliders[SLIDER_R4].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R4].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R5].active = 0;
	sliders[SLIDER_R5].reverse = 0;
	sliders[SLIDER_R5].channel = 0;
	sliders[SLIDER_R5].event = 75;
	sliders[SLIDER_R5].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R5].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R6].active = 0;
	sliders[SLIDER_R6].reverse = 0;
	sliders[SLIDER_R6].channel = 0;
	sliders[SLIDER_R6].event = 76;
	sliders[SLIDER_R6].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R6].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R7].active = 0;
	sliders[SLIDER_R7].reverse = 0;
	sliders[SLIDER_R7].channel = 0;
	sliders[SLIDER_R7].event = 77;
	sliders[SLIDER_R7].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R7].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_R8].active = 0;
	sliders[SLIDER_R8].reverse = 0;
	sliders[SLIDER_R8].channel = 0;
	sliders[SLIDER_R8].event = 78;
	sliders[SLIDER_R8].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R8].max_out_value = SLIDER_R_MAX_OUT;

	sliders[SLIDER_P1].active = 0;
	sliders[SLIDER_P1].reverse = 0;
	sliders[SLIDER_P1].channel = 0;
	sliders[SLIDER_P1].event = 65;
	sliders[SLIDER_P1].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P1].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P2].active = 1;
	sliders[SLIDER_P2].reverse = 1;
	sliders[SLIDER_P2].channel = 0;
	sliders[SLIDER_P2].event = 64;
	sliders[SLIDER_P2].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P2].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P3].active = 0;
	sliders[SLIDER_P3].reverse = 0;
	sliders[SLIDER_P3].channel = 0;
	sliders[SLIDER_P3].event = 66;
	sliders[SLIDER_P3].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P3].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_PITCH].active = 0;
	sliders[SLIDER_PITCH].reverse = 0;
	sliders[SLIDER_PITCH].channel = 0;
	sliders[SLIDER_PITCH].event = 66;
	sliders[SLIDER_PITCH].min_out_value = SLIDER_PITCH_MIN_OUT;
	sliders[SLIDER_PITCH].max_out_value = SLIDER_PITCH_MAX_OUT;

	sliders[SLIDER_MOD].active = 0;
	sliders[SLIDER_MOD].reverse = 0;
	sliders[SLIDER_MOD].channel = 0;
	sliders[SLIDER_MOD].event = 1;
	sliders[SLIDER_MOD].min_out_value = SLIDER_MOD_MIN_OUT;
	sliders[SLIDER_MOD].max_out_value = SLIDER_MOD_MAX_OUT;

	sliders[SLIDER_AT].active = 1;
	sliders[SLIDER_AT].reverse = 0;
	sliders[SLIDER_AT].channel = 0;
	sliders[SLIDER_AT].event = 66;
	sliders[SLIDER_AT].min_out_value = SLIDER_AT_MIN_OUT;
	sliders[SLIDER_AT].max_out_value = SLIDER_AT_MAX_OUT;
	for (int i = 0; i < SLIDERS_AMOUNT; i++) //Calculate factors for all sliders
		slider_init_struct(&sliders[i],&sliders_calibr[i]);

}

void buttons_set_defaults(Button_type* but) {
	for (int i = 0; i < BUTTONS_AMOUNT; i++) {
		but[i].type = 0;
		but[i].toggle = 0;
		but[i].active = 0;
		but[i].off = 0;
		but[i].on = 127;
		but[i].channel = 0;
	}
	but[0].event = 47;
	but[1].event = 48;
	but[2].event = 44;
	but[3].event = 45;
	but[4].event = 46;
	for (int i=5; i<BUTTONS_AMOUNT; i++){
		but[i].event=11+i;
		but[i].active=1;
	}
}

//typedef struct {
//	uint8_t active;
//	uint8_t channel;
//	uint8_t type; //0-CC, 1 -NOTE, 2 MMS
//	uint8_t toggle; //0-momentary, !=0 toggle (work only for ÑÑ)
//	uint8_t event;
//	uint8_t on;
//	uint8_t off;
//} Button_type;

button_port_type button_ports[3] = { { BUTTON0_PORT, BUTTON0_PIN }, { BUTTON1_PORT, BUTTON1_PIN }, { BUTTON2_PORT, BUTTON2_PIN } };

static uint16_t tick_counter = 0; //Counter of timer ticks
static uint16_t mux_pin = 0; //Multiplexor pin number 0..7
static uint8_t slider_number = 0; // Slider number from 0 to 23
static uint32_t ADC1_sum = 0; //SUM of ADC1 measuring
static uint32_t ADC2_sum = 0; //SUM of ADC2 measuring
static uint32_t ADC3_sum = 0; //SUM of ADC3 measuring
static uint16_t ADC1_min = 0xFFFF; //Minimum ADC result in measuring set
static uint16_t ADC1_max = 0; //Maxmum ADC result in measuring set
static uint16_t ADC2_min = 0xFFFF;
static uint16_t ADC2_max = 0;
static uint16_t ADC3_min = 0xFFFF;
static uint16_t ADC3_max = 0;
static uint16_t ADC_old_values[24] = { 0 };
static uint8_t sliders_old_values[24] = { 0 };
static uint8_t buttons_chunk = 0;
static uint8_t buttons_state[24] = { 0 };
static uint8_t buttons; //result of IDR reading
static uint8_t button_counter = 0; //Number of a button in chunk
static uint8_t encoder_state = 3;
static uint8_t encoder_zero = 0;

uint8_t buttons_active = 0; //This flag prevents activity of buttons and  hd44780 in the same time

extern uint8_t hd44780_active; //This flag prevents activity of buttons and  hd44780 in the same time


static void slider_FIFO_send(uint8_t num, uint16_t value, Slider_type* sliders) {
	int midi_value = (uint8_t)(sliders[num].a * value + sliders[num].b);
	if (midi_value > 127) {
		midi_value = 127;
	}
	if (midi_value < 0) {
		midi_value = 0;
	}
	if (midi_value != sliders_old_values[num]) {
		FIFO_PUSH(sliders_events, (((uint16_t)(midi_value))<<8)+num);
		sliders_old_values[num] = midi_value;
	}
}

void slider_midi_send(uint16_t value, Slider_type* sliders) {
	uint8_t num = (uint8_t)(value & 0x00FF);
	uint8_t midi_value = (uint8_t)(value >> 8);
	switch (num) {
		case SLIDER_PITCH:
			sendPitchBend((uint8_t)(midi_value), sliders[num].channel);
			break;
		case SLIDER_AT:
			sendAfterTouch((uint8_t)(midi_value), sliders[num].channel);
			break;
		case SLIDER_MOD:
			sendControlChange(sliders[num].event, (uint8_t)(midi_value), sliders[num].channel);
			break;
		default:
			sendControlChange(sliders[num].event, (uint8_t)(midi_value), sliders[num].channel);
			break;
	}
}

void buttons_delay(void) {
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

/****Simple median filter*****/
uint16_t median(uint16_t* a) {
	if (a[0] < a[1]) {
		if (a[1] < a[2]) {
			return a[1];
		} else {
			if (a[0] < a[2]) {
				return a[0];
			} else {
				return a[2];
			}
		}
	} else {
		if (a[1] > a[2]) {
			return a[1];
		} else {
			if (a[0] > a[2]) {
				return a[2];
			} else {
				return a[0];
			}
		}

	}

}

void read_controls(Slider_type* sliders, Calibration_slider_type* cal) {
	uint16_t ADC_value;
	uint16_t ADC_change;
	uint16_t ODR_tmp, IDR_tmp, tmp;
	static uint8_t button_number; //Number of current button;
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select
	uint16_t adc1_arr[3], adc2_arr[3], adc3_arr[3];
	uint16_t adc_med;
	switch (controls_read_status) {

		case read_data:
			for (uint8_t i = 0; i < 3; i++) { //read all ADC1, ADC2, ADC3 3 times each and add to sum. Paralle search min & max values foe each ADC to remove them from sum in future
				ADC_SoftwareStartConv(ADC1);
				while (ADC_GetSoftwareStartConvStatus(ADC1) != RESET) {
				}
				adc1_arr[i] = ADC_GetConversionValue(ADC1);

				ADC_SoftwareStartConv(ADC2);
				while (ADC_GetSoftwareStartConvStatus(ADC2) != RESET) {
				}
				adc2_arr[i] = ADC_GetConversionValue(ADC2);

				ADC_SoftwareStartConv(ADC3);
				while (ADC_GetSoftwareStartConvStatus(ADC3) != RESET) {
				}
				adc3_arr[i] = ADC_GetConversionValue(ADC3);
			}
			adc_med = median(adc1_arr);//apply median filter to all  ADC values
			ADC1_sum += adc_med;
			if (adc_med > ADC1_max) {
				ADC1_max = adc_med;
			}
			if (adc_med < ADC1_min) {
				ADC1_min = adc_med;
			}
			adc_med = median(adc2_arr);
			ADC2_sum += adc_med;
			if (adc_med > ADC2_max) {
				ADC2_max = adc_med;
			}
			if (adc_med < ADC2_min) {
				ADC2_min = adc_med;
			}
			adc_med = median(adc3_arr);
			ADC3_sum += adc_med;
			if (adc_med > ADC3_max) {
				ADC3_max = adc_med;
			}
			if (adc_med < ADC3_min) {
				ADC3_min = adc_med;
			}
			tick_counter++;
			if (tick_counter >= SLIDERS_MEASURE_NUM) {
				tick_counter = 0;
				controls_read_status = check_value;
			}

			break;
		case check_value://Calculate ADC results after many measurements.
			if (sliders[slider_number].active) {
				ADC_value = (ADC1_sum - ADC1_min - ADC1_max) / (SLIDERS_MEASURE_NUM - 2);//Remove min & max values and calculate average per SLIDERS_MEASURE_NUM-2 measurements
				ADC1_sum = 0;
				ADC1_min = 0xFFFF;
				ADC1_max = 0;
				if (ADC_value > ADC_old_values[slider_number]) {//Compare changes with SLIDERS_DELTA.
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > cal[slider_number].delta) {//Change a result only if difference exceeds SLIDERS_DELTA.
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value, sliders);
				}
			} else {
				ADC1_sum = 0;
				ADC1_min = 0xFFFF;
				ADC1_max = 0;
			}
			slider_number++;

            /*same for ADC2*/
			if (sliders[slider_number].active) {
				ADC_value = (ADC2_sum - ADC2_min - ADC2_max) / (SLIDERS_MEASURE_NUM - 2);
				ADC2_sum = 0;
				ADC2_min = 0xFFFF;
				ADC2_max = 0;
				if (ADC_value > ADC_old_values[slider_number]) {
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > cal[slider_number].delta) {
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value, sliders);
				}
			} else {
				ADC2_sum = 0;
				ADC2_min = 0xFFFF;
				ADC2_max = 0;
			}
			slider_number++;

	        /*same for ADC3*/
			if (sliders[slider_number].active) {
				ADC_value = (ADC3_sum - ADC3_min - ADC3_max) / (SLIDERS_MEASURE_NUM - 2);
				ADC3_sum = 0;
				ADC3_min = 0xFFFF;
				ADC3_max = 0;
				if (ADC_value > ADC_old_values[slider_number]) {
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > cal[slider_number].delta) {
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value, sliders);
				}
			} else {
				ADC3_sum = 0;
				ADC3_min = 0xFFFF;
				ADC3_max = 0;
			}
			controls_read_status = next_mux;
			break;
		case next_mux: //Switch multiplexors to next state
			mux_pin++;
			if (mux_pin > 7) {
				mux_pin = 0;
			}
			ODR_tmp = GPIOB->ODR & 0xFF8F; //PB4, PB5, PB6
			tmp = ODR_tmp | (mux_pin << 4); //next value to multiplexors PB4, PB5, PB6
			GPIOB->ODR = tmp;
			slider_number = mux_pin * 3;
			controls_read_status = wait_mux;
			break;
		case wait_mux: //Waiting several ticks after multiplexors switch
			tick_counter++;
			if (tick_counter >= SLIDERS_MUX_DELAY) {
				tick_counter = 0;
				controls_read_status = read_buttons;
			}
			break;
		case read_buttons:
			if (!hd44780_active) {//If display is writing we do not read buttons to avoid pins conflict.
				buttons_active = 1;//Set to prevent display usage in this moment. The display should wait buttons_active = 0;
				GPIOE->ODR |= 0x00FF; //High level on PE0-7;
				GPIOE->MODER &= 0xFFFF0000; //PE0-7 Will be Input
				button_ports[buttons_chunk].port->BSRRH = button_ports[buttons_chunk].pin;
				buttons_delay();
				buttons = ~GPIOE->IDR; //Read buttons state
				button_ports[buttons_chunk].port->BSRRL = button_ports[buttons_chunk].pin;
				GPIOE->MODER |= 0x00005555; //PE0-7 Will be Output
				GPIOE->ODR |= 0x00FF; //High level on PD0-7;
				controlLEDs_switch();
				controls_read_status = check_button;
				buttons_active = 0;
				break;
			} else {
				controls_read_status = read_encoders;
				break;
			}
		case check_button:
			button_number = buttons_chunk * 8 + button_counter;

			if (buttons & k[button_counter]) {
				if (buttons_state[button_number] == 0) {
					buttons_state[button_number] = 1;
					FIFO_PUSH(control_events, button_number);
					//send pressed
				}
			} else {
				if (buttons_state[button_number] != 0) {
					buttons_state[button_number] = 0;
					FIFO_PUSH(control_events, 0x80|button_number);
					//send depressed
				}
			}
			button_counter++;
			if (button_counter > 7) {
				button_counter = 0;
				controls_read_status = next_buttons_chunk;
			}
			break;
		case next_buttons_chunk:
			buttons_chunk++;
			if (buttons_chunk > 2) {
				buttons_chunk = 0;
				controls_read_status = read_encoders;
			} else {
				controls_read_status = read_buttons;
			}
			break;
		case read_encoders:
			/*Read both encoder signals from the same port because  ENCODER1_PORT=ENCODER2_PORT =GPIOD*/
			IDR_tmp = (uint8_t)((ENCODER1_PORT->IDR & ENCODER1_PIN) | (ENCODER2_PORT->IDR & ENCODER2_PIN));
			if (IDR_tmp == encoder_state) { //State is not changed
				controls_read_status = read_data;
				break;
			} else {
				if (IDR_tmp == 0) {
					encoder_zero = 1;
					encoder_state = 0;
					controls_read_status = read_data;
					break;
				} else if (IDR_tmp == 3) { // This means the encoder is in unstable average position because it is turned.
					if (encoder_zero) {
						if (encoder_state == 1) {//Direction depends previous state
							encoder_state = 3;
							FIFO_PUSH(control_events, ENCODER_LEFT);
							controls_read_status = read_data;
							encoder_zero = 0;
							break;
						} else if (encoder_state == 2) {
							encoder_state = 3;
							FIFO_PUSH(control_events, ENCODER_RIGHT);
							controls_read_status = read_data;
							encoder_zero = 0;
							break;
						}
					} else {
						encoder_state = IDR_tmp;
						controls_read_status = read_data;
						break;
					}
				} else {
					encoder_state = IDR_tmp;
					controls_read_status = read_data;
					break;
				}
			}
	}
}

/*Check Sliders FIFO buffer*/
void checkSliders_events(Slider_type* sliders) {
	uint16_t event;
	if (FIFO_COUNT(sliders_events) != 0) {
		event = FIFO_FRONT(sliders_events);
		FIFO_POP(sliders_events);
		slider_midi_send(event, sliders);
	}

}

