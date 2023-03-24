/*
 * LCD.c
 *
 *  Created on: Mar 22, 2023
 *      Author: osama
 */


/*****************************************Include **************************************************/
#include "../../inc/LCD.h"
#include "LCD_cfg.h"
#include "LCD_private.h"
#include "../../inc/GPIO.h"

/******************************************Define ****************************************************/
#define low		0
#define high	1

#define Init_1		0
#define Init_2		1

#define No_Elements_Per_Block 	8
#define Max_Screen_Length		15

#define second_line				2
#define first_place				0
/******************************************Declaration ****************************************************/
u8 init_Done = 0;
static u8 state = Init_1;
u8 ReqType = ReqType_NoReq;
u8 Counter_Writing;

static LCD_t LCD_Storage;
extern const Lcd_cfg_t Lcd_cfg[LCD_Pins_Counts];

/***************************************Implementations********************************************************/
/*
-----------                   ----------
| ATmega32  |                 |   LCD    |
|           |                 |          |
|        PD7|---------------->|D7        |
|        PD6|---------------->|D6        |
|        PD5|---------------->|D5        |
|        PD4|---------------->|D4        |
|        PD3|---------------->|D3        |
|        PD2|---------------->|D2        |
|        PD1|---------------->|D1        |
|        PD0|---------------->|D0        |
|           |                 |          |
|        PA2|---------------->|E         |
|        PA1|---------------->|RW        |
|        PA0|---------------->|RS        |
-----------                   ----------
*/
/*------------------------------------Commands -------------------------------*/
void LCD_voidWriteCommand(s8 Copy_s8Command)	//its used to write the command
{
	GPIO_Port_Value(LCD_DataGroup , Copy_s8Command);

	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlRS].port, Lcd_cfg[LCD_ControlRS].BSRR_Pin , low ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// set it 0 for command Register
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlRW].port, Lcd_cfg[LCD_ControlRW].BSRR_Pin , low ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// set it 0 for write status
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlE].port, Lcd_cfg[LCD_ControlE].BSRR_Pin  , high ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// Enable the control
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlE].port, Lcd_cfg[LCD_ControlE].BSRR_Pin  , low  ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// Enable the control
}

void LCD_voidWriteData(s8 Copy_s8Data)
{
	GPIO_Port_Value(LCD_DataGroup , Copy_s8Data);
	//trace_printf("WritingNow");
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlRS].port, Lcd_cfg[LCD_ControlRS].BSRR_Pin , high ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// set it 0 for command Register
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlRW].port, Lcd_cfg[LCD_ControlRW].BSRR_Pin , low  ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// set it 0 for write status
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlE].port, Lcd_cfg[LCD_ControlE].BSRR_Pin  , high  ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// Enable the control
	GPIO_Write_PinValue(Lcd_cfg[LCD_ControlE].port, Lcd_cfg[LCD_ControlE].BSRR_Pin  , low   ^ Lcd_cfg[LCD_ControlRS].circuit_type);		// Enable the control
}


void LCD_Pins_Init(void)
{
	GPIO_init_t GPIO_cfg;

	for(u8 indx = 0; indx <LCD_Pins_Counts; indx++)
	{
		GPIO_cfg.Mode			 = Lcd_cfg[indx].mode;			/* Mode_out*/
		GPIO_cfg.Pin 			 = Lcd_cfg[indx].pin;			/* No of pin */
		GPIO_cfg.Port			 = Lcd_cfg[indx].port;			/* Port A,B,C,D */
		GPIO_cfg.Speed			 = Lcd_cfg[indx].speed;			/* Speed Range */
		GPIO_cfg.Circuit_Type 	 = Lcd_cfg[indx].circuit_type;	/* active high or active low */
		GPIO_cfg.PUPD 			 = Lcd_cfg[indx].PUPD;			/* Pull up or Push Down or no pull up or down*/
		GPIO_Init_Pin(&GPIO_cfg);
	}
}
/*------------------------------------Init -------------------------------*/



/*
 *
 *  What if it returns not init or busy the data from the user will be lost
 */

LCD_ErrorStatus init_LCD_Seq(void)	//every 2ms
{
	switch(state)
	{
	case Init_1:
		LCD_voidWriteCommand(Function_Sets);
		state = Init_2;
		break;

	case Init_2:
		LCD_voidWriteCommand(Cursor_On_Display_On);
		state = LCD_NOT_init;
		break;

	case LCD_NOT_init:
		LCD_voidWriteCommand(Clear_Screen);
		state = LCD_Ok;
		break;

	case LCD_Ok:
		LCD_voidWriteCommand(Entry_ModeSet);
		LCD_voidWriteCommand(First_Row_Address);
		init_Done = 1;
		state = LCD_IdleState;
		//trace_printf("done");
		break;
	}
	return state;
}
/*------------------------------------Main Task -------------------------------*/
void LCD_Task(void)
{
	if(init_Done != 1)
	{
		//this is an init function needs to be executed for a period of time not all the time
		init_LCD_Seq();
	}
	else
	{
		switch(ReqType)
		{
		case ReqType_Write:
			 write_seq();		//Sub service write a char per time
			break;
		case ReqType_Clear:
			clear_seq();
		break;
		}
	}
	//return state;
}

/*------------------------------------Position on LCD -------------------------------*/
void LCD_voidGoToXY(u8 X,u8 Y)
{
u8 Position[] = {First_Row_Address, Second_Row_Address};
LCD_voidWriteCommand(Position[X-1] + Y);
}
/*------------------------------------Write -------------------------------*/
LCD_ErrorStatus Lcd_writestringAsync(const char * str, u8 length, u8 posX, u8 posY)
{
	//trace_printf("writestring\n");
	u8 res = LCD_busystate;
	if(state == LCD_IdleState)
	{
		ReqType = ReqType_Write;
		res = LCD_Ok;
		state = LCD_busystate;

		LCD_Storage.string = str;
		LCD_Storage.len = length;
		LCD_Storage.posx = posX;
		LCD_Storage.posy = posY;

		LCD_voidGoToXY(LCD_Storage.posx , LCD_Storage.posy);
		Counter_Writing = 0;
	}
	else if(state <= LCD_NOT_init)
	{
		res = LCD_NOT_init;
	}
	return res;
}

void write_seq(void)
{
	if(Counter_Writing < LCD_Storage.len)
	{
		if(Counter_Writing == Max_Screen_Length)
		{
			LCD_voidGoToXY(2,0);
			LCD_voidWriteData(LCD_Storage.string[Counter_Writing]);
		}
		else
		{
		LCD_voidWriteData(LCD_Storage.string[Counter_Writing]);
		}
		Counter_Writing++;
	} else {
		state = LCD_IdleState;
		ReqType = ReqType_NoReq;
	}
}
/*------------------------------------Clear -------------------------------*/
void LCD_Clear(void)
{
	ReqType = ReqType_Clear;
}
void clear_seq(void)
{
	LCD_voidWriteCommand(LCD_ClearDisplay);
	ReqType = ReqType_NoReq;
	state = LCD_IdleState;
}



/***************************************END********************************************************/
