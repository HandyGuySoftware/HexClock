// LEDMatrix.h

#include "ClockDigit.h"

#ifndef _LEDMATRIX_h
#define _LEDMATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define COLOR_RED 7,0,0
#define COLOR_LT_RED 1,0,0
#define COLOR_MED_RED 4,0,0
#define COLOR_GREEN 0,7,0
#define COLOR_LT_GREEN 0,1,0
#define COLOR_MED_GREEN 0,4,0
#define COLOR_BLUE 0,0,7
#define COLOR_LT_BLUE 0,0,2
#define COLOR_MED_BLUE 0,0,4
#define COLOR_WHITE 7,7,7
#define COLOR_BLACK 0,0,0

class LedMatrixClass
{
public:
	LedMatrixClass(int h, int w);
	~LedMatrixClass() {};
	void setPixel(int, int);
	void clearPixel(int, int);
	void placeChar(ClockDigitClass *, int, int);
	void placeBinary(int, int, int, int);
	void setColor(int, int, int);
	void clearScreen();
	void fillScreen();
	void saveColor();
	void restoreColor();
	
private:
	int colorRed, colorGreen, colorBlue;
	int saveColorRed, saveColorGreen, saveColorBlue;
};

#endif

