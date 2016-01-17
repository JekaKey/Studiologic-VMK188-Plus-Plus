#include "presets.h"


#define YES_POS 5 //Cursor position Yes in yes/no dialog
#define NO_POS 11 //Cursor position No in yes/no dialog


#define MENU_TEXT_POS 3
#define MENU_VALUE_POS 13
#define MENU_CURSOR_POS 1
#define MENU_CURSOR_CHAR 0x0
#define MENU_CHECK_CHAR 0x1
#define MENU_YES_POS 14
#define MENU_NO_POS 1

#define MENU_YN_YES "Yes"
#define MENU_YN_NO 	"No"

#define TEMP_MSG_INTERVAL 1500


typedef enum {t_none, t_uint8, t_uint16, t_int8, t_bool, t_perc, t_note} value_tp;



typedef struct {
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t    Pos;
	void		*Value;
	value_tp    tValue;
	int16_t   Min;
	int16_t   Max;
	void       (*Command_Enter)(void);
	void       (*Command_Edit)(void);
	char       Text[];
} menuItem_type;


typedef struct {
	const char  Title[16];
	void       (*Command_Yes)(void);
	uint8_t    Return_after_yes;
	void       *Previous;
} menuYNItem_type;


#define MAKE_MENU(Name, Next, Previous, Parent, Child, Pos, Value, tValue, Min, Max, Command_Enter, Command_Edit, Text) \
	extern  menuItem_type  Next;     \
	extern  menuItem_type  Previous; \
	extern  menuItem_type  Parent;   \
	extern  menuItem_type  Child;  \
	menuItem_type Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Pos, (void*)Value, (value_tp)tValue, (uint16_t)Min, (uint16_t)Max, (void*) Command_Enter, (void*) Command_Edit, { Text }}

#define MAKE_MENU_YN(Name, Title, Command_Yes, Return_after_yes, Previous) \
	extern  menuItem_type  Previous; \
	menuYNItem_type Name = {{Title}, (void*) Command_Yes, (uint8_t) Return_after_yes, (void*)&Previous}


#define NULL_ENTRY Null_Menu

#define MENU_PREVIOUS   ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Previous))
#define MENU_NEXT       ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Next))
#define MENU_PARENT     ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Parent))
#define MENU_CHILD      ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Child))
#define MENU_SELECT	    (selectedMenuItem->Select)
#define MENU_POS        (selectedMenuItem->Pos)
#define MENU_VALUE      (selectedMenuItem->Value)
#define MENU_TVALUE     (selectedMenuItem->tValue)
#define MENU_MIN        (selectedMenuItem->Min)
#define MENU_MAX        (selectedMenuItem->Max)





typedef enum {	STATE_presets_list,
				STATE_menu,
				STATE_preset_edit_name,
				STATE_curve_edit,
				STATE_preset_curve_edit,
				STATE_text_edit,
				STATE_number_edit,
				STATE_calibration_start,
				STATE_calibration_continue,
				STATE_calibrations_list,
				STATE_curve_list,
				STATE_preset_curve_list,
				STATE_yn_menu
			} i_state_t;


typedef struct {
      	uint8_t x;
       	uint8_t y;
       	uint8_t n;//maximum number of characters
}xy_t; //Coordinates pair


typedef struct {
	char title[17];
	char text[17];
	char old_text[17];
	uint8_t state;
	uint8_t pos;
	uint8_t line;
	void (*onComplete)(void);
} text_edit_object_t;

typedef struct {
	uint32_t * value;
    uint32_t min;
    uint32_t max;
} curve_edit_item_t;

typedef struct {
	int8_t pos;
	curve_points_type * Curve;
	curve_edit_item_t item[6];
} curve_edit_object_t;

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t on;
} menu_cursor_object_t;


typedef struct {
   uint8_t on;
   uint8_t pressed;
} button_object_t;

void btoa(uint8_t value, char* buffer);


void interface_init(char *name);
void calibration_init(char *name);
void checkControl_events(void);
void menu_btns_n_msg_handler(uint8_t event);
void changeSplitKey(uint8_t note);
