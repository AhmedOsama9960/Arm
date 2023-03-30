/*
 * Sched_cfg.c
 *
 *  Created on: Mar 19, 2023
 *      Author: osama
 */


/*-------------------------------------------- Include ---------------------------------------------*/

#include "Sched_cfg.h"
#include "../inc/LCD.h"
#include "Schedler_Functions.h"
/**---------------------------------------------Define------------------------------------------------*/

#define High_Prio_0			0
#define Lower_Prio_1		1
#define Lower_Prio_2		2
#define Lower_Prio_3		3
#define Lower_Prio_4		4
#define Lower_Prio_5		5


/*---------------------------------------------Implementations------------------------------------------*/


const Taskinfo_t Task_info[num] = {
	  //[High_Prio_0]  = { .name = "LED1" 	 , .Task_Cbf 	 = LED1			   , .Period = 500, .Start_Delay = 0 },
	  //[Lower_Prio_1] = { .name = "LED2" 	 , .Task_Cbf 	 = LED2 	 	   , .Period = 1000, .Start_Delay = 500 },
	  //[Lower_Prio_2] = { .name = "LED3" 	 , .Task_Cbf 	 = LED3 		   , .Period = 1500, .Start_Delay = 1000 },
	//[Lower_Prio_3] = { .name = "Debounce"  , .Task_Cbf 	 = DebouncingSwitch, .Period = 5  , .Start_Delay = 10 },
	//[Lower_Prio_4] = { .name = "Switch"    , .Task_Cbf 	 = Switch		   , .Period = 20  , .Start_Delay = 0},
	  [Lower_Prio_3] = { .name = "LCD"       , .Task_Cbf 	 = LCD_Task		   , .Period = 5  , .Start_Delay = 50},
	  [Lower_Prio_4] = { .name = "LCD"       , .Task_Cbf 	 = LCD_App		   , .Period = 10  , .Start_Delay = 100},
	  [Lower_Prio_5] = { .name = "UART"       , .Task_Cbf 	 = USART_App	   , .Period = 5  , .Start_Delay = 100},

};



/*------------------------------------------------- END ---------------------------------------------*/
