#include <PG25664CG.h>

/*
D/C     A0
WR      A1
RD      A2
D0      37      RE0
D1      36      RE1
D2      35      RE2
D3      34      RE3
D4      33      RE4
D5      32      RE5
D6      31      RE6
D7      30      RE7
CS      A3
RES     A4
*/

void PG25664CG::startDisplay() {
    // Set_Command_Lock(0x12)
    command(0xFD); data(0x12);

    // Set_Display_On_Off(0x00);       // Display Off (0x00/0x01)
    displayOff();

    // Set_Display_Clock(0x91);        // Set Clock as 80 Frames/Sec
    command(0xB3); data(0x91);

    // Set_Multiplex_Ratio(0x3F);      // 1/64 Duty (0x0F~0x3F)
    command(0xCA); data(0x3F);

    // Set_Display_Offset(0x00);       // Shift Mapping RAM Counter (0x00~0x3F)
    command(0xA2); data(0x00);

    // Set_Start_Line(0x00);           // Set Mapping RAM Display Start Line (0x00~0x7F)
    command(0xA1); data(0x00);
    // Set_Remap_Format(0x14);         // Set Horizontal Address Increment
                        //     Column Address 0 Mapped to SEG0
                        //     Disable Nibble Remap
                        //     Scan from COM[N-1] to COM0
                        //     Disable COM Split Odd Even
                        //     Enable Dual COM Line Mode
    command(0xA0); data(0x14); data(0x11);
// 0x14 0x11

    // Set_GPIO(0x00);             // Disable GPIO Pins Input
    command(0xB5); data(0x00);

    // Set_Function_Selection(0x01);       // Enable Internal VDD Regulator
    command(0xAB); data(0x01);

    // Set_Display_Enhancement_A(0xA0,0xFD);   // Enable External VSL
    command(0xB4); data(0xA0); data(0xFD);

    // Set_Contrast_Current(0xFF);     // Set Segment Output Current
    command(0xC1); data(0xFF);

    // Set_Master_Current(Brightness);     // Set Scale Factor of Segment Output Current Control
    command(0xC7); data(0x0F);

    // Set_Gray_Scale_Table();         // Set Pulse Width for Gray Scale Table
    command(0xB8);
        data(0x00);           //   Gray Scale Level 1
        data(0x00);           //   Gray Scale Level 2
        data(0x00);           //   Gray Scale Level 3
        data(0x03);           //   Gray Scale Level 4
        data(0x06);           //   Gray Scale Level 5
        data(0x10);           //   Gray Scale Level 6
        data(0x1D);           //   Gray Scale Level 7
        data(0x2A);           //   Gray Scale Level 8
        data(0x37);           //   Gray Scale Level 9
        data(0x46);           //   Gray Scale Level 10
        data(0x58);           //   Gray Scale Level 11
        data(0x6A);           //   Gray Scale Level 12
        data(0x7F);           //   Gray Scale Level 13
        data(0x96);           //   Gray Scale Level 14
        data(0xB4);           //   Gray Scale Level 15
    command(0x00);            // Enable gray scale table

    // Set_Phase_Length(0xE8);         // Set Phase 1 as 17 Clocks & Phase 2 as 14 Clocks
    command(0xB1); data(0xE8);

    // Set_Display_Enhancement_B(0x20);    // Enhance Driving Scheme Capability (0x00/0x20)
    command(0xD1); data(0x82); data(0x20); // These were or-ed together

    // Set_Precharge_Voltage(0x1F);        // Set Pre-Charge Voltage Level as 0.60*VCC
    command(0xBB); data(0x1F);

    // Set_Precharge_Period(0x08);     // Set Second Pre-Charge Period as 8 Clocks
    command(0xB6); data(0x08);

    // Set_VCOMH(0x07);            // Set Common Pins Deselect Voltage Level as 0.86*VCC
    command(0xBE); data(0x07);

    // Set_Display_Mode(0x02);         // Normal Display Mode (0x00/0x01/0x02/0x03)
    command(0xA4 | 0x02);

    // Set_Partial_Display(0x01,0x00,0x00);    // Disable Partial Display
    command(0xA8 | 0x01); // data(0x00); data(0x00);  <-- only for 0xA8 | 0x00

    // Fill_RAM(0x00);             // Clear Screen

    // Set_Display_On_Off(0x01);       // Display On (0x00/0x01)
    displayOn();

}

