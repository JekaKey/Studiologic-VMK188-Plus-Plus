/*******************************************************************/
#define STM32F40XX

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_spi.h"
#include "misc.h"
#include "math.h"

#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define MAIN

#include "fifo.h"
#include "keyboardscan.h"
#include "midi.h"
#include "hd44780.h"

#define MIDI_BAUDRATE 31250                         //Midi speed baudrate

//USB_OTG_CORE_HANDLE USB_OTG_dev;

TIM_TimeBaseInitTypeDef timer;

uint16_t previousState;
uint8_t count;
uint16_t i;
uint16_t min = 0xFFFF;
uint16_t max = 0;
uint8_t mid = 0;

typedef struct {
    uint8_t channel;
    uint8_t event;
    uint8_t value;
    uint8_t min_in_value;
    uint8_t max_in_value;
    uint8_t min_out_value;
    uint8_t max_out_value;
    uint8_t reverse;
} Slider;

#define MAX_STRLEN 12 // this is the maximum string length of our string in characters

volatile char received_string[MAX_STRLEN + 1]; // this will hold the recieved string

void delay(volatile uint32_t c ) {
    while ( --c ) {
        __NOP();
    }
}

void delayms(volatile uint32_t c ) {
    c++;
    while ( --c ) {
        delay(23080);
    }
}

/*
* GPIO init
*/

void init_GPIO(void) {

    GPIO_InitTypeDef GPIO_InitStruct;

    /*Enable or disable the AHB1 peripheral clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);


    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIOA->PUPDR |= 0x00005555;


    /* Настройка таймера 4 */

    //Заполняем поля структуры дефолтными значениями
    TIM_TimeBaseStructInit(&timer);

    //Выставляем предделитель, 100uS
    timer.TIM_Prescaler = 84 - 1;

    //Тут значение, досчитав до которого таймер сгенерирует прерывание
    timer.TIM_Period = 50 - 1;

    //Предделитель таймера
    timer.TIM_ClockDivision = 0;
    //Инициализируем TIM4 нашими значениями
    TIM_TimeBaseInit(TIM4, &timer);

}


void init_ADC() {
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef adc_init;
    /* разрешаем тактирование AЦП1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* сбрасываем настройки АЦП */
    ADC_DeInit();

    /* АЦП работают независимо */
    adc_init.ADC_Mode = ADC_Mode_Independent;
    adc_init.ADC_Prescaler = ADC_Prescaler_Div2;

    /* выключаем scan conversion */
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    /* Не делать длительные преобразования */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

    /* Начинать преобразование программно, а не по срабатыванию тригера */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
    /* 12 битное преобразование. результат в 12 младших разрядах результата */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    /* инициализация */
    ADC_CommonInit(&adc_init);

    ADC_Init(ADC1, &ADC_InitStructure);
    /* Включаем АЦП1 */
    ADC_Cmd(ADC1, ENABLE);

}

/*******************************************************************/

/* This funcion initializes the USART1 peripheral
 *
 * Arguments: baudrate --> the baudrate at which the USART is
 *                         supposed to operate
 */
void init_USART1(uint32_t baudrate) {

    /* This is a concept that has to do with the libraries provided by ST
     * to make development easier the have made up something similar to
     * classes, called TypeDefs, which actually just define the common
     * parameters that every peripheral needs to work correctly
     *
     * They make our life easier because we don't have to mess around with
     * the low level stuff of setting bits in the correct registers
     */
    GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
    USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
    // NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

    /* enable APB2 peripheral clock for USART1
     * note that only USART1 and USART6 are connected to APB2
     * the other USARTs are connected to APB1
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* enable the peripheral clock for the pins used by
     * USART1, PB6 for TX and PB7 for RX
     */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* This sequence sets up the TX and RX pins
     * so they work correctly with the USART1 peripheral
     */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pins 6 (TX) and 7 (RX) are used
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;           // the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;      // this defines the IO speed and has nothing to do with the baudrate!
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;         // this defines the output type as push pull mode (as opposed to open drain)
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;           // this activates the pullup resistors on the IO pins
    GPIO_Init(GPIOB, &GPIO_InitStruct);                 // now all the values are passed to the GPIO_Init() function which sets the GPIO registers

    /* The RX and TX pins are now connected to their AF
     * so that the USART1 can take over control of the
     * pins
     */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); //
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    /* Now the USART_InitStruct is used to define the
     * properties of USART1
     */
    USART_InitStruct.USART_BaudRate = baudrate;             // the baudrate is set to the value we passed into this init function
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
    USART_InitStruct.USART_StopBits = USART_StopBits_1;     // we want 1 stop bit (standard)
    USART_InitStruct.USART_Parity = USART_Parity_No;        // we don't want a parity bit (standard)
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver
    USART_Init(USART1, &USART_InitStruct);                  // again all the properties are passed to the USART_Init function which takes care of all the bit setting


    /* Here the USART1 receive interrupt is enabled
     * and the interrupt controller is configured
     * to jump to the USART1_IRQHandler() function
     * if the USART1 receive interrupt occurs
     */
    //  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt

    //  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;        // we want to configure the USART1 interrupts
    //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
    //  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       // this sets the subpriority inside the group
    //  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          // the USART1 interrupts are globally enabled
    //  NVIC_Init(&NVIC_InitStructure);                          // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    // finally this enables the complete USART1 peripheral
    USART_Cmd(USART1, ENABLE);
}

void USART_puts(USART_TypeDef *USARTx, volatile char *s) {

    while (*s) {
        // wait until data register is empty
        while ( !(USARTx->SR & 0x00000040) );
        USART_SendData(USARTx, *s);
        *s++;
    }
}

