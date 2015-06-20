#include <SSD1963.h>

SSD1963::SSD1963(
   uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
   uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
   uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
   uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
   uint8_t tft_bus_width
   ) {

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
   pin_rs = rs;
   pin_wr = wr;
   pin_rd = rd;
   pin_cs = cs;
   pin_reset = reset;
   bus_width = tft_bus_width;
}

SSD1963::SSD1963(
   uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
   uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
   uint8_t tft_bus_width
   ) {

   pin_d0 = d0;
   pin_d1 = d1;
   pin_d2 = d2;
   pin_d3 = d3;
   pin_d4 = d4;
   pin_d5 = d5;
   pin_d6 = d6;
   pin_d7 = d7;
   pin_d8 = NOT_A_PIN;
   pin_d9 = NOT_A_PIN;
   pin_d10 = NOT_A_PIN;
   pin_d11 = NOT_A_PIN;
   pin_d12 = NOT_A_PIN;
   pin_d13 = NOT_A_PIN;
   pin_d14 = NOT_A_PIN;
   pin_d15 = NOT_A_PIN;
   pin_rs = rs;
   pin_wr = wr;
   pin_rd = rd;
   pin_cs = cs;
   pin_reset = reset;
   bus_width = tft_bus_width;
}
void SSD1963::initializeDevice() {

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

    _width  = SSD1963::Width;
    _height = SSD1963::Height;

    digitalWrite(pin_cs, HIGH);

    pinMode(pin_reset, OUTPUT);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);

    digitalWrite(pin_cs, LOW);

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
   if (TFTBUS24 == bus_width)
      data(0x0020);         // 24 bits. The SSD1963 controller can be connected to the TFT screen with 18 or 24 data lines.
   else
      data(0x0000);         // 18 bits. The SSD1963 controller can be connected to the TFT screen with 18 or 24 data lines.
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
   if (NOT_A_PIN == pin_d8)
      data(0x0000);
   else
      data(0x0003);

    delay(5);

    command(SSD1963_SetDisplayOn);
    command(SSD1963_SetDBCConf);
    data(0x000d);
}

void SSD1963::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

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

void SSD1963::setPixel(int16_t x, int16_t y, uint16_t color) {
   if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height))
      return;

   setAddrWindow(x,y,x,y);
   if (NOT_A_PIN == pin_d8)
   {
      uint8_t red = (color & 0xF800) >> 8;
      red |= ((red & 0x08) ? 0x07 : 0x00);
      data8(red);
      uint8_t green = (color & 0x7E0) >> 3;
      green |= ((green & 0x08) ? 0x07 : 0x00);
      data8(green);
      uint8_t blue = (color & 0x1F) << 3;
      blue |= ((blue & 0x08) ? 0x07 : 0x00);
      data8(blue);
   }
   else
      data(color);
}

void SSD1963::fillScreen(uint16_t color) {
   fillRectangle(0, 0,  _width, _height, color);
}

void SSD1963::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
   setAddrWindow(x, y, x+w-1, y+h-1);
   for(uint32_t i = 0; i < w * h; i++) {
      if (NOT_A_PIN == pin_d8)
      {
         uint8_t red = (color & 0xF800) >> 8;
         red |= ((red & 0x08) ? 0x07 : 0x00);
         data8(red);
         uint8_t green = (color & 0x7E0) >> 3;
         green |= ((green & 0x08) ? 0x07 : 0x00);
         data8(green);
         uint8_t blue = (color & 0x1F) << 3;
         blue |= ((blue & 0x08) ? 0x07 : 0x00);
         data8(blue);
      }
      else
         data(color);
   }
}

void SSD1963::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
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
      if (NOT_A_PIN == pin_d8)
      {
         uint8_t red = (color & 0xF800) >> 8;
         red |= ((red & 0x08) ? 0x07 : 0x00);
         data8(red);
         uint8_t green = (color & 0x7E0) >> 3;
         green |= ((green & 0x08) ? 0x07 : 0x00);
         data8(green);
         uint8_t blue = (color & 0x1F) << 3;
         blue |= ((blue & 0x08) ? 0x07 : 0x00);
         data8(blue);
      }
      else
         data(color);
   }
}

void SSD1963::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
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
      if (NOT_A_PIN == pin_d8)
      {
         uint8_t red = (color & 0xF800) >> 8;
         red |= ((red & 0x08) ? 0x07 : 0x00);
         data8(red);
         uint8_t green = (color & 0x7E0) >> 3;
         green |= ((green & 0x08) ? 0x07 : 0x00);
         data8(green);
         uint8_t blue = (color & 0x1F) << 3;
         blue |= ((blue & 0x08) ? 0x07 : 0x00);
         data8(blue);
      }
      else
         data(color);
   }
}

void SSD1963::setRotation(uint8_t m) {
   rotation = m % 4; // can't be higher than 3
}

void SSD1963::invertDisplay(boolean i) {
   command(i ? SSD1963_EnterInvertMode : SSD1963_ExitInvertMode);
}

void SSD1963::displayOn() {
    command(SSD1963_ExitIdleMode);
    command(SSD1963_SetDisplayOn);
    command(SSD1963_EnterSleepMode);
    enableBacklight();
}

void SSD1963::displayOff() {
    command(SSD1963_ExitSleepMode);
    command(SSD1963_SetDisplayOff);
    command(SSD1963_EnterIdleMode);
    disableBacklight();
}


void SSD1963::windowData(uint16_t d) {
    data(d);
}

void SSD1963::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void SSD1963::enableBacklight() {
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(0xFF);
    data(0x01);
    data(0xFF);
    data(0x00);
    data(0x00);
    _brightness = 0xff;
}

void SSD1963::disableBacklight() {
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(0xFF);
    data(0x00);
    data(_brightness);
    data(0x00);
    data(0x00);
}

void SSD1963::setBacklight(uint8_t b) {
    _brightness = b;
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(_brightness);
    data(0x01);
    data(_brightness);
    data(0x00);
    data(0x00);
}

uint16_t SSD1963::colorAt(int16_t x, int16_t y) {
    setAddrWindow(x, y, x, y);
    command(0x2E);
    return read();
}


