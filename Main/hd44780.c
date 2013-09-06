#include "hd44780.h"

void hd44780_wr_hi_nibble( uint8_t data ) {

    if ( data & 0x10 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    }
    if ( data & 0x20 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    }
    if ( data & 0x40 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    }
    if ( data & 0x80 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    }

    /* set the EN signal */
    hd44780_EN_On();

    /* wait */
    hd44780_EN_high_delay();

    /* reset the EN signal */
    hd44780_EN_Off();

}


#if HD44780_CONF_BUS == HD44780_FUNC_BUS_4BIT

void hd44780_wr_lo_nibble( uint8_t data ) {

    if ( data & 0x01 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    }
    if ( data & 0x02 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    }
    if ( data & 0x04 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    }
    if ( data & 0x08 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    }

    /* set the EN signal */
    hd44780_EN_On();

    /* wait */
    hd44780_EN_high_delay();

    /* reset the EN signal */
    hd44780_EN_Off();

}


/* 4bit bus version */
void hd44780_write( uint8_t data ) {
    /* send the data bits - high nibble first */
    hd44780_wr_hi_nibble( data );
    hd44780_wr_lo_nibble( data );

}
#endif /* HD44780_CONF_BUS == HD44780_FUNC_BUS_4BIT */


#if HD44780_CONF_BUS == HD44780_FUNC_BUS_8BIT

/* 8bit bus version */
void hd44780_write( uint8_t data ) {
    /* set the data bits */
    if ( data & 0x01 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT0 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT0 );
    }
    if ( data & 0x02 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT1 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT1 );
    }
    if ( data & 0x04 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT2 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT2 );
    }
    if ( data & 0x08 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT3 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT3 );
    }
    if ( data & 0x10 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
    }
    if ( data & 0x20 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
    }
    if ( data & 0x40 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
    }
    if ( data & 0x80 ) {
        GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    } else {
        GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
    }

    /* tell the lcd that we have a command to read in */
    hd44780_EN_On();

    /* wait long enough so that the lcd can see the command */
    hd44780_EN_high_delay();

    /* reset the ce line */
    hd44780_EN_Off();
    hd44780_init_end_delay();

}
#endif /* HD44780_CONF_BUS == HD44780_FUNC_BUS_8BIT */


void hd44780_wr_cmd( uint8_t cmd ) {
    hd44780_RS_Off();
    hd44780_write( cmd );
}


void hd44780_wr_data( uint8_t data ) {
    hd44780_RS_On();
    hd44780_write( data );
}


void hd44780_init( void ) {
    /* clear control bits */
    hd44780_EN_Off();
    hd44780_RS_Off();
    hd44780_RW_Off();

    /* wait initial delay for LCD to settle */
    /* reset procedure - 3 function calls resets the device */
    hd44780_init_delay();
    hd44780_wr_hi_nibble( HD44780_CMD_RESET );
    hd44780_init_delay2();
    hd44780_wr_hi_nibble( HD44780_CMD_RESET );
    hd44780_init_delay3();
    hd44780_wr_hi_nibble( HD44780_CMD_RESET );

#if HD44780_CONF_BUS == HD44780_FUNC_BUS_4BIT
    /* 4bit interface */
    hd44780_wr_hi_nibble( HD44780_CMD_FUNCTION );
#endif /* HD44780_CONF_BUS == HD44780_FUNC_BUS_4BIT */

    /* sets the configured values - can be set again only after reset */
    hd44780_function( HD44780_CONF_BUS, HD44780_CONF_LINES, HD44780_CONF_FONT );

    /* turn the display off with no cursor or blinking */
    hd44780_display( HD44780_DISP_OFF, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF );

    /* clear the display */
    hd44780_clear();

    /* addr increment, shift cursor */
    hd44780_entry( HD44780_ENTRY_ADDR_INC, HD44780_ENTRY_SHIFT_DISP );

}


void hd44780_write_string( char *s ) {
    uint32_t i;
    for ( i = 0; s[i] != '\0'; ++i ) {
        hd44780_write_char( s[i] );
    }
}


void hd44780_write_line( uint8_t line, char *msg ) {
    if ( line >= HD44780_DISP_ROWS ) return;
    /* TODO: dokonèi... */
}

