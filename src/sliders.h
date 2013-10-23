

typedef struct {
	uint8_t channel;
	uint8_t event;
	uint8_t value;
	uint8_t min_in_value;
	uint8_t max_in_value;
	uint8_t min_out_value;
	uint8_t max_out_value;
	uint8_t reverse;
} Slider;

void init_ADC(void);
void read_sliders(void);
