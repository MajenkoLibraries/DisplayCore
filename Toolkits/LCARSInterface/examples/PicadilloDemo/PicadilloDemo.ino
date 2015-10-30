#include <Picadillo.h>
#include <LCARSInterface.h>

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

LCARS::HBarBend topBar(
    ts, tft, // Devices to work with
    0, 0, // Top left corner
    LCARS::HBarBend::BendUp | LCARS::HBarBend::BendLeft,
    LCARS::DarkRed, // Left colour
    LCARS::MidOrange, // Mid colour
    LCARS::DarkRed, // Right Color
    LCARS::DarkBlue, // End cap colour
    100, // Mid position
    100, // Mid size
    10, // Bend size
    "19372-33" // Bend text
);

LCARS::HBarBend secondBar(
    ts, tft, // Devices to work with
    0, 62, // Top left corner
    LCARS::HBarBend::BendDown | LCARS::HBarBend::BendLeft,
    LCARS::DarkBlue, // Left colour
    LCARS::MidRed, // Mid colour
    LCARS::DarkOrange, // Right Color
    LCARS::DarkBlue, // End cap colour
    100, // Mid position
    100, // Mid size
    10, // Bend size
    "29424-69" // Bend text
);

LCARS::StaticText title(
    ts, tft,
    380, 7, 
    LCARS::Yellow,
    Fonts::LCARS30,
    "LCARS DEMO"
);

LCARS::MiniScope scope(
    ts, tft,
    200, 80
);

LCARS::RectButton panel1(
    ts, tft,
    0, 124, 80, 40,
    LCARS::DarkOrange,
    LCARS::MidOrange,
    LCARS::LightOrange,
    Fonts::LCARS16,
    "PRESS ME"
);

LCARS::RectButton panel2(
    ts, tft,
    0, 166, 80, 40,
    LCARS::DarkOrange,
    LCARS::MidOrange,
    LCARS::LightOrange,
    Fonts::LCARS16,
    "AND ME"
);

LCARS::RectButton panel3(
    ts, tft,
    0, 208, 80, 40,
    LCARS::DarkOrange,
    LCARS::MidOrange,
    LCARS::LightOrange,
    Fonts::LCARS16,
    "MAYBE ME"
);

LCARS::RectButton panel4(
    ts, tft,
    0, 250, 80, 40,
    LCARS::DarkOrange,
    LCARS::MidOrange,
    LCARS::LightOrange,
    Fonts::LCARS16,
    "ALSO ME"
);

LCARS::VScale scale(
    ts, tft,
    120, 90,
    LCARS::DarkBlue,
    LCARS::MidOrange,
    LCARS::DarkRed
);

LCARS::ExpandedOvalButton toggle(
    ts, tft,
    200, 180, 100, // X, Y, Width of gap area
    LCARS::DarkBlue,
    LCARS::DarkOrange,
    LCARS::LightOrange,
    LCARS::Yellow,
    "TOGGLE",
    "I TOGGLE",
    "I AM OFF",
    "I AM ON"
);

void setScaleValue(Event *e) {
    e->source->setValue(100 - (e->y / 2));
}

void setup() {
	ts.initializeDevice();
    ts.setRotation(1);

	// These set the touch screen resolution.
	ts.scaleX(4.2);
	ts.scaleY(3.2);
	ts.offsetX(10);
    ts.offsetY(10);

	tft.initializeDevice();
    tft.setRotation(1);
	tft.setBacklight(255);
	tft.fillScreen(Color::Black);

    topBar.setValue(0);
    secondBar.setValue(0);

    scale.onPress(setScaleValue);
    scale.onDrag(setScaleValue);
}

void loop() {
    static uint32_t tick = millis();

    ts.sample();

    title.render();
    topBar.render();
    secondBar.render();
    scope.render();
    
    panel1.render();
    panel2.render();
    panel3.render();
    panel4.render();

    scale.render();
    toggle.render();
    
    if (millis() - tick > 1000) {
        tick = millis();

        int pos = rand() % 300;

        topBar.setValue(pos);
        secondBar.setValue(pos);
    }

    scope.setValue(rand() % 4096);

}
