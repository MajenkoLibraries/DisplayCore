#include <XPT2046.h>
#include <SSD1963.h>

DSPI0 spi;

XPT2046 ts(spi, A14, 800, 480);
SSD1963 tft(24, 23, 22, 21, 20, 18, 16, 15, 12, 14, 11, 10, 9, 8, 7, 6, 5, 4, 19, 17, 2);


void setup() {
	ts.initializeDevice();
	ts.offsetX(-20);
	ts.offsetY(-20);
	ts.scaleX(1.1);
	ts.scaleY(1.1);
	tft.initializeDevice();
	tft.setBacklight(255);
	tft.fillScreen(Color::Black);
}

void loop() {
	ts.sample();
	if (ts.isPressed()) {
		tft.fillCircle(ts.x(), ts.y(), 5, rand());
	}
}
