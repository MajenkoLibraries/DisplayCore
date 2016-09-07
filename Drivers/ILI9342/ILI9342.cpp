#include <ILI9342.h>

void ILI9342::command(uint16_t cmd) {
    _rs_port->lat.clr = _rs_mask;
    _cs_port->lat.clr = _cs_mask;

    if (cmd & 0x01) _d0_port->lat.set = _d0_mask; else _d0_port->lat.clr = _d0_mask;
    if (cmd & 0x02) _d1_port->lat.set = _d1_mask; else _d1_port->lat.clr = _d1_mask;
    if (cmd & 0x04) _d2_port->lat.set = _d2_mask; else _d2_port->lat.clr = _d2_mask;
    if (cmd & 0x08) _d3_port->lat.set = _d3_mask; else _d3_port->lat.clr = _d3_mask;
    if (cmd & 0x10) _d4_port->lat.set = _d4_mask; else _d4_port->lat.clr = _d4_mask;
    if (cmd & 0x20) _d5_port->lat.set = _d5_mask; else _d5_port->lat.clr = _d5_mask;
    if (cmd & 0x40) _d6_port->lat.set = _d6_mask; else _d6_port->lat.clr = _d6_mask;
    if (cmd & 0x80) _d7_port->lat.set = _d7_mask; else _d7_port->lat.clr = _d7_mask;
    if (_d8_port != NULL) {
        if (cmd & 0x0100) _d8_port->lat.set = _d8_mask; else _d8_port->lat.clr = _d8_mask;
        if (cmd & 0x0200) _d9_port->lat.set = _d9_mask; else _d9_port->lat.clr = _d9_mask;
        if (cmd & 0x0400) _d10_port->lat.set = _d10_mask; else _d10_port->lat.clr = _d10_mask;
        if (cmd & 0x0800) _d11_port->lat.set = _d11_mask; else _d11_port->lat.clr = _d11_mask;
        if (cmd & 0x1000) _d12_port->lat.set = _d12_mask; else _d12_port->lat.clr = _d12_mask;
        if (cmd & 0x2000) _d13_port->lat.set = _d13_mask; else _d13_port->lat.clr = _d13_mask;
        if (cmd & 0x4000) _d14_port->lat.set = _d14_mask; else _d14_port->lat.clr = _d14_mask;
        if (cmd & 0x8000) _d15_port->lat.set = _d15_mask; else _d15_port->lat.clr = _d15_mask;
    }

    //delayMicroseconds(1);
    _wr_port->lat.clr = _wr_mask;
    //delayMicroseconds(1);
    _wr_port->lat.set = _wr_mask;
    //delayMicroseconds(1);

    _cs_port->lat.set = _cs_mask;
}

