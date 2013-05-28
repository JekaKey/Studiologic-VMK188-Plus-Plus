#define STM32F40XX

#include "keyboardscan.h"

/* Current port state, first contact */
uint16_t d11 = 0x00;
uint16_t d12 = 0x00;
uint16_t d13 = 0x00;
uint16_t d14 = 0x00;
uint16_t d15 = 0x00;
uint16_t d16 = 0x00;
uint16_t d17 = 0x00;
uint16_t d18 = 0x00;
uint16_t d19 = 0x00;
uint16_t d110 = 0x00;
uint16_t d111 = 0x00;

/* Current port state, second contact */
uint16_t d21 = 0x00;
uint16_t d22 = 0x00;
uint16_t d23 = 0x00;
uint16_t d24 = 0x00;
uint16_t d25 = 0x00;
uint16_t d26 = 0x00;
uint16_t d27 = 0x00;
uint16_t d28 = 0x00;
uint16_t d29 = 0x00;
uint16_t d210 = 0x00;
uint16_t d211 = 0x00;

/* Last state key send in chunk */
uint16_t lastState1 = 0x00;
uint16_t lastState2 = 0x00;
uint16_t lastState3 = 0x00;
uint16_t lastState4 = 0x00;
uint16_t lastState5 = 0x00;
uint16_t lastState6 = 0x00;
uint16_t lastState7 = 0x00;
uint16_t lastState8 = 0x00;
uint16_t lastState9 = 0x00;
uint16_t lastState10 = 0x00;
uint16_t lastState11 = 0x00;


/* Variables */
uint16_t duration_note1 = 0;
uint16_t duration_note2 = 0;
uint16_t duration_note3 = 0;
uint16_t duration_note4 = 0;
uint16_t duration_note5 = 0;
uint16_t duration_note6 = 0;
uint16_t duration_note7 = 0;
uint16_t duration_note8 = 0;
uint16_t duration_note9 = 0;
uint16_t duration_note10 = 0;
uint16_t duration_note11 = 0;
uint16_t duration_note12 = 0;
uint16_t duration_note13 = 0;
uint16_t duration_note14 = 0;
uint16_t duration_note15 = 0;
uint16_t duration_note16 = 0;
uint16_t duration_note17 = 0;
uint16_t duration_note18 = 0;
uint16_t duration_note19 = 0;
uint16_t duration_note20 = 0;
uint16_t duration_note21 = 0;
uint16_t duration_note22 = 0;
uint16_t duration_note23 = 0;
uint16_t duration_note24 = 0;
uint16_t duration_note25 = 0;
uint16_t duration_note26 = 0;
uint16_t duration_note27 = 0;
uint16_t duration_note28 = 0;
uint16_t duration_note29 = 0;
uint16_t duration_note30 = 0;
uint16_t duration_note31 = 0;
uint16_t duration_note32 = 0;
uint16_t duration_note33 = 0;
uint16_t duration_note34 = 0;
uint16_t duration_note35 = 0;
uint16_t duration_note36 = 0;
uint16_t duration_note37 = 0;
uint16_t duration_note38 = 0;
uint16_t duration_note39 = 0;
uint16_t duration_note40 = 0;
uint16_t duration_note41 = 0;
uint16_t duration_note42 = 0;
uint16_t duration_note43 = 0;
uint16_t duration_note44 = 0;
uint16_t duration_note45 = 0;
uint16_t duration_note46 = 0;
uint16_t duration_note47 = 0;
uint16_t duration_note48 = 0;
uint16_t duration_note49 = 0;
uint16_t duration_note50 = 0;
uint16_t duration_note51 = 0;
uint16_t duration_note52 = 0;
uint16_t duration_note53 = 0;
uint16_t duration_note54 = 0;
uint16_t duration_note55 = 0;
uint16_t duration_note56 = 0;
uint16_t duration_note57 = 0;
uint16_t duration_note58 = 0;
uint16_t duration_note59 = 0;
uint16_t duration_note60 = 0;
uint16_t duration_note61 = 0;
uint16_t duration_note62 = 0;
uint16_t duration_note63 = 0;
uint16_t duration_note64 = 0;
uint16_t duration_note65 = 0;
uint16_t duration_note66 = 0;
uint16_t duration_note67 = 0;
uint16_t duration_note68 = 0;
uint16_t duration_note69 = 0;
uint16_t duration_note70 = 0;
uint16_t duration_note71 = 0;
uint16_t duration_note72 = 0;
uint16_t duration_note73 = 0;
uint16_t duration_note74 = 0;
uint16_t duration_note75 = 0;
uint16_t duration_note76 = 0;
uint16_t duration_note77 = 0;
uint16_t duration_note78 = 0;
uint16_t duration_note79 = 0;
uint16_t duration_note80 = 0;
uint16_t duration_note81 = 0;
uint16_t duration_note82 = 0;
uint16_t duration_note83 = 0;
uint16_t duration_note84 = 0;
uint16_t duration_note85 = 0;
uint16_t duration_note86 = 0;
uint16_t duration_note87 = 0;
uint16_t duration_note88 = 0;

