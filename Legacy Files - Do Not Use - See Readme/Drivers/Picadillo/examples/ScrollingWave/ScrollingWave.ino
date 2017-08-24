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
	printCentered(50, "Scrolling Wave");
	printCentered(70, "Audio Visualisation");
}

void loop() {
	static int16_t data[320];

	for (int x = 0; x < 319; x++) {
		data[x] = data[x+1];
	}

    int16_t os = 0;
    for (int i = 0; i < 10; i++) {
        int16_t vs = abs(analogRead(0)-512)>>1;
        if (vs > os) {
            os = vs;
        }
    }
    data[319] = os;

	tft.openWindow(0, 128, 320, 255);
	for (int y = 0; y < 255; y++) {
		for (int x = 0; x < 320; x++) {
			if (y == 128) {
				tft.windowData(Color::Blue);				
			} else if (y < 128) {
				if (data[x] > 128-y) {
					tft.windowData(rgb((127-y)*2, 255-((127-y)*2), 0));
				} else {
					tft.windowData(rgb(0, 0, data[64+y]));
				}
			} else {
				if (data[x] > y-128) {
					tft.windowData(rgb((y-128)*2, 255-((y-128)*2), 0));					
				} else {
					tft.windowData(rgb(0, 0, data[64+y]));
				}
			}
		}
	}
	tft.closeWindow();
}
