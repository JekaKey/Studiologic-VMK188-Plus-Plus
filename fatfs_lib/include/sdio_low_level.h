#ifndef SDIO_LOW_LEVEL_H_
#define SDIO_LOW_LEVEL_H_

#include <stm32f4xx.h>

#define IO16_Pin_ALL_LSB           0x00FF
#define IO16_Pin_ALL_MSB           0xFF00

/**
 * @brief  GPIO Registers
 */
#define IOE16_REG_GPMR_LSB         0x10
#define IOE16_REG_GPMR_MSB         0x11
#define IOE16_REG_GPSR_LSB         0x12
#define IOE16_REG_GPSR_MSB         0x13
#define IOE16_REG_GPDR_LSB         0x14
#define IOE16_REG_GPDR_MSB         0x15
#define IOE16_REG_GPPIR_LSB        0x16
#define IOE16_REG_GPPIR_MSB        0x17

/**
 * @brief  SD FLASH SDIO Interface
 */
#define SDIO_FIFO_ADDRESS             ((uint32_t)0x40012C80)
/**
 * @brief  SDIO Intialization Frequency (400KHz max)
 */

#define SDIO_INIT_CLK_DIV             ((uint8_t)0x76)

/**
 * @brief  SDIO Data Transfer Frequency (25MHz max)
 */
//#define SDIO_TRANSFER_CLK_DIV         ((uint8_t)0x0)
#define SDIO_TRANSFER_CLK_DIV         ((uint8_t)0x76)

#define SD_SDIO_DMA                   DMA2
#define SD_SDIO_DMA_CLK               RCC_AHB1Periph_DMA2

#define SD_SDIO_DMA_STREAM3             3

#ifdef SD_SDIO_DMA_STREAM3
#define SD_SDIO_DMA_STREAM            DMA2_Stream3
#define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
#define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF3
#define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF3
#define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF3
#define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF3
#define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF3
#define SD_SDIO_DMA_IRQn              DMA2_Stream3_IRQn
#define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream3_IRQHandler
#elif defined SD_SDIO_DMA_STREAM6
#define SD_SDIO_DMA_STREAM            DMA2_Stream6
#define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
#define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF6
#define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF6
#define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF6
#define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF6
#define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF6
#define SD_SDIO_DMA_IRQn              DMA2_Stream6_IRQn
#define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream6_IRQHandler
#endif /* SD_SDIO_DMA_STREAM3 */

void SD_LowLevel_DeInit (void);
void SD_LowLevel_Init (void);
void SD_LowLevel_DMA_TxConfig (uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig (uint32_t *BufferDST, uint32_t BufferSize);
uint8_t IOE16_MonitorIOPin (uint16_t IO_Pin);

#endif /* SDIO_LOW_LEVEL_H_ */
