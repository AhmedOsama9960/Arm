/*
 * Switch_cfg.c
 *
 *  Created on: Feb 22, 2023
 *      Author: osama
 */


/*****************************************Include **************************************************/
#include "../../inc/GPIO.h"
#include "Switch_cfg.h"

/***************************************** Type ****************************************************/

const Switch_cfg_t Switch_cfg[Switch_Counts]=
							  {
									  [Switch_for_Led] = {
											  	  	  	  	  .port  = GPIO_B,
															  .pin 	 = pin_3,
															  .speed = Low_Speed,
															  .mode  = Input,
															  .IDR_Pin  = Set_Pin_3,
															  .PUPD  = Pull_UP

									  },
									  [Switch_for_SvSg] = {
															.port  = GPIO_B,
															.pin   = pin_4,
															.speed = Low_Speed,
															.mode  = Input,
															.IDR_Pin  = Set_Pin_4,
															.PUPD  = Pull_UP

									  }
							  };


/******************************************Define ****************************************************/

