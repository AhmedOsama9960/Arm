/*
 * Systick_Impe.c
 *
 *  Created on: Mar 8, 2023
 *      Author: osama
 */


/* ------------------------ Include --------------------------------------*/

#include "../../My_Lib/Typedef.h"
#include "../../inc/Systick_Stm.h"


/* ------------------------ Define --------------------------------------*/

#define Clear			0
#define NULL			(void*)0

#define Clock_HSE				25000000
#define Clock_HSI				16000000

#define _1MS_HSI		16000
#define _1MS_HSE		25000

#define _1MircoS_HSI	16
#define _1MicroS_HSE	25
/* ------------------------ Types --------------------------------------*/

typedef struct
{
	u32 SYS_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}Systick_Register_Map;

/* ------------------------ Declaration --------------------------------------*/

volatile Systick_Register_Map * const Systick_Map = (volatile Systick_Register_Map * const)0xE000E010;

// To avoid the WildPTR Problem
static void(*PTF)(void) = NULL;


/* ------------------------ Implementation --------------------------------------*/

void SysTick_start(void)
{
	u8 CTRL = 0;
	// Clear the current value
	Systick_Map->STK_VAL = Clear;

	//setting the clock of the Systick
	CTRL |= Clock_AHB;

	//Enable IRQ for Systick
	CTRL |= Enable_Request;

	//Enable To Count
	CTRL |= Enable_Counter;

	Systick_Map->SYS_CTRL = CTRL;
}
void Systick_Counting_Stop(void)
{
		u8 CTRL = 0;
		//Disable To Count
		CTRL |= Disable_Counter;

		//Disable IRQ for Systick
		CTRL |= Disable_Request;

		Systick_Map->SYS_CTRL = CTRL;
}
Error_Status_Systick Systick_Set_CBF(CBF cbf)
{
	u8 status;
	if(cbf == NULL)
	{
		status = Systick_NullPtr;
	}
	else
	{
		PTF = cbf;
		status = Systick_Ok;
	}
	return status;
}

void SysTick_Handler(void)
{
	PTF();
}

Error_Status_Systick Systick_Set_Period_MS(unsigned short _MS , llu System_Clock)
{
	u8 status;

	switch(Clock_Selection)
	{
	case Clock_AHB:
	if(System_Clock <= Clock_HSE && System_Clock > Clock_HSI)
	{
		Systick_Map->STK_LOAD = ((_MS) * _1MS_HSE)-1;
		status = Systick_Ok;
	}
	else if ( System_Clock > 0 && System_Clock <= Clock_HSI)
	{
		Systick_Map->STK_LOAD = ((_MS) * _1MS_HSI)-1;
		status = Systick_Ok;
	}
	else
	{
		status = Systick_Wrong_Clock;
	}
	break;

	case Clock_AHB_8:

		break;
	}
	return status; // One Return MisraRule
}
Error_Status_Systick Systick_Set_Period_Micro_S(unsigned short _MS , llu System_Clock)
{
	u8 status;

	switch(Clock_Selection)
	{
	case Clock_AHB:

	if(System_Clock <= Clock_HSE && System_Clock > Clock_HSI)
	{
		Systick_Map->STK_LOAD = ((_MS ) * _1MicroS_HSE) -1;
		status = Systick_Ok;
	}
	else if ( System_Clock > 0 && System_Clock <= Clock_HSI)
	{
		Systick_Map->STK_LOAD = ((_MS) * _1MircoS_HSI) -1;
		status = Systick_Ok;
	}
	else
	{
		status = Systick_Wrong_Clock;
	}
	break;

	case Clock_AHB_8:

	break;
	}
	return status;

}


/* ------------------------ END --------------------------------------*/
