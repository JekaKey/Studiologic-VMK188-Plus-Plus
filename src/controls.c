//#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include <string.h>
#include "presets.h"
#include "controls.h"
#include "midi.h"
#include "menu.h"
#include "usb_midi_io.h"
#include "fifo.h"
#include "hd44780.h"
#include "leds.h"
#include "log.h"
#include "filter.h"

/*Array of slider names by slider number with fixed values, should be in flash memory*/
const char slider_names[][MAX_ATTR_SIZE] = { ATTR_R2, ATTR_S8, ATTR_P2, ATTR_R3, ATTR_S2,
		ATTR_P1, ATTR_R4, ATTR_S6, ATTR_EY, ATTR_R1, ATTR_S3, ATTR_P3, ATTR_R8,
		ATTR_S7, ATTR_S1, ATTR_R5, ATTR_S5, ATTR_AT, ATTR_R7, ATTR_S9, ATTR_MO,
		ATTR_R6, ATTR_S4, ATTR_PI };
const char button_names[][MAX_ATTR_SIZE] = { ATTR_B1, ATTR_B2, ATTR_B3, ATTR_B4, ATTR_B5, ATTR_B6, ATTR_B7,
		ATTR_B8 };

const uint8_t button_positions[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select


FIFO8(128) control_events;
FIFO16(128) sliders_events;
FIFO16(128) pitch_events;
sliders_state_t sliders_state;
uint8_t buttons_control_state = 0;


extern presetType Preset;

void send_message(uint8_t mes){
	FIFO_PUSH(control_events, mes);
}


void ADC_init_all(void) {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	/* ADC Common configuration *************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div6;
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

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);

	/* Enable ADC1 to ADC3*/
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	ADC_Cmd(ADC3, ENABLE);
	median_filter_init();
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
	sliders[SLIDER_S1].event = 11;
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

	sliders[SLIDER_PITCH].active = 1;
	sliders[SLIDER_PITCH].reverse = 0;
	sliders[SLIDER_PITCH].channel = 0;
	sliders[SLIDER_PITCH].event = 66;
	sliders[SLIDER_PITCH].min_out_value = SLIDER_PITCH_MIN_OUT;
	sliders[SLIDER_PITCH].max_out_value = SLIDER_PITCH_MAX_OUT;

	sliders[SLIDER_MOD].active = 1;
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

}

static struct{
	uint8_t value;
	uint8_t pressed;
} buttons_state[24] = {{0}};

void buttons_set_defaults(Button_type* but) {
	for (int i = 0; i < BUTTONS_AMOUNT; i++) {
		but[i].type = BTN_TYPE_SIMPLE;
		but[i].active = 0;
		but[i].off = 0;
		but[i].on = 127;
		but[i].channel = 0;

		but[i].event = 85 + i;
	}
}

const button_port_type button_ports[3] = { { BUTTON0_PORT, BUTTON0_PIN }, { BUTTON1_PORT, BUTTON1_PIN }, { BUTTON2_PORT, BUTTON2_PIN } };

static uint16_t tick_counter = 0; //Counter of timer ticks
static uint16_t mux_pin = 0; //Multiplexor pin number 0..7
static uint16_t ADC_res[8][3] = {{0}}; //Result of ADC1,2,3 measuring after first 3x median filter.
static uint16_t ADC_old_values[SLIDERS_AMOUNT] = { 0 };
static uint8_t sliders_old_values[SLIDERS_AMOUNT] = { 0 };
static uint16_t pitch_old_value = 8192;
static uint8_t buttons_chunk = 0;
static uint8_t buttons; //result of IDR reading
static uint8_t button_counter = 0; //Number of a button in chunk
static uint8_t encoder_state = 3;
static uint8_t encoder_zero = 0;

/*Variables to calculate advanced delta*
static uint16_t delta_sum[SLIDERS_AMOUNT]={0};
static uint16_t delta_average[SLIDERS_AMOUNT]={0};
static uint8_t delta_counter =0;
********/


uint8_t slider_calibrate_number = 0; // Slider chosen for calibrate procedure;
uint16_t slider_calibrate_store;
uint8_t buttons_active = 0; //This flag prevents activity of buttons and  hd44780 in the same time

extern uint8_t hd44780_active; //This flag prevents activity of buttons and  hd44780 in the same time


static void slider_FIFO_send(uint8_t num, uint16_t value, Slider_type* sliders, Calibration_slider_type* sliders_calibr) {
	double a,b;
	int midi_value;

	//pitch band has a dead zone and 14-bit precision
	if (num == SLIDER_PITCH) {
		//pitch potentiometer is inverted
		value = sliders_calibr->max_in_value - value + sliders_calibr->min_in_value;

		//TODO: setting the dead zone in the preset
		double dead = 0.25 * (double)(sliders_calibr->max_in_value - sliders_calibr->min_in_value);
		a = (double) (sliders->max_out_value - sliders->min_out_value) / (double) (sliders_calibr->max_in_value - sliders_calibr->min_in_value - dead);

		double middle_in = (double)(sliders_calibr->max_in_value + sliders_calibr->min_in_value) / 2;
		double middle_out = (double)(sliders->max_out_value + sliders->min_out_value) / 2;

		//alpha is the point when the dead zone begins
		double alpha = middle_in - dead/2;

		//the in-out function is piecewise linear
		if (value < alpha) {
			midi_value = (int)(a * value - sliders_calibr->min_in_value * a + sliders->min_out_value);
		} else if (value < alpha + dead) {
			midi_value = (middle_out - (int) middle_out) > 0   ?  (int) (middle_out + 1)   :  (int) middle_out;
		} else {
			midi_value = (int)(a * value - (alpha + dead) * a + middle_out);
		}
	} else {
		a = (double) (sliders->max_out_value - sliders->min_out_value) / (double) (sliders_calibr->max_in_value - sliders_calibr->min_in_value);
		if (sliders->reverse) {
			a = -a;
			b = (double) (sliders->max_out_value) - (double) (sliders_calibr->min_in_value) * a;
		} else {
			b = (double) (sliders->min_out_value) - (double) (sliders_calibr->min_in_value) * a;
		}
		midi_value = (int)(a * value + b);
	}

	//the 3rd pedal in a binary mode
	//TODO: setting the binary mode in the preset
	if (num == SLIDER_P3) {
		double middle = (double)(sliders->max_out_value + sliders->min_out_value) / 2;
		middle = (middle - (int) middle) > 0   ?  (int) (middle + 1)   :  (int) middle;
		if (midi_value < middle) {
			midi_value = sliders->min_out_value;
		} else {
			midi_value = sliders->max_out_value;
		}
	} else {
		if (midi_value > sliders->max_out_value) {
			midi_value = sliders->max_out_value;
		}

		if (midi_value < sliders->min_out_value) {
			midi_value = sliders->min_out_value;
		}
	}

	if (num == SLIDER_PITCH) {
		uint16_t midi_value16 = (uint16_t)(midi_value);
		if (midi_value16 != pitch_old_value) {
			FIFO_PUSH(pitch_events, midi_value16);
			pitch_old_value = midi_value16;
		}
	} else {
		uint8_t midi_value8=(uint8_t)(midi_value);
		if (midi_value8 != sliders_old_values[num]) {
			FIFO_PUSH(sliders_events, (((uint16_t)(midi_value8))<<8)+num);
			sliders_old_values[num] = midi_value8;
		}
	}
}

void slider_midi_send(uint16_t value, Slider_type* sliders) {
		uint8_t num = (uint8_t)(value & 0x00FF);
		uint8_t midi_value = (uint8_t)(value >> 8);

		uint8_t channel = sliders[num].channel ? sliders[num].channel : Preset.MidiChannel;
		if (channel)
			channel--; //Real channels are 0-15
		if (channel > 15)
			 channel = 0;

		switch (num) {
		case SLIDER_PITCH:
			break;
		case SLIDER_AT:
			sendAfterTouch((uint8_t)(midi_value), channel);
			break;
		case SLIDER_MOD:
			sendControlChange(sliders[num].event, (uint8_t)(midi_value), channel);
			break;
		default:
			sendControlChange(sliders[num].event, (uint8_t)(midi_value), channel);
			break;
		}
}

void pitch_midi_send(uint16_t value, uint8_t channel) {
	channel = channel ? channel : Preset.MidiChannel;
	if (channel)
		channel--; //Real channels are 0-15
	if (channel > 15)
		 channel = 0;

	sendPitchBend(value, channel);
}

void button_midi_send(uint16_t value, Button_type* buttons) {
	uint8_t is_pressed = (value & 0x80) ? 0 : 1;

	uint8_t num = is_pressed ? value : (value & 0x7F);
	num -= BUTTON_B1;

	if (!buttons[num].active)
		return;

	uint8_t channel = buttons[num].channel ? buttons[num].channel : Preset.MidiChannel;
	if (channel)
		channel--; //Real channels are 0-15
	if (channel > 15)
		channel = 0;

	//buttons_state storage states of button in binary mode: 01001001
	//button num is order number, button state is 0 or 1
	if (is_pressed) {
		if (buttons[num].type == BTN_TYPE_SWITCH) {
			if (buttons_control_state & button_positions[num]) {
				sendControlChange(buttons[num].event, buttons[num].off, channel);
				buttons_control_state -= button_positions[num];
			} else {
				sendControlChange(buttons[num].event, buttons[num].on, channel);
				buttons_control_state += button_positions[num];
			}
		} else {
			sendControlChange(buttons[num].event, buttons[num].on, channel);
		}
	} else if (buttons[num].type == BTN_TYPE_PUSH) {
		sendControlChange(buttons[num].event, buttons[num].off, channel);
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


static uint16_t read_ADC(uint32_t adc){
	ADC_SoftwareStartConv((ADC_TypeDef*) (adc));
	while (ADC_GetSoftwareStartConvStatus((ADC_TypeDef*) (adc))
			!= RESET) {
	}
   return ADC_GetConversionValue((ADC_TypeDef*) (adc));
}


static enum controls_read_status_type {
	next_mux, wait_mux, read_data, check_value
} controls_read_status = read_data;

extern filter_storage_t filter_storage[NUMBER_OF_BUFFERS];


static uint8_t check_delta(uint16_t * ADC_value, uint8_t n, uint16_t delta){
	//Calculate change comparing with old value.
	uint16_t value = *ADC_value;
	uint16_t ADC_change = (value > ADC_old_values[n]) ? value - ADC_old_values[n] : ADC_old_values[n] - value;
	if (ADC_change > delta)  //Change a result only if difference exceeds SLIDERS_DELTA.
		return 1;
	else
		return 0;
}


void read_controls(Slider_type* sliders, Calibration_slider_type* cal) {
	uint16_t ADC_value;
	uint8_t slider_number;
	uint16_t ODR_tmp;
	uint16_t tmp;
	uint16_t adc_arr[3][3];
	uint16_t adc_med;
	switch (controls_read_status) {
	case read_data:
		for (uint8_t i = 0; i < 3; i++) { //read all ADC1, ADC2, ADC3 3 times each and add to sum. Search min & max values for each ADC to remove them from sum in future
			for (uint8_t j = 0; j < 3; j++) { //Same for ADC1, ADC2, ADC3
				uint32_t adc = ADC1_BASE + j * 0x100; //change ADC base address to ADC2_BASE, ADC3_BASE
				adc_arr[j][i] = read_ADC(adc);
			}
		}
		for (uint8_t j = 0; j < 3; j++) {
			adc_med = median(adc_arr[j]); //apply simple median filter to all  ADC values
			ADC_res[mux_pin][j] = adc_med; //Calculate sum of values
		}

		controls_read_status = check_value;
		break;
	case check_value:
		//Calculate ADC results after measurement.
		for (uint8_t i = 0; i < 3; i++) { //Same for ADC1, ADC2, ADC3
			slider_number = mux_pin * 3 + i;
			ADC_value = median_filter(ADC_res[mux_pin][i],&filter_storage[slider_number]); //big median filter
			switch (sliders_state) { // SLIDERS_WORK is for ordinary work, other values are for calibration only
			case SLIDERS_WORK:
				//Calculate change comparing with old value.
				if (check_delta(&ADC_value, slider_number, cal->delta)) { //Change a result only if difference exceeds SLIDERS_DELTA.
					ADC_old_values[slider_number] = ADC_value;
					if (sliders[slider_number].active) //only active sliders work send fifo
						slider_FIFO_send(slider_number, ADC_value, &sliders[slider_number], &cal[slider_number]);
				}
				break;
			case SLIDERS_SEARCH:
				//Calculate change comparing with old value.
				if (check_delta(&ADC_value, slider_number, SLIDERS_DELTA_SEARCH)) { //Change a result only if difference exceeds SLIDERS_DELTA.
					ADC_old_values[slider_number] = ADC_value;
					slider_calibrate_number = slider_number;
					sliders_state = SLIDERS_FOUND;
					send_message(MES_SLIDER_SHOW);
				}
				break;
			case SLIDERS_MENU_SEARCH:
				//Calculate change comparing with old value.
				if (check_delta(&ADC_value, slider_number, SLIDERS_DELTA_SEARCH)) { //Change a result only if difference exceeds SLIDERS_DELTA.
					ADC_old_values[slider_number] = ADC_value;
					slider_calibrate_number = slider_number;
					send_message(MES_SLIDER_MENU_FOUND);
				}
				break;
			case SLIDERS_CALIBRATE:
				if (slider_number == slider_calibrate_number) {
					sliders_state = SLIDERS_EDGE;
					slider_calibrate_store = ADC_value;
					send_message(MES_SLIDER_EDGE);
				}
				break;
			default:
				break;
			}
		}
		controls_read_status = next_mux;
		break;
	case next_mux:
		//Switch multiplexors to next state
		mux_pin++;
		if (mux_pin > 7) {
			mux_pin = 0;
		}
		ODR_tmp = GPIOB->ODR & 0xFF8F; //PB4, PB5, PB6
		tmp = ODR_tmp | (mux_pin << 4); //next value to multiplexors PB4, PB5, PB6
		GPIOB->ODR = tmp;
		controls_read_status = wait_mux;
		break;
	case wait_mux:
		//Waiting several ticks after multiplexors switch
		tick_counter++;
		if (tick_counter >= SLIDERS_MUX_DELAY) {
			tick_counter = 0;
			controls_read_status = read_data;
		}
		break;
	}
}

static enum buttons_read_status_type {
	read_buttons, check_button, next_buttons_chunk, read_encoders
} buttons_read_status = read_buttons;


static uint16_t encoder_speed_counter=0;

static void encoder_speed_tick(void){
	if (encoder_speed_counter < 0xFFFF )
	 encoder_speed_counter++;
}


static encoder_speed_t encoder_speed_measure(void){
	if (encoder_speed_counter>ENCODER_SPEED1){
		encoder_speed_counter=0;
		return ENCODER_SLOW;
	}
	if (encoder_speed_counter>ENCODER_SPEED2){
    		encoder_speed_counter=0;
			return ENCODER_AVERAGE;
	}
	encoder_speed_counter=0;
	return ENCODER_FAST;
}


void read_buttons_state(void) {
	static uint8_t button_number; //Number of current button;
	uint16_t IDR_tmp;
	encoder_speed_tick();
	switch (buttons_read_status) {
	case read_buttons:
		if (!hd44780_active) { //If display is writing we do not read buttons to avoid pins conflict.
			buttons_active = 1; //Set to prevent display usage in this moment. The display should wait buttons_active = 0;
			GPIOE->ODR |= 0x00FF; //High level on PE0-7;
			GPIOE->MODER &= 0xFFFF0000; //PE0-7 Will be Input
			button_ports[buttons_chunk].port->BSRRH =
					button_ports[buttons_chunk].pin;
			buttons_delay();
			buttons = ~GPIOE->IDR; //Read buttons state
			button_ports[buttons_chunk].port->BSRRL =
					button_ports[buttons_chunk].pin;
			GPIOE->MODER |= 0x00005555; //PE0-7 Will be Output
			GPIOE->ODR |= 0x00FF; //High level on PD0-7;
			controlLEDs_switch();
			buttons_read_status = check_button;
			buttons_active = 0;
			break;
		} else {
			buttons_read_status = read_encoders;
			break;
		}
	case check_button:
		button_number = buttons_chunk * 8 + button_counter;

		if (buttons & button_positions[button_counter]) {
			if (buttons_state[button_number].value < BUTTON_MAX_STATE) {
				buttons_state[button_number].value++;
			} else if (!buttons_state[button_number].pressed) {
				FIFO_PUSH(control_events, button_number);
				buttons_state[button_number].pressed = 1;
				//send pressed
			}
		} else {
			if (buttons_state[button_number].value > 0) {
				buttons_state[button_number].value--;
			} else if (buttons_state[button_number].pressed) {
				FIFO_PUSH(control_events, 0x80|button_number);
				buttons_state[button_number].pressed = 0;
				//send depressed
			}
		}
		button_counter++;
		if (button_counter > 7) {
			button_counter = 0;
			buttons_read_status = next_buttons_chunk;
		}
		break;
	case next_buttons_chunk:
		buttons_chunk++;
		if (buttons_chunk > 2) {
			buttons_chunk = 0;
			buttons_read_status = read_encoders;
		} else {
			buttons_read_status = read_buttons;
		}
		break;
	case read_encoders:
		/*Read both encoder signals from the same port because  ENCODER1_PORT=ENCODER2_PORT =GPIOD*/
		IDR_tmp = (uint8_t)(
				(ENCODER1_PORT->IDR & ENCODER1_PIN)
						| (ENCODER2_PORT->IDR & ENCODER2_PIN));
		if (IDR_tmp == encoder_state) { //State is not changed
			buttons_read_status = read_buttons;
			break;
		} else {
			if (IDR_tmp == 0) {
				encoder_zero = 1;
				encoder_state = 0;
				buttons_read_status = read_buttons;
				break;
			} else if (IDR_tmp == 3) { // This means the encoder is in unstable average position because it is turned.
				if (encoder_zero) {
					if (encoder_state == 1) { //Direction depends previous state
						encoder_state = 3;
						switch (encoder_speed_measure()){
						case ENCODER_SLOW:
						   FIFO_PUSH(control_events, ENCODER_LEFT1);
						   break;
						case ENCODER_AVERAGE:
						   FIFO_PUSH(control_events, ENCODER_LEFT2);
						   break;
						case ENCODER_FAST:
						   FIFO_PUSH(control_events, ENCODER_LEFT3);
						   break;
						}
						buttons_read_status = read_buttons;
						encoder_zero = 0;
						break;
					} else if (encoder_state == 2) {
						encoder_state = 3;
						switch (encoder_speed_measure()){
						case ENCODER_SLOW:
						   FIFO_PUSH(control_events, ENCODER_RIGHT1);
						   break;
						case ENCODER_AVERAGE:
						   FIFO_PUSH(control_events, ENCODER_RIGHT2);
						   break;
						case ENCODER_FAST:
						   FIFO_PUSH(control_events, ENCODER_RIGHT3);
						   break;
						}
						buttons_read_status = read_buttons;
						encoder_zero = 0;
						break;
					}
					encoder_speed_counter = 0;
				} else {
					encoder_state = IDR_tmp;
					buttons_read_status = read_buttons;
					break;
				}
			} else {
				encoder_state = IDR_tmp;
				buttons_read_status = read_buttons;
				break;
			}
		}
	}

}

uint16_t get_slider_event(void) {
	if (FIFO_COUNT(sliders_events) != 0) {
		uint16_t event = FIFO_FRONT(sliders_events);
		FIFO_POP(sliders_events);
		//event maybe = 0, so this is for correct sending
		return event + 1;
	} else {
		return 0;
	}
}


uint16_t get_pitch_event(void) {
	if (FIFO_COUNT(pitch_events) != 0) {
		uint16_t event = FIFO_FRONT(pitch_events);
		FIFO_POP(pitch_events);
		return event + 1;
	} else {
		return 0;
	}
}

/*Check Sliders events according to the sliders_state*/
void checkSliders_events(Slider_type* sliders) {
	uint16_t event = get_slider_event();
	if (event) {
    	slider_midi_send(event - 1, sliders);
	}

	event = get_pitch_event();
	if (event) {
		pitch_midi_send(event - 1, sliders[SLIDER_PITCH].channel);
	}
}

void checkButtons_events(Button_type* buttons) {
	uint8_t event;
	if (FIFO_COUNT(control_events) == 0)
		return; //No events

	event = FIFO_FRONT(control_events);
	FIFO_POP(control_events);

	uint8_t btn_num = event & 0x7F;

	if (btn_num <= BUTTON_RIGHT || btn_num >= ENCODER_LEFT1) {
		if (!(event & 0x80))
		   control_buttons_handler(event);
	} else if (btn_num >= BUTTON_B1) {
		button_midi_send(event, buttons);
	}
}

