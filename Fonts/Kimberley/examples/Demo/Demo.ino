#include <TFT.h>
#include <Kimberley.h>

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
	tft.setFont(Fonts::Kimberley8);
	tft.println("Kimberley 8");
	tft.setFont(Fonts::Kimberley12);
	tft.println("Kimberley 12");
	tft.setFont(Fonts::Kimberley16);
	tft.println("Kimberley 16");
	tft.setFont(Fonts::Kimberley20);
	tft.println("Kimberley 20");
	tft.setFont(Fonts::Kimberley24);
	tft.println("Kimberley 24");
	tft.setFont(Fonts::Kimberley28);
	tft.println("Kimberley 28");
	tft.setFont(Fonts::Kimberley32);
	tft.println("Kimberley 32");
	tft.setFont(Fonts::Kimberley36);
	tft.println("Kimberley 36");
	tft.setFont(Fonts::Kimberley40);
	tft.println("Kimberley 40");
}

void loop()
{
}
