#ifndef _TWHBAR_H
#define _TWHBAR_H

#include <Widgets.h>

class twHBar : public Widget {
    private:
        uint16_t _w;
        uint16_t _h;
        int32_t _min;
        int32_t _max;
        int32_t _value;
        uint16_t _border;
        uint16_t _scale;
        uint16_t _bg;

    public:
        twHBar(Touch &ts, DisplayCore &dev, int16_t x, int16_t y, int16_t w, int16_t h) : Widget(ts, dev, x, y),
            _w(w), _h(h),
           _min(0), _max(100), _value(0), _border(Color::Blue), _scale(Color::Blue), _bg(Color::Black) {}

        void draw(DisplayCore *dev, int16_t x, int16_t y);

        void setBorderColor(uint16_t c) { _border = c; }
        void setScaleColor(uint16_t c) { _scale = c; }
        void setBackgroundColor(uint16_t c) { _bg = c; }
        void setMinimum(int32_t m) { _min = m; }
        void setMaximum(int32_t m) { _max = m; }
        void setValue(int32_t m) { _value = m; }
};

#endif
