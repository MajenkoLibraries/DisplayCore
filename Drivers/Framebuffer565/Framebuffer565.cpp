#include <Framebuffer565.h>

Framebuffer565::Framebuffer565(int w, int h, color_t *b) {
    _width = w;
    _height = h;
    _buf = b;
}

void Framebuffer565::initializeDevice() {
    fillScreen(0);
}

void Framebuffer565::setPixel(int x, int y, color_t color) {
    translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    _buf[x + y * _width] = color;
}

void Framebuffer565::fillScreen(color_t color) {
    for (uint32_t x = 0; x < _width * _height; x++) {
        _buf[x] = color;
    }
}

void Framebuffer565::draw(DisplayCore *dev, int x, int y) {
    if (_filter != NULL) {
        uint32_t p = 0;
        color_t line[getWidth()];
        for (int py = 0; py < getHeight(); py++) {
            for (int px = 0; px < getWidth(); px++) {
                line[px] = _filter->process(_buf[p]);
                p++;
            }
            dev->openWindow(x, y + py, getWidth(), 1);
            dev->windowData(line, getWidth());
            dev->closeWindow();
        }
    } else {
        dev->openWindow(x, y, getWidth(), getHeight());
        dev->windowData((color_t *)_buf, (uint32_t)getWidth() * (uint32_t)getHeight());
        dev->closeWindow();
    }
}

void Framebuffer565::draw(DisplayCore *dev, int x, int y, color_t t) {
    uint32_t p = 0;
    color_t line[getWidth()];

    for (int py = 0; py < getHeight(); py++) {
        boolean haveTrans = false;
        for (int px = 0; px < getWidth(); px++) {
            color_t col = _buf[p];
            if (col == t) {
                haveTrans = true;
                line[px] = col;
            } else {
                if (_filter != NULL) {
                    col = _filter->process(col);
                }
                line[px] = col;
            }
            p++;
        }
        if (!haveTrans) {
            dev->openWindow(x, y + py, getWidth(), 1);
            dev->windowData(line, getWidth());
            dev->closeWindow();
        } else {
            for (int px = 0; px < getWidth(); px++) {
                if (_buf[py * getWidth() + px] != t) {
                    dev->setPixel(x + px, y + py, line[px]);
                }
            }
        }
    }
}

void Framebuffer565::drawTransformed(DisplayCore *dev, int x, int y, int transform) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            switch (transform) {
                default:
                    dev->setPixel(x + px, y + py, _buf[p]);
                    break;
                case MirrorH:
                    dev->setPixel(getWidth() - (x + px) - 1, y + py, _buf[p]);
                    break;
                case MirrorV:
                    dev->setPixel(x + px, getHeight() - (y + py) - 1, _buf[p]);
                    break;
                case Rotate180:
                    dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _buf[p]);
                    break;
            }
            p++;
        }
    }
}

void Framebuffer565::drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            if (_buf[p] != t) {
                switch (transform) {
                    default:
                        dev->setPixel(x + px, y + py, _buf[p]);
                        break;
                    case MirrorH:
                        dev->setPixel(getWidth() - (x + px) - 1, y + py, _buf[p]);
                        break;
                    case MirrorV:
                        dev->setPixel(x + px, getHeight() - (y + py) - 1, _buf[p]);
                        break;
                    case Rotate180:
                        dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _buf[p]);
                        break;
                }
            }
            p++;
        }
    }
}
