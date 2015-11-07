#include <Picadillo.h>
#include <SD.h>
#include <gciWidget.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

gciWidget meter(ts, tft, "/TEST~DTN", "Meter0");
gciWidget angular(ts, tft, "/TEST~DTN", "Coolgauge0");
gciWidget sw(ts, tft, "/TEST~DTN", "4Dbutton0");
gciWidget slider(ts, tft, "/TEST~DTN", "4Dbutton1");
gciWidget led(ts, tft, "/TEST~DTN", "Led0");
gciWidget knob(ts, tft, "/TEST~DTN", "Knob0");
gciWidget gauge0(ts, tft, "/TEST~DTN", "Gauge0");
gciWidget gauge1(ts, tft, "/TEST~DTN", "Gauge1");
gciWidget button(ts, tft, "/TEST~DTN", "Winbutton0");
gciWidget slidebar(ts, tft, "/TEST~DTN", "Slider0");

boolean switchState = false;
int knobValue = 0;

void setup() {	
	tft.initializeDevice();
    tft.setBacklight(255);

	ts.initializeDevice();
    ts.scaleX(4.3);
    ts.scaleY(3.3);
    ts.offsetY(5);

	tft.fillScreen(Color::Black);
	tft.setTextColor(Color::White);
	tft.setFont(Fonts::Default);
	if (!SD.begin(PIN_SD_SS)) {
		tft.print("Error opening SD card");
	}

	sw.onTap(switchPress);
	slider.onTap(switchPress);
	
	knob.onDrag(turnKnob);

	slidebar.onDrag(dragSlider);

	button.onPress(btnPress);
	button.onRelease(btnRelease);
	button.onTap(btnTap);

}

void dragSlider(Event *e) {
	knobValue = (e->x-5) * 100 / 160;
	if (knobValue < 0) knobValue = 0;
	if (knobValue > 100) knobValue = 100;
	knob.setValue(knobValue);
	slidebar.setValue(knobValue);
	if (switchState) {
		meter.setValue(knobValue);
		gauge0.setValue(knobValue);
	} else {
		angular.setValue(knobValue);
		gauge1.setValue(knobValue);
	}
}

void btnPress(Event *e) {
	e->source->setValue(1);
}

void btnRelease(Event *e) {
	e->source->setValue(0);
}

void btnTap(Event *e) {
	knobValue = 0;
	switchState = false;
	sw.setValue(0);
	slidebar.setValue(0);
	led.setValue(0);
	knob.setValue(0);
	meter.setValue(0);
	angular.setValue(0);
	gauge0.setValue(0);
	gauge1.setValue(0);
	slider.setValue(0);
}


void switchPress(Event *e) {
	switchState = !switchState;
	sw.setValue(switchState ? 1 : 0);
	slider.setValue(switchState ? 1 : 0);
	led.setValue(switchState ? 1 : 0);
}

void turnKnob(Event *e) {
	float px = e->x - (e->source->getWidth() / 2.0);
	float py = e->y - (e->source->getHeight() / 2.0);
	float angle = atan2(py, px);
	int deg = 180 + (angle * 57.2957795);

	knobValue = (float)((deg + 30) % 360) / 2.3;
	
	if (knobValue > 100) knobValue = 100;
	if (knobValue < 0) knobValue = 0;
	
	knob.setValue(knobValue);
	slidebar.setValue(knobValue);
	if (switchState) {
		meter.setValue(knobValue);
		gauge0.setValue(knobValue);
	} else {
		angular.setValue(knobValue);
		gauge1.setValue(knobValue);
	}
}

void loop() {
	ts.sample();
    AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

    meter.render();
    angular.render();
    sw.render();
    slider.render();
    led.render();
    knob.render();
    gauge0.render();
    gauge1.render();
    button.render();
    slidebar.render();
}

