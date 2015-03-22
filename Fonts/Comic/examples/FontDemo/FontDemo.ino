#include <Picadillo.h>
#include <Comic.h>

Picadillo tft;

void setup() {
    tft.initializeDevice();
    tft.setRotation(1);
    tft.setBacklight(255);
    tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Comic);

    tft.setTextWrap(false);
    tft.setCursor(0, 0);

    tft.setTextColor(Color::Red);
    tft.println("Comic Font...");

    tft.setTextColor(Color::Green);
    tft.println(" Comic Font...");

    tft.setTextColor(Color::Blue);
    tft.println("  Comic Font...");

    tft.setTextColor(Color::White);
    tft.println("   Comic Font...");
}

void loop() {
    tft.setCursor(300, 100);
    tft.print(millis());
}
