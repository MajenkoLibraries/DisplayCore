#include <ILI9481.h>

void ILI9481::command(uint16_t cmd) {
    _dcp->lat.clr = _dcb;
    _csp->lat.clr = _csb;
    _spi->transfer(cmd);
    _csp->lat.set = _csb;
}

void ILI9481::data(uint16_t dat) {
    _dcp->lat.set = _dcb;
    _csp->lat.clr = _csb;
    _spi->transfer(dat);
    _csp->lat.set = _csb;
}

void ILI9481::initializeDevice() {
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
    startDisplay();
}

void ILI9481::startDisplay() {
    _width  = ILI9481::Width;
    _height = ILI9481::Height;

	command(0x11);
    delay(20);
	command(0xD0);
    data(0x07);
    data(0x42);
    data(0x18);

	command(0xD1);
    data(0x00);
    data(0x07);
    data(0x10);

	command(0xD2);
    data(0x01);
    data(0x02);

	command(0xC0);
    data(0x10);
    data(0x3B);
    data(0x00);
    data(0x02);
    data(0x11);

	command(0xC5);
    data(0x03);

	command(0xC8);
    data(0x00);
    data(0x32);
    data(0x36);
    data(0x45);
    data(0x06);
    data(0x16);
    data(0x37);
    data(0x75);
    data(0x77);
    data(0x54);
    data(0x0C);
    data(0x00);

	command(0x36);
    data(0x0A);


	command(0x3A);
    data(0x55);

	command(0x2A);
    data(0x00);
    data(0x00);
    data(0x01);
    data(0x3F);

	command(0x2B);
    data(0x00);
    data(0x00);
    data(0x01);
    data(0xE0);
    delay(120);
	command(0x29);
}

void ILI9481::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    command(0x002A);
    data(x0 >> 8);
    data(x0 & 0xFF);
    data(x1 >> 8);
    data(x1 & 0xFF);
    command(0x002B);
    data(y0 >> 8);
    data(y0 & 0xFF);
    data(y1 >> 8);
    data(y1 & 0xFF);
    command(0x002c);
}

void ILI9481::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color);
}

void ILI9481::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9481::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	setAddrWindow(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            data(color);
		}
	}
}

void ILI9481::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	while (w--) {
        data(color);
	}
}

void ILI9481::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        data(color);
	}
}

void ILI9481::setRotation(uint8_t m) {
	command(0x36);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			data(0x0A);
			_width  = ILI9481::Width;
			_height = ILI9481::Height;
			break;
		case 1:
		    data(0x28);
			_width  = ILI9481::Height;
			_height = ILI9481::Width;
			break;
		case 2:
			data(0x09);
			_width  = ILI9481::Width;
			_height = ILI9481::Height;
			break;
		case 3:
			data(0x2B);
			_width  = ILI9481::Height;
			_height = ILI9481::Width;
			break;
	}
}

void ILI9481::invertDisplay(boolean i) {
	command(i ? 0x21 : 0x20);
}

void ILI9481::displayOn() {
    command(0x29);
}

void ILI9481::displayOff() {
    command(0x28);
}

void ILI9481::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9481::windowData(uint16_t c) {
    data(c);
}

void ILI9481::windowData(uint16_t *c, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i]);
    }
}

void ILI9481::closeWindow() {
}


void ILI9481_PMP::initializeDevice() {
    PMCONbits.ON = 0;
    asm volatile("nop");

    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;
    PMCONbits.CSF = 0b01; // Enable CS2

    PMAEN = 0x8001; // Enable PMA0 pin for DC pin and CS2 as CS

    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 1;
    PMMODEbits.WAITE = 0;

    PMADDR = 0x8000; // Set current address to 0, CS2 Active

    PMCONbits.ON = 1;

    pinMode(pin_reset, OUTPUT);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);

    startDisplay();
}

void ILI9481_PMP::command(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8000;
    PMDIN = cmd;
}

void ILI9481_PMP::data(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8001;
    PMDIN = cmd;
}

