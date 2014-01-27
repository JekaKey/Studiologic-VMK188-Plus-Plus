#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "menu.h"

extern FIFO16(128) control_events;
menuItem_type Null_Menu = { (void*) 0, (void*) 0, (void*) 0, (void*) 0, 0, { 0x00 } };

menuItem_type* selectedMenuItem; // current menu item

enum {
	status_presets, status_menu, status_curves
} interface_status;

void interface_init(void) {
	interface_status = status_presets;
}

void menuChange(menuItem_type* NewMenu) {
	if ((void*) NewMenu == (void*) &NULL_ENTRY)
		return;

	selectedMenuItem = NewMenu;
}

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

enum {
	MENU_CANCEL = 1, MENU_RESET, MENU_MODE1, MENU_MODE2, MENU_MODE3, MENU_SENS1, MENU_SENS2,
};

//                     NEXT,        PREVIOUS     PARENT,     CHILD
MAKE_MENU(menu1_item1, menu1_item2, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, 0, "Sliders");
MAKE_MENU(menu1_item2, menu1_item3, menu1_item1, NULL_ENTRY, NULL_ENTRY, 0, "Buttons");
MAKE_MENU(menu1_item3, menu1_item4, menu1_item2, NULL_ENTRY, NULL_ENTRY, 0, "Setting");
MAKE_MENU(menu1_item4, menu1_item5, menu1_item3, NULL_ENTRY, NULL_ENTRY, 0, "Curves");
MAKE_MENU(menu1_item5, NULL_ENTRY, menu1_item4, NULL_ENTRY, NULL_ENTRY, 0, "Calibration");

uint8_t dispMenu(void) {
	return (1);
}

void startMenu(void) {
	selectedMenuItem = (menuItem_type*) &menu1_item1;

	dispMenu();
}

uint8_t checkButtons_events(void) {
	uint16_t event;
	uint8_t button_number;

	if (FIFO_COUNT(control_events) == 0) {
		return 0;
	}
	event = FIFO_FRONT(control_events);
	FIFO_POP(control_events);
	if ((event & 0x00FF) == 0x00FF) { //Encoder Event
		if (event == 0x01FF) { //Encoder turned right
			return ENCODER_RIGHT;
		} else {
			return ENCODER_LEFT;
		}
	} else { //Button Event
		button_number = (uint8_t)(event & 0x00FF);
		if ((event & 0xFF00) == 0) { //Button down
			return 0;
		} else { //Button _up
			return event & 0x00FF; //return key number
		}
	}
}

void command_button_action(uint8_t button) {

}

void play_button_action(uint8_t button) {

}

void button_handler_menu(uint8_t button) {
	switch (button) {
		case BUTTON_PAGEUP: {
			menuChange(PREVIOUS);
			break;
		}
		case BUTTON_PAGEDOWN: {
			menuChange(NEXT);
			break;
		}
		case BUTTON_ENTER: {

		}
		case BUTTON_STORAGE: {
			break;
		}
		case BUTTON_EDIT: {
			interface_status = status_presets;
			break;
		}
		case BUTTON_PANIC: {

		}
		case BUTTON_CHANNEL: {

		}
		case BUTTON_BANK: {

		}
		case BUTTON_PROGRAM: {

		}
		case ENCODER_LEFT: {

		}
		case ENCODER_RIGHT: {

		}
	}

}

void button_handler_presets(uint8_t button) {
	switch (button) {
		case BUTTON_PAGEUP: {
			break;
		}
		case BUTTON_PAGEDOWN: {
			break;
		}
		case BUTTON_ENTER: {

		}
		case BUTTON_STORAGE: {

		}
		case BUTTON_EDIT: {
			interface_status = status_menu;
			break;
		}
		case BUTTON_PANIC: {

		}
		case BUTTON_CHANNEL: {

		}
		case BUTTON_BANK: {

		}
		case BUTTON_PROGRAM: {

		}
		case ENCODER_LEFT: {

		}
		case ENCODER_RIGHT: {

		}
	}

}

void button_handler_curves(uint8_t button) {
	switch (button) {
		case BUTTON_PAGEUP: {
			menuChange(PREVIOUS);
			break;
		}
		case BUTTON_PAGEDOWN: {
			menuChange(NEXT);
			break;
		}
		case BUTTON_ENTER: {

		}
		case BUTTON_STORAGE: {

		}
		case BUTTON_EDIT: {

		}
		case BUTTON_PANIC: {

		}
		case BUTTON_CHANNEL: {

		}
		case BUTTON_BANK: {

		}
		case BUTTON_PROGRAM: {

		}
		case ENCODER_LEFT: {

		}
		case ENCODER_RIGHT: {

		}
	}

}

void setup_button_action(uint8_t button) {
	switch (interface_status) {
		case status_presets: {
			button_handler_presets(button);
			break;
		}
		case status_menu: {
			button_handler_menu(button);
			break;
		}
		case status_curves: {
			button_handler_curves(button);
			break;
		}
	}
}

void button_action(void) {
	uint8_t result = checkButtons_events();
	if (result == 0) {
		return;
	}
	if ((result >= BUTTON_B1) && (result <= BUTTON_B8)) {
		command_button_action(result);
	} else if ((result >= BUTTON_LEFT) && (result <= BUTTON_STOP)) {
		play_button_action(result);
	} else {
		setup_button_action(result);
	}
}

uint8_t keyMenu(uint8_t par) {
	switch (par) {
		case BUTTON_PAGEUP: {
			menuChange(PREVIOUS);
			break;
		}
		case BUTTON_PAGEDOWN: {
			menuChange(NEXT);
			break;
		}
		case BUTTON_ENTER: { // item select
//			uint8_t sel;
//			sel = SELECT;
//			if (sel != 0) {
//				sendMessage(MSG_MENU_SELECT, sel);

//				killHandler(MSG_KEY_PRESS, &keyMenu);
//				killHandler(MSG_DISP_REFRESH, &dispMenu);

			return (1);
//			} else {
//				menuChange(CHILD);
//			}
			break;
		}
		case BUTTON_EDIT: { //return to parent
			menuChange(PARENT);
		}
	}
	dispMenu();
	return (1);
}
