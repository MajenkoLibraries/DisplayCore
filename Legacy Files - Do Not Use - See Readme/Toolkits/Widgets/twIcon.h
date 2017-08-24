#ifndef _TWICON_H
#define _TWICON_H

#include <Widgets.h>

class twIcon : public Widget {
    private:
        int _width;
        int _height;
        const char *_txt;
        const color_t *_icon;
        const uint8_t *_font;
        color_t _textColor;
        color_t _bgColor;

    public:
        twIcon(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, const char *txt, const color_t *icon, const uint8_t *f) : 
            Widget(ts, dev, x, y), 
            _width(w), _height(h), _txt(txt), _icon(icon), _font(f),
            _textColor(Color::White), _bgColor(Color::Black) {
                _touch = true;
                _sense_x = 0;
                _sense_y = 0; 
                _sense_w = _width;
                _sense_h = _height;
        }

        void draw(DisplayCore *dev, int x, int y);

        void setBackgroundColor(color_t c) { _bgColor = c; }
        void setTextColor(color_t c) { _textColor = c; }
        void setFont(const uint8_t *f) { _font = f; }
        void setLabel(const char *t);
};

#endif
