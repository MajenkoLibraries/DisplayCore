#include <KS0108.h>

void KS0108::setPage(uint8_t page)
{
    command(GLCD_CMD_SET_PAGE | (page & 0x07));
}

void KS0108::setY(uint8_t y)
{
    command(GLCD_CMD_SET_Y | (y & 63));
}

void KS0108::endBuffer() {
    _buffered--;
    if (_buffered <= 0) {
        _buffered = 0;
        uint8_t x,y;
        for(y=0; y<8; y++)
        {
            setPage(y);
            setY(0);
            for(x=0; x<64; x++)
            {
                data(_buffer[C2B(x, y)]);
            }
        }
    }
}

void KS0108::startBuffer() {
    _buffered++;
}

// This is where we configure the PMP and set up the display
void KS0108::initializeDevice() {
    PMCONbits.ON = 0; // Turn it off while we sort it all out
    delayMicroseconds(2);

    // Turn on the RD and WR pins
    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;

    // Turn on the address pins we need
    PMAEN |= (_reg | _data);

#ifdef _PMMODE_MODE16_MASK
    PMMODEbits.MODE16 = 0;  // 8-bit mode
#endif
    PMMODEbits.MODE = 0b11; // RW + E
    PMCONbits.WRSP = 1; // E is active HIGH
    PMCONbits.RDSP = 1; // RW is HIGH for read, LOW for write
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 10;
    PMMODEbits.WAITE = 0;

    PMCONbits.ON = 1; // We're done, so turn it on again

    delayMicroseconds(20);

    displayInit(); // Configure the screen itself.
}

void KS0108::displayInit() {
    command(GLCD_CMD_ON);
    command(GLCD_CMD_START);
}

void KS0108::command(uint8_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = _reg;
    PMDIN = c;
    delayMicroseconds(5);
}

void KS0108::data(uint8_t d) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = _data;
    PMDIN = d;
    delayMicroseconds(5);
}

void KS0108::setPixel(int x, int y, color_t color) {
    uint8_t row;
    uint8_t pixel;
    uint8_t mask;

	if((x < 0) ||(x >= 64) || (y < 0) || (y >= 64)) 
		return;

    row = y>>3;
    pixel = y & 0x07;
    mask = 1<<pixel;
    if (color) {
        _buffer[C2B(x, row)] |= mask;
    } else {
        _buffer[C2B(x, row)] &= ~mask;
    }

    if (_buffered == 0) {
        setPage(row);
        setY(x);
        data(_buffer[C2B(x, row)]);
    }
}

int KS0108::getWidth() { return 64; }
int KS0108::getHeight() { return 64; }

void KS0108_BB2::initializeDevice() {
    _lcd1.initializeDevice();
    _lcd2.initializeDevice();
}

void KS0108_2::initializeDevice() {
    _lcd1.initializeDevice();
    _lcd2.initializeDevice();
}

void KS0108_BB2::setPixel(int x, int y, color_t color) {
    if (x >= 64) {
        _lcd2.setPixel(x-64, y, color);
    } else {
        _lcd1.setPixel(x, y, color);
    }
}

void KS0108_2::setPixel(int x, int y, color_t color) {
    if (x >= 64) {
        _lcd2.setPixel(x-64, y, color);
    } else {
        _lcd1.setPixel(x, y, color);
    }
}

void KS0108_BB2::startBuffer() {
    _lcd1.startBuffer();
    _lcd2.startBuffer();
}

void KS0108_2::startBuffer() {
    _lcd1.startBuffer();
    _lcd2.startBuffer();
}

void KS0108_BB2::endBuffer() {
    _lcd1.endBuffer();
    _lcd2.endBuffer();
}

void KS0108_2::endBuffer() {
    _lcd1.endBuffer();
    _lcd2.endBuffer();
}

int KS0108_2::getWidth() { return 128; }
int KS0108_2::getHeight() { return 64; }

int KS0108_BB2::getWidth() { return 128; }
int KS0108_BB2::getHeight() { return 64; }

