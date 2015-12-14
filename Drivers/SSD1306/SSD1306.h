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

#include <DisplayCore.h>
#include <DSPI.h>

class SSD1306 : public DisplayCore {

    private:
        const int DC_DATA = HIGH;
        const int DC_COMMAND = LOW;

        const int CMD_SEG_REMAP         = 0xA1;
        const int CMD_COM_DIR           = 0xC8;
        const int CMD_COM_CONFIG        = 0xDA;
        const int CMD_DISP_ON           = 0xAF;
        const int CMD_DISP_OFF          = 0xAE;


        DSPI *_spi;
        int _cs;
        int _dc;
        int _vdd;
        int _vbat;
        int _reset;
        int _buffered;

        uint8_t _buffer[8*128]; // 8 pages of 128 bytes.
        void updateDisplay();

        void command(uint8_t c);
        void command(uint8_t c1, uint8_t c2);
        void command(uint8_t c1, uint8_t c2, uint8_t c3);
        void data(uint8_t d);

        void setPage(int p);
        void setY(int y);

    public:
        SSD1306(DSPI &spi, int cs, int dc, int vdd, int vbat, int reset = -1) : 
            _spi(&spi), _cs(cs), _dc(dc), _vdd(vdd), _vbat(vbat), _reset(reset),
            _buffered(0) {
                _width = 128;
                _height = 32;
        }

        void initializeDevice();

        void setPixel(int16_t x, int16_t y, uint16_t color);
        void displayOn();
        void displayOff();

        void setRotation(uint8_t r) {}
        void invertDisplay(boolean i) {}

        void startBuffer() { _buffered++; }
        void endBuffer() { _buffered--; if (_buffered == 0) {updateDisplay();} }

        uint16_t getWidth() { return 128; }
        uint16_t getHeight() { return 32; }

        void fillScreen(uint16_t color);
};

