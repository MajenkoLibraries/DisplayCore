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
 */

#include <DSPI.h>
#include <Picadillo.h>

// Configure the display
Picadillo tft;
TFTSoftSPI mySPI(11, 13, 10, 8);
ST7735 tft2(&mySPI, ST7735::BlackTab);

void setup() {
	tft.initializeDevice();
	tft2.initializeDevice();
	tft.setRotation(1);
	tft2.setRotation(1);
	tft.fillScreen(Color::Black);
	tft2.fillScreen(Color::Black);
	tft.setFont(Fonts::Topaz);
	tft2.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	tft2.setTextColor(Color::White, Color::Black);	
    tft.setBackloght(255);
}

void loop() {
	static int primitives = 0;
	int primno = rand() % 7;

	switch (primno) {
		case 0:
			drawLine();
			drawLine2();
			break;
		case 1:
			drawRectangle();
			drawRectangle2();
			break;
		case 2:
			drawCircle();
			drawCircle2();
			break;
		case 3:
			drawFilledRectangle();
			drawFilledRectangle2();
			break;
		case 4:
			drawFilledCircle();
			drawFilledCircle2();
			break;
		case 5:
			drawRoundedRectangle();
			drawRoundedRectangle2();
			break;
		case 6:
			drawFilledRoundedRectangle();
			drawFilledRoundedRectangle2();
			break;
	}

	primitives++;
	if(primitives == 20) {
		delay(1000);
		tft.fillScreen(Color::Black);
		tft2.fillScreen(Color::Black);
		primitives = 0;
	}
}

void drawLine() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int endX = rand() % tft.getWidth();
	int endY = rand() % tft.getHeight();
	uint16_t color = rand();

	tft.drawLine(startX, startY, endX, endY, color);
}

void drawLine2() {
	int startX = rand() % tft2.getWidth();
	int startY = rand() % tft2.getHeight();
	int endX = rand() % tft2.getWidth();
	int endY = rand() % tft2.getHeight();
	uint16_t color = rand();

	tft2.drawLine(startX, startY, endX, endY, color);
}

void drawRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.drawRectangle(startX, startY, width, height, color);
}

void drawRectangle2() {
	int startX = rand() % tft2.getWidth();
	int startY = rand() & tft2.getHeight();
	int width = rand() % tft2.getWidth() / 2;
	int height = rand() % tft2.getHeight() / 2;
	uint16_t color = rand();

	tft2.drawRectangle(startX, startY, width, height, color);
}

void drawCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.drawCircle(centerX, centerY, radius, color);
}

void drawCircle2() {
	int centerX = rand() % tft2.getWidth();
	int centerY = rand() % tft2.getHeight();
	int radius = rand() % tft2.getWidth() / 4;
	uint16_t color = rand();

	tft2.drawCircle(centerX, centerY, radius, color);
}

void drawFilledRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.fillRectangle(startX, startY, width, height, color);
}

void drawFilledRectangle2() {
	int startX = rand() % tft2.getWidth();
	int startY = rand() % tft2.getHeight();
	int width = rand() % tft2.getWidth() / 2;
	int height = rand() % tft2.getHeight() / 2;
	uint16_t color = rand();

	tft2.fillRectangle(startX, startY, width, height, color);
}

void drawFilledCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.fillCircle(centerX, centerY, radius, color);
}

void drawFilledCircle2() {
	int centerX = rand() % tft2.getWidth();
	int centerY = rand() % tft2.getHeight();
	int radius = rand() % tft2.getWidth() / 4;
	uint16_t color = rand();

	tft2.fillCircle(centerX, centerY, radius, color);
}

void drawRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.drawRoundRect(startX, startY, width, height, radius, color);
}

void drawRoundedRectangle2() {
	int startX = rand() % tft2.getWidth();
	int startY = rand() & tft2.getHeight();
	int width = rand() % tft2.getWidth() / 2;
	int height = rand() % tft2.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft2.drawRoundRect(startX, startY, width, height, radius, color);
}

void drawFilledRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.fillRoundRect(startX, startY, width, height, radius, color);
}

void drawFilledRoundedRectangle2() {
	int startX = rand() % tft2.getWidth();
	int startY = rand() & tft2.getHeight();
	int width = rand() % tft2.getWidth() / 2;
	int height = rand() % tft2.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft2.fillRoundRect(startX, startY, width, height, radius, color);
}
