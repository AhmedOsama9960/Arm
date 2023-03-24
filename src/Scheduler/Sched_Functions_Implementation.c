/*
 * Sched_Functions_Implementation.c

 *
 *  Created on: Mar 20, 2023
 *      Author: osama
 */


/*---------------------------------------- Include---------------------------------*/
#include "../inc/LED.h"
#include "../inc/LCD.h"
#include "../My_Lib/Typedef.h"
#include "../inc/Switch.h"

/*---------------------------------------- Define---------------------------------*/
#define high	    1
#define low		    0
#define Mod_2	    2
#define _5Readings	5

#define LED_1	    0
#define LED_2	    1
#define LED_3	    2
#define LED_4		3

#define Switch_0	0

#define Pressed		0
#define unpressed	1
/*---------------------------------------- Declaration---------------------------------*/
static u8 counter1 = high;
static u8 counter2 = high;
static u8 counter3 = high;
static u8 switch_value = unpressed;

/*---------------------------------------- Implementations------------------------*/

void LED1(void)		//Every 3000ms
{
		led_set_state(LED_1,counter1);
		counter1 ^= high;
}

void LED2(void)		//Every 2000ms
{
		led_set_state(LED_2,counter2);
		counter2 ^= high;
}

void LED3(void)		//Every 1000ms
{
		led_set_state(LED_3,counter3);
		counter3 ^= high;
}

//Solution for debouncing by sampling every 10ms to detect the stable case of the switch debouncing
void DebouncingSwitch(void) // Every 10ms and 20ms for switch pressing so the sampling must be a multiplicative value of pressing switch
{
	//trace_printf("Debouncing\n");
	static u8 switch_counter = 0;	//tmam
	u8 current_state;
	static u8 previous_switch_state;	//tmam

	Switch_Get_Value(Switch_0, &current_state);
	//get the state of the switch

	//check if it is the same as the previous state
	if(current_state == previous_switch_state)
	{
		switch_counter++;
	}
	else
	{
		switch_counter = 0;
	}

	if(switch_counter == _5Readings)
	{
		switch_value = current_state;
		switch_counter = 0;
	}
	else{ /* Misra Rule */ }

	//assign it in the previous state
	previous_switch_state = current_state;
}

void Switch(void)			//Every 20ms
{
	//trace_printf("SWIIIIIIIIIIIIIIIIIIIIIITCH0\n");
	if(switch_value == Pressed)
	{
		led_set_state(LED_4,high);
	}
	else
	{
		led_set_state(LED_4,low);
	}
}

void LCD_App(void)
{
	u8 res;
	if(switch_value == Pressed){
	res = Lcd_writestringAsync("RamadanKareem" , 13 , 1 , 1 );
	//trace_printf("Res = %d\n",res);
	//write_seq();
	} else {
		LCD_Clear();
	}
}
