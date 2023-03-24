/*
 * GPIO.c
 *
 *  Created on: Feb 14, 2023
 *      Author: osama
 */



/***************************************** Include **********************************************/
#include "../../inc/GPIO.h"

/**************************************** Define ************************************************/

#define Half_Register		16
/**************************************** Types *************************************************/

typedef struct
{
	u32 GPIO_x_Moder;
	u32 GPIO_x_Otyper;
	u32 GPIO_x_OSpeed;
	u32 GPIO_x_PUPDR;
	u32 GPIO_x_IDR;
	u32 GPIO_x_ODR;
	u32 GPIO_x_BSRR;
	u32 GPIO_x_LCKR;
	u32 GPIO_x_AFRL;
	u32 GPIO_x_AFRH;
}GPIO_Register;


/*************************************** Variables ************************************************/

GPIO_init_t Led_Pin;

/*****************************************Implementations****************************************/

void GPIO_Init_Pin(GPIO_init_t * Init_Pins)
{
		((GPIO_Register*)Init_Pins->Port)->GPIO_x_Moder  |= (Init_Pins->Mode)<<(Init_Pins->Pin);
		((GPIO_Register*)Init_Pins->Port)->GPIO_x_OSpeed |= (Init_Pins->Speed)<<(Init_Pins->Pin);
		((GPIO_Register*)Init_Pins->Port)->GPIO_x_Otyper |= Init_Pins->Circuit_Type;
		((GPIO_Register*)Init_Pins->Port)->GPIO_x_PUPDR  |= (Init_Pins->PUPD)<<(Init_Pins->Pin);
}
void GPIO_Init(void)
{
	Led_Pin.Port 		 = ((GPIO_Register*)PORT_Cofig);
	Led_Pin.Pin  		 = pin_0;
	Led_Pin.Mode 		 = Output;
	Led_Pin.Speed   	 = Speed_Type;
	Led_Pin.PUPD    	 = No_Pullup_down;
	Led_Pin.Circuit_Type = Push_Pull;
	//GPIO_Init_Pin(&Led_Pin);
}

GPIO_ErrorStatus GPIO_Write_PinValue(void* GPIO_Group, Set_Pins Set_Pin, u8 GPIO_Status)
{
	u8 state;
	if( (u32)GPIO_Group > (u32)GPIO_E)
	{
		state = GPIO_Wrong_Port;
	}
	else if (Set_Pin > Set_Pin_15)
	{
		state = GPIO_Wrong_Pin;
	}
	else{
			if(GPIO_Status == High)
			{
				((volatile GPIO_Register*const)GPIO_Group)->GPIO_x_BSRR = Set_Pin;
			}
			else if(GPIO_Status == Low)
			{
				((volatile GPIO_Register*const)GPIO_Group)->GPIO_x_BSRR = (Set_Pin<<Half_Register);
			}
			state = GPIO_Ok;
	}

		return state;
}
GPIO_ErrorStatus GPIO_Get_Value(void* GPIO_Group, Set_Pins Set_Pin, u8 * CpyPinValue)
{
	if((u32)GPIO_Group >= (u32)GPIO_E)
		{
			return GPIO_Wrong_Port;
		}
		else if (Set_Pin > Set_Pin_15)
		{
			return GPIO_Wrong_Pin;
		}
			/* Either value equal GPIO_Pin_No or zero */
				* CpyPinValue = ((GPIO_Register*)GPIO_Group)->GPIO_x_IDR & Set_Pin;

			return GPIO_Ok;
}

GPIO_ErrorStatus GPIO_Port_Value(void* GPIO_Group, u16 GPIO_Value)
{
	if((u32)GPIO_Group > (u32)GPIO_E)
		{
			return GPIO_Wrong_Port;
		}
	else
	{
		//Misra Rule
	}
		((GPIO_Register*)GPIO_Group)->GPIO_x_ODR = GPIO_Value;
			return GPIO_Ok;
}

/******************************************END***************************************************/
