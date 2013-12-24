//#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include "presets.h"
#include "controls.h"
#include "midi.h"
#include "usb_midi_io.h"
#include "fifo.h"

FIFO16(128) control_events;
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

static Slider_type sliders[24];
static enum controls_read_status_type {
	next_mux, wait_mux, read_data, check_value, read_buttons, check_button, next_buttons_chunk, read_encoders
} controls_read_status = read_data;

void slider_init_struct(uint8_t num) {
	if (sliders[num].reverse) {
		sliders[num].a = (double) (sliders[num].max_out_value - sliders[num].min_out_value) / (double) ((int) (sliders[num].min_in_value) - (int) (sliders[num].max_in_value));
		sliders[num].b = (double) (sliders[num].min_out_value) - (double) (sliders[num].max_in_value) * sliders[num].a;
	} else {
		sliders[num].a = (double) (sliders[num].max_out_value - sliders[num].min_out_value) / (double) (sliders[num].max_in_value - sliders[num].min_in_value);
		sliders[num].b = (double) (sliders[num].min_out_value) - (double) (sliders[num].min_in_value) * sliders[num].a;
	}
}

void sliders_init(void) {

	sliders[SLIDER_EMPTY].active = 0;

	sliders[SLIDER_S1].active = 1;
	sliders[SLIDER_S1].reverse = 0;
	sliders[SLIDER_S1].channel = 0;
	sliders[SLIDER_S1].event = 7;
	sliders[SLIDER_S1].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S1].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S1].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S1].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S1);

	sliders[SLIDER_S2].active = 1;
	sliders[SLIDER_S2].reverse = 0;
	sliders[SLIDER_S2].channel = 0;
	sliders[SLIDER_S2].event = 22;
	sliders[SLIDER_S2].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S2].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S2].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S2].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S2);

	sliders[SLIDER_S3].active = 1;
	sliders[SLIDER_S3].reverse = 0;
	sliders[SLIDER_S3].channel = 0;
	sliders[SLIDER_S3].event = 23;
	sliders[SLIDER_S3].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S3].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S3].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S3].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S3);

	sliders[SLIDER_S4].active = 1;
	sliders[SLIDER_S4].reverse = 0;
	sliders[SLIDER_S4].channel = 0;
	sliders[SLIDER_S4].event = 24;
	sliders[SLIDER_S4].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S4].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S4].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S4].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S4);

	sliders[SLIDER_S5].active = 1;
	sliders[SLIDER_S5].reverse = 0;
	sliders[SLIDER_S5].channel = 0;
	sliders[SLIDER_S5].event = 25;
	sliders[SLIDER_S5].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S5].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S5].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S5].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S5);

	sliders[SLIDER_S6].active = 1;
	sliders[SLIDER_S6].reverse = 0;
	sliders[SLIDER_S6].channel = 0;
	sliders[SLIDER_S6].event = 26;
	sliders[SLIDER_S6].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S6].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S6].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S6].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S6);

	sliders[SLIDER_S7].active = 1;
	sliders[SLIDER_S7].reverse = 0;
	sliders[SLIDER_S7].channel = 0;
	sliders[SLIDER_S7].event = 27;
	sliders[SLIDER_S7].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S7].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S7].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S7].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S7);

	sliders[SLIDER_S8].active = 1;
	sliders[SLIDER_S8].reverse = 0;
	sliders[SLIDER_S8].channel = 0;
	sliders[SLIDER_S8].event = 28;
	sliders[SLIDER_S8].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S8].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S8].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S8].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S8);

	sliders[SLIDER_S9].active = 1;
	sliders[SLIDER_S9].reverse = 0;
	sliders[SLIDER_S9].channel = 0;
	sliders[SLIDER_S9].event = 29;
	sliders[SLIDER_S9].min_in_value = SLIDER_S_MIN_IN;
	sliders[SLIDER_S9].max_in_value = SLIDER_S_MAX_IN;
	sliders[SLIDER_S9].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_S9].max_out_value = SLIDER_S_MAX_OUT;
	slider_init_struct(SLIDER_S9);

	sliders[SLIDER_R1].active = 1;
	sliders[SLIDER_R1].reverse = 0;
	sliders[SLIDER_R1].channel = 0;
	sliders[SLIDER_R1].event = 71;
	sliders[SLIDER_R1].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R1].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R1].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R1].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R1);

	sliders[SLIDER_R2].active = 1;
	sliders[SLIDER_R2].reverse = 0;
	sliders[SLIDER_R2].channel = 0;
	sliders[SLIDER_R2].event = 72;
	sliders[SLIDER_R2].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R2].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R2].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R2].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R2);

	sliders[SLIDER_R3].active = 1;
	sliders[SLIDER_R3].reverse = 0;
	sliders[SLIDER_R3].channel = 0;
	sliders[SLIDER_R3].event = 73;
	sliders[SLIDER_R3].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R3].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R3].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R3].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R3);

	sliders[SLIDER_R4].active = 1;
	sliders[SLIDER_R4].reverse = 0;
	sliders[SLIDER_R4].channel = 0;
	sliders[SLIDER_R4].event = 74;
	sliders[SLIDER_R4].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R4].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R4].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R4].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R4);

	sliders[SLIDER_R5].active = 1;
	sliders[SLIDER_R5].reverse = 0;
	sliders[SLIDER_R5].channel = 0;
	sliders[SLIDER_R5].event = 75;
	sliders[SLIDER_R5].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R5].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R5].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R5].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R5);

	sliders[SLIDER_R6].active = 1;
	sliders[SLIDER_R6].reverse = 0;
	sliders[SLIDER_R6].channel = 0;
	sliders[SLIDER_R6].event = 76;
	sliders[SLIDER_R6].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R6].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R6].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R6].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R6);

	sliders[SLIDER_R7].active = 1;
	sliders[SLIDER_R7].reverse = 0;
	sliders[SLIDER_R7].channel = 0;
	sliders[SLIDER_R7].event = 77;
	sliders[SLIDER_R7].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R7].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R7].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R7].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R7);

	sliders[SLIDER_R8].active = 1;
	sliders[SLIDER_R8].reverse = 0;
	sliders[SLIDER_R8].channel = 0;
	sliders[SLIDER_R8].event = 78;
	sliders[SLIDER_R8].min_in_value = SLIDER_R_MIN_IN;
	sliders[SLIDER_R8].max_in_value = SLIDER_R_MAX_IN;
	sliders[SLIDER_R8].min_out_value = SLIDER_R_MIN_OUT;
	sliders[SLIDER_R8].max_out_value = SLIDER_R_MAX_OUT;
	slider_init_struct(SLIDER_R8);

	sliders[SLIDER_P2].active = 1;
	sliders[SLIDER_P2].reverse = 1;
	sliders[SLIDER_P2].channel = 0;
	sliders[SLIDER_P2].event = 64;
	sliders[SLIDER_P2].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P2].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P2].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P2].max_out_value = SLIDER_P_MAX_OUT;
	slider_init_struct(SLIDER_P2);

	sliders[SLIDER_P1].active = 0;
	sliders[SLIDER_P1].reverse = 0;
	sliders[SLIDER_P1].channel = 0;
	sliders[SLIDER_P1].event = 65;
	sliders[SLIDER_P1].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P1].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P1].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P1].max_out_value = SLIDER_P_MAX_OUT;
	slider_init_struct(SLIDER_P1);

	sliders[SLIDER_P3].active = 0;
	sliders[SLIDER_P3].reverse = 0;
	sliders[SLIDER_P3].channel = 0;
	sliders[SLIDER_P3].event = 66;
	sliders[SLIDER_P3].min_in_value = SLIDER_P_MIN_IN;
	sliders[SLIDER_P3].max_in_value = SLIDER_P_MAX_IN;
	sliders[SLIDER_P3].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P3].max_out_value = SLIDER_P_MAX_OUT;
	slider_init_struct(SLIDER_P3);

	sliders[SLIDER_PITCH].active = 1;
	sliders[SLIDER_PITCH].reverse = 0;
	sliders[SLIDER_PITCH].channel = 0;
	sliders[SLIDER_PITCH].event = 66;
	sliders[SLIDER_PITCH].min_in_value = SLIDER_PITCH_MIN_IN;
	sliders[SLIDER_PITCH].max_in_value = SLIDER_PITCH_MAX_IN;
	sliders[SLIDER_PITCH].min_out_value = SLIDER_PITCH_MIN_OUT;
	sliders[SLIDER_PITCH].max_out_value = SLIDER_PITCH_MAX_OUT;
	slider_init_struct(SLIDER_PITCH);

	sliders[SLIDER_MOD].active = 1;
	sliders[SLIDER_MOD].reverse = 0;
	sliders[SLIDER_MOD].channel = 0;
	sliders[SLIDER_MOD].event = 1;
	sliders[SLIDER_MOD].min_in_value = SLIDER_MOD_MIN_IN;
	sliders[SLIDER_MOD].max_in_value = SLIDER_MOD_MAX_IN;
	sliders[SLIDER_MOD].min_out_value = SLIDER_MOD_MIN_OUT;
	sliders[SLIDER_MOD].max_out_value = SLIDER_MOD_MAX_OUT;
	slider_init_struct(SLIDER_MOD);

	sliders[SLIDER_AT].active = 0;
	sliders[SLIDER_AT].reverse = 0;
	sliders[SLIDER_AT].channel = 0;
	sliders[SLIDER_AT].event = 66;
	sliders[SLIDER_AT].min_in_value = SLIDER_AT_MIN_IN;
	sliders[SLIDER_AT].max_in_value = SLIDER_AT_MAX_IN;
	sliders[SLIDER_AT].min_out_value = SLIDER_AT_MIN_OUT;
	sliders[SLIDER_AT].max_out_value = SLIDER_AT_MAX_OUT;
	slider_init_struct(SLIDER_AT);

}

