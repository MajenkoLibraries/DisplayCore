#include <BD663474.h>

inline color_t swapcolor(color_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void BD663474::command(uint16_t com) {
    _port_rs->lat.clr = _mask_rs;
    _port_cs->lat.clr = _mask_cs;
    _dspi->transfer((uint32_t)com);
    _port_cs->lat.set = _mask_cs;
}

void BD663474::data(uint16_t com) {
    _port_rs->lat.set = _mask_rs;
    _port_cs->lat.clr = _mask_cs;
    _dspi->transfer((uint32_t)com);
    _port_cs->lat.set = _mask_cs;
}

void BD663474::initializeDevice() {
    _dspi->begin();
    _dspi->setTransferSize(16);
    _dspi->setSpeed(20000000UL);
    pinMode(_pin_rs, OUTPUT);
    pinMode(_pin_cs, OUTPUT);
    pinMode(_pin_reset, OUTPUT);
    _port_cs = getPortInformation(_pin_cs, &_mask_cs);
    _port_rs = getPortInformation(_pin_rs, &_mask_rs);
    digitalWrite(_pin_rs, HIGH);
    digitalWrite(_pin_cs, HIGH);
    digitalWrite(_pin_reset, HIGH);
    delay(100);
    digitalWrite(_pin_reset, LOW);
    delay(100);
    digitalWrite(_pin_reset, HIGH);
    delay(100);
    startDisplay();
}

void BD663474::startDisplay() {
    _width  = BD663474::Width;
    _height = BD663474::Height;

    // Power
    command(0x0000); data(0x0001);

    delay(10);
    command(0x0100); data(0x0000);
    command(0x0101); data(0x0000);
    command(0x0102); data(0x3110);
    command(0x0103); data(0xE200);
    command(0x0110); data(0x009D);
    command(0x0111); data(0x0022);
    command(0x0100); data(0x0120);
    delay(20);
    command(0x0100); data(0x3120);
    delay(80);
    // Display
    command(0x0001); data(0x0100);
    command(0x0002); data(0x0000);
    command(0x0003); data(0x1230);
    command(0x0006); data(0x0000);
    command(0x0007); data(0x0101);
    command(0x0008); data(0x0808);
    command(0x0009); data(0x0000);
    command(0x000B); data(0x0000);
    command(0x000C); data(0x0000);
    command(0x000D); data(0x0018);
    // LTPS
    command(0x0012); data(0x0000);
    command(0x0013); data(0x0000);
    command(0x0018); data(0x0000);
    command(0x0019); data(0x0000);

    command(0x0203); data(0x0000);
    command(0x0204); data(0x0000);

    command(0x0210); data(0x0000);
    command(0x0211); data(0x00EF);
    command(0x0212); data(0x0000);
    command(0x0213); data(0x013F);
    command(0x0214); data(0x0000);
    command(0x0215); data(0x0000);
    command(0x0216); data(0x0000);
    command(0x0217); data(0x0000);

    // Grey scale
    command(0x0300); data(0x5343);
    command(0x0301); data(0x1021);
    command(0x0302); data(0x0003);
    command(0x0303); data(0x0011);
    command(0x0304); data(0x050A);
    command(0x0305); data(0x4342);
    command(0x0306); data(0x1100);
    command(0x0307); data(0x0003);
    command(0x0308); data(0x1201);
    command(0x0309); data(0x050A);

    // RAM access
    command(0x0400); data(0x4027);
    command(0x0401); data(0x0000);
    command(0x0402); data(0x0000);
    command(0x0403); data(0x013F);
    command(0x0404); data(0x0000);

    command(0x0200); data(0x0000);
    command(0x0201); data(0x0000);

    command(0x0100); data(0x7120);
    command(0x0007); data(0x0103);
    delay(10);
    command(0x0007); data(0x0113);
}

void BD663474::setAddrWindow(int x0, int y0, int x1, int y1) {

    int x0a, x1a, y0a, y1a;

    switch(rotation) {
        case 1:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
  
            x0 = y0a;
            x1 = y1a;
            y0 = _width - x1a;
            y1 = _width - x0a;
            break;
        case 2:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
        
            x0 = _width - x1a;
            x1 = _width - x0a;
            y0 = _height - y1a;
            y1 = _height - y0a;
            break;
  

        case 3:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;

            x0 = _height - y1a;
            x1 = _height - y0a;
            y0 = x0a;
            y1 = x1a;
            break;
    }

//    x1 -= 1;
//    y1 += 3;
    command(0x0210); data(x0);
    command(0x0211); data(x1);
    command(0x0212); data(y0);
    command(0x0213); data(y1);
    command(0x0200); data(x0);
    command(0x0201); data(y0);
    command(0x0202);
}

void BD663474::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    fillRectangle(x, y, 1, 1, color);

//    _comm->streamStart();
//	setAddrWindow(x,y,x+1,y+1);
//    command(0x0202);
//	data(color);
//    _comm->streamEnd();
}

void BD663474::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void BD663474::fillRectangle(int x, int y, int w, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;

	setAddrWindow(x, y, x+w-1, y+h-1);
	for(uint32_t y = 0; y < h; y++) {
        for(uint32_t x = 0; x < w; x++) {
            data(color);
		}
	}
}

void BD663474::drawHorizontalLine(int x, int y, int w, color_t color) {
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

void BD663474::drawVerticalLine(int x, int y, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;

	setAddrWindow(x, y, x, y+h-1);
	while (h--) {
		data(color);
	}
}

#define BD663474_EMODE 0x0003

#define BD663474_TRI 0x8000
#define BD663474_DFM 0x4000
#define BD663474_BGR 0x1000
#define BD663474_HWM 0x0200
#define BD663474_ORG 0x0080
#define BD663474_ID0 0x0000
#define BD663474_ID1 0x0010
#define BD663474_ID2 0x0020
#define BD663474_ID3 0x0030
#define BD663474_AM  0x0008

void BD663474::setRotation(int m) {
	rotation = m % 4; // can't be higher than 3
    command(BD663474_EMODE);
	switch (rotation) {
		case 0:
            data(BD663474_BGR | BD663474_ORG | BD663474_ID3);
			_width  = BD663474::Width;
			_height = BD663474::Height;
			break;
		case 1:
            data(BD663474_BGR | BD663474_ORG | BD663474_ID1 | BD663474_AM); 
			_width  = BD663474::Height;
			_height = BD663474::Width;
			break;
		case 2:
            data(BD663474_BGR | BD663474_ORG | BD663474_ID0);
			_width  = BD663474::Width;
			_height = BD663474::Height;
			break;
		case 3:
            data(BD663474_BGR | BD663474_ORG | BD663474_ID2 | BD663474_AM);
			_width  = BD663474::Height;
			_height = BD663474::Width;
			break;
	}

}

void BD663474::invertDisplay(boolean i) {
//	_comm->writeCommand(i ? BD663474_INVON : BD663474_INVOFF);
}

