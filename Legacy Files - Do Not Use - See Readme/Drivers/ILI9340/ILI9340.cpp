#include <ILI9340.h>

void ILI9340::command(uint8_t cmd) {
    _dcp->lat.clr = _dcb;
    _csp->lat.clr = _csb;
    _spi->transfer(cmd);
    _csp->lat.set = _csb;
}

void ILI9340::data(uint8_t dat) {
    _dcp->lat.set = _dcb;
    _csp->lat.clr = _csb;
    _spi->transfer(dat);
    _csp->lat.set = _csb;
}

void ILI9340::initializeDevice() {
    if (_cs >= NUM_DIGITAL_PINS_EXTENDED) {
        return;
    }
    if (_dc >= NUM_DIGITAL_PINS_EXTENDED) {
        return;
    }
    _spi->begin();
    _spi->setSpeed(20000000UL);

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);

    uint32_t port = digitalPinToPort(_cs);
    if (port == NOT_A_PIN) {
        return;
    }
    _csp = (p32_ioport *)portRegisters(port);
    _csb = digitalPinToBitMask(_cs);

    port = digitalPinToPort(_dc);
    if (port == NOT_A_PIN) {
        return;
    }
    _dcp = (p32_ioport *)portRegisters(port);
    _dcb = digitalPinToBitMask(_dc);

    _csp->lat.set = _csb;

    _width  = ILI9340::Width;
    _height = ILI9340::Height;

    pinMode(_reset, OUTPUT);
    digitalWrite(_reset, HIGH);
    delay(100);
    digitalWrite(_reset, LOW);
    delay(100);
    digitalWrite(_reset, HIGH);
    delay(100);

    command(0xEF);
    data(0x03);
    data(0x80);
    data(0x02);

    command(0xCF);
    data(0x00);
    data(0XC1);
    data(0X30);

    command(0xED);
    data(0x64);
    data(0x03);
    data(0X12);
    data(0X81);

    command(0xE8);
    data(0x85);
    data(0x00);
    data(0x78);

    command(0xCB);
    data(0x39);
    data(0x2C);
    data(0x00);
    data(0x34);
    data(0x02);

    command(0xF7);
    data(0x20);

    command(0xEA);
    data(0x00);
    data(0x00);

    command(ILI9340_PWCTR1); //Power control
    data(0x23); //VRH[5:0]

    command(ILI9340_PWCTR2); //Power control
    data(0x10); //SAP[2:0];BT[3:0]

    command(ILI9340_VMCTR1); //VCM control
    data(0x3e);
    data(0x28);

    command(ILI9340_VMCTR2); //VCM control2
    data(0x86); //--

    command(ILI9340_MADCTL); // Memory Access Control
    data(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);

    command(ILI9340_PIXFMT);
    data(0x55);

    command(ILI9340_FRMCTR1);
    data(0x00);
    data(0x18);

    command(ILI9340_DFUNCTR); // Display Function Control
    data(0x08);
    data(0x82);
    data(0x27);

    command(0xF2); // 3Gamma Function Disable
    data(0x00);

    command(ILI9340_GAMMASET); //Gamma curve selected
    data(0x01);

    command(ILI9340_GMCTRP1); //Set Gamma
    data(0x0F);
    data(0x31);
    data(0x2B);
    data(0x0C);
    data(0x0E);
    data(0x08);
    data(0x4E);
    data(0xF1);
    data(0x37);
    data(0x07);
    data(0x10);
    data(0x03);
    data(0x0E);
    data(0x09);
    data(0x00);

    command(ILI9340_GMCTRN1); //Set Gamma
    data(0x00);
    data(0x0E);
    data(0x14);
    data(0x03);
    data(0x11);
    data(0x07);
    data(0x31);
    data(0xC1);
    data(0x48);
    data(0x08);
    data(0x0F);
    data(0x0C);
    data(0x31);
    data(0x36);
    data(0x0F);

    command(ILI9340_SLPOUT); //Exit Sleep
    delay(120);
    command(ILI9340_DISPON); //Display on 
}

void ILI9340::setAddrWindow(int x0, int y0, int x1, int y1) {
	command(ILI9340_CASET); // Column addr set
    data(x0 >> 8);
    data(x0 & 0xFF);
    data(x1 >> 8);
    data(x1 & 0xFF);

	command(ILI9340_PASET); // Row addr set
	data(y0 >> 8);
	data(y0 & 0xFF);     // YSTART
	data(y1 >> 8);
	data(y1 & 0xFF);     // YEND

	command(ILI9340_RAMWR); // write to RAM
}

void ILI9340::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color >> 8);
    data(color & 0xFF);
}

void ILI9340::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9340::fillRectangle(int x, int y, int w, int h, color_t color) {
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

void ILI9340::drawHorizontalLine(int x, int y, int w, color_t color) {
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

void ILI9340::drawVerticalLine(int x, int y, int h, color_t color) {
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

void ILI9340::setRotation(int m) {
	command(ILI9340_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			data(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Width;
			_height = ILI9340::Height;
			break;
		case 1:
		    data(ILI9340_MADCTL_MV | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Height;
			_height = ILI9340::Width;
			break;
		case 2:
			data(ILI9340_MADCTL_MY | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Width;
			_height = ILI9340::Height;
			break;
		case 3:
			data(ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Height;
			_height = ILI9340::Width;
			break;
	}
}

void ILI9340::invertDisplay(boolean i) {
	command(i ? ILI9340_INVON : ILI9340_INVOFF);
}

void ILI9340::openWindow(int x0, int y0, int x1, int y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9340::windowData(color_t c) {
    data(c >> 8);
    data(c & 0xFF);
}

void ILI9340::windowData(color_t *c, int len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i] >> 8);
        data(c[i] & 0xFF);
    }
}

void ILI9340::closeWindow() {
}
