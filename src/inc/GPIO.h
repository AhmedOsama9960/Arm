/*
 *  * GPIO.h
 *
 *  Created on: Feb 14, 2023
 *      Author: osama
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

/***************************************** Include **********************************************/
#include "../My_Lib/Typedef.h"


/**************************************** Define ************************************************/
#define High 		1
#define Low			0

#define PORT_Max_Value		0xffff


/**************************************** Types *************************************************/
/* Bit Masking for each pin */
typedef struct {
	void* Port;
	u8 Pin;
	u8 Speed;
	u8 Mode;
	u8 PUPD;
	u8 Circuit_Type;
	u8 AFValue;
}GPIO_init_t;


typedef enum {

Set_Pin_0  = 0x01,
Set_Pin_1  = 0x02,
Set_Pin_2  = 0x04,
Set_Pin_3  = 0x08,
Set_Pin_4  = 0x10,
Set_Pin_5  = 0x20,
Set_Pin_6  = 0x40,
Set_Pin_7  = 0x80,
Set_Pin_8  = 0x100,
Set_Pin_9  = 0x200,
Set_Pin_10 = 0x400,
Set_Pin_11 = 0x800,
Set_Pin_12 = 0x1000,
Set_Pin_13 = 0x2000,
Set_Pin_14 = 0x4000,
Set_Pin_15 = 0x8000

} Set_Pins;


typedef enum
{
	pin_0 = 0,
	pin_1 = 2,
	pin_2 = 4,
	pin_3 = 6,
	pin_4 = 8,
	pin_5 = 10,
	pin_6 = 12,
	pin_7 = 14,
	pin_8 = 16,
	pin_9 = 18,
	pin_10 = 20,
	pin_11 = 22,
	pin_12 = 24,
	pin_13 = 26,
	pin_14 = 28,
	pin_15 = 30
}Pin_No;

typedef enum {
	GPIO_Ok,
	GPIO_Nok,
	GPIO_Wrong_Port,
	GPIO_Wrong_Pin
}GPIO_ErrorStatus;

/************************************** Configurations ******************************************/

#define PORT_Cofig			GPIO_B
#define GPIO_A			(void*)0x40020000
#define GPIO_B			(void*)0x40020400
#define GPIO_C			(void*)0x40020800
#define GPIO_D			(void*)0x40020C00
#define GPIO_E			(void*)0x40021000

/* Modes OTYPER Register */
#define Push_Pull			    0x00

#define Open_Drain_Pin0		    0x01
#define Open_Drain_Pin1		    0x02
#define Open_Drain_Pin2		    0x04
#define Open_Drain_Pin3		    0x08
#define Open_Drain_Pin4		    0x10
#define Open_Drain_Pin5		    0x20
#define Open_Drain_Pin6		    0x40
#define Open_Drain_Pin7		    0x80
#define Open_Drain_Pin8		    0x100
#define Open_Drain_Pin9		    0x200
#define Open_Drain_Pin10		0x400
#define Open_Drain_Pin11		0x800
#define Open_Drain_Pin12		0x1000
#define Open_Drain_Pin13		0x2000
#define Open_Drain_Pin14		0x4000
#define Open_Drain_Pin15		0x8000

/* Speed */
#define Speed_Type			Low_Speed

#define Low_Speed			0x00
#define Medium_Speed		0x01
#define High_Speed			0x02
#define Very_High_Speed		0x03

/*     Pins Config   MODER Register  */
#define Input			0x00
#define Output			0x01
#define AF				0x02				// Alternative Function
#define Analog			0x03






/* ************ PUPD Register *****************/
#define No_Pullup_down			0x00
#define Pull_UP					0x01
#define PUll_Down				0x02

/*****************************************APIS***************************************************/
void GPIO_Init_Pin(GPIO_init_t * Init_Pins);
void GPIO_Init(void);
GPIO_ErrorStatus GPIO_Write_PinValue(void* GPIO_Group, Set_Pins Set_Pin, u8 GPIO_Status);
GPIO_ErrorStatus GPIO_Get_Value(void* GPIO_Group, Set_Pins Set_Pin, u8 * CpyPinValue);
GPIO_ErrorStatus GPIO_Port_Value(void* GPIO_Group, u16 GPIO_Value);

/******************************************END***************************************************/

#endif /* INC_GPIO_H_ */
