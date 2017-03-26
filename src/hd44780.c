#include <string.h>
#include "hd44780.h"
#include "leds.h"


const uint8_t symbol_menu_pointer[]={0b00001000,
                                     0b00000100,
                                     0b00011110,
                                     0b00011111,
                                     0b00011110,
                                     0b00000100,
                                     0b00001000,
                                     0b00000000};
/*
const uint8_t symbol_check[]=       {0b00000111,
                                     0b00010101,
                                     0b00010111,
                                     0b00010001,
                                     0b00011101,
                                     0b00010101,
                                     0b00011100,
                                     0b00000000};
*/
const uint8_t symbol_check[]=       {0b00000000,
                                     0b00001110,
                                     0b00011111,
                                     0b00011111,
                                     0b00011111,
                                     0b00001110,
                                     0b00000000,
                                     0b00000000};

#ifdef WS0010_GRAPHICS
const uint8_t pictureVMK188 [] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x78, 0x03, 0xF0, 0x1F, 0x80, 0x1C, 0x00,
		0x1F, 0x80, 0x03, 0xF0, 0x00, 0x78, 0x00, 0x08, 0x00, 0x00, 0x1F, 0xF8, 0x1F, 0xF8, 0x00, 0x38,
		0x01, 0xF0, 0x0F, 0x80, 0x1C, 0x00, 0x0F, 0x80, 0x01, 0xF0, 0x00, 0x38, 0x1F, 0xF8, 0x1F, 0xF8,
		0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1F, 0xF8, 0x01, 0x80, 0x00, 0xC0, 0x01, 0xE0, 0x07, 0xB0,
		0x1E, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x30, 0x1F, 0xF8,
		0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x70, 0x1F, 0xF8, 0x19, 0x98, 0x19, 0x98, 0x19, 0x98,
		0x1F, 0xF8, 0x0E, 0x70, 0x00, 0x00, 0x0E, 0x70, 0x1F, 0xF8, 0x19, 0x98, 0x19, 0x98, 0x19, 0x98,
		0x1F, 0xF8, 0x0E, 0x70, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x0F, 0xF0, 0x0F, 0xF0,
		0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x0F, 0xF0,
		0x0F, 0xF0, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

char buffer[HD44780_DISP_VOLUME] = {' '};
uint8_t currentPos;

uint8_t showingTemp;


volatile uint8_t hd44780_active;
extern uint8_t buttons_active;

void hd44780_wr_hi_nibble(uint8_t data) {
	if (data & 0x10) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT4);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT4);
	}
	if (data & 0x20) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT5);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT5);
	}
	if (data & 0x40) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT6);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT6);
	}
	if (data & 0x80) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT7);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT7);
	}

	/* set the EN signal */hd44780_EN_On();

	/* wait */hd44780_EN_high_delay();

	/* reset the EN signal */
	hd44780_EN_Off();
}

#if HD44780_CONF_BUS == HD44780_FUNC_BUS_8BIT

/* 8bit bus version */


void hd44780_write(uint8_t data) {
	while (buttons_active){
	}
	hd44780_active=1;
	controlLEDs_enable(0);

	/* set the data bits */
	uint16_t dataportValue = HD44780_DATAPORT->IDR;
	HD44780_DATAPORT->ODR = (dataportValue & 0xFF00) + data; //In the current project the display uses PE0-PE7 GPIO, so it is possible to switch them by one command

/*
	if (data & 0x01) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT0);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT0);
	}
	if (data & 0x02) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT1);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT1);
	}
	if (data & 0x04) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT2);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT2);
	}
	if (data & 0x08) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT3);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT3);
	}
	if (data & 0x10) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT4);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT4);
	}
	if (data & 0x20) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT5);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT5);
	}
	if (data & 0x40) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT6);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT6);
	}
	if (data & 0x80) {
		GPIO_SetBits(HD44780_DATAPORT, HD44780_DATABIT7);
	} else {
		GPIO_ResetBits(HD44780_DATAPORT, HD44780_DATABIT7);
	}
*/
	/* tell the lcd that we have a command to read in */hd44780_EN_On();

	/* wait long enough so that the lcd can see the command */hd44780_EN_high_delay();

	/* reset the ce line */hd44780_EN_Off();
	hd44780_init_end_delay();
	hd44780_active=0;
	controlLEDs_enable(1);
}
#endif /* HD44780_CONF_BUS == HD44780_FUNC_BUS_8BIT */


void hd44780_clear() {
//	for (int i = 0; i < HD44780_DISP_VOLUME; i++)
//		buffer[i] = ' ';

	memset(buffer, ' ', HD44780_DISP_VOLUME);

	if (!showingTemp)
		hd44780_wr_cmd(HD44780_CMD_CLEAR);
}

void hd44780_home() {
	currentPos = 0;
	if (!showingTemp)
		hd44780_wr_cmd(HD44780_CMD_RETURN_HOME);
}


void hd44780_wr_cmd(const uint8_t cmd) {
	hd44780_RS_Off();
	hd44780_write(cmd);
}

void hd44780_write_char(const uint8_t data) {
	buffer[currentPos] = data;

	if (currentPos < HD44780_DISP_VOLUME - 1)
		currentPos++;

	if (!showingTemp)
		hd44780_wr_data_noblock(data);
}

