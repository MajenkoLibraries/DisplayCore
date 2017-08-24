
#include <HX8347D.h>

void HX8347D::writeCommand(uint8_t c) {
    _spi->setSpeed(20000000UL);
    _dc_port->lat.clr = _dc_mask;
    _cs_port->lat.clr = _cs_mask;
    _spi->transfer(c);
    _cs_port->lat.set = _cs_mask;
}

void HX8347D::writeData(uint8_t c) {
    _spi->setSpeed(20000000UL);
    _dc_port->lat.set = _dc_mask;
    _cs_port->lat.clr = _cs_mask;
    _spi->transfer(c);
    _cs_port->lat.set = _cs_mask;
}

void HX8347D::setRegister(uint8_t reg, uint8_t val) {
    writeCommand(reg);
    writeData(val);
}

void HX8347D::initializeDevice() 
{
    _dc_port = getPortInformation(_dc, &_dc_mask);
    _cs_port = getPortInformation(_cs, &_cs_mask);

    _spi->begin();
    _spi->setSpeed(20000000UL);

    pinMode(_dc, OUTPUT);
    pinMode(_cs, OUTPUT);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, HIGH);

    _width  = HX8347D::Width;
    _height = HX8347D::Height;

    
    //Driving ability Setting

    setRegister(0xEA,0x00); //PTBA[15:8]
    setRegister(0xEB,0x20); //PTBA[7:0]
    setRegister(0xEC,0x0C); //STBA[15:8]
    setRegister(0xED,0xC4); //STBA[7:0]
    setRegister(0xE8,0x38); //OPON[7:0]
    setRegister(0xE9,0x10); //OPON1[7:0]
    setRegister(0xF1,0x01); //OTPS1B
    setRegister(0xF2,0x10); //GEN
    //Gamma 2.2 Setting
    setRegister(0x40,0x01); //
    setRegister(0x41,0x00); //
    setRegister(0x42,0x00); //
    setRegister(0x43,0x10); //
    setRegister(0x44,0x0E); //
    setRegister(0x45,0x24); //
    setRegister(0x46,0x04); //
    setRegister(0x47,0x50); //
    setRegister(0x48,0x02); //
    setRegister(0x49,0x13); //
    setRegister(0x4A,0x19); //
    setRegister(0x4B,0x19); //
    setRegister(0x4C,0x16); //
    setRegister(0x50,0x1B); //
    setRegister(0x51,0x31); //
    setRegister(0x52,0x2F); //
    setRegister(0x53,0x3F); //
    setRegister(0x54,0x3F); //
    setRegister(0x55,0x3E); //
    setRegister(0x56,0x2F); //
    setRegister(0x57,0x7B); //
    setRegister(0x58,0x09); //
    setRegister(0x59,0x06); //
    setRegister(0x5A,0x06); //
    setRegister(0x5B,0x0C); //
    setRegister(0x5C,0x1D); //
    setRegister(0x5D,0xCC); //
    //Power Voltage Setting
    setRegister(0x1B,0x1B); //VRH=4.65V
    setRegister(0x1A,0x01); //BT (VGH~15V,VGL~-10V,DDVDH~5V)
    setRegister(0x24,0x2F); //VMH(VCOM High voltage ~3.2V)
    setRegister(0x25,0x57); //VML(VCOM Low voltage -1.2V)

    setRegister(0x23,0x88); //for Flicker adjust //can reload from OTP
    //Power on Setting
    setRegister(0x18,0x34); //I/P_RADJ,N/P_RADJ, Normal mode 60Hz
    setRegister(0x19,0x01); //OSC_EN='1', start Osc
    setRegister(0x01,0x00); //DP_STB='0', out deep sleep
    setRegister(0x1F,0x88);// GAS=1, VOMG=00, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=0
    delay(5);
    setRegister(0x1F,0x80);// GAS=1, VOMG=00, PON=0, DK=0, XDK=0, DVDH_TRI=0, STB=0
    delay(5);
    setRegister(0x1F,0x90);// GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
    delay(5);
    setRegister(0x1F,0xD0);// GAS=1, VOMG=10, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
    delay(5);
    //262k/65k color selection
    setRegister(0x17,0x05); //default 0x06 262k color // 0x05 65k color
    //SET PANEL
    setRegister(0x36,0x00); //SS_P, GS_P,REV_P,BGR_P
    //Display ON Setting
    setRegister(0x28,0x38); //GON=1, DTE=1, D=1000
    delay(40);
    setRegister(0x28,0x3F); //GON=1, DTE=1, D=1100
    setRegister(0x16,0x18); 
    //Set GRAM Area
    setRegister(0x02,0x00);
    setRegister(0x03,0x00); //Column Start
    setRegister(0x04,0x00);
    setRegister(0x05,0xEF); //Column End
    setRegister(0x06,0x00);
    setRegister(0x07,0x00); //Row Start
    setRegister(0x08,0x01);
    setRegister(0x09,0x3F); //Row End

    clearClipping();
}

