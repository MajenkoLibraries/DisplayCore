#include <TFT.h>
#include <OCRAExtended.h>

PICadillo35t tft;
 
void setup()
{
	analogWrite(PIN_BACKLIGHT, 255);
	tft.initializeDevice();
	tft.setTextWrap(false);
	tft.setRotation(1);
	tft.setCursor(0, 0);
	tft.fillScreen(Color::Black);
	tft.setTextColor(Color::Red);
	tft.setFont(Fonts::OCRAExtended8);
	tft.println("OCRAExtended 8");
	tft.setFont(Fonts::OCRAExtended12);
	tft.println("OCRAExtended 12");
	tft.setFont(Fonts::OCRAExtended16);
	tft.println("OCRAExtended 16");
	tft.setFont(Fonts::OCRAExtended20);
	tft.println("OCRAExtended 20");
	tft.setFont(Fonts::OCRAExtended24);
	tft.println("OCRAExtended 24");
	tft.setFont(Fonts::OCRAExtended28);
	tft.println("OCRAExtended 28");
	tft.setFont(Fonts::OCRAExtended32);
	tft.println("OCRAExtended 32");
	tft.setFont(Fonts::OCRAExtended36);
	tft.println("OCRAExtended 36");
	tft.setFont(Fonts::OCRAExtended40);
	tft.println("OCRAExtended 40");
}

void loop()
{
}
