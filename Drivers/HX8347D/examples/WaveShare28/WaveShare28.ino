#include <HX8347D.h>
#include <XPT2046.h>

DSPI0 spi;
HX8347D tft(spi, 7, 10); // D/C and CS pins
XPT2046 ts(spi, 4, 240, 320);  // 4 = touch chip select

void setup() {
    Serial.begin(115200);
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);
    tft.initializeDevice();
    ts.initializeDevice();

    ts.setRotation(2);
    ts.scaleX(1.15);
    ts.offsetX(-20);
    ts.scaleY(1.15);
    ts.offsetY(-20);
    
    tft.fillScreen(Color::Black);
    tft.setTextColor(Color::Red);
}

void loop() {
    tft.setCursor(10, 10);
    tft.print(millis());
    ts.sample();
    if (ts.isPressed()) {
        tft.fillCircle(ts.x(), ts.y(), 10, Color::Green);
    }
}