//#ifndef STM32F40XX
//#define STM32F40XX
#ifndef _HD44780_H_
#define _HD44780_H_

// #include <stdint.h>
#include "stm32f4xx.h"
#include <stm32f4xx_gpio.h>


/***************************************************************
 *
 * CONSTANTS
 *
 ***************************************************************/

/* COMMANDS */
#define HD44780_CMD_RESET               0x30     /*!< Resets display - used in init 3x */
#define HD44780_CMD_CLEAR               0x01     /*!< Clears display */
#define HD44780_CMD_RETURN_HOME         0x02     /*!< Sets DDRAM pointer to 0 */
#define HD44780_CMD_ENTRY_MODE          0x04     /*!< Sets how the pointer is updated after a character write */
#define HD44780_CMD_DISPLAY             0x08     /*!< Display settings */
#define HD44780_CMD_SHIFT               0x10     /*!< Cursor and display movement */
#define HD44780_CMD_FUNCTION            0x20     /*!< Screen type setup */
#define HD44780_CMD_CGRAM_ADDR          0x40     /*!< Sets CGRAM address */
#define HD44780_CMD_DDRAM_ADDR          0x80     /*!< Sets DDRAM address */

/* ENTRY_MODE Command parameters */
#define HD44780_ENTRY_SHIFT_DISP        0x01     /*!< Shift display */
#define HD44780_ENTRY_SHIFT_CURS        0x00     /*!< Shift cursor */
#define HD44780_ENTRY_ADDR_INC          0x02     /*!< Increments pointer */
#define HD44780_ENTRY_ADDR_DEC          0x00     /*!< Decrements pointer */

/* DISPLAY Command parameters */
#define HD44780_DISP_ON                 0x04      /*!< Enables the display */
#define HD44780_DISP_OFF                0x00      /*!< Disables the display */
#define HD44780_DISP_CURS_ON            0x02      /*!< Enables cursor */
#define HD44780_DISP_CURS_OFF           0x00      /*!< Disables cursor */
#define HD44780_DISP_BLINK_ON           0x01      /*!< Enables cursor blinking */
#define HD44780_DISP_BLINK_OFF          0x00      /*!< Disables cursor blinking */

/* SHIFT Command parameters */
#define HD44780_SHIFT_DISPLAY           0x08      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_CURSOR            0x00      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_RIGHT             0x04      /*!< Shift to the right */
#define HD44780_SHIFT_LEFT              0x00      /*!< Shift to the left  */

/* FUNCTION Command parameters */
#define HD44780_FUNC_BUS_8BIT           0x10      /*!< 8 bit bus */
#define HD44780_FUNC_BUS_4BIT           0x00      /*!< 4 bit bus */
#define HD44780_FUNC_LINES_2            0x08      /*!< 2 lines */
#define HD44780_FUNC_LINES_1            0x00      /*!< 1 line */
#define HD44780_FUNC_FONT_5x10          0x04      /*!< 5x10 font */
#define HD44780_FUNC_FONT_5x8           0x00      /*!< 5x8 font */

/* Busy Flag - actually not used */
#define HD44780_BUSY_FLAG               0x80      /*!< Busy flag */


/***************************************************************
 *
 * CONFIGURATION
 *
 ***************************************************************/

#define HD44780_CONF_BUS            HD44780_FUNC_BUS_8BIT
#define HD44780_CONF_LINES          HD44780_FUNC_LINES_2
#define HD44780_CONF_FONT           HD44780_FUNC_FONT_5x8

#define HD44780_DISP_LENGTH         16
#define HD44780_DISP_ROWS           2
#define HD44780_CONF_SCROLL_MS      20

#define HD44780_DATAPORT            GPIOE
#define HD44780_DATABIT0            GPIO_Pin_0
#define HD44780_DATABIT1            GPIO_Pin_1
#define HD44780_DATABIT2            GPIO_Pin_2
#define HD44780_DATABIT3            GPIO_Pin_3
#define HD44780_DATABIT4            GPIO_Pin_4
#define HD44780_DATABIT5            GPIO_Pin_5
#define HD44780_DATABIT6            GPIO_Pin_6
#define HD44780_DATABIT7            GPIO_Pin_7

#define HD44780_RS_PORT             GPIOB
#define HD44780_RS_BIT              GPIO_Pin_8
//#define HD44780_RW_PORT             GPIOB
//#define HD44780_RW_BIT              GPIO_Pin_6
#define HD44780_EN_PORT             GPIOB
#define HD44780_EN_BIT              GPIO_Pin_9


/***************************************************************
 *
 * FUNCTIONS
 *
 ***************************************************************/

#define hd44780_RS_On()                 GPIO_SetBits( HD44780_RS_PORT, HD44780_RS_BIT )
#define hd44780_RS_Off()                GPIO_ResetBits( HD44780_RS_PORT, HD44780_RS_BIT )
#define hd44780_RW_On()                 GPIO_SetBits( HD44780_RW_PORT, HD44780_RW_BIT )
#define hd44780_RW_Off()                GPIO_ResetBits( HD44780_RW_PORT, HD44780_RW_BIT )
#define hd44780_EN_On()                 GPIO_SetBits( HD44780_EN_PORT, HD44780_EN_BIT )
#define hd44780_EN_Off()                GPIO_ResetBits( HD44780_EN_PORT, HD44780_EN_BIT )


#define hd44780_EN_high_delay()         delay( 1250 )
#define hd44780_init_delay()            delayms( 16 )
#define hd44780_init_delay2()           delayms( 5 )
#define hd44780_init_delay3()           delayms( 1 )
//#define hd44780_init_end_delay()        delayms( 1 )
#define hd44780_init_end_delay()        delay( 6000 )

#define hd44780_clear()                           hd44780_wr_cmd( HD44780_CMD_CLEAR )
#define hd44780_home()                            hd44780_wr_cmd( HD44780_CMD_RETURN_HOME )
#define hd44780_entry( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_ENTRY_MODE | inc_dec | shift ) & 0x07 )
#define hd44780_display( on_off, cursor, blink )  hd44780_wr_cmd( ( HD44780_CMD_DISPLAY | on_off | cursor | blink ) & 0x0F )
#define hd44780_shift( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_SHIFT | inc_dec | shift ) & 0x1F )
#define hd44780_function( bus, lines, font )      hd44780_wr_cmd( ( HD44780_CMD_FUNCTION | bus | lines | font ) & 0x3F )
#define hd44780_cgram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_CGRAM_ADDR | ( addr & 0x3F ) )
#define hd44780_ddram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_DDRAM_ADDR | ( (addr) & 0x7F ) )
#define hd44780_write_char( c )                   hd44780_wr_data( c & 0xff )

void hd44780_wr_cmd( uint8_t );
void hd44780_wr_data( uint8_t );
void hd44780_init( void );
void hd44780_write_string( const char *s );
void hd44780_write_line( uint8_t line, char *msg );
void hd44780_goto( uint8_t line, uint8_t position);
void hd44780_rewrite_string( const char *s );
void delay( uint32_t c );
void delayms( uint32_t c );
void hd44780_message(const char *s);
void hd44780_message_center(const char *s, uint8_t line);
void hd44780_load_symbol(uint8_t addr, const uint8_t * data);

#endif /* !_HD44780_H_ */
