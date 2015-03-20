#include <ILI9163.h>

void ILI9163::command(uint16_t com) {
    port_rs->lat.clr = mask_rs;
    port_cs->lat.clr = mask_cs;
    _dspi->transfer(com);
    port_cs->lat.set = mask_cs;
}

void ILI9163::data(uint16_t com) {
    port_rs->lat.set = mask_rs;
    port_cs->lat.clr = mask_cs;
    _dspi->transfer(com);
    port_cs->lat.set = mask_cs;
}

void ILI9163::initializeDevice() {
    pinMode(pin_rs, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_reset, OUTPUT);

    port_rs = getPortInformation(pin_rs, &mask_rs);
    port_cs = getPortInformation(pin_cs, &mask_cs);

    _dspi->begin();
    _dspi->setSpeed(10000000UL);

    digitalWrite(pin_rs, HIGH);
    digitalWrite(pin_cs, HIGH);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);

    startDisplay();
}

void ILI9163::startDisplay() {
    _width  = ILI9163::Width;
    _height = ILI9163::Height;


    command(0x01); // Software reset
    delay(1);
	command(0x11); // Wake up
    delay(20);
    command(0x28); // Turn off the display while we work on it

    command(0x13); // Normal mode
    command(0x20); // No inversion
    command(0x26); // Gamma set
        data(0x01);

	command(0x2A); // Set X dimension
        data(0x00);
        data(0x00);
        data(0x00);
        data(0x7F);

	command(0x2B); // Set Y dimension
        data(0x00);
        data(0x00);
        data(0x00);
        data(0x7F);

	command(0x36); // Set display pixel format BGR
        data(0x0A);

	command(0x3A); // Set interface pixel format 16-bit
        data(0x55);

    delay(120);
	command(0x29); // Turn the display on.
}

void ILI9163::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    // My display has a Y offset of 32 pixels.  The chip is a 128x160 pixel device
    // but connected to a 128x128 screen, so 32 pixels are not driven.
    y0 += 32;
    y1 += 32;
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

void ILI9163::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x,y);
    data(color >> 8);
    data(color & 0xFF);
}

void ILI9163::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
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

void ILI9163::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
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

void ILI9163::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
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

void ILI9163::setRotation(uint8_t m) {
	command(0x36);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			data(0x0A);
			_width  = ILI9163::Width;
			_height = ILI9163::Height;
			break;
		case 1:
		    data(0x28);
			_width  = ILI9163::Height;
			_height = ILI9163::Width;
			break;
		case 2:
			data(0x09);
			_width  = ILI9163::Width;
			_height = ILI9163::Height;
			break;
		case 3:
			data(0x2B);
			_width  = ILI9163::Height;
			_height = ILI9163::Width;
			break;
	}
}

void ILI9163::invertDisplay(boolean i) {
	command(i ? 0x21 : 0x20);
}

void ILI9163::displayOn() {
    command(0x29);
}

void ILI9163::displayOff() {
    command(0x28);
}

void ILI9163::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9163::windowData(uint16_t c) {
    data(c >> 8);
    data(c & 0xFF);
}

void ILI9163::windowData(uint16_t *c, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i] >> 8);
        data(c[i] & 0xFF);
    }
}

void ILI9163::closeWindow() {
}

