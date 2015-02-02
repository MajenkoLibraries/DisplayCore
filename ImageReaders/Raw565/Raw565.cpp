#include <Raw565.h>

Raw565::Raw565(const uint16_t *data, uint16_t w, uint16_t h) : Image() {
    _data = data;
    _width = w;
    _height = h;
}

void Raw565::draw(DisplayCore *dev, int16_t x, int16_t y) {
    if (_filter != NULL) {
        uint32_t p = 0;
        uint16_t line[getWidth()];
        for (int py = 0; py < getHeight(); py++) {
            for (int px = 0; px < getWidth(); px++) {
                line[px] = _filter->process(_data[p]);
                p++;
            }
            dev->openWindow(x, y + py, getWidth(), 1);
            dev->windowData(line, getWidth());
            dev->closeWindow();
        }
    } else {
        dev->openWindow(x, y, getWidth(), getHeight());
        dev->windowData((uint16_t *)_data, (uint32_t)getWidth() * (uint32_t)getHeight());
        dev->closeWindow();
    }
}

void Raw565::draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t) {
    uint32_t p = 0;
    uint16_t line[getWidth()];

    for (int py = 0; py < getHeight(); py++) {
        boolean haveTrans = false;
        for (int px = 0; px < getWidth(); px++) {
            uint16_t col = _data[p];
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
                if (_data[py * getWidth() + px] != t) {
                    dev->setPixel(x + px, y + py, line[px]);
                }
            }
        }
    }
}

void Raw565::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            switch (transform) {
                default:
                    dev->setPixel(x + px, y + py, _data[p]);
                    break;
                case MirrorH:
                    dev->setPixel(getWidth() - (x + px) - 1, y + py, _data[p]);
                    break;
                case MirrorV:
                    dev->setPixel(x + px, getHeight() - (y + py) - 1, _data[p]);
                    break;
                case Rotate180:
                    dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _data[p]);
                    break;
            }
            p++;
        }
    }
}

void Raw565::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            if (_data[p] != t) {
                switch (transform) {
                    default:
                        dev->setPixel(x + px, y + py, _data[p]);
                        break;
                    case MirrorH:
                        dev->setPixel(getWidth() - (x + px) - 1, y + py, _data[p]);
                        break;
                    case MirrorV:
                        dev->setPixel(x + px, getHeight() - (y + py) - 1, _data[p]);
                        break;
                    case Rotate180:
                        dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _data[p]);
                        break;
                }
            }
            p++;
        }
    }
}
