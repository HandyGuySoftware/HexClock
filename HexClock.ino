// RTC Header Files
#include <Wire.h>
#include <ds3231.h>
#include <config.h>

// Program header files
#include "ButtonMgr.h"
#include "LEDMatrix.h"
#include "RTClock.h"
#include "ClockDigit.h"

//RGB matrix panel header files
#include <RGBmatrixPanel.h>
#include <gamma.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel LEDBoard(A, B, C, CLK, LAT, OE, false);

// Some global constants to give some flexibility
#define MATRIXHEIGHT 16
#define MATRIXWIDTH 32

// Set side of display digit array (digitArray[]).
// This is the array of symbols that can be displayed on the matrix.
// If you add symbols to the array, you *MUST* update this value.
#define DIGITARRAYSIZE 19

// Define Arduino I/O pins for button management
int modeButtonPin = 11; // Pin for mode setting button input
int setButtonPin = 12; // Pin for value setting button input
int ledLampPin = 13;  // Pin for display LED

ClockDigitClass *digitArray[DIGITARRAYSIZE]; // digit character maps
LedMatrixClass mtrx(MATRIXHEIGHT, MATRIXWIDTH);  // size of matrix array
RTClockClass clock;  // Real-time clock abstrator class
ButtonMgrClass buttonManager(modeButtonPin, setButtonPin, ledLampPin); // Manage mode & set buttons

/*
Given a particular character, find the index into the array of hex digit display maps (*digitArray[]) corresponding to that character.
*/
int SelectDigit(char sym)
{
	for (int i = 0; i < DIGITARRAYSIZE; ++i)
		if (digitArray[i]->getSymbol() == sym)
			return i;
			
	return -1;
}

/*
Given a particular number and number base, return a character (non-terminated string) representation of that string
*/
int Num2Char(int in, char *out, int base, int width)
{
	String strTmp;
	int i;

	strTmp = String(in, base);
	if (strTmp.length() != width)
	{
		for (i = 0; i < (width - strTmp.length()); ++i)
			strTmp = "0" + strTmp;
	}

	strTmp.toUpperCase();
	for (i = 0; i < width; ++i)
		out[i] = strTmp.charAt(i);

	return 0;
}


void setup()
{

	// Set mode buttons and indicator LED
	pinMode(modeButtonPin, INPUT); // Mode setting pin
	pinMode(setButtonPin, INPUT); // Set intividual values
	pinMode(ledLampPin, OUTPUT);  // Mode indicator - ON=setup mode  OFF=Running mode

	// Initialize the LED Matrix
	LEDBoard.begin();

	// Initialize the RTC
	Wire.begin();
	DS3231_init(DS3231_INTCN);

	/*
	Create an array with binary representations for the Hex characters.
	The full character map is not stored, just a binary representation of lit & unlit pixels for each character.
	0=unlit pixel, 1=lit pixel
	This costs some extra processing time for conversion to a visual form when needed,
	but saves a bunch of memory space for not having to store full character maps for each character.
	*/
	digitArray[0] = new ClockDigitClass(5, 3, '0', 0x2b6a);
	digitArray[1] = new ClockDigitClass(5, 3, '1', 0x6497);
	digitArray[2] = new ClockDigitClass(5, 3, '2', 0x73e7);
	digitArray[3] = new ClockDigitClass(5, 3, '3', 0x73cf);
	digitArray[4] = new ClockDigitClass(5, 3, '4', 0x5bc9);
	digitArray[5] = new ClockDigitClass(5, 3, '5', 0x79cf);
	digitArray[6] = new ClockDigitClass(5, 3, '6', 0x79ef);
	digitArray[7] = new ClockDigitClass(5, 3, '7', 0x7249);
	digitArray[8] = new ClockDigitClass(5, 3, '8', 0x7bef);
	digitArray[9] = new ClockDigitClass(5, 3, '9', 0x7bc9);
	digitArray[10] = new ClockDigitClass(5, 3, 'A', 0x2bed);
	digitArray[11] = new ClockDigitClass(5, 3, 'B', 0x6bae);
	digitArray[12] = new ClockDigitClass(5, 3, 'C', 0x3923);
	digitArray[13] = new ClockDigitClass(5, 3, 'D', 0x6b6e);
	digitArray[14] = new ClockDigitClass(5, 3, 'E', 0x79e7);
	digitArray[15] = new ClockDigitClass(5, 3, 'F', 0x79e4);
	digitArray[16] = new ClockDigitClass(3, 1, ':', 0x0005);
	digitArray[17] = new ClockDigitClass(3, 3, '/', 0x0054);
	digitArray[18] = new ClockDigitClass(3, 1, '|', 0x0007);
	
	return;
}

