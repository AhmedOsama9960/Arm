/*
 * UART.h
 *
 *  Created on: Mar 28, 2023
 *      Author: osama
 */

#ifndef INC_UART_H_
#define INC_UART_H_

/*****************************************Include **************************************************/
#include "../My_Lib/Typedef.h"

/***************************************** Type ****************************************************/



typedef enum
{
	USART_BusyState,
	USART_Idle,
	USART_ok,
	USART_NullPointer

}UART_t;
/******************************************Define ****************************************************/
#define UART_1		0x40011000
#define UART_2		0x40014400
#define UART_6		0x40011400


/***************************************APIs********************************************************/
void UART_init(void);
UART_t UART_SendBuffer_ZeroCopy(u8 * Buffer , u8 size);
UART_t UART_Recieve_Buffer(u8 * Buffer , u8 size);

/***************************************END********************************************************/


#endif /* INC_UART_H_ */
