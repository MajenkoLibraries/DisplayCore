#include <SSD1289.h>
#include <Sinclair.h>

SSD1289_PMP tft(A4);

void setup() {
	tft.initializeDevice();
	tft.setRotation(1);
	tft.setFont(Fonts::Sinclair);
	tft.fillScreen(Color::White);
	tft.setTextColor(Color::Black);
	tft.setCursor(32, 32);
	tft.print("Program: PIC32-TFT");
}

void loop() {
	static uint32_t ms = millis();
	if (millis() - ms >= 40) {
		ms = millis();
		for (int i = 0; i < 24; i++) {
			tft.drawHorizontalLine(0, i, tft.getWidth(), rand() & 1 ? Color::Blue : Color::Yellow);
		}
		for (int i = 24; i < 216; i++) {
			uint16_t c = rand() & 1 ? Color::Blue : Color::Yellow;
			tft.drawHorizontalLine(0, i, 32, c);
			tft.drawHorizontalLine(288, i, 32, c);
		}
		for (int i = 216; i < 240; i++) {
			tft.drawHorizontalLine(0, i, tft.getWidth(), rand() & 1 ? Color::Blue : Color::Yellow);
		}
	}
}
