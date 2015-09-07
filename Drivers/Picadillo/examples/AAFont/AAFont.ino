#include <Picadillo.h>
#include <Liberation.h>
#include <Hazard.h>
#include <OldStandard.h>

Picadillo tft;
 
void setup()
{
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setTextWrap(false);
	tft.setRotation(1);
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Liberation30);
	tft.setTextColor(Color::Red);
	tft.setCursor(10, 150);
	tft.print("This is a font test");
	tft.setFont(Fonts::OldStandard10);
	tft.setTextColor(Color::SkyBlue);
	tft.setCursor(10, 260);
	tft.print("OldStandard is a normal 1-bit font");
	tft.setFont(Fonts::Liberation10);
	tft.setTextColor(Color::White);
	tft.setCursor(10, 280);
	tft.print("Liberation is the first of the 2-bits-per-pixel");
	tft.setCursor(10, 300);
	tft.print("anti-aliased fonts in the TFT library.");
}

void loop()
{
	static uint32_t ts = millis();
	tft.setFont(Fonts::Liberation30);
	tft.setTextColor(Color::Green);
	tft.setCursor(100, 50);
	tft.print(millis());

	if (millis() - ts > 1000) {
		tft.setFont(Fonts::Hazard40);
		tft.setCursor(10, 200);
		tft.setTextColor(Color::Yellow);
		tft.fillRectangle(0, 200, 480, 56, Color::Black);
		for (int i = 0; i < 10; i++) {
			tft.write(random(32, 127));
		}
		ts = millis();
	}
}
