/*
 * Systick_Stm.h
 *
 *  Created on: Mar 8, 2023
 *      Author: osama
 */

#ifndef INC_SYSTICK_STM_H_
#define INC_SYSTICK_STM_H_


/* ------------------------ Include --------------------------------------*/



/*--------------------------Type-------------------------------------------*/
typedef unsigned long long int  llu;
typedef void(*CBF)(void);

typedef enum
{
	Systick_Ok,
	Systick_NoK,
	Systick_NullPtr,
	Systick_Wrong_Clock


}Error_Status_Systick;

/*---------------------------Config -----------------------------------*/

#define Clock_AHB_8			0			// AHBClock divided by 8
#define Clock_AHB			0x04		//Processor Clock

#define Clock_Selection		Clock_AHB


// Systick Enable Request

#define Disable_Request			0x00
#define Enable_Request			0x02


// Systick Counter Enable

#define Enable_Counter			0x01
#define Disable_Counter			0x00

// CounterFlag
#define CountFlag			0x10000			// if returns 1 so it has counted to zero


// Reload Value
#define Max_Reload_Value		0x00FFFFFF			// Must be between 0x00FFFFFF ---> 0x00000001
/* ------------------------ APIS --------------------------------------*/

void SysTick_start(void);
void Systick_Counting_Stop(void);
Error_Status_Systick Systick_Set_CBF(CBF);
Error_Status_Systick Systick_Set_Period_MS(unsigned short _MS , llu System_Clock);
Error_Status_Systick Systick_Set_Period_Micro_S(unsigned short _MS , llu System_Clock);

/* ------------------------ END --------------------------------------*/



#endif /* INC_SYSTICK_STM_H_ */
