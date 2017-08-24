#ifndef _TWBUTTON_H
#define _TWBUTTON_H

#include <Widgets.h>

class twButton : public Widget {
    private:
        boolean _lastPressed;

        int _width;
        int _height;
        const char *_txt;
        color_t _fgHi;
        color_t _fgLo;
        color_t _bgHi;
        color_t _bgLo;
        const uint8_t *_font;
        int _bevel;
        color_t _bhi;
        color_t _blow;

    public:
        twButton(Touch &ts, DisplayCore &dev, int x, int y, int w, int h, const char *txt) : 
            Widget(ts, dev, x, y), 
            _width(w), _height(h), _txt(txt),
            _fgHi(Color::Black), _fgLo(Color::Black),
            _bgHi(Color::Gray75), _bgLo(Color::Gray50), 
            _font(Fonts::Default), _bevel(2), 
            _bhi(Color::Gray85), _blow(Color::Gray45) {
                _touch = true;
                _sense_x = 0;
                _sense_y = 0; 
                _sense_w = _width;
                _sense_h = _height;
        }

        void draw(DisplayCore *dev, int x, int y);

        void setBackgroundColor(color_t c1, color_t c2) { _bgLo = c1; _bgHi = c2; }
        void setTextColor(color_t c1, color_t c2) { _fgLo = c1; _fgHi = c2; }
        void setBevel(int b) { _bevel = b; }
        void setBevelColor(color_t hi, color_t low) { _bhi = hi; _blow = low; }
        void setFont(const uint8_t *f) { _font = f; }
        void setLabel(char *t);
};

#endif
