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
extern uint16_t slider_calibrate_store;
extern const char slider_names[][MAX_ATTR_SIZE];//defined in "control.c"
extern uint8_t slider_calibrate_number;

menuItem_type Null_Menu = { (void*) 0, (void*) 0, (void*) 0, (void*) 0, 0, 0,(void*)0, {0x00}, { 0x00 } };

menuItem_type* selectedMenuItem; // current menu item

static i_state_t I_state;
static text_edit_object_t Text_Edit_object;

extern file_list_type presets_list, calibrations_list, curves_list;
extern presetType Preset;
extern currentStateType Current_state;
extern sliders_state_t sliders_state;
extern calibrationType Calibration;

uint8_t menuChange(menuItem_type* NewMenu) {
	if ((void*) NewMenu == (void*) &NULL_ENTRY)
		return 0;
	selectedMenuItem = NewMenu;
	return 1;
}

static void menu_preset_copy(void);
static void menu_preset_copy_yes(void);
static void menu_preset_delete_yes(void);
static void menu_preset_rename(void);
static void menu_preset_rename_yes(void);
static void menu_back_to_preset(void);
static void preset_name_current_state(void); //save new active preset
static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent,  void (*com)(void));
static void menu_edit_calibration(void);
static void calibration_name_current_state(void); //save new active preset
static void menu_calibration_copy(void);
static void menu_calibration_copy_yes(void);
static void menu_calibration_save_yes(void);
static void menu_calibration_delete_yes(void);
static void menu_calibration_rename(void);
static void menu_calibration_rename_yes(void);
static void menu_back_to_calibration(void);//Return to calibrations list
static void calibration_list_start(void);

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

