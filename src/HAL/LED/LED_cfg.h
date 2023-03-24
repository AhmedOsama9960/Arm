/*
 * LED_cfg.h
 *
 *  Created on: Feb 21, 2023
 *      Author: osama
 */

#ifndef HAL_LED_LED_CFG_H_
#define HAL_LED_LED_CFG_H_




#endif /* HAL_LED_LED_CFG_H_ */

/********************************* types ***********************************/

typedef enum {
	led_Red,
	led_Green,
	Led_Yellow,
	Led_Black,
	led_count
}led_usage;

typedef struct
{
	void* port;
	u8 pin;
	u8 mode;
	u8 speed;
	u8 PUPD;
	u8 circuit_type;
	u8 name;
	u8 color;
	u8 BSRR_Pin;
}Led_cfg_t;



/************************************ define *********************************/
