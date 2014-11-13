#include "presets.h"


#define YES_POS 5 //Cursor position Yes in yes/no dialog
#define NO_POS 11 //Cursor position No in yes/no dialog


/*the events to send to controls FIFO*/
#define MES_REDRAW 30


/*************************************/


typedef struct PROGMEM{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Select;
	const char  Text[];
} menuItem_type;

#define MAKE_MENU(Name, Next, Previous, Parent, Child, Select, Text) \
	extern menuItem_type Next;     \
	extern menuItem_type Previous; \
	extern menuItem_type Parent;   \
	extern menuItem_type Child;  \
	menuItem_type Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Select, { Text }}

#define NULL_ENTRY Null_Menu

#define PREVIOUS   ((menuItem_type*)/*pgm_read_word*/(&selectedMenuItem->Previous))
#define NEXT       ((menuItem_type*)/*pgm_read_word*/(&selectedMenuItem->Next))
#define PARENT     ((menuItem_type*)/*pgm_read_word*/(&selectedMenuItem->Parent))
#define CHILD      ((menuItem_type*)/*pgm_read_word*/(&selectedMenuItem->Child))
//#define SELECT	    (pgm_read_byte(&selectedMenuItem->Select))
#define SELECT	    (&selectedMenuItem->Select)



typedef enum {STATE_presets_list, STATE_menu, STATE_preset_edit_name, STATE_calibration_edit, STATE_curve_edit, STATE_yes_no, STATE_text_edit} i_state_t;

typedef struct {
	char name[17];
	char text[17];
	uint8_t state;
	uint8_t pos;
	uint8_t line;
	i_state_t parent;
}text_edit_object_t;

typedef struct {
	char text[16];
	uint8_t state;
	uint8_t pos;
	i_state_t parent;
}yes_no_object_t;

void btoa(uint8_t value, char* buffer);


void interface_init(const presetType *pr, char *name);
void checkControl_events(void);
uint8_t checkButtons_events(void);
void head_buttons_handler(void);