void ILI9342::data(uint16_t dat) {
    _rs_port->lat.set = _rs_mask;
    _cs_port->lat.clr = _cs_mask;

    if (dat & 0x01) _d0_port->lat.set = _d0_mask; else _d0_port->lat.clr = _d0_mask;
    if (dat & 0x02) _d1_port->lat.set = _d1_mask; else _d1_port->lat.clr = _d1_mask;
    if (dat & 0x04) _d2_port->lat.set = _d2_mask; else _d2_port->lat.clr = _d2_mask;
    if (dat & 0x08) _d3_port->lat.set = _d3_mask; else _d3_port->lat.clr = _d3_mask;
    if (dat & 0x10) _d4_port->lat.set = _d4_mask; else _d4_port->lat.clr = _d4_mask;
    if (dat & 0x20) _d5_port->lat.set = _d5_mask; else _d5_port->lat.clr = _d5_mask;
    if (dat & 0x40) _d6_port->lat.set = _d6_mask; else _d6_port->lat.clr = _d6_mask;
    if (dat & 0x80) _d7_port->lat.set = _d7_mask; else _d7_port->lat.clr = _d7_mask;
    if (_d8_port != NULL) {
        if (dat & 0x0100) _d8_port->lat.set = _d8_mask; else _d8_port->lat.clr = _d8_mask;
        if (dat & 0x0200) _d9_port->lat.set = _d9_mask; else _d9_port->lat.clr = _d9_mask;
        if (dat & 0x0400) _d10_port->lat.set = _d10_mask; else _d10_port->lat.clr = _d10_mask;
        if (dat & 0x0800) _d11_port->lat.set = _d11_mask; else _d11_port->lat.clr = _d11_mask;
        if (dat & 0x1000) _d12_port->lat.set = _d12_mask; else _d12_port->lat.clr = _d12_mask;
        if (dat & 0x2000) _d13_port->lat.set = _d13_mask; else _d13_port->lat.clr = _d13_mask;
        if (dat & 0x4000) _d14_port->lat.set = _d14_mask; else _d14_port->lat.clr = _d14_mask;
        if (dat & 0x8000) _d15_port->lat.set = _d15_mask; else _d15_port->lat.clr = _d15_mask;
    }

    //delayMicroseconds(1);
    _wr_port->lat.clr = _wr_mask;
    //delayMicroseconds(1);
    _wr_port->lat.set = _wr_mask;
    //delayMicroseconds(1);

    _cs_port->lat.set = _cs_mask;
}

void ILI9342::initializeDevice() {
    if (_cs_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_rs_pin >= NUM_DIGITAL_PINS_EXTENDED) return; 
    if (_wr_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_rd_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_reset_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d0_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d1_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d2_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d3_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d4_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d5_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d6_pin >= NUM_DIGITAL_PINS_EXTENDED) return;
    if (_d7_pin >= NUM_DIGITAL_PINS_EXTENDED) return;

    pinMode(_cs_pin, OUTPUT);
    pinMode(_rs_pin, OUTPUT);
    pinMode(_wr_pin, OUTPUT);
    pinMode(_rd_pin, OUTPUT);
    pinMode(_reset_pin, OUTPUT);
    pinMode(_d0_pin, OUTPUT);
    pinMode(_d1_pin, OUTPUT);
    pinMode(_d2_pin, OUTPUT);
    pinMode(_d3_pin, OUTPUT);
    pinMode(_d4_pin, OUTPUT);
    pinMode(_d5_pin, OUTPUT);
    pinMode(_d6_pin, OUTPUT);
    pinMode(_d7_pin, OUTPUT);

    _cs_port = getPortInformation(_cs_pin, &_cs_mask);
    _rs_port = getPortInformation(_rs_pin, &_rs_mask);
    _wr_port = getPortInformation(_wr_pin, &_wr_mask);
    _rd_port = getPortInformation(_rd_pin, &_rd_mask);
    _d0_port = getPortInformation(_d0_pin, &_d0_mask);
    _d1_port = getPortInformation(_d1_pin, &_d1_mask);
    _d2_port = getPortInformation(_d2_pin, &_d2_mask);
    _d3_port = getPortInformation(_d3_pin, &_d3_mask);
    _d4_port = getPortInformation(_d4_pin, &_d4_mask);
    _d5_port = getPortInformation(_d5_pin, &_d5_mask);
    _d6_port = getPortInformation(_d6_pin, &_d6_mask);
    _d7_port = getPortInformation(_d7_pin, &_d7_mask);

    if (_d8_pin <= NUM_DIGITAL_PINS_EXTENDED) {
        pinMode(_d8_pin, OUTPUT);
        pinMode(_d9_pin, OUTPUT);
        pinMode(_d10_pin, OUTPUT);
        pinMode(_d11_pin, OUTPUT);
        pinMode(_d12_pin, OUTPUT);
        pinMode(_d13_pin, OUTPUT);
        pinMode(_d14_pin, OUTPUT);
        pinMode(_d15_pin, OUTPUT);
        _d8_port = getPortInformation(_d8_pin, &_d8_mask);
        _d9_port = getPortInformation(_d9_pin, &_d9_mask);
        _d10_port = getPortInformation(_d10_pin, &_d10_mask);
        _d11_port = getPortInformation(_d11_pin, &_d11_mask);
        _d12_port = getPortInformation(_d12_pin, &_d12_mask);
        _d13_port = getPortInformation(_d13_pin, &_d13_mask);
        _d14_port = getPortInformation(_d14_pin, &_d14_mask);
        _d15_port = getPortInformation(_d15_pin, &_d15_mask);
    } else {
        _d8_port = NULL;
        _d9_port = NULL;
        _d10_port = NULL;
        _d11_port = NULL;
        _d12_port = NULL;
        _d13_port = NULL;
        _d14_port = NULL;
        _d15_port = NULL;
    }


    _width  = ILI9342::Width;
    _height = ILI9342::Height;

    digitalWrite(_cs_pin, HIGH);
    digitalWrite(_rs_pin, HIGH);
    digitalWrite(_wr_pin, HIGH);
    digitalWrite(_rd_pin, HIGH);

    digitalWrite(_reset_pin, HIGH);
    delay(10);
    digitalWrite(_reset_pin, LOW);
    delay(10);
    digitalWrite(_reset_pin, HIGH);
    delay(10);

    configureScreen();
}

