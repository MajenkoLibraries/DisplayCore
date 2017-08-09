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
   _profile=TFT7;
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
   _profile=TFT7;
}

void SSD1963::command(uint16_t cmd) {
    port_rs->lat.clr = mask_rs;
    (cmd & 0x0001) ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    (cmd & 0x0002) ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    (cmd & 0x0004) ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    (cmd & 0x0008) ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    (cmd & 0x0010) ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    (cmd & 0x0020) ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    (cmd & 0x0040) ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    (cmd & 0x0080) ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    (cmd & 0x0100) ? port_d8->lat.set = mask_d8 : port_d8->lat.clr = mask_d8;
    (cmd & 0x0200) ? port_d9->lat.set = mask_d9 : port_d9->lat.clr = mask_d9;
    (cmd & 0x0400) ? port_d10->lat.set = mask_d10 : port_d10->lat.clr = mask_d10;
    (cmd & 0x0800) ? port_d11->lat.set = mask_d11 : port_d11->lat.clr = mask_d11;
    (cmd & 0x1000) ? port_d12->lat.set = mask_d12 : port_d12->lat.clr = mask_d12;
    (cmd & 0x2000) ? port_d13->lat.set = mask_d13 : port_d13->lat.clr = mask_d13;
    (cmd & 0x4000) ? port_d14->lat.set = mask_d14 : port_d14->lat.clr = mask_d14;
    (cmd & 0x8000) ? port_d15->lat.set = mask_d15 : port_d15->lat.clr = mask_d15;
    port_cs->lat.clr = mask_cs;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

void SSD1963::data8(uint8_t cmd) {
    port_rs->lat.set = mask_rs;
    (cmd & 0x0001) ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    (cmd & 0x0002) ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    (cmd & 0x0004) ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    (cmd & 0x0008) ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    (cmd & 0x0010) ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    (cmd & 0x0020) ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    (cmd & 0x0040) ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    (cmd & 0x0080) ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    port_cs->lat.clr = mask_cs;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

void SSD1963::data(uint16_t cmd) {
    port_rs->lat.set = mask_rs;
    (cmd & 0x0001) ? port_d0->lat.set = mask_d0 : port_d0->lat.clr = mask_d0;
    (cmd & 0x0002) ? port_d1->lat.set = mask_d1 : port_d1->lat.clr = mask_d1;
    (cmd & 0x0004) ? port_d2->lat.set = mask_d2 : port_d2->lat.clr = mask_d2;
    (cmd & 0x0008) ? port_d3->lat.set = mask_d3 : port_d3->lat.clr = mask_d3;
    (cmd & 0x0010) ? port_d4->lat.set = mask_d4 : port_d4->lat.clr = mask_d4;
    (cmd & 0x0020) ? port_d5->lat.set = mask_d5 : port_d5->lat.clr = mask_d5;
    (cmd & 0x0040) ? port_d6->lat.set = mask_d6 : port_d6->lat.clr = mask_d6;
    (cmd & 0x0080) ? port_d7->lat.set = mask_d7 : port_d7->lat.clr = mask_d7;
    (cmd & 0x0100) ? port_d8->lat.set = mask_d8 : port_d8->lat.clr = mask_d8;
    (cmd & 0x0200) ? port_d9->lat.set = mask_d9 : port_d9->lat.clr = mask_d9;
    (cmd & 0x0400) ? port_d10->lat.set = mask_d10 : port_d10->lat.clr = mask_d10;
    (cmd & 0x0800) ? port_d11->lat.set = mask_d11 : port_d11->lat.clr = mask_d11;
    (cmd & 0x1000) ? port_d12->lat.set = mask_d12 : port_d12->lat.clr = mask_d12;
    (cmd & 0x2000) ? port_d13->lat.set = mask_d13 : port_d13->lat.clr = mask_d13;
    (cmd & 0x4000) ? port_d14->lat.set = mask_d14 : port_d14->lat.clr = mask_d14;
    (cmd & 0x8000) ? port_d15->lat.set = mask_d15 : port_d15->lat.clr = mask_d15;
    port_cs->lat.clr = mask_cs;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

uint16_t SSD1963::read() {
    port_d0->tris.set = mask_d0;
    port_d1->tris.set = mask_d1;
    port_d2->tris.set = mask_d2;
    port_d3->tris.set = mask_d3;
    port_d4->tris.set = mask_d4;
    port_d5->tris.set = mask_d5;
    port_d6->tris.set = mask_d6;
    port_d7->tris.set = mask_d7;
    port_d8->tris.set = mask_d8;
    port_d9->tris.set = mask_d9;
    port_d10->tris.set = mask_d10;
    port_d11->tris.set = mask_d11;
    port_d12->tris.set = mask_d12;
    port_d13->tris.set = mask_d13;
    port_d14->tris.set = mask_d14;
    port_d15->tris.set = mask_d15;

    port_rs->lat.set = mask_rs;
    port_cs->lat.clr = mask_cs;
    port_rd->lat.clr = mask_rd;
    uint16_t out = 0;

    out |= (port_d0->port.reg & mask_d0) ? 0x0001 : 0x0000;
    out |= (port_d1->port.reg & mask_d1) ? 0x0002 : 0x0000;
    out |= (port_d2->port.reg & mask_d2) ? 0x0004 : 0x0000;
    out |= (port_d3->port.reg & mask_d3) ? 0x0008 : 0x0000;
    out |= (port_d4->port.reg & mask_d4) ? 0x0010 : 0x0000;
    out |= (port_d5->port.reg & mask_d5) ? 0x0020 : 0x0000;
    out |= (port_d6->port.reg & mask_d6) ? 0x0040 : 0x0000;
    out |= (port_d7->port.reg & mask_d7) ? 0x0080 : 0x0000;
    out |= (port_d8->port.reg & mask_d8) ? 0x0100 : 0x0000;
    out |= (port_d9->port.reg & mask_d9) ? 0x0200 : 0x0000;
    out |= (port_d10->port.reg & mask_d10) ? 0x0400 : 0x0000;
    out |= (port_d11->port.reg & mask_d11) ? 0x0800 : 0x0000;
    out |= (port_d12->port.reg & mask_d12) ? 0x1000 : 0x0000;
    out |= (port_d13->port.reg & mask_d13) ? 0x2000 : 0x0000;
    out |= (port_d14->port.reg & mask_d14) ? 0x4000 : 0x0000;
    out |= (port_d15->port.reg & mask_d15) ? 0x8000 : 0x0000;

    port_rd->lat.set = mask_rd;
    port_d0->tris.clr = mask_d0;
    port_d1->tris.clr = mask_d1;
    port_d2->tris.clr = mask_d2;
    port_d3->tris.clr = mask_d3;
    port_d4->tris.clr = mask_d4;
    port_d5->tris.clr = mask_d5;
    port_d6->tris.clr = mask_d6;
    port_d7->tris.clr = mask_d7;
    port_d8->tris.clr = mask_d8;
    port_d9->tris.clr = mask_d9;
    port_d10->tris.clr = mask_d10;
    port_d11->tris.clr = mask_d11;
    port_d12->tris.clr = mask_d12;
    port_d13->tris.clr = mask_d13;
    port_d14->tris.clr = mask_d14;
    port_d15->tris.clr = mask_d15;

    port_cs->lat.set = mask_cs;
    return out;

}

void SSD1963::initInterface() {
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
    port_cs = getPortInformation(pin_cs, &mask_cs);
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


    digitalWrite(pin_cs, HIGH);

    pinMode(pin_reset, OUTPUT);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);

}

void SSD1963::initializeDevice() {
    initInterface();

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

    command(SSD1963_SetLCDMode);
    // The SSD1963 controller can be connected to the TFT screen with 18 or 24 data lines.
    if (bus_width == TFTBUS24) {
        data(0x0020);
    } else {
        data(0x0000);
    }
    data(0x0000);


    // Set the timing for the different profiles.

    // 7 inch TFT profile

    if (_profile == TFT7) {
        _width  = 800;
        _height = 480;

        // Continues on from previous SetLCDMode command
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

        command(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
        data(0x0003);
        data(0x00ff);
        data(0x00ff);

        command(SSD1963_SetAddressMode); //rotation
        data(0x0000); // RGB

    } else if (_profile == MIKROMEDIA) {
        _width  = 480;
        _height = 272;

        // Continues on from previous SetLCDMode command
        data((479>>8)&0X00FF);  //Set HDP
        data(479&0X00FF);
        data((271>>8)&0X00FF);  //Set VDP
        data(271&0X00FF);
        data(0x0000);

        command(SSD1963_SetHoriPeriod);
        data((531>>8)&0X00FF);  //Set HT
        data(531&0X00FF);
        data((43>>8)&0X00FF);  //Set HPS
        data(43&0X00FF);
        data(10);              //Set HPW
        data((8>>8)&0X00FF);  //Set HPS
        data(8&0X00FF);
        data(0x0000);

        command(SSD1963_SetVertPeriod);
        data((288>>8)&0X00FF);   //Set VT
        data(288&0X00FF);
        data((12>>8)&0X00FF);  //Set VPS
        data(12&0X00FF);
        data(10);              //Set VPW
        data((4>>8)&0X00FF);  //Set FPS
        data(4&0X00FF);

        command(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
        data(0x0003);
        data(0x00ff);
        data(0x00ff);

        command(SSD1963_SetAddressMode); //rotation
        data(0x0000); // RGB

    } else if (_profile == VGA640) {
        _width  = 640;
        _height = 480;
        uint16_t hdp = 640 - 1; // panel width
        uint16_t vdp = 480 - 1; // panel height

        uint16_t ht = 800 - 1; // total pixel clocks per line
        uint16_t hps = 96+48 - 1 + 16; // Blank period
        uint16_t hpw = 96 - 1;  // Sync width
        uint16_t lps = 16 - 1;  // Front porch

        uint16_t vt = 525 - 1;
        uint16_t vps = 2+33 - 1 + 10; // Blank period
        uint16_t vpw = 2 - 1;
        uint16_t fps = 10 - 1;  // Front porch

        // Continues on from previous SetLCDMode command
        data((hdp>>8)&0X00FF);  //Set HDP
        data(hdp&0X00FF);
        data((vdp>>8)&0X00FF);  //Set VDP
        data(vdp&0X00FF);
        data(0x0000);

        command(SSD1963_SetHoriPeriod);
        data((ht>>8)&0X00FF);  //Set HT
        data(ht&0X00FF);
        data((hps>>8)&0X00FF);  //Set HPS
        data(hps&0X00FF);
        data(hpw);              //Set HPW
        data((lps>>8)&0X00FF);  //Set HPS
        data(lps&0X00FF);
        data(0x0000);

        command(SSD1963_SetVertPeriod);
        data((vt>>8)&0X00FF);   //Set VT
        data(vt&0X00FF);
        data((vps>>8)&0X00FF);  //Set VPS
        data(vps&0X00FF);
        data(vpw);              //Set VPW
        data((fps>>8)&0X00FF);  //Set FPS
        data(fps&0X00FF);

        command(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
        // 73Hz (steady as a rock)
        data(0x0003);
        data(0x0068);
        data(0x001a);
/*
        // 60Hz (has a shimmer on my monitor)
        data(0x0002);
        data(0x00CC);
        data(0x0016);
*/

        command(SSD1963_SetAddressMode); //rotation
        data(0x0008); // BGR
    } else if (_profile == VGA720) {
        _width  = 720;
        _height = 400;
        const uint16_t hdp = 720 - 1; // panel width
        const uint16_t vdp = 400 - 1; // panel height

        const uint16_t h_fp = 36;
        const uint16_t h_pw = 72;
        const uint16_t h_bp = 108;

        const uint16_t ht = 936 - 1; // total pixel clocks per line
        const uint16_t hps = h_fp + h_pw + h_bp - 1; // Blank period
        const uint16_t hpw = h_pw - 1;  // Sync width
        const uint16_t lps = h_fp - 1;  // Front porch

        const uint16_t v_fp = 1;
        const uint16_t v_pw = 3;
        const uint16_t v_bp = 42;

        uint16_t vt = 446 - 1;
        uint16_t vps = v_fp + v_pw + v_bp - 1; // Blank period
        uint16_t vpw = v_pw - 1;
        uint16_t fps = v_fp - 1;  // Front porch

        // Continues on from previous SetLCDMode command
        data((hdp>>8)&0X00FF);  //Set HDP
        data(hdp&0X00FF);
        data((vdp>>8)&0X00FF);  //Set VDP
        data(vdp&0X00FF);
        data(0x0000);

        command(SSD1963_SetHoriPeriod);
        data((ht>>8)&0X00FF);  //Set HT
        data(ht&0X00FF);
        data((hps>>8)&0X00FF);  //Set HPS
        data(hps&0X00FF);
        data(hpw);              //Set HPW
        data((lps>>8)&0X00FF);  //Set HPS
        data(lps&0X00FF);
        data(0x0000);

        command(SSD1963_SetVertPeriod);
        data((vt>>8)&0X00FF);   //Set VT
        data(vt&0X00FF);
        data((vps>>8)&0X00FF);  //Set VPS
        data(vps&0X00FF);
        data(vpw);              //Set VPW
        data((fps>>8)&0X00FF);  //Set FPS
        data(fps&0X00FF);

        command(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
        // 75Hz
        data(0x0003);
        data(0x007a);
        data(0x0092);

        // 73Hz (steady as a rock)
//        data(0x0003);
//        data(0x0068);
//        data(0x001a);

        // 60Hz (has a shimmer on my monitor)
//        data(0x0002);
//        data(0x00CC);
//        data(0x0016);


        command(SSD1963_SetAddressMode); //rotation
        data(0x0008); // BGR
    }

    command(SSD1963_SetGPIOValue);
    data(0x0005);    //GPIO[3:0] out 1

    command(SSD1963_SetGPIOConf);
    data(0x0007);    //GPIO3=input, GPIO[2:0]=output
    data(0x0001);    //GPIO0 normal

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

void SSD1963::setAddrWindow(int x0, int y0, int x1, int y1) {

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

void SSD1963::setPixel(int x, int y, color_t color) {
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

void SSD1963::fillScreen(color_t color) {
   fillRectangle(0, 0,  _width, _height, color);
}

void SSD1963::fillRectangle(int x, int y, int w, int h, color_t color) {
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

void SSD1963::drawHorizontalLine(int x, int y, int w, color_t color) {
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

void SSD1963::drawVerticalLine(int x, int y, int h, color_t color) {
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

void SSD1963::setRotation(int m) {
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


void SSD1963::windowData(color_t d) {
    data(d);
}

void SSD1963::windowData(const color_t *d, int l) {
    for (int i = 0; i < l; i++) {
        data(d[i]);
    }
}

void SSD1963::openWindow(int x0, int y0, int x1, int y1) {
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

void SSD1963::setBacklight(int b) {
    _brightness = b;
    command(SSD1963_SetPWMConf);
    data(0x06);
    data(_brightness);
    data(0x01);
    data(_brightness);
    data(0x00);
    data(0x00);
}

color_t SSD1963::colorAt(int x, int y) {
    setAddrWindow(x, y, x, y);
    command(0x2E);
    return read();
}


/*------------------------- PORT B VARIANT ------------------------------*/

SSD1963_PORTB::SSD1963_PORTB(
   uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
   uint8_t tft_bus_width
   ) {

   pin_rs = rs;
   pin_wr = wr;
   pin_rd = rd;
   pin_cs = cs;
   pin_reset = reset;
   pin_d8 = 1; // Force 16 bit mode
   bus_width = tft_bus_width;
   _profile=TFT7;
}

void SSD1963_PORTB::command(uint16_t cmd) {
    TRISB = 0x0000;
    port_rs->lat.clr = mask_rs;
    port_cs->lat.clr = mask_cs;
    LATB = cmd;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

void SSD1963_PORTB::data8(uint8_t cmd) {
    TRISB = 0x0000;
    port_rs->lat.set = mask_rs;
    port_cs->lat.clr = mask_cs;
    LATB = cmd;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

void SSD1963_PORTB::data(uint16_t cmd) {
    TRISB = 0x0000;
    port_rs->lat.set = mask_rs;
    port_cs->lat.clr = mask_cs;
    LATB = cmd;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
    port_cs->lat.set = mask_cs;
}

uint16_t SSD1963_PORTB::read() {
    TRISB = 0xFFFF;
    port_rs->lat.set = mask_rs;
    port_rd->lat.clr = mask_rd;
    port_cs->lat.clr = mask_cs;
    uint16_t out = PORTB;
    port_rd->lat.set = mask_rd;
    TRISB = 0x0000;
    port_cs->lat.set = mask_cs;
    return out;
}

void SSD1963_PORTB::initInterface() {
    pinMode(pin_rs, OUTPUT);
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_rd, OUTPUT);
    pinMode(pin_wr, OUTPUT);
    pinMode(pin_reset, OUTPUT);

    TRISB = 0x0000;
#ifdef __PIC32_PPS__
    ANSELB = 0x0000;
#endif

    port_rs = getPortInformation(pin_rs, &mask_rs);
    port_rd = getPortInformation(pin_rd, &mask_rd);
    port_wr = getPortInformation(pin_wr, &mask_wr);
    port_cs = getPortInformation(pin_cs, &mask_cs);

    digitalWrite(pin_rs, HIGH);
    digitalWrite(pin_cs, HIGH);
    digitalWrite(pin_rd, HIGH);
    digitalWrite(pin_wr, HIGH);


    digitalWrite(pin_cs, HIGH);

    pinMode(pin_reset, OUTPUT);
    digitalWrite(pin_reset, HIGH);
    delay(100);
    digitalWrite(pin_reset, LOW);
    delay(100);
    digitalWrite(pin_reset, HIGH);
    delay(100);
}

void SSD1963_PORTB::openWindow(int x0, int y0, int x1, int y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
    port_cs->lat.clr = mask_cs;
    port_rs->lat.set = mask_rs;
}

void SSD1963_PORTB::windowData(color_t d) {
    LATB = d;
    port_wr->lat.clr = mask_wr;
    port_wr->lat.set = mask_wr;
}

void SSD1963_PORTB::windowData(color_t *d, int l) {
    for (uint32_t x = 0; x < l; x++) {
        LATB = d[x];
        port_wr->lat.clr = mask_wr;
        port_wr->lat.set = mask_wr;
    }
}

void SSD1963_PORTB::closeWindow() {
    port_cs->lat.set = mask_cs;
}
