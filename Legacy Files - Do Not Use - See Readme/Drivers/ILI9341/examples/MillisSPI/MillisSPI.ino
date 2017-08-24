#include <DSPI.h>
#include <ILI9341.h>

// DSPI channel 0 is where the screen is connected
DSPI0 spi;

// It is wired to use CS pin 10 and RS (AKA DC) pin 9.
ILI9341_DSPI tft(spi, 10, 9);

void setup() {
    // If RESET is wired to the MCU's RESET you want a delay here.
    delay(1000);

    // Backlight happens to be connected to A0.
    pinMode(A0, OUTPUT);
    digitalWrite(A0, HIGH);

    tft.initializeDevice();
    tft.fillScreen(Color::Green);
    tft.setTextColor(Color::Red, Color::Green);
}

void loop() {
    tft.setCursor(20, 20);
    tft.print(millis());
}

