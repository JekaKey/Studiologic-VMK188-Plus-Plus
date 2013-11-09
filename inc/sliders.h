#include "timer.h"

#define SLIDERS_TICKS_FACTOR 2000/TIMER_TIMPERIOD
#define SLIDERS_DELTA 0x80
#define SLIDERS_MUX_DELAY 200/TIMER_TIMPERIOD
#define SLIDERS_MEASURE_NUM 100

#define SLIDER_S1 20
#define SLIDER_S2 4
#define SLIDER_S3 6
#define SLIDER_S4 7
#define SLIDER_S5 5
#define SLIDER_S6 2
#define SLIDER_S7 1
#define SLIDER_S8 0
#define SLIDER_S9 3

#define SLIDER_R1 11
#define SLIDER_R2 8
#define SLIDER_R3 9
#define SLIDER_R4 10
#define SLIDER_R5 13
#define SLIDER_R6 15
#define SLIDER_R7 14
#define SLIDER_R8 12

#define SLIDER_AT 21
#define SLIDER_PITCH 23
#define SLIDER_MOD 22
#define SLIDER_P1 19
#define SLIDER_P2 16
#define SLIDER_P3 17
#define SLIDER_EMPTY 18

#define SLIDER_S_MIN_IN 0
#define SLIDER_S_MAX_IN 1
#define SLIDER_S_MIN_OUT 0
#define SLIDER_S_MAX_OUT 127

#define SLIDER_R_MIN_IN 0
#define SLIDER_R_MAX_IN 1
#define SLIDER_R_MIN_OUT 0
#define SLIDER_R_MAX_OUT 127

#define SLIDER_P_MIN_IN 0
#define SLIDER_P_MAX_IN 1
#define SLIDER_P_MIN_OUT 0
#define SLIDER_P_MAX_OUT 127

#define SLIDER_PITCH_MIN_IN 0
#define SLIDER_PITCH_MAX_IN 1
#define SLIDER_PITCH_MIN_OUT 0
#define SLIDER_PITCH_MAX_OUT 127

#define SLIDER_MOD_MIN_IN 0
#define SLIDER_MOD_MAX_IN 1
#define SLIDER_MOD_MIN_OUT 0
#define SLIDER_MOD_MAX_OUT 127

#define SLIDER_AT_MIN_IN 0
#define SLIDER_AT_MAX_IN 1
#define SLIDER_AT_MIN_OUT 0
#define SLIDER_AT_MAX_OUT 127


typedef struct {
	uint8_t active;
	uint8_t channel;
	uint8_t event;
	uint8_t value;
	uint8_t min_in_value;
	uint8_t max_in_value;
	uint8_t min_out_value;
	uint8_t max_out_value;
	uint8_t reverse;
} Slider_type;

void ADC_init_all(void);
void read_sliders(void);
void sliders_init(void);
