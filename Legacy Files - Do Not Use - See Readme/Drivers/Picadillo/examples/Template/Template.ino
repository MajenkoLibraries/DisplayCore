#include <Picadillo.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);


void setup() {
	ts.initializeDevice();

	// These set the touch screen resolution.
	ts.scaleX(4.3);
	ts.scaleY(3.3);
	ts.offsetY(5);

	tft.initializeDevice();
	tft.setBacklight(255);
	tft.fillScreen(Color::Black);

}

void loop() {
    
}
