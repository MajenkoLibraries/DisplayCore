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
 * Slideshow
 * 
 * Copy the folder "slides" from the "files" folder onto an SD card.
 * This is meant to be run on a picLCD-35T
 */

#include <Picadillo.h>
#include <Topaz.h>

// Configure the display
Picadillo tft;

void printCentered(uint16_t pos, char *data) {
	uint16_t w = tft.stringWidth(data);
	tft.setCursor((tft.getWidth() / 2) - (w / 2), pos);
	tft.print(data);
}

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(0);
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	printCentered(50, "High Speed Window");
	printCentered(70, "Operation Demonstration");
}

void loop() {
	static uint32_t offr = 0;
	static uint32_t offg = 0;
	static uint32_t offb = 0;
	static uint32_t ts = millis();
	static uint32_t count = 0;

	tft.openWindow(32, 128, 256, 256);
	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			uint8_t red = (x + offr);
			uint8_t green = (x + offg);
			uint8_t blue = (y + offb);
			tft.windowData(rgb(red, green, blue));
			
		}
	}
	offr++;
	offg+=2;
	offb+=3;
	tft.closeWindow();
	
	count++;
	if (millis() - ts >= 10000) {
		float fps = count / 10.0;
		tft.setCursor(120, 400);
		tft.print(fps);
		tft.print(" fps");
		count = 0;
		ts = millis();
	}
}
