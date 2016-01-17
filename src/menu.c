#include <string.h>
#include "controls.h"
#include "fifo.h"
#include "hd44780.h"
#include "main.h"
#include "menu.h"
#include "midi.h"
#include "sd_fatfs.h"
#include "log.h"
#include "leds.h"
#include "velocity.h"
#include "keyboardscan.h"
#include "bootloader.h"
#include "usb_init.h"

const xy_t curve_xy[6]={{3,1,2},{7,1,3},{12,1,4},{3,2,2},{7,2,3},{12,2,4}};

extern FIFO8(128) control_events; //defined in "control.c"
extern uint16_t slider_calibrate_store;
extern const char slider_names[][MAX_ATTR_SIZE];//defined in "control.c"
extern uint8_t slider_calibrate_number;
extern uint8_t okIO;//if this flag is zero all I/O operations will be canceled.

extern uint8_t buttonsToMenu;
extern uint8_t keySeek;
extern uint8_t curNoteSeek;

menuItem_type Null_Menu = { (void*)0, (void*)0, (void*)0, (void*)0, 0, (void*)0, 0, 0, 0, (void*)0, (void*)0, {0x00} };

menuItem_type * menus_sliders_ordered [SLIDERS_AMOUNT] = { NULL };
menuItem_type * menus_buttons_ordered [BUTTONS_AMOUNT] = { NULL };

menuItem_type* selectedMenuItem; // current menu item
menuYNItem_type* selectedMenuYNItem;

char temp_msg_1[HD44780_DISP_LENGTH + 1] = {' '};
char temp_msg_2[HD44780_DISP_LENGTH + 1] = {' '};
uint8_t temp_msg_time = TEMP_MSG_INTERVAL;
uint8_t showing_temp_msg = 0;

static i_state_t I_state;
static i_state_t prev_state;

static uint8_t calibrationActive = 0;

static text_edit_object_t Text_Edit_object;
static menu_cursor_object_t Menu_Cursor;

extern file_list_type presets_list, calibrations_list, curves_list;
extern presetType Preset;
extern currentStateType Current_state;
extern sliders_state_t sliders_state;
extern calibrationType Calibration;
extern curve_points_type Curve;

static curve_edit_object_t Curve_Edit_object[6]={{STATE_menu, 0, &Curve, //Initialization of bounds for white and black curves points
		{{NULL, MIN_XW1, MAX_XW1},
		{NULL, MIN_XW2, MAX_XW2},
		{NULL, MIN_XW3, MAX_XW3},
		{NULL, MIN_XB1, MAX_XB1},
		{NULL, MIN_XB2, MAX_XB2},
		{NULL, MIN_XB3, MAX_XB3}}}};


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
static void menu_preset_save_yes(void);
static void menu_back_to_preset(void);
static void preset_name_current_state(void); //save new active preset
static void text_object_init(text_edit_object_t *obj, const char *st1, const char *st2, i_state_t parent,  void (*com)(void));
static void menu_edit_calibration(void);
static void calibration_name_current_state(void); //save new active preset
static void menu_calibration_copy(void);
static void menu_calibration_copy_yes(void);
static void menu_calibration_save_yes(void);
static void menu_calibration_delete_yes(void);
static void menu_curve_load_yes(void);
static void menu_calibration_rename(void);
static void menu_calibration_rename_yes(void);
static void calibrationlist_start(void);

static void menu_edit_curve(void);
static void menu_preset_edit_curve(void);
static void menu_curve_copy(void);
static void menu_curve_copy_yes(void);
static void menu_curve_save_yes(void);
static void menu_curve_delete_yes(void);
static void menu_curve_rename(void);
static void menu_curve_rename_yes(void);
static void menu_curve_export(void);
static void menu_curve_export_yes(void);
static void curvelist_start(void);
static void preset_curvelist_start(void);
static void menu_bootloader_yes(void);
static void menu_USBdisk_on_yes(void);
static void menu_USBdisk_off_yes(void);

static void menu_preset_sl_enter(void);
static void menu_preset_sl_edit(void);
static void menu_slider_enter(void);
static void menu_slider_edit(void);

static void menu_preset_bt_enter(void);
static void menu_button_enter(void);
static void menu_preset_bt_edit(void);
static void menu_button_edit(void);

static void menu_show_param(menuItem_type * menu);

static void menu_preset_as_default(void);


static void startMenuYN_preset_save(void);
static void startMenuYN_preset_delete(void);
static void startMenuYN_curve_save(void);
static void startMenuYN_curve_delete(void);
static void startMenuYN_calibration_save(void);
static void startMenuYN_calibration_delete(void);
static void startMenuYN_bootloader(void);
static void startMenuYN_USBdisk(void);
static void check_saving_preset(void);


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

