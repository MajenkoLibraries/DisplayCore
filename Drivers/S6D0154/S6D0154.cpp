#include <S6D0154.h>

uint32_t S6D0154::readIdCode() {
    command(0, true);
    uint8_t b0 = read(true);
    uint8_t b1 = read(false);

    return (b0 << 8) | b1;
}

void S6D0154::command(uint8_t cmd, bool cont) {
    //delayMicroseconds(1);
    _rs_port->lat.clr = _rs_mask;
    _cs_port->lat.clr = _cs_mask;

    if (cmd & 0x01) _d0_port->lat.set = _d0_mask; else _d0_port->lat.clr = _d0_mask;
    if (cmd & 0x02) _d1_port->lat.set = _d1_mask; else _d1_port->lat.clr = _d1_mask;
    if (cmd & 0x04) _d2_port->lat.set = _d2_mask; else _d2_port->lat.clr = _d2_mask;
    if (cmd & 0x08) _d3_port->lat.set = _d3_mask; else _d3_port->lat.clr = _d3_mask;
    if (cmd & 0x10) _d4_port->lat.set = _d4_mask; else _d4_port->lat.clr = _d4_mask;
    if (cmd & 0x20) _d5_port->lat.set = _d5_mask; else _d5_port->lat.clr = _d5_mask;
    if (cmd & 0x40) _d6_port->lat.set = _d6_mask; else _d6_port->lat.clr = _d6_mask;
    if (cmd & 0x80) _d7_port->lat.set = _d7_mask; else _d7_port->lat.clr = _d7_mask;

    //delayMicroseconds(1);
    _wr_port->lat.clr = _wr_mask;
    //delayMicroseconds(1);
    _wr_port->lat.set = _wr_mask;
    //delayMicroseconds(1);

    if (!cont) {
        _cs_port->lat.set = _cs_mask;
    }
    //delayMicroseconds(1);
}

void S6D0154::data(uint8_t dat, bool cont) {
    //delayMicroseconds(1);
    _rs_port->lat.set = _rs_mask;
    _cs_port->lat.clr = _cs_mask;

    if (dat & 0x01) _d0_port->lat.set = _d0_mask; else _d0_port->lat.clr = _d0_mask;
    if (dat & 0x02) _d1_port->lat.set = _d1_mask; else _d1_port->lat.clr = _d1_mask;
    if (dat & 0x04) _d2_port->lat.set = _d2_mask; else _d2_port->lat.clr = _d2_mask;
    if (dat & 0x08) _d3_port->lat.set = _d3_mask; else _d3_port->lat.clr = _d3_mask;
    if (dat & 0x10) _d4_port->lat.set = _d4_mask; else _d4_port->lat.clr = _d4_mask;
    if (dat & 0x20) _d5_port->lat.set = _d5_mask; else _d5_port->lat.clr = _d5_mask;
    if (dat & 0x40) _d6_port->lat.set = _d6_mask; else _d6_port->lat.clr = _d6_mask;
    if (dat & 0x80) _d7_port->lat.set = _d7_mask; else _d7_port->lat.clr = _d7_mask;

    //delayMicroseconds(1);
    _wr_port->lat.clr = _wr_mask;
    //delayMicroseconds(1);
    _wr_port->lat.set = _wr_mask;
    //delayMicroseconds(1);

    if (!cont) {
        _cs_port->lat.set = _cs_mask;
    }
    //delayMicroseconds(1);
}

