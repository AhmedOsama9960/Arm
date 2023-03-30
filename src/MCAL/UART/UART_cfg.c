/*
 * UART_cfg.c
 *
 *  Created on: Mar 30, 2023
 *      Author: osama
 */

#include "UART_cfg.h"
#include "../../inc/GPIO.h"

#define UART_RX_pin		0
#define RX_AFValue 		7

const UART_pins UARTPINS[USART_PinNo] =
{
		[UART_RX_pin] = {
				.Name         = "RX Pin",
				.Port		  = GPIO_B,			            // Port B
				.Pin  		  = pin_7,			            // Pin No 7
				.Mode 		  = AF, 		            	//pin mode
				.Speed		  = Low_Speed,		            // Speed
				.PUPD 		  = No_Pullup_down,		        // Pull_UP / Pull_Down
				.Circuit_Type = Push_Pull,					// Open drain or PushPull
				.AFValue	  = RX_AFValue,
		}
};
