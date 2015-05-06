#include <ST7735.h>

// For the Adafruit Shield the communication is through DSPI0.  TCS is pin 10 and DC is pin 8.
// Mine is a "black tab" variant.  Choose one of ST7735::GreenTab, ST7735::RedTab, ST7735::BlackTab
// or ST7735::TypeB depending on which version you have.  If in doubt try them all until it works
// right.

DSPI0 spi;
ST7735 tft(spi, 10, 8, ST7735::BlackTab);

void setup() {
	tft.initializeDevice();	
	tft.fillScreen(Color::Black);
	tft.setTextColor(Color::Red, Color::Black);
	tft.setFont(Fonts::Default);
}

void loop() {
	tft.setCursor(20, 20);
	tft.print(millis());
}
