#include <ILI9488.h>

static void inline tinyDelay() {
#if defined(__PIC32MZ__)
    asm volatile("nop");
    asm volatile("nop");
#endif
}

ILI9488::ILI9488(
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
    bus_width = 16;
}

ILI9488::ILI9488(
    uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7
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
    bus_width = 8;
}

void ILI9488::command(uint16_t com) {
    port_rs->lat.clr = mask_rs;
    com & 0x0001 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    com & 0x0002 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    com & 0x0004 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    com & 0x0008 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    com & 0x0010 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    com & 0x0020 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    com & 0x0040 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    com & 0x0080 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    if (bus_width == 16) {
        port_d8->lat.clr = mask_d8;
        port_d9->lat.clr = mask_d9;
        port_d10->lat.clr = mask_d10;
        port_d11->lat.clr = mask_d11;
        port_d12->lat.clr = mask_d12;
        port_d13->lat.clr = mask_d13;
        port_d14->lat.clr = mask_d14;
        port_d15->lat.clr = mask_d15;
    }
    port_wr->lat.clr = mask_wr;
    tinyDelay();
    port_wr->lat.set = mask_wr;
}

void ILI9488::data8(uint8_t com) {
    port_rs->lat.set = mask_rs;
    com & 0x0001 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    com & 0x0002 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    com & 0x0004 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    com & 0x0008 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    com & 0x0010 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    com & 0x0020 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    com & 0x0040 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    com & 0x0080 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    if (bus_width == 16) {
        port_d8->lat.clr = mask_d8;
        port_d9->lat.clr = mask_d9;
        port_d10->lat.clr = mask_d10;
        port_d11->lat.clr = mask_d11;
        port_d12->lat.clr = mask_d12;
        port_d13->lat.clr = mask_d13;
        port_d14->lat.clr = mask_d14;
        port_d15->lat.clr = mask_d15;
    } 
    port_wr->lat.clr = mask_wr;
    tinyDelay();
    port_wr->lat.set = mask_wr;
}

void ILI9488::data16(uint16_t com) {
    port_rs->lat.set = mask_rs;
    if (bus_width == 8) {
        com & 0x0100 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
        com & 0x0200 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
        com & 0x0400 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
        com & 0x0800 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
        com & 0x1000 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
        com & 0x2000 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
        com & 0x4000 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
        com & 0x8000 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
        port_wr->lat.clr = mask_wr;
        tinyDelay();
        port_wr->lat.set = mask_wr;
    }
    com & 0x0001 ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    com & 0x0002 ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    com & 0x0004 ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    com & 0x0008 ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    com & 0x0010 ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    com & 0x0020 ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    com & 0x0040 ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    com & 0x0080 ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    if (bus_width == 16) {
        com & 0x0100 ? port_d8->lat.set = mask_d8 : port_d8->lat.clr = mask_d8;
        com & 0x0200 ? port_d9->lat.set = mask_d9 : port_d9->lat.clr = mask_d9;
        com & 0x0400 ? port_d10->lat.set = mask_d10 : port_d10->lat.clr = mask_d10;
        com & 0x0800 ? port_d11->lat.set = mask_d11 : port_d11->lat.clr = mask_d11;
        com & 0x1000 ? port_d12->lat.set = mask_d12 : port_d12->lat.clr = mask_d12;
        com & 0x2000 ? port_d13->lat.set = mask_d13 : port_d13->lat.clr = mask_d13;
        com & 0x4000 ? port_d14->lat.set = mask_d14 : port_d14->lat.clr = mask_d14;
        com & 0x8000 ? port_d15->lat.set = mask_d15 : port_d15->lat.clr = mask_d15;
    } 
    port_wr->lat.clr = mask_wr;
    tinyDelay();
    port_wr->lat.set = mask_wr;
}


