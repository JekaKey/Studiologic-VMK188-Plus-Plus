/**
 ******************************************************************************
 * @author  MCD Application Team (modified by lukasz.iwaszkiewicz@gmail.com)
 * @version V1.0.3
 * @date    13-November-2013
 * @brief   This file provides
 *            - set of firmware functions to manage Leds, push-button and COM ports
 *            - low level initialization functions for SD card (on SDIO) and EEPROM
 *          available on STM324x9I-EVAL evaluation board(MB1045) RevB from
 *          STMicroelectronics.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>
#include "sdio_low_level.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_dma.h"

/**
 * @brief  DeInitializes the SDIO interface.
 * @param  None
 * @retval None
 */
void SD_LowLevel_DeInit (void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        /*!< Disable SDIO Clock */
        SDIO_ClockCmd (DISABLE);

        /*!< Set Power State to OFF */
        SDIO_SetPowerState (SDIO_PowerState_OFF);

        /*!< DeInitializes the SDIO peripheral */
        SDIO_DeInit ();

        /* Disable the SDIO APB2 Clock */
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_SDIO, DISABLE);

        GPIO_PinAFConfig (GPIOC, GPIO_PinSource8, GPIO_AF_MCO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource9, GPIO_AF_MCO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource10, GPIO_AF_MCO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource11, GPIO_AF_MCO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource12, GPIO_AF_MCO);
        GPIO_PinAFConfig (GPIOD, GPIO_PinSource2, GPIO_AF_MCO);

        /* Configure PC.08, PC.09, PC.10, PC.11 pins: D0, D1, D2, D3 pins */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init (GPIOC, &GPIO_InitStructure);

        /* Configure PD.02 CMD line */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init (GPIOD, &GPIO_InitStructure);

        /* Configure PC.12 pin: CLK pin */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_Init (GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Initializes the SD Card and put it into StandBy State (Ready for
 *         data transfer).
 * @param  None
 * @retval None
 */
void SD_LowLevel_Init (void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        /* GPIOC and GPIOD Periph clock enable */
        RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

        GPIO_PinAFConfig (GPIOC, GPIO_PinSource8, GPIO_AF_SDIO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource9, GPIO_AF_SDIO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource10, GPIO_AF_SDIO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource11, GPIO_AF_SDIO);
        GPIO_PinAFConfig (GPIOC, GPIO_PinSource12, GPIO_AF_SDIO);
        GPIO_PinAFConfig (GPIOD, GPIO_PinSource2, GPIO_AF_SDIO);

        /* Configure PC.08, PC.09, PC.10, PC.11 pins: D0, D1, D2, D3 pins */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init (GPIOC, &GPIO_InitStructure);

        /* Configure PD.02 CMD line */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init (GPIOD, &GPIO_InitStructure);

        /* Configure PC.12 pin: CLK pin */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init (GPIOC, &GPIO_InitStructure);

        /* Enable the SDIO APB2 Clock */
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_SDIO, ENABLE);

        /* Enable the DMA2 Clock */
        RCC_AHB1PeriphClockCmd (SD_SDIO_DMA_CLK, ENABLE);
}

/**
 * @brief  Configures the DMA2 Channel4 for SDIO Tx request.
 * @param  BufferSRC: pointer to the source buffer
 * @param  BufferSize: buffer size
 * @retval None
 */
void SD_LowLevel_DMA_TxConfig (uint32_t *BufferSRC, uint32_t BufferSize)
{
        DMA_InitTypeDef SDDMA_InitStructure;

        DMA_ClearFlag (SD_SDIO_DMA_STREAM, SD_SDIO_DMA_FLAG_FEIF | SD_SDIO_DMA_FLAG_DMEIF | SD_SDIO_DMA_FLAG_TEIF | SD_SDIO_DMA_FLAG_HTIF | SD_SDIO_DMA_FLAG_TCIF);

        /* DMA2 Stream3  or Stream6 disable */
        DMA_Cmd (SD_SDIO_DMA_STREAM, DISABLE);

        /* DMA2 Stream3  or Stream6 Config */
        DMA_DeInit (SD_SDIO_DMA_STREAM );

        SDDMA_InitStructure.DMA_Channel = SD_SDIO_DMA_CHANNEL;
        SDDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) SDIO_FIFO_ADDRESS;
        SDDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) BufferSRC;
        SDDMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
        SDDMA_InitStructure.DMA_BufferSize = 1;
        SDDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        SDDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        SDDMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
        SDDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
        SDDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        SDDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        SDDMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
        SDDMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
        SDDMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC4;
        SDDMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_INC4;
        DMA_Init (SD_SDIO_DMA_STREAM, &SDDMA_InitStructure);
        DMA_ITConfig (SD_SDIO_DMA_STREAM, DMA_IT_TC, ENABLE);
        DMA_FlowControllerConfig (SD_SDIO_DMA_STREAM, DMA_FlowCtrl_Peripheral);

        /* DMA2 Stream3  or Stream6 enable */
        DMA_Cmd (SD_SDIO_DMA_STREAM, ENABLE);

}
/**
 * @brief  Configures the DMA2 Channel4 for SDIO Rx request.
 * @param  BufferDST: pointer to the destination buffer
 * @param  BufferSize: buffer size
 * @retval None
 */
void SD_LowLevel_DMA_RxConfig (uint32_t *BufferDST, uint32_t BufferSize)
{
        DMA_InitTypeDef SDDMA_InitStructure;

        DMA_ClearFlag (SD_SDIO_DMA_STREAM, SD_SDIO_DMA_FLAG_FEIF | SD_SDIO_DMA_FLAG_DMEIF | SD_SDIO_DMA_FLAG_TEIF | SD_SDIO_DMA_FLAG_HTIF | SD_SDIO_DMA_FLAG_TCIF);

        /* DMA2 Stream3  or Stream6 disable */
        DMA_Cmd (SD_SDIO_DMA_STREAM, DISABLE);

        /* DMA2 Stream3 or Stream6 Config */
        DMA_DeInit (SD_SDIO_DMA_STREAM );

        SDDMA_InitStructure.DMA_Channel = SD_SDIO_DMA_CHANNEL;
        SDDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) SDIO_FIFO_ADDRESS;
        SDDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) BufferDST;
        SDDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
        SDDMA_InitStructure.DMA_BufferSize = 1;
        SDDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        SDDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        SDDMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
        SDDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
        SDDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        SDDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        SDDMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
        SDDMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
        SDDMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC4;
        SDDMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_INC4;
        DMA_Init (SD_SDIO_DMA_STREAM, &SDDMA_InitStructure);
        DMA_ITConfig (SD_SDIO_DMA_STREAM, DMA_IT_TC, ENABLE);
        DMA_FlowControllerConfig (SD_SDIO_DMA_STREAM, DMA_FlowCtrl_Peripheral);

        /* DMA2 Stream3 or Stream6 enable */
        DMA_Cmd (SD_SDIO_DMA_STREAM, ENABLE);
}

