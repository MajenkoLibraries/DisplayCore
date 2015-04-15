#ifndef _TWBUTTON_H
#define _TWBUTTON_H

#include <Widgets.h>

class twButton : public Widget {
    private:
        boolean _lastPressed;

        uint16_t _width;
        uint16_t _height;
        const char *_txt;
        uint16_t _fgHi;
        uint16_t _fgLo;
        uint16_t _bgHi;
        uint16_t _bgLo;
        const uint8_t *_font;
        uint16_t _bevel;
        uint16_t _bhi;
        uint16_t _blow;

    public:
        twButton(Touch &ts, DisplayCore &dev, int16_t x, int16_t y, uint16_t w, uint16_t h, const char *txt) : 
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

        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void setBackgroundColor(uint16_t c1, uint16_t c2) { _bgLo = c1; _bgHi = c2; }
        void setTextColor(uint16_t c1, uint16_t c2) { _fgLo = c1; _fgHi = c2; }
        void setBevel(uint16_t b) { _bevel = b; }
        void setBevelColor(uint16_t hi, uint16_t low) { _bhi = hi; _blow = low; }
        void setFont(const uint8_t *f) { _font = f; }
        void setLabel(char *t);
};

#endif
