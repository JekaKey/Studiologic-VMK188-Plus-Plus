#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "log.h"


__attribute__ ((section (".noinit"))) volatile uint32_t boot_flag;


void BootLoaderStart(void) {

	void (*SysMemBootJump)(void) = (void (*)(void)) (*((uint32_t *) 0x1FFF0004));
		if (boot_flag==0xE4E4E4E4) {
			boot_flag = 0;
		RCC_DeInit();
		SysTick->CTRL = 0;
		SysTick->LOAD = 0;
		SysTick->VAL = 0;
		//__set_PRIMASK(1);
		//RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
		__set_MSP(0x20001000);
		SysMemBootJump();
		}
	}


void gotoBootLoader(void){
	boot_flag=0xE4E4E4E4;
	NVIC_SystemReset();
}
