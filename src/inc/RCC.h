/*
 * RCC.h
 *
 *  Created on: Feb 5, 2023
 *      Author: osama
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

/* ---------------------------------------------Include ------------------------------------------*/
#include "../My_Lib/Typedef.h"


/*----------------------------------------------Define --------------------------------------------*/
/* System Selection */
#define Clock_HSI		0
#define Clock_HSE		1
#define Clock_PLL		2

/*------------------RCC_CFGR--------------------*/
/* SW Bits */
#define SW0		0x01
#define SW1		0x02

/* SWS bits */

#define SWS0		0x04
#define SWS1		0x08

/* RCC_CR bits */
#define HSI_On			0x01
#define HSI_RDY			0x02
#define HSE_On			0x10000
#define HSE_RDY			0x20000
#define PLL_ON			0x1000000
#define PLL_RDY			0x2000000


/* RCC_APH1 by Masking */

#define GPIOAEn			0x01
#define GPIOBEn			0x02
#define GPIOCEn			0x04
#define GPIODEn			0x08
#define GPIOEEn			0x10
#define GPIOHEn			0x20

#define DMA2En			0x400000
#define DMA1En			0x200000

/* RCC_APB1 */
#define TIM2En			0x01
#define TIM3En			0x02
#define TIM4En			0x04
#define TIM5En			0x08

/*RCC_APB2 */

#define USART1En		0x10
#define TIM1En			0x01

/* -------------- RCC_PLLCFG----------------*/
#define PLLSCR			0x400000

/* PLL_M_Bits */
#define PLL_M_B1		0x01
#define PLL_M_B2		0x02
#define PLL_M_B3		0x04
#define PLL_M_B4		0x08
#define PLL_M_B5		0x10
#define PLL_M_B6		0x20

/* PLL_P Bits */
#define PLL_P_bit1			0x10000
#define PLL_P_bit2			0x20000

/* PLL_N Bits */
#define PLL_N_B1				0x40
#define PLL_N_B2				0x80
#define PLL_N_B3				0x100
#define PLL_N_B4				0x200
#define PLL_N_B5				0x400
#define PLL_N_B6				0x800
#define PLL_N_B7				0x1000
#define PLL_N_B8				0x2000
#define PLL_N_B9				0x4000

/* -------------------------------------Configuration --------------------------------------------------*/
/* RCC_PLLCFGR bits */

/* PLL_M 2,--->000010
 * PLL_M 3,--->000011
 * PLL_M 4,--->000100
 * PLL_M 5,--->000101
 * PLL_M_20--->010100
 * PLL_M.....63
 * */

/* PLL_M Configuration */
#define PLL_M_2			2
#define PLL_M_20		20
#define PLL_M_25		25
#define PLL_M_Config		PLL_M_25	// Make sure when you select this the frequency becomes 1-->2MHZ

/* PLL_P 2,--->00
 * PLL_P 4,--->01
 * PLL_P 6,--->10
 * PLL_P 8,--->11
 * */

/* PLL_P Configuration */
#define PLL_P_2			1
#define PLL_P_4			2
#define PLL_P_6			3
#define PLL_P_8			4
#define PLL_P_Config		PLL_P_4		// Make sure that the output freq is below 85MHZ


/* PLL_N  from 192 ----> 432
 * because it has bits from 6 --> 14, which are 8 bits
 *
 *		 b14<--------b6
 * PLL_N_192 --> 0 1100 0000
 * PLL_N_193---> 0 1100 0001
 * PLL_N_200---> 0 1100 1000
 *
 * 433 ----- > 511 Wrong Configuration
 * */
/* PLL_N_Config */
#define PLL_N_192				1
#define PLL_N_193				2
#define PLL_N_200				3

#define PLL_N_Config			PLL_N_200	//Make sure the freq is between 192 to 432 MHZ

//bits from 24 --->27

/* PLL_Q 2,--->0010
 * PLL_Q 3,--->0011
 * PLL_Q 4,--->0100
 * PLL_Q 5,--->4
 * ...
 * ..PLL_Q	->1111
 * */
#define PLL_Q			2


/* ******************Prescaler for Peripherals of AHB register*********** */


/*
 	 Prescaler_1---> 1
 	 Prescaler_4---> 4
 	 Prescaler_8---> 8
 	 Prescaler_16---> 16
 	 Prescaler_64---> 64

 */
#define Prescaler_1			1
#define Prescaler_2			2
#define Prescaler_4			4
#define Prescaler_8			8
#define Prescaler_16		16
#define Prescaler_64		64

#define AHB_Prescaler	Prescaler_1

/*------------------------------------------------Types ----------------------------------------------*/
typedef enum {
	Ok=0,
	Not_Ok
}Error_State;

/* -------------------------------------------------APIS---------------------------------------------*/

Error_State	RCC_EnuSelect_Clock (u8 Clock_Selection);
void RCC_voidEnablePeri(u8 Peri_Name);
void RCC_voidDisablePeri(u8 Peri_Name);


/* --------------------------------------------------END----------------------------------------------*/

#endif /* INC_RCC_H_ */
