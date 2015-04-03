#include "presets.h"


#define YES_POS 5 //Cursor position Yes in yes/no dialog
#define NO_POS 11 //Cursor position No in yes/no dialog


#define MENU_TEXT_POS 3
#define MENU_VALUE_POS 13
#define MENU_CURSOR_POS 1
#define MENU_CURSOR_CHAR 0x0
#define MENU_CHECK_CHAR 0x1
#define MENU_YES_POS 4
#define MENU_NO_POS 11

typedef enum {t_uint8, t_uint16, t_bool} value_t;


typedef struct {
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Pos;
	uint8_t    Vertical;
	int8_t       *Value;
	value_t    tValue;
	uint16_t   Min;
	uint16_t   Max;
	void       (*Command_Enter)(void);
	void       (*Command_Edit)(void);
	void       (*Command_Show)(void * menuaddr);
	const char  Title[16];
	char       Text[];
} menuItem_type;


#define MAKE_MENU(Name, Next, Previous, Parent, Child, Pos, Vertical, Value, tValue, Min, Max, Command_Enter, Command_Edit, Command_Show, Title, Text) \
	extern menuItem_type Next;     \
	extern menuItem_type Previous; \
	extern menuItem_type Parent;   \
	extern menuItem_type Child;  \
	menuItem_type Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Pos, (uint8_t)Vertical, (void*)Value, (value_t)tValue, (uint16_t)Min, (uint16_t)Max, (void*) Command_Enter, (void*) Command_Edit, (void*) Command_Show, {Title},{ Text }}

#define NULL_ENTRY Null_Menu

#define MENU_PREVIOUS   ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Previous))
#define MENU_NEXT       ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Next))
#define MENU_PARENT     ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Parent))
#define MENU_CHILD      ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Child))
#define MENU_SELECT	    (selectedMenuItem->Select)
#define MENU_POS        (selectedMenuItem->Pos)
#define MENU_VERTICAL   (selectedMenuItem->Vertical)
#define MENU_VALUE      (selectedMenuItem->Value)
#define MENU_TVALUE     (selectedMenuItem->tValue)
#define MENU_MIN        (selectedMenuItem->Min)
#define MENU_MAX        (selectedMenuItem->Max)





typedef enum {STATE_presets_list,
	          STATE_menu,
	          STATE_preset_edit_name,
	          STATE_curve_edit,
	          STATE_text_edit,
	          STATE_number_edit,
	          STATE_calibration_start,
	          STATE_calibration_continue,
              STATE_calibrations_list} i_state_t;

typedef struct {
	char title[17];
	char text[17];
	char old_text[17];
	uint8_t state;
	uint8_t pos;
	uint8_t line;
	i_state_t parent;
	void (*command)(void);
}text_edit_object_t;

typedef struct {
	char title[17];
	char text[17];
    uint16_t value;
    uint16_t old_value;
    uint16_t min;
    uint16_t max;
	uint8_t state;
	uint8_t pos;
	uint8_t line;
	uint8_t left;
	uint8_t size;
	i_state_t parent;
	void (*command)(void);
}number_edit_object_t;


void btoa(uint8_t value, char* buffer);


void interface_init(char *name);
void calibration_init(char *name);
void checkControl_events(void);
uint8_t checkButtons_events(void);
void head_buttons_handler(void);
