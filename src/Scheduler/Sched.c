/*
 * Sched.c
 *
 *  Created on: Mar 19, 2023
 *      Author: osama
 */


/*-------------------------------------------- Include ---------------------------------------------*/

#include "../inc/Sched.h"
#include "Sched_cfg.h"
#include "../inc/Systick_Stm.h"
#include "../inc/LED.h"
#include "diag/Trace.h"

/**---------------------------------------------Define------------------------------------------------*/

#define _25MHz				25000000
#define _5Ms				5

/*----------------------------------------- Declaration----------------------------------------------*/
// Type of Task
static Task_t Tasks[num];

/* All Global Vars are zero initialized*/
u8 Sched_Flag = 0;
u8 CPU_LOAD;
u8 index;

/*---------------------------------------------Implementations------------------------------------------*/

void Sched_init(void)
{
	// Config for Systick
	Systick_Set_Period_MS(_5Ms , _25MHz);
	Systick_Set_CBF(Tick_CBF);

	// Tasks
	for(index = 0; index < num ; index++)
	{
		Tasks[index].Taskinfo 		 = Task_info[index];
		Tasks[index].remainTimeMS 	 = Task_info[index].Start_Delay;
	}
}

void Sched(void)
{
	// Tasks
	for(index = 0; index < num ; index++)
	{
		if(Tasks[index].Taskinfo.Task_Cbf)
		{
			if(Tasks[index].remainTimeMS == 0)
			{
				Tasks[index].Taskinfo.Task_Cbf();
				Tasks[index].remainTimeMS = Tasks[index].Taskinfo.Period - _5Ms;
			}
			else
			{
				Tasks[index].remainTimeMS -= _5Ms;
			}
		}
		else
		{
			//Misra Rule
		}
	}
}

void Sched_start(void)
{
	SysTick_start();
	while(1)
	{
		if(Sched_Flag == 1)
		{
			Sched();
			Sched_Flag = 0;
		}
		else
		{
			//Misra Rule
		}
	}
}


void Tick_CBF(void)
{
	if(Sched_Flag == 0)
	{
		Sched_Flag = 1;
	}
	else
	{
		trace_printf("CPULOAD = %d\n",CPU_LOAD);
		CPU_LOAD++;
	}
}


/*------------------------------------------------- END ---------------------------------------------*/
