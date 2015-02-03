#include <SSD1963_7.h>

const uint16_t   HDP=799;
const uint16_t   HT=928;
const uint16_t   HPS=46;
const uint16_t   LPS=15;
const uint8_t    HPW=48;

const uint16_t   VDP=479;
const uint16_t   VT=525;
const uint16_t   VPS=16;
const uint16_t   FPS=8;
const uint8_t    VPW=16;

SSD1963_7::SSD1963_7(
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
    uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
    uint8_t cs, uint8_t rs, uint8_t wr, uint8_t rd
) {
    pins[_PIN_D0] = d0;
    pins[_PIN_D1] = d1;
    pins[_PIN_D2] = d2;
    pins[_PIN_D3] = d3;
    pins[_PIN_D4] = d4;
    pins[_PIN_D5] = d5;
    pins[_PIN_D6] = d6;
    pins[_PIN_D7] = d7;
    pins[_PIN_D8] = d8;
    pins[_PIN_D9] = d9;
    pins[_PIN_D10] = d10;
    pins[_PIN_D11] = d11;
    pins[_PIN_D12] = d12;
    pins[_PIN_D13] = d13;
    pins[_PIN_D14] = d14;
    pins[_PIN_D15] = d15;
    pins[_PIN_CS] = cs;
    pins[_PIN_RS] = rs;
    pins[_PIN_WR] = wr;
    pins[_PIN_RD] = rd;
}

