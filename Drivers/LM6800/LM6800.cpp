#include <LM6800.h>

LM6800::LM6800(
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t csa, uint8_t csb, uint8_t csc, uint8_t e,
            uint8_t rs, uint8_t rw, uint8_t reset) {
    _pin_d0 = d0;
    _pin_d1 = d1;
    _pin_d2 = d2;
    _pin_d3 = d3;
    _pin_d4 = d4;
    _pin_d5 = d5;
    _pin_d6 = d6;
    _pin_d7 = d7;
    _pin_csa = csa;
    _pin_csb = csb;
    _pin_csc = csc;
    _pin_e = e;
    _pin_rs = rs;
    _pin_rw = rw;
    _pin_reset = reset;
}

void LM6800::initializeDevice() {
    uint32_t port = 0;

    if (_pin_d0 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d0, OUTPUT);
    port = digitalPinToPort(_pin_d0);
    if (port == NOT_A_PIN) { return; }
    _port_d0 = (p32_ioport *)portRegisters(port);
    _mask_d0 = digitalPinToBitMask(_pin_d0);

    if (_pin_d1 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d1, OUTPUT);
    port = digitalPinToPort(_pin_d1);
    if (port == NOT_A_PIN) { return; }
    _port_d1 = (p32_ioport *)portRegisters(port);
    _mask_d1 = digitalPinToBitMask(_pin_d1);

    if (_pin_d2 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d2, OUTPUT);
    port = digitalPinToPort(_pin_d2);
    if (port == NOT_A_PIN) { return; }
    _port_d2 = (p32_ioport *)portRegisters(port);
    _mask_d2 = digitalPinToBitMask(_pin_d2);

    if (_pin_d3 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d3, OUTPUT);
    port = digitalPinToPort(_pin_d3);
    if (port == NOT_A_PIN) { return; }
    _port_d3 = (p32_ioport *)portRegisters(port);
    _mask_d3 = digitalPinToBitMask(_pin_d3);

    if (_pin_d4 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d4, OUTPUT);
    port = digitalPinToPort(_pin_d4);
    if (port == NOT_A_PIN) { return; }
    _port_d4 = (p32_ioport *)portRegisters(port);
    _mask_d4 = digitalPinToBitMask(_pin_d4);

    if (_pin_d5 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d5, OUTPUT);
    port = digitalPinToPort(_pin_d5);
    if (port == NOT_A_PIN) { return; }
    _port_d5 = (p32_ioport *)portRegisters(port);
    _mask_d5 = digitalPinToBitMask(_pin_d5);

    if (_pin_d6 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d6, OUTPUT);
    port = digitalPinToPort(_pin_d6);
    if (port == NOT_A_PIN) { return; }
    _port_d6 = (p32_ioport *)portRegisters(port);
    _mask_d6 = digitalPinToBitMask(_pin_d6);

    if (_pin_d7 >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_d7, OUTPUT);
    port = digitalPinToPort(_pin_d7);
    if (port == NOT_A_PIN) { return; }
    _port_d7 = (p32_ioport *)portRegisters(port);
    _mask_d7 = digitalPinToBitMask(_pin_d7);

    if (_pin_csa >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_csa, OUTPUT);
    port = digitalPinToPort(_pin_csa);
    if (port == NOT_A_PIN) { return; }
    _port_csa = (p32_ioport *)portRegisters(port);
    _mask_csa = digitalPinToBitMask(_pin_csa);

    if (_pin_csb >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_csb, OUTPUT);
    port = digitalPinToPort(_pin_csb);
    if (port == NOT_A_PIN) { return; }
    _port_csb = (p32_ioport *)portRegisters(port);
    _mask_csb = digitalPinToBitMask(_pin_csb);

    if (_pin_csc >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_csc, OUTPUT);
    port = digitalPinToPort(_pin_csc);
    if (port == NOT_A_PIN) { return; }
    _port_csc = (p32_ioport *)portRegisters(port);
    _mask_csc = digitalPinToBitMask(_pin_csc);

    if (_pin_e >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_e, OUTPUT);
    port = digitalPinToPort(_pin_e);
    if (port == NOT_A_PIN) { return; }
    _port_e = (p32_ioport *)portRegisters(port);
    _mask_e = digitalPinToBitMask(_pin_e);

    if (_pin_rs >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_rs, OUTPUT);
    port = digitalPinToPort(_pin_rs);
    if (port == NOT_A_PIN) { return; }
    _port_rs = (p32_ioport *)portRegisters(port);
    _mask_rs = digitalPinToBitMask(_pin_rs);

    if (_pin_rw >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(_pin_rw, OUTPUT);
    port = digitalPinToPort(_pin_rw);
    if (port == NOT_A_PIN) { return; }
    _port_rw = (p32_ioport *)portRegisters(port);
    _mask_rw = digitalPinToBitMask(_pin_rw);

    _port_rs->lat.set = _mask_rs;
    _port_rw->lat.set = _mask_rw;
    _port_e->lat.set = _mask_e;

    if (_pin_reset != NULL) {
        pinMode(_pin_reset, OUTPUT);
        digitalWrite(_pin_reset, HIGH);
        delay(100);
        digitalWrite(_pin_reset, LOW);
        delay(100);
        digitalWrite(_pin_reset, HIGH);
        delay(100);
    }

    _width  = 256;
    _height = 64;
    command(0, GLCD_CMD_ON);
    command(1, GLCD_CMD_ON);
    command(2, GLCD_CMD_ON);
    command(3, GLCD_CMD_ON);

    command(0, GLCD_CMD_START);
    command(1, GLCD_CMD_START);
    command(2, GLCD_CMD_START);
    command(3, GLCD_CMD_START);

    command(0, GLCD_CMD_SET_Y);
    command(1, GLCD_CMD_SET_Y);
    command(2, GLCD_CMD_SET_Y);
    command(3, GLCD_CMD_SET_Y);

    command(0, GLCD_CMD_SET_PAGE);
    command(1, GLCD_CMD_SET_PAGE);
    command(2, GLCD_CMD_SET_PAGE);
    command(3, GLCD_CMD_SET_PAGE);
}

void LM6800::setPixel(int x, int y, color_t color) {
    doSetPixel(x, y, color);
    if (!_buffered) {
        y = y >> 3;
        uint8_t page = y & 0x07;
        uint8_t chip = x / 64;
        setPage(chip, page);
        setY(chip, x & 63);
        data(chip, this->buffer[(y << 8) + x]);
    }
}

void LM6800::doSetPixel(int x, int y, color_t color) {
    uint8_t row;
    uint8_t pixel;
    uint8_t mask;

	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    row = y>>3;
    pixel = y & 0x07;
    mask = 1<<pixel;
    if (color) {
        this->buffer[(row << 8) + x] |= mask;
    } else {
        this->buffer[(row << 8) + x] &= ~mask;
    }
}

void LM6800::fillScreen(color_t color) {
    for (int16_t x = 0; x < 2048; x++) {
        this->buffer[x] = color ? 0xFF : 0x00;
    }
    updateScreen();
}

void LM6800::fillRectangle(int x, int y, int w, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;

    for (int dy = y; dy < y + h; dy++) {
        for (int dx = x; dx < x + w; dx++) {
            setPixel(dx, dy, color);
        }
    }
    updateScreen();
}

void LM6800::drawHorizontalLine(int x, int y, int w, color_t color) {
    drawLine(x, y, x + w, y, color);
    updateScreen();
}

void LM6800::drawVerticalLine(int x, int y, int h, color_t color) {
    drawLine(x, y, x, y + h, color);
    updateScreen();
}

void LM6800::invertDisplay(boolean i) {
    for (int x = 0; x < 2048; x++) {
        this->buffer[x] = ~this->buffer[x];
    }
    updateScreen();
}

void LM6800::updateScreen() {
    for (int chip = 0; chip < 4; chip++) {
        for(int y=0; y<8; y++)
        {
            setPage(chip, y);
            setY(chip, 0);
            for(int x=0; x<64; x++)
            {
                data(chip, this->buffer[(y << 8) + x + (chip * 64)]);
            }
        }
    }
}
