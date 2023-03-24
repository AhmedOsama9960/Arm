/*
 * NVIC_STM.c
 *
 *  Created on: Feb 28, 2023
 *      Author: osama
 */


/*****************************************Include **************************************************/
#include "../../inc/NVIC_STM.h"

/******************************************Define ****************************************************/

#define Max_Bit_Of_Reg		32
#define Move_5				5
/***************************************** Type ****************************************************/
typedef struct
{
	u32 NVIC_ISER[7];
	u32 Reserved_1[25];
	u32 NVIC_ICER[7];
	u32 Reserved_2[25];
	u32	NVIC_ISPR[7];
	u32 Reserved_3[25];
	u32 NVIC_ICPR[7];
	u32 Reserved_4[25];
	u32 NVIC_IABR[7];
	u32 Reserved_5[57];
	u32 NVIC_IPR[59];
	u32 Reserved_6[645];
	u32 STIR;
}NVIC_Register_t;


/******************************************Declaration ****************************************************/

 volatile NVIC_Register_t * NVIC_t = ( volatile NVIC_Register_t *)0xE000E100;

/******************************************Implement ****************************************************/

void NVIC_IRQ_Enable(IRQNumber_t IRQ_Interrupt_No)
{

	/* shifting to left means dividing number by 2 power(n) --> 2 (5) means 32 */
	/* Or anding with masking by 31 will bring a number must be between 0 ---> 31*/
	u8 Location = IRQ_Interrupt_No >> Move_5;
	u8 Num_Of_Bits = IRQ_Interrupt_No % Max_Bit_Of_Reg;
	NVIC_t->NVIC_ISER[Location] =   1<<Num_Of_Bits;
}
void NVIC_IRQ_Disable (IRQNumber_t IRQ_Interrupt_No)
{
	/* shifting to left means dividing number by 2 power(n) --> 2 (5) means 32 */
	/* Or anding with masking by 31 will bring a number must be between 0 ---> 31*/
	u8 Location = IRQ_Interrupt_No >> Move_5;
	u8 Num_Of_Bits = IRQ_Interrupt_No % Max_Bit_Of_Reg;
	NVIC_t->NVIC_ICER[Location] =   1<<Num_Of_Bits;
}

void NVIC_IRQ_SetPending(IRQNumber_t IRQ_Interrupt_No)
{
	/* Making the pending high for any interrupt to occur */
	u8 Location = IRQ_Interrupt_No >> Move_5;
	u8 Num_Of_Bits = IRQ_Interrupt_No % Max_Bit_Of_Reg;
	NVIC_t->NVIC_ISPR[Location] =   1<<Num_Of_Bits;
}
void NVIC_IRQ_ClearPending(IRQNumber_t IRQ_Interrupt_No)
{
	/* Making the pending low to disable any interrupt to occur */
	u8 Location = IRQ_Interrupt_No >> Move_5;
	u8 Num_Of_Bits = IRQ_Interrupt_No % Max_Bit_Of_Reg;
	NVIC_t->NVIC_ICPR[Location] =   1<<Num_Of_Bits;

}
u32 NVIC_GetActiveStatus(IRQNumber_t IRQ_Interrupt_No)
{
	u8 Location = IRQ_Interrupt_No >> Move_5;
	u8 Num_Of_Bits = IRQ_Interrupt_No % Max_Bit_Of_Reg;
	return (NVIC_t->NVIC_IABR[Location] &  (1<<Num_Of_Bits));
}

void NVIC_Set_Priority (IRQNumber_t IRQn, u32 priority)
{
	u8 Location = IRQn>>2;
	u8 Num_OF_Bit = (IRQn & 0x07) * 8;

	NVIC_t->NVIC_IPR[Location] = priority<< Num_OF_Bit;

}
void NVIC_Set_Priority_Grouping(PriGroup PriorityGroup)
{
			SCB_AIRCR |= PriorityGroup;
}



/******************************************END ****************************************************/
