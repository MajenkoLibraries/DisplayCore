#ifndef _TWICON_H
#define _TWICON_H

#include <Widgets.h>

class twIcon : public Widget {
    private:
        uint16_t _width;
        uint16_t _height;
        const uint16_t *_icon;
        const char *_txt;
        const uint8_t *_font;
        uint16_t _textColor;
        uint16_t _bgColor;

    public:
        twIcon(Touch &ts, DisplayCore &dev, int16_t x, int16_t y, uint16_t w, uint16_t h, const char *txt, const uint16_t *icon, const uint8_t *f) : 
            Widget(ts, dev, x, y), 
            _width(w), _height(h), _txt(txt), _icon(icon), _font(f),
            _textColor(Color::White), _bgColor(Color::Black) {
                _touch = true;
                _sense_x = 0;
                _sense_y = 0; 
                _sense_w = _width;
                _sense_h = _height;
        }

        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void setBackgroundColor(uint16_t c) { _bgColor = c; }
        void setTextColor(uint16_t c) { _textColor = c; }
        void setFont(const uint8_t *f) { _font = f; }
        void setLabel(const char *t);
};

#endif