static uint16_t tick_counter = 0; //Counter of timer ticks
static uint16_t mux_pin = 0; //Multiplexor pin number 0..7
static uint8_t slider_number = 0; // Slider number from 0 to 23
static uint32_t ADC1_sum = 0; //SUM of ADC1 measuring
static uint32_t ADC2_sum = 0; //SUM of ADC2 measuring
static uint32_t ADC3_sum = 0; //SUM of ADC3 measuring
uint16_t ADC_old_values[24] = { 0 };
uint8_t sliders_old_values[24] = { 0 };
button_port_type button_ports[3] = { { BUTTON0_PORT, BUTTON0_PIN }, { BUTTON1_PORT, BUTTON1_PIN }, { BUTTON2_PORT, BUTTON2_PIN } };
static uint8_t buttons_chunk = 0;
static uint8_t buttons_state[24] = { 0 };
static uint8_t buttons;
static uint8_t button_counter = 0; //Number of a button in chunk
static uint8_t encoder_state = 3;
static uint8_t encoder_zero = 0;
extern uint8_t hd44780_active;
uint8_t buttons_active = 0;

static void slider_FIFO_send(uint8_t num, uint16_t value) {
	int midi_value;
	midi_value = (uint8_t)(sliders[num].a * value + sliders[num].b);
	if (midi_value > 127) {
		midi_value = 127;
	}
	if (midi_value < 0) {
		midi_value = 0;
	}
	if (midi_value!=sliders_old_values[num]){
		FIFO_PUSH(sliders_events, (((uint16_t)(midi_value))<<8)+num);
		sliders_old_values[num]=midi_value;
	}
}