void SSD1963_7::initializeDevice() {
    uint32_t port = 0;

    if (pins[_PIN_D0] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D0], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D0]);
    if (port == NOT_A_PIN) { return; }
    _port_d0 = (p32_ioport *)portRegisters(port);
    _mask_d0 = digitalPinToBitMask(pins[_PIN_D0]);

    if (pins[_PIN_D1] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D1], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D1]);
    if (port == NOT_A_PIN) { return; }
    _port_d1 = (p32_ioport *)portRegisters(port);
    _mask_d1 = digitalPinToBitMask(pins[_PIN_D1]);

    if (pins[_PIN_D2] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D2], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D2]);
    if (port == NOT_A_PIN) { return; }
    _port_d2 = (p32_ioport *)portRegisters(port);
    _mask_d2 = digitalPinToBitMask(pins[_PIN_D2]);

    if (pins[_PIN_D3] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D3], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D3]);
    if (port == NOT_A_PIN) { return; }
    _port_d3 = (p32_ioport *)portRegisters(port);
    _mask_d3 = digitalPinToBitMask(pins[_PIN_D3]);

    if (pins[_PIN_D4] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D4], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D4]);
    if (port == NOT_A_PIN) { return; }
    _port_d4 = (p32_ioport *)portRegisters(port);
    _mask_d4 = digitalPinToBitMask(pins[_PIN_D4]);

    if (pins[_PIN_D5] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D5], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D5]);
    if (port == NOT_A_PIN) { return; }
    _port_d5 = (p32_ioport *)portRegisters(port);
    _mask_d5 = digitalPinToBitMask(pins[_PIN_D5]);

    if (pins[_PIN_D6] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D6], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D6]);
    if (port == NOT_A_PIN) { return; }
    _port_d6 = (p32_ioport *)portRegisters(port);
    _mask_d6 = digitalPinToBitMask(pins[_PIN_D6]);

    if (pins[_PIN_D7] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D7], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D7]);
    if (port == NOT_A_PIN) { return; }
    _port_d7 = (p32_ioport *)portRegisters(port);
    _mask_d7 = digitalPinToBitMask(pins[_PIN_D7]);

    if (pins[_PIN_D8] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D8], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D8]);
    if (port == NOT_A_PIN) { return; }
    _port_d8 = (p32_ioport *)portRegisters(port);
    _mask_d8 = digitalPinToBitMask(pins[_PIN_D8]);

    if (pins[_PIN_D9] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D9], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D9]);
    if (port == NOT_A_PIN) { return; }
    _port_d9 = (p32_ioport *)portRegisters(port);
    _mask_d9 = digitalPinToBitMask(pins[_PIN_D9]);

    if (pins[_PIN_D10] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D10], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D10]);
    if (port == NOT_A_PIN) { return; }
    _port_d10 = (p32_ioport *)portRegisters(port);
    _mask_d10 = digitalPinToBitMask(pins[_PIN_D10]);

    if (pins[_PIN_D11] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D11], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D11]);
    if (port == NOT_A_PIN) { return; }
    _port_d11 = (p32_ioport *)portRegisters(port);
    _mask_d11 = digitalPinToBitMask(pins[_PIN_D11]);

    if (pins[_PIN_D12] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D12], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D12]);
    if (port == NOT_A_PIN) { return; }
    _port_d12 = (p32_ioport *)portRegisters(port);
    _mask_d12 = digitalPinToBitMask(pins[_PIN_D12]);

    if (pins[_PIN_D13] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D13], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D13]);
    if (port == NOT_A_PIN) { return; }
    _port_d13 = (p32_ioport *)portRegisters(port);
    _mask_d13 = digitalPinToBitMask(pins[_PIN_D13]);

    if (pins[_PIN_D14] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D14], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D14]);
    if (port == NOT_A_PIN) { return; }
    _port_d14 = (p32_ioport *)portRegisters(port);
    _mask_d14 = digitalPinToBitMask(pins[_PIN_D14]);

    if (pins[_PIN_D15] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_D15], OUTPUT);
    port = digitalPinToPort(pins[_PIN_D15]);
    if (port == NOT_A_PIN) { return; }
    _port_d15 = (p32_ioport *)portRegisters(port);
    _mask_d15 = digitalPinToBitMask(pins[_PIN_D15]);

    if (pins[_PIN_CS] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_CS], OUTPUT);
    port = digitalPinToPort(pins[_PIN_CS]);
    if (port == NOT_A_PIN) { return; }
    _port_cs = (p32_ioport *)portRegisters(port);
    _mask_cs = digitalPinToBitMask(pins[_PIN_CS]);

    if (pins[_PIN_RS] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_RS], OUTPUT);
    port = digitalPinToPort(pins[_PIN_RS]);
    if (port == NOT_A_PIN) { return; }
    _port_rs = (p32_ioport *)portRegisters(port);
    _mask_rs = digitalPinToBitMask(pins[_PIN_RS]);

    if (pins[_PIN_WR] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_WR], OUTPUT);
    port = digitalPinToPort(pins[_PIN_WR]);
    if (port == NOT_A_PIN) { return; }
    _port_wr = (p32_ioport *)portRegisters(port);
    _mask_wr = digitalPinToBitMask(pins[_PIN_WR]);

    if (pins[_PIN_RD] >= NUM_DIGITAL_PINS_EXTENDED) { return; }
    pinMode(pins[_PIN_RD], OUTPUT);
    port = digitalPinToPort(pins[_PIN_RD]);
    if (port == NOT_A_PIN) { return; }
    _port_rd = (p32_ioport *)portRegisters(port);
    _mask_rd = digitalPinToBitMask(pins[_PIN_RD]);

    _port_cs->lat.clr = _mask_cs;
    _port_rd->lat.set = _mask_rd;
    _port_wr->lat.set = _mask_wr;

    _width  = SSD1963_7::Width;
    _height = SSD1963_7::Height;

    command(SSD1963_SetPLLMN);
    data(0x0023);        //N=0x36 for 6.5M, 0x23 for 10M crystal
    data(0x0002);
    data(0x0004);
    command(SSD1963_SetPLL);  // PLL enable
    data(0x0001);
    delay(1);
    command(SSD1963_SetPLL);
    data(0x0003);
    delay(5);
    command(SSD1963_SoftReset);  // software reset
    delay(5);
    command(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
    data(0x0003);
    data(0x00ff);
    data(0x00ff);

    command(SSD1963_SetLCDMode);
    data(0x0000);
    data(0x0000);
    data((HDP>>8)&0X00FF);  //Set HDP
    data(HDP&0X00FF);
    data((VDP>>8)&0X00FF);  //Set VDP
    data(VDP&0X00FF);
    data(0x0000);

    command(SSD1963_SetHoriPeriod);
    data((HT>>8)&0X00FF);  //Set HT
    data(HT&0X00FF);
    data((HPS>>8)&0X00FF);  //Set HPS
    data(HPS&0X00FF);
    data(HPW);              //Set HPW
    data((LPS>>8)&0X00FF);  //Set HPS
    data(LPS&0X00FF);
    data(0x0000);

    command(SSD1963_SetVertPeriod); 
    data((VT>>8)&0X00FF);   //Set VT
    data(VT&0X00FF);
    data((VPS>>8)&0X00FF);  //Set VPS
    data(VPS&0X00FF);
    data(VPW);              //Set VPW
    data((FPS>>8)&0X00FF);  //Set FPS
    data(FPS&0X00FF);

    command(SSD1963_SetGPIOValue);
    data(0x0005);    //GPIO[3:0] out 1

    command(SSD1963_SetGPIOConf);
    data(0x0007);    //GPIO3=input, GPIO[2:0]=output
    data(0x0001);    //GPIO0 normal

    command(SSD1963_SetAddressMode); //rotation
    data(0x0000);

    command(SSD1963_SetPixelDataInterface);
    data(0x0003);

    delay(5);

    command(SSD1963_SetDisplayOn);
    command(SSD1963_SetDBCConf);
    data(0x000d);
}

