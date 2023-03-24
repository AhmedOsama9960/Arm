/*
 * Sched_cfg.h
 *
 *  Created on: Mar 19, 2023
 *      Author: osama
 */

/*------------------------------------------ Include ---------------------------------------*/
#include "../My_Lib/Typedef.h"

/*------------------------------------------Define ---------------------------------------------*/
#define num		6

/*------------------------------------------Types--------------------------------------------*/
typedef void (*CBF)(void) ;

typedef struct {

	char * name;
	CBF Task_Cbf;
	u32 Period;
	u32 Start_Delay;
}Taskinfo_t;

typedef struct
{
	Taskinfo_t Taskinfo;
	u32 remainTimeMS;
}Task_t;

/*--------------------------------------Declarations---------------------------------*/

const Taskinfo_t Task_info[num];

