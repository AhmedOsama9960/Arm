/*
 * LCD.h
 *
 *  Created on: Mar 22, 2023
 *      Author: osama
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
/*****************************************Include **************************************************/
#include "../My_Lib/Typedef.h"

/***************************************** Type ****************************************************/

typedef struct
{
	const char * string;
	u8 len;
	u8 posx;
	u8 posy;
}LCD_t;

typedef enum {
	LCD_IdleState = 1,
	LCD_NOT_init,
	LCD_Ok,
	LCD_busystate
}LCD_ErrorStatus;

typedef enum
{
	ReqType_Idle,
	ReqType_NoReq,
	ReqType_Write,
	ReqType_Clear
}reqtype_t;

/******************************************Define ****************************************************/



/***************************************APIs********************************************************/
void LCD_Pins_Init(void);
LCD_ErrorStatus Lcd_writestringAsync(const char * str, u8 length, u8 posX, u8 posY);
LCD_ErrorStatus init_LCD_Seq(void);
void LCD_Task(void);
void LCD_voidWriteCommand(s8 Copy_s8Command);
void LCD_voidWriteData(s8 Copy_s8Command);
void LCD_voidGoToXY(u8 X,u8 Y);
void write_seq(void);
void LCD_Clear(void);
void clear_seq(void);

/***************************************END********************************************************/



#endif /* INC_LCD_H_ */
