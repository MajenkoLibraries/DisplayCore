#ifndef _FRAMEBUFFER565FAST_H
#define _FRAMEBUFFER565FAST_H

#include <DisplayCore.h>

class Framebuffer565 : public Image {
    private:
        color_t *_buf;

    public:
        Framebuffer565(int w, int h, color_t *b);

        void initializeDevice();

        void setPixel(int x, int y, color_t c);
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
