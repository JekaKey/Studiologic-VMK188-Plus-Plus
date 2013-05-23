#include "midi.h"

void sendNoteOn(byte NoteNumber, byte Velocity, byte Channel) {
    FIFO_PUSH(midiMessagesArray, NoteOn ^ Channel);    //Событие и канал
    FIFO_PUSH(midiMessagesArray, NoteNumber);          //Номер ноты
    FIFO_PUSH(midiMessagesArray, Velocity);            //Скорость
}

void sendNoteOff(byte NoteNumber, byte Velocity, byte Channel) {
    FIFO_PUSH(midiMessagesArray, NoteOff ^ Channel);   //Событие и канал
    FIFO_PUSH(midiMessagesArray, NoteNumber);          //Номер ноты
    FIFO_PUSH(midiMessagesArray, Velocity);            //Скорость
}