void PG25664CG::displayOff() {
    command(0xAE);
}

void PG25664CG::displayOn() {
    command(0xAF);
}

void PG25664CG::setAddressWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) {
    command(0x15);
    data(xs & 0xFF);
    data(xe & 0xFF);
    command(0x75);
    data(ys & 0xFF);
    data(ye & 0xFF);
}

void PG25664CG::fillScreen(uint16_t c) {
    uint8_t pd = (c & 0x0F) | ((c & 0x0F) << 4);
    for (int x = 0; x < 8192; x++) {
        _buffer[x] = pd;
    }
    if (!_buffered) {
        update();
    }
}

void PG25664CG::update() {
    setAddressWindow(28, 0, 91, 63);
    command(0x5C);
    for (int x = 0; x < 8192; x++) {
        data(_buffer[x]);
    }
}

void PG25664CG::setPixel(int16_t x, int16_t y, uint16_t c) {
    if (x < 0 || y < 0 || x > 255 || y > 63) {
        return;
    }
    int16_t dx = x / 2;
    uint8_t b = _buffer[dx + (y * 128)];
    if (x & 1) {
        b &= 0xF0;
        b |= (c & 0x0F);
    } else {
        b &= 0x0F;
        b |= ((c & 0x0f) << 4);
    }
    _buffer[dx + (y * 128)] = b;
    if (!_buffered) {
        update();
    }
}

void PG25664CG::startBuffer() {
    _buffered = true;
}

void PG25664CG::endBuffer() {
    _buffered = false;
    update();
}


void PG25664CG::command(uint8_t cmd) {
    digitalWrite(pin_dc, LOW);
    digitalWrite(pin_d0, cmd & 0x01);
    digitalWrite(pin_d1, cmd & 0x02);
    digitalWrite(pin_d2, cmd & 0x04);
    digitalWrite(pin_d3, cmd & 0x08);
    digitalWrite(pin_d4, cmd & 0x10);
    digitalWrite(pin_d5, cmd & 0x20);
    digitalWrite(pin_d6, cmd & 0x40);
    digitalWrite(pin_d7, cmd & 0x80);
    digitalWrite(pin_wr, LOW);
    digitalWrite(pin_wr, HIGH);
}

void PG25664CG::data(uint8_t cmd) {
    digitalWrite(pin_dc, HIGH);
    digitalWrite(pin_d0, cmd & 0x01);
    digitalWrite(pin_d1, cmd & 0x02);
    digitalWrite(pin_d2, cmd & 0x04);
    digitalWrite(pin_d3, cmd & 0x08);
    digitalWrite(pin_d4, cmd & 0x10);
    digitalWrite(pin_d5, cmd & 0x20);
    digitalWrite(pin_d6, cmd & 0x40);
    digitalWrite(pin_d7, cmd & 0x80);
    digitalWrite(pin_wr, LOW);
    digitalWrite(pin_wr, HIGH);
}

void PG25664CG_PORTB::command(uint8_t cmd) {
    uint16_t cmask = cmd;
    cmask <<= pin_data;
    LATBCLR = 1<<pin_dc;
    LATBCLR = 0xFF << pin_data;
    LATBSET = cmask;
    LATBCLR = 1 << pin_wr;
    LATBSET = 1 << pin_wr;
}

void PG25664CG_PORTB::data(uint8_t cmd) {
    uint16_t cmask = cmd;
    cmask <<= pin_data;
    LATBSET = 1<<pin_dc;
    LATBCLR = 0xFF << pin_data;
    LATBSET = cmask;
    LATBCLR = 1 << pin_wr;
    LATBSET = 1 << pin_wr;
}

void PG25664CG_PMP::command(uint8_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8000;
    PMDIN = cmd;
}

void PG25664CG_PMP::data(uint8_t cmd) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x8001;
    PMDIN = cmd;
}




