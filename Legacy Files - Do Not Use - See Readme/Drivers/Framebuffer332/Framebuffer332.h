#ifndef _FRAMEBUFFER332FAST_H
#define _FRAMEBUFFER332FAST_H

#include <DisplayCore.h>

class Framebuffer332 : public Image {
    private:
        uint8_t *_buf;

    public:
        Framebuffer332(int w, int h, uint8_t *b);

        void initializeDevice();

        void setPixel(int x, int y, color_t c);
        color_t colorAt(int x, int y);
        void fillScreen(color_t c);

        void draw(DisplayCore *dev, int x, int y);
        void draw(DisplayCore *dev, int x, int y, color_t t);
        void drawTransformed(DisplayCore *dev, int x, int y, int transform);
        void drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t);

        void draw(DisplayCore &dev, int x, int y) { draw(&dev, x, y); }
        void draw(DisplayCore &dev, int x, int y, color_t t) { draw(&dev, x, y, t); }
        void drawTransformed(DisplayCore &dev, int x, int y, int transform) { drawTransformed(&dev, x, y, transform); }
        void drawTransformed(DisplayCore &dev, int x, int y, int transform, color_t t) { drawTransformed(&dev, x, y, t); }


};

#endif
