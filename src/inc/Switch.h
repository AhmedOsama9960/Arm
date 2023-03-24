/*
 * Switch.h
 *
 *  Created on: Feb 22, 2023
 *      Author: osama
 */

#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_


/*****************************************Include **************************************************/
#include "../inc/GPIO.h"

/***************************************** Type ****************************************************/

typedef enum
{
	Switch_Unpressed,
	Switch_Released,
	Switch_PreReleased,
	Switch_Pressed

}Switch_ErrorState;


/******************************************Define ****************************************************/




/***************************************APIs********************************************************/
void Switch_Init(void);
void Switch_Get_Value(u8 Switch_Name, u8 * Value);


/***************************************END********************************************************/





#endif /* INC_SWITCH_H_ */
