/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This sketch demonstrates how to stutch multiple small images together
 * to form one single image on the screen.  It takes a selection of small
 * images representing each of the segments of a 7 segment display in both
 * the on and off states, and stitches them together to form large digits.
 * 
 * The demonstration takes a reading from ADC channel A0 and maps it to 
 * a value between 0 and 999 to display in large 7-segment digits filling
 * the PICadillo display.
 * 
 * You may want to provide a sensible input to A0, such as the wiper output
 * of a potentiometer connected between +3.3V and GND.
 */

#include <Picadillo.h>
#include <Raw565.h>

Picadillo tft;

// These are references to the images in flash.
extern uint16_t aOn_565[] asm("_binary_objects_aOn_565_start");
extern uint16_t bOn_565[] asm("_binary_objects_bOn_565_start");
extern uint16_t cOn_565[] asm("_binary_objects_csOn_565_start");
extern uint16_t dOn_565[] asm("_binary_objects_dOn_565_start");
extern uint16_t eOn_565[] asm("_binary_objects_eOn_565_start");
extern uint16_t fOn_565[] asm("_binary_objects_fOn_565_start");
extern uint16_t gOn_565[] asm("_binary_objects_gOn_565_start");
extern uint16_t aOff_565[] asm("_binary_objects_aOff_565_start");
extern uint16_t bOff_565[] asm("_binary_objects_bOff_565_start");
extern uint16_t cOff_565[] asm("_binary_objects_cOff_565_start");
extern uint16_t dOff_565[] asm("_binary_objects_dOff_565_start");
extern uint16_t eOff_565[] asm("_binary_objects_eOff_565_start");
extern uint16_t fOff_565[] asm("_binary_objects_fOff_565_start");
extern uint16_t gOff_565[] asm("_binary_objects_gOff_565_start");

// We now create a selection of raw 565 image wrappers for each image.

Raw565 aOn(aOn_565, 114, 28);
Raw565 aOff(aOff_565, 114, 28);

Raw565 bOn(bOn_565, 28, 114);
Raw565 bOff(bOff_565, 28, 114);

Raw565 cOn(cOn_565, 28, 114);
Raw565 cOff(cOff_565, 28, 114);

Raw565 dOn(dOn_565, 114, 28);
Raw565 dOff(dOff_565, 114, 28);

Raw565 eOn(eOn_565, 28, 115);
Raw565 eOff(eOff_565, 28, 115);

Raw565 fOn(fOn_565, 28, 113);
Raw565 fOff(fOff_565, 28, 113);

Raw565 gOn(gOn_565, 111, 29);
Raw565 gOff(gOff_565, 111, 29);

// This is the relative position of each segment within
// the finished image for one digit.  It is measured from
// the top left of the digit.

typedef struct {
	int x;
	int y;
} Point;

Point locations[] = {
	{ 14, 0 },
	{ 113, 9 },
	{ 113, 127 },
	{ 13, 223 },
	{ 0, 126 },
	{ 0, 10 },
	{ 15, 110 }
};

// This is a mapping of which segments are turned on or off for
// each number from 0 to 9.

uint8_t numbers[] = {
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00100111,
	0b01111111,
	0b01101111
};

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(1);
	tft.fillScreen(Color::Black);
}

void loop() {
	int reading = analogRead(0);
	int mapped = map(reading, 0, 1023, 0, 999);
	displayDigits(mapped, 10, 30);
}

// This works out each of the three digits to display and
// cuts out any unwanted leading zeroes.

void displayDigits(int num, int x, int y) {
	int hundreds = (num / 100) % 10;
	int tens = (num / 10) % 10;
	int units = num % 10;
	
	if (hundreds== 0) {
		displayNothing(x, y);
	} else {
		displayNumber(hundreds, x, y);
	}

	if ((hundreds == 0) && (tens == 0)) {
		displayNothing(x + 160, y);
	} else {
		displayNumber(tens, x + 160, y);
	}
	
	displayNumber(units, x + 320, y);
}

// This displays "nothing" at a location on the screen.
// Displaying nothing is basically displaying a 7 segment
// display with all digits turned off.

void displayNothing(int x, int y) {
	setA(x, y, false);
	setB(x, y, false);
	setC(x, y, false);
	setD(x, y, false);
	setE(x, y, false);
	setF(x, y, false);
	setG(x, y, false);
}

// This takes a number 0 to 9 and looks it up in the
// table of segments to switch different segments on and off.

void displayNumber(int num, int x, int y) {
	setA(x, y, numbers[num % 10] & 0x01);
	setB(x, y, numbers[num % 10] & 0x02);
	setC(x, y, numbers[num % 10] & 0x04);
	setD(x, y, numbers[num % 10] & 0x08);
	setE(x, y, numbers[num % 10] & 0x10);
	setF(x, y, numbers[num % 10] & 0x20);
	setG(x, y, numbers[num % 10] & 0x40);
}

// The remaining functions control individual segments within
// the digit.  The X/Y coordinates are for the upper-left of the
// digit, and the offset in the locations table is added to get the
// actual location of the segment on the screen.

void setA(int x, int y, boolean onoff) {
	if (onoff) {
		aOn.draw(&tft, x + locations[0].x, y + locations[0].y, Color::Black);
	} else {
		aOff.draw(&tft, x + locations[0].x, y + locations[0].y, Color::Black);
	}
}

void setB(int x, int y, boolean onoff) {
	if (onoff) {
		bOn.draw(&tft, x + locations[1].x, y + locations[1].y, Color::Black);
	} else {
		bOff.draw(&tft, x + locations[1].x, y + locations[1].y, Color::Black);
	}
}

void setC(int x, int y, boolean onoff) {
	if (onoff) {
		cOn.draw(&tft, x + locations[2].x, y + locations[2].y, Color::Black);
	} else {
		cOff.draw(&tft, x + locations[2].x, y + locations[2].y, Color::Black);
	}
}

void setD(int x, int y, boolean onoff) {
	if (onoff) {
		dOn.draw(&tft, x + locations[3].x, y + locations[3].y, Color::Black);
	} else {
		dOff.draw(&tft, x + locations[3].x, y + locations[3].y, Color::Black);
	}
}

void setE(int x, int y, boolean onoff) {
	if (onoff) {
		eOn.draw(&tft, x + locations[4].x, y + locations[4].y, Color::Black);
	} else {
		eOff.draw(&tft, x + locations[4].x, y + locations[4].y, Color::Black);
	}
}

void setF(int x, int y, boolean onoff) {
	if (onoff) {
		fOn.draw(&tft, x + locations[5].x, y + locations[5].y, Color::Black);
	} else {
		fOff.draw(&tft, x + locations[5].x, y + locations[5].y, Color::Black);
	}
}

void setG(int x, int y, boolean onoff) {
	if (onoff) {
		gOn.draw(&tft, x + locations[6].x, y + locations[6].y, Color::Black);
	} else {
		gOff.draw(&tft, x + locations[6].x, y + locations[6].y, Color::Black);
	}
}
