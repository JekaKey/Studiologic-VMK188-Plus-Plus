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
const char slider_names[][MAX_ATTR_SIZE] = { ATTR_R2, ATTR_S8, ATTR_P2, ATTR_R3, ATTR_S2, ATTR_P1, ATTR_R4, ATTR_S6,
		                                     ATTR_EY, ATTR_R1, ATTR_S3, ATTR_P3, ATTR_R8, ATTR_S7, ATTR_S1, ATTR_R5,
		                                     ATTR_S5, ATTR_AT, ATTR_R7, ATTR_S9, ATTR_MO, ATTR_R6, ATTR_S4, ATTR_PI };
                                            // 0        1        2         3        4        5        6       7
const uint8_t pedalsN[PEDALS_N] = {SLIDER_P1, SLIDER_P2, SLIDER_P3};
const uint8_t slidersN[SLIDERS_N] = {SLIDER_S1, SLIDER_S2, SLIDER_S3, SLIDER_S4, SLIDER_S5 ,SLIDER_S6, SLIDER_S7, SLIDER_S8, SLIDER_S9};
const uint8_t knobsN[KNOBS_N] = {SLIDER_R1, SLIDER_R2, SLIDER_R3, SLIDER_R4, SLIDER_R5, SLIDER_R6, SLIDER_R7, SLIDER_R8};

const char button_names[][MAX_ATTR_SIZE] = { ATTR_B1, ATTR_B2, ATTR_B3, ATTR_B4, ATTR_B5, ATTR_B6, ATTR_B7,
		ATTR_B8 };

const uint8_t button_positions[8] = { 1, 2, 4, 8, 16, 32, 64, 128 }; //array with values for key select


FIFO8(128) control_events;
FIFO16(128) sliders_events;
FIFO16(128) pitch_events;

sliders_state_t sliders_state = SLIDERS_WORK;
uint8_t buttonsToMenu;
uint8_t buttons_control_state;


extern presetType Preset;

void send_message(uint8_t mes){
	FIFO_PUSH(control_events, mes);
}

static volatile uint16_t ADC_DMA_buffer[3]={0,0,0};// DMA puts ADC values to this buffer

void ADC_init_all()
{
	//variables
	DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	//RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);



	ADC_DeInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);


	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 3;
	ADC_Init(ADC1, &ADC_InitStructure);


	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_84Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_84Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_84Cycles);

    // DMA



    DMA_DeInit(DMA2_Stream4);//Can be used for ADC1
    DMA_InitStructure.DMA_Channel = 0;//Can be used for ADC1
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) &ADC_DMA_buffer; //DMA buffer Address
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//From ADC to memory
    DMA_InitStructure.DMA_BufferSize = 3;// 3
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream4, &DMA_InitStructure);

    DMA_Cmd(DMA2_Stream4, ENABLE);

    while(DMA_GetCmdStatus(DMA2_Stream4)==DISABLE){};


    ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

    ADC_ContinuousModeCmd(ADC1,ENABLE);

	ADC_SoftwareStartConv(ADC1);
	median_filter_init();
}


/*
 Set default values in an array of calibration structures.
 */

