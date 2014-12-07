#include "presets.h"


#define YES_POS 5 //Cursor position Yes in yes/no dialog
#define NO_POS 11 //Cursor position No in yes/no dialog


/*the events to send to controls FIFO*/
#define MES_REDRAW 30
#define MES_YES 31


/*************************************/

#define MENU_TEXT_POS 3
#define MENU_CURSOR_POS 1
#define MENU_CURSOR_CHAR '*'
#define MENU_YES_POS 4
#define MENU_NO_POS 11

typedef struct {
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	uint8_t     Pos;
	uint8_t    Vertical;
	void       (*Command_Enter)(void);
	void       (*Command_Edit)(void);
	const char  Title[16];
	const char  Text[];
} menuItem_type;


#define MAKE_MENU(Name, Next, Previous, Parent, Child, Pos, Vertical, Command_Enter, Command_Edit, Title, Text) \
	extern menuItem_type Next;     \
	extern menuItem_type Previous; \
	extern menuItem_type Parent;   \
	extern menuItem_type Child;  \
	menuItem_type Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, (uint8_t)Pos, (uint8_t)Vertical, (void*) Command_Enter, (void*) Command_Edit, {Title},{ Text }}

#define NULL_ENTRY Null_Menu

#define MENU_PREVIOUS   ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Previous))
#define MENU_NEXT       ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Next))
#define MENU_PARENT     ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Parent))
#define MENU_CHILD      ((menuItem_type*)/*pgm_read_word*/(selectedMenuItem->Child))
//#define SELECT	    (pgm_read_byte(&selectedMenuItem->Select))
#define MENU_SELECT	    (selectedMenuItem->Select)
#define MENU_POS        (selectedMenuItem->Pos)
#define MENU_VERTICAL   (selectedMenuItem->Vertical)


typedef enum {STATE_presets_list, STATE_menu, STATE_preset_edit_name, STATE_calibration_edit, STATE_curve_edit, STATE_text_edit} i_state_t;

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

void btoa(uint8_t value, char* buffer);


void interface_init(const presetType *pr, char *name);
void checkControl_events(void);
uint8_t checkButtons_events(void);
void head_buttons_handler(void);
