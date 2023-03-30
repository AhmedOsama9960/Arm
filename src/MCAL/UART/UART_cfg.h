/*
 * UART_cfg.h
 *
 *  Created on: Mar 29, 2023
 *      Author: osama
 */

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

#include "../../My_Lib/Typedef.h"

#define Async			0
#define DMA_Mode		1
#define Sync			2

#define USART_Mode			Async


#define _1Stop		0
#define	_half_Stop	1000
#define _2Stop		2000

#define StopBits	_1Stop


typedef enum
{
	RX,
	USART_PinNo
}USART_pins;

typedef struct {
	char * Name;
	void* Port;
	u8 Pin;
	u8 Speed;
	u8 Mode;
	u8 PUPD;
	u8 Circuit_Type;
	u8 AFValue;
}UART_pins;

#endif /* MCAL_UART_UART_CFG_H_ */
