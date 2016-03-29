#include <ILI9325.h>


void ILI9325::command(uint8_t cmd) {
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

    _cs_port->lat.set = _cs_mask;
    //delayMicroseconds(1);
}

void ILI9325::data(uint8_t dat) {
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

    _cs_port->lat.set = _cs_mask;
    //delayMicroseconds(1);
}

void ILI9325::initializeDevice() {
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

    _width  = ILI9325::Width;
    _height = ILI9325::Height;

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

    regset(ILI932X_START_OSC, 0x0001);
    delay(50);
    regset(ILI932X_DRIV_OUT_CTRL, 0x0100);
    regset(ILI932X_DRIV_WAV_CTRL, 0x0700);
    regset(ILI932X_ENTRY_MOD, 0x1030);
    regset(ILI932X_RESIZE_CTRL, 0x0000);
    regset(ILI932X_DISP_CTRL2, 0x0202);
    regset(ILI932X_DISP_CTRL3, 0x0000);
    regset(ILI932X_DISP_CTRL4, 0x0000);
    regset(ILI932X_RGB_DISP_IF_CTRL1, 0x0);
    regset(ILI932X_FRM_MARKER_POS, 0x0);
    regset(ILI932X_RGB_DISP_IF_CTRL2, 0x0);
    regset(ILI932X_POW_CTRL1, 0x0000);
    regset(ILI932X_POW_CTRL2, 0x0007);
    regset(ILI932X_POW_CTRL3, 0x0000);
    regset(ILI932X_POW_CTRL4, 0x0000);
    delay(200);
    regset(ILI932X_POW_CTRL1, 0x1690);
    regset(ILI932X_POW_CTRL2, 0x0227);
    delay(50);
    regset(ILI932X_POW_CTRL3, 0x001A);
    delay(50);
    regset(ILI932X_POW_CTRL4, 0x1800);
    regset(ILI932X_POW_CTRL7, 0x002A);
    delay(50);
    regset(ILI932X_GAMMA_CTRL1, 0x0000);
    regset(ILI932X_GAMMA_CTRL2, 0x0000);
    regset(ILI932X_GAMMA_CTRL3, 0x0000);
    regset(ILI932X_GAMMA_CTRL4, 0x0206);
    regset(ILI932X_GAMMA_CTRL5, 0x0808);
    regset(ILI932X_GAMMA_CTRL6, 0x0007);
    regset(ILI932X_GAMMA_CTRL7, 0x0201);
    regset(ILI932X_GAMMA_CTRL8, 0x0000);
    regset(ILI932X_GAMMA_CTRL9, 0x0000);
    regset(ILI932X_GAMMA_CTRL10, 0x0000);
    regset(ILI932X_GRAM_HOR_AD, 0x0000);
    regset(ILI932X_GRAM_VER_AD, 0x0000);
    regset(ILI932X_HOR_START_AD, 0x0000);
    regset(ILI932X_HOR_END_AD, 0x00EF);
    regset(ILI932X_VER_START_AD, 0X0000);
    regset(ILI932X_VER_END_AD, 0x013F);
    regset(ILI932X_GATE_SCAN_CTRL1, 0xA700);
    regset(ILI932X_GATE_SCAN_CTRL2, 0x0003);
    regset(ILI932X_GATE_SCAN_CTRL3, 0x0000);
    regset(ILI932X_PANEL_IF_CTRL1, 0X0010);
    regset(ILI932X_PANEL_IF_CTRL2, 0X0000);
    regset(ILI932X_PANEL_IF_CTRL3, 0X0003);
    regset(ILI932X_PANEL_IF_CTRL4, 0X1100);
    regset(ILI932X_PANEL_IF_CTRL5, 0X0000);
    regset(ILI932X_PANEL_IF_CTRL6, 0X0000);
    regset(ILI932X_DISP_CTRL1, 0x0133);

}

void ILI9325::setAddrWindow(int x0, int y0, int x1, int y1) {
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
      x0 = ILI9325::Width  - 1 - y1;
      y1 = x1;
      x1 = ILI9325::Width  - 1 - t;
      x  = x1;
      y  = y0;
      break;
     case 2:
      t  = x0;
      x0 = ILI9325::Width  - 1 - x1;
      x1 = ILI9325::Width  - 1 - t;
      t  = y0;
      y0 = ILI9325::Height - 1 - y1;
      y1 = ILI9325::Height - 1 - t;
      x  = x1;
      y  = y1;
      break;
     case 3:
      t  = x0;
      x0 = y0;
      y0 = ILI9325::Height - 1 - x1;
      x1 = y1;
      y1 = ILI9325::Height - 1 - t;
      x  = x0;
      y  = y1;
      break;
    }

    regset(0x50, x0);
    regset(0x51, x1);
    regset(0x52, y0);
    regset(0x53, y1);
    regset(0x20, x);
    regset(0x21, y);
    command(0x22);

}

void ILI9325::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color >> 8);
    data(color & 0xFF);
}

void ILI9325::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9325::fillRectangle(int x, int y, int w, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	setAddrWindow(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            data(color >> 8);
            data(color & 0xFF);
		}
	}
}

void ILI9325::drawHorizontalLine(int x, int y, int w, color_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	while (w--) {
        data(color >> 8);
        data(color & 0xFF);
	}
}

void ILI9325::drawVerticalLine(int x, int y, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        data(color >> 8);
        data(color & 0xFF);
	}
}

void ILI9325::setRotation(int m) {
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0: 
            regset(0x3, 0x1030);
			_width  = ILI9325::Width;
			_height = ILI9325::Height;
			break;
		case 1:
            regset(0x3, 0x1028);
			_width  = ILI9325::Height;
			_height = ILI9325::Width;
			break;
		case 2:
            regset(0x3, 0x1000);
			_width  = ILI9325::Width;
			_height = ILI9325::Height;
			break;
		case 3:
            regset(0x3, 0x1018);
			_width  = ILI9325::Height;
			_height = ILI9325::Width;
			break;
	}
}

void ILI9325::invertDisplay(boolean i) {
//	command(i ? ILI9325_INVERTON : ILI9325_INVERTOFF);
}

void ILI9325::openWindow(int x0, int y0, int x1, int y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9325::windowData(color_t c) {
    data(c >> 8);
    data(c & 0xFF);
}

void ILI9325::windowData(color_t *c, int len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i] >> 8);
        data(c[i] & 0xFF);
    }
}

void ILI9325::closeWindow() {
}