/**
* First init
*/
void firstInit() {

    init_GPIO();                //GPIO init
    init_USART1(MIDI_BAUDRATE); //Midi init

//       USBD_Init(&USB_OTG_dev,
// #ifdef USE_USB_OTG_HS 
//             USB_OTG_HS_CORE_ID,
// #else            
//             USB_OTG_FS_CORE_ID,
// #endif 
//             &USR_desc, 
//             &AUDIO_cb, 
//             &USR_cb);
      
    //First port init, all for high
    GPIOB->BSRRL = 0xFC07;  // B0-B2, B10-B15
    GPIOC->BSRRL = 0x30;    // C4-C5
    GPIOD->BSRRL = 0x300;   // D8-D9
    GPIOE->BSRRL = 0xFF80;  // E7-E15

    //Настраиваем таймер для генерации прерывания по обновлению (переполнению)
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    //Запускаем таймер
    TIM_Cmd(TIM4, ENABLE);

    //Разрешаем соответствующее прерывание
    NVIC_EnableIRQ(TIM4_IRQn);

}

uint16_t readADC1(uint8_t channel) {
    delay(1000);
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_56Cycles);
    // начинаем работу
    delay(1000);
    ADC_SoftwareStartConv(ADC1);
    delay(1000);
    ADC_SoftwareStartInjectedConv(ADC1);
    delay(1000);
    // ждём пока преобразуется напряжение в код
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {}
    delay(1000);
    // очищаем статус
    // ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    // возвращаем результат
    return ADC_GetConversionValue(ADC1);
}

/**DocID022945 Rev 4 29/33
AN4073 Averaging of N-X ADC samples: source code
 * @brief Sort the N ADC samples
 * @param ADC samples to be sorted
 * @param Numbre of ADC samples to be sorted
 * @retval None
 */
void Sort_tab(uint16_t tab[], uint8_t lenght) {
    uint8_t l = 0x00, exchange = 0x01;
    uint16_t tmp = 0x00;
    /* Sort tab */
    while (exchange == 1) {
        exchange = 0;
        for (l = 0; l < lenght - 1; l++) {
            if ( tab[l] > tab[l + 1] ) {
                tmp = tab[l];
                tab[l] = tab[l + 1];
                tab[l + 1] = tmp;
                exchange = 1;
            }
        }
    }
}

/**
 * @brief Get the average of N-X ADC samples
 * @param Numbre of ADC samples to be averaged
 * @param Numbre of ADC samples to be averaged
 * @retval The average value
 */
uint16_t ADC_GetSampleAvgNDeleteX(uint8_t N , uint8_t X) {
    uint32_t avg_sample = 0x00;
    uint16_t adc_sample[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t index = 0x00;
    for (index = 0x00; index < N; index++) {
        /* ADC start conv */
        ADC_SoftwareStartConv(ADC1);
        /* Wait end of conversion */
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
        /* Store ADC samples */
        // adc_sample[index] = ADC_GetConversionValue(ADC1);
        adc_sample[index] = readADC1(ADC_Channel_10);
    }
    /* Sort the N-X ADC samples */
    Sort_tab(adc_sample, N);
    /* Add the N ADC samples */
    for (index = X / 2; index < N - X / 2; index++) {
        avg_sample += adc_sample[index];
    }
    /* Compute the average of N-X ADC sample */
    avg_sample /= N - X;
    /* Return average value */
    return avg_sample;
}


uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int main(void) {
    //      uint32_t i;
    firstInit();

    init_ADC();                                 //ADC init

    //USART_puts(USART1, "Init complete! Hello World!rn"); //Тестовая мессага

    //Тестовый кусок для Константина, отправляем  noteOn при включении
    //sendNoteOn(56, 90, 0);
    delayms(400);
    hd44780_init();
    hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_ON, HD44780_DISP_BLINK_OFF );


    hd44780_write_string("FATARMINATOR");
    hd44780_goto(2, 4);
    hd44780_write_string("PROJECT  v0.1");

    GPIO_SetBits(GPIOD, GPIO_Pin_15);

    /* Основной цикл программы */
    while (1) {

        //Проверяем, если ли считанные ноты
        checkNoteArray();

        //Проверка и отправка буффера midi сообщений
        sendMidiData();

        // count = FIFO_COUNT(midiMessagesArray);

        // i = ADC_GetSampleAvgNDeleteX(8, 6) >> 1;

        //        if (i != sliders.value) {
        //                  __NOP();
        //            sliders.value = i;
        //            sendControlChange(64,i,0);
        //        }

    }
}

// this is the interrupt request handler (IRQ) for ALL USART1 interrupts
void USART1_IRQHandler(void) {

    // check if the USART1 receive interrupt flag was set
    if ( USART_GetITStatus(USART1, USART_IT_RXNE) ) {

        static uint8_t cnt = 0; // this counter is used to determine the string length
        char t = USART1->DR; // the character from the USART1 data register is saved in t

        /* check if the received character is not the LF character (used to determine end of string)
         * or the if the maximum string length has been been reached
         */
        if ( (t != 'n') && (cnt < MAX_STRLEN) ) {
            received_string[cnt] = t;
            cnt++;
        } else { // otherwise reset the character counter and print the received string
            cnt = 0;
            USART_puts(USART1, received_string);
        }
    }
}

/**
Таймер для чтения состояния клавиш
**/

void TIM4_IRQHandler() {
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {

        //Очищаем бит
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

        // GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
        //Считываем состояние клавиш
        readKeyState();
    }
}