uint8_t S6D0154::read(bool cont) {
    uint8_t dat = 0;
    _rs_port->lat.set = _rs_mask;
    _cs_port->lat.clr = _cs_mask;

    _d0_port->tris.set = _d0_mask;
    _d1_port->tris.set = _d1_mask;
    _d2_port->tris.set = _d2_mask;
    _d3_port->tris.set = _d3_mask;
    _d4_port->tris.set = _d4_mask;
    _d5_port->tris.set = _d5_mask;
    _d6_port->tris.set = _d6_mask;
    _d7_port->tris.set = _d7_mask;

    _rd_port->lat.clr = _rd_mask;
    delayMicroseconds(1);

    dat |= _d0_port->port.reg & _d0_mask ? 0x01 : 0;
    dat |= _d1_port->port.reg & _d1_mask ? 0x02 : 0;
    dat |= _d2_port->port.reg & _d2_mask ? 0x04 : 0;
    dat |= _d3_port->port.reg & _d3_mask ? 0x08 : 0;
    dat |= _d4_port->port.reg & _d4_mask ? 0x10 : 0;
    dat |= _d5_port->port.reg & _d5_mask ? 0x20 : 0;
    dat |= _d6_port->port.reg & _d6_mask ? 0x40 : 0;
    dat |= _d7_port->port.reg & _d7_mask ? 0x80 : 0;

    _rd_port->lat.set = _rd_mask;

    if (!cont) {
        _cs_port->lat.set = _cs_mask;
    }

    _d0_port->tris.clr = _d0_mask;
    _d1_port->tris.clr = _d1_mask;
    _d2_port->tris.clr = _d2_mask;
    _d3_port->tris.clr = _d3_mask;
    _d4_port->tris.clr = _d4_mask;
    _d5_port->tris.clr = _d5_mask;
    _d6_port->tris.clr = _d6_mask;
    _d7_port->tris.clr = _d7_mask;

    return dat;
}

void S6D0154::initializeDevice() {
    if (_cs_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_rs_pin >= NUM_DIGITAL_PINS_EXTENDED) return; 
    if (_wr_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_rd_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_reset_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d0_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d1_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d2_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d3_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d4_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d5_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d6_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d7_pin >= NUM_DIGITAL_PINS_EXTENDED) return;

    pinMode(_cs_pin, OUTPUT);
    pinMode(_rs_pin, OUTPUT);
    pinMode(_wr_pin, OUTPUT);
    pinMode(_rd_pin, OUTPUT);
    pinMode(_reset_pin, OUTPUT);
    pinMode(_d0_pin, OUTPUT);
    pinMode(_d1_pin, OUTPUT);
    pinMode(_d2_pin, OUTPUT);
    pinMode(_d3_pin, OUTPUT);
    pinMode(_d4_pin, OUTPUT);
    pinMode(_d5_pin, OUTPUT);
    pinMode(_d6_pin, OUTPUT);
    pinMode(_d7_pin, OUTPUT);

    _cs_port = getPortInformation(_cs_pin, &_cs_mask);
    _rs_port = getPortInformation(_rs_pin, &_rs_mask);
    _wr_port = getPortInformation(_wr_pin, &_wr_mask);
    _rd_port = getPortInformation(_rd_pin, &_rd_mask);
    _d0_port = getPortInformation(_d0_pin, &_d0_mask);
    _d1_port = getPortInformation(_d1_pin, &_d1_mask);
    _d2_port = getPortInformation(_d2_pin, &_d2_mask);
    _d3_port = getPortInformation(_d3_pin, &_d3_mask);
    _d4_port = getPortInformation(_d4_pin, &_d4_mask);
    _d5_port = getPortInformation(_d5_pin, &_d5_mask);
    _d6_port = getPortInformation(_d6_pin, &_d6_mask);
    _d7_port = getPortInformation(_d7_pin, &_d7_mask);

    _width  = S6D0154::Width;
    _height = S6D0154::Height;

    digitalWrite(_cs_pin, HIGH);
    digitalWrite(_rs_pin, HIGH);
    digitalWrite(_wr_pin, HIGH);
    digitalWrite(_rd_pin, HIGH);

    digitalWrite(_reset_pin, HIGH);
    delay(100);
    digitalWrite(_reset_pin, LOW);
    delay(100);
    digitalWrite(_reset_pin, HIGH);
    delay(100);

    regset(0x11,0x001A);
    regset(0x12,0x3121);
    regset(0x13,0x006C);
    regset(0x14,0x4249);

    regset(0x10,0x0800);
    delay(10);
    regset(0x11,0x011A);
    delay(10);
    regset(0x11,0x031A);
    delay(10);
    regset(0x11,0x071A);
    delay(10);
    regset(0x11,0x0F1A);
    delay(20);
    regset(0x11,0x0F3A);
    delay(30);

    regset(0x01,0x0128);
    regset(0x02,0x0100);
    regset(0x03,0x1030);
    regset(0x07,0x1012);
    regset(0x08,0x0303);
    regset(0x0B,0x1100);
    regset(0x0C,0x0000);
    regset(0x0F,0x1801);
    regset(0x15,0x0020);
    regset(0x07,0x0012);
    delay(40);

    regset(0x07,0x0013);/*  GRAM Address Set */
    regset(0x07,0x0017);/*  Display Control  DISPLAY ON */
}

