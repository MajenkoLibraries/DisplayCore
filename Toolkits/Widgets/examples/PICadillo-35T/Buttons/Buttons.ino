#include <Picadillo.h>
#include <Widgets.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

twButton on(tft, ts, 0, 100, 160, 100, "ON");
twButton off(tft, ts, 160, 100, 160, 100, "OFF");

twButton a1(tft, ts, 0, 200, 80, 80, "C");
twButton a2(tft, ts, 80, 200, 80, 80, "D");
twButton a3(tft, ts, 160, 200, 80, 80, "E");
twButton a4(tft, ts, 240, 200, 80, 80, "F");

twButton b1(tft, ts, 0, 280, 80, 80, "G");
twButton b2(tft, ts, 80, 280, 80, 80, "A");
twButton b3(tft, ts, 160, 280, 80, 80, "B");
twButton b4(tft, ts, 240, 280, 80, 80, "C");

void setup() {
	tft.initializeDevice();
    tft.setBacklight(255);
	ts.initializeDevice();
    ts.scaleX(4.3);
    ts.scaleY(3.3);
    ts.offsetY(5);

	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Default);
	tft.setTextColor(Color::White);
	on.setBevel(4);
	on.setTextColor(Color::DarkGreen);
	on.setFont(Fonts::Ubuntu30);
	
	off.setBevel(4);
	off.setTextColor(Color::Red);
	off.setFont(Fonts::Ubuntu30);

	a1.setFont(Fonts::Ubuntu20);
	a2.setFont(Fonts::Ubuntu20);
	a3.setFont(Fonts::Ubuntu20);
	a4.setFont(Fonts::Ubuntu20);
	b1.setFont(Fonts::Ubuntu20);
	b2.setFont(Fonts::Ubuntu20);
	b3.setFont(Fonts::Ubuntu20);
	b4.setFont(Fonts::Ubuntu20);

	pinMode(PIN_AUDENB, OUTPUT);
	digitalWrite(PIN_AUDENB, HIGH);
}

void loop() {
	ts.sample();
	static boolean onoff = false;
	boolean onval = on.render();
	boolean offval = off.render();

	if (a1.render()) tone(PIN_AUDIO, 262, 50);
	if (a2.render()) tone(PIN_AUDIO, 294, 50);
	if (a3.render()) tone(PIN_AUDIO, 330, 50);
	if (a4.render()) tone(PIN_AUDIO, 349, 50);

	if (b1.render()) tone(PIN_AUDIO, 392, 50);
	if (b2.render()) tone(PIN_AUDIO, 440, 50);
	if (b3.render()) tone(PIN_AUDIO, 494, 50);
	if (b4.render()) tone(PIN_AUDIO, 523, 50);

	if (onval && (onoff == false)) {
		onoff = true;
		digitalWrite(PIN_AUDENB, LOW);
		tone(PIN_AUDIO, 1000, 10);
		delay(10);
	}
	if (offval && (onoff == true)) {
		onoff = false;
		tone(PIN_AUDIO, 800, 10);
		delay(10);
		digitalWrite(PIN_AUDENB, HIGH);
	}
}
