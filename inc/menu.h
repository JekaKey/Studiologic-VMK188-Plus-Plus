#include "presets.h"

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


typedef enum {STATE_presets_list, STATE_menu, STATE_preset_edit_name, STATE_calibration_edit, STATE_curve_edit} interface_state_t;

typedef struct {
	char text[16];
	enum {start, edit, } state;
	uint8_t pos;
	uint8_t line;
}text_object_t;

void btoa(uint8_t value, char* buffer);

void text_object_init(text_object_t *object, const char *st, const uint8_t line);
void text_object_edit(text_object_t *object, char *st);

void interface_init(const presetType *pr, char * name);
void checkControl_events(void);
uint8_t checkButtons_events(void);
void head_buttons_handler(void);
