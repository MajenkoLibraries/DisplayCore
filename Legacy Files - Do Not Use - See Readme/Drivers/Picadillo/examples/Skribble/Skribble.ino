#include <Picadillo.h>
#include <Topaz.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

const int btnSize = 64;

uint16_t colors[8] = {
	Color::Black,
	Color::Red,
	Color::Green,
	Color::Yellow,
	Color::Blue,
	Color::Magenta,
	Color::Cyan,
	Color::White
};

uint16_t color = 1;
uint16_t size = 2;


void menu() {
	for (int i = 0; i < 320; i+=btnSize) {
		tft.fillRectangle(i, 479-btnSize, btnSize-1, btnSize-1, Color::Black);
		tft.drawRectangle(i, 479-btnSize, btnSize-1, btnSize-1, Color::Yellow);
	}

	tft.fillCircle(32, 479-32, size, colors[color]);
	tft.drawCircle(32, 479-32, size, Color::Gray50);
	tft.fillCircle(32+64, 479-32, 4, Color::White);
	tft.fillCircle(32+64+64, 479-32, 14, Color::White);
	tft.fillTriangle(
		64*3+10, 479-32, 
		64*3+54, 479-10, 
		64*3+54, 479-54, 
		Color::White
	);
	tft.fillTriangle(
		64*4+54, 479-32, 
		64*4+10, 479-10, 
		64*4+10, 479-54, 
		Color::White
	);
}

void setup() {
	ts.initializeDevice();
	ts.scaleX(4.3);
	ts.scaleY(3.3);
	ts.offsetY(5);
	tft.initializeDevice();
    tft.setBacklight(255);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);
	tft.fillScreen(Color::Black);
	menu();
}

void loop() {
	static boolean isPressed = false;
	static uint32_t btnTs = millis();
	ts.sample();

	if (millis() - btnTs > 100) {
		btnTs = millis();
		if (ts.isPressed() != isPressed) {
			isPressed = ts.isPressed();
			if (isPressed) {
				if (ts.y() > 479-btnSize) {
					switch (ts.x() / 64) {
						case 0:
							break;
						case 1:
							if (size > 2) {
								size--;
							}
							menu();
							break;
						case 2:
							if (size < 30) {
								size++;
							}
							menu();
							break;
						case 3:
							color--;
							if (color > 7) {
								color = 7;
							}
							menu();
							break;
						case 4:
							color++;
							if (color > 7) {
								color = 0;
							}
							menu();
							break;
					}
				}
			}
		}
	}
	if (ts.isPressed()) {
		if (ts.y() < 479-btnSize-size) {
			tft.fillCircle(ts.x(), ts.y(), size, colors[color]);
		}
	}
}