void sliders_calibr_set_defaults(Calibration_slider_type* sliders_calibr) {
	sliders_calibr[SLIDER_EMPTY].min_in_value = SLIDER_S_MIN_IN; //One slider is absent physically
	sliders_calibr[SLIDER_EMPTY].max_in_value = SLIDER_S_MAX_IN; //and initialized by any correct data
	sliders_calibr[SLIDER_EMPTY].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_EMPTY].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_EMPTY].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S1].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S1].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S1].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S1].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S1].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S2].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S2].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S2].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S2].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S2].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S3].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S3].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S3].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S3].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S3].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S4].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S4].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S4].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S4].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S4].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S5].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S5].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S5].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S5].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S5].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S6].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S6].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S6].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S6].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S6].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S7].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S7].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S7].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S7].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S7].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S8].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S8].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S8].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S8].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S8].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_S9].min_in_value = SLIDER_S_MIN_IN;
	sliders_calibr[SLIDER_S9].max_in_value = SLIDER_S_MAX_IN;
	sliders_calibr[SLIDER_S9].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_S9].gap = SLIDERS_S_GAP;
	sliders_calibr[SLIDER_S9].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R1].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R1].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R1].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R1].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R1].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R2].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R2].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R2].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R2].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R2].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R3].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R3].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R3].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R3].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R3].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R4].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R4].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R4].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R4].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R4].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R5].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R5].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R5].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R5].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R5].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R6].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R6].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R6].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R6].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R6].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R7].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R7].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R7].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R7].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R7].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_R8].min_in_value = SLIDER_R_MIN_IN;
	sliders_calibr[SLIDER_R8].max_in_value = SLIDER_R_MAX_IN;
	sliders_calibr[SLIDER_R8].delta = SLIDERS_DELTA_S;
	sliders_calibr[SLIDER_R8].gap = SLIDERS_R_GAP;
	sliders_calibr[SLIDER_R8].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_P1].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P1].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P1].delta = SLIDERS_DELTA_P;
	sliders_calibr[SLIDER_P1].gap = SLIDERS_P_GAP;
	sliders_calibr[SLIDER_P1].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_P2].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P2].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P2].delta = SLIDERS_DELTA_P;
	sliders_calibr[SLIDER_P2].gap = SLIDERS_P_GAP;
	sliders_calibr[SLIDER_P2].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_P3].min_in_value = SLIDER_P_MIN_IN;
	sliders_calibr[SLIDER_P3].max_in_value = SLIDER_P_MAX_IN;
	sliders_calibr[SLIDER_P3].delta = SLIDERS_DELTA_P;
	sliders_calibr[SLIDER_P3].gap = SLIDERS_P_GAP;
	sliders_calibr[SLIDER_P3].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_PITCH].min_in_value = SLIDER_PITCH_MIN_IN;
	sliders_calibr[SLIDER_PITCH].max_in_value = SLIDER_PITCH_MAX_IN;
	sliders_calibr[SLIDER_PITCH].delta = SLIDERS_DELTA_PI;
	sliders_calibr[SLIDER_PITCH].gap = SLIDERS_PI_GAP;
	sliders_calibr[SLIDER_PITCH].dead = SLIDERS_PI_DEAD;

	sliders_calibr[SLIDER_MOD].min_in_value = SLIDER_MOD_MIN_IN;
	sliders_calibr[SLIDER_MOD].max_in_value = SLIDER_MOD_MAX_IN;
	sliders_calibr[SLIDER_MOD].delta = SLIDERS_DELTA_MOD;
	sliders_calibr[SLIDER_MOD].gap = SLIDERS_MOD_GAP;
	sliders_calibr[SLIDER_MOD].dead = SLIDERS_DEAD;

	sliders_calibr[SLIDER_AT].min_in_value = SLIDER_AT_MIN_IN;
	sliders_calibr[SLIDER_AT].max_in_value = SLIDER_AT_MAX_IN;
	sliders_calibr[SLIDER_AT].delta = SLIDERS_DELTA_AT;
	sliders_calibr[SLIDER_AT].gap = SLIDERS_AT_GAP;
	sliders_calibr[SLIDER_AT].dead = SLIDERS_DEAD;
}


/*
 Set default values in an array of sliders with address "sliders" using an array of calibrations
 the size of addressed array must be equal SLIDERS_AMOUNT
 */
