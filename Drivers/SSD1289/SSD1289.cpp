#include <SSD1289.h>

SSD1289::SSD1289(
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

void SSD1289::command(uint16_t com) {
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

void SSD1289::data(uint16_t com) {
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

void SSD1289::initializeDevice() {
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

void SSD1289::startDisplay() {
    _width  = SSD1289::Width;
    _height = SSD1289::Height;

    delay(15);
    command(0x0000); data(0x0001);
    command(0x0003); data(0xA8A4);
    command(0x000C); data(0x0000);
    command(0x000D); data(0x800C);
    command(0x000E); data(0x2B00);
    command(0x001E); data(0x00B7);
    command(0x0001); data(0x2B3F);
    command(0x0002); data(0x0600);
    command(0x0010); data(0x0000);
    command(0x0011); data(0x6070);
    command(0x0005); data(0x0000);
    command(0x0006); data(0x0000);
    command(0x0016); data(0xEF1C);
    command(0x0017); data(0x0003);
    command(0x0007); data(0x0233);
    command(0x000B); data(0x0000);
    command(0x000F); data(0x0000);
    command(0x0041); data(0x0000);
    command(0x0042); data(0x0000);
    command(0x0048); data(0x0000);
    command(0x0049); data(0x013F);
    command(0x004A); data(0x0000);
    command(0x004B); data(0x0000);
    command(0x0044); data(0xEF95);
    command(0x0045); data(0x0000);
    command(0x0046); data(0x013F);
    command(0x0030); data(0x0707);
    command(0x0031); data(0x0204);
    command(0x0032); data(0x0204);
    command(0x0033); data(0x0502);
    command(0x0034); data(0x0507);
    command(0x0035); data(0x0204);
    command(0x0036); data(0x0204);
    command(0x0037); data(0x0502);
    command(0x003A); data(0x0302);
    command(0x003B); data(0x0302);
    command(0x0023); data(0x0000);
    command(0x0024); data(0x0000);
    command(0x0025); data(0x8000);
    command(0x004f); data(0x0000);
    command(0x004e); data(0x0000);
    command(0x0022);
}

static void inline swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void SSD1289::setAddrWindow(int x0, int y0, int x1, int y1) {

    int x0a, x1a, y0a, y1a;

    switch(rotation) {
        case 0:
        case 2:
            break;
        case 1:
        case 3:
            swap(x0, y0);
            swap(x1, y1);
            break;
    }
    command(68); data((x1 << 8) | x0);
    command(69); data(y0);
    command(70); data(y1);
    command(78); data(x0);
    command(79); data(y0);
    command(34);
}

void SSD1289::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

	setAddrWindow(x,y,x,y);
	data(color);
}

void SSD1289::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void SSD1289::fillRectangle(int x, int y, int w, int h, color_t color) {
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            data(color);
		}
	}
}

void SSD1289::drawHorizontalLine(int x, int y, int w, color_t color) {
    int h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }

    setAddrWindow(x, y, x+w-1, y);
    while (w--) {
        data(color);
    }
}

void SSD1289::drawVerticalLine(int x, int y, int h, color_t color) {
    int w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }

    setAddrWindow(x, y, x, y+h-1);
    while (h--) {
        data(color);
    }
}


#define SSD1289_EMODE 0x0003

#define SSD1289_TRI 0x8000
#define SSD1289_DFM 0x4000
#define SSD1289_BGR 0x1000
#define SSD1289_HWM 0x0200
#define SSD1289_ORG 0x0080
#define SSD1289_ID0 0x0000
#define SSD1289_ID1 0x0010
#define SSD1289_ID2 0x0020
#define SSD1289_ID3 0x0030
#define SSD1289_AM  0x0008

void SSD1289::setRotation(int m) {
	rotation = m % 4; // can't be higher than 3
    switch(rotation) {
        case 0:
            command(0x0001); data(0x2B3F);
            _width = Width;
            _height = Height;
            break;
        case 1:
            command(0x0001); data(0x6B3F);
            _width = Height;
            _height = Width;
            break;
        case 2:
            command(0x0001); data(0x693F);
            _width = Width;
            _height = Height;
            break;
        case 3:
            command(0x0001); data(0x293F);
            _width = Height;
            _height = Width;
            break;
    }
}

void SSD1289::invertDisplay(boolean i) {
//	command(i ? SSD1289_INVON : SSD1289_INVOFF);
}

void SSD1289::openWindow(int x0, int y0, int x1, int y1) {
    setAddrWindow(x0, y0, x1, y1);
}

void SSD1289::windowData(color_t d) {
    data(d);
}

void SSD1289::windowData(color_t *d, int l) {
    for (uint32_t i = 0; i < l; i++) {
        data(d[i]);
    }
}

void SSD1289::closeWindow() {
}


void SSD1289_PMP::initializeDevice() {
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

void SSD1289_PMP::command(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8000;
    PMDIN = cmd;
}

void SSD1289_PMP::data(uint16_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8001;
    PMDIN = cmd;
}

