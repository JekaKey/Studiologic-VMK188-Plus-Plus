/**
 * GPIO and peripheral configuration
 */

void GPIO_init();	//Configuration all in\out pin
//void SPI1_init(); 	//Configuration SPI1 on PB3,PB4,PB5 pin to use memory
void USART1_init(); //Configuration USART1 on PB6,PB7 pin to send\receive midi message via midi cable

void USART6_init(); //Configuration USART6 on PC6,PC7 pin to send\receive debug port
