#include <ILI9340.h>

#define ILI9340_NOP     0x00
#define ILI9340_SWRESET 0x01
#define ILI9340_RDDID   0x04
#define ILI9340_RDDST   0x09

#define ILI9340_SLPIN   0x10
#define ILI9340_SLPOUT  0x11
#define ILI9340_PTLON   0x12
#define ILI9340_NORON   0x13

#define ILI9340_RDMODE 0x0A
#define ILI9340_RDMADCTL 0x0B
#define ILI9340_RDPIXFMT 0x0C
#define ILI9340_RDIMGFMT 0x0A
#define ILI9340_RDSELFDIAG 0x0F

#define ILI9340_INVOFF 0x20
#define ILI9340_INVON 0x21
#define ILI9340_GAMMASET 0x26
#define ILI9340_DISPOFF 0x28
#define ILI9340_DISPON 0x29

#define ILI9340_CASET 0x2A
#define ILI9340_PASET 0x2B
#define ILI9340_RAMWR 0x2C
#define ILI9340_RAMRD 0x2E

#define ILI9340_PTLAR 0x30
#define ILI9340_MADCTL 0x36


#define ILI9340_MADCTL_MY 0x80
#define ILI9340_MADCTL_MX 0x40
#define ILI9340_MADCTL_MV 0x20
#define ILI9340_MADCTL_ML 0x10
#define ILI9340_MADCTL_RGB 0x00
#define ILI9340_MADCTL_BGR 0x08
#define ILI9340_MADCTL_MH 0x04

#define ILI9340_PIXFMT 0x3A

#define ILI9340_FRMCTR1 0xB1
#define ILI9340_FRMCTR2 0xB2
#define ILI9340_FRMCTR3 0xB3
#define ILI9340_INVCTR 0xB4
#define ILI9340_DFUNCTR 0xB6

#define ILI9340_PWCTR1 0xC0
#define ILI9340_PWCTR2 0xC1
#define ILI9340_PWCTR3 0xC2
#define ILI9340_PWCTR4 0xC3
#define ILI9340_PWCTR5 0xC4
#define ILI9340_VMCTR1 0xC5
#define ILI9340_VMCTR2 0xC7

#define ILI9340_RDID1 0xDA
#define ILI9340_RDID2 0xDB
#define ILI9340_RDID3 0xDC
#define ILI9340_RDID4 0xDD

#define ILI9340_GMCTRP1 0xE0
#define ILI9340_GMCTRN1 0xE1

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

void ILI9340::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
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

void ILI9340::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color >> 8);
    data(color & 0xFF);
}

void ILI9340::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9340::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
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

void ILI9340::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
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

void ILI9340::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
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

void ILI9340::setRotation(uint8_t m) {
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

void ILI9340::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9340::windowData(uint16_t c) {
    data(c >> 8);
    data(c & 0xFF);
}

void ILI9340::windowData(uint16_t *c, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i] >> 8);
        data(c[i] & 0xFF);
    }
}

void ILI9340::closeWindow() {
}
