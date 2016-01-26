// ClockDigit.h

#ifndef _CLOCKDIGIT_h
#define _CLOCKDIGIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ClockDigitClass
{
public:
	ClockDigitClass(int, int, char, uint16_t);
	~ClockDigitClass();
	int getDisplayRows() { return rows; } // Return number of rows (height) of the displayed character
	int getDisplayColumns() { return columns; } // Return number of columns (width) of the displayed character
	unsigned int getBitValue(int bitnum) { return charMap & (0x8000 >> bitnum); } // Looks for a certain bit in the bitmap and returns zero (no bit set) or nonzero (bit set)
	char getSymbol() { return symbol; }

private:
	uint16_t charMap;
	int rows, columns;
	char symbol;
};

#endif

