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
 * Primitives demonstration
 * 
 * Displays random primitives.
 *
 * IMPORTANT: This requires the "replacement" hardware SD library
 *
 */

#include <DSPI.h>
#include <Picadillo.h>
#include <SD.h>
#include <BMPFile.h>
#include <Topaz.h>

// Configure the display
Picadillo tft;

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(0);
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	tft.setCursor(0, 0);
	tft.print("Initializing SD card...");
	if (!SD.begin(PIN_SD_SS)) {
		tft.print("failed");
		while(1);
	}
	tft.println("OK");
}

void loop() {
	File myFile = SD.open("/slides");
	dir_t p;
	myFile.seek(0);
	while (myFile.readDir(&p)) {
		if (p.name[0] == DIR_NAME_FREE) {
			break;
		}
		if (p.name[0] == DIR_NAME_DELETED || p.name[0] == '.') {
			continue;
		}
		if (!DIR_IS_FILE_OR_SUBDIR(&p)) {
			continue;
		}
		if (!strncmp((const char *)p.name+8, "BMP", 3)) {
			char fn[15];
			char fullPath[100];
			dirToChar(p, fn);
			sprintf(fullPath, "/slides/%s", fn);
			File f = SD.open(fullPath);
			BMPFile bmp(f);
			uint32_t start = millis();
			bmp.draw(&tft, 0, 0);
			uint32_t end = millis();
			uint32_t len = end - start;
			tft.setCursor(0, 0);
			tft.print(len);
			f.close();
			delay(5000);
		}
	}
	myFile.close();
}

void dirToChar(dir_t &p, char *s) {
	memset(s, 0, 14);
	char *ptr = s;
	for (int i = 0; i < 11; i++) {
		if (p.name[i] == ' ') {
			continue;
		}
		if (i == 8) {
			*ptr++ = '.';
		}
		*ptr++ = p.name[i];
	}
}
