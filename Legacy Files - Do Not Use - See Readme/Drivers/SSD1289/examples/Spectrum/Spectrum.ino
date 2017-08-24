#include <SSD1289.h>
#include <Sinclair.h>

SSD1289 tft(3, 4, 5, 6, 7,
            26, 27, 28, 29, 30, 31, 32, 33,
            34, 35, 36, 37, 38, 39, 40, 41 
    );

void setup() {
	tft.initializeDevice();
	tft.setRotation(1);
	tft.setFont(Fonts::Sinclair);
	tft.fillScreen(Color::White);
	tft.setTextColor(Color::Black);
}

void setBorderSingle(uint16_t c) {
	tft.fillRectangle(0, 0, 320, 24, c);
	tft.fillRectangle(0, 24, 32, 192, c);
	tft.fillRectangle(288, 24, 32, 192, c);
	tft.fillRectangle(0, 216, 320, 24, c);
}

void randomStripes(uint16_t ca, uint16_t cb) {
	for (int i = 0; i < 24; i++) {
		tft.drawHorizontalLine(0, i, tft.getWidth(), rand() & 1 ? ca : cb);
	}
	for (int i = 24; i < 216; i++) {
		uint16_t c = rand() & 1 ? ca : cb;
		tft.drawHorizontalLine(0, i, 32, c);
		tft.drawHorizontalLine(288, i, 32, c);
	}
	for (int i = 216; i < 240; i++) {
		tft.drawHorizontalLine(0, i, tft.getWidth(), rand() & 1 ? ca : cb);
	}
}

void regularStripes(uint16_t ca, uint16_t cb, uint32_t w, uint32_t off) {
	uint32_t l = off;
	for (int i = 0; i < 24; i++) {
		tft.drawHorizontalLine(0, i, tft.getWidth(), (l / w) & 1 ? ca : cb);
		l++;
	}
	for (int i = 24; i < 216; i++) {
		uint16_t c = (l/w) & 1 ? ca : cb;
		tft.drawHorizontalLine(0, i, 32, c);
		tft.drawHorizontalLine(288, i, 32, c);
		l++;
	}
	for (int i = 216; i < 240; i++) {
		tft.drawHorizontalLine(0, i, tft.getWidth(), (l/w) & 1 ? ca : cb);
		l++;
	}	
}

void silence(uint32_t del) {
	uint32_t ts = millis();
	bool color = false;
	
	setBorderSingle(Color::Cyan);
	uint32_t delLeft = del;

	while (millis() - ts < del) {
		uint32_t nextDel = rand() % delLeft;
		delLeft -= nextDel;
		delay(nextDel);
		if (color) {
			setBorderSingle(Color::Cyan);	
		} else {
			setBorderSingle(Color::Red);				
		}
		color = !color;
	}
}

void loadHeader(uint32_t del) {
	uint32_t ts = millis();
	uint32_t o = 0;
	while (millis() - ts < del) {
		regularStripes(Color::Red, Color::Cyan, 12, o++);
		delay(40);
	}
}

void loadBody(uint32_t del) {
	uint32_t ts = millis();
	while (millis() - ts < del) {
		randomStripes(Color::Blue, Color::Yellow);
		delay(40);
	}
}

void cls(uint16_t c) {
	tft.fillRectangle(32, 24, 256, 192, c);
}

void loop() {
	setBorderSingle(Color::Black);
	cls(Color::Black);
	delay(1000);
	setBorderSingle(Color::White);
	delay(500);
	cls(Color::White);
	tft.setCursor(32, 208);
	tft.setTextColor(Color::Black, Color::White);
	tft.print("  \x80 1982 Sinclair Research Ltd");
	delay(3000);
	cls(Color::White);
	for (int i = 0; i < 2; i++) {
		tft.setCursor(32, 208);
		tft.setTextColor(Color::White, Color::Black);
		tft.print("K");
		delay(500);
		tft.setCursor(32, 208);
		tft.setTextColor(Color::Black, Color::White);
		tft.print("K");
		delay(500);
	}

	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(32, 208);
	tft.print("LOAD");

	for (int i = 0; i < 3; i++) {
		tft.setCursor(72, 208);
		tft.setTextColor(Color::White, Color::Black);
		tft.print("L");
		delay(500);
		tft.setCursor(72, 208);
		tft.setTextColor(Color::Black, Color::White);
		tft.print("L");
		delay(500);
	}

	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(72, 208);
	tft.print("\"");

	for (int i = 0; i < 1; i++) {
		tft.setCursor(80, 208);
		tft.setTextColor(Color::White, Color::Black);
		tft.print("L");
		delay(500);
		tft.setCursor(80, 208);
		tft.setTextColor(Color::Black, Color::White);
		tft.print("L");
		delay(500);
	}

	tft.setTextColor(Color::Black, Color::White);
	tft.setCursor(80, 208);
	tft.print("\"");

	for (int i = 0; i < 2; i++) {
		tft.setCursor(88, 208);
		tft.setTextColor(Color::White, Color::Black);
		tft.print("L");
		delay(500);
		tft.setCursor(88, 208);
		tft.setTextColor(Color::Black, Color::White);
		tft.print("L");
		delay(500);
	}

	
	cls(Color::White);

	silence(5000);
	loadHeader(1000);
	loadBody(250);	
	tft.setCursor(32, 32);
	tft.print("Program: PIC32-TFT");
	silence(1000);
	loadHeader(1000);
	loadBody(3000);	
	
	cls(Color::Black);
	silence(2000);
	loadHeader(1000);
	loadBody(250);	
	silence(1000);
	loadHeader(1000);
	loadBody(7000);	
	
	silence(1000);
	loadHeader(1000);
	loadBody(250);
	silence(1000);
	loadHeader(1000);
	loadBody(30000);
	setBorderSingle(Color::Black);
	delay(5000);
}