void SSD1963_7::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

    uint16_t x0a, x1a, y0a, y1a;

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

    command(SSD1963_SetColumnAddress);
    data((x0 >> 8) & 0xFF);
    data(x0 & 0xFF);
    data((x1 >> 8) & 0xFF);
    data(x1 & 0xFF);
    command(SSD1963_SetPageAddress);
    data((y0 >> 8) & 0xFF);
    data(y0 & 0xFF);
    data((y1 >> 8) & 0xFF);
    data(y1 & 0xFF);
    command(SSD1963_WriteMemoryStart);

}

void SSD1963_7::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

	setAddrWindow(x,y,x,y);
    data(color);
}

void SSD1963_7::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void SSD1963_7::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);
	for(uint32_t i = 0; i < w * h; i++) {
        data(color);
	}
}

void SSD1963_7::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if ((y < 0) || (y >= _height) || (w <= 0)) {
        return;
    }

    if (x < 0) {
        w += x;
        x = 0;
        if (w <= 0) {
            return;
        }
    }

    if (x >= _width) {
        return;
    }

    if (x + w >= _width) {
        w = _width-x;
        if (w <= 0) {
            return;
        }
    }

	setAddrWindow(x, y, x+w-1, y);
	while (w--) {
        data(color);
	}
}

void SSD1963_7::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if ((x < 0) || (x >= _width) || (h <= 0)) {
        return;
    }

    if (y < 0) {
        h += y;
        y = 0;
        if (h <= 0) {
            return;
        }
    }

    if (y >= _height) {
        return;
    }

    if (y + h >= _height) {
        h = _height-y;
        if (h <= 0) {
            return;
        }
    }

	setAddrWindow(x, y, x, y+h-1);
	while (h--) {
        data(color);
	}
}

#define SSD1963_EMODE 0x0003

#define SSD1963_TRI 0x8000
#define SSD1963_DFM 0x4000
#define SSD1963_BGR 0x1000
#define SSD1963_HWM 0x0200
#define SSD1963_ORG 0x0080
#define SSD1963_ID0 0x0000
#define SSD1963_ID1 0x0010
#define SSD1963_ID2 0x0020
#define SSD1963_ID3 0x0030
#define SSD1963_AM  0x0008

void SSD1963_7::setRotation(uint8_t m) {
	rotation = m % 4; // can't be higher than 3
}

void SSD1963_7::invertDisplay(boolean i) {
	command(i ? SSD1963_EnterInvertMode : SSD1963_ExitInvertMode);
}

void SSD1963_7::displayOn() {
    command(SSD1963_ExitIdleMode);
    command(SSD1963_SetDisplayOn);
    command(SSD1963_EnterSleepMode);
}

void SSD1963_7::displayOff() {
    command(SSD1963_ExitSleepMode);
    command(SSD1963_SetDisplayOff);
    command(SSD1963_EnterIdleMode);
}


void SSD1963_7::windowData(uint16_t d) {
    data(d);
}

void SSD1963_7::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void SSD1963_7::enableBacklight() {
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(0xFF);
    data(0x01);
    data(0xFF);
    data(0x00);
    data(0x00);
    _brightness = 0xff;
}

void SSD1963_7::disableBacklight() {
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(0xFF);
    data(0x00);
    data(_brightness);
    data(0x00);
    data(0x00);
}

void SSD1963_7::setBacklight(uint8_t b) {
    _brightness = b;
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(_brightness);
    data(0x01);
    data(_brightness);
    data(0x00);
    data(0x00);
}
