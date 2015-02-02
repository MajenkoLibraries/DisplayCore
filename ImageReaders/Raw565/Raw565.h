#ifndef _RAW565_H
#define _RAW565_H

#include <DisplayCore.h>

class Raw565 : public Image {
    public:
        Raw565(const uint16_t *data, uint16_t w, uint16_t h);
        void draw(DisplayCore *dev, int16_t x, int16_t y);
        void draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);
        void draw(DisplayCore &dev, int16_t x, int16_t y) { draw(&dev, x, y); }
        void draw(DisplayCore &dev, int16_t x, int16_t y, uint16_t t) { draw(&dev, x, y, t); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform) { drawTransformed(&dev, x, y, transform); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) { drawTransformed(&dev, x, y, t); }

    private:
        const uint16_t *_data;
};

#endif
