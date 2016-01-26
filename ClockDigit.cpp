// 
// 
// 

#include "ClockDigit.h"

ClockDigitClass::ClockDigitClass(int digitRows, int digitColumns, char symb, uint16_t initValue)
{
	rows = digitRows;		// # of rows in character representation - passed in
	columns = digitColumns;	// # of columns in character representation - passed in
	symbol = symb;			// ASCII symbol for character
	charMap;			// A 16-bit bitmap of the character  - *** NEED	TO FIX THIS TO HANDLE CHARACTERS LARGER THAN 5X3

	/*
	charMap is a 16-bit string of 1's & 0's that denote the character map when displayed.
	For the standard 15-pixel (5x3) characters, only the 15 LSBs are used
	When organized in the rows and columns of the character map, the 1's will be the outline of the lit LEDs in the display.
	The 0's will not be lit in the display.
	This means more processing to later convert the bitmap back to displayable characters,
	but saves a lot of memory over having to store the full character matrix for each character.
	*/
	charMap = initValue;
}

ClockDigitClass::~ClockDigitClass()
{
}
