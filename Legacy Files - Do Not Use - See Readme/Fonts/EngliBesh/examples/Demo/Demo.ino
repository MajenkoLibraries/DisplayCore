#include <Picadillo.h>
#include <EngliBesh.h>

Picadillo tft;
 
void setup()
{
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setTextWrap(false);
	tft.setRotation(1);
	tft.setCursor(0, 0);
	tft.fillScreen(Color::Black);
	tft.setTextColor(Color::Red);
	tft.setFont(Fonts::EngliBesh8);
	tft.println("EngliBesh 8");
	tft.setFont(Fonts::EngliBesh12);
	tft.println("EngliBesh 12");
	tft.setFont(Fonts::EngliBesh16);
	tft.println("EngliBesh 16");
	tft.setFont(Fonts::EngliBesh20);
	tft.println("EngliBesh 20");
	tft.setFont(Fonts::EngliBesh24);
	tft.println("EngliBesh 24");
	tft.setFont(Fonts::EngliBesh28);
	tft.println("EngliBesh 28");
	tft.setFont(Fonts::EngliBesh32);
	tft.println("EngliBesh 32");
	tft.setFont(Fonts::EngliBesh36);
	tft.println("EngliBesh 36");
	tft.setFont(Fonts::EngliBesh40);
	tft.println("EngliBesh 40");
}

void loop()
{
}
