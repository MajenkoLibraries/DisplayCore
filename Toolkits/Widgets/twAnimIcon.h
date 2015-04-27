#ifndef _TWANIMICON_H
#define _TWANIMICON_H

#include <Widgets.h>

struct tsAnimIconData {
    uint16_t frames;
    uint16_t width;
    uint16_t height;
    uint16_t data[];
};

class twAnimIcon : public Widget {
    private:
        const struct tsAnimIconData *_data;
        const char *_txt;
        const uint8_t *_font;
        uint16_t _textColor;
        uint16_t _bgColor;

    public:
        twAnimIcon(Touch &ts, DisplayCore &dev, int16_t x, int16_t y, const char *txt, const uint16_t *data, const uint8_t *f) : 
            Widget(ts, dev, x, y), 
            _txt(txt), _data((const struct tsAnimIconData *)data), _font(f),
            _textColor(Color::White), _bgColor(Color::Black) {
                _touch = true;
                _sense_x = 0;
                _sense_y = 0; 
                _sense_w = _data->width;
                _sense_h = _data->height;
        }

        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void setBackgroundColor(uint16_t c) { _bgColor = c; }
        void setTextColor(uint16_t c) { _textColor = c; }
        void setFont(const uint8_t *f) { _font = f; }
        void setLabel(const char *t);

        uint16_t getWidth() { return _data->width; }
        uint16_t getHeight() { return _data->height; }
};

#endif
