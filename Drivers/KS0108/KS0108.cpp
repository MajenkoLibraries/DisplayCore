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

    PMMODEbits.MODE16 = 0;  // 8-bit mode
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

void KS0108::setPixel(int16_t x, int16_t y, uint16_t color) {
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

uint16_t KS0108::getWidth() { return 64; }
uint16_t KS0108::getHeight() { return 64; }

void KS0108_2::initializeDevice() {
    _lcd1.initializeDevice();
    _lcd2.initializeDevice();
}

void KS0108_2::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x >= 64) {
        _lcd2.setPixel(x-64, y, color);
    } else {
        _lcd1.setPixel(x, y, color);
    }
}

void KS0108_2::startBuffer() {
    _lcd1.startBuffer();
    _lcd2.startBuffer();
}

void KS0108_2::endBuffer() {
    _lcd1.endBuffer();
    _lcd2.endBuffer();
}

uint16_t KS0108_2::getWidth() { return 128; }
uint16_t KS0108_2::getHeight() { return 64; }
