/*
 * LED_cfg.c
 *
 *  Created on: Feb 21, 2023
 *      Author: osama
 */


/* ******************************Include ***********************************/

#include "../../inc/GPIO.h"
#include "LED_cfg.h"

/********************************* types ***********************************/


const Led_cfg_t Led_cfg[led_count] =
						{
	[led_Red] = {
							.port		  = GPIO_B,			            // Port A
							.pin  		  = pin_0,			            // Pin No 0
							.mode 		  = Output, 		            //led_mode_high
							.speed		  = Low_Speed,		            // Speed
							.PUPD 		  = No_Pullup_down,		        // Pull-up / Pull Down
							.circuit_type = Push_Pull,			// Open drain or PushPull
							.BSRR_Pin	  = Set_Pin_0

					},

	[led_Green] =  {
							.port 		  = GPIO_B,
							.pin  		  = pin_1,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_1
					},
	[Led_Yellow] =  {
							.port 		  = GPIO_B,
							.pin  		  = pin_2,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_2
								},
	[Led_Black] =  {
							.port 		  = GPIO_A,
							.pin  		  = pin_5,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_5
								}
						};







