#ifndef _TWTEXT_H
#define _TWTEXT_H

#include <Widgets.h>

class twText : public Widget {
    private:
        uint16_t _color;
        const uint8_t *_font;
        char _text[100];
        uint8_t _align;

    public:
        static const uint8_t AlignLeft = 0;
        static const uint8_t AlignRight = 1;
        static const uint8_t AlignCenter = 2;
        twText(Touch &ts, DisplayCore &dev, int x, int y, uint16_t col, const uint8_t *f, const char *txt) : Widget(ts, dev, x, y), 
            _color(col), _font(f), _align(AlignLeft) {
            memset(_text, 0, 100);
            strncpy(_text, txt, 99);
        }
            
        void setPixel(int16_t x, int16_t y, uint16_t c) {} // No drawing!

        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void initializeDevice() { }

        void setAlign(uint8_t align);
        void setText(const char *txt);
};

#endif
