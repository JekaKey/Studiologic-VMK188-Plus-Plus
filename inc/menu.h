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


#define BUTTON_PAGEUP 0
#define BUTTON_PAGEDOWN 2
#define BUTTON_PANIC 4
#define BUTTON_EDIT 6
#define BUTTON_CHANNEL 1
#define BUTTON_BANK 3
#define BUTTON_PROGRAM 5
#define BUTTON_STORAGE 7
#define BUTTON_ENTER 10

#define BUTTON_LEFT 11
#define BUTTON_RIGHT 12
#define BUTTON_RECORD 13
#define BUTTON_PLAY 14
#define BUTTON_STOP 15

#define BUTTON_B1 16
#define BUTTON_B2 17
#define BUTTON_B3 18
#define BUTTON_B4 19
#define BUTTON_B5 20
#define BUTTON_B6 21
#define BUTTON_B7 22
#define BUTTON_B8 23
#define ENCODER_LEFT 25
#define ENCODER_RIGHT 26

void interface_init (void);
void checkControl_events(void);
uint8_t checkButtons_events(void);

