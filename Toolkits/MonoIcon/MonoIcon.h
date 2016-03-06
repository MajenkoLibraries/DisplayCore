#ifndef _MONO_ICON_H
#define _MONO_ICON_H

#include <DisplayCore.h>
#include <Framebuffer565.h>

class MonoIcon : public Widget {
    private:
        const uint16_t *_bg;
        const uint8_t *_icon;
        uint16_t _color;
        const char *_text;
        const uint8_t *_font;
        uint16_t _textcol;

    public:
        static const uint16_t MonoIconBG[];

        MonoIcon(Touch &ts, DisplayCore &dev, int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *bg, const uint8_t *icon, uint16_t color, 
                                const char *text, const uint8_t *font, uint16_t textcol) :
            Widget(ts, dev, x, y), _bg(bg), _icon(icon), _color(color), _text(text), _font(font), _textcol(textcol) {
                _touch = true;
                _sense_x = 0;
                _sense_y = 0;
                _sense_w = w;
                _sense_h = h;
            }

        void draw(DisplayCore *dev, int16_t x, int16_t y);
        void setColor(uint16_t c);
        void setIcon(const uint8_t *i);
};

#endif
