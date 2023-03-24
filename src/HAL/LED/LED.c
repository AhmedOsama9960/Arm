/*
  * LED.c
 *
 *  Created on: Feb 21, 2023
 *      Author: osama
 */


/********************Include **************/
#include "../../inc/LED.h"
#include "LED_cfg.h"

/*****************Define *******************/

#define init_value 		0

/***************Declaration****************/

extern const Led_cfg_t Led_cfg[led_count];


/********************************Implementations ****************/

void led_init(void)
{
	GPIO_init_t GPIO_cfg;

	for(u8 indx = init_value; indx <led_count; indx++)
	{
		GPIO_cfg.Mode			 = Led_cfg[indx].mode;			/* Mode_out*/
		GPIO_cfg.Pin 			 = Led_cfg[indx].pin;			/* No of pin */
		GPIO_cfg.Port			 = Led_cfg[indx].port;			/* Port A,B,C,D */
		GPIO_cfg.Speed			 = Led_cfg[indx].speed;			/* Speed Range */
		GPIO_cfg.Circuit_Type 	 = Led_cfg[indx].circuit_type;	/* active high or active low */
		GPIO_cfg.PUPD 			 = Led_cfg[indx].PUPD;			/* Pull up or Push Down or no pull up or down*/
		GPIO_Init_Pin(&GPIO_cfg);
	}

}
void led_set_state(u8 led, u8 state)
{
	GPIO_Write_PinValue(Led_cfg[led].port, Led_cfg[led].BSRR_Pin, (state ^ Led_cfg[led].circuit_type));
}
