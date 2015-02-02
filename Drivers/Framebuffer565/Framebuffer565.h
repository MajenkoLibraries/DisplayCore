#ifndef _FRAMEBUFFER565FAST_H
#define _FRAMEBUFFER565FAST_H

#include <DisplayCore.h>

class Framebuffer565 : public Image {
    private:
        uint16_t *_buf;

    public:
        Framebuffer565(int16_t w, int16_t h, uint16_t *b);

        void initializeDevice();

        void setPixel(int16_t x, int16_t y, uint16_t c);
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
