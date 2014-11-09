#include <string.h>
#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "menu.h"
#include "sd_fatfs.h"
#include "log.h"

extern FIFO8(128) control_events; //defined in "control.c"

menuItem_type Null_Menu = { (void*) 0, (void*) 0, (void*) 0, (void*) 0, 0, { 0x00 } };

menuItem_type* selectedMenuItem; // current menu item

static enum {state_presets, state_menu, state_curves } I_state;

void menuChange(menuItem_type* NewMenu) {
	if ((void*) NewMenu == (void*) &NULL_ENTRY)
		return;

	selectedMenuItem = NewMenu;
}

extern file_list_type presets_list, calibrations_list, curves_list;
extern presetType Preset;


/**********************************************/

void btoa(const uint8_t value, char* buffer) {
	buffer += 2;
	*buffer = 0;
	*--buffer = value % 10 + 48;
	*--buffer = value / 10 + 48;
}

void btoa_mem(const uint8_t value, char* buffer) {
	buffer += 2;
	*--buffer = value % 10 + 48;
	*--buffer = value / 10 + 48;
}

/***************************************************************************/
/*Function for the testing of buttons, encoders, and the display*/

const char note_names[12][3]={"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};

static int note_name (uint8_t note_num, char *name) {
	if (!note_num) {
		name[0]=0;
		return 0;
	}
	note_num--;
	strcpy(name, note_names[note_num%12]);
	int l=strlen(name);
	name[l]=note_num/12+'0';
	l++;
//	name[l]=0;
	return l;
}


enum {
	MENU_CANCEL, MENU_RESET, MENU_MODE1, MENU_MODE2, MENU_MODE3, MENU_SENS1, MENU_SENS2};

//                     NEXT,        PREVIOUS     PARENT,     CHILD
MAKE_MENU(menu1_item1, menu1_item2, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, 0, "Sliders");
MAKE_MENU(menu1_item2, menu1_item3, menu1_item1, NULL_ENTRY, NULL_ENTRY, 0, "Buttons");
MAKE_MENU(menu1_item3, menu1_item4, menu1_item2, NULL_ENTRY, NULL_ENTRY, 0, "Setting");
MAKE_MENU(menu1_item4, menu1_item5, menu1_item3, NULL_ENTRY, NULL_ENTRY, 0, "Curves");
MAKE_MENU(menu1_item5, NULL_ENTRY, menu1_item4, NULL_ENTRY, NULL_ENTRY, 0, "Calibration");

void text_object_init(text_object_t *object, const char *st, const uint8_t line) {
	strcpy(object->text, st);
	object->pos = 0;
	object->state = start;
	object->line = line;
}

void text_object_edit(text_object_t *object, char *st){

}

uint8_t dispMenu(void) {
	return (1);
}

void startMenu(void) {
	selectedMenuItem = (menuItem_type*) &menu1_item1;

	dispMenu();
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
			I_state = state_presets;
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

/*this function is calling if any setup button pressed, according to
 * the interface status it calls button_handlers
 */


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

static void show_preset (const presetType *pr, char *name){
	char line[17];
	memset(line,' ',16);
	line[16]=0;
	int len = strlen(name);
	memcpy(line, name, len-4);
	hd44780_goto(1,1);
	hd44780_write_string(line);
	memset(line,' ',16);
	memcpy(line,"Ch:",3);
    btoa_mem(pr->MidiChannel+1,line+3);
    if (pr->SplitKey){
	    len=note_name(pr->SplitKey,line+6)+6;
	    memcpy(line+len," Ch:",4 );
	    btoa_mem(pr->SplitChannel+1,line +len+4);
    }
	hd44780_goto(2,1);
	hd44780_write_string(line);
}


static void presets_button_handler(uint8_t button){
	switch (button) {
	case BUTTON_PAGEUP: {
		presets_list.pos--;
		if (presets_list.pos == 0xFFFF)
			presets_list.pos = presets_list.num - 1;
		FIO_status status=preset_load(presets_list.names[presets_list.pos], &Preset);
		LOG("Preset %s loaded with status: %d\r\n",presets_list.names[presets_list.pos],status);
		status=curve_load(Preset.CurveFileName, &Preset);
		LOG("Curve %s loaded with status: %d\r\n",presets_list.names[presets_list.pos],status);
		show_preset(&Preset, presets_list.names[presets_list.pos]);
		break;
	}
	case BUTTON_PAGEDOWN: {
		presets_list.pos++;
		if (presets_list.pos >= presets_list.num)
			presets_list.pos = 0;
		FIO_status status=preset_load(presets_list.names[presets_list.pos], &Preset);
		LOG("Preset %s loaded with status: %d\r\n",presets_list.names[presets_list.pos],status);
		status=curve_load(Preset.CurveFileName, &Preset);
		LOG("Curve %s loaded with status: %d\r\n",Preset.CurveFileName,status);
		show_preset(&Preset, presets_list.names[presets_list.pos]);
		break;
	}
	case BUTTON_ENTER: {
		break;
	}
	case BUTTON_STORAGE: {
		break;
	}
	case BUTTON_EDIT: {
		I_state = state_menu;
		break;
	}
	case BUTTON_PANIC: {
		break;
	}
	case BUTTON_CHANNEL: {
		break;
	}
	case BUTTON_BANK: {
		break;
	}
	case BUTTON_PROGRAM: {

	}
	case ENCODER_LEFT: {
		presets_list.pos--;
		if (presets_list.pos == 0xFFFF)
			presets_list.pos = presets_list.num - 1;
		preset_load(presets_list.names[presets_list.pos], &Preset);
		curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, presets_list.names[presets_list.pos]);
		break;
	}
	case ENCODER_RIGHT: {
		presets_list.pos++;
		if (presets_list.pos >= presets_list.num)
			presets_list.pos = 0;
		preset_load(presets_list.names[presets_list.pos], &Preset);
		curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, presets_list.names[presets_list.pos]);
		break;
	}
	}

}


static void control_buttons_handler(uint8_t event){
	switch (I_state){
	case state_presets:{
		presets_button_handler(event);
		break;
	}
	case state_menu:{
//		presets_button_handler(event);
		break;
	}
	case state_curves:{
//		presets_button_handler(event);
		break;
	}
    }

}

static void midi_buttons_handler(uint8_t event)
{

}


void head_buttons_handler(void){
	uint8_t event;
	if (FIFO_COUNT(control_events) == 0) {
		return; //No events
	}
	event = FIFO_FRONT(control_events);
	LOG("Event0: %d\r\n",event);
	FIFO_POP(control_events);
	if (((event & 0x7F) < 11)||(event>24)){
		LOG("Event1: %d\r\n",event);
		if (!(event & 0x80)){
		   control_buttons_handler(event);
			LOG("Event2: %d\r\n",event);
		}
	} else {
        midi_buttons_handler(event);
	}
}



/*Find position number of file in directory */
int file_list_find(file_list_type *fl, const char *name){
	int len=strlen(name);
	for(int i=0; i< fl->num; i++){
		if (!memcmp(name, fl->names[i], len)) {
			fl->pos=i;
			return i;
		}
	}
	return -1;
}

void interface_init(const presetType *pr, char * name) {
	I_state = state_presets;
    show_preset(pr, name);
    file_list_find(&presets_list, name);
}
