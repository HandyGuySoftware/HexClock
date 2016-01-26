// 
// 
// 

#include "ButtonMgr.h"
#include "LEDMatrix.h"
#include "ClockDigit.h"
#include "RTClock.h"

// Define Arduino I/O pins for button management
extern LedMatrixClass mtrx;

extern int Num2Char(int, char *, int, int);
extern int SelectDigit(char);
extern ClockDigitClass *digitArray[]; // digit character maps
extern RTClockClass clock;  // Real-time clock abstrator class

ButtonMgrClass::ButtonMgrClass(int mPin, int sPin, int lPin)
{
	modePin = mPin;
	setPin = sPin;
	ledPin = lPin;
	
	modeButtonState = setButtonState = HIGH; // Buttons not pressed

	currentOpMode = MODE_RUN;
	currentSetupMode = SETUP_NONE;
	milCounter = 0;
}

int ButtonMgrClass::getModeButtonState()
{
	return digitalRead(modePin);
}

int ButtonMgrClass::getSetupButtonState()
{
	return digitalRead(setPin);
}

// Check if mode button pressed for more than 3 seconds
int ButtonMgrClass::modeBtnLongPress()
{
	int current = millis();
	return ((current - milCounter) >= 3000); // check for 3 second delay
}

int ButtonMgrClass::checkClockSet()
{

	if ((getModeButtonState() == HIGH) && (getSetupButtonState() == HIGH)) // Neither button is pressed.
	{
		switch (getOpMode())
		{
		case MODE_RUN:
			return 0;
			break;
		case MODE_PENDING:
			milCounter = 0; // In case we were 
			setOpMode(MODE_RUN);
			return 0;
			break;
		case MODE_SETUP:
			break;
		}
	}

	// If both buttons are pressed for 5 seconds, reset clock!
	if ((getModeButtonState() == LOW) && (getSetupButtonState() == LOW)) 
	{
		int mtmp1 = millis(), mtmp2;

		while ((getModeButtonState() == LOW) && (getSetupButtonState() == LOW))
		{
			mtmp2 = millis();
			if ((mtmp2 - mtmp1) >= 5000) // Wait for 5 seconds
			{
				mtrx.fillScreen();
				clock.resetClock();
				setOpMode(MODE_RUN);
				setSetupMode(SETUP_NONE);
				milCounter = 0;
			}
		}

		mtrx.clearScreen();
		return 0;
	}

	if (getModeButtonState() == LOW) // Mode button is pressed
	{
		switch (getOpMode())
		{
		case MODE_RUN:
			// Currently in normal mode - switch to pending setup mode, start long-press counter
			setOpMode(MODE_PENDING);
			milCounter = millis(); // reset long-press counter
			return 0;
			break;
		case MODE_PENDING:
			// In pending set up mode - see if the button has been pressed for a while
			if (modeBtnLongPress())
			{
				setOpMode(MODE_SETUP);
				setSetupMode(SETUP_HOUR);
				milCounter = 0;
				digitalWrite(ledPin, HIGH);
				delay(250);
				while ((getModeButtonState() == LOW)); // Wait until button is released. Otherwise will loop through options uncontrollably
				mtrx.clearScreen();
			}
			return 0;
			break;
		case MODE_SETUP: // Currently in setup mode - switch the thing you're setting
			mtrx.clearScreen();
			if (++currentSetupMode == setupArraySize) // done with setup
			{
				setOpMode(MODE_RUN);
				setSetupMode(SETUP_NONE);
				digitalWrite(ledPin, LOW);
				milCounter = 0;
			}
			delay(250);
			while ((getModeButtonState() == LOW)); // Wait until button is released. Otherwise will loop through options uncontrollably
			return 0;
			break;
		}
	}

	if (getSetupButtonState() == LOW) // Setup button is pressed
	{
		switch (getSetupMode())
		{
		case SETUP_HOUR:
			clock.incrementUnit(UNIT_HOUR);
			break;
		case SETUP_MINUTE:
			clock.incrementUnit(UNIT_MINUTE);
			break;
		case SETUP_DAY:
			clock.incrementUnit(UNIT_DAY);
			break;
		case SETUP_MONTH:
			clock.incrementUnit(UNIT_MONTH);
			break;
		case SETUP_YEAR:
			clock.incrementUnit(UNIT_YEAR);
			break;
		case SETUP_NONE:
			break;
		}

		while ((getSetupButtonState() == LOW)) // Wait until button is released. Otherwise will loop through options uncontrollably
		{
			if (getModeButtonState() == LOW) // Mode buton pressed in the middle
				return 0;
		}
	
	}
	runClockSet(getOpMode());
}

void ButtonMgrClass::runClockSet(int mode)
{
	char hexnum[5];

	switch (getSetupMode())
	{
	case SETUP_HOUR:
		Num2Char(clock.getUnit(UNIT_HOUR), hexnum, DEC, 2);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[0])], 0, 0);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[1])], 0, 4);
		mtrx.placeChar(digitArray[SelectDigit(':')], 1, 9);
		break;
	case SETUP_MINUTE:
		Num2Char(clock.getUnit(UNIT_MINUTE), hexnum, DEC, 2);
		mtrx.placeChar(digitArray[SelectDigit(':')], 1, 9);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[0])], 0, 12);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[1])], 0, 16);
		mtrx.placeChar(digitArray[SelectDigit(':')], 1, 21);
		break;
	case SETUP_MONTH:
		Num2Char(clock.getUnit(UNIT_MONTH), hexnum, DEC, 2);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[0])], 6, 0);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[1])], 6, 4);
		mtrx.placeChar(digitArray[SelectDigit('/')], 7, 8);
		break;
	case SETUP_DAY:
		Num2Char(clock.getUnit(UNIT_DAY), hexnum, DEC, 2);
		mtrx.placeChar(digitArray[SelectDigit('/')], 7, 8);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[0])], 6, 12);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[1])], 6, 16);
		mtrx.placeChar(digitArray[SelectDigit('/')], 7, 20);
		break;
	case SETUP_YEAR:
		Num2Char(clock.getUnit(UNIT_YEAR) % 100, hexnum, DEC, 2);
		mtrx.placeChar(digitArray[SelectDigit('/')], 7, 20);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[0])], 6, 24);
		mtrx.placeChar(digitArray[SelectDigit(hexnum[1])], 6, 28);
		break;
	case SETUP_NONE:
		break;
	}
}