uint8_t curNote;
uint16_t duration;

//Пересчет тиков в велосити
//velocity=round(a/(x1+b)+c)
uint8_t getVelocity(uint16_t tickNum) {

    uint8_t velocity;

    if (tickNum >= 990)
        return 0;

    if (tickNum <= 36)
        return 127;

    velocity = ((10500 / (tickNum + 41)) - 9);

    return velocity;
}

/**
* Расчет velocity и запись в midi буффер
*/
void checkNoteArray(void) {
    //Проверяем буффер считанных клавиш с длительностями

    if (FIFO_COUNT(notes) > 0) {

        curNote = FIFO_FRONT(notes);
        duration = FIFO_FRONT(durations);

        FIFO_POP(durations);
        FIFO_POP(notes);

        if ((curNote & 0x80) == 0) {
            sendNoteOn(curNote, getVelocity(duration), 0);
        } else {
            sendNoteOff(curNote & 0x7F, 70, 0);
        }

    }
}

void readKeyState(void) {

    /* Read all contact state*/

    /* 1 chunk */

    GPIOE->BSRRH = GPIO_Pin_11;
    Delay(KEY_SWITCH_DELAY);
    d11 = ~GPIOA->IDR; //Read port state first contact
    GPIOE->BSRRL = GPIO_Pin_11;

    GPIOE->BSRRH = GPIO_Pin_12;
    Delay(KEY_SWITCH_DELAY);
    d21 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_12;

    /* 2 chunk */

    GPIOD->BSRRH = GPIO_Pin_9;
    Delay(KEY_SWITCH_DELAY);
    d12 = ~GPIOA->IDR; //Read port state first contact
    GPIOD->BSRRL = GPIO_Pin_9;

    GPIOE->BSRRH = GPIO_Pin_13;
    Delay(KEY_SWITCH_DELAY);
    d22 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_13;

    /* 3 chunk */

    GPIOE->BSRRH = GPIO_Pin_15;
    Delay(KEY_SWITCH_DELAY);
    d13 = ~GPIOA->IDR; //Read port state first contact
    GPIOE->BSRRL = GPIO_Pin_15;

    GPIOD->BSRRH = GPIO_Pin_8;
    Delay(KEY_SWITCH_DELAY);
    d23 = ~GPIOA->IDR; //Read port state second contact
    GPIOD->BSRRL = GPIO_Pin_8;

    /* 4 chunk */

    GPIOB->BSRRH = GPIO_Pin_11;
    Delay(KEY_SWITCH_DELAY);
    d14 = ~GPIOA->IDR; //Read port state first contact
    GPIOB->BSRRL = GPIO_Pin_11;

    GPIOB->BSRRH = GPIO_Pin_10;
    Delay(KEY_SWITCH_DELAY);
    d24 = ~GPIOA->IDR; //Read port state second contact
    GPIOB->BSRRL = GPIO_Pin_10;

    /* 5 chunk */

    GPIOB->BSRRH = GPIO_Pin_15;
    Delay(KEY_SWITCH_DELAY);
    d15 = ~GPIOA->IDR; //Read port state first contact
    GPIOB->BSRRL = GPIO_Pin_15;

    GPIOE->BSRRH = GPIO_Pin_14;
    Delay(KEY_SWITCH_DELAY);
    d25 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_14;

    /* 6 chunk */

    GPIOB->BSRRH = GPIO_Pin_13;
    Delay(KEY_SWITCH_DELAY);
    d16 = ~GPIOA->IDR; //Read port state first contact
    GPIOB->BSRRL = GPIO_Pin_13;

    GPIOB->BSRRH = GPIO_Pin_14;
    Delay(KEY_SWITCH_DELAY);
    d26 = ~GPIOA->IDR; //Read port state second contact
    GPIOB->BSRRL = GPIO_Pin_14;

    /* 7 chunk */

    GPIOC->BSRRH = GPIO_Pin_4;
    Delay(KEY_SWITCH_DELAY);
    d17 = ~GPIOA->IDR; //Read port state first contact
    GPIOC->BSRRL = GPIO_Pin_4;

    GPIOB->BSRRH = GPIO_Pin_12;
    Delay(KEY_SWITCH_DELAY);
    d27 = ~GPIOA->IDR; //Read port state second contact
    GPIOB->BSRRL = GPIO_Pin_12;

    /* 8 chunk */

    GPIOB->BSRRH = GPIO_Pin_0;
    Delay(KEY_SWITCH_DELAY);
    d18 = ~GPIOA->IDR; //Read port state first contact
    GPIOB->BSRRL = GPIO_Pin_0;

    GPIOC->BSRRH = GPIO_Pin_5;
    Delay(KEY_SWITCH_DELAY);
    d28 = ~GPIOA->IDR; //Read port state second contact
    GPIOC->BSRRL = GPIO_Pin_5;

    /* 9 chunk */

    GPIOB->BSRRH = GPIO_Pin_2;
    Delay(KEY_SWITCH_DELAY);
    d19 = ~GPIOA->IDR; //Read port state first contact
    GPIOB->BSRRL = GPIO_Pin_2;

    GPIOB->BSRRH = GPIO_Pin_1;
    Delay(KEY_SWITCH_DELAY);
    d29 = ~GPIOA->IDR; //Read port state second contact
    GPIOB->BSRRL = GPIO_Pin_1;

    /* 10 chunk */

    GPIOE->BSRRH = GPIO_Pin_8;
    Delay(KEY_SWITCH_DELAY);
    d110 = ~GPIOA->IDR; //Read port state first contact
    GPIOE->BSRRL = GPIO_Pin_8;

    GPIOE->BSRRH = GPIO_Pin_7;
    Delay(KEY_SWITCH_DELAY);
    d210 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_7;

    /* 11 chunk */

    GPIOE->BSRRH = GPIO_Pin_9;
    Delay(KEY_SWITCH_DELAY);
    d111 = ~GPIOA->IDR; //Read port state first contact
    GPIOE->BSRRL = GPIO_Pin_9;

    GPIOE->BSRRH = GPIO_Pin_10;
    Delay(KEY_SWITCH_DELAY);
    d211 = ~GPIOA->IDR; //Read port state second contact
    GPIOE->BSRRL = GPIO_Pin_10;

    /*************************************************************************/

    /* 1 key */

    if (d11 & 0x0001) { //Первый контакт

        if (duration_note1 < 0xFFFF)  {
            duration_note1++; //Увеличиваем длительность
        }

        if (d21 & 0x0001) { //Второй контакт

            if (lastState1 & 0x0001) {
                duration_note1 = 0; //Пока нажат второй контакт, сбрасываем длительность
            } else {
                FIFO_PUSH(notes, 21); //Добавляем в ФИФО текущую ноту
                FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность

                lastState1 ^= 0x1; //Устанавливаем прошлый статус как отправлен
                duration_note1 = 0; //Сбрасываем длительность
            }

        }

    } else if (lastState1 & 0x0001) {
        FIFO_PUSH(notes, 149); //Добавляем в ФИФО текущую ноту
        FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность
        lastState1 &= 0xFFFE; //Убираем статус отправки с бита
        duration_note1 = 0; //Сброс длительности
    } else {
        duration_note1 = 0; //Сброс длительности
    }

    /*************************************************************************/
}
