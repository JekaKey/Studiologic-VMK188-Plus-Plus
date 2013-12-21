#include <stdio.h>

#ifndef FIFO__H
#define FIFO__H

//Size should be: 4,8,16,32...128
#define FIFO8( size )\
    struct {\
        uint8_t buf[size];\
        uint8_t tail;\
        uint8_t head;\
    }

#define FIFO16( size )\
    struct {\
        uint16_t buf[size];\
        uint8_t tail;\
        uint8_t head;\
    }

#define FIFO32( size )\
    struct {\
        uint32_t buf[size];\
        uint8_t tail;\
        uint8_t head;\
    }

#define FIFO_IS_FULL(fifo)   ((fifo.head-fifo.tail)==(sizeof(fifo.buf) / sizeof(fifo.buf[0]))

#define FIFO_IS_EMPTY(fifo)  (fifo.tail==fifo.head)

#define FIFO_COUNT(fifo)     (fifo.head-fifo.tail)

#define FIFO_SIZE(fifo)      (sizeof(fifo.buf) / sizeof(fifo.buf[0]))

#define FIFO_SPACE(fifo)     (FIFO_SIZE(fifo)-FIFO_COUNT(fifo))

#define FIFO_PUSH(fifo, byte) \
    {\
        fifo.buf[fifo.head & (FIFO_SIZE(fifo) - 1)] = byte; \
        fifo.head++; \
    }

#define FIFO_FRONT(fifo) (fifo.buf[(fifo).tail & ((sizeof(fifo.buf) / sizeof(fifo.buf[0])) - 1)])

#define FIFO_POP(fifo)   \
    {\
        fifo.tail++; \
    }

#define FIFO_FLUSH(fifo)   \
    {\
        fifo.tail=0;\
        fifo.head=0;\
    }

#endif //FIFO__H

	/**/
