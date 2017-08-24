#include <Picadillo.h>
#include <BMP.h>

#include "4d.h"
BMP logo(logo_4d);

Picadillo tft;

void setup()
{
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setRotation(0);
	tft.fillScreen(Color::White);
	logo.draw(&tft, tft.getWidth() / 2 - 52, tft.getHeight() / 2 - 52);
	delay(1000);
}

void loop() 
{
	char temp[100];
	static uint32_t totFill = 0;
	static uint32_t totCirc = 0;
	static uint32_t totRect = 0;
	static uint32_t count = 0;
	tft.fillScreen(Color::White);

	uint32_t fill = fillScreen(100);
	uint32_t circ = circle(1000);
	uint32_t rect = rectangle(1000);
	totFill += fill;
	totCirc += circ;
	totRect += rect;
	count++;

	tft.fillScreen(Color::White);
	tft.setFont(Fonts::Default);
	tft.setTextColor(Color::Blue, Color::White); //FG, BG
	tft.setCursor(0, 0);
	tft.println();
	tft.println(" Fill Screen x 100:");
	sprintf(temp, "    %5dms / ave: %5dms / ea: %.3f", fill, totFill / count, ((float)totFill / (float)count) / 100.0 );
	tft.println(temp);
	tft.println();
	tft.println(" Fill Circle x 1000:");
	sprintf(temp, "    %5dms / ave: %5dms / ea: %.3f", circ, totCirc / count, ((float)totCirc / (float)count) / 1000.0 );
	tft.println(temp);
	tft.println();
	tft.println(" Fill Rectangle x 1000:");
	sprintf(temp, "    %5dms / ave: %5dms / ea: %.3f", rect, totRect / count, ((float)totRect / (float)count) / 1000.0 );
	tft.println(temp);
	delay(10000);
}

uint32_t circle(uint32_t c) {
	uint32_t start = millis();
	for (int i = 0; i < c; i++) {
		tft.fillCircle( random(0, tft.getWidth()), random(0, tft.getHeight()), random(0, tft.getWidth()/2), random(65535));
	}
	uint32_t end = millis();
	uint32_t elapsed = end - start;
	return elapsed;
}

uint32_t fillScreen(uint32_t c) {
	uint32_t start = millis();
	for (int i = 0; i < c; i++) {
		tft.fillScreen(i);
	}
	uint32_t end = millis();
	uint32_t elapsed = end - start;
	return elapsed;
}

uint32_t rectangle(uint32_t c) {
	uint32_t start = millis();
	for (int i = 0; i < c; i++) {
		tft.fillRectangle( random(0, tft.getWidth()), random(0, tft.getHeight()), random(0, tft.getWidth()/2), random(0, tft.getHeight()/2), random(65535));
	}
	uint32_t end = millis();
	uint32_t elapsed = end - start;
	return elapsed;
}