void hd44780_wr_data_noblock(const uint8_t data) {
	while (buttons_active) {}

	hd44780_RS_On();
	hd44780_write(data);
}

void hd44780_init(void) {
	while (buttons_active) {}

	hd44780_active=1;
	controlLEDs_enable(0);

	/* clear control bits */
	hd44780_EN_Off();
	hd44780_RS_Off();
//	hd44780_RW_Off();


	/* sets the configured values - can be set again only after reset */
	hd44780_function( HD44780_CONF_BUS, HD44780_CONF_LINES, HD44780_CONF_FONT, HD44780_FONT_TABLE);

	/* turn the display off with no cursor or blinking */
	hd44780_display( HD44780_DISP_OFF, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF);

	/* clear the display */
	hd44780_clear();

	/* addr increment, shift cursor */
	hd44780_entry( HD44780_ENTRY_SHIFT_CURS, HD44780_ENTRY_ADDR_INC);

	hd44780_load_symbol(0x0, symbol_menu_pointer);
	hd44780_load_symbol(0x8, symbol_check);

	/*cursor to zero position*/
	hd44780_ddram_addr(0);

	hd44780_active=0;
	controlLEDs_enable(1);
}


void hd44780_write_string(const char *s) {
	for (uint8_t i = 0; (s[i] != '\0') && (i < HD44780_DISP_LENGTH); i++)
		hd44780_write_char(s[i]);
}

void hd44780_goto(uint8_t line, uint8_t position) {
	currentPos = HD44780_DISP_LENGTH * (line - 1) + position - 1;

	if (!showingTemp)
		hd44780_goto_noblock(line, position);
}

void hd44780_goto_noblock(uint8_t line, uint8_t position) {
	while (buttons_active) {}

	hd44780_active = 1;
	controlLEDs_enable(0);
	hd44780_ddram_addr((0x40 * (line - 1)) + (position - 1));
	hd44780_active = 0;
	controlLEDs_enable(1);
}

void hd44780_rewrite_string(const char *s) {
	hd44780_goto(1,1);
	hd44780_write_string(s);
}

void hd44780_message(const char *s) {
	hd44780_clear();
	hd44780_rewrite_string(s);
}

//TODO: don't work (no center)
void hd44780_message_center(const char *s, uint8_t line) {
	hd44780_goto(line, (HD44780_DISP_LENGTH - strlen(s)) / 2 + 1);
	hd44780_write_string(s);
}

void hd44780_load_symbol(uint8_t addr, const uint8_t * data) {
//	hd44780_wr_cmd((addr<<3)+0b10000000);
	hd44780_cgram_addr(addr);
	for (uint8_t i = 0; i < 8; i++)
		hd44780_write_char(data[i]);
//	hd44780_ddram_addr(0);
}

void hd44780_show_temp_msg(const char *line1, const char *line2) {
	if (showingTemp)
		return;
	showingTemp = 1;

	hd44780_wr_cmd(HD44780_CMD_CLEAR);

	hd44780_goto_noblock(1, (HD44780_DISP_LENGTH - strlen(line1)) / 2 + 1);
	for (uint8_t i = 0; line1[i] != '\0'; ++i)
		hd44780_wr_data_noblock(line1[i]);

	hd44780_goto_noblock(2, (HD44780_DISP_LENGTH - strlen(line2)) / 2 + 1);
	for (uint8_t i = 0; line2[i] != '\0'; ++i)
		hd44780_wr_data_noblock(line2[i]);
}

void hd44780_remove_temp_msg() {
	hd44780_goto_noblock(1, 1);
	for (uint8_t i = 0; i < HD44780_DISP_LENGTH; i++)
		hd44780_wr_data_noblock(buffer[i]);

	hd44780_goto_noblock(2, 1);
	for (uint8_t i = 0; i < HD44780_DISP_LENGTH; i++)
		hd44780_wr_data_noblock(buffer[i + HD44780_DISP_LENGTH]);

	hd44780_goto_noblock(currentPos / HD44780_DISP_LENGTH + 1, currentPos % HD44780_DISP_LENGTH + 1);

	showingTemp = 0;
}
#ifdef WS0010_GRAPHICS

void ws0010_Graphics_mode(){
	hd44780_wr_cmd(WS0010_GRAPHICS_MODE_ON | WS0010_INTERNAL_POWER_ON);
}

void ws0010_Character_mode(){
	hd44780_wr_cmd (WS0010_GHARACTER_MODE_ON | WS0010_INTERNAL_POWER_ON);
}

void ws0010_Draw(uint8_t x, uint8_t y, uint8_t data){
	hd44780_ddram_addr(x);
	hd44780_cgram_addr(y);
	hd44780_wr_data_noblock(data);
}



void ws0010_Draw_buffer(const uint8_t *buffer ){ //put buffer to display as quick is possible
	uint8_t i;
	hd44780_ddram_addr(0);
	hd44780_cgram_addr(0);
    for (i=0; i<80; i++){
		hd44780_wr_data_noblock(buffer[(i<<1)+1]);
    }
	hd44780_ddram_addr(0);
	hd44780_cgram_addr(1);
    for (i=0; i<80; i++){
		hd44780_wr_data_noblock(buffer[i<<1]);
    }
}

#endif

