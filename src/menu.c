#include <string.h>
#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "menu.h"
#include "midi.h"
#include "sd_fatfs.h"
#include "log.h"

extern FIFO8(128) control_events; //defined in "control.c"

menuItem_type Null_Menu = { (void*) 0, (void*) 0, (void*) 0, (void*) 0, 0, { 0x00 } };

menuItem_type* selectedMenuItem; // current menu item

static i_state_t I_state;
static yes_no_object_t Yes_No_object;
static text_edit_object_t Text_Edit_object;

extern file_list_type presets_list, calibrations_list, curves_list;
extern presetType Preset;
extern currentStateType Current_state;

void menuChange(menuItem_type* NewMenu) {
	if ((void*) NewMenu == (void*) &NULL_ENTRY)
		return;

	selectedMenuItem = NewMenu;
}


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

static char rotate_char(const char ch, int8_t direction, uint8_t space_enable){
	char c=ch;
	if (direction>0) {
		switch (c){
		case ' ': return '0';
		case '9': return 'A';
		case 'Z': return 'a';
		case 'z': {
			if (space_enable)
				return ' ';
			else
				return '0';
		}
		default: return ++c;
		}
	}else{
		switch (c){
		case ' ': return 'z';
		case 'A': return '9';
		case 'a': return 'Z';
		case '0': {
			if (space_enable)
				return ' ';
			else
				return 'z';
		}
		default: return --c;
		}
	}
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

static void text_object_draw(text_edit_object_t *obj){
	if (!obj->state) {
		hd44780_clear();
		hd44780_message_center(obj->name, 1);
		hd44780_goto(2,1);
		hd44780_write_string(obj->text);
		hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_ON, HD44780_DISP_BLINK_OFF);
		hd44780_goto(2,obj->pos+1);
	}
}

static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent) {
	int len=strlen(st2)-4;
	strcpy(obj->name, st1);
	memset(obj->text,' ', 16);
	memcpy(obj->text, st2, len);
	obj->text[16]=0;
	obj->pos = 0;
	obj->state = 0;
	obj->parent=parent;
	text_object_draw(obj);
}



static void text_object_edit(uint8_t button, text_edit_object_t *obj){
	uint8_t pos;
	switch (button) {
	case BUTTON_PAGEUP: {
		(obj->pos)++;
		if (obj->pos>15) obj->pos=0;
		hd44780_goto(2, obj->pos+1);
		break;
	}
	case BUTTON_PAGEDOWN: {
		(obj->pos)--;
		if (obj->pos==0xFF) obj->pos=15;
		hd44780_goto(2, obj->pos+1);
		break;
	}
	case ENCODER_LEFT: {
		pos=obj->pos;
		obj->text[pos]=rotate_char(obj->text[pos],-1,pos);
		hd44780_write_char(obj->text[pos]);
		hd44780_goto(2, pos+1);
		break;
	}
	case ENCODER_RIGHT: {
		pos=obj->pos;
		obj->text[pos]=rotate_char(obj->text[pos],1,pos);
		hd44780_write_char(obj->text[pos]);
		hd44780_goto(2, pos+1);
		break;
	}
	case BUTTON_ENTER: {
		if (obj->pos==YES_POS){
			strcpy(Current_state.preset_name, presets_list.names[presets_list.pos]);
			presets_list.active=presets_list.pos;
			currentState_save();
		}
		I_state=obj->parent;
		FIFO_PUSH(control_events, MES_REDRAW);
		break;
	}
	default: {
	    break;
	}
	}

}

static void yes_no_draw(yes_no_object_t *obj) {
	if (!obj->state) {
		hd44780_clear();
		hd44780_message_center(obj->text, 1);
		hd44780_goto(2,1);
		hd44780_write_string("    Yes   No    ");
        hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_ON, HD44780_DISP_BLINK_OFF);
	}
	if (obj->pos==YES_POS) {
		hd44780_goto(2,YES_POS);
	} else {
		hd44780_goto(2,NO_POS);
	}

}


static void yes_no_init(yes_no_object_t *obj, const char *mes, uint8_t pos, i_state_t parent){
    I_state=STATE_yes_no;
    obj->pos=pos;
    obj->state=0;
    obj->parent=parent;
    strcpy(obj->text, mes);
    yes_no_draw(obj);
    obj->state=1;
}




static void yes_no_work(uint8_t button, yes_no_object_t *obj){
	switch (button) {
	case BUTTON_PAGEUP: {
	}
	case BUTTON_PAGEDOWN: {
	}
	case ENCODER_LEFT: {
	}
	case ENCODER_RIGHT: {
		obj->pos = (obj->pos == YES_POS) ? NO_POS : YES_POS;
		yes_no_draw(obj);
		break;
	}
	case BUTTON_ENTER: {
		if (obj->pos==YES_POS){
			strcpy(Current_state.preset_name, presets_list.names[presets_list.pos]);
			presets_list.active=presets_list.pos;
			currentState_save();
		}
		I_state=obj->parent;
		FIFO_PUSH(control_events, MES_REDRAW);
		break;
	}
	default: {
	    break;
	}
	}
}



static void show_preset (const presetType *pr, file_list_type *pr_list){
	char line[17];
    hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	memset(line,' ',16);
	line[16]=0;
	int len = strlen(pr_list->names[pr_list->pos]);
	memcpy(line,pr_list->names[pr_list->pos], len-4);
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
	if (pr_list->pos==pr_list->active){
		hd44780_goto(2,16);
		hd44780_write_char('*');
	}
}


static void presets_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:{
		show_preset(&Preset, &presets_list);
		break;
	}
	case ENCODER_LEFT: {
	}
	case BUTTON_PAGEUP: {
		presets_list.pos--;
		if (presets_list.pos == 0xFFFF)
			presets_list.pos = presets_list.num - 1;
		FIO_status status=preset_load(presets_list.names[presets_list.pos], &Preset);
		status=curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, &presets_list);
		break;
	}
	case ENCODER_RIGHT: {
	}
	case BUTTON_PAGEDOWN: {
		presets_list.pos++;
		if (presets_list.pos >= presets_list.num)
			presets_list.pos = 0;
		FIO_status status=preset_load(presets_list.names[presets_list.pos], &Preset);
		status=curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, &presets_list);
		break;
	}
	case BUTTON_STORAGE: {
		yes_no_init(&Yes_No_object,"Set active?",YES_POS, I_state);
		break;
	}
	case BUTTON_ENTER: {
		I_state = STATE_text_edit;
		text_object_init(&Text_Edit_object, "Change name:", presets_list.names[presets_list.pos], STATE_presets_list);
		break;
	}
	case BUTTON_EDIT: {

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
        break;
	}
	}

}


static void control_buttons_handler(uint8_t event) {
	if (event == BUTTON_PANIC) {
		sendControlChange(120, 0, Preset.MidiChannel);
		if (Preset.MidiChannel != Preset.SplitChannel) {
			sendControlChange(120, 0, Preset.SplitChannel);
		}
	}
	switch (I_state) {
	case STATE_presets_list: {
		presets_button_handler(event);
		break;
	}
	case STATE_menu: {
		break;
	}
	case STATE_curve_edit: {
		break;
	}
	case STATE_yes_no: {
		yes_no_work(event, &Yes_No_object);
		break;
	}
	case STATE_text_edit: {
		text_object_edit(event, &Text_Edit_object);
		break;
	}
	default:
		break;
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

void interface_init(const presetType *pr, char *name) {
	I_state = STATE_presets_list;
    file_list_find(&presets_list, name);
    presets_list.active=presets_list.pos;
    show_preset(pr, &presets_list);
}
