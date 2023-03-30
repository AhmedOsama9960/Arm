/*
 * UART_private.h
 *
 *  Created on: Mar 29, 2023
 *      Author: osama
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#include "UART_cfg.h"

/**---------Status Register------*/
typedef enum
{

	RXNE_SR		=	0x20,
	TC_SR		=	0x40,
	TXE_SR		=	0x80
}SR;

/*---------Control Register1 -------*/

typedef enum
{
	UE_CR1 	  = 0x2000,		//1 means enable
	M_CR1  	  = 0x1000,		//0 means 8 bits 1 means 9 bits
	TXEIE_CR1 = 0x80,
	RXEIE_CR1 = 0x20,
	TE_CR1    = 0x08,		// Transmitter enabled
	RE_CR1	  = 0x04,		// Receiver Enabled
}CR1;


/*---------Control Register2 -------*/
typedef enum
{
	Stop_Bits_CR2   = 	_1Stop,
	CLKEn_CR2		= 	0x800

}CR2;

/*---------Control Register3 -------*/


typedef enum
{
	OneSampleBit_CR3=	0x800,
	DMAT_CR3   		= 	0x80,		//DMA Transmitter Enable
	DMAR_CR3		= 	0x40		//DMA Receiver Enable

}CR3;

/*------------ BaudRate --------*/
// At 16MHz		OVERSampling 16
// 9.6Kbps

#define BaudRate		0x683

#endif /* MCAL_UART_UART_PRIVATE_H_ */
