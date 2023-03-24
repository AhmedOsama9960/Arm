/*
 * Switch.c
 *
 *  Created on: Feb 22, 2023
 *      Author: osama
 */

#ifndef HAL_SWITCH_SWITCH_C_
#define HAL_SWITCH_SWITCH_C_




/*****************************************Include **************************************************/
#include "../../inc/Switch.h"
#include "Switch_cfg.h"
/***************************************** Type ****************************************************/

extern const Switch_cfg_t Switch_cfg[Switch_Counts];


/******************************************Define ****************************************************/


/**************************************** Implementations ********************************************/
void Switch_Init(void)
{
	GPIO_init_t GPIO_cfg;
	for(u8 iter = 0; iter < Switch_Counts; iter++)
	{
		GPIO_cfg.Pin = Switch_cfg[iter].pin;
		GPIO_cfg.Port = Switch_cfg[iter].port;
		GPIO_cfg.Mode = Switch_cfg[iter].mode;
		GPIO_cfg.PUPD = Switch_cfg[iter].PUPD;
		GPIO_Init_Pin(&GPIO_cfg);
	}
}
void Switch_Get_Value(u8 Switch_Name, u8 * Value)
{
	GPIO_Get_Value(Switch_cfg[Switch_Name].port, Switch_cfg[Switch_Name].IDR_Pin , Value);
}

#endif /* HAL_SWITCH_SWITCH_C_ */
