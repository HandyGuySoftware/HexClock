Hexadecimal Clock ReadMe
------------------------

The Hexadecimal Clock (HexClock) will display the current time and date in both hexadecimal and binary notation. HexClock uses a realtime clock module to keep accurate time with a battery backup in case of lost power.

Setting the clock
-----------------
The clock has two buttons: Mode and Set. Holding the Mode button for 3 seconds will put the clock into Setup Mode. The LED on the Mode button will light up to indicate that you are in setup mode.

When you enter setup mode the display will blank and only the "hours" portion of the display will be lit. 

For ease of use, the clock uses standard decimal notation for time & date. Time is set using a 24-hour clock (i.e., hours are 0-23). When you have completed setting the proper time the clock will again display time and dates in hex/binary.

To set the hour, press the Set button repeatedly until the correct hour is displayed. Once you have set the correct hour, press the Mode button again and the minutes portion will be displayed. Press the Set button repeatedly until the proper minutes are displayed.

Repeatedy pressing the Mode button will cycle through all the setup modes:

- Hours
- Minutes
- Day
- Month
- Year

Continue pressing Mode and Set as described above until all the time and date segments have been properly set. Pressing the Mode button after you set the year will put the clock back into Run mode. The LED on the Mode button will turn off indicating you are in run mode.

HexClock uses American date styles (mm/dd/yy). Euro-style dates (dd/mm/yy) will have to wait for a future update. :-)

Resetting the Clock
-------------------
To reset the clock back to its original state (0:00:00 1/1/2016) press *both* the Mode and Set buttons for 5 seconds. After 5 seconds all the pixels on the display will light up in white until you release the buttons. Once both buttons are released the clock will display the starting time/date. use the procedure above ("Setting the Clock") to set the correct time and date.

Parts
-----
These are the major parts used. Incidental parts (terminal blocks, power jacks, connecting cables, etc.) are left to the imagination of the builder.

1 - Arduino Uno
1 - 16x32 LED Matrix (https://www.adafruit.com/products/420)
1 - Adafruit ProtoShield (http://www.adafruit.com/products/2077)
1 - DS3231 RealTime Clock module (http://www.amazon.com/gp/product/B00LZCTMJM?psc=1&redirect=true&ref_=oh_aui_detailpage_o04_s02)
1 - 16mm Illuminated Pushbutton (Mode Button)([http://www.adafruit.com/products/1479)
1 - 16mm Panel Mount Momentary Pushbutton -  Black (Set button) (http://www.adafruit.com/products/1505)
1 - 5V 4A (4000mA) switching power supply - (http://www.adafruit.com/products/1466)
1 - Project Box (7.5" x 4.3" x 2.2") (191mm x 110mm x 57mm) - http://www.amazon.com/gp/product/B0002BSRIO?psc=1&redirect=true&ref_=oh_aui_detailpage_o02_s00
1 - 330 Ohm Resistor
2 - 10k Ohm Resistors
1 - 4700 uf Capacitor

Code Modules
------------
ButtonMgr - Class to deal with button presses and handle setup mode.

ClockDigit - Class to handle display of digits/characters on the LED matrix

HexClock.ino - Main HexClock Arduino code. Includes setup() and loop() routines, as well as some helper functions that should have gone into classes somewhere, but I got lazy. ;-)

LEDMatrix.cpp - Class to manage display on the LED matrix. A thin wrapper for the Adafruit libraries.

RTClock - Class to get/set time for the real time clock. A wrapper for the DS3231 libraries.

Developer's Note: I used to be a professional developer back in the stone age when we used to chisel our code into stone tablets. As a result, I'm sure I have violated lots of current C/C++/Arduino coding standards. Sorry, not sorry. The code works, so 'nuff said. If someone would like to politely explain where I can bring the code up to current standards I would be happy to incorporate that into a future release. 

Miscellaneous
-------------
Special thanks to adafruit_support_mike for helping me through some of the power supply issues

ToDo:
- Adjust the color of the panel through Setup mode
- Adjust the brightness of the panel LEDs (not sure of this is possible with these matrix boards
- Display Euro-style dates (dd/mm/yy)
- Choose either 12- or 24-hour notation on the display
- Clean up the code/better commentary

Comments, suggestions, & contributions (code, not money) are all welcome.

Enjoy!

