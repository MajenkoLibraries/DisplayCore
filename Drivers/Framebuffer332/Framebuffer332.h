#ifndef _FRAMEBUFFER332FAST_H
#define _FRAMEBUFFER332FAST_H

#include <DisplayCore.h>

class Framebuffer332 : public Image {
    private:
        uint8_t *_buf;

    public:
        Framebuffer332(int16_t w, int16_t h, uint8_t *b);

        void initializeDevice();

        void setPixel(int16_t x, int16_t y, uint16_t c);
        uint16_t colorAt(int16_t x, int16_t y);
        void fillScreen(uint16_t c);

        void draw(DisplayCore *dev, int16_t x, int16_t y);
        void draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);

        void draw(DisplayCore &dev, int16_t x, int16_t y) { draw(&dev, x, y); }
        void draw(DisplayCore &dev, int16_t x, int16_t y, uint16_t t) { draw(&dev, x, y, t); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform) { drawTransformed(&dev, x, y, transform); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) { drawTransformed(&dev, x, y, t); }


};

#endif