void S6D0154::setAddrWindow(int x0, int y0, int x1, int y1) {
    // Values passed are in current (possibly rotated) coordinate
    // system.  932X requires hardware-native coords regardless of
    // MADCTL, so rotate inputs as needed.  The address counter is
    // set to the top-left corner -- although fill operations can be
    // done in any direction, the current screen rotation is applied
    // because some users find it disconcerting when a fill does not
    // occur top-to-bottom.
    int x, y, t;
    switch(rotation) {
     default:
      x  = x0;
      y  = y0;
      break;
     case 1:
      t  = y0;
      y0 = x0;
      x0 = S6D0154::Width  - 1 - y1;
      y1 = x1;
      x1 = S6D0154::Width  - 1 - t;
      x  = x1;
      y  = y0;
      break;
     case 2:
      t  = x0;
      x0 = S6D0154::Width  - 1 - x1;
      x1 = S6D0154::Width  - 1 - t;
      t  = y0;
      y0 = S6D0154::Height - 1 - y1;
      y1 = S6D0154::Height - 1 - t;
      x  = x1;
      y  = y1;
      break;
     case 3:
      t  = x0;
      x0 = y0;
      y0 = S6D0154::Height - 1 - x1;
      x1 = y1;
      y1 = S6D0154::Height - 1 - t;
      x  = x0;
      y  = y1;
      break;
    }

    regset(0x37, x0);
    regset(0x36, x1);
    regset(0x39, y0);
    regset(0x38, y1);
    regset(0x20, x);
    regset(0x21, y);
    command(0x22, 0);
}

void S6D0154::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color >> 8, true);
    data(color & 0xFF, false);
}

void S6D0154::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void S6D0154::fillRectangle(int x, int y, int w, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	setAddrWindow(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            data(color >> 8, true);
            data(color & 0xFF, false);
		}
	}
}

void S6D0154::drawHorizontalLine(int x, int y, int w, color_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	while (w--) {
        data(color >> 8, true);
        data(color & 0xFF, false);
	}
}

void S6D0154::drawVerticalLine(int x, int y, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        data(color >> 8, true);
        data(color & 0xFF, false);
	}
}

void S6D0154::setRotation(int m) {
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0: 
            regset(0x3, 0x1030);
			_width  = S6D0154::Width;
			_height = S6D0154::Height;
			break;
		case 1:
            regset(0x3, 0x1028);
			_width  = S6D0154::Height;
			_height = S6D0154::Width;
			break;
		case 2:
            regset(0x3, 0x1000);
			_width  = S6D0154::Width;
			_height = S6D0154::Height;
			break;
		case 3:
            regset(0x3, 0x1018);
			_width  = S6D0154::Height;
			_height = S6D0154::Width;
			break;
	}
}

void S6D0154::invertDisplay(boolean i) {
//	command(i ? S6D0154_INVERTON : S6D0154_INVERTOFF);
}

void S6D0154::openWindow(int x0, int y0, int x1, int y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void S6D0154::windowData(color_t c) {
    data(c >> 8, true);
    data(c & 0xFF, false);
}

void S6D0154::windowData(color_t *c, int len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i] >> 8, true);
        data(c[i] & 0xFF, i < (len-1));
    }
}

void S6D0154::closeWindow() {
}
