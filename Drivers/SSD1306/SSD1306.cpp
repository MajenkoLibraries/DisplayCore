/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <SSD1306.h>

void SSD1306::initializeDevice() {
    _spi->begin();
    _spi->setSpeed(20000000UL);
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    pinMode(_dc, OUTPUT);
    digitalWrite(_dc, DC_COMMAND);
    pinMode(_vdd, OUTPUT);
    digitalWrite(_vdd, LOW);
    pinMode(_vbat, OUTPUT);
    digitalWrite(_vbat, LOW);

    // Start off by powering the thing up.  Step one is
    // turn on the VDD supply.
    digitalWrite(_vdd, HIGH);
    delay(1);

    displayOff();

    // Then do a reset if we control the reset pin:

    if (_reset >= 0) {
        pinMode(_reset, OUTPUT);
        digitalWrite(_reset, HIGH);
        delay(20);
        digitalWrite(_reset, LOW);
        delay(20);
        digitalWrite(_reset, HIGH);
    }

    // Now configure the charge pump:

    command(0x8D, 0x14);
    command(0xD9, 0xF1);

    // Now VBAT needs to be turned on:

    digitalWrite(_vbat, HIGH);
    delay(100);

    // Invert the display
    command(CMD_SEG_REMAP);
    command(CMD_COM_DIR);

    // Sequential COM
    command(CMD_COM_CONFIG);
    command(0x20);

    // Display on

    displayOn();
}

#define C2B(X, Y) (((Y) << 7) + (X))

void SSD1306::setPixel(int16_t x, int16_t y, uint16_t color) {
    uint8_t row;
    uint8_t pixel;
    uint8_t mask;

    if((x < 0) ||(x >= 128) || (y < 0) || (y >= 32))
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

void SSD1306::displayOn() {
    command(CMD_DISP_ON);
}

void SSD1306::displayOff() {
    command(CMD_DISP_OFF);
}

void SSD1306::command(uint8_t c) {
    digitalWrite(_dc, DC_COMMAND);
    digitalWrite(_cs, LOW);
    _spi->transfer(c);
    digitalWrite(_cs, HIGH);
}

void SSD1306::command(uint8_t c1, uint8_t c2) {
    digitalWrite(_dc, DC_COMMAND);
    digitalWrite(_cs, LOW);
    _spi->transfer(c1);
    _spi->transfer(c2);
    digitalWrite(_cs, HIGH);
}

void SSD1306::command(uint8_t c1, uint8_t c2, uint8_t c3) {
    digitalWrite(_dc, DC_COMMAND);
    digitalWrite(_cs, LOW);
    _spi->transfer(c1);
    _spi->transfer(c2);
    _spi->transfer(c3);
    digitalWrite(_cs, HIGH);
}

void SSD1306::data(uint8_t c) {
    digitalWrite(_dc, DC_DATA);
    digitalWrite(_cs, LOW);
    _spi->transfer(c);
    digitalWrite(_cs, HIGH);
}

void SSD1306::setPage(int page) {
    command(0x22, page & 0x07, page & 0x07);
}

void SSD1306::setY(int y) {
    command(0x00 | (y & 0x0F)); // Low nibble
    command(0x10 | ((y >> 4) & 0x0F)); // High nibble
}

void SSD1306::updateDisplay() {
    for (int p = 0; p < 7; p++) {
        setPage(p);
        setY(0);
        for (int y = 0; y < 128; y++) {
            data(_buffer[C2B(y, p)]);
        }
    }
}

