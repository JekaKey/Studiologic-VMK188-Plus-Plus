#include <string.h>
#include "stm32f4xx.h"
#include "log.h"

int _write(int file, char *ptr, int len)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
        int counter;

        counter = len;
        for (; counter > 0; counter--)
        {
                        if (*ptr == 0) break;
                        USART_SendData(USART6, (uint16_t) (*ptr));
                        /* Loop until the end of transmission */
                        while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
                        ptr++;
        }
        return len;
}


//
//int _write( int file, char *ptr, int len )
//
//{
//
//int txCount;
//
//  (void)file;
//
//  for ( txCount = 0; txCount < len; txCount++)
//
//  {
//
//  USART_SendData(USART6, ptr[txCount]);   //Don't forget to include "stm32f10x_usart.h"
//
//  /* Loop until the end of transmission */
//
//   while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
//
//   {
//
//   }
//
//  }
//
//  return len;
//
//}

void abort(void)

{

  /* Abort called */

  while(1);

}

