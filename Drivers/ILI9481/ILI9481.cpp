#include <ILI9481.h>

ILI9481::ILI9481(
    uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
    uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15
) {
    pin_rs = rs;
    pin_wr = wr;
    pin_rd = rd;
    pin_cs = cs;
    pin_reset = reset;
    pin_d0 = d0;
    pin_d1 = d1;
    pin_d2 = d2;
    pin_d3 = d3;
    pin_d4 = d4;
    pin_d5 = d5;
    pin_d6 = d6;
    pin_d7 = d7;
    pin_d8 = d8;
    pin_d9 = d9;
    pin_d10 = d10;
    pin_d11 = d11;
    pin_d12 = d12;
    pin_d13 = d13;
    pin_d14 = d14;
    pin_d15 = d15;
}

void ILI9481::command(uint16_t com) {
    port_rs->lat.clr = mask_rs;
    com & 0x0001 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    com & 0x0002 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    com & 0x0004 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    com & 0x0008 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    com & 0x0010 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    com & 0x0020 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    com & 0x0040 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    com & 0x0080 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    com & 0x0100 ? port_d8->lat.set = mask_d8 : port_d8->lat.clr = mask_d8;
    com & 0x0200 ? port_d9->lat.set = mask_d9 : port_d9->lat.clr = mask_d9;
    com & 0x0400 ? port_d10->lat.set = mask_d10 : port_d10->lat.clr = mask_d10;
    com & 0x0800 ? port_d11->lat.set = mask_d11 : port_d11->lat.clr = mask_d11;
    com & 0x1000 ? port_d12->lat.set = mask_d12 : port_d12->lat.clr = mask_d12;
    com & 0x2000 ? port_d13->lat.set = mask_d13 : port_d13->lat.clr = mask_d13;
    com & 0x4000 ? port_d14->lat.set = mask_d14 : port_d14->lat.clr = mask_d14;
    com & 0x8000 ? port_d15->lat.set = mask_d15 : port_d15->lat.clr = mask_d15;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
}

void ILI9481::data(uint16_t com) {
    port_rs->lat.set = mask_rs;
    com & 0x0001 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    com & 0x0002 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    com & 0x0004 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    com & 0x0008 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    com & 0x0010 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    com & 0x0020 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    com & 0x0040 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    com & 0x0080 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    com & 0x0100 ? port_d8->lat.set = mask_d8 : port_d8->lat.clr = mask_d8;
    com & 0x0200 ? port_d9->lat.set = mask_d9 : port_d9->lat.clr = mask_d9;
    com & 0x0400 ? port_d10->lat.set = mask_d10 : port_d10->lat.clr = mask_d10;
    com & 0x0800 ? port_d11->lat.set = mask_d11 : port_d11->lat.clr = mask_d11;
    com & 0x1000 ? port_d12->lat.set = mask_d12 : port_d12->lat.clr = mask_d12;
    com & 0x2000 ? port_d13->lat.set = mask_d13 : port_d13->lat.clr = mask_d13;
    com & 0x4000 ? port_d14->lat.set = mask_d14 : port_d14->lat.clr = mask_d14;
    com & 0x8000 ? port_d15->lat.set = mask_d15 : port_d15->lat.clr = mask_d15;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
}


void ILI9481::initializeDevice() {
    pinMode(pin_rs, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_rd, OUTPUT);
    pinMode(pin_wr, OUTPUT);
    pinMode(pin_reset, OUTPUT);
    pinMode(pin_d0, OUTPUT);
    pinMode(pin_d1, OUTPUT);
    pinMode(pin_d2, OUTPUT);
    pinMode(pin_d3, OUTPUT);
    pinMode(pin_d4, OUTPUT);
    pinMode(pin_d5, OUTPUT);
    pinMode(pin_d6, OUTPUT);
    pinMode(pin_d7, OUTPUT);
    pinMode(pin_d8, OUTPUT);
    pinMode(pin_d9, OUTPUT);
    pinMode(pin_d10, OUTPUT);
    pinMode(pin_d11, OUTPUT);
    pinMode(pin_d12, OUTPUT);
    pinMode(pin_d13, OUTPUT);
    pinMode(pin_d14, OUTPUT);
    pinMode(pin_d15, OUTPUT);

    port_rs = getPortInformation(pin_rs, &mask_rs);
    port_rd = getPortInformation(pin_rd, &mask_rd);
    port_wr = getPortInformation(pin_wr, &mask_wr);
    port_d0 = getPortInformation(pin_d0, &mask_d0);
    port_d1 = getPortInformation(pin_d1, &mask_d1);
    port_d2 = getPortInformation(pin_d2, &mask_d2);
    port_d3 = getPortInformation(pin_d3, &mask_d3);
    port_d4 = getPortInformation(pin_d4, &mask_d4);
    port_d5 = getPortInformation(pin_d5, &mask_d5);
    port_d6 = getPortInformation(pin_d6, &mask_d6);
    port_d7 = getPortInformation(pin_d7, &mask_d7);
    port_d8 = getPortInformation(pin_d8, &mask_d8);
    port_d9 = getPortInformation(pin_d9, &mask_d9);
    port_d10 = getPortInformation(pin_d10, &mask_d10);
    port_d11 = getPortInformation(pin_d11, &mask_d11);
    port_d12 = getPortInformation(pin_d12, &mask_d12);
    port_d13 = getPortInformation(pin_d13, &mask_d13);
    port_d14 = getPortInformation(pin_d14, &mask_d14);
    port_d15 = getPortInformation(pin_d15, &mask_d15);

    digitalWrite(pin_rs, HIGH);
    digitalWrite(pin_cs, HIGH);
    digitalWrite(pin_rd, HIGH);
    digitalWrite(pin_wr, HIGH);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_cs, LOW);

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
	setAddrWindow(x,y,x,y);
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


uint16_t ILI9481::read(boolean cont) {
    return 0;
}

uint16_t ILI9481_PMP::read(boolean cont) {
    uint16_t din;
    PMADDR = 0x8001;
    if (!cont) {
        while (PMMODEbits.BUSY == 1);
        din = PMDIN;
    }
    while (PMMODEbits.BUSY == 1);
    din = PMDIN;
    return din;
}

uint16_t ILI9481::colorAt(int16_t x, int16_t y) {
	setAddrWindow(x,y,x,y);
    command(0x002E);
    (void)read();
    uint16_t color = read();
    uint16_t color1 = 0;
    color1 |= ((color & 0xF800) >> 11);
    color1 |= (color & 0x07E0);
    color1 |= ((color & 0x001F) << 11);
    return color1;
}
void ILI9481::getRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *buf) {
    setAddrWindow(x, y, x+w-1, y+h-1);
    command(0x002E);
    (void)read();
    (void)read(true);
    for (uint32_t i = 0; i < w * h; i++) {
        uint16_t color1 = 0;
        uint16_t color = read(true);
        buf[i] = 0;
        buf[i] |= ((color & 0xF800) >> 11);
        buf[i] |= (color & 0x07E0);
        buf[i] |= ((color & 0x001F) << 11);
    }
}

