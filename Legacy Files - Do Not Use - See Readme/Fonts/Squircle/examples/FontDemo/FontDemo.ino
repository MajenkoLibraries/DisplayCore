#include <Picadillo.h>
#include <Squircle.h>

Picadillo tft;

void setup() {
    tft.initializeDevice();
    tft.setRotation(1);
    tft.setBacklight(255);
    tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Squircle);

    tft.setTextWrap(false);
    tft.setCursor(0, 0);

    tft.setTextColor(Color::Red);
    tft.println("Squircle Font...");

    tft.setTextColor(Color::Green);
    tft.println(" Squircle Font...");

    tft.setTextColor(Color::Blue);
    tft.println("  Squircle Font...");

    tft.setTextColor(Color::White);
    tft.println("   Squircle Font...");
}

void loop() {
    tft.setCursor(300, 100);
    tft.print(millis());
}
