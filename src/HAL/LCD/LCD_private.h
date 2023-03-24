/*
 * LCD_private.h
 *
 *  Created on: Mar 22, 2023
 *      Author: osama
 */

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_


#define LCD_ClearDisplay     0x01

typedef enum {
	Clear_Screen 		= 0x01,		// clears the entire screen content
	Return_Home  		= 0x02,		// Sets DDRAM to the entry point 00H and returns the cursor as well
	Entry_ModeSet		= 0x06,		// To enable the shift of the screen when cursor moves left or right
	Display_Off  		= 0x08,		// Display off and cursor as well
	Display_On   		= 0x0C,		// Set the display and Cursor off
	Cursor_On_Display_On= 0x0E,		// display on and cursor on
	Shift_Left   		= 0x18,		// Moves display to the left
	Shift_Right  		= 0x1C,		// Moves display to right
	Function_Sets 		= 0x3C,		// 8bit mode and 2 line with 5x11
	LCD_SetAddressCGRAM = 0x40,		// Set the CGRAM's address in Address Counter{AC}
	LCD_SetAddressDDRAM = 0x80,		// Set the DDRAM's address in Address Counter{AC}
	First_Row_Address   = 0x80,
	Second_Row_Address	= 0xC0
}LCD_Instructions;


#endif /* HAL_LCD_LCD_PRIVATE_H_ */
