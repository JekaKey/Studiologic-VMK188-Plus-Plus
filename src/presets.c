#include "presets.h"

void preset_load() {

	//load preset data
	memory_page_to_buffer(1, 10);
	memory_page_to_buffer(2, 11);

	preset.Id = 1;

//	for (uint8_t var = 0; var < 16; ++var) {
//		preset.Name[var] = memory_read_8bit(1, var + 2);
//	}

	preset.MidiChannel = 0;
	preset.HighResEnable = 1;

}

void memory_start() {
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

void memory_stop() {
	GPIO_SetBits(GPIOC, GPIO_Pin_3);
}

uint8_t memory_transfer_data(uint8_t data) {
	SPI1->DR = data; // write data to be transmitted to the SPI data register
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE))
		; // wait until transmit complete
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE))
		; // wait until receive complete
	while (SPI1->SR & SPI_I2S_FLAG_BSY)
		; // wait until SPI is not busy anymore
	return SPI1->DR; // return received data from SPI data register
}

/**
 * Read current memory status
 */
uint8_t memory_ready_status() {
	uint8_t temp;

	memory_start();
	memory_transfer_data(0xD7);
	temp = memory_transfer_data(0x00);
	memory_stop();

	return temp;
}

void memory_wait_ready() {
	uint8_t MEM_status;

	do {
		MEM_status = memory_ready_status();
	} while (!(MEM_status & 0x80));

}

void memory_send_command(uint8_t opcode, uint8_t adress_byte1, uint8_t adress_byte2, uint8_t adress_byte3) {

}

/**
 * Transfer page data to buffer 1 or 2
 */
void memory_page_to_buffer(uint8_t buffer, uint16_t target_number_page) {

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0x53); // Command - Buffer 1
	else
		memory_transfer_data(0x55); // Command - Buffer 2

	memory_transfer_data(target_number_page >> 7); // Address - x x x P P P P P
	memory_transfer_data(target_number_page << 1); // Address - P P P P P P P x
	memory_transfer_data(0x00); // Address - x x x x x x x x

	memory_stop(); //CS memory

	memory_wait_ready(); //Wait for ready

}

/**
 * Save buffered page into memory
 */
void memory_buffer_to_page(uint8_t buffer, uint16_t target_number_page) {

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0x83); // Command - Buffer 1
	else
		memory_transfer_data(0x86); // Command - Buffer 2

	memory_transfer_data(target_number_page >> 7); // Address - x x x P P P P P
	memory_transfer_data(target_number_page << 1); // Address - P P P P P P P x
	memory_transfer_data(0x00); // Address - x x x x x x x x

	memory_stop(); //CS memory

	memory_wait_ready(); //Wait for ready

}

void memory_send_8bit_to_buffer(uint8_t buffer, uint8_t from_byte, uint8_t data) {

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0x84); // Command - Buffer 1
	else
		memory_transfer_data(0x87); // Command - Buffer 2

	memory_transfer_data(0x00); // Address - x x x x x x x x
	memory_transfer_data(0x00); // Address - x x x x x x x B
	memory_transfer_data(from_byte); // Address - B B B B B B B B

	memory_transfer_data(data);

	memory_stop(); //CS memory

}

void memory_send_16bit_to_buffer(uint8_t buffer, uint8_t from_byte, uint16_t data) {

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0x84); // Command - Buffer 1
	else
		memory_transfer_data(0x87); // Command - Buffer 2

	memory_transfer_data(0x00); // Address - x x x x x x x x
	memory_transfer_data(0x00); // Address - x x x x x x x B
	memory_transfer_data(from_byte); // Address - B B B B B B B B

	memory_transfer_data(data & 0xFF);
	memory_transfer_data((data >> 8) & 0xFF);

	memory_stop(); //CS memory

}

uint8_t memory_read_8bit(uint8_t buffer, uint8_t from_byte) {
	uint8_t return_data;

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0xD4); // Command - Buffer 1
	else
		memory_transfer_data(0xD6); // Command - Buffer 2

	memory_transfer_data(0x00); // Address - x x x x x x x x
	memory_transfer_data(0x00); // Address - x x x x x x x B
	memory_transfer_data(from_byte); // Address - B B B B B B B B

	memory_transfer_data(0x00); //Dummy byte

	return_data = memory_transfer_data(0x00); //Return data

	memory_stop(); //CS memory

	return return_data;
}

uint16_t memory_read_16bit(uint8_t buffer, uint8_t from_byte) {
	uint16_t return_data;

	memory_start(); //CS memory

	if (buffer == 1)
		memory_transfer_data(0xD4); // Command - Buffer 1
	else
		memory_transfer_data(0xD6); // Command - Buffer 2

	memory_transfer_data(0x00); // Address - x x x x x x x x
	memory_transfer_data(0x00); // Address - x x x x x x x B
	memory_transfer_data(from_byte); // Address - B B B B B B B B

	memory_transfer_data(0x00); //Dummy byte

	return_data = memory_transfer_data(0x00); //Return data

	memory_stop(); //CS memory

	return return_data;
}
