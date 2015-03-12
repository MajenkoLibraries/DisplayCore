#include <Goldelox.h>

boolean Goldelox::command(uint16_t *data, uint8_t len) {
    for (int i = 0; i < len; i++) {
        _dev->write(data[i] >> 8);
        _dev->write(data[i] & 0xFF);
    }
    uint32_t timeout = 1000;
    while (--timeout > 0) {
        if (_dev->available()) {
            return _dev->read() == ACK;
        }
        delay(1);
    }
    return false;
}

void Goldelox::initializeDevice() {
    if (_reset != 255) {
        pinMode(_reset, OUTPUT);
        digitalWrite(_reset, LOW);
        delay(10);
        digitalWrite(_reset, HIGH);
        delay(3000);
    }
}

void Goldelox::displayOn() {
}

void Goldelox::displayOff() {
}

void Goldelox::fillScreen(uint16_t color) {
    uint16_t bytes[2];
    bytes[0] = SET_BG;
    bytes[1] = color;
    command(bytes, 2);
    bytes[0] = CLEAR_SCREEN;
    command(bytes, 1);
}

void Goldelox::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || y < 0) {
        return;
    }
    if (x >= _width || y >= _height) {
        return;
    }
    uint16_t bytes[4];
    bytes[0] = PUT_PIXEL;
    bytes[1] = x;
    bytes[2] = y;
    bytes[3] = color;
    command(bytes, 4);
}

void Goldelox::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    uint16_t bytes[6];
    bytes[0] = DRAW_LINE;
    bytes[1] = x0;
    bytes[2] = y0;
    bytes[3] = x1;
    bytes[4] = y1;
    bytes[5] = color;
    command(bytes, 6);
}

void Goldelox::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    drawLine(x, y, x+w, y, color);
}

void Goldelox::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    drawLine(x, y, x, y+h, color);
}

void Goldelox::drawRectangle(int16_t x0, int16_t y0, int16_t w, int16_t h, uint16_t color) {
    uint16_t bytes[6];
    bytes[0] = DRAW_RECTANGLE;
    bytes[1] = x0;
    bytes[2] = y0;
    bytes[3] = x0 + w;
    bytes[4] = y0 + h;
    bytes[5] = color;
    command(bytes, 6);
}

void Goldelox::fillRectangle(int16_t x0, int16_t y0, int16_t w, int16_t h, uint16_t color) {
    uint16_t bytes[6];
    bytes[0] = FILL_RECTANGLE;
    bytes[1] = x0;
    bytes[2] = y0;
    bytes[3] = x0 + w;
    bytes[4] = y0 + h;
    bytes[5] = color;
    command(bytes, 6);
}

void Goldelox::changeBaudRate(uint32_t baud) {
    uint16_t bval;
    if (baud <= 110) {
        bval = 27271;
    } else if (baud <= 300) {
        bval = 9999;
    } else if (baud <= 600) {
        bval = 4999;
    } else if (baud <= 1200) {
        bval = 2499;
    } else if (baud <= 2400) {
        bval = 1249;
    } else if (baud <= 4800) {
        bval = 624;
    } else if (baud <= 9600) {
        bval = 312;
    } else if (baud <= 14400) {
        bval = 207;
    } else if (baud <= 19200) {
        bval = 155;
    } else if (baud <= 31250) {
        bval = 95;
    } else if (baud <= 38400) {
        bval = 77;
    } else if (baud <= 56000) {
        bval = 53;
    } else if (baud <= 57600) {
        bval = 51;
    } else if (baud <= 115200) {
        bval = 25;
    } else if (baud <= 128000) {
        bval = 22;
    } else if (baud <= 256000) {
        bval = 11;
    } else if (baud <= 300000) {
        bval = 10;
    } else if (baud <= 375000) {
        bval = 8;
    } else if (baud <= 500000) {
        bval = 6;
    } else if (baud <= 600000) {
        bval = 4;
    }
    _dev->write((uint8_t)0x00);
    _dev->write((uint8_t)0x0B);
    _dev->write(bval >> 8);
    _dev->write(bval & 0xFF);
    delay(200);
}

void Goldelox::openWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    _window_x = x;
    _window_y = y;
    _window_w = w;
    _window_h = h;
}

void Goldelox::closeWindow() {
}

void Goldelox::windowData(uint16_t d) {
    // Single word sending is not supported
}

// Caution: THIS MUST BE AN ENTIRE WINDOW'S WORTH OF DATA!!!

void Goldelox::windowData(uint16_t *d, uint32_t len) {
//    if (len < _window_w * _window_h) {
//        return;
//    }
    _dev->write((uint8_t)0x00);
    _dev->write((uint8_t)0x0A);
    _dev->write(_window_x >> 8);
    _dev->write(_window_x & 0xFF);
    _dev->write(_window_y >> 8);
    _dev->write(_window_y & 0xFF);
    _dev->write(_window_w >> 8);
    _dev->write(_window_w & 0xFF);
    _dev->write(_window_h >> 8);
    _dev->write(_window_h & 0xFF);
    for (uint32_t i = 0; i < _window_w * _window_h; i++) {
        _dev->write(d[i] >> 8);
        _dev->write(d[i] & 0xFF);
    }
    uint32_t timeout = 1000;
    while (--timeout > 0) {
        if (_dev->available()) {
            if (_dev->read() == 0x06) {
                return;
            }
        }
        delay(1);
    }
}
