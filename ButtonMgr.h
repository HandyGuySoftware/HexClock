// ButtonMgr.h

#ifndef _BUTTONMGR_h
#define _BUTTONMGR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Define modes for button management
#define MODE_RUN 0
#define MODE_PENDING 1
#define MODE_SETUP 2

// Define Setup Modes
#define SETUP_NONE 0
#define SETUP_HOUR 1
#define SETUP_MINUTE 2
#define SETUP_MONTH 3
#define SETUP_DAY 4
#define SETUP_YEAR 5
//#define SETUP_COLOR 6

const int setupArraySize = 6;

class ButtonMgrClass
{
	public:
		ButtonMgrClass(int, int, int);
		int getModeButtonState();
		int getSetupButtonState();
		int getOpMode() { return currentOpMode;  }
		int setOpMode(int mode) { return currentOpMode = mode;  }
		int getSetupMode() {return currentSetupMode;}
		int setSetupMode(int mode) { return currentSetupMode = mode; }
		int setCounter() { return milCounter = 0; }
		int modeBtnLongPress();
		int checkClockSet();
		void runClockSet(int);

	private:
		int modeButtonState, setButtonState, currentOpMode, milCounter, currentSetupMode;
		int modePin, setPin, ledPin;
		int setupModeState[setupArraySize] = { SETUP_HOUR, SETUP_MINUTE, SETUP_MONTH, SETUP_DAY, SETUP_YEAR };

};


#endif