void ILI9488::initializeDevice() {
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
    if (bus_width == 16) {
        pinMode(pin_d8, OUTPUT);
        pinMode(pin_d9, OUTPUT);
        pinMode(pin_d10, OUTPUT);
        pinMode(pin_d11, OUTPUT);
        pinMode(pin_d12, OUTPUT);
        pinMode(pin_d13, OUTPUT);
        pinMode(pin_d14, OUTPUT);
        pinMode(pin_d15, OUTPUT);
    }
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
    if (bus_width == 16) {
        port_d8 = getPortInformation(pin_d8, &mask_d8);
        port_d9 = getPortInformation(pin_d9, &mask_d9);
        port_d10 = getPortInformation(pin_d10, &mask_d10);
        port_d11 = getPortInformation(pin_d11, &mask_d11);
        port_d12 = getPortInformation(pin_d12, &mask_d12);
        port_d13 = getPortInformation(pin_d13, &mask_d13);
        port_d14 = getPortInformation(pin_d14, &mask_d14);
        port_d15 = getPortInformation(pin_d15, &mask_d15);
    }

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

void ILI9488::startDisplay() {
    _width  = ILI9488::Width;
    _height = ILI9488::Height;

    /* PGAMCTRL (Positive Gamma Control) (E0h) */
    command(0xE0);
    data8(0x04);
    data8(0x67);
    data8(0x35);
    data8(0x04);
    data8(0x08);
    data8(0x06);
    data8(0x24);
    data8(0x1);
    data8(0x37);
    data8(0x40);
    data8(0x03);
    data8(0x10);
    data8(0x8);
    data8(0x80);
    data8(0x0);

    /* NGAMCTRL (Negative Gamma Control) (E1h)  */
    command(0xE1);
    data8(0x00);
    data8(0x22);
    data8(0x24);
    data8(0x06);
    data8(0x12);
    data8(0x07);
    data8(0x36);
    data8(0x47);
    data8(0x47);
    data8(0x06);
    data8(0x0a);
    data8(0x07);
    data8(0x30);
    data8(0x37);
    data8(0x0f);

    /* Power Control 1 (C0h)  */
    command(0xC0);
    data8(0x10);
    data8(0x10);

    /* Power Control 2 (C1h)  */
    command(0xC1);
    data8(0x41);

    /* VCOM Control (C5h)  */
    command(0xC5);
    data8(0x00);
    data8(0x2c); // VCOM
    data8(0x80);

    /* Memory Access Control (36h)  */
    command(0x36);
    data8(0x08);
    //- data8(0x08);

    /* Interface Pixel Format (3Ah) */
    command(0x3A);  //Interface Mode Control
    data8(0x55);

    command(0xB0);  //Interface Mode Control
    data8(0x00);
    command(0xB1);   //Frame rate 70HZ
    data8(0xB0);

    /* Display Inversion Control (B4h) */
    command(0xB4);
    data8(0x02);

    /* Display Function Control (B6h)  */
    command(0xB6);  //RGB/MCU Interface Control
    data8(0x02);
    data8(0x22);

    /* Set Image Function (E9h)  */
    command(0xE9);
    data8(0x00);

    /* Adjust Control 3 (F7h)  */
    command(0XF7);
    data8(0xA9);
    data8(0x51);
    data8(0x2C);
    data8(0x82);

    /* Sleep Out (11h) */
    command(0x11);
    delay(150);

    /* Display ON (29h) */
    command(0x29);
}

void ILI9488::setAddrWindow(int x0, int y0, int x1, int y1) {
    command(0x002A);
    data8(x0 >> 8);
    data8(x0 & 0xFF);
    data8(x1 >> 8);
    data8(x1 & 0xFF);
    command(0x002B);
    data8(y0 >> 8);
    data8(y0 & 0xFF);
    data8(y1 >> 8);
    data8(y1 & 0xFF);
    command(0x002c);
}

void ILI9488::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x,y);
    data16(color);
}

void ILI9488::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9488::fillRectangle(int x, int y, int w, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	setAddrWindow(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            data16(color);
		}
	}
}

void ILI9488::drawHorizontalLine(int x, int y, int w, color_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	while (w--) {
        data16(color);
	}
}

void ILI9488::drawVerticalLine(int x, int y, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        data16(color);
	}
}

void ILI9488::setRotation(int m) {
	command(0x36);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			data8(0x08);
			_width  = ILI9488::Width;
			_height = ILI9488::Height;
			break;
		case 1:
		    data8(0x68);
			_width  = ILI9488::Height;
			_height = ILI9488::Width;
			break;
		case 2:
			data8(0xC8);
			_width  = ILI9488::Width;
			_height = ILI9488::Height;
			break;
		case 3:
			data8(0xA8);
			_width  = ILI9488::Height;
			_height = ILI9488::Width;
			break;
	}
}

void ILI9488::invertDisplay(boolean i) {
	command(i ? 0x21 : 0x20);
}

void ILI9488::displayOn() {
    command(0x29);
}

void ILI9488::displayOff() {
    command(0x28);
}

void ILI9488::openWindow(int x0, int y0, int x1, int y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9488::windowData(color_t c) {
    data16(c);
}

void ILI9488::windowData(color_t *c, int len) {
    for (uint32_t i = 0; i < len; i++) {
        data16(c[i]);
    }
}

void ILI9488::closeWindow() {
}


#ifdef _PMMODE_MODE16_POSITION

void ILI9488_PMP::initializeDevice() {
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

void ILI9488_PMP::command(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8000;
    PMDIN = cmd;
}

void ILI9488_PMP::data8(uint8_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8001;
    PMDIN = cmd;
}

void ILI9488_PMP::data16(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8001;
    PMDIN = cmd;
}

uint16_t ILI9488_PMP::read(boolean cont) {
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

#endif


uint16_t ILI9488::read(boolean cont) {
    return 0;
}

color_t ILI9488::colorAt(int x, int y) {
	setAddrWindow(x,y,x,y);
    command(0x002E);
    (void)read();
    color_t color = read();
    color_t color1 = 0;
    color1 |= ((color & 0xF800) >> 11);
    color1 |= (color & 0x07E0);
    color1 |= ((color & 0x001F) << 11);
    return color1;
}
void ILI9488::getRectangle(int x, int y, int w, int h, color_t *buf) {
    setAddrWindow(x, y, x+w-1, y+h-1);
    command(0x002E);
    (void)read();
    (void)read(true);
    for (uint32_t i = 0; i < w * h; i++) {
        color_t color1 = 0;
        color_t color = read(true);
        buf[i] = 0;
        buf[i] |= ((color & 0xF800) >> 11);
        buf[i] |= (color & 0x07E0);
        buf[i] |= ((color & 0x001F) << 11);
    }
}

