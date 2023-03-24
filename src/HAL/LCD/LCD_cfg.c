/*
 * LCD_cfg.c
 *
 *  Created on: Mar 23, 2023
 *      Author: osama
 */



/* ******************************Include ***********************************/

#include "../../inc/GPIO.h"
#include "LCD_cfg.h"

/********************************* types ***********************************/


const Lcd_cfg_t Lcd_cfg[LCD_Pins_Counts] =
						{
	[DataPin0] = {
							.port		  = LCD_DataGroup,			            // Port A
							.pin  		  = pin_0,			            // Pin No 0
							.mode 		  = Output, 		            //led_mode_high
							.speed		  = Low_Speed,		            // Speed
							.PUPD 		  = No_Pullup_down,		        // Pull-up / Pull Down
							.circuit_type = Push_Pull,			// Open drain or PushPull
							.BSRR_Pin	  = Set_Pin_0

					},

	[DataPin1] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_1,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_1
					},
	[DataPin2] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_2,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_2
								},
	[DataPin3] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_3,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_3
								},
	[DataPin4] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_4,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_4
								},
	[DataPin5] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_5,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_5
								},
	[DataPin6] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_6,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_6
								},
	[DataPin7] =  {
							.port 		  = LCD_DataGroup,
							.pin  		  = pin_7,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_7
								},
	[LCD_ControlE] =  {
							.port 		  = LCD_ControlGroup,
							.pin  		  = pin_14,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_14
								},
	[LCD_ControlRW] =  {
							.port 		  = LCD_ControlGroup,
							.pin  		  = pin_13,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_13
								},
	[LCD_ControlRS] =  {
							.port 		  = LCD_ControlGroup,
							.pin  		  = pin_12,
							.mode		  = Output,
							.speed		  = Low_Speed,
							.PUPD		  = No_Pullup_down,
							.circuit_type = Push_Pull,
							.BSRR_Pin	  = Set_Pin_12
								}

						};



/*-----------------------------------END ----------------------------------*/