void sliders_set_defaults(Slider_type* sliders, Calibration_slider_type* sliders_calibr) {

	uint8_t i;

	sliders[SLIDER_EMPTY].active = 0;    //One slider is absent physically
	sliders[SLIDER_EMPTY].reverse = 0;
	sliders[SLIDER_EMPTY].binary = 0;
	sliders[SLIDER_EMPTY].channel = 0;
	sliders[SLIDER_EMPTY].event = 0;
	sliders[SLIDER_EMPTY].min_out_value = SLIDER_S_MIN_OUT;
	sliders[SLIDER_EMPTY].max_out_value = SLIDER_S_MAX_OUT;
	for (i = 0; i < SLIDERS_N; i++) {
		sliders[slidersN[i]].active = 0;
		sliders[slidersN[i]].reverse = 0;
		sliders[slidersN[i]].binary = 0;
		sliders[slidersN[i]].channel = 0;
		sliders[slidersN[i]].event = 11+i;
		sliders[slidersN[i]].min_out_value = SLIDER_S_MIN_OUT;
		sliders[slidersN[i]].max_out_value = SLIDER_S_MAX_OUT;
	}
	for (i = 0; i < KNOBS_N; i++) {
		sliders[knobsN[i]].active = 0;
		sliders[knobsN[i]].reverse = 0;
		sliders[knobsN[i]].binary = 0;
		sliders[knobsN[i]].channel = 0;
		sliders[knobsN[i]].event = 33+i;
		sliders[knobsN[i]].min_out_value = SLIDER_S_MIN_OUT;
		sliders[knobsN[i]].max_out_value = SLIDER_S_MAX_OUT;
	}

	sliders[SLIDER_P1].active = 0;
	sliders[SLIDER_P1].reverse = 0;
	sliders[SLIDER_P1].binary = 0;
	sliders[SLIDER_P1].channel = 0;
	sliders[SLIDER_P1].event = 65;
	sliders[SLIDER_P1].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P1].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P2].active = 1;
	sliders[SLIDER_P2].reverse = 1;
	sliders[SLIDER_P2].binary = 0;
	sliders[SLIDER_P2].channel = 0;
	sliders[SLIDER_P2].event = 64;
	sliders[SLIDER_P2].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P2].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_P3].active = 0;
	sliders[SLIDER_P3].reverse = 0;
	sliders[SLIDER_P3].binary = 1;
	sliders[SLIDER_P3].channel = 0;
	sliders[SLIDER_P3].event = 66;
	sliders[SLIDER_P3].min_out_value = SLIDER_P_MIN_OUT;
	sliders[SLIDER_P3].max_out_value = SLIDER_P_MAX_OUT;

	sliders[SLIDER_PITCH].active = 1;
	sliders[SLIDER_PITCH].reverse = 1;
	sliders[SLIDER_PITCH].binary = 0;
	sliders[SLIDER_PITCH].channel = 0;
	sliders[SLIDER_PITCH].event = 66;
	sliders[SLIDER_PITCH].min_out_value = SLIDER_PITCH_MIN_OUT;
	sliders[SLIDER_PITCH].max_out_value = SLIDER_PITCH_MAX_OUT;

	sliders[SLIDER_MOD].active = 1;
	sliders[SLIDER_MOD].reverse = 0;
	sliders[SLIDER_MOD].binary = 0;
	sliders[SLIDER_MOD].channel = 0;
	sliders[SLIDER_MOD].event = 1;
	sliders[SLIDER_MOD].min_out_value = SLIDER_MOD_MIN_OUT;
	sliders[SLIDER_MOD].max_out_value = SLIDER_MOD_MAX_OUT;

	sliders[SLIDER_AT].active = 0;
	sliders[SLIDER_AT].reverse = 0;
	sliders[SLIDER_AT].binary = 0;
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

static uint16_t mux_pin = 0; //Multiplexor pin number 0..7
static uint16_t ADC_old_values[SLIDERS_AMOUNT] = { 0 };
static uint8_t sliders_old_values[SLIDERS_AMOUNT] = { 0 };
static uint16_t pitch_old_value = 8192;
static uint8_t buttons_chunk = 0;
static uint8_t buttons; //result of IDR reading
static uint8_t button_counter = 0; //Number of a button in chunk
static uint8_t encoder_state = 3;
static uint8_t encoder_zero = 0;
static uint8_t ADC_channel=0;



uint8_t slider_calibrate_number = 0; // Slider chosen for calibrate procedure;
uint16_t slider_calibrate_store;
uint8_t buttons_active = 0; //This flag prevents activity of buttons and  hd44780 in the same time

extern uint8_t hd44780_active; //This flag prevents activity of buttons and  hd44780 in the same time