void KS0108_BB::initializeDevice() {
    _port_rs = getPortInformation(_rs, &_mask_rs);
    _port_rw = getPortInformation(_rw, &_mask_rw);
    _port_e = getPortInformation(_e, &_mask_e);
    _port_cs = getPortInformation(_cs, &_mask_cs);
    _port_d0 = getPortInformation(_d0, &_mask_d0);
    _port_d1 = getPortInformation(_d1, &_mask_d1);
    _port_d2 = getPortInformation(_d2, &_mask_d2);
    _port_d3 = getPortInformation(_d3, &_mask_d3);
    _port_d4 = getPortInformation(_d4, &_mask_d4);
    _port_d5 = getPortInformation(_d5, &_mask_d5);
    _port_d6 = getPortInformation(_d6, &_mask_d6);
    _port_d7 = getPortInformation(_d7, &_mask_d7);

    pinMode(_rs, OUTPUT);
    pinMode(_rw, OUTPUT);
    pinMode(_e, OUTPUT);
    pinMode(_cs, OUTPUT);
    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);
    pinMode(_d4, OUTPUT);
    pinMode(_d5, OUTPUT);
    pinMode(_d6, OUTPUT);
    pinMode(_d7, OUTPUT);

    delayMicroseconds(20);

    digitalWrite(_rw, LOW);
    digitalWrite(_cs, LOW);

    displayInit(); // Configure the screen itself.
}

void KS0108_BB::command(uint8_t c) {
    _port_rs->lat.clr = _mask_rs;
    _port_cs->lat.set = _mask_cs;
    if (c & 0x01) _port_d0->lat.set = _mask_d0; else _port_d0->lat.clr = _mask_d0;
    if (c & 0x02) _port_d1->lat.set = _mask_d1; else _port_d1->lat.clr = _mask_d1;
    if (c & 0x04) _port_d2->lat.set = _mask_d2; else _port_d2->lat.clr = _mask_d2;
    if (c & 0x08) _port_d3->lat.set = _mask_d3; else _port_d3->lat.clr = _mask_d3;
    if (c & 0x10) _port_d4->lat.set = _mask_d4; else _port_d4->lat.clr = _mask_d4;
    if (c & 0x20) _port_d5->lat.set = _mask_d5; else _port_d5->lat.clr = _mask_d5;
    if (c & 0x40) _port_d6->lat.set = _mask_d6; else _port_d6->lat.clr = _mask_d6;
    if (c & 0x80) _port_d7->lat.set = _mask_d7; else _port_d7->lat.clr = _mask_d7;
    delayMicroseconds(10);
    _port_e->lat.set = _mask_e;
    delayMicroseconds(10);
    _port_e->lat.clr = _mask_e;
    delayMicroseconds(10);
    _port_cs->lat.clr = _mask_cs;
}

void KS0108_BB::data(uint8_t c) {
    _port_rs->lat.set = _mask_rs;
    _port_cs->lat.set = _mask_cs;
    if (c & 0x01) _port_d0->lat.set = _mask_d0; else _port_d0->lat.clr = _mask_d0;
    if (c & 0x02) _port_d1->lat.set = _mask_d1; else _port_d1->lat.clr = _mask_d1;
    if (c & 0x04) _port_d2->lat.set = _mask_d2; else _port_d2->lat.clr = _mask_d2;
    if (c & 0x08) _port_d3->lat.set = _mask_d3; else _port_d3->lat.clr = _mask_d3;
    if (c & 0x10) _port_d4->lat.set = _mask_d4; else _port_d4->lat.clr = _mask_d4;
    if (c & 0x20) _port_d5->lat.set = _mask_d5; else _port_d5->lat.clr = _mask_d5;
    if (c & 0x40) _port_d6->lat.set = _mask_d6; else _port_d6->lat.clr = _mask_d6;
    if (c & 0x80) _port_d7->lat.set = _mask_d7; else _port_d7->lat.clr = _mask_d7;
    delayMicroseconds(10);
    _port_e->lat.set = _mask_e;
    delayMicroseconds(10);
    _port_e->lat.clr = _mask_e;
    delayMicroseconds(10);
    _port_cs->lat.clr = _mask_cs;
}