static void string_cut_spaces(char * st) {
	size_t len;
	for (len = strlen(st) - 1; len >= 0; len--) {
		if (st[len] != ' ')
			break;
	}
	st[len + 1] = 0;
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



//                     NEXT,        PREVIOUS       PARENT,      CHILD,      POS,   VERTICAL, COMMAND_ENTER,         COMMAND_EDIT
MAKE_MENU(menu0_item1, menu0_item2, NULL_ENTRY,  NULL_ENTRY, menu_preset1,   0,    1,         NULL,                menu_back_to_preset,  "","Edit preset");
MAKE_MENU(menu0_item2, menu0_item3, menu0_item1, NULL_ENTRY, NULL_ENTRY,     0,    1,         menu_preset_copy,    menu_back_to_preset,  "","Copy preset");
MAKE_MENU(menu0_item3, menu0_item4, menu0_item2, NULL_ENTRY, NULL_ENTRY,     0,    1,         menu_preset_rename,  menu_back_to_preset,  "","Rename preset");
MAKE_MENU(menu0_item4, NULL_ENTRY,  menu0_item3, NULL_ENTRY, menuYN3_item2,  1,    1,         NULL,                menu_back_to_preset,  "","Delete preset");




//                     NEXT,        PREVIOUS      PARENT,       CHILD,   POS, VERTICAL,  COMMAND_ENTER,            COMMAND_EDIT
MAKE_MENU(menu1_item1, menu1_item2, NULL_ENTRY,  NULL_ENTRY, NULL_ENTRY, 0,   1,          NULL,                     menu_back_to_preset,    "","Curves");
MAKE_MENU(menu1_item2, NULL_ENTRY,  menu1_item1, NULL_ENTRY, menu2_item1, 0,   1,         calibration_list_start,   menu_back_to_preset,    "","Calibration");


MAKE_MENU(menu2_item1, menu2_item2,  NULL_ENTRY,  NULL_ENTRY, NULL_ENTRY,    0,   1,         menu_edit_calibration,   menu_back_to_calibration,    "","Calibrate");
MAKE_MENU(menu2_item2, menu2_item3,  menu2_item1, NULL_ENTRY, menuYN9_item1, 0,   1,         NULL,                    menu_back_to_calibration,    "","Save");
MAKE_MENU(menu2_item3, menu2_item4,  menu2_item2, NULL_ENTRY, NULL_ENTRY,    0,   1,         menu_calibration_copy,   menu_back_to_calibration,    "","Copy");
MAKE_MENU(menu2_item4, menu2_item5,  menu2_item3, NULL_ENTRY, NULL_ENTRY,    0,   1,         menu_calibration_rename, menu_back_to_calibration,    "","Rename");
MAKE_MENU(menu2_item5, NULL_ENTRY,   menu2_item4, NULL_ENTRY, menuYN7_item2, 0,   1,         NULL,                    menu_back_to_calibration,    "","Delete");


//                       NEXT,        PREVIOUS     PARENT,      CHILD,       POS,VERTICAL,COMMAND_ENTER,                   COMMAND_EDIT
MAKE_MENU(menuYN1_item1, menuYN1_item2, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY,  0,  0,       preset_name_current_state,         NULL,          "Set active?","Yes");
MAKE_MENU(menuYN1_item2, NULL_ENTRY, menuYN1_item1, NULL_ENTRY, NULL_ENTRY,  0,  0,       menu_back_to_preset,               NULL,          "Set active?","No");

MAKE_MENU(menuYN2_item1, menuYN2_item2, NULL_ENTRY, NULL_ENTRY, menu0_item3, 0,  0,       menu_preset_rename_yes,            NULL,          "Save preset?","Yes");
MAKE_MENU(menuYN2_item2, NULL_ENTRY, menuYN2_item1, NULL_ENTRY, menu0_item3, 0,  0,       NULL,                              NULL,          "Save preset?","No");

MAKE_MENU(menuYN3_item1, menuYN3_item2, NULL_ENTRY, NULL_ENTRY, menu0_item4, 0,  0,       menu_preset_delete_yes,            NULL,          "Delete preset?","Yes");
MAKE_MENU(menuYN3_item2, NULL_ENTRY, menuYN3_item1, NULL_ENTRY, menu0_item4, 1,  0,       NULL,                              NULL,          "Delete preset?","No");

MAKE_MENU(menuYN4_item1, menuYN4_item2, NULL_ENTRY, NULL_ENTRY, menu0_item2, 0,  0,       menu_preset_copy_yes,              NULL,          "Copy preset?","Yes");
MAKE_MENU(menuYN4_item2, NULL_ENTRY, menuYN4_item1, NULL_ENTRY, menu0_item2, 0,  0,       NULL,                              NULL,          "Copy preset?","No");

MAKE_MENU(menuYN5_item1, menuYN5_item2, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY,  0,  0,       calibration_name_current_state,    NULL,          "Set active?","Yes");
MAKE_MENU(menuYN5_item2, NULL_ENTRY, menuYN5_item1, NULL_ENTRY, NULL_ENTRY,  0,  0,       NULL,                              NULL,          "Set active?","No");

MAKE_MENU(menuYN6_item1, menuYN6_item2, NULL_ENTRY, NULL_ENTRY, menu2_item4, 0,  0,       menu_calibration_rename_yes,       NULL,          "Save?","Yes");
MAKE_MENU(menuYN6_item2, NULL_ENTRY, menuYN6_item1, NULL_ENTRY, menu2_item4, 0,  0,       NULL,                              NULL,          "Save?","No");

MAKE_MENU(menuYN7_item1, menuYN7_item2, NULL_ENTRY, NULL_ENTRY, menu2_item5, 0,  0,       menu_calibration_delete_yes,       NULL,          "Delete?","Yes");
MAKE_MENU(menuYN7_item2, NULL_ENTRY, menuYN7_item1, NULL_ENTRY, menu2_item5, 1,  0,       NULL,                              NULL,          "Delete?","No");

MAKE_MENU(menuYN8_item1, menuYN8_item2, NULL_ENTRY, NULL_ENTRY, menu2_item3, 0,  0,       menu_calibration_copy_yes,         NULL,          "Copy?","Yes");
MAKE_MENU(menuYN8_item2, NULL_ENTRY, menuYN8_item1, NULL_ENTRY, menu2_item3, 0,  0,       NULL,                              NULL,          "Copy?","No");

MAKE_MENU(menuYN9_item1, menuYN9_item2, NULL_ENTRY, NULL_ENTRY, menu2_item2, 0,  0,       menu_calibration_save_yes,         NULL,          "Save?","Yes");
MAKE_MENU(menuYN9_item2, NULL_ENTRY, menuYN9_item1, NULL_ENTRY, menu2_item2, 1,  0,       NULL,                              NULL,          "Save?","No");


//                      NEXT,          PREVIOUS      PARENT,       CHILD,   POS, VERTICAL,  COMMAND_ENTER,          COMMAND_EDIT
MAKE_MENU(menu_preset1, menu_preset2, NULL_ENTRY,    menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","  Channel: ");
MAKE_MENU(menu_preset2, menu_preset3, menu_preset1,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Split Key: ");
MAKE_MENU(menu_preset3, menu_preset4, menu_preset2,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Split Chl: ");
MAKE_MENU(menu_preset4, menu_preset5, menu_preset3,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        ""," High Res: ");
MAKE_MENU(menu_preset5, menu_preset6, menu_preset4,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","Midi Port: ");
MAKE_MENU(menu_preset6, menu_preset7, menu_preset5,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","    Curve  ");
MAKE_MENU(menu_preset7, menu_preset8, menu_preset6,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","  Sliders ");
MAKE_MENU(menu_preset8, NULL_ENTRY  , menu_preset7,  menu0_item1, NULL_ENTRY, 0,   1,         NULL,                   NULL,        "","  Buttons ");




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
	if ((presets_list.pos) == (presets_list.active)){
		menu0_item3.Next=&NULL_ENTRY;
	}else{
		menu0_item3.Next=&menu0_item4;
	}
	selectedMenuItem = (menuItem_type*) &menu0_item1;
	showMenu();
}


static void startMenuYN_preset_active(void) {
	selectedMenuItem = (menuItem_type*) &menuYN1_item1;
	showMenu();
}



static void startMenuYN_preset_rename(void) {
	selectedMenuItem = (menuItem_type*) &menuYN2_item1;
	showMenu();
}

static void startMenuYN_preset_copy(void) {
	selectedMenuItem = (menuItem_type*) &menuYN4_item1;
	showMenu();
}




static void startMenu_setting(void) {
	selectedMenuItem = (menuItem_type*) &menu1_item1;

	showMenu();
}




static void startMenuYN_calibration_rename(void) {
	selectedMenuItem = (menuItem_type*) &menuYN6_item1;
	showMenu();
}

static void startMenuYN_calibration_copy(void) {
	selectedMenuItem = (menuItem_type*) &menuYN8_item1;
	showMenu();
}

static void startMenuYN_calibration_active(void) {
	selectedMenuItem = (menuItem_type*) &menuYN5_item1;
	showMenu();
}



static void menu_preset_rename(void){
	char name[17];
	strcpy(name,presets_list.names[presets_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name
	I_state = STATE_text_edit;
	text_object_init(&Text_Edit_object, "Rename preset:", name, STATE_presets_list, startMenuYN_preset_rename);
}

static void menu_preset_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	preset_rename(&presets_list, Text_Edit_object.text);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void menu_preset_copy(void){
	char name[17];
	strcpy(name,presets_list.names[presets_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name
	I_state = STATE_text_edit;
	text_object_init(&Text_Edit_object, "Copy preset:", name, STATE_presets_list, startMenuYN_preset_copy);
}

static void menu_preset_copy_yes(void){
	char path[64]= "0:/" PRESET_DIR_NAME "/";
	char file_name[21];
	char old_active_preset_name [21];
	strcpy(old_active_preset_name, presets_list.names[presets_list.active]);
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, PRESET_EXT);
    strcat(path, file_name);
	preset_save(path, &Preset);
	SDFS_scandir("0:/" PRESET_DIR_NAME, &presets_list);
	file_list_find(&presets_list, old_active_preset_name);
	presets_list.active=presets_list.pos;
	file_list_find(&presets_list, file_name);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void menu_preset_delete_yes(void){
	char old_active_preset_name [21];
	strcpy(old_active_preset_name, presets_list.names[presets_list.active]);
	preset_delete(&presets_list);
	SDFS_scandir("0:/" PRESET_DIR_NAME, &presets_list);
	file_list_find(&presets_list, old_active_preset_name);
	presets_list.active=presets_list.pos;
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}




static void calibration_message_draw(const char *line1, const char *line2){
	hd44780_clear();
	hd44780_message_center(line1, 1);
	hd44780_message_center(line2, 2);
}


static void menu_edit_calibration(void){
	calibration_message_draw("Move control","to calibrate");
	I_state = STATE_calibration_start;
	sliders_state = SLIDERS_SEARCH;
}


static void menu_calibration_rename(void){
	char name[17];
	strcpy(name,calibrations_list.names[calibrations_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name
	I_state = STATE_text_edit;
	text_object_init(&Text_Edit_object, "Rename calibr.:", name, STATE_calibrations_list, startMenuYN_calibration_rename);
}

static void menu_calibration_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	calibration_rename(&calibrations_list, Text_Edit_object.text);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}

static void menu_calibration_save_yes(void){
	char path[64] = "0:/" CALIBR_DIR_NAME "/";
	strcat(path, calibrations_list.names[calibrations_list.pos]);
	calibration_save(path, &Calibration);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void menu_calibration_copy(void){
	char name[17];
	strcpy(name,calibrations_list.names[calibrations_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name
	I_state = STATE_text_edit;
	text_object_init(&Text_Edit_object, "Copy calibr.:", name, STATE_calibrations_list, startMenuYN_calibration_copy);
}

static void menu_calibration_copy_yes(void){
	char path[64]= "0:/" CALIBR_DIR_NAME "/";
	char file_name[21];
	char old_active_calibration_name [21];
	strcpy(old_active_calibration_name, calibrations_list.names[calibrations_list.active]);
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, CALIBR_EXT);
    strcat(path, file_name);
	calibration_save(path, &Calibration);
	SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list);
	file_list_find(&calibrations_list, old_active_calibration_name);
	calibrations_list.active=calibrations_list.pos;
	file_list_find(&calibrations_list, file_name);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void menu_calibration_delete_yes(void){
	char old_active_calibration_name [21];
	strcpy(old_active_calibration_name, calibrations_list.names[calibrations_list.active]);
	calibration_delete(&calibrations_list);
	SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list);
	file_list_find(&calibrations_list, old_active_calibration_name);
	calibrations_list.active=calibrations_list.pos;
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}


static void startMenu_calibration(void) {
	if ((calibrations_list.pos) == (calibrations_list.active)){
		menu2_item3.Next=&NULL_ENTRY;
	}else{
		menu2_item3.Next=&menu2_item4;
	}
	selectedMenuItem = (menuItem_type*) &menu2_item1;
	showMenu();
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




static void text_object_draw(text_edit_object_t *obj){
	if (!obj->state) {
		hd44780_clear();
		hd44780_message_center(obj->title, 1);
		hd44780_goto(2,1);
		hd44780_write_string(obj->text);
		hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_ON, HD44780_DISP_BLINK_OFF);
		hd44780_goto(2,obj->pos+1);
	}
}

static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent, void (*com)(void)) {
	int len=strlen(st2); //remove file extension
	strcpy(obj->title, st1);
	memset(obj->text,' ', 16);
	memcpy(obj->text, st2, len);
	obj->text[16]=0;
	strcpy(obj->old_text,obj->text); //save initial text string
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
	case BUTTON_STORAGE: {
		if (strcmp(obj->text, obj->old_text)) { //text changed
			hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF,
					HD44780_DISP_BLINK_OFF);
			obj->command();
			I_state = STATE_menu;
			controlLED1on(1);
		}
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
	FIO_status status;
	switch (button) {
	case MES_REDRAW:
		show_preset(&Preset, &presets_list);
		controlLED1on(0);
		break;
	case ENCODER_LEFT:
	case BUTTON_PAGEUP:
		presets_list.pos--;
		if (presets_list.pos == 0xFFFF)
			presets_list.pos = presets_list.num - 1;
		status = preset_load(presets_list.names[presets_list.pos], &Preset);
		status = curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, &presets_list);
		break;
	case ENCODER_RIGHT:
	case BUTTON_PAGEDOWN:
		presets_list.pos++;
		if (presets_list.pos >= presets_list.num)
			presets_list.pos = 0;
		FIO_status status=preset_load(presets_list.names[presets_list.pos], &Preset);
		status=curve_load(Preset.CurveFileName, &Preset);
		show_preset(&Preset, &presets_list);
		break;
	case BUTTON_STORAGE:
		startMenuYN_preset_active();
		I_state=STATE_menu;
		controlLED1on(1);
		break;
	case BUTTON_ENTER:
		startMenu_preset();
		I_state=STATE_menu;
		break;
	case BUTTON_EDIT:
		startMenu_setting();
		I_state=STATE_menu;
		break;
	default:
		break;
	}

}


static void show_calibration (const calibrationType *cal, file_list_type *cal_list){
	char line[17];
    hd44780_clear();
	hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	memset(line,' ',16);
	line[16]=0;
	int len = strlen(cal_list->names[cal_list->pos]);
	memcpy(line,cal_list->names[cal_list->pos], len-4);
	hd44780_goto(1,1);
	hd44780_write_string(line);
	if (cal_list->pos==cal_list->active){
		hd44780_goto(2,1);
		hd44780_write_char('*');
	}
}

static void calibration_name_current_state(void){
	strcpy(Current_state.calibration_name, calibrations_list.names[calibrations_list.pos]);
	calibrations_list.active=calibrations_list.pos;
	currentState_save();
	menu_back_to_calibration();
}


void calibration_init(char *name) {
	file_list_find(&calibrations_list, name);
	calibrations_list.active = calibrations_list.pos;
}


static void calibration_list_start(void) {
	I_state = STATE_calibrations_list;
	show_calibration(&Calibration, &calibrations_list);
}


static uint16_t slider_edge1, slider_edge2;

static void start_calibration_handler(uint8_t event){
	switch (event) {
	case MES_SLIDER_SHOW:
		LOG("start_calibration_handler, MES_SLIDER_SHOW: %d\r\n",event);
		calibration_message_draw(slider_names[slider_calibrate_number], "Set Min & Ent");
		break;
	case MES_SLIDER_EDGE:
		LOG("start_calibration_handler, MES_SLIDER_EDGE: %d\r\n",event);
		slider_edge1 = slider_calibrate_store; //save first age;
		I_state = STATE_calibration_continue;
		send_message(MES_SLIDER_SHOW);
		break;
	case BUTTON_ENTER:
		if (sliders_state == SLIDERS_FOUND)
     		sliders_state = SLIDERS_CALIBRATE;
		break;
	case BUTTON_EDIT:
		sliders_state = SLIDERS_WORK;
		I_state = STATE_menu;
		send_message(MES_REDRAW);
		break;
	default:
		break;
	}
}


static void continue_calibration_handler(uint8_t event){
	switch (event){
	case MES_SLIDER_SHOW:
		calibration_message_draw(slider_names[slider_calibrate_number],"Set Max & Ent");
		break;
	case MES_SLIDER_EDGE:
		slider_edge2 = slider_calibrate_store; //save first age;
		if (slider_edge1<slider_edge2){
			Calibration.calibr[slider_calibrate_number].min_in_value=slider_edge1;
			Calibration.calibr[slider_calibrate_number].max_in_value=slider_edge2;
		}else{
			Calibration.calibr[slider_calibrate_number].min_in_value=slider_edge2;
			Calibration.calibr[slider_calibrate_number].max_in_value=slider_edge1;
		}
		LOG("Min value: %d, max value: %d \n\r,", Calibration.calibr[slider_calibrate_number].min_in_value, Calibration.calibr[slider_calibrate_number].max_in_value);
		slider_init_struct(&Preset.sliders[slider_calibrate_number], &Calibration.calibr[slider_calibrate_number]); //Recalculate slider constants
		sliders_state = SLIDERS_WORK;
		I_state = STATE_menu;
		send_message(MES_REDRAW);
		break;
	case BUTTON_EDIT:
		sliders_state = SLIDERS_WORK;
		I_state=STATE_menu;
		send_message(MES_REDRAW);
		break;
	case BUTTON_ENTER:
		if (sliders_state == SLIDERS_EDGE)
     		sliders_state = SLIDERS_CALIBRATE;
		break;
	default:
		break;
	}
}


static void calibrations_button_handler(uint8_t button){
	FIO_status status;
	switch (button) {
	case MES_REDRAW:
		show_calibration(&Calibration, &calibrations_list);
		controlLED1on(0);
		break;
	case ENCODER_LEFT:
	case BUTTON_PAGEUP:
		calibrations_list.pos--;
		if (calibrations_list.pos == 0xFFFF)
			calibrations_list.pos = calibrations_list.num - 1;
		Calibration.calibr[0].min_in_value=99;
		status = calibration_load(calibrations_list.names[calibrations_list.pos], &Calibration);
		show_calibration(&Calibration, &calibrations_list);
		calculate_sliders_constants(Preset.sliders, Calibration.calibr);
		LOG("Status: %d\n\r",status);
		for (int i=0; i<24; i++)
			LOG("%s, %s, Min: %d, Max: %d\r\n", calibrations_list.names[calibrations_list.pos], slider_names[i], Calibration.calibr[i].min_in_value, Calibration.calibr[i].max_in_value);
		break;
	case ENCODER_RIGHT:
	case BUTTON_PAGEDOWN:
		calibrations_list.pos++;
		if (calibrations_list.pos >= calibrations_list.num)
			calibrations_list.pos = 0;
		status=calibration_load(calibrations_list.names[calibrations_list.pos], &Calibration);
		show_calibration(&Calibration, &calibrations_list);
		calculate_sliders_constants(Preset.sliders, Calibration.calibr);
		LOG("Status: %d\n\r",status);
		for (int i=0; i<24; i++)
	    	LOG("%s, %s, Min: %d, Max: %d\r\n", calibrations_list.names[calibrations_list.pos], slider_names[i], Calibration.calibr[i].min_in_value, Calibration.calibr[i].max_in_value);
		break;
	case BUTTON_STORAGE:
		startMenuYN_calibration_active();
		I_state=STATE_menu;
		controlLED1on(1);
		break;
	case BUTTON_ENTER:
		startMenu_calibration();
		I_state=STATE_menu;
		break;
	case BUTTON_EDIT:
		startMenu_setting();
		I_state=STATE_menu;
		break;
	default:
		break;
	}

}



/*this function is calling if any setup button pressed, according to
 * the interface status it calls button_handlers
 */

static void control_buttons_handler(uint8_t event) {
	if (event == BUTTON_PANIC) {
		sendControlChange(120, 0, Preset.MidiChannel);
		if (Preset.MidiChannel != Preset.SplitChannel) {
			sendControlChange(120, 0, Preset.SplitChannel);
		}
	}
	switch (I_state) {
	case STATE_presets_list:
		presets_button_handler(event);
		break;
	case STATE_menu:
		menu_button_handler(event);
		break;
	case STATE_curve_edit:
		break;
	case STATE_text_edit:
		text_object_edit(event, &Text_Edit_object);
		break;
	case STATE_calibrations_list:
		calibrations_button_handler(event);
		break;
	case STATE_calibration_start:
		LOG("control_buttons_handler, STATE_calibration_start, event: %d\r\n",event);
		start_calibration_handler(event);
		break;
	case STATE_calibration_continue:
		LOG("control_buttons_handler, STATE_calibration_continue, event: %d\r\n",event);
		continue_calibration_handler(event);
		break;
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
	FIFO_POP(control_events);
	if (((event & 0x7F) < 11)||(event>24)){
		if (!(event & 0x80)){
		   control_buttons_handler(event);
			LOG("Event: %d\r\n",event);
		}
	} else {
        midi_buttons_handler(event);
	}
}




static void menu_back_to_preset(void){
	I_state = STATE_presets_list;
    show_preset(&Preset, &presets_list);
}

static void menu_back_to_calibration(void){
    I_state = STATE_calibrations_list;
    show_calibration(&Calibration, &calibrations_list);
}

void interface_init(char *name) {
	I_state = STATE_presets_list;
	file_list_find(&presets_list, name);
	presets_list.active = presets_list.pos;
	show_preset(&Preset, &presets_list);
}
