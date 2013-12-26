#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "menu.h"

extern FIFO16(128) control_events;

/**********************************************/

void btoa(uint8_t value, char* buffer) {
	buffer += 2;
	*buffer = 0;
	*--buffer = value % 10 + 48;
	*--buffer = value / 10 + 48;
}
/***************************************************************************/
/*Function for the testing of buttons, encoders, and the display*/

int encoder_counter = 0; //test variable will removed after test


/*Check buttons and encoder FIFO buffer*/
void checkControl_events(void) {
	uint16_t event;
	char st[10];

	if (FIFO_COUNT(control_events) != 0) {
		event = FIFO_FRONT(control_events);
		FIFO_POP(control_events);
		hd44780_goto(1, 1);
		if ((event & 0x00FF) == 0x00FF) {
			if (event == 0x01FF) {
				encoder_counter++;
				if (encoder_counter > 99)
					encoder_counter = 0;
				hd44780_write_string("Encoder right ");
				btoa((uint8_t)(encoder_counter), st);
				hd44780_write_string(st);
			} else {
				encoder_counter--;
				if (encoder_counter < 0)
					encoder_counter = 99;
				hd44780_write_string("Encoder left  ");
				btoa((uint8_t)(encoder_counter), st);
				hd44780_write_string(st);
			}
		} else {
			hd44780_write_string("Butt ");
			btoa((uint8_t)(event & 0x00FF), st);
			hd44780_write_string(st);
			if ((event & 0xFF00) == 0) {
				hd44780_write_string(" down     ");
			} else {
				hd44780_write_string("  up      ");
			}
		}
	}

}