void HX8347D::setAddrWindow(int x0, int y0, int x1, int y1) 
{
    // Column start
    setRegister(0x02, x0 >> 8);
    setRegister(0x03, x0 & 0xFF);

    // Column end
    setRegister(0x04, x1 >> 8);
    setRegister(0x05, x1 & 0xFF);

    // Row start
    setRegister(0x06, y0 >> 8);
    setRegister(0x07, y0 & 0xFF);

    // Row end
    setRegister(0x08, y1 >> 8);
    setRegister(0x09, y1 & 0xFF);

    writeCommand(0x22);
}

void HX8347D::setPixel(int x, int y, color_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
    if ((x < _clip_x0) || (x > _clip_x1) || (y < _clip_y0) || (y > _clip_y1)) 
        return;
    openWindow(x, y, 1, 1);
    windowData(color);
    closeWindow();
}

void HX8347D::fillScreen(color_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
}

void HX8347D::fillRectangle(int x, int y, int w, int h, color_t color) 
{
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
    openWindow(x, y, w, h);
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            windowData(color);
		}
	}
    closeWindow();
}

void HX8347D::drawHorizontalLine(int x, int y, int w, color_t color) 
{
    int h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
    openWindow(x, y, w, 1);
	while (w--) {
		windowData(color);
	}
    closeWindow();
}

void HX8347D::drawVerticalLine(int x, int y, int h, color_t color) 
{
    int w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
    openWindow(x, y, 1, h);
	while (h--) {
        windowData(color);
	}
    closeWindow();
}

void HX8347D::setRotation(int m) 
{
// 0x80 = up/down flip
// 0x40 = left/right flip
// 0x20 = portrait/landscape
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			//PORTRAIT
            setRegister(0x16, 0x18);
			_width  = HX8347D::Width;
			_height = HX8347D::Height;
			break;
		case 1:
		    //LANDSCAPE
            setRegister(0x16, 0x18 | 0x40 | 0x20);
			_width  = HX8347D::Height;
			_height = HX8347D::Width;
			break;
		case 2:	
			//UPSIDE DOWN PORTRAIT
            setRegister(0x16, 0x18 | 0x80 | 0x40);
			_width  = HX8347D::Width;
			_height = HX8347D::Height;
			break;
		case 3:
			//UPSIDE DOWN LANDSCAPE
            setRegister(0x16, 0x18 | 0x80 | 0x20);
			_width  = HX8347D::Height;
			_height = HX8347D::Width;
			break;
	}
    clearClipping();
}

void HX8347D::invertDisplay(boolean i) 
{
    setRegister(0x01,i ? 0x02 : 0x00);
}

void HX8347D::displayOn() 
{
    setRegister(0x01,0x00);
}

void HX8347D::displayOff() 
{
    setRegister(0x01,0xC0);
}

void HX8347D::openWindow(int x0, int y0, int x1, int y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
    _cs_port->lat.clr = _cs_mask;
    _dc_port->lat.set = _dc_mask;
}

void HX8347D::windowData(color_t d) {
    _spi->setSpeed(20000000UL);
    _spi->transfer((uint8_t)(d >> 8));
    _spi->transfer((uint8_t)(d & 0xFF));
}

void HX8347D::windowData(color_t *d, uint32_t l) {
    _spi->setSpeed(20000000UL);
    for (uint32_t i = 0; i < l; i++) {
        _spi->transfer((uint8_t)(d[i] >> 8));
        _spi->transfer((uint8_t)(d[i] & 0xFF));
    }
}

void HX8347D::closeWindow() {
    _cs_port->lat.set = _cs_mask;
}
