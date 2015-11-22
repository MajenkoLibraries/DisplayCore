#include <Brankic.h>
#include <MonoIcon.h>
#include <Picadillo.h>
#include <Open24Display.h>

char number[50] = "";

Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

MonoIcon num1 (ts, tft, 48, 128, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num1Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num2 (ts, tft, 128, 128, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num2Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num3 (ts, tft, 208, 128, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num3Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num4 (ts, tft, 48, 208, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num4Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num5 (ts, tft, 128, 208, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num5Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num6 (ts, tft, 208, 208, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num6Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num7 (ts, tft, 48, 288, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num7Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num8 (ts, tft, 128, 288, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num8Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon num9 (ts, tft, 208, 288, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num9Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon kpcan (ts, tft, 48, 368, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::ErrorOpen, Color::Red,
    NULL, NULL, Color::White
    );

MonoIcon num0 (ts, tft, 128, 368, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::Num0Open, Color::Cyan,
    NULL, NULL, Color::White
    );

MonoIcon kpok (ts, tft, 208, 368, 64, 64, 
    MonoIcon::MonoIconBG, Brankic::CheckOpen, Color::Green,
    NULL, NULL, Color::White
    );

Form keypad(12, &num1, &num2, &num3, &num4, &num5, &num6, &num7, &num8, &num9, &kpcan, &num0, &kpok);

void addNumber(Event *e) {
    Widget *w = e->source;

    int num = -1;
    if (w == &num1) num = 1;
    if (w == &num2) num = 2;
    if (w == &num3) num = 3;
    if (w == &num4) num = 4;
    if (w == &num5) num = 5;
    if (w == &num6) num = 6;
    if (w == &num7) num = 7;
    if (w == &num8) num = 8;
    if (w == &num9) num = 9;
    if (w == &num0) num = 0;
    if (w == &kpcan) num = 10;
    if (w == &kpok) num = 11;

    number[strlen(number)+1] = 0;

    switch (num) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            number[strlen(number)] = '0' + num;
            break;
        case 10:
        case 11:
            number[0] = 0;
            tft.fillRectangle(0, 0, 320, 100, Color::Black);
            break;
    }

    tft.setFont(Fonts::Open24Display40);
    tft.setTextColor(Color::Red, Color::Black);
    int sw = tft.stringWidth(number);
    tft.setCursor(320-sw, 30);
    tft.print(number);
    
}

void setup() {
    ts.initializeDevice();

    ts.scaleX(4.3);
    ts.scaleY(3.3);
    ts.offsetY(5);

    tft.initializeDevice();
    tft.setBacklight(255);
    tft.fillScreen(Color::Black);

    keypad.onPress(addNumber);
}

void loop() {
    ts.sample();
    keypad.render();
}
