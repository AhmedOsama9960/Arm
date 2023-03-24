/*
 * Switch_cfg.h
 *
 *  Created on: Feb 22, 2023
 *      Author: osama
 */


/*****************************************Include **************************************************/


/***************************************** Type ****************************************************/

typedef struct
	{
		void* port;
		u8 pin;
		u8 mode;
		u8 speed;
		u8 PUPD;
		u8 IDR_Pin;
	}Switch_cfg_t;

typedef enum
	{
		Switch_for_Led,
		Switch_for_SvSg,
		Switch_Counts
	}Switch_Types;


/******************************************Define ****************************************************/

