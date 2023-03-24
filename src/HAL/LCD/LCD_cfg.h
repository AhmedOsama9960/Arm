/*
 * LCD_cfg.h
 *
 *  Created on: Mar 22, 2023
 *      Author: osama
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/*----------------------------------------Include --------------------------------------*/
#include "../../My_Lib/Typedef.h"

/*---------------------------------------Define--------------------------------------*/
#define LCD_DataGroup			GPIO_A
#define LCD_ControlGroup		GPIO_B

/*--------------------------------------Type-----------------------------------------*/
typedef enum
{	// write the pin you wish to make it as output
	DataPin0,
	DataPin1,
	DataPin2,
	DataPin3,
	DataPin4,
	DataPin5,
	DataPin6,
	DataPin7,
	LCD_ControlE,
	LCD_ControlRW,
	LCD_ControlRS,
	LCD_Pins_Counts = 11
}LCD_pins;

typedef struct {

	void* port;
	u8 pin;
	u8 mode;
	u8 speed;
	u8 PUPD;
	u8 circuit_type;
	u8 name;
	u8 color;
	u16 BSRR_Pin;

} __attribute__((packed ,aligned(1))) Lcd_cfg_t;

#endif /* HAL_LCD_LCD_CFG_H_ */