static void slider_FIFO_send(uint8_t num, uint16_t value, Slider_type* sliders, Calibration_slider_type* sliders_calibr) {
	double a,b;
	int midi_value;

	double max_in = sliders_calibr->max_in_value;
	double min_in = sliders_calibr->min_in_value;
	double length = max_in - min_in;
	min_in = min_in + length / 100 * (double)(sliders_calibr->gap);
	max_in = max_in - length / 100 * (double)(sliders_calibr->gap);
	length = max_in - min_in;

	//pitch band has a dead zone and 14-bit precision
	if (num == SLIDER_PITCH) {
		double dead = (double)sliders_calibr->dead / 100 * length;
		a = (double) (sliders->max_out_value - sliders->min_out_value) / (double) (length - dead);

		double middle_in = (double)(max_in + min_in) / 2;
		double middle_out = (double)(sliders->max_out_value + sliders->min_out_value) / 2;

		//alpha is the point when the dead zone begins
		double alpha = middle_in - dead/2;

		//pitch potentiometer is inverted
		value = max_in - value + min_in;

		//the in-out function is piecewise linear
		if (value < alpha) {
			midi_value = (int)(a * value - min_in * a + sliders->min_out_value);
		} else if (value < alpha + dead) {
			midi_value = (middle_out - (int) middle_out) > 0   ?  (int) (middle_out + 1)   :  (int) middle_out;
		} else {
			midi_value = (int)(a * value - (alpha + dead) * a + middle_out);
		}
	} else if (num==SLIDER_MOD) {
			double dead = (double)sliders_calibr->dead / 100 * length;
			a = (double) (sliders->max_out_value - sliders->min_out_value)*2.0/ (double) (length - dead);

			double middle_in = (double)(max_in + min_in) / 2;

			//alpha is the point when the dead zone begins
			double alpha = middle_in - dead/2;
			value = max_in - value + min_in;


			if (value < alpha) {
				midi_value = (int)(a * (min_in-value) + sliders->max_out_value);
			} else if (value < alpha + dead) {
				midi_value = sliders->min_out_value;
			} else {
				midi_value = (int)(a * (value-max_in) + sliders->max_out_value);
			}
	}else{
		a = (double) (sliders->max_out_value - sliders->min_out_value) / length;
		if (sliders->reverse) {
			a = -a;
			b = (double)(sliders->max_out_value) - min_in * a;
		} else {
			b = (double)(sliders->min_out_value) - min_in * a;
		}
		midi_value = (int)(a * value + b);
	}

	if (sliders->binary) {
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

void slider_midi_send(uint16_t value, Slider_type* sliders, uint8_t analog) {
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
			sendAfterTouch((uint8_t)(midi_value), channel, analog);
			break;
		default:
			sendControlChange(sliders[num].event, (uint8_t)(midi_value), channel, analog);
			break;
		}
}

void pitch_midi_send(uint16_t value, uint8_t channel, uint8_t analog) {
	channel = channel ? channel : Preset.MidiChannel;
	if (channel)
		channel--; //Real channels are 0-15
	if (channel > 15)
		 channel = 0;

	sendPitchBend(value, channel, analog);
}

void button_midi_send(uint16_t value, Button_type* buttons, uint8_t analog) {
	uint8_t is_pressed = (value & 0x80) ? 0 : 1;
	uint8_t num = value & 0x7F;

	if ((num < BUTTON_B1) && is_pressed) {
		switch (num) {
		case BUTTON_STOP:
			sendMMC(MMC_STOP, analog);
			break;
		case BUTTON_PLAY:
			sendMMC(MMC_PLAY, analog);
			break;
		case BUTTON_RECORD:
			sendMMC(MMC_REC, analog);
			break;
		case BUTTON_LEFT:
			if (Preset.TransportBtnFunc==0)
				sendMMC(MMC_RW, analog);
		case BUTTON_RIGHT:
			if (Preset.TransportBtnFunc==0)
				sendMMC(MMC_FF, analog);
		}
		return;
	}

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
				sendControlChange(buttons[num].event, buttons[num].off, channel, analog);
				buttons_control_state -= button_positions[num];
			} else {
				sendControlChange(buttons[num].event, buttons[num].on, channel, analog);
				buttons_control_state += button_positions[num];
			}
		} else {
			sendControlChange(buttons[num].event, buttons[num].on, channel, analog);
		}
	} else if (buttons[num].type == BTN_TYPE_PUSH) {
		sendControlChange(buttons[num].event, buttons[num].off, channel, analog);
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



static enum controls_read_status_type {
	NEXT_MUX, WAIT_MUX, CHECK_VALUE
} controls_read_status = CHECK_VALUE;

extern filter_storage_t filter_storage[NUMBER_OF_BUFFERS];


/*Variables to calculate advanced delta*/
static struct {int16_t buf[MAX_DELTA_COUNTER];
               uint8_t index;
               uint8_t count;
               int16_t sum;
               } delta_storage[SLIDERS_AMOUNT];
/********/



static uint8_t check_delta(uint16_t * ADC_value, uint8_t n, uint16_t delta){
	//Calculate change comparing with old value.
	uint16_t value = *ADC_value;
	uint16_t ADC_change = (value > ADC_old_values[n]) ? value - ADC_old_values[n] : ADC_old_values[n] - value;
	if (ADC_change > delta)  //Change a result only if difference exceeds SLIDERS_DELTA.
		return 1;
	else
		return 0;
}



static uint8_t check_integral_delta(uint16_t * ADC_value, uint8_t sliderNum, uint16_t delta) {
	//Calculate change comparing with old value.

	uint8_t buffer_full = (delta_storage[sliderNum].count >= MAX_DELTA_COUNTER);
	if (!buffer_full)
		delta_storage[sliderNum].count++;

	int16_t diff = (int16_t)(*ADC_value) - (int16_t)(ADC_old_values[sliderNum]);
	delta_storage[sliderNum].sum += diff;
	if (buffer_full)
		delta_storage[sliderNum].sum -= delta_storage[sliderNum].buf[ delta_storage[sliderNum].index ];

	delta_storage[sliderNum].buf[ delta_storage[sliderNum].index ] = diff;

	delta_storage[sliderNum].index++;
	if (delta_storage[sliderNum].index >= MAX_DELTA_COUNTER)
		delta_storage[sliderNum].index = 0;

	int16_t ADC_change = delta_storage[sliderNum].sum;
	ADC_change = ADC_change > 0  ?  ADC_change  :  - ADC_change;
	if ((uint16_t)ADC_change > delta) {  //Change a result only if difference exceeds SLIDERS_DELTA.
		*ADC_value = ADC_old_values[sliderNum] + delta_storage[sliderNum].sum / delta_storage[sliderNum].count;
		delta_storage[sliderNum].sum = 0;
		delta_storage[sliderNum].count = 0;
		delta_storage[sliderNum].index = 0;
		for (int i = 0; i < MAX_DELTA_COUNTER; i++)
			delta_storage[sliderNum].buf[i] = 0;
		return 1;
	}
	return 0;
}

static uint16_t ADC_sourse[SLIDERS_AMOUNT] [3];

void read_controls(Slider_type* sliders, Calibration_slider_type* cal) {
	uint16_t ADC_value;
	uint8_t slider_number;
	uint16_t ODR_tmp;
	uint16_t tmp;
	uint16_t adc_res;
	uint8_t mux3;
	uint8_t i;

	switch (controls_read_status) {
	case CHECK_VALUE:
		mux3=mux_pin*3;
		for (i=0; i<3; i++)
			ADC_sourse[mux3+i][ADC_channel]= ADC_DMA_buffer[i] & 0x0FFF;
		slider_number = mux3 + ADC_channel;
		adc_res = median(&ADC_sourse[slider_number][0]);
		ADC_value = median_filter(adc_res, &filter_storage[slider_number]); //big window median filter
		switch (sliders_state) { // SLIDERS_WORK is for ordinary work, other values are for calibration only
		case SLIDERS_WORK:
			//Calculate change comparing with old value.
			if (check_integral_delta(&ADC_value, slider_number, cal[slider_number].delta)) { //Change a result only if difference exceeds SLIDERS_DELTA.
				ADC_old_values[slider_number] = ADC_value;
				if (sliders[slider_number].active) //only active sliders work send fifo
					slider_FIFO_send(slider_number, ADC_value,
							&sliders[slider_number], &cal[slider_number]);
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
		ADC_channel++;
		if (ADC_channel>=3){
		   ADC_channel=0;
		   controls_read_status = NEXT_MUX;
		}
		break;
	case NEXT_MUX:
		//Switch multiplexors to next state
		mux_pin++;
		if (mux_pin > 7) {
			mux_pin = 0;
		}
		ODR_tmp = GPIOB->ODR & 0xFF8F; //PB4, PB5, PB6
		tmp = ODR_tmp | (mux_pin << 4); //next value to multiplexors PB4, PB5, PB6
		GPIOB->ODR = tmp;
		controls_read_status = WAIT_MUX;
		break;
	case WAIT_MUX:
		controls_read_status = CHECK_VALUE;
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
void checkSliders_events(Slider_type* sliders, uint8_t analog) {
	uint16_t event = get_slider_event();
	if (event) {
    	slider_midi_send(event - 1, sliders, analog);
	}

	event = get_pitch_event();
	if (event) {
		pitch_midi_send(event - 1, sliders[SLIDER_PITCH].channel, analog);
	}
}

void checkButtons_events(Button_type* buttons, uint8_t analog) {
	uint8_t event;

	if (FIFO_COUNT(control_events) == 0)
		return; //No events

	event = FIFO_FRONT(control_events);
	FIFO_POP(control_events);

	uint8_t btn_num = event & 0x7F;

	//messages has number > ENCODER_LEFT1
	//so messages sends to menu_btns_n_msg_handler
	if (btn_num == BUTTON_PANIC) {
		if (!(event & 0x80))
			sendPanicAll(Preset.AnalogMidiEnable);
	} else if (btn_num <= BUTTON_RIGHT || btn_num >= ENCODER_LEFT1 || buttonsToMenu) {
		   menu_btns_n_msg_handler(event);
	} else {
		button_midi_send(event, buttons, analog);
	}
}

