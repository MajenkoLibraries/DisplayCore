#include <Picadillo.h>
#include <SheepSans.h>

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
	tft.setFont(Fonts::SheepSans8);
	tft.println("SheepSans 8");
	tft.setFont(Fonts::SheepSans12);
	tft.println("SheepSans 12");
	tft.setFont(Fonts::SheepSans16);
	tft.println("SheepSans 16");
	tft.setFont(Fonts::SheepSans20);
	tft.println("SheepSans 20");
	tft.setFont(Fonts::SheepSans24);
	tft.println("SheepSans 24");
	tft.setFont(Fonts::SheepSans28);
	tft.println("SheepSans 28");
	tft.setFont(Fonts::SheepSans32);
	tft.println("SheepSans 32");
	tft.setFont(Fonts::SheepSans36);
	tft.println("SheepSans 36");
	tft.setFont(Fonts::SheepSans40);
	tft.println("SheepSans 40");
}

void loop()
{
}