void slider_midi_send(uint16_t value) {
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

static void volatile buttons_delay(void) {
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

void read_controls() {
	uint16_t ADC_value;
	uint16_t ADC_change;
	uint16_t ODR_tmp, IDR_tmp, tmp;
	static uint8_t button_number; //Number of current button;
	uint8_t k[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select
	uint8_t i;
	uint16_t adc1_arr[3], adc2_arr[3], adc3_arr[3];
	switch (controls_read_status) {

		case read_data:
			for (i = 0; i < 3; i++) {
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
			ADC1_sum += median(adc1_arr);
			ADC2_sum += median(adc2_arr);
			ADC3_sum += median(adc3_arr);
			tick_counter++;
			if (tick_counter >= SLIDERS_MEASURE_NUM) {
				tick_counter = 0;
				controls_read_status = check_value;
			}

			break;
		case check_value:
			if (sliders[slider_number].active) {
				ADC_value = ADC1_sum / SLIDERS_MEASURE_NUM;
				ADC1_sum = 0;
				if (ADC_value > ADC_old_values[slider_number]) {
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > SLIDERS_DELTA) {
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value);
				}
			} else {
				ADC1_sum = 0;
			}
			slider_number++;

			if (sliders[slider_number].active) {
				ADC_value = ADC2_sum / SLIDERS_MEASURE_NUM;
				ADC2_sum = 0;
				if (ADC_value > ADC_old_values[slider_number]) {
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > SLIDERS_DELTA) {
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value);
				}
			} else {
				ADC2_sum = 0;
			}
			slider_number++;

			if (sliders[slider_number].active) {
				ADC_value = ADC3_sum / SLIDERS_MEASURE_NUM;
				ADC3_sum = 0;
				if (ADC_value > ADC_old_values[slider_number]) {
					ADC_change = ADC_value - ADC_old_values[slider_number];
				} else {
					ADC_change = ADC_old_values[slider_number] - ADC_value;
				}
				if (ADC_change > SLIDERS_DELTA) {
					ADC_old_values[slider_number] = ADC_value;
					slider_FIFO_send(slider_number, ADC_value);
				}
			} else {
				ADC3_sum = 0;
			}
			controls_read_status = next_mux;
			break;
		case next_mux:
			mux_pin++;
			if (mux_pin > 7) {
				mux_pin = 0;
			}
			ODR_tmp = GPIOC->ODR & 0xFCBF;
			tmp = ODR_tmp | ((mux_pin & 0x0006) << 7) | ((mux_pin & 0x0001) << 6); //next value to multiplexors PC6, PC8, PC9
			GPIOC->ODR = tmp;
			slider_number = mux_pin * 3;
			controls_read_status = wait_mux;
			break;
		case wait_mux:
			tick_counter++;
			if (tick_counter >= SLIDERS_MUX_DELAY) {
				tick_counter = 0;
				controls_read_status = read_buttons;
			}
			break;
		case read_buttons:
			if (!hd44780_active) {
				buttons_active = 1;
				GPIOD->ODR |= 0x00FF; //High level on PA0-7;
				GPIOD->MODER &= 0xFFFF0000; //PA0-7 Will be Input
				button_ports[buttons_chunk].port->BSRRH = button_ports[buttons_chunk].pin;
				buttons_delay();
				buttons = ~GPIOD->IDR; //Read buttons state
				button_ports[buttons_chunk].port->BSRRL = button_ports[buttons_chunk].pin;
				GPIOD->MODER |= 0x00005555; //PA0-7 Will be Output
				GPIOD->ODR |= 0x00FF; //High level on PA0-7;
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
					FIFO_PUSH(control_events, (uint16_t)(button_number));
					//send pressed
				}
			} else {
				if (buttons_state[button_number] != 0) {
					buttons_state[button_number] = 0;
					FIFO_PUSH(control_events, 0xFF00|(uint16_t)(button_number));
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
			IDR_tmp = (uint8_t)(((ENCODER1_PORT->IDR & ENCODER1_PIN) >> 12) | ((ENCODER2_PORT->IDR & ENCODER2_PIN) >> 11)); //Read both encoder signals from the same port because  ENCODER1_PORT=ENCODER2_PORT =GPIOC
			if (IDR_tmp == encoder_state) {
				controls_read_status = read_data;
				break;
			} else {
				if (IDR_tmp == 0) {
					encoder_zero = 1;
					encoder_state = 0;
					controls_read_status = read_data;
					break;
				} else if (IDR_tmp == 3) {
					if (encoder_zero) {
						if (encoder_state == 1) {
							encoder_state = 3;
							FIFO_PUSH(control_events, 0x01FF);
							controls_read_status = read_data;
							encoder_zero = 0;
							break;
						} else if (encoder_state == 2) {
							encoder_state = 3;
							FIFO_PUSH(control_events, 0x02FF);
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