void ILI9342::setAddrWindow(int x0, int y0, int x1, int y1) {
    command(0x2a);   
    data(x0 >> 8);
    data(x0 & 0xff);
    data(x1 >> 8);
    data(x1 & 0xff);

    command(0x2b);   
    data(y0 >> 8);
    data(y0 & 0xff);
    data(y1 >> 8);
    data(y1 & 0xff);
    
    command(0x2c);
}

void ILI9342::setPixel(int x, int y, color_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    data(color);
}

void ILI9342::fillScreen(color_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9342::fillRectangle(int x, int y, int w, int h, color_t color) {
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

void ILI9342::drawHorizontalLine(int x, int y, int w, color_t color) {
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

void ILI9342::drawVerticalLine(int x, int y, int h, color_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        data(color);
	}
}

void ILI9342::setRotation(int m) {
	command(ILI9342_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			data(ILI9342_MADCTL_MX | ILI9342_MADCTL_BGR);
			_width  = ILI9342::Width;
			_height = ILI9342::Height;
			break;
		case 1:
		    data(ILI9342_MADCTL_MV | ILI9342_MADCTL_BGR);
			_width  = ILI9342::Height;
			_height = ILI9342::Width;
			break;
		case 2:
			data(ILI9342_MADCTL_MY | ILI9342_MADCTL_BGR);
			_width  = ILI9342::Width;
			_height = ILI9342::Height;
			break;
		case 3:
			data(ILI9342_MADCTL_MV | ILI9342_MADCTL_MY | ILI9342_MADCTL_MX | ILI9342_MADCTL_BGR);
			_width  = ILI9342::Height;
			_height = ILI9342::Width;
			break;
	}
}

void ILI9342::invertDisplay(boolean i) {
	command(i ? ILI9342_INVERTON : ILI9342_INVERTOFF);
}

void ILI9342::openWindow(int x0, int y0, int x1, int y1) {
	setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void ILI9342::windowData(color_t c) {
    data(c);
}

void ILI9342::windowData(color_t *c, int len) {
    for (uint32_t i = 0; i < len; i++) {
        data(c[i]);
    }
}

void ILI9342::closeWindow() {
}

ILI9342_PMP::ILI9342_PMP(uint8_t c, uint8_t r) {
    _reset_pin = r;
    _cs_pin = c;
}

void ILI9342_PMP::command(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0000;
    PMDIN = c;
}

void ILI9342_PMP::data(uint16_t d) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0001;
    PMDIN = d;
}

void ILI9342_PMP::initializeDevice() {
    PMCONbits.ON = 0;
    asm volatile("nop");

    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;
    PMCONbits.CSF = 0;

    PMAEN = 0x0001; // Enable PMA0 pin for RS pin and CS1 as CS

    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 0x0;
    PMMODEbits.WAITM = 0x0;
    PMMODEbits.WAITE = 0x0;

    //PMADDR = 0; // Set current address to 0
    PMADDR = 0x0000; // Set current address to 0, CS1 Active

    PMCONbits.ON = 1;

    pinMode(_cs_pin, OUTPUT);
    pinMode(_reset_pin, OUTPUT);

    digitalWrite(_cs_pin, HIGH);
    digitalWrite(_reset_pin, HIGH);
    delay(10);
    digitalWrite(_cs_pin, LOW);
    digitalWrite(_reset_pin, LOW);
    delay(10);
    digitalWrite(_reset_pin, HIGH);
    delay(10);

    _width  = ILI9342::Width;
    _height = ILI9342::Height;

    configureScreen();
}

void ILI9342::configureScreen() {
    delay(100);

    command(0x01);
    delay(10);


    command(0xc8);
    data(0xFF);
    data(0x93);
    data(0x42); 
 
    
    command(0x36);       //Memory Access Control
    data(0xc8);//MY,MX,MV,ML,BGR,MH
    

    command(0x3A);       //Pixel Format Set
    data(0x55);//DPI [2:0],DBI [2:0]

    command(0xC0);  // Power control
    data(0x10);     // Iffy
    data(0x10);     // Plain wrong?
    
    command(0xC1);
    data(0x36);
        
    command(0xC5);     //VCOM
    data(0xC3);
                              

    command(0xE0);    //Set Gamma 
    data(0x00); 
    data(0x05); 
    data(0x08); 
    data(0x02); 
    data(0x1A); 
    data(0x0C); 
    data(0x42); 
    data(0X7A); 
    data(0x54); 
    data(0x08); 
    data(0x0D); 
    data(0x0C); 
    data(0x23); 
    data(0x25); 
    data(0x0F); 
      
    command(0XE1);    //Set Gamma 
    data(0x00); 
    data(0x29); 
    data(0x2F); 
    data(0x03); 
    data(0x0F); 
    data(0x05); 
    data(0x42); 
    data(0x55); 
    data(0x53); 
    data(0x06); 
    data(0x0F); 
    data(0x0C); 
    data(0x38); 
    data(0x3A); 
    data(0x0F);  

    command(0x11);//Exit Sleep
    delay(120);
    command(0x29);//Display On  

}

void ILI9342_PMP::windowData(color_t *d, int l) {
    uint32_t toXfer = l * 2;

    uint16_t *data = d;

    while (toXfer > 0) {
        while (DCH3CONbits.CHBUSY);
        uint32_t chunk = toXfer;
        if (chunk > 65534) {
            chunk = 65534;
        }

        toXfer -= chunk;

        PMMODEbits.IRQM = 0b01;

        DCH3INTbits.CHSDIE = 1;
        DCH3SSA = ((uint32_t)data) & 0x1FFFFFFF;
        DCH3DSA = ((uint32_t)&PMDIN) & 0x1FFFFFFF;
        DCH3SSIZ = chunk;
        DCH3DSIZ = 2;
        DCH3CSIZ = 2;
        DCH3ECONbits.SIRQEN = 1;
        DCH3ECONbits.CHSIRQ = _PMP_IRQ;
        DCH3CONbits.CHAEN = 0;
        DCH3CONbits.CHEN = 1;

        DMACONbits.ON=1;

        DCH3ECONbits.CFORCE = 1;
        data += (chunk >> 1);
    }
}

void ILI9342_PMP::closeWindow() {
    if (DCH3CONbits.CHEN == 1) {
        while (DCH3CONbits.CHBUSY);
        DCH3CONbits.CHEN = 0;
    }
}

