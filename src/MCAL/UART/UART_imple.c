/*
 * UART_imple.c
 *
 *  Created on: Mar 28, 2023
 *      Author: osama
 */


/*****************************************Include **************************************************/
#include "../../inc/UART.h"
#include "UART_private.h"
#include "../../inc/GPIO.h"
#include <diag/Trace.h>

/***************************************** Define ****************************************************/

#define Null 	(void*)0

/******************************************Types **********************************************/
typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
} USARTReg_t;

typedef struct
{
	u8 *buffer;
	u8 size;
	u8 indx;
	u8 Status;
}USART_Buffer;

extern const UART_pins UARTPINS[USART_PinNo];

/******************************************Declarations **********************************************/

volatile USARTReg_t  * const USARTRegs = (volatile USARTReg_t * const) UART_1;
USART_Buffer  USART_TXData;
USART_Buffer  USART_RXData;

u8 res ;

/***************************************Implementations**********************************************/
void UART_Pins_Init(void)
{
	GPIO_init_t GPIO_cfg;

	for(u8 indx = 0; indx <USART_PinNo; indx++)
	{
		GPIO_cfg.Mode			 = UARTPINS[indx].Mode;			/* Mode_out*/
		GPIO_cfg.Pin 			 = UARTPINS[indx].Pin;			/* No of pin */
		GPIO_cfg.Port			 = UARTPINS[indx].Port;			/* Port A,B,C,D */
		GPIO_cfg.Speed			 = UARTPINS[indx].Speed;			/* Speed Range */
		GPIO_cfg.Circuit_Type 	 = UARTPINS[indx].Circuit_Type;	/* active high or active low */
		GPIO_cfg.PUPD 			 = UARTPINS[indx].PUPD;			/* Pull up or Push Down or no pull up or down*/
		GPIO_cfg.AFValue		 = UARTPINS[indx].AFValue;

		GPIO_Init_Pin(&GPIO_cfg);
	}
}
void UART_init(void)
{
/*
1. Oversampling: 16
2. Word length: 8-bit
3. Stop bit: 1-bit
6. USART enable: Enabled
7. Transmitter enable: Enabled
8. Receiver enable: Enabled
 */

		//Init the pins for UART
		UART_Pins_Init();

		u32 CR1_Var = 0;
		CR1_Var |= UE_CR1;		// Enable USART
		CR1_Var &= ~M_CR1;		// 8 Bits
		CR1_Var |= RE_CR1;		// Enable Receiving
		CR1_Var |= TE_CR1;		// Enable Transmitting


		USARTRegs->USART_CR2 |= Stop_Bits_CR2;		// 1StopBit
		USARTRegs->USART_CR3 |= OneSampleBit_CR3;	//OneBitSampling
		USARTRegs->USART_BRR  = BaudRate;			//9600
		USARTRegs->USART_CR1 |= CR1_Var;			// Enable with 8 Bit Data

		USART_RXData.Status = USART_Idle;
		USART_TXData.Status = USART_Idle;
}


UART_t UART_SendBuffer_ZeroCopy( u8 * Buffer , u8 size)
{
	res = USART_BusyState;
	if(USART_TXData.Status == USART_Idle)
	{
		if(Buffer != Null){
			USART_TXData.buffer = Buffer;
			USART_TXData.size   = size;
			USART_TXData.indx   = 0;

			USARTRegs->USART_DR = USART_TXData.buffer[USART_TXData.indx];
			USART_TXData.indx++;

			USART_TXData.Status = USART_BusyState;
			res = USART_ok;

		} else {
			res = USART_NullPointer;
		}
	}

	return res;
}

UART_t UART_Recieve_Buffer(u8 *Buffer , u8 size)
{
	res = USART_BusyState;
	if(USART_RXData.Status == USART_Idle)
	{
		(USART_RXData.buffer) = Buffer;
		USART_RXData.size = size;
		USART_RXData.indx   = 0;

		USARTRegs->USART_CR1 |= RXEIE_CR1;  // Enable The Interrupt
		USARTRegs->USART_SR  &= ~RXNE_SR;	//Clear Status Reg		RXNE = 0

		USART_RXData.Status = USART_BusyState;
		res = USART_ok;
	}

	return res;
}

void USART1_IRQHandler(void)
{
	//trace_printf("Hi");
	if(USARTRegs->USART_SR & TXE_SR)
	{
		if(USART_TXData.size > USART_TXData.indx){
			if(&USART_TXData.buffer[USART_TXData.indx] != Null)
			USARTRegs->USART_DR = USART_TXData.buffer[USART_TXData.indx];
			USART_TXData.indx++;
		} else {
			USART_TXData.Status = USART_Idle;
		}
	}

	if((USARTRegs->USART_SR & RXNE_SR) && (USART_RXData.Status == USART_BusyState))
	{
		if(USART_RXData.size > USART_RXData.indx)
		{
			//trace_printf("Entered\t");
			if(&USART_RXData.buffer[USART_TXData.indx] != Null){

			*(USART_RXData.buffer) = USARTRegs->USART_DR ;
			USART_RXData.indx++;

			}
			else
			{
				//trace_printf("Null\t");
			}
		}

		if (USART_RXData.size == USART_RXData.indx){
			USART_RXData.Status = USART_Idle;
			USARTRegs->USART_CR1 &= ~RXEIE_CR1;		//Clear Interrupt
		}
	}
}

/***************************************END********************************************************/
