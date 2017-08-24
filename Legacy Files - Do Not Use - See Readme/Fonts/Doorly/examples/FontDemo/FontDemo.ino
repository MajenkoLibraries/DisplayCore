#include <Picadillo.h>
#include <Doorly.h>

Picadillo tft;

void setup() {
    tft.initializeDevice();
    tft.setRotation(1);
    tft.setBacklight(255);
    tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Doorly);

    tft.setTextWrap(false);
    tft.setCursor(0, 0);

    tft.setTextColor(Color::Red);
    tft.println("Doorly Font...");

    tft.setTextColor(Color::Green);
    tft.println(" Doorly Font...");

    tft.setTextColor(Color::Blue);
    tft.println("  Doorly Font...");

    tft.setTextColor(Color::White);
    tft.println("   Doorly Font...");
}

void loop() {
    tft.setCursor(300, 100);
    tft.print(millis());
}
