/*******************************************************************/
#define STM32F40XX //test

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "math.h"

#include "system_stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "core_cm4.h"

#define MAIN

#include "main.h"
#include "fifo.h"
#include "midi.h"

#define MIDI_BAUDRATE 31250                         //Midi speed baudrate
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))     //Check bit in position

FIFO8(8) notes;         //Array for current note
FIFO16(8) durations;    //Array for duration for current note

TIM_TimeBaseInitTypeDef timer;

uint16_t previousState;
uint8_t curNote;
uint16_t duration;

#define MAX_STRLEN 12 // this is the maximum string length of our string in characters

volatile char received_string[MAX_STRLEN + 1]; // this will hold the recieved string

void Delay(__IO uint32_t nCount) {
    while (nCount--) {
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
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Настройка таймера 4 */

    //Заполняем поля структуры дефолтными значениями
    TIM_TimeBaseStructInit(&timer);

    //Выставляем предделитель, 100uS
    //timer.TIM_Prescaler = (uint16_t) ((SystemCoreClock / 7) / 2624) - 1;
    timer.TIM_Prescaler = 1;

    //Тут значение, досчитав до которого таймер сгенерирует прерывание
    timer.TIM_Period = 1343;

    //Предделитель таймера
    timer.TIM_ClockDivision = 0;
    //Инициализируем TIM4 нашими значениями
    TIM_TimeBaseInit(TIM4, &timer);

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
    init_USART1(9600);          //Midi init

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
/**
* Отправка миди данных из буффера
*/
void sendMidiData(void) {
    if (FIFO_COUNT(midiMessagesArray) > 0) {
        if ((USART1->SR & 0x00000040)) {
            USART_SendData(USART1, FIFO_FRONT(midiMessagesArray));
            FIFO_POP(midiMessagesArray);
        }
    }
}

//Пересчет тиков в велосити
//velocity=round(a/(x1+b)+c)
uint8_t getVelocity(uint16_t tickNum) {

    uint16_t minTickVelocity = 36;
    uint16_t maxTickVelocity = 990;
    uint8_t velocity;

    if (tickNum >= maxTickVelocity)
        return 0;

    if (tickNum <= minTickVelocity)
        return 127;

    velocity = ((10500 / (tickNum + 41)) - 9);

    return velocity;
}

/**
* Расчет velocity и запись в midi буффер
*/

void getNoteToVelocity(void) {

    if (FIFO_COUNT(notes) > 0) {

        curNote = FIFO_FRONT(notes);
        duration = FIFO_FRONT(durations);

        if ((curNote & 0x80) == 0) {
            sendNoteOn(curNote, getVelocity(duration), 0);
        } else {
            sendNoteOff(curNote & 0x7F, getVelocity(duration), 0);
        }

        FIFO_POP(notes);
        FIFO_POP(durations);

    }
}

void readKeyState() {
    /* Read all contact state*/

    /* 1 chunk */

    GPIOE->BSRRH = GPIO_Pin_11;
    d11 = ~GPIOA->IDR; //Read port state first contact
    GPIOE->BSRRL = GPIO_Pin_11;

    Delay(10); //Test delay

    GPIOE->BSRRH = GPIO_Pin_12;
    d21 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_12;

    /* 2 chunk */

    // GPIOD->BSRRH = GPIO_Pin_9;
    // d12 = ~GPIOA->IDR; //Read port state first contact
    // GPIOD->BSRRL = GPIO_Pin_9;

    // GPIOE->BSRRH = GPIO_Pin_13;
    // d22 = ~GPIOA->IDR; //Read port state second contact
    // GPIOE->BSRRL = GPIO_Pin_13;

    // /* 3 chunk */

    // GPIOE->BSRRH = GPIO_Pin_15;
    // d13 = ~GPIOA->IDR; //Read port state first contact
    // GPIOE->BSRRL = GPIO_Pin_15;

    // GPIOD->BSRRH = GPIO_Pin_8;
    // d23 = ~GPIOA->IDR; //Read port state second contact
    // GPIOD->BSRRL = GPIO_Pin_8;

    // /* 4 chunk */

    // GPIOB->BSRRH = GPIO_Pin_11;
    // d14 = ~GPIOA->IDR; //Read port state first contact
    // GPIOB->BSRRL = GPIO_Pin_11;

    // GPIOB->BSRRH = GPIO_Pin_10;
    // d24 = ~GPIOA->IDR; //Read port state second contact
    // GPIOB->BSRRL = GPIO_Pin_10;

    // /* 5 chunk */

    // GPIOB->BSRRH = GPIO_Pin_15;
    // d15 = ~GPIOA->IDR; //Read port state first contact
    // GPIOB->BSRRL = GPIO_Pin_15;

    // GPIOE->BSRRH = GPIO_Pin_14;
    // d25 = ~GPIOA->IDR; //Read port state second contact
    // GPIOE->BSRRL = GPIO_Pin_14;

    // /* 6 chunk */

    // GPIOB->BSRRH = GPIO_Pin_13;
    // d16 = ~GPIOA->IDR; //Read port state first contact
    // GPIOB->BSRRL = GPIO_Pin_13;

    // GPIOB->BSRRH = GPIO_Pin_14;
    // d26 = ~GPIOA->IDR; //Read port state second contact
    // GPIOB->BSRRL = GPIO_Pin_14;

    //  7 chunk

    // GPIOC->BSRRH = GPIO_Pin_4;
    // d17 = ~GPIOA->IDR; //Read port state first contact
    // GPIOC->BSRRL = GPIO_Pin_4;

    // GPIOB->BSRRH = GPIO_Pin_12;
    // d27 = ~GPIOA->IDR; //Read port state second contact
    // GPIOB->BSRRL = GPIO_Pin_12;

    // /* 8 chunk */

    // GPIOB->BSRRH = GPIO_Pin_0;
    // d18 = ~GPIOA->IDR; //Read port state first contact
    // GPIOB->BSRRL = GPIO_Pin_0;

    // GPIOC->BSRRH = GPIO_Pin_5;
    // d28 = ~GPIOA->IDR; //Read port state second contact
    // GPIOC->BSRRL = GPIO_Pin_5;

    // /* 9 chunk */

    // GPIOB->BSRRH = GPIO_Pin_2;
    // d19 = ~GPIOA->IDR; //Read port state first contact
    // GPIOB->BSRRL = GPIO_Pin_2;

    // GPIOB->BSRRH = GPIO_Pin_1;
    // d29 = ~GPIOA->IDR; //Read port state second contact
    // GPIOB->BSRRL = GPIO_Pin_1;

    // /* 10 chunk */

    // GPIOE->BSRRH = GPIO_Pin_8;
    // d110 = ~GPIOA->IDR; //Read port state first contact
    // GPIOE->BSRRL = GPIO_Pin_8;

    // GPIOE->BSRRH = GPIO_Pin_7;
    // d210 = ~GPIOA->IDR; //Read port state second contact
    // GPIOE->BSRRL = GPIO_Pin_7;

    // /* 11 chunk */

    // GPIOE->BSRRH = GPIO_Pin_9;
    // d111 = ~GPIOA->IDR; //Read port state first contact
    // GPIOE->BSRRL = GPIO_Pin_9;

    // GPIOE->BSRRH = GPIO_Pin_10;
    // d211 = ~GPIOA->IDR; //Read port state second contact
    // GPIOE->BSRRL = GPIO_Pin_10;

    /*************************************************************************/

    /* 1 key */

    if (d11 & 0x0001) { //Первый контакт
        duration_note1++; //Увеличиваем длительность

        if (d21 & 0x0001) { //Второй контакт

            if (lastState1 & 0x0001) {
                duration_note1 = 0; //Пока нажат второй контакт, сбрасываем длительность
            } else {
                FIFO_PUSH(notes, 1); //Добавляем в ФИФО текущую ноту
                FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность

                lastState1 ^= 0x1; //Устанавливаем прошлый статус как отправлен
                duration_note1 = 0; //Сбрасываем длительность
            }

        }

    } else if (lastState1 & 0x0001) {
        FIFO_PUSH(notes, 1); //Добавляем в ФИФО текущую ноту
        FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность
        lastState1 &= 0xFFFE; //Убираем статус отправки с бита
        duration_note1 = 0; //Сброс длительности
    } else {
        duration_note1 = 0; //Сброс длительности
    }

    /*************************************************************************/
}

int main(void) {

    firstInit();

    //USART_puts(USART1, "Init complete! Hello World!rn"); //Тестовая мессага

    /* Основной цикл программы */
    while (1) {

        __NOP();

        //Проверяем буффер считанных клавиш с длительностями
        if (FIFO_COUNT(notes) > 0) {

            curNote = FIFO_FRONT(notes);
            duration = FIFO_FRONT(durations);

            if ((curNote & 0x80) == 0) {
                sendNoteOn(curNote, getVelocity(duration), 0);
            } else {
                sendNoteOff(curNote & 0x7F, getVelocity(duration), 0);
            }

            FIFO_POP(notes);
            FIFO_POP(durations);

        }

        //Проверка и отправка буффера midi сообщений
        sendMidiData();

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

        //Считываем состояние клавиш
        readKeyState();
    }
}
