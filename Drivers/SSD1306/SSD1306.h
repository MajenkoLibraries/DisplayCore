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

    protected:
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

        int _offset_x;
        int _offset_y;

        uint8_t _buffer[8*128]; // 8 pages of 128 bytes.
        void updateDisplay();

        virtual void command(uint8_t c);
        virtual void command(uint8_t c1, uint8_t c2);
        virtual void command(uint8_t c1, uint8_t c2, uint8_t c3);
        virtual void data(uint8_t d);

        void setPage(int p);
        void setY(int y);

    public:
        SSD1306(DSPI &spi, int cs, int dc, int vdd, int vbat, int reset = -1) : 
            _spi(&spi), _cs(cs), _dc(dc), _vdd(vdd), _vbat(vbat), _reset(reset),
            _buffered(0) {
                _width = 128;
                _height = 64;
                _offset_x = 0;
                _offset_y = 0;
        }
        SSD1306(DSPI *spi, int cs, int dc, int vdd, int vbat, int reset = -1) : 
            _spi(spi), _cs(cs), _dc(dc), _vdd(vdd), _vbat(vbat), _reset(reset),
            _buffered(0) {
                _width = 128;
                _height = 64;
                _offset_x = 0;
                _offset_y = 0;
        }
        SSD1306(int cs, int dc, int vdd, int vbat, int reset = -1) : 
            _spi(NULL), _cs(cs), _dc(dc), _vdd(vdd), _vbat(vbat), _reset(reset),
            _buffered(0) {
                _width = 128;
                _height = 64;
                _offset_x = 0;
                _offset_y = 0;
        }

        virtual void initializeDevice();

        void setPixel(int x, int y, color_t color);
        void displayOn();
        void displayOff();

        void setRotation(int r);
        void invertDisplay(boolean i) {}

        void startBuffer() { _buffered++; }
        void endBuffer() { _buffered--; if (_buffered == 0) {updateDisplay();} }

        int getWidth() { return _width; }
        int getHeight() { return _height; }

        void fillScreen(color_t color);
};

class SSD1306_BB : public SSD1306 {
    private:
        p32_ioport *_mosi_port;
        p32_ioport *_sck_port;
        uint32_t _mosi_mask;
        uint32_t _sck_mask;
        uint32_t _mosi_pin;
        uint32_t _sck_pin;

        void sendByte(uint8_t b);
        virtual void command(uint8_t c);
        virtual void command(uint8_t c1, uint8_t c2);
        virtual void command(uint8_t c1, uint8_t c2, uint8_t c3);
        virtual void data(uint8_t d);

    public:
        SSD1306_BB(uint32_t mosi, uint32_t sck, int cs, int dc, int vdd, int vbat, int reset = -1) : _mosi_pin(mosi), _sck_pin(sck), SSD1306(cs, dc, vdd, vbat, reset) {}
        virtual void initializeDevice();
};

// These should work with any Uno32-like board with the PMOD shield attached
// Not all boards will have SPI in the same place, so we shall just
// bit-bang everything regardless.

class SSD1306_UMOD_JA : public SSD1306_BB {
    public:
        SSD1306_UMOD_JA() : SSD1306_BB(27, 29, 26, 30, 33, 32, 31) {_height = 32;}
};
    
class SSD1306_UMOD_JB : public SSD1306_BB {
    public:
        SSD1306_UMOD_JB() : SSD1306_BB(1, 38, 7, 36, 37, 10, 34) {_height = 32;}
};
    
//class SSD1306_UMOD_JC : public SSD1306 {
//    public:
//        SSD1306_UMOD_JC() : SSD1306_BB([2], [4], [1], [7], [10], [9], [8]) {_height = 32;}
//};
    
class SSD1306_UMOD_JD : public SSD1306_BB {
    public:
        SSD1306_UMOD_JD() : SSD1306_BB(40, 19, 16, 42, 5, 3, 41) {_height = 32;}
};
    
class SSD1306_UMOD_JE : public SSD1306_BB {
    public:
        SSD1306_UMOD_JE() : SSD1306_BB(6, 22, 14, 18, 24, 35, 9) {_height = 32;}
};
    

#if defined(_BOARD_CMOD_)
class SSD1306_CMOD_J1 : public SSD1306 {
    public:
        SSD1306_CMOD_J1() : SSD1306(new DSPI0(), 24, 7, 8, 30, 6) {_height = 32;}
};

class SSD1306_CMOD_J2 : public SSD1306_BB {
    public:
        SSD1306_CMOD_J2() : SSD1306_BB(20, 34, 22, 33, 17, 32, 36) {_height = 32;}
};

#endif

#if defined(_BOARD_PRO_MX7_) || defined(_BOARD_PRO_MX4_) || defined (_BOARD_PRO_MX3_)

class SSD1306_PMOD_A : public SSD1306_BB {
    public:
        SSD1306_PMOD_A() : SSD1306_BB(1, 3, 0, 4, 7, 6, 5) {_height = 32;}
};

class SSD1306_PMOD_B : public SSD1306_BB {
    public:
        SSD1306_PMOD_B() : SSD1306_BB(9, 11, 8, 12, 15, 14, 13) {_height = 32;}
};

class SSD1306_PMOD_C : public SSD1306_BB {
    public:
        SSD1306_PMOD_C() : SSD1306_BB(17, 19, 16, 20, 23, 22, 21) {_height = 32;}
};

class SSD1306_PMOD_D : public SSD1306 {
    public:
        SSD1306_PMOD_D() : SSD1306(new DSPI0(), 24, 28, 31, 30, 29) {_height = 32;}
};

class SSD1306_PMOD_E : public SSD1306 {
    public:
        SSD1306_PMOD_E() : SSD1306(new DSPI1(), 32, 36, 39, 38, 37) {_height = 32;}
};

class SSD1306_PMOD_F : public SSD1306 {
    public:
        SSD1306_PMOD_F() : SSD1306(new DSPI2(), 40, 44, 47, 46, 45) {_height = 32;}
};

#endif

class SSD1306_IOSHIELD : public SSD1306 {
    public:
        SSD1306_IOSHIELD() : SSD1306(new DSPI0(), 41, 39, 38, 40, 10) {_height = 32;}
};


class CLICK_OLED_B : public SSD1306 {
    public:
        CLICK_OLED_B(DSPI *spi, uint8_t cs, uint8_t dc, uint8_t reset) : SSD1306(spi, cs, dc, NOT_A_PIN, NOT_A_PIN, reset) { _width = 96; _height = 39; _offset_y = 64 - 39; _offset_x = 128 - 96; }
        CLICK_OLED_B(DSPI &spi, uint8_t cs, uint8_t dc, uint8_t reset) : SSD1306(&spi, cs, dc, NOT_A_PIN, NOT_A_PIN, reset) { _width = 96; _height = 39; _offset_y = 64 - 39; _offset_x = 128 - 96; }
};
