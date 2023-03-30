/*
 * RCC.c
 *
 *  Created on: Feb 5, 2023
 *      Author: osama
 */

/* ------------------------ Include --------------------------------------*/
#include "../../inc/RCC.h"
#include <diag/Trace.h>
/* -------------------------Define ---------------------------------------*/

#define Timeout 	0
#define Max_Value	0xffff
/* -------------------------Types ----------------------------------------*/
typedef struct {
	u32 RCC_CR;
	u32 RCC_PLLCFG;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1_Reset;
	u32 RCC_AHB2_Reset;
	u32 Reserved_1;
	u32 Reserved_2;
	u32 RCC_APB1_Reset;
	u32 RCC_APB2_Reset;
	u32 Reserved_3;
	u32 Reserved_4;
	u32 RCC_AHB1_Enable;
	u32 RCC_AHB2_Enable;
	u32 Reserved_5;
	u32 Reserved_6;
	u32 RCC_APB1_Enable;
	u32 RCC_APB2_Enable;
}__attribute__((packed, aligned(4))) RCC_Register;

/*-------------------------Variable -------------------------------------*/

volatile RCC_Register * const RCC_Reg = (volatile RCC_Register * const)0x40023800;


/*-------------------------Implementation -------------------------------*/

Error_State	RCC_EnuSelect_Clock (u8 Clock_Selection)
{
	/* Variable for Registers */
	u32 RCC_CFGR = RCC_Reg->RCC_CFGR;
	u32 RCC_PLLCFG = RCC_Reg->RCC_PLLCFG;
	u8 state = Ok;

	u16 Counter = Max_Value;

	if(Clock_Selection == Clock_HSI)
	{
			RCC_Reg->RCC_CR = 0x81;
	}

	else if (Clock_Selection == Clock_HSE)
	{
		/* Enable HSE */
		RCC_Reg->RCC_CR |= HSE_On;

		/* Wait until Flag is ready for HSE */
		while( (RCC_Reg->RCC_CR & HSE_RDY) != HSE_RDY && Counter--> Timeout);

		if((RCC_Reg->RCC_CR & HSE_RDY) == HSE_RDY)
			Counter = Max_Value;
		else
		{
			//trace_printf("NotOk");
			state = Not_Ok;
		}

		/* Select the HSE */
		RCC_CFGR |= SW0;
		RCC_CFGR &= (~SW1);

		RCC_Reg->RCC_CFGR |=RCC_CFGR;

		/* Keep polling until The status becomes HSE */
		while((RCC_Reg->RCC_CFGR & SWS0) != SWS0 && (RCC_Reg->RCC_CFGR & SWS1) != SWS1  && Counter--> Timeout);

		if((RCC_Reg->RCC_CFGR & SWS0) == SWS0 && (RCC_Reg->RCC_CFGR & SWS1) != SWS1)
			Counter = Max_Value;
		else
		{
			//trace_printf("\nCFG_Reg");
			state = Not_Ok;
		}
	}
	else if (Clock_Selection == Clock_PLL)
	{
		RCC_Reg->RCC_CR |= HSE_On;							// Enable HSE
		while((RCC_Reg->RCC_CR & HSE_RDY) != HSE_RDY && Counter > Timeout)
		{
			Counter--;								// wait until its ready
		}
		if((RCC_Reg->RCC_CR & HSE_RDY) == HSE_RDY)
				Counter = Max_Value;
		else
			{
			//trace_printf("NotOk PLL1");
			state = Not_Ok;
			}

		/* Set HSE as PLL Source */
		RCC_PLLCFG |= PLLSCR;

							/* PLL Configuration like M,N,Q,P */

								/* PLL_M Configuration */
#if PLL_M_Config == PLL_M_2

		RCC_PLLCFG &= (~PLL_M_B1);
		RCC_PLLCFG |= (PLL_M_B2);
		RCC_PLLCFG &= (~PLL_M_B3);
		RCC_PLLCFG &= (~PLL_M_B4);
		RCC_PLLCFG &= (~PLL_M_B5);
		RCC_PLLCFG &= (~PLL_M_B6);

#elif	PLL_M_Config	== PLL_M_3
		RCC_PLLCFG |= (PLL_M_B1);
		RCC_PLLCFG |= (PLL_M_B2);
		RCC_PLLCFG &= (~PLL_M_B3);
		RCC_PLLCFG &= (~PLL_M_B4);
		RCC_PLLCFG &= (~PLL_M_B5);
		RCC_PLLCFG &= (~PLL_M_B6);

#elif PLL_M_Config == PLL_M_4
		RCC_PLLCFG &= (~PLL_M_B1);
		RCC_PLLCFG &= (~PLL_M_B2);
		RCC_PLLCFG |= (PLL_M_B3);
		RCC_PLLCFG &= (~PLL_M_B4);
		RCC_PLLCFG &= (~PLL_M_B5);
		RCC_PLLCFG &= (~PLL_M_B6);


#elif PLL_M_Config == PLL_M_5
		RCC_PLLCFG |= (PLL_M_B1);
		RCC_PLLCFG &= (~PLL_M_B2);
		RCC_PLLCFG |= (PLL_M_B3);
		RCC_PLLCFG &= (~PLL_M_B4);
		RCC_PLLCFG &= (~PLL_M_B5);
		RCC_PLLCFG &= (~PLL_M_B6);

#elif PLL_M_Config == PLL_M_20
		RCC_PLLCFG &= (~PLL_M_B1);
		RCC_PLLCFG &= (~PLL_M_B2);
		RCC_PLLCFG |= (PLL_M_B3);
		RCC_PLLCFG &= (~PLL_M_B4);
		RCC_PLLCFG |= (PLL_M_B5);
		RCC_PLLCFG &= (~PLL_M_B6);

#elif PLL_M_Config == PLL_M_25
		RCC_PLLCFG |= (PLL_M_B1);
		RCC_PLLCFG |= (PLL_M_B4);
		RCC_PLLCFG |= (PLL_M_B5);
#endif
		RCC_Reg->RCC_PLLCFG |= RCC_PLLCFG;
								/********** PLL_N Multiplication Factor ************/
#if	PLL_N_Config == PLL_N_192

		RCC_PLLCFG &= (~PLL_N_B1);
		RCC_PLLCFG &= (~PLL_N_B2);
		RCC_PLLCFG &= (~PLL_N_B3);
		RCC_PLLCFG &= (~PLL_N_B4);
		RCC_PLLCFG &= (~PLL_N_B5);
		RCC_PLLCFG &= (~PLL_N_B6);
		RCC_PLLCFG |= (PLL_N_B7);
		RCC_PLLCFG |= (PLL_N_B8);
		RCC_PLLCFG &= (~PLL_N_B9);

#elif PLL_N_Config == PLL_N_193

		RCC_PLLCFG |= (PLL_N_B1);
		RCC_PLLCFG &= (~PLL_N_B2);
		RCC_PLLCFG &= (~PLL_N_B3);
		RCC_PLLCFG &= (~PLL_N_B4);
		RCC_PLLCFG &= (~PLL_N_B5);
		RCC_PLLCFG &= (~PLL_N_B6);
		RCC_PLLCFG |= (PLL_N_B7);
		RCC_PLLCFG |= (PLL_N_B8);
		RCC_PLLCFG &= (~PLL_N_B9);

#elif PLL_N_Config == PLL_N_200

		RCC_PLLCFG |= (PLL_N_B4);
		RCC_PLLCFG |= (PLL_N_B7);
		RCC_PLLCFG |= (PLL_N_B8);


#endif
		RCC_Reg->RCC_PLLCFG |= RCC_PLLCFG;
									/********** PLL_P ************/
#if	PLL_P_Config == PLL_P_2

	RCC_PLLCFG &= (~PLL_P_bit1);
	RCC_PLLCFG &= (~PLL_P_bit2);

#elif PLL_P_Config == PLL_P_4

	RCC_PLLCFG |= PLL_P_bit1;

#elif PLL_P_Config == PLL_P_6

	RCC_PLLCFG &= (~PLL_P_bit1);
	RCC_PLLCFG |= (PLL_P_bit2);

#else
	RCC_PLLCFG |= (PLL_P_bit1);
	RCC_PLLCFG |= (PLL_P_bit2);

#endif

	// Set the PLL config
	RCC_Reg->RCC_PLLCFG |= RCC_PLLCFG;
		/* Enable PLL */

		RCC_Reg->RCC_CR |= PLL_ON;

		/* wait until it is ready */
		while((RCC_Reg->RCC_CR & PLL_RDY) != PLL_RDY)
			{
				Counter--;
			}
		if((RCC_Reg->RCC_CR & PLL_RDY) == PLL_RDY)
		{
			Counter = Max_Value;
		}
		else
		{
			//trace_printf("NotOk PLL2");
			state = Not_Ok;
		}
		/* Switch the system clock to be PLL Source */
		RCC_Reg->RCC_CFGR |= SW1;

		/* polling until the Hardware Status indicates that the source system is PLL SCR*/
		while((RCC_Reg->RCC_CFGR & SWS1) != SWS1 && Counter--> Timeout);

		if((RCC_Reg->RCC_CFGR & SWS1) == SWS1)
		 {
				Counter = Max_Value;
		 }
		else
		{
			trace_printf("NotOk PLL3");
			state = Not_Ok;
		}
	}
	else
	{
		/* Misra Rule */
	}
	return state;
}


void RCC_voidEnablePeri(u8 Peri_Name)
{
	/* Set bits by bit masking */
	if(Peri_Name == GPIOAEn || Peri_Name == GPIOBEn || Peri_Name == DMA1En)
	{
		//RCC_AHB1
	RCC_Reg->RCC_AHB1_Enable |= Peri_Name;

	} else if (Peri_Name == USART1En) {
		//RCC_AHB1
	RCC_Reg->RCC_APB2_Enable |= Peri_Name;

	}
}

void RCC_voidDisablePeri(u8 Peri_Name)
{
		/* Clear Bits by bit masking */
		RCC_Reg->RCC_AHB1_Reset &= (~Peri_Name);
}
