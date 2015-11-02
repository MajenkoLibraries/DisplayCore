#include <VLCD.h>

static const uint8_t CMD_PUSH = 129;
static const uint8_t CMD_SET_DIM = 130;
static const uint8_t CMD_SET_BG = 131;
static const uint8_t CMD_SET_FG = 132;
static const uint8_t CMD_SET_PIX = 133;
static const uint8_t CMD_CLR_PIX = 134;
static const uint8_t CMD_SET_LINE = 135;
static const uint8_t CMD_CLR_LINE = 136;
static const uint8_t CMD_SET_BAUD = 137;

void VLCD::initializeDevice() {
    initializeDevice(Serial);
}

void VLCD::initializeDevice(Stream &s) {
    _ser = &s;
    _width = 64;
    _height = 64;
}

void VLCD::push(uint8_t v) {
    _ser->write(CMD_PUSH);
    _ser->write('a' + (v & 0x0F));
    _ser->write('a' + ((v >> 4) & 0x0F));
}

void VLCD::setBaud(uint32_t b) {
    push(b);
    push(b >> 8);
    push(b >> 16);
    push(b >> 24);
    _ser->write(CMD_SET_BAUD);
}

void VLCD::setPixel(int16_t x, int16_t y, uint16_t c) {
    push(x);
    push(y);
    if (c) {
        _ser->write(CMD_SET_PIX);
    } else {
        _ser->write(CMD_CLR_PIX);
    }
}

void VLCD::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t col) {
    push(x0);
    push(y0);
    push(x1);
    push(y1);
    if (col) {
        _ser->write(CMD_SET_LINE);
    } else {
        _ser->write(CMD_CLR_LINE);
    }
}

void VLCD::setSize(uint16_t x, uint16_t y) {
    push(x);
    push(y);
    _ser->write(CMD_SET_DIM);
    _width = x;
    _height = y;
}

void VLCD::setBackground(uint16_t c) {
    uint32_t rgb = color2rgb(c);
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    push(r);
    push(g);
    push(b);
    _ser->write(CMD_SET_BG);
}

void VLCD::setForeground(uint16_t c) {
    uint32_t rgb = color2rgb(c);
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    push(r);
    push(g);
    push(b);
    _ser->write(CMD_SET_FG);
}

void VLCD::sendData(uint8_t *data) {
    boolean first = true;
    uint32_t pos = 0;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width / 8; x++) {
            sendByte(data[pos++], first);
            first = false;
        }
    }

}

void VLCD::sendByte(uint8_t v, boolean startbit) {
    uint8_t b1 = v >> 4;
    uint8_t b2 = v & 0x0F;

    if (startbit) {
        b1 += 'A';
        b2 += 'a';
    } else {
        b1 += 'a';
        b2 += 'a';
    }
    _ser->write(b1);
    _ser->write(b2);
}