void uint16toa(uint16_t n, char *s) {
	char c;
	uint16_t i = 0;
	uint16_t j;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	s[i] = '\0';
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void string_number_format(char * s, uint8_t n){
	char sss [10];
	uint8_t l=strlen(s);
	if (n<=l)
	   return;
	strcpy(sss,s);
	memset(s,' ',n-l);
	s[n-l]=0;
	strcat(s,sss);
}

void uint8toa(uint8_t n, char *s) {
	char c;
	uint16_t i = 0;
	uint16_t j;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	s[i] = '\0';
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void int8toa(int8_t n, char *s) {
	char temp[5];

	if (n == 0) {
		strcpy(s, " 0");
	} else if (n > 0) {
		strcpy(s, "+");
		uint8toa((uint8_t) n, temp);
		strcat(s, temp);
	} else {
		strcpy(s, "-");
		uint8toa((uint8_t) -n, temp);
		strcat(s, temp);
	}
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

const char note_names[12][3]={"C","C#","D","D#","E","F","F#","G","G#", "A","A#","B"};

static int note_name (uint8_t note_num, char *name) {
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



//							NEXT				PREVIOUS			PARENT			CHILD			POS		Value	t_Value		Min		Max		COMMAND_ENTER						COMMAND_EDIT			TEXT

MAKE_MENU(menu_stor_def,	menu_stor_save,		NULL_ENTRY,			NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_preset_as_default,				menu_back_to_preset,	"Pst as default");
MAKE_MENU(menu_stor_save,	menu_stor_copy,		menu_stor_def,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		startMenuYN_preset_save,			menu_back_to_preset,	"Save preset"	);
MAKE_MENU(menu_stor_copy,	menu_stor_rename,	menu_stor_save,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_preset_copy,					menu_back_to_preset,	"Copy preset"	);
MAKE_MENU(menu_stor_rename,	menu_stor_del,		menu_stor_copy,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_preset_rename,					menu_back_to_preset,	"Rename preset"	);
MAKE_MENU(menu_stor_del,	NULL_ENTRY,			menu_stor_rename,	NULL_ENTRY,		NULL_ENTRY,		1,		NULL,	t_none,		0,		0,		startMenuYN_preset_delete,			menu_back_to_preset,	"Delete preset"	);

MAKE_MENU(menu1_item1,		menu1_item2,		NULL_ENTRY,			NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		curvelist_start,					menu_back_to_preset,	"Curves"		);
MAKE_MENU(menu1_item2,		menu1_item3,		menu1_item1,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		calibrationlist_start,				menu_back_to_preset,	"Calibration"	);
MAKE_MENU(menu1_item3,		menu1_item4,		menu1_item2,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		startMenuYN_USBdisk,				menu_back_to_preset,	"USB disk"	);
MAKE_MENU(menu1_item4,		NULL_ENTRY,			menu1_item3,		NULL_ENTRY,		NULL_ENTRY,		1,		NULL,	t_none,		0,		0,		startMenuYN_bootloader,				menu_back_to_preset,	"Firmware"	);


MAKE_MENU(menu_clb_edit,	menu_clb_save,		NULL_ENTRY,			NULL_ENTRY,		menu_slider1,	0,		NULL,	t_none,		0,		0,		menu_preset_sl_enter,				calibrationlist_start,	"Edit calibr."	);
MAKE_MENU(menu_clb_save,	menu_clb_copy,		menu_clb_edit,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		startMenuYN_calibration_save,		calibrationlist_start,	"Save calibr."	);
MAKE_MENU(menu_clb_copy,	menu_clb_rename,	menu_clb_save,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_calibration_copy,				calibrationlist_start,	"Copy calibr."	);
MAKE_MENU(menu_clb_rename,	menu_clb_del,		menu_clb_copy,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_calibration_rename,			calibrationlist_start,	"Rename calibr.");
MAKE_MENU(menu_clb_del,		NULL_ENTRY,			menu_clb_rename,	NULL_ENTRY,		NULL_ENTRY,		1,		NULL,	t_none,		0,		0,		startMenuYN_calibration_delete,		calibrationlist_start,	"Delete calibr.");

MAKE_MENU(menu_clb_e_set,	menu_clb_e_delta,	NULL_ENTRY,			NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_edit_calibration,				menu_slider_edit,		"Set min & max"	);
MAKE_MENU(menu_clb_e_delta,	menu_clb_e_gaps,	menu_clb_e_set,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_uint16,	2,		512,	NULL,								menu_slider_edit,		"Delta:"	);
MAKE_MENU(menu_clb_e_gaps,	menu_clb_e_dead,	menu_clb_e_delta,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_perc,		0,		49,		NULL,								menu_slider_edit,		"Gaps:");
MAKE_MENU(menu_clb_e_dead,	NULL_ENTRY,			menu_clb_e_gaps,	NULL_ENTRY,		NULL_ENTRY,		1,		NULL,	t_perc,		0,		99,		NULL,								menu_slider_edit,		"Dead zone:");

MAKE_MENU(menu3_item1,		menu3_item2,		NULL_ENTRY,			NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_edit_curve,					curvelist_start,		"Edit curve"	);
MAKE_MENU(menu3_item2,		menu3_item3,		menu3_item1,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		startMenuYN_curve_save,				curvelist_start,		"Save curve"	);
MAKE_MENU(menu3_item3,		menu3_item4,		menu3_item2,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_curve_copy,					curvelist_start,		"Copy curve"	);
MAKE_MENU(menu3_item4,		menu3_item5,		menu3_item3,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_curve_rename,					curvelist_start,		"Rename curve"	);
MAKE_MENU(menu3_item5,		NULL_ENTRY,			menu3_item4,		NULL_ENTRY,		NULL_ENTRY,		1,		NULL,	t_none,		0,		0,		startMenuYN_curve_delete,			curvelist_start,		"Delete curve"	);

MAKE_MENU(menu4_item1,		menu4_item2,		NULL_ENTRY,			menu_pst_curve,	NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		preset_curvelist_start,				NULL,					"Load curve"	);
MAKE_MENU(menu4_item2,		menu4_item3,		menu4_item1,		menu_pst_curve,	NULL_ENTRY,		0,		NULL,	t_none,		0,		0,		menu_preset_edit_curve,				NULL,					"Edit curve"	);
MAKE_MENU(menu4_item3,		NULL_ENTRY,			menu4_item2,		menu_pst_curve,	NULL_ENTRY,		1,		NULL,	t_none,		0,		0,		menu_curve_export,					NULL,					"Export curve"	);



//							NEXT,			PREVIOUS		PARENT,			CHILD,			POS,	Value,						t_Value,	Min,	Max,	COMMAND_ENTER,			COMMAND_EDIT			

MAKE_MENU(menu_pst_gen,		menu_pst_split,	NULL_ENTRY,		NULL_ENTRY,		menu_pst_chan,	0,		NULL,						t_none,		0,		0,		NULL,					check_saving_preset,	"  General "	);
MAKE_MENU(menu_pst_split,	menu_pst_curve,	menu_pst_gen,	NULL_ENTRY,		menu_split_on,	0,		NULL,						t_none,		0,		0,		NULL,					check_saving_preset,	"  Split   "	);
MAKE_MENU(menu_pst_curve,	menu_pst_slid,	menu_pst_split,	NULL_ENTRY,		menu4_item1, 	0,		NULL,						t_none,		0,		0,		NULL,					check_saving_preset,	"  Curve   "	);
MAKE_MENU(menu_pst_slid,	menu_pst_btns,	menu_pst_curve,	NULL_ENTRY,		menu_slider1,	0,		NULL,						t_none,		0,		0,		menu_preset_sl_enter,	check_saving_preset,	"  Sliders "	);
MAKE_MENU(menu_pst_btns,	NULL_ENTRY,		menu_pst_slid,	NULL_ENTRY,		menu_button1,	1,		NULL,						t_none,		0,		0,		menu_preset_bt_enter,	check_saving_preset,	"  Buttons "	);

MAKE_MENU(menu_pst_chan,	menu_pst_transp,NULL_ENTRY,		menu_pst_gen,	NULL_ENTRY,		0,		&Preset.MidiChannel,		t_uint8,	1,		16,		NULL,					NULL,					"  Channel: "	);
MAKE_MENU(menu_pst_transp,	menu_pst_oct,	menu_pst_chan,	menu_pst_gen,	NULL_ENTRY,		0,		&Preset.Transpose,			t_int8, 	-11,	11,		NULL,					NULL,					"Transpose: "	);
MAKE_MENU(menu_pst_oct,		menu_pst_hires,	menu_pst_transp,menu_pst_gen,	NULL_ENTRY,		0,		&Preset.OctaveShift,		t_int8,	    -3,		3,		NULL,					NULL,					"Oct Shift: "	);
MAKE_MENU(menu_pst_hires,	menu_pst_midi,	menu_pst_oct,	menu_pst_gen,	NULL_ENTRY,		0,		&Preset.HighResEnable,		t_bool,		0,		1,		NULL,					NULL,					" High Res: "	);
MAKE_MENU(menu_pst_midi,	NULL_ENTRY,		menu_pst_hires,	menu_pst_gen,	NULL_ENTRY,		1,		&Preset.AnalogMidiEnable,	t_bool,		0,		1,		NULL,					NULL,					"Midi Port: "	);

MAKE_MENU(menu_split_on,	menu_split_key,	NULL_ENTRY,		menu_pst_split,	NULL_ENTRY,		0,		&Preset.SplitActive,		t_bool,		0,		1,		NULL,					NULL,					"    Split: "	);
MAKE_MENU(menu_split_key,	menu_split_chan,menu_split_on,	menu_pst_split,	NULL_ENTRY,		0,		&Preset.SplitKey,			t_note,		22,		108,	NULL,					NULL,					"Split Key: "	);
MAKE_MENU(menu_split_chan,	menu_split_oct,	menu_split_key,	menu_pst_split,	NULL_ENTRY,		0,		&Preset.SplitChannel,		t_uint8,	1,		16,		NULL,					NULL,					"Split Chl: "	);
MAKE_MENU(menu_split_oct,	NULL_ENTRY,		menu_split_chan,menu_pst_split,	NULL_ENTRY,		1,		&Preset.SplitOctShift,		t_int8,		-3,		3,		NULL,					NULL,					"Split Oct: "	);

/*For sliders menu items "Min" parameter is used for slider number keeping*/
MAKE_MENU(menu_slider1,		menu_slider2,	NULL_ENTRY,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S1,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 1 "	);
MAKE_MENU(menu_slider2,		menu_slider3,	menu_slider1,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S2,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 2 "	);
MAKE_MENU(menu_slider3,		menu_slider4,	menu_slider2,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S3,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 3 "	);
MAKE_MENU(menu_slider4,		menu_slider5,	menu_slider3,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S4,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 4 "	);
MAKE_MENU(menu_slider5,		menu_slider6,	menu_slider4,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S5,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 5 "	);
MAKE_MENU(menu_slider6,		menu_slider7,	menu_slider5,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S6,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 6 "	);
MAKE_MENU(menu_slider7,		menu_slider8,	menu_slider6,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S7,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 7 "	);
MAKE_MENU(menu_slider8,		menu_slider9,	menu_slider7,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S8,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 8 "	);
MAKE_MENU(menu_slider9,		menu_knob1,		menu_slider8,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_S9,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Slider 9 "	);
MAKE_MENU(menu_knob1,		menu_knob2,		menu_slider9,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R1,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 1 "		);
MAKE_MENU(menu_knob2,		menu_knob3,		menu_knob1,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R2,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 2 "		);
MAKE_MENU(menu_knob3,		menu_knob4,		menu_knob2,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R3,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 3 "		);
MAKE_MENU(menu_knob4,		menu_knob5,		menu_knob3,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R4,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 4 "		);
MAKE_MENU(menu_knob5,		menu_knob6,		menu_knob4,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R5,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 5 "		);
MAKE_MENU(menu_knob6,		menu_knob7,		menu_knob5,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R6,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 6 "		);
MAKE_MENU(menu_knob7,		menu_knob8,		menu_knob6,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R7,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 7 "		);
MAKE_MENU(menu_knob8,		menu_pedal1,	menu_knob7,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_R8,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Knob 8 "		);
MAKE_MENU(menu_pedal1,		menu_pedal2,	menu_knob8,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_P1,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Pedal 1 "	);
MAKE_MENU(menu_pedal2,		menu_pedal3,	menu_pedal1,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_P2,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Pedal 2 "	);
MAKE_MENU(menu_pedal3,		menu_pitch,		menu_pedal2,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_P3,		0,		menu_slider_enter,		menu_preset_sl_edit,	"  Pedal 3 "	);
MAKE_MENU(menu_pitch,		menu_mod,		menu_pedal3,	menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_PITCH,	0,		menu_slider_enter,		menu_preset_sl_edit,	"  Pitch "		);
MAKE_MENU(menu_mod,			menu_at,		menu_pitch,		menu_pst_slid,	NULL_ENTRY,		0,		NULL,						t_none,		SLIDER_MOD,		0,		menu_slider_enter,		menu_preset_sl_edit,	"Modulation "	);
MAKE_MENU(menu_at,			NULL_ENTRY,		menu_mod,		menu_pst_slid,	NULL_ENTRY,		1,		NULL,						t_none,		SLIDER_AT,		0,		menu_slider_enter,		menu_preset_sl_edit,	"AfterTouch"	);
/*************************/

/*The following list of menu items can be switched to any slider*/
MAKE_MENU(menu_sl_active,	menu_sl_channel,NULL_ENTRY,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_bool,		0,		1,		NULL,					menu_slider_edit,		"  Active:"		);
MAKE_MENU(menu_sl_channel,	menu_sl_event,	menu_sl_active,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	0,		16,		NULL,					menu_slider_edit,		" Channel:"		);
MAKE_MENU(menu_sl_event,	menu_sl_reverse,menu_sl_channel,NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	0,		127,	NULL,					menu_slider_edit,		"   Event:"		);
MAKE_MENU(menu_sl_reverse,	menu_sl_min,	menu_sl_event,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_bool,		0,		1,		NULL,					menu_slider_edit,		" Reverse:"		);
MAKE_MENU(menu_sl_min,		menu_sl_max,	menu_sl_reverse,NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint16,	0,		127,	NULL,					menu_slider_edit,		"     Min:"		);
MAKE_MENU(menu_sl_max,		menu_sl_bin,	menu_sl_min,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint16,	0,		127,	NULL,					menu_slider_edit,		"     Max:"		);
MAKE_MENU(menu_sl_bin,		NULL_ENTRY,		menu_sl_max,	NULL_ENTRY,		NULL_ENTRY,		1,		NULL,						t_bool,		0,		1,		NULL,					menu_slider_edit,		"  Binary:"		);
/********/



MAKE_MENU(menu_button1,		menu_button2,	NULL_ENTRY,		menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B1,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 1 "	);
MAKE_MENU(menu_button2,		menu_button3,	menu_button1,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B2,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 2 "	);
MAKE_MENU(menu_button3,		menu_button4,	menu_button2,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B3,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 3 "	);
MAKE_MENU(menu_button4,		menu_button5,	menu_button3,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B4,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 4 "	);
MAKE_MENU(menu_button5,		menu_button6,	menu_button4,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B5,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 5 "	);
MAKE_MENU(menu_button6,		menu_button7,	menu_button5,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B6,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 6 "	);
MAKE_MENU(menu_button7,		menu_button8,	menu_button6,	menu_pst_btns,	NULL_ENTRY,		0,		NULL,						t_none,		BUTTON_B7,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 7 "	);
MAKE_MENU(menu_button8,		NULL_ENTRY,		menu_button7,	menu_pst_btns,	NULL_ENTRY,		1,		NULL,						t_none,		BUTTON_B8,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Button 8 "	);
/*
MAKE_MENU(menu_button_l,	menu_button_r,	menu_button8,	menu_preset8,	NULL_ENTRY,		0,		NULL,						t_none,		0,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Left "		);
MAKE_MENU(menu_button_r,	menu_button_rec,menu_button_l,	menu_preset8,	NULL_ENTRY,		0,		NULL,						t_none,		0,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Right "		);
MAKE_MENU(menu_button_rec,	menu_button_p,	menu_button_r,	menu_preset8,	NULL_ENTRY,		0,		NULL,						t_none,		0,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Record "		);
MAKE_MENU(menu_button_p,	menu_button_s,	menu_button_rec,menu_preset8,	NULL_ENTRY,		0,		NULL,						t_none,		0,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Play "		);
MAKE_MENU(menu_button_s,	NULL_ENTRY,		menu_button_p,	menu_preset8,	NULL_ENTRY,		1,		NULL,						t_none,		0,		0,		menu_button_enter,		menu_preset_bt_edit,	"  Stop "		);
*/

MAKE_MENU(menu_bt_active,	menu_bt_type,	NULL_ENTRY,		NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_bool,		0,		1,		NULL,					menu_button_edit,		"   Active:"	);
MAKE_MENU(menu_bt_type,		menu_bt_channel,menu_bt_active,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	0,		2,		NULL,					menu_button_edit,		"     Type:"	);
MAKE_MENU(menu_bt_channel,	menu_bt_event,	menu_bt_type,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	0,		16,		NULL,					menu_button_edit,		"  Channel:"	);
MAKE_MENU(menu_bt_event,	menu_bt_on,		menu_bt_channel,NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	1,		127,	NULL,					menu_button_edit,		"    Event:"	);
MAKE_MENU(menu_bt_on,		menu_bt_off,	menu_bt_event,	NULL_ENTRY,		NULL_ENTRY,		0,		NULL,						t_uint8,	0,		127,	NULL,					menu_button_edit,		" On value:"	);
MAKE_MENU(menu_bt_off,		NULL_ENTRY,		menu_bt_on,		NULL_ENTRY,		NULL_ENTRY,		1,		NULL,						t_uint8,	0,		127,	NULL,					menu_button_edit,		"Off value:"	);



menuItem_type * const  menus_sliders [] = {
		&menu_slider1, &menu_slider2, &menu_slider3, &menu_slider4, &menu_slider5, &menu_slider6, &menu_slider7, &menu_slider8, &menu_slider9,
		&menu_knob1, &menu_knob2, &menu_knob3, &menu_knob4, &menu_knob5, &menu_knob6, &menu_knob7, &menu_knob8,
		&menu_pedal1, &menu_pedal2, &menu_pedal3,
		&menu_pitch, &menu_mod, &menu_at,
		NULL};

menuItem_type * const  menus_buttons [] = {
		&menu_button1, &menu_button2, &menu_button3, &menu_button4, &menu_button5, &menu_button6, &menu_button7, &menu_button8};



MAKE_MENU_YN(menuYN_preset_default, "Set as default?", 	preset_name_current_state, 		1,	menu_stor_def);
MAKE_MENU_YN(menuYN_preset_rename, 	"Rename preset?", 	menu_preset_rename_yes, 		1,	menu_stor_rename);
MAKE_MENU_YN(menuYN_preset_save, 	"Save changes?", 	menu_preset_save_yes, 			1,	NULL_ENTRY);
MAKE_MENU_YN(menuYN_preset_delete, 	"Delete preset?", 	menu_preset_delete_yes, 		1,	menu_stor_del);
MAKE_MENU_YN(menuYN_preset_copy, 	"Copy preset?", 	menu_preset_copy_yes, 			1,	menu_stor_copy);

MAKE_MENU_YN(menuYN_calibr_active, 	"Set active?", 		calibration_name_current_state,	0,	NULL_ENTRY);
MAKE_MENU_YN(menuYN_calibr_rename, 	"Rename calibr.?", 	menu_calibration_rename_yes, 	1,	menu_clb_rename);
MAKE_MENU_YN(menuYN_calibr_save, 	"Save calibr.?", 	menu_calibration_save_yes, 		1,	menu_clb_save);
MAKE_MENU_YN(menuYN_calibr_delete, 	"Delete calibr.?", 	menu_calibration_delete_yes, 	1,	menu_clb_del);
MAKE_MENU_YN(menuYN_calibr_copy, 	"Copy calibr.?", 	menu_calibration_copy_yes, 		1,	menu_clb_copy);

MAKE_MENU_YN(menuYN_curve_rename, 	"Rename curve?", 	menu_curve_rename_yes, 			1,	menu3_item4);
MAKE_MENU_YN(menuYN_curve_save, 	"Save curve?", 		menu_curve_save_yes, 			1,	menu3_item2);
MAKE_MENU_YN(menuYN_curve_delete, 	"Delete curve?", 	menu_curve_delete_yes, 			1,	menu3_item5);
MAKE_MENU_YN(menuYN_curve_copy, 	"Copy curve?", 		menu_curve_copy_yes, 			1,	menu3_item3);
MAKE_MENU_YN(menuYN_curve_load, 	"Load curve?", 		menu_curve_load_yes, 			1,	menu4_item1);
MAKE_MENU_YN(menuYN_curve_export, 	"Export curve?", 	menu_curve_export_yes, 			1,	menu4_item3);
MAKE_MENU_YN(menuYN_USBdisk_on,    	"USB disk On?",		menu_USBdisk_on_yes,   			1,	menu1_item3);
MAKE_MENU_YN(menuYN_USBdisk_off,    "USB disk Off?",	menu_USBdisk_off_yes,  			1,	menu1_item3);
MAKE_MENU_YN(menuYN_bootloader, 	"Run bootloader?",	menu_bootloader_yes, 			1,	menu1_item4);



static void menu_cursor_draw(menu_cursor_object_t* cursor, uint8_t y, uint8_t x){
	if (cursor->on) {
		hd44780_goto(cursor->y, cursor->x);
		hd44780_write_char(' ');
	}
	hd44780_goto(y, x);
	hd44780_write_char(MENU_CURSOR_CHAR);
	cursor->y=y;
	cursor->x=x;
	cursor->on=1;
}

static void showMenu() {
	hd44780_clear();
	Menu_Cursor.on = 0;
	hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);

	if (MENU_POS) {
		hd44780_goto(1, MENU_TEXT_POS);
		hd44780_write_string(MENU_PREVIOUS->Text);
		hd44780_goto(1, MENU_VALUE_POS);
		if (MENU_PREVIOUS->tValue != t_none)
			menu_show_param(MENU_PREVIOUS);

		hd44780_goto(2, MENU_TEXT_POS);
		hd44780_write_string(selectedMenuItem->Text);
		hd44780_goto(2, MENU_VALUE_POS);
		if (selectedMenuItem->tValue != t_none)
			menu_show_param(selectedMenuItem);

		menu_cursor_draw(&Menu_Cursor, 2, MENU_CURSOR_POS);

	} else {
		hd44780_goto(1, MENU_TEXT_POS);
		hd44780_write_string(selectedMenuItem->Text);
		hd44780_goto(1, MENU_VALUE_POS);

		if (selectedMenuItem->tValue != t_none)
			menu_show_param(selectedMenuItem);
		hd44780_goto(2, MENU_TEXT_POS);
		hd44780_write_string(MENU_NEXT->Text);
		hd44780_goto(2, MENU_VALUE_POS);

		if (MENU_NEXT->tValue != t_none)
			menu_show_param(MENU_NEXT);

		menu_cursor_draw(&Menu_Cursor, 1, MENU_CURSOR_POS);
	}

	if (selectedMenuItem->tValue == t_note)
		keySeek = 1;
	else
		keySeek = 0;
}

void changeSplitKey(uint8_t note) {
	if (selectedMenuItem->tValue != t_note || Preset.SplitKey == note)
		return;

	Preset.SplitKey = note;

	hd44780_goto(MENU_POS + 1, MENU_VALUE_POS);
	hd44780_write_string("    ");
	hd44780_goto(MENU_POS + 1, MENU_VALUE_POS);

	menu_show_param(selectedMenuItem);
}

static void showYNMenu() {
	hd44780_clear();
	Menu_Cursor.on = 0;

	hd44780_message_center(selectedMenuYNItem->Title, 1);

	hd44780_goto(2, MENU_NO_POS);
	hd44780_write_string(MENU_YN_NO);
	hd44780_goto(2, MENU_YES_POS);
	hd44780_write_string(MENU_YN_YES);
}

static void toYNMenu() {
	//Example of using temp message.
	//strcpy(temp_msg_1, "why it works?");
	//send_message(MES_SHOW_TEMP_MSG);

	if (!okIO) {
		if (menuChange(selectedMenuYNItem->Previous))
			send_message(MES_REDRAW);
		else
			menu_back_to_preset();
		return;
	}

	prev_state = I_state;
	I_state = STATE_yn_menu;

	showYNMenu();
}

static void toYNMenu_noIO() {
	//Example of using temp message.
	//strcpy(temp_msg_1, "why it works?");
	//send_message(MES_SHOW_TEMP_MSG);
	prev_state = I_state;
	I_state = STATE_yn_menu;

	showYNMenu();
}


static void menu_show_param(menuItem_type * menu) {
	char s[5];
	uint8_t *b;
	uint16_t *w;
	int8_t *i;
	switch (menu->tValue) {
	case t_uint8:
		b = (uint8_t*) (menu->Value);
		uint8toa(*b, s);
		hd44780_write_string(s);
		break;
	case t_uint16:
		w = (uint16_t*) (menu->Value);
		uint16toa(*w, s);
		hd44780_write_string(s);
		break;
	case t_int8:
		i = (int8_t*) (menu->Value);
		int8toa(*i, s);
		hd44780_write_string(s);
		break;
	case t_bool:
		b = (uint8_t*) (menu->Value);
		if (*b)
			hd44780_write_string("On");
		else
			hd44780_write_string("Off");
		break;

	case t_perc:
		b = (uint8_t*) (menu->Value);
		uint8toa(*b, s);
		strcat(s, "%");
		hd44780_write_string(s);
		break;

	case t_note:
		b = (uint8_t*) (menu->Value);
		note_name (*b, s);
		hd44780_write_string(s);
		break;

	default:
		break;
	}
}

static void startMenu_preset(void) {
	if (!okIO)
		return;

	if ((presets_list.pos) == (presets_list.active))
		menu_stor_rename.Next = &NULL_ENTRY;
	else
		menu_stor_rename.Next = &menu_stor_del;

	selectedMenuItem = (menuItem_type*) &menu_stor_def;
	showMenu();

	I_state = STATE_menu;
}

static void startMenuYN_preset_save(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_save;
	toYNMenu();
}

static void startMenuYN_preset_rename(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_rename;
	toYNMenu();
}

static void startMenuYN_preset_delete(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_delete;
	toYNMenu();
}

static void startMenuYN_preset_copy(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_copy;
	toYNMenu();
}

static void startMenuYN_calibration_rename(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_calibr_rename;
	toYNMenu();
}

static void startMenuYN_calibration_save(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_calibr_save;
	toYNMenu();
}

static void startMenuYN_calibration_delete(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_calibr_delete;
	toYNMenu();
}

static void startMenuYN_calibration_copy(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_calibr_copy;
	toYNMenu();
}

static void startMenuYN_curve_rename(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_rename;
	toYNMenu();
}

static void startMenuYN_curve_save(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_save;
	toYNMenu();
}

static void startMenuYN_curve_delete(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_delete;
	toYNMenu();
}

static void startMenuYN_curve_copy(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_copy;
	toYNMenu();
}

static void startMenuYN_curve_export(void){
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_export;
	toYNMenu();
}

static void startMenuYN_bootloader(void){
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_bootloader;
	toYNMenu_noIO();
}

static void startMenuYN_USBdisk(void){
	if (USBdisk_active)
    	selectedMenuYNItem = (menuYNItem_type*) &menuYN_USBdisk_off;
	else {
    	selectedMenuYNItem = (menuYNItem_type*) &menuYN_USBdisk_on;
	}
	toYNMenu_noIO();
}


static void menu_preset_as_default(void) {
	selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_default;
	toYNMenu();
}


static void menu_preset_rename(void){
	if (!okIO)
		return;

	char name[MAX_FNAME - FEXT_SIZE];
	strcpy(name,presets_list.names[presets_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name

	text_object_init(&Text_Edit_object, "Rename preset:", name, STATE_presets_list, startMenuYN_preset_rename);
}

static void menu_preset_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	preset_rename(&presets_list, Text_Edit_object.text);
}


static void menu_preset_copy(void){
	if (!okIO)
		return;

	char name[MAX_FNAME - FEXT_SIZE];
	strcpy(name,presets_list.names[presets_list.pos]);
	size_t len=strlen(name);
	name[len-4]=0; //cut file extension from the name
	text_object_init(&Text_Edit_object, "Copy preset:", name, STATE_presets_list, startMenuYN_preset_copy);
}



static void menu_preset_copy_yes(void){
	char path[MAX_PATH]= "0:/" PRESET_DIR_NAME "/";
	char file_name[MAX_FNAME];
	char old_active_preset_name [MAX_FNAME];
	strcpy(old_active_preset_name, presets_list.names[presets_list.active]);
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, PRESET_EXT);
    strcat(path, file_name);
	if (preset_save(path, &Preset)!=FIO_OK)
		set_okIOzero();
	if (SDFS_scandir("0:/" PRESET_DIR_NAME, &presets_list)!=SDFS_OK)
		set_okIOzero();//update Presets list
	file_list_find(&presets_list, old_active_preset_name);
	presets_list.active=presets_list.pos;
	file_list_find(&presets_list, file_name);
}


static void menu_preset_save_yes(void){
	char path[MAX_PATH]= "0:/" PRESET_DIR_NAME "/";
    strcat(path, presets_list.names[presets_list.pos]);
	if (preset_save(path, &Preset)!=FIO_OK)
		set_okIOzero();
	Preset.Crc = presetCRC(&Preset);
}

static void menu_preset_delete_yes(void){
	char old_active_preset_name [MAX_FNAME];
	strcpy(old_active_preset_name, presets_list.names[presets_list.active]);
	if (preset_delete(&presets_list)!=FIO_OK)
		set_okIOzero();
	if (SDFS_scandir("0:/" PRESET_DIR_NAME, &presets_list)!=SDFS_OK)
		set_okIOzero();//update Presets list
	file_list_find(&presets_list, old_active_preset_name);
	presets_list.active=presets_list.pos;
}




static void calibration_message_draw(const char *line1, const char *line2){
	hd44780_clear();
	hd44780_message_center(line1, 1);
	hd44780_message_center(line2, 2);
}


static void menu_edit_calibration(void){
	I_state = STATE_calibration_start;
	send_message(MES_SLIDER_SHOW);
}


static void startMenu_calibration(void) {
	if (!okIO)
		return;

	if ((calibrations_list.pos) == (calibrations_list.active))
		menu_clb_rename.Next = &NULL_ENTRY;
	else
		menu_clb_rename.Next = &menu_clb_del;

	selectedMenuItem = (menuItem_type*) &menu_clb_edit;
	showMenu();
}


static void menu_calibration_rename(void){
	if (!okIO)
		return;

	char name[MAX_FNAME-FEXT_SIZE];
	strcpy(name,calibrations_list.names[calibrations_list.pos]);
	size_t len=strlen(name);
	name[len-FEXT_SIZE]=0; //cut file extension from the name
	text_object_init(&Text_Edit_object, "Rename calibr.:", name, STATE_calibrations_list, startMenuYN_calibration_rename);
}

static void menu_calibration_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	calibration_rename(&calibrations_list, Text_Edit_object.text);
}

static void menu_calibration_save_yes(void){
	char path[MAX_PATH] = "0:/" CALIBR_DIR_NAME "/";
	strcat(path, calibrations_list.names[calibrations_list.pos]);
	if (calibration_save(path, &Calibration)!=FIO_OK)
			set_okIOzero();
}


static void menu_calibration_copy(void){
	if (!okIO)
		return;

	char name[MAX_FNAME-FEXT_SIZE];
	strcpy(name,calibrations_list.names[calibrations_list.pos]);
	size_t len=strlen(name);
	name[len-FEXT_SIZE]=0; //cut file extension from the name
	text_object_init(&Text_Edit_object, "Copy calibr.:", name, STATE_calibrations_list, startMenuYN_calibration_copy);
}

static void menu_calibration_copy_yes(void){
	char path[MAX_PATH]= "0:/" CALIBR_DIR_NAME "/";
	char file_name[MAX_FNAME];
	char old_active_calibration_name [MAX_FNAME];
	strcpy(old_active_calibration_name, calibrations_list.names[calibrations_list.active]);
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, CALIBR_EXT);
    strcat(path, file_name);
	if (calibration_save(path, &Calibration)!=FIO_OK)
			set_okIOzero();
	if(SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list)!=SDFS_OK)
		set_okIOzero();
	file_list_find(&calibrations_list, old_active_calibration_name);
	calibrations_list.active=calibrations_list.pos;
	file_list_find(&calibrations_list, file_name);
}


static void menu_calibration_delete_yes(void){
	char old_active_calibration_name [MAX_FNAME];
	strcpy(old_active_calibration_name, calibrations_list.names[calibrations_list.active]);
	if(calibration_delete(&calibrations_list)!=FIO_OK)
		set_okIOzero();
	if(SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list)!=SDFS_OK)
		set_okIOzero();
	file_list_find(&calibrations_list, old_active_calibration_name);
	calibrations_list.active=calibrations_list.pos;
}


/*Initialize pointers to Curve_points structure elements*/
static void curve_editor_init(curve_edit_object_t  * C_object, curve_points_type * curve){ //Initialize pointers to Curve_points structure elements
	C_object->pos = 0;
	C_object->Curve = curve;
	C_object->item[0].value = &(curve->xw1);
	C_object->item[1].value = &(curve->xw2);
	C_object->item[2].value = &(curve->xw3);
	C_object->item[3].value = &(curve->xb1);
	C_object->item[4].value = &(curve->xb2);
	C_object->item[5].value = &(curve->xb3);
}


static void menu_edit_curve(void){
    curve_editor_init(Curve_Edit_object, &Curve);
//    Curve_Edit_object.parent=STATE_menu;
	I_state = STATE_curve_edit;
	send_message(MES_REDRAW);
}

static void menu_preset_edit_curve(void){
    curve_editor_init(Curve_Edit_object, &(Preset.Curve));
//    Curve_Edit_object.parent=STATE_menu;
	I_state = STATE_preset_curve_edit;
	send_message(MES_REDRAW);
}

static void menu_curve_export(void){
	if (!okIO)
		return;

	text_object_init(&Text_Edit_object, "Curve name:", "", STATE_menu, startMenuYN_curve_export);
}


static void menu_curve_rename(void){
	if (!okIO)
		return;

	char name[MAX_FNAME-FEXT_SIZE];
	strcpy(name,curves_list.names[curves_list.pos]);
	size_t len=strlen(name);
	name[len-FEXT_SIZE]=0; //cut file extension from the name
	text_object_init(&Text_Edit_object, "Rename curve.:", name, STATE_curve_list, startMenuYN_curve_rename);
}

static void menu_curve_rename_yes(void){
	string_cut_spaces(Text_Edit_object.text);
	curve_rename(&curves_list, Text_Edit_object.text);
}

static void menu_curve_save_yes(void){
	char path[MAX_PATH] = "0:/" CURVE_DIR_NAME "/";
	strcat(path, curves_list.names[curves_list.pos]);
	if (curve_save(path, &Curve)!=FIO_OK)
		set_okIOzero();
}


static void menu_curve_copy(void){
	if (!okIO)
		return;

	char name[MAX_FNAME-FEXT_SIZE];
	strcpy(name,curves_list.names[curves_list.pos]);
	size_t len=strlen(name);
	name[len-FEXT_SIZE]=0; //cut file extension from the name
	text_object_init(&Text_Edit_object, "Copy curve:", name, STATE_curve_list, startMenuYN_curve_copy);
}

//ÍÀÄÎ ÇÀÃÐÓÇÈÒÜ ×ÒÎ ÑÎÕÐÀÍßÒÜ
static void menu_curve_copy_yes(void){
	char path[MAX_PATH]= "0:/" CURVE_DIR_NAME "/";
	char file_name[MAX_FNAME];
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, CURVE_EXT);
    strcat(path, file_name);
	if(curve_save(path, (curve_points_type*)(&Curve))!=FIO_OK)
		set_okIOzero();
	if(SDFS_scandir("0:/" CURVE_DIR_NAME, &curves_list)!=SDFS_OK)
		set_okIOzero();
	file_list_find(&curves_list, file_name);
}

static void menu_curve_export_yes(void){
	char path[MAX_PATH]= "0:/" CURVE_DIR_NAME "/";
	char file_name[MAX_FNAME];
	strcpy(file_name,Text_Edit_object.text);
	string_cut_spaces(file_name);
    strcat(file_name, CURVE_EXT);
    strcat(path, file_name);
	if(curve_save(path, &Preset.Curve)!=FIO_OK)//Save (export) from selected preset
		 set_okIOzero();
	if(SDFS_scandir("0:/" CURVE_DIR_NAME, &curves_list)!=SDFS_OK)
		set_okIOzero();
	file_list_find(&curves_list, file_name);
}

static void menu_curve_load_yes(void){
	char path[MAX_PATH]= "0:/" CURVE_DIR_NAME "/";
	char file_name[MAX_FNAME];
	strcpy(file_name, curves_list.names[curves_list.pos]);
    strcat(file_name, CURVE_EXT);
    strcat(path, file_name);
    if (curve_load(file_name, &Preset.Curve)!=FIO_OK)
    	set_okIOzero();
}

static void menu_curve_delete_yes(void){
	char old_active_curve_name [MAX_FNAME];
	strcpy(old_active_curve_name, curves_list.names[curves_list.active]);
	if(curve_delete(&curves_list)!=FIO_OK)
		set_okIOzero();
	if(SDFS_scandir("0:/" CURVE_DIR_NAME, &curves_list)!=SDFS_OK)
		set_okIOzero();
	file_list_find(&curves_list, old_active_curve_name);
	curves_list.active=curves_list.pos;
}

static void menu_bootloader_yes(void){
   hd44780_clear();
   hd44780_message_center("BOOTLOADER",1);
   gotoBootLoader();
}

static void menu_USBdisk_on_yes(void){
	set_okIOzero();
	USBdisk_active=1;
	usb_midi_MSC_cb();
}

static void menu_USBdisk_off_yes(void){
	USBdisk_active=0;
	usb_midi_cb();
	reset_okIOzero();
}


static void menu_preset_sl_enter(void) {
	sliders_state = SLIDERS_MENU_SEARCH;
    controlLED1on(1);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}

static void menu_preset_sl_edit(void) {
	sliders_state = SLIDERS_WORK;
    controlLED1on(0);

    if (calibrationActive)
    	menuChange(&menu_clb_edit);
    else
    	menuChange(MENU_PARENT);
	send_message(MES_REDRAW);
}


static void menu_slider_edit(void){
	sliders_state = SLIDERS_MENU_SEARCH;
    controlLED1on(1);
	menuChange(MENU_PARENT);
	send_message(MES_REDRAW);
}


static void menu_slider_enter(void) {
	sliders_state = SLIDERS_WORK;
	controlLED1on(0);

	uint8_t num = selectedMenuItem->Min;
	slider_calibrate_number = num;

	if (calibrationActive) {
		if (num == SLIDER_PITCH) {
			menu_clb_e_dead.Parent = selectedMenuItem;
			menu_clb_e_dead.Value = (uint8_t*)(&Calibration.calibr[num].dead);
			menu_clb_e_gaps.Next = &menu_clb_e_dead;
		} else {
			menu_clb_e_gaps.Next = &NULL_ENTRY;
		}

		menu_clb_e_set.Parent = selectedMenuItem;
		menu_clb_e_delta.Parent = selectedMenuItem;
		menu_clb_e_delta.Value = (uint16_t*)(&Calibration.calibr[num].delta);
		menu_clb_e_gaps.Parent = selectedMenuItem;
		menu_clb_e_gaps.Value = (uint8_t*)(&Calibration.calibr[num].gap);

		menuChange(&menu_clb_e_set);

	} else {
		menu_sl_active.Parent = selectedMenuItem;
		menu_sl_active.Value = (uint8_t*)(&Preset.sliders[num].active);
		menu_sl_channel.Parent = selectedMenuItem;
		menu_sl_channel.Value = (uint8_t*)(&Preset.sliders[num].channel);

		if (num == SLIDER_PITCH) {
			menu_sl_channel.Next = &NULL_ENTRY;

		} else if (num == SLIDER_AT) {
			menu_sl_channel.Next = &menu_sl_min;
			menu_sl_min.Previous = &menu_sl_channel;

			menu_sl_min.Parent = selectedMenuItem;
			menu_sl_min.Value = (uint16_t*) (&(Preset.sliders[num].min_out_value));
			menu_sl_max.Parent = selectedMenuItem;
			menu_sl_max.Value = (uint16_t*) (&Preset.sliders[num].max_out_value);
			menu_sl_bin.Parent = selectedMenuItem;
			menu_sl_bin.Value = (uint8_t*) (&Preset.sliders[num].binary);
		} else {
			menu_sl_channel.Next = &menu_sl_event;
			menu_sl_event.Previous = &menu_sl_channel;

			menu_sl_event.Parent = selectedMenuItem;
			menu_sl_event.Value = (uint8_t*) (&Preset.sliders[num].event);
			menu_sl_reverse.Parent = selectedMenuItem;
			menu_sl_reverse.Value = (uint8_t*)(&Preset.sliders[num].reverse);
			menu_sl_min.Parent = selectedMenuItem;
			menu_sl_min.Value = (uint16_t*) (&(Preset.sliders[num].min_out_value));
			menu_sl_max.Parent = selectedMenuItem;
			menu_sl_max.Value = (uint16_t*) (&Preset.sliders[num].max_out_value);
		}

		if (num == SLIDER_P1 || num == SLIDER_P2 || num == SLIDER_P3) {
			menu_sl_max.Next = &menu_sl_bin;
			menu_sl_bin.Parent = selectedMenuItem;
			menu_sl_bin.Value = (uint8_t*) (&Preset.sliders[num].binary);
		} else {
			menu_sl_max.Next = &NULL_ENTRY;
		}

		menuChange(&menu_sl_active);
	}

	send_message(MES_REDRAW);
}


static void menu_preset_bt_enter(void) {
	buttonsToMenu = 1;
	controlLED1on(1);
	menuChange(MENU_CHILD);
	send_message(MES_REDRAW);
}

static void menu_preset_bt_edit(void) {
	buttonsToMenu = 0;
	controlLED1on(0);
	menuChange(MENU_PARENT);
	send_message(MES_REDRAW);
}

static void menu_button_edit(void) {
	buttonsToMenu = 1;
	controlLED1on(1);
	menuChange(MENU_PARENT);
	send_message(MES_REDRAW);
}

static void menu_button_enter(void) {
	uint8_t but_num = selectedMenuItem->Min - BUTTON_B1;

	menu_bt_active.Parent = selectedMenuItem;
	menu_bt_active.Value = (uint8_t*)(&Preset.buttons[but_num].active);
	menu_bt_type.Parent = selectedMenuItem;
	menu_bt_type.Value = (uint8_t*)(&Preset.buttons[but_num].type);
	menu_bt_channel.Parent = selectedMenuItem;
	menu_bt_channel.Value = (uint8_t*)(&Preset.buttons[but_num].channel);
	menu_bt_event.Parent = selectedMenuItem;
	menu_bt_event.Value = (uint8_t*)(&Preset.buttons[but_num].event);
	menu_bt_on.Parent = selectedMenuItem;
	menu_bt_on.Value = (uint8_t*)(&(Preset.buttons[but_num].on));
	menu_bt_off.Parent = selectedMenuItem;
	menu_bt_off.Value = (uint8_t*)(&Preset.buttons[but_num].off);

	buttonsToMenu = 0;
	controlLED1on(0);
	menuChange(&menu_bt_active);
	send_message(MES_REDRAW);
}


static void change_value(int16_t changer) {
	if (selectedMenuItem->Value == NULL || selectedMenuItem->tValue == t_none)
		return;

	int16_t value;

	switch (selectedMenuItem->tValue) {
	case t_uint16:
		value = *((uint16_t*) (selectedMenuItem->Value));
		break;

	case t_int8:
		value = *((int8_t*) (selectedMenuItem->Value));
		break;

	default:
		value = *((uint8_t*) (selectedMenuItem->Value));
		break;
	}

	int16_t old_value = value;
	value += changer;

	if (value < selectedMenuItem->Min)
		value = selectedMenuItem->Min;
	if (value > selectedMenuItem->Max)
		value = selectedMenuItem->Max;

	if (old_value == value)
		return;

	switch (selectedMenuItem->tValue) {
	case t_uint16:
		*((uint16_t*) selectedMenuItem->Value) = (uint16_t) value;
		break;

	case t_int8:
		*((int8_t*) selectedMenuItem->Value) = (int8_t) value;
		break;

	default:
		*((uint8_t*) selectedMenuItem->Value) = (uint8_t) value;
		break;
	}

	hd44780_goto(MENU_POS + 1, MENU_VALUE_POS);
	hd44780_write_string("    ");
	hd44780_goto(MENU_POS + 1, MENU_VALUE_POS);
	menu_show_param(selectedMenuItem);
}


void menu_button_handler(uint8_t button) {
	if (button >= BUTTON_B1 && button <= BUTTON_B8) {
		selectedMenuItem = menus_buttons_ordered[button - BUTTON_B1];
		showMenu();
		return;
	}

	switch (button) {
	case MES_SLIDER_MENU_FOUND:
		selectedMenuItem = menus_sliders_ordered[slider_calibrate_number];
		showMenu();
		break;
	case MES_KEY_SEEK:
		changeSplitKey(curNoteSeek);
		break;
	case MES_REDRAW:
		showMenu();
		break;
	case ENCODER_LEFT1:
		change_value(-1);
		break;
	case ENCODER_LEFT2:
		change_value(-5);
		break;
	case ENCODER_LEFT3:
		change_value(-10);
		break;
	case BUTTON_PAGEUP:
		if (menuChange(MENU_PREVIOUS)) {
    		MENU_POS = 0;
	    	showMenu();
		}
		break;
	case ENCODER_RIGHT1:
		change_value(1);
		break;
	case ENCODER_RIGHT2:
		change_value(5);
		break;
	case ENCODER_RIGHT3:
		change_value(10);
		break;
	case BUTTON_PAGEDOWN:
		if (menuChange(MENU_NEXT)) {
	    	MENU_POS = 1;
    		showMenu();
		}
		break;
	case BUTTON_ENTER:
		if (selectedMenuItem->Command_Enter) {
	        selectedMenuItem->Command_Enter();
		} else {
			menuChange(MENU_CHILD);
			send_message(MES_REDRAW);
		}
		break;
	case BUTTON_EDIT:
		if (selectedMenuItem->Command_Edit) {
	        selectedMenuItem->Command_Edit();
		} else {
			menuChange(MENU_PARENT);
			send_message(MES_REDRAW);
		}
		break;
	case BUTTON_STORAGE:
	default:
		break;
	}

}

void menu_yn_button_handler(uint8_t button) {
	switch (button) {

	case MES_REDRAW:
		showYNMenu();
		break;

	case BUTTON_ENTER:
		I_state = prev_state;

		if (selectedMenuYNItem->Command_Yes)
	        selectedMenuYNItem->Command_Yes();

		if (selectedMenuYNItem->Return_after_yes &&
				menuChange(selectedMenuYNItem->Previous))
			send_message(MES_REDRAW);
		else
			menu_back_to_preset();

		break;

	case BUTTON_EDIT:
		I_state = prev_state;

		if (menuChange(selectedMenuYNItem->Previous))
			send_message(MES_REDRAW);
		else
			menu_back_to_preset();

		break;

	case BUTTON_STORAGE:
/*		I_state = prev_state;
		menuChange(selectedMenuYNItem->Previous);
		send_message(MES_REDRAW);
*/		break;

	default:
		break;

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
	I_state = STATE_text_edit;

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



static void text_object_edit(uint8_t button, text_edit_object_t *obj) {
	uint8_t pos;
	switch (button) {
	case BUTTON_PAGEUP:
		(obj->pos)++;
		if (obj->pos>15) obj->pos=0;
		hd44780_goto(2, obj->pos+1);
		break;

	case BUTTON_PAGEDOWN:
		(obj->pos)--;
		if (obj->pos==0xFF) obj->pos=15;
		hd44780_goto(2, obj->pos+1);
		break;

	case ENCODER_LEFT3:
	case ENCODER_LEFT2:
	case ENCODER_LEFT1:
		pos=obj->pos;
		obj->text[pos]=rotate_char(obj->text[pos],-1,pos);
		hd44780_write_char(obj->text[pos]);
		hd44780_goto(2, pos+1);
		break;

	case ENCODER_RIGHT3:
	case ENCODER_RIGHT2:
	case ENCODER_RIGHT1:
		pos=obj->pos;
		obj->text[pos]=rotate_char(obj->text[pos],1,pos);
		hd44780_write_char(obj->text[pos]);
		hd44780_goto(2, pos+1);
		break;

	case BUTTON_ENTER:
	case BUTTON_STORAGE:
		if (strcmp(obj->text, obj->old_text)) { //text changed
			I_state = STATE_menu;
			hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
			obj->command();
		}
		break;

	default:
	    break;
	}

}

static void octave_shift_show(void) {
	char temp[4];
	int delta = Preset.OctaveShift * 12 + Preset.Transpose;
	if (delta != 0) {
		int8toa(delta, temp);
		if (delta < 10)
			strcat(temp, " ");
	} else {
		strcpy(temp, "   ");
	}

	hd44780_goto(2, 14);
	hd44780_write_string(temp);
}

static void preset_show (const presetType *pr, file_list_type *pr_list) {
	hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);

	char line[MAX_FNAME];
	memset(line, ' ', HD44780_DISP_LENGTH);
	line[HD44780_DISP_LENGTH] = 0;

	int len = 0;

	if (okIO) {
		len = strlen(pr_list->names[pr_list->pos]);
		memcpy(line, pr_list->names[pr_list->pos], len - FEXT_SIZE);
	} else if (USBdisk_active) {
		strcpy(line, "USB DISK ACTIVE");
	} else {
		strcpy(line, " SD CARD ERROR!");
	}

	hd44780_goto(1, 1);
	hd44780_write_string(line);

	memset(line,' ',HD44780_DISP_LENGTH);
	memcpy(line,"Ch:",3);
    btoa_mem(pr->MidiChannel,line+3);

    if (pr->SplitActive){
	    len=note_name(pr->SplitKey,line+6)+6;
	    memcpy(line+len,":",1 );
	    btoa_mem(pr->SplitChannel,line +len+1);
    }

    hd44780_goto(2, 1);
	hd44780_write_string(line);

	if (pr_list->pos == pr_list->active) {
		hd44780_goto(1, 16);
		hd44780_write_char(MENU_CHECK_CHAR);
	}

	octave_shift_show();
}


static void preset_name_current_state(void) {
	strcpy(Current_state.preset_name, presets_list.names[presets_list.pos]);
	presets_list.active = presets_list.pos;
	if (currentState_save() != FIO_OK)
		set_okIOzero();
}


static void presets_button_handler(uint8_t button){
	switch (button) {

	case MES_REDRAW:
		preset_show(&Preset, &presets_list);
		break;

	case ENCODER_LEFT1:
	case ENCODER_LEFT2:
	case ENCODER_LEFT3:
	case BUTTON_PAGEUP:
		if (!okIO)
			break;

		presets_list.pos--;
		if (presets_list.pos == 0xFFFF)
			presets_list.pos = presets_list.num - 1;
		if (preset_load(presets_list.names[presets_list.pos], &Preset)!=FIO_OK)
			set_okIOzero();
		preset_show(&Preset, &presets_list);
		break;

	case ENCODER_RIGHT3:
	case ENCODER_RIGHT2:
	case ENCODER_RIGHT1:
	case BUTTON_PAGEDOWN:
		if (!okIO)
			break;

		presets_list.pos++;
		if (presets_list.pos >= presets_list.num)
			presets_list.pos = 0;
		if (preset_load(presets_list.names[presets_list.pos], &Preset)!=FIO_OK)
			set_okIOzero();
		preset_show(&Preset, &presets_list);
		break;

	case BUTTON_STORAGE:
		startMenu_preset();
		break;

	case BUTTON_ENTER:
		selectedMenuItem = (menuItem_type*) &menu_pst_gen;
		showMenu();
		I_state=STATE_menu;
		break;

	case BUTTON_EDIT:
		selectedMenuItem = (menuItem_type*) &menu1_item1;
		showMenu();
		I_state=STATE_menu;
		break;

	case BUTTON_LEFT:
		if (Preset.OctaveShift > -OCTAVE_SHIFT_MAX)
			Preset.OctaveShift--;
		octave_shift_show();
		break;

	case BUTTON_RIGHT:
		if (Preset.OctaveShift < OCTAVE_SHIFT_MAX)
			Preset.OctaveShift++;
		octave_shift_show();
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
		hd44780_write_char(MENU_CHECK_CHAR);
	}
}

static void calibration_name_current_state(void){
	strcpy(Current_state.calibration_name, calibrations_list.names[calibrations_list.pos]);
	calibrations_list.active=calibrations_list.pos;
	if (currentState_save()!=FIO_OK)
		set_okIOzero();
	calibrationlist_start();
}


void calibration_init(char *name) {
	file_list_find(&calibrations_list, name);
	calibrations_list.active = calibrations_list.pos;
}

static void calibrationActiveSwitch(uint8_t active) {
	calibrationActive = active;
}

static void calibrationlist_start(void) {
	I_state = STATE_calibrations_list;
	calibrationActiveSwitch(1);
	show_calibration(&Calibration, &calibrations_list);
}


static uint16_t slider_edge1, slider_edge2;

static void start_calibration_handler(uint8_t event){
	switch (event) {
	case MES_SLIDER_SHOW:
		sliders_state = SLIDERS_FOUND;
		calibration_message_draw(slider_names[slider_calibrate_number], "Set Min & Enter");
		controlLED1on(1);
		break;
	case MES_SLIDER_EDGE:
		slider_edge1 = slider_calibrate_store; //save first edge;
		I_state = STATE_calibration_continue;
		send_message(MES_SLIDER_SHOW);
		break;
	case BUTTON_ENTER:
		if (sliders_state == SLIDERS_FOUND)
     		sliders_state = SLIDERS_CALIBRATE;
		break;
	case BUTTON_EDIT:
		sliders_state = SLIDERS_WORK;
        controlLED1on(0);
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
		slider_edge2 = slider_calibrate_store; //save second edge;
		if (slider_edge1<slider_edge2){
			Calibration.calibr[slider_calibrate_number].min_in_value=slider_edge1;
			Calibration.calibr[slider_calibrate_number].max_in_value=slider_edge2;
		}else{
			Calibration.calibr[slider_calibrate_number].min_in_value=slider_edge2;
			Calibration.calibr[slider_calibrate_number].max_in_value=slider_edge1;
		}
		sliders_state = SLIDERS_WORK;
        controlLED1on(0);
		I_state = STATE_menu;
		send_message(MES_REDRAW);
		break;
	case BUTTON_EDIT:
		sliders_state = SLIDERS_WORK;
        controlLED1on(0);
		I_state=STATE_menu;
		send_message(MES_REDRAW);
		break;
	case BUTTON_ENTER:
		if (sliders_state == SLIDERS_EDGE){
     		sliders_state = SLIDERS_CALIBRATE;
    	    controlLED1on(1);
		}
		break;
	default:
		break;
	}
}


static void calibrations_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:
		show_calibration(&Calibration, &calibrations_list);
		break;
	case ENCODER_LEFT1:
	case ENCODER_LEFT2:
	case ENCODER_LEFT3:
	case BUTTON_PAGEUP:
		calibrations_list.pos--;
		if (calibrations_list.pos == 0xFFFF)
			calibrations_list.pos = calibrations_list.num - 1;
		Calibration.calibr[0].min_in_value=99;
		if(calibration_load(calibrations_list.names[calibrations_list.pos], &Calibration)!=FIO_OK)
			set_okIOzero();
		show_calibration(&Calibration, &calibrations_list);
		break;
	case ENCODER_RIGHT1:
	case ENCODER_RIGHT2:
	case ENCODER_RIGHT3:
	case BUTTON_PAGEDOWN:
		calibrations_list.pos++;
		if (calibrations_list.pos >= calibrations_list.num)
			calibrations_list.pos = 0;
		if(calibration_load(calibrations_list.names[calibrations_list.pos], &Calibration)!=FIO_OK)
			set_okIOzero();
		show_calibration(&Calibration, &calibrations_list);
		break;
	case BUTTON_STORAGE:
		selectedMenuYNItem = (menuYNItem_type*) &menuYN_calibr_active;
		toYNMenu();
		break;
	case BUTTON_ENTER:
		startMenu_calibration();
		I_state=STATE_menu;
		break;
	case BUTTON_EDIT:
		calibrationActiveSwitch(0);

		selectedMenuItem = (menuItem_type*) &menu1_item1;
		showMenu();
		I_state=STATE_menu;
		break;
	default:
		break;
	}

}

static void show_curve (file_list_type *curve_list){
	char line[17];
    hd44780_clear();
	hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	memset(line,' ',16);
	line[16]=0;
	if (curve_list->num > 0) {
		int len = strlen(curve_list->names[curve_list->pos]);
		memcpy(line, curve_list->names[curve_list->pos], len - 4);
		hd44780_goto(1, 1);
		hd44780_write_string(line);
	}else{
		hd44780_message_center("EMPTY", 1);
	}
}


static void preset_curves_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:
		show_curve(&curves_list);
		break;
	case ENCODER_LEFT1:
	case ENCODER_LEFT2:
	case ENCODER_LEFT3:
	case BUTTON_PAGEUP:
		curves_list.pos--;
		if (curves_list.pos == 0xFFFF)
			curves_list.pos = curves_list.num - 1;
		if(curve_load(curves_list.names[curves_list.pos], &(Preset.Curve))!=FIO_OK)
				set_okIOzero();
		show_curve(&curves_list);
		break;
	case ENCODER_RIGHT1:
	case ENCODER_RIGHT2:
	case ENCODER_RIGHT3:
	case BUTTON_PAGEDOWN:
		curves_list.pos++;
		if (curves_list.pos >= curves_list.num)
			curves_list.pos = 0;
		if(curve_load(curves_list.names[curves_list.pos], &(Preset.Curve))!=FIO_OK)
				set_okIOzero();
		show_curve(&curves_list);
		break;
	case BUTTON_STORAGE:
		break;
	case BUTTON_ENTER:
		selectedMenuYNItem = (menuYNItem_type*) &menuYN_curve_load;
		toYNMenu();
		break;
	case BUTTON_EDIT:
		selectedMenuItem = (menuItem_type*) &menu4_item1;
		showMenu();
		I_state=STATE_menu;
		break;
	default:
		break;
	}

}

static void curves_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:
		if(curve_load(curves_list.names[curves_list.pos], &Curve)!=FIO_OK)
			set_okIOzero();
		show_curve(&curves_list);
		break;
	case ENCODER_LEFT1:
	case ENCODER_LEFT2:
	case ENCODER_LEFT3:
	case BUTTON_PAGEUP:
		curves_list.pos--;
		if (curves_list.pos == 0xFFFF)
			curves_list.pos = curves_list.num - 1;
		if(curve_load(curves_list.names[curves_list.pos], &Curve)!=FIO_OK)
			set_okIOzero();
		show_curve(&curves_list);
		break;
	case ENCODER_RIGHT1:
	case ENCODER_RIGHT2:
	case ENCODER_RIGHT3:
	case BUTTON_PAGEDOWN:
		curves_list.pos++;
		if (curves_list.pos >= curves_list.num)
			curves_list.pos = 0;
		if(curve_load(curves_list.names[curves_list.pos], &Curve)!=FIO_OK)
			set_okIOzero();
		show_curve(&curves_list);
		break;
	case BUTTON_STORAGE:
		break;
	case BUTTON_ENTER:
	//	if ((curves_list.pos) == (curves_list.active)){
	//		menu3_item3.Next=&NULL_ENTRY;
	//	}else{
	//		menu3_item3.Next=&menu3_item4;
	//	}
		selectedMenuItem = (menuItem_type*) &menu3_item1;
		showMenu();
		I_state=STATE_menu;
		break;
	case BUTTON_EDIT:
		selectedMenuItem = (menuItem_type*) &menu1_item1;
		showMenu();
		I_state=STATE_menu;
		break;
	default:
		break;
	}

}


static void curve_editor_value_draw(curve_edit_object_t* C_object, uint8_t i){
	uint16_t n;
	char s[10];
	n = (uint16_t)((*(C_object->item[i].value))/CURVE_X_FACTOR);
	uint16toa(n, s);
	string_number_format(s,curve_xy[i].n);
	hd44780_goto(curve_xy[i].y, curve_xy[i].x);
	hd44780_write_string(s);
}




static void curve_editor_draw(curve_edit_object_t* C_object){
    hd44780_clear();
    Menu_Cursor.on=0;
	hd44780_display(HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);
	hd44780_goto(1,1);
	hd44780_write_char('w');
	hd44780_goto(2,1);
	hd44780_write_char('b');
	for (uint8_t i=0; i<6; i++){
		curve_editor_value_draw(C_object, i);
	}
	menu_cursor_draw(&Menu_Cursor, curve_xy[C_object->pos].y, curve_xy[C_object->pos].x-1);
}

static void curve_editor_change_pos(curve_edit_object_t* C_object, int8_t n){
	int8_t pos=C_object->pos+n;
	if (pos>5)
		pos=pos-6;
	else if (pos<0)
		pos=pos+6;
	menu_cursor_draw(&Menu_Cursor, curve_xy[pos].y, curve_xy[pos].x-1);
	C_object->pos=pos;
}

static void curves_editor_change_value(curve_edit_object_t* C_object, int32_t change) {
	uint8_t pos = C_object->pos;
	uint32_t value = *(C_object->item[pos].value) + change;
	uint32_t max = C_object->item[pos].max;
	uint32_t min = C_object->item[pos].min;
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	*(C_object->item[pos].value) = value;
	curve_editor_value_draw(C_object, pos);
	hd44780_goto(curve_xy[pos].y, curve_xy[pos].x);
	calculate_velocity_formula(C_object->Curve);
}

static void curves_editor_button_handler(uint8_t button){
	switch (button) {
	case MES_REDRAW:
		curve_editor_draw(Curve_Edit_object);
		break;
	case ENCODER_LEFT1:
		curves_editor_change_value(Curve_Edit_object, -1*CURVE_X_FACTOR);
		break;
	case ENCODER_LEFT2:
		curves_editor_change_value(Curve_Edit_object, -10*CURVE_X_FACTOR);
		break;
	case ENCODER_LEFT3:
		curves_editor_change_value(Curve_Edit_object, -50*CURVE_X_FACTOR);
		break;
	case ENCODER_RIGHT1:
		curves_editor_change_value(Curve_Edit_object, 1*CURVE_X_FACTOR);
		break;
	case ENCODER_RIGHT2:
		curves_editor_change_value(Curve_Edit_object, 10*CURVE_X_FACTOR);
		break;
	case ENCODER_RIGHT3:
		curves_editor_change_value(Curve_Edit_object, 50*CURVE_X_FACTOR);
		break;
	case BUTTON_PAGEDOWN:
		curve_editor_change_pos(Curve_Edit_object,1);
		break;
	case BUTTON_PAGEUP:
		curve_editor_change_pos(Curve_Edit_object,-1);
		break;
	case BUTTON_STORAGE:
		break;
	case BUTTON_ENTER:
		break;
	case BUTTON_EDIT:
		I_state=STATE_menu;
		send_message(MES_REDRAW);
		break;
	default:
		break;
	}

}

static void temp_msg_handler(uint8_t event) {
	switch (event) {
		case MES_SHOW_TEMP_MSG:
			showing_temp_msg = 1;
			hd44780_show_temp_msg(temp_msg_1, temp_msg_2);
			strcpy(temp_msg_1, "");
			strcpy(temp_msg_2, "");
			setTimerMs(temp_msg_time * 1000);
			break;

		case MES_TIMER_END:
		case BUTTON_ENTER:
		case BUTTON_STORAGE:
		case BUTTON_EDIT:
			showing_temp_msg = 0;
			hd44780_remove_temp_msg();
			break;

		default:
			break;
	}
}


/*this function is calling if any setup button pressed, according to
 * the interface status it calls button_handlers
 */

void menu_btns_n_msg_handler(uint8_t event) {
	if ((event == MES_SHOW_TEMP_MSG || showing_temp_msg) && event != MES_REDRAW) {
		temp_msg_handler(event);
		return;
	}

	switch (I_state) {
	case STATE_presets_list:
		presets_button_handler(event);
		break;
	case STATE_menu:
		menu_button_handler(event);
		break;
	case STATE_curve_edit:
		curves_editor_button_handler(event);
		break;
	case STATE_preset_curve_edit:
		curves_editor_button_handler(event);
		break;
	case STATE_curve_list:
		curves_button_handler(event);
		break;
	case STATE_preset_curve_list:
		preset_curves_button_handler(event);
		break;
	case STATE_text_edit:
		text_object_edit(event, &Text_Edit_object);
		break;
	case STATE_calibrations_list:
		calibrations_button_handler(event);
		break;
	case STATE_calibration_start:
		start_calibration_handler(event);
		break;
	case STATE_calibration_continue:
		continue_calibration_handler(event);
		break;
	case STATE_yn_menu:
		menu_yn_button_handler(event);
		break;
	default:
		break;
	}
}

static void check_saving_preset(void) {
	if (Preset.Crc != presetCRC(&Preset)) {
		selectedMenuYNItem = (menuYNItem_type*) &menuYN_preset_save;
		toYNMenu();
	} else {
		menu_back_to_preset();
	}
}

static void menu_back_to_preset(void) {
	calculate_velocity_formula(&Preset.Curve);//Use curve from preset
	I_state = STATE_presets_list;
	preset_show(&Preset, &presets_list);
}

static void curvelist_start(void){
	if (!okIO)
		return;

    I_state = STATE_curve_list;
    send_message(MES_REDRAW);
}

static void preset_curvelist_start(void){
	if (!okIO)
		return;

    I_state = STATE_preset_curve_list;
    send_message(MES_REDRAW);
}


void interface_init(char *name) {
	I_state = STATE_presets_list;
	file_list_find(&presets_list, name);
	presets_list.active = presets_list.pos;
	preset_show(&Preset, &presets_list);

	for (int i = 0; i < SLIDERS_AMOUNT; i++) {
		menuItem_type * temp_menu = menus_sliders[i];
		if (temp_menu != NULL)
			menus_sliders_ordered[temp_menu->Min] = temp_menu;
	}
	for (int i = 0; i < BUTTONS_AMOUNT; i++) {
		menuItem_type * temp_menu = menus_buttons[i];
		if (temp_menu != NULL)
			menus_buttons_ordered[temp_menu->Min - BUTTON_B1] = temp_menu;
	}
}
