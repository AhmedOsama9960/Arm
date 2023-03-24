/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// --------------------- Include-------------------------------------------------------

#include "inc/RCC.h"
#include "inc/LED.h"
#include "inc/Switch.h"
#include "inc/LCD.h"
#include "inc/Systick_Stm.h"
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f401xc.h"
#include "inc/Sched.h"

/*****************************Define *************************************/
#define	Led_1	1
#define Led_0	0
// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

//extern unsigned int _Hamo_Begin;

/*
void EXTI0_IRQHandler(void)
	{
		led_set_state(Led_1,High);
		//Gamda Awiii
		trace_printf("1");
	}

void EXTI1_IRQHandler(void)
	{
		led_set_state(Led_0,High);
		// Gamda Awiiiii
		trace_printf("0");
	}
void Cfb(void)
{
	led_set_state(Led_1,High);
	trace_printf("0");
}
*/
int
main(int argc, char* argv[])
{

/*-------------------- Scheduler --------------------*/
	// Clock Tree
	u8 state =	RCC_EnuSelect_Clock(Clock_HSE);
	if(state == Ok) {
	RCC_voidEnablePeri(GPIOAEn);
	RCC_voidEnablePeri(GPIOBEn);
	}

	//Initialization
	if(state == Ok) {
	led_init();
	Switch_Init();
	LCD_Pins_Init();
	}

	//Scheduler
	Sched_init();
	Sched_start();

	/*--------------------------------------- NVIC and Systic and LED -----------*/
	/*RCC_EnuSelect_Clock(Clock_HSI);
	RCC_voidEnablePeri(GPIOAEn);
	led_init();

	// NVIC Testing
	NVIC_Set_Priority_Grouping(PriorityGroup_4_PriGroup_0_SubGroup);
	NVIC_Set_Priority(EXTI0_IRQ,1);
	NVIC_Set_Priority(EXTI1_IRQ,2);
	NVIC_IRQ_Enable(EXTI0_IRQ);
	NVIC_IRQ_Enable(EXTI1_IRQ);
	//NVIC_IRQ_SetPending(EXTI0_IRQ);

	// Systick Testing
	Systick_Set_Period_MS(100,25000000);
	Systick_Set_CBF(Cfb);
	SysTick_start();*/

/*
while(1)
{
	//NVIC_IRQ_SetPending(EXTI0_IRQ);
}
*/


	/*
	__attribute__ ((section (".Hamo"),used))
	    volatile static long int aStatic;
	aStatic++;
	// the same reference to this variable and can change its value created in the section file
	_Hamo_Begin ++ ;
*/


	/* App from LED Driver */
	/*RCC_EnuSelect_Clock(Clock_HSI);
	RCC_voidEnablePeri(GPIOAEn);
	led_init();
	led_set_state(Led_1,High);*/



	/* GPIO_A APP LED */

/*		RCC_EnuSelect_Clock(Clock_HSI);
		RCC_voidEnablePeri(GPIOAEn);
		GPIO_Init();
		GPIO_Write_PinValue(GPIO_A,Set_Pin_0,High);
*/

	/* RCC App */
  // Infinite loop
	/*
	RCC_EnuSelect_Clock(Clock_HSI);
	RCC_voidEnablePeri(GPIOAEn);
	RCC_voidDisablePeri(GPIOAEn);
	*/
  while (1)
    {
       // Add your code here.
    }
  return 0;
}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
