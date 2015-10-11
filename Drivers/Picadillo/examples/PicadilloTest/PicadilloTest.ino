#include <Picadillo.h>
#include <BMPFile.h>
#include <Widgets.h>
#include <Topaz.h>
#include <Liberation.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

const int btnSize = 64;

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

void audioOn() {
    pinMode(PIN_AUDENB, OUTPUT);
    digitalWrite(PIN_AUDENB, LOW);
}

void audioOff() {
    pinMode(PIN_AUDENB, OUTPUT);
    digitalWrite(PIN_AUDENB, HIGH);
}

twButton cont(ts, tft, 75, 300, 170, 75, "CONTINUE");

void error(char *message) {
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);
	tft.fillScreen(Color::Black);
	tft.setCursor(0, 0);
	tft.print(message);
	fadeUp();
    doContinue();
}

void setup() {
	ts.initializeDevice();

	// These set the touch screen resolution.
	ts.scaleX(4.3);
	ts.scaleY(3.3);
	ts.offsetY(5);

	tft.initializeDevice();
	tft.setBacklight(0);
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);
	tft.fillScreen(Color::Black);

	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	tft.setCursor(0, 0);
    cont.setBevel(4);
    cont.setTextColor(Color::Red, Color::Black);
    cont.setFont(Fonts::Liberation20);
	if (!SD.begin(PIN_SD_SS)) {
		error("Unable to initialize SD card!");
	}

	drawLogo();
	tinkle();
	prims();
	scribble();
}

void tinkle() {
	audioOn();
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 10; i++) {
			tone(PIN_AUDIO, NOTE_C4, 20);
			delay(20);
			tone(PIN_AUDIO, NOTE_E4, 20);
			delay(20);
			tone(PIN_AUDIO, NOTE_G4, 20);
			delay(20);
		}
		delay(100);
		for (int i = 0; i < 10; i++) {
			tone(PIN_AUDIO, NOTE_C4, 20);
			delay(20);
			tone(PIN_AUDIO, NOTE_F4, 20);
			delay(20);
			tone(PIN_AUDIO, NOTE_A4, 20);
			delay(20);
		}
		delay(100);
	}
	audioOff();
}

boolean continuePressed = false;

void pressContinue(Event *e) {
    continuePressed = true;
}

void doContinue() {
	cont.render();
	fadeUp();
	ts.sample();
	int lx = ts.x();
	int ly = ts.y();
    cont.onTap(pressContinue);
    cont.redraw();
    continuePressed = false;
	while (continuePressed == false) {
        cont.render();
		tft.fillTriangle(0, ly-4, 4, ly, 0, ly+4, Color::Black);		
		tft.fillTriangle(319, ly-4, 319-4, ly, 319, ly+4, Color::Black);		

		tft.fillTriangle(lx-4, 0, lx, 4, lx+4, 0, Color::Black);		
		tft.fillTriangle(lx-4, 479, lx, 479-4, lx+4, 479, Color::Black);		

		ts.sample();
		lx = ts.x();
		ly = ts.y();
		tft.fillTriangle(0, ly-4, 4, ly, 0, ly+4, Color::White);		
		tft.fillTriangle(319, ly-4, 319-4, ly, 319, ly+4, Color::White);		

		tft.fillTriangle(lx-4, 0, lx, 4, lx+4, 0, Color::White);		
		tft.fillTriangle(lx-4, 479, lx, 479-4, lx+4, 479, Color::White);		

        delay(3); // Small delay to keep the triangles visible
	}
	audioOn();
	delay(10);
	tone(PIN_AUDIO, 2000, 5);
	delay(50);
	audioOff();
	
	fadeDown();	
}

void fadeUp() {
	for (int i = 0; i < 255; i++) {
		tft.setBacklight(i);
		delay(1);
	}	
}

void fadeDown() {
	for (int i = 0; i < 255; i++) {
		tft.setBacklight(254 - i);
		delay(1);
	}	
}

void drawLogo() {
	File f = SD.open("/4dlogo.bmp");
	if (!f) {
		error("Unable to open image file!!!");
        return;
	}
	tft.fillScreen(Color::Gray40);
	BMPFile bmp(f);
	bmp.draw(&tft, 10, 100);
	doContinue();
	tft.fillScreen(Color::Black);
}

void loop() { }

void scribble() {
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Liberation32);
	int tw = tft.stringWidth("DRAW!");
	tft.setCursor(160 - (tw/2), 220);
	tft.setTextColor(Color::White, Color::Black);	
	tft.print("DRAW!");
	fadeUp();
	while (1) {
		ts.sample();
	
		if (ts.isPressed()) {
			tft.fillCircle(ts.x(), ts.y(), 4, Color::Red);
		}
	}
}

void prims() {
	for (int i = 0; i < 1000; i++) {
		int primno = rand() % 7;
		switch (primno) {
			case 0:
				drawLine();
				break;
			case 1:
				drawRectangle();
				break;
			case 2:
				drawCircle();
				break;
			case 3:
				drawFilledRectangle();
				break;
			case 4:
				drawFilledCircle();
				break;
			case 5:
				drawRoundedRectangle();
				break;
			case 6:
				drawFilledRoundedRectangle();
				break;
		}
	}
	doContinue();
	tft.fillScreen(Color::Black);
}

void drawLine() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int endX = rand() % tft.getWidth();
	int endY = rand() % tft.getHeight();
	uint16_t color = rand();

	tft.drawLine(startX, startY, endX, endY, color);
}

void drawRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.drawRectangle(startX, startY, width, height, color);
}

void drawCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.drawCircle(centerX, centerY, radius, color);
}

void drawFilledRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.fillRectangle(startX, startY, width, height, color);
}

void drawFilledCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.fillCircle(centerX, centerY, radius, color);
}

void drawRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.drawRoundRect(startX, startY, width, height, radius, color);
}

void drawFilledRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.fillRoundRect(startX, startY, width, height, radius, color);
}

