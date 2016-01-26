#include "LEDMatrix.h"

// Headers for Adafruit LED Matric Panel
#include <RGBmatrixPanel.h>
#include <gamma.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>

extern RGBmatrixPanel LEDBoard;

LedMatrixClass::LedMatrixClass(int h, int w)
{
	colorRed = colorGreen = colorBlue = 0;
}

/*
Set an individual pixel in the matrix display
rw, cl - row/column for pixel
co - color specification
brt - brightness specification
*/
void LedMatrixClass::setPixel(int rw, int cl)
{

	LEDBoard.drawPixel(cl, rw, LEDBoard.Color333(colorRed, colorGreen, colorBlue));

	return;
}

/*
Turn off a pixel in the display.
*/
void LedMatrixClass::clearPixel(int r, int c)
{
	LEDBoard.drawPixel(c, r, LEDBoard.Color333(0, 0, 0));

	return;
}

/*
Place a hex digit character on the matrix
cd - ClockDigit class instance
r,c - Row/column for the digit
co - color value
br - brightness value
*/
void LedMatrixClass::placeChar(ClockDigitClass *cd, int r, int c)
{
	int crows = cd->getDisplayRows();
	int ccols = cd->getDisplayColumns();
	
	// Since each char is a 16-bit value, the MSB's are unused on many of the symbols
	// Let's figure out how many are unused
	int startBit = 16 - (crows*ccols);

	for (int i = 0; i < crows; ++i)
	{
		for (int j = 0; j < ccols; ++j)
		{
			if (cd->getBitValue((i*ccols) + j + startBit) != 0)
				setPixel(r + i, c + j);
			else
				clearPixel(r + i, c + j);
		}
	}
	return;
}

/*
Place a row representing a binary number on the matrix
b - value to convert to binary representation
r, c - row/col in matrix
d - digits (columns) to use for binary number
co - color value
br - brightness value
*/
void LedMatrixClass::placeBinary(int b, int r, int c, int p)
{
	int rtmp, gtmp, btmp;

	for (int i = 0; i < p; ++i) // only need 'p' LSB from number
	{
		if (b & (0x01 << i))
			setPixel(r, c + p - 1 - i);
		else
			clearPixel(r, c + p - 1 - i);
	}

	return;
}

void LedMatrixClass::setColor(int r, int g, int b)
{
	colorRed = r;
	colorGreen = g;
	colorBlue = b;

	return ;
}

void LedMatrixClass::clearScreen()
{
	LEDBoard.fillScreen(LEDBoard.Color333(0, 0, 0));
}

void LedMatrixClass::fillScreen()
{
	LEDBoard.fillScreen(LEDBoard.Color333(7, 7, 7));
}

void LedMatrixClass::saveColor()
{
	saveColorRed = colorRed;
	saveColorGreen = colorGreen;
	saveColorBlue = colorBlue;
}

void LedMatrixClass::restoreColor()
{
	colorRed = saveColorRed;
	colorGreen = saveColorGreen;
	colorBlue = saveColorBlue;
}