void loop()
{

	char numCharRep[5];

	// See if clock is in setup mode. If it is, keep looping until it's not
	do
	{
		buttonManager.checkClockSet();
	}
	while (buttonManager.getOpMode() == MODE_SETUP);
	 
	mtrx.setColor(COLOR_LT_BLUE);
	
	/*
	Time  Display - Hexidecimal
	*/
	// Display Hour
	Num2Char(clock.getUnit(UNIT_HOUR), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 0, 0);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 0, 4);
	mtrx.placeChar(digitArray[SelectDigit(':')], 1, 9);

	// Display Minute
	Num2Char(clock.getUnit(UNIT_MINUTE), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 0, 12);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 0, 16);
	mtrx.placeChar(digitArray[SelectDigit(':')], 1, 21);

	// Display Seconds
	Num2Char(clock.getUnit(UNIT_SECOND), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 0, 24);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 0, 28);
	
	/*
	Date Display - Hexidecimal
	*/
	// Display Month
	Num2Char(clock.getUnit(UNIT_MONTH), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 6, 0);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 6, 4);
	mtrx.placeChar(digitArray[SelectDigit('/')], 7, 8);

	// Display Day
	Num2Char(clock.getUnit(UNIT_DAY), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 6, 12);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 6, 16);
	mtrx.placeChar(digitArray[SelectDigit('/')], 7, 20);

	//Display Year
	Num2Char(clock.getUnit(UNIT_YEAR_SHORT), numCharRep, HEX, 2);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[0])], 6, 24);
	mtrx.placeChar(digitArray[SelectDigit(numCharRep[1])], 6, 28);

	/*
	Time Display - Binary
	Convert time values into a binary representation for display on the bottom part of the matrix.
	Why? Because we can. ;-)
	*/
	mtrx.placeBinary(clock.getUnit(UNIT_HOUR), 12, 8, 5);
	mtrx.placeBinary(clock.getUnit(UNIT_MINUTE), 13, 7, 6);
	mtrx.placeBinary(clock.getUnit(UNIT_SECOND), 14, 7, 6);
	mtrx.saveColor();
	mtrx.setColor(COLOR_LT_GREEN);
	mtrx.placeChar(digitArray[SelectDigit('|')], 12, 6);
	mtrx.placeChar(digitArray[SelectDigit('|')], 12, 13);
	mtrx.restoreColor();
	
	/*
	Date Display - Binary
	Convert date  values into a binary representation for display on the bottom part of the matrix
	*/
	mtrx.placeBinary(clock.getUnit(UNIT_MONTH), 12, 21, 4);
	mtrx.placeBinary(clock.getUnit(UNIT_DAY), 13, 20, 5);
	mtrx.placeBinary(clock.getUnit(UNIT_YEAR_SHORT), 14, 18, 7);
	mtrx.saveColor();
	mtrx.setColor(COLOR_LT_GREEN);
	mtrx.placeChar(digitArray[SelectDigit('|')], 12, 17);
	mtrx.placeChar(digitArray[SelectDigit('|')], 12, 25);
	mtrx.restoreColor();

	return;
}
