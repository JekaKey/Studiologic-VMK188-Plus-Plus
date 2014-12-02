#include <string.h>
#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "menu.h"
#include "midi.h"
#include "sd_fatfs.h"
#include "log.h"
#include "leds.h"

extern FIFO8(128) control_events; //defined in "control.c"

menuItem_type Null_Menu = { (void*) 0, (void*) 0, (void*) 0, (void*) 0, 0, 0,(void*)0, {0x00}, { 0x00 } };

menuItem_type* selectedMenuItem; // current menu item

static i_state_t I_state;
static text_edit_object_t Text_Edit_object;

extern file_list_type presets_list, calibrations_list, curves_list;
extern presetType Preset;
extern currentStateType Current_state;

uint8_t menuChange(menuItem_type* NewMenu) {
	if ((void*) NewMenu == (void*) &NULL_ENTRY)
		return 0;
	selectedMenuItem = NewMenu;
	return 1;
}

static void menu_preset_copy(void);
static void menu_preset_delete(void);
static void menu_preset_rename(void);
static void menu_preset_rename_yes(void);
static void menu_back_to_preset(void);
static void preset_name_current_state(void); //save new active preset
static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent,  void (*com)(void));

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

static void send_message(uint8_t mes){
	FIFO_PUSH(control_events, mes);
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

static string_cut_spaces(char * st) {
	size_t len;
	for (len = strlen(st) - 1; len >= 0; len--) {
		if (st[len] != ' ')
			break;
	}
	st[len + 1] = 0;
}


//                     NEXT,        PREVIOUS       PARENT,      CHILD,  POS,   VERTICAL, COMMAND_ENTER,         COMMAND_EDIT
MAKE_MENU(menu0_item1, menu0_item2, NULL_ENTRY,  NULL_ENTRY, NULL_ENTRY, 0,    1,         NULL,                menu_back_to_preset,  "","Edit preset");
MAKE_MENU(menu0_item2, menu0_item3, menu0_item1, NULL_ENTRY, NULL_ENTRY, 0,    1,         NULL,                menu_back_to_preset,  "","Copy preset");
MAKE_MENU(menu0_item3, menu0_item4, menu0_item2, NULL_ENTRY, NULL_ENTRY, 0,    1,         &menu_preset_rename, menu_back_to_preset,  "","Rename preset");
MAKE_MENU(menu0_item4, NULL_ENTRY,  menu0_item3, NULL_ENTRY, NULL_ENTRY, 0,    1,         NULL,                menu_back_to_preset,  "","Delete preset");



//                     NEXT,        PREVIOUS      PARENT,       CHILD,   POS, VERTICAL,  COMMAND_ENTER,          COMMAND_EDIT
MAKE_MENU(menu1_item1, menu1_item2, NULL_ENTRY,  NULL_ENTRY, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Sliders");
MAKE_MENU(menu1_item2, menu1_item3, menu1_item1, NULL_ENTRY, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Buttons");
MAKE_MENU(menu1_item3, menu1_item4, menu1_item2, NULL_ENTRY, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Setting");
MAKE_MENU(menu1_item4, menu1_item5, menu1_item3, NULL_ENTRY, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Curves");
MAKE_MENU(menu1_item5, NULL_ENTRY,  menu1_item4, NULL_ENTRY, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Calibration");


//                       NEXT,        PREVIOUS     PARENT,      CHILD,       POS,VERTICAL,COMMAND_ENTER,              COMMAND_EDIT
MAKE_MENU(menuYN1_item1, menuYN1_item2, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY,  0,  0,       preset_name_current_state,  NULL,          "Set active?","Yes");
MAKE_MENU(menuYN1_item2, NULL_ENTRY, menuYN1_item1, NULL_ENTRY, NULL_ENTRY,  0,  0,       menu_back_to_preset,        NULL,          "Set active?","No");

MAKE_MENU(menuYN2_item1, menuYN2_item2, NULL_ENTRY, NULL_ENTRY, menu0_item3, 0,  0,       menu_preset_rename_yes,     NULL,          "Save?","Yes");
MAKE_MENU(menuYN2_item2, NULL_ENTRY, menuYN2_item1, NULL_ENTRY, menu0_item3, 0,  0,       NULL,                       NULL,          "Save?","No");


static void showMenu() {
	hd44780_clear();
	if (MENU_VERTICAL) {
		if (MENU_POS) {
			hd44780_goto(1, MENU_TEXT_POS);
			hd44780_write_string(MENU_PREVIOUS->Text);
			hd44780_goto(2, MENU_TEXT_POS);
			hd44780_write_string(selectedMenuItem->Text);
			hd44780_goto(2, MENU_CURSOR_POS);
			hd44780_write_char(MENU_CURSOR_CHAR);
		} else {
			hd44780_goto(1, MENU_TEXT_POS);
			hd44780_write_string(selectedMenuItem->Text);
			hd44780_goto(2, MENU_TEXT_POS);
			hd44780_write_string(MENU_NEXT->Text);
			hd44780_goto(1, MENU_CURSOR_POS);
			hd44780_write_char(MENU_CURSOR_CHAR);
		}
	} else {
		hd44780_message_center(selectedMenuItem->Title, 1);
		if (MENU_POS) {
			hd44780_goto(2,MENU_YES_POS);
			hd44780_write_string(MENU_PREVIOUS->Text);
			hd44780_goto(2, MENU_NO_POS);
			hd44780_write_string(selectedMenuItem->Text);
			hd44780_goto(2, MENU_NO_POS-1);
			hd44780_write_char(MENU_CURSOR_CHAR);
		}else {
			hd44780_goto(2,MENU_YES_POS);
			hd44780_write_string(selectedMenuItem->Text);
			hd44780_goto(2, MENU_NO_POS);
			hd44780_write_string(MENU_NEXT->Text);
			hd44780_goto(2, MENU_YES_POS-1);
			hd44780_write_char(MENU_CURSOR_CHAR);
		}
	}
}

static void startMenu_preset(void) {
	selectedMenuItem = (menuItem_type*) &menu0_item1;

	showMenu();
}


static void startMenuYN_preset_active(void) {
	selectedMenuItem = (menuItem_type*) &menuYN1_item1;
	showMenu();
	controlLED1on(0);
}


static void startMenuYN_preset_rename(void) {
	selectedMenuItem = (menuItem_type*) &menuYN2_item1;
	showMenu();
	controlLED1on(0);
}


static void startMenu_setting(void) {
	selectedMenuItem = (menuItem_type*) &menu1_item1;

	showMenu();
}


static void menu_preset_rename(void){
	I_state = STATE_text_edit;
	text_object_init(&Text_Edit_object, "Rename preset:", presets_list.names[presets_list.pos], STATE_presets_list, startMenuYN_preset_rename);
}

static void menu_preset_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	preset_rename(&presets_list, Text_Edit_object.text);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void menu_preset_copy(void){

}

static void menu_preset_delete(void){

}

void menu_button_handler(uint8_t button) {
	switch (button) {
	case MES_REDRAW:{
		showMenu();
		break;
	}
	case ENCODER_LEFT: {

	}
	case BUTTON_PAGEUP: {
		menuChange(MENU_PREVIOUS);
		MENU_POS=0;
		showMenu();
		break;
	}
	case ENCODER_RIGHT: {

	}
	case BUTTON_PAGEDOWN: {
		menuChange(MENU_NEXT);
		MENU_POS=1;
		showMenu();
		break;
	}
	case BUTTON_ENTER: {
		if (selectedMenuItem->Command_Enter){
	        selectedMenuItem->Command_Enter();
            break;
		}else{
			menuChange(MENU_CHILD);
			send_message(MES_REDRAW);
			break;
		}

	}
	case BUTTON_STORAGE: {
		break;
	}
	case BUTTON_EDIT: {
		if (selectedMenuItem->Command_Edit){
	        selectedMenuItem->Command_Edit();
            break;
		}else{
			menuChange(MENU_PARENT);
			send_message(MES_REDRAW);
			break;
		}
	}
	default:
		break;
	}

}


void curves_button_handler(uint8_t button) {
	switch (button) {
		case BUTTON_PAGEUP: {
			menuChange(MENU_PREVIOUS);
			break;
		}
		case BUTTON_PAGEDOWN: {
			menuChange(MENU_NEXT);
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

static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent, void (*com)(void)) {
	int len=strlen(st2)-4;
	strcpy(obj->name, st1);
	memset(obj->text,' ', 16);
	memcpy(obj->text, st2, len);
	obj->text[16]=0;
	obj->pos = 0;
	obj->state = 0;
	obj->parent=parent;
	text_object_draw(obj);
	obj->command=com;
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
		break;
	}
	case BUTTON_STORAGE:{
		hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
		obj->command();
		I_state=STATE_menu;
		controlLED1on(1);
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

static void preset_name_current_state(void){
	strcpy(Current_state.preset_name, presets_list.names[presets_list.pos]);
	presets_list.active=presets_list.pos;
	currentState_save();
	menu_back_to_preset();
}


static void presets_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:{
		show_preset(&Preset, &presets_list);
		controlLED1on(0);
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
		startMenuYN_preset_active();
		I_state=STATE_menu;
		controlLED1on(1);
		break;
	}
	case BUTTON_ENTER: {
		startMenu_preset();
		I_state=STATE_menu;
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
		menu_button_handler(event);
		break;
	}
	case STATE_curve_edit: {
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

static void menu_back_to_preset(void){
	I_state = STATE_presets_list;
    show_preset(&Preset, &presets_list);
}


void interface_init(const presetType *pr, char *name) {
	I_state = STATE_presets_list;
    file_list_find(&presets_list, name);
    presets_list.active=presets_list.pos;
    show_preset(pr, &presets_list);
}
