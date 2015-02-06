#ifndef _LM6800_H_
#define _LM6800_H_

#include <DisplayCore.h>

#define GLCD_CMD_OFF         0b00111110
#define GLCD_CMD_ON          0b00111111
#define GLCD_CMD_SET_Y       0b01000000
#define GLCD_CMD_SET_PAGE    0b10111000
#define GLCD_CMD_START       0b11000000

#define GLCD_STAT_BUSY   0b10000000
#define GLCD_STAT_ONOFF  0b00100000
#define GLCD_STAT_RESET  0b00010000

class LM6800 : public DisplayCore {

    private:
        p32_ioport *_port_d0;
        p32_ioport *_port_d1;
        p32_ioport *_port_d2;
        p32_ioport *_port_d3;
        p32_ioport *_port_d4;
        p32_ioport *_port_d5;
        p32_ioport *_port_d6;
        p32_ioport *_port_d7;

        p32_ioport *_port_csa;
        p32_ioport *_port_csb;
        p32_ioport *_port_csc;

        p32_ioport *_port_e;
        p32_ioport *_port_rs;
        p32_ioport *_port_rw;

        uint32_t _mask_d0;
        uint32_t _mask_d1;
        uint32_t _mask_d2;
        uint32_t _mask_d3;
        uint32_t _mask_d4;
        uint32_t _mask_d5;
        uint32_t _mask_d6;
        uint32_t _mask_d7;

        uint32_t _mask_csa;
        uint32_t _mask_csb;
        uint32_t _mask_csc;

        uint32_t _mask_e;
        uint32_t _mask_rs;
        uint32_t _mask_rw;

        uint8_t _pin_d0;
        uint8_t _pin_d1;
        uint8_t _pin_d2;
        uint8_t _pin_d3;
        uint8_t _pin_d4;
        uint8_t _pin_d5;
        uint8_t _pin_d6;
        uint8_t _pin_d7;

        uint8_t _pin_csa;
        uint8_t _pin_csb;
        uint8_t _pin_csc;

        uint8_t _pin_e;
        uint8_t _pin_rs;
        uint8_t _pin_rw;
        uint8_t _pin_reset;

        inline void command(uint8_t chip, uint8_t cmd) {
            (chip & 0x01) ? _port_csa->lat.set = _mask_csa : _port_csa->lat.clr = _mask_csa;
            (chip & 0x02) ? _port_csb->lat.set = _mask_csb : _port_csb->lat.clr = _mask_csb;
            _port_csc->lat.clr = _mask_csc;
            _port_rs->lat.clr = _mask_rs;
            _port_rw->lat.clr = _mask_rw;
            (cmd & 0x01) ? _port_d0->lat.set = _mask_d0 : _port_d0->lat.clr = _mask_d0;
            (cmd & 0x02) ? _port_d1->lat.set = _mask_d1 : _port_d1->lat.clr = _mask_d1;
            (cmd & 0x04) ? _port_d2->lat.set = _mask_d2 : _port_d2->lat.clr = _mask_d2;
            (cmd & 0x08) ? _port_d3->lat.set = _mask_d3 : _port_d3->lat.clr = _mask_d3;
            (cmd & 0x10) ? _port_d4->lat.set = _mask_d4 : _port_d4->lat.clr = _mask_d4;
            (cmd & 0x20) ? _port_d5->lat.set = _mask_d5 : _port_d5->lat.clr = _mask_d5;
            (cmd & 0x40) ? _port_d6->lat.set = _mask_d6 : _port_d6->lat.clr = _mask_d6;
            (cmd & 0x80) ? _port_d7->lat.set = _mask_d7 : _port_d7->lat.clr = _mask_d7;
            _port_e->lat.clr = _mask_e;
            delayMicroseconds(10);
            _port_e->lat.set = _mask_e;
            _port_csc->lat.set = _mask_csc;
        }

        inline void data(uint8_t chip, uint8_t cmd) {
            (chip & 0x01) ? _port_csa->lat.set = _mask_csa : _port_csa->lat.clr = _mask_csa;
            (chip & 0x02) ? _port_csb->lat.set = _mask_csb : _port_csb->lat.clr = _mask_csb;
            _port_csc->lat.clr = _mask_csc;
            _port_rs->lat.set = _mask_rs;
            _port_rw->lat.clr = _mask_rw;
            (cmd & 0x01) ? _port_d0->lat.set = _mask_d0 : _port_d0->lat.clr = _mask_d0;
            (cmd & 0x02) ? _port_d1->lat.set = _mask_d1 : _port_d1->lat.clr = _mask_d1;
            (cmd & 0x04) ? _port_d2->lat.set = _mask_d2 : _port_d2->lat.clr = _mask_d2;
            (cmd & 0x08) ? _port_d3->lat.set = _mask_d3 : _port_d3->lat.clr = _mask_d3;
            (cmd & 0x10) ? _port_d4->lat.set = _mask_d4 : _port_d4->lat.clr = _mask_d4;
            (cmd & 0x20) ? _port_d5->lat.set = _mask_d5 : _port_d5->lat.clr = _mask_d5;
            (cmd & 0x40) ? _port_d6->lat.set = _mask_d6 : _port_d6->lat.clr = _mask_d6;
            (cmd & 0x80) ? _port_d7->lat.set = _mask_d7 : _port_d7->lat.clr = _mask_d7;
            _port_e->lat.clr = _mask_e;
            delayMicroseconds(10);
            _port_e->lat.set = _mask_e;
            _port_csc->lat.set = _mask_csc;
        }

        void setPage(uint8_t chip, uint8_t page) {
            command(chip, GLCD_CMD_SET_PAGE | (page & 0x07));
        }

        void setY(uint8_t chip, uint8_t y) {
            command(chip, GLCD_CMD_SET_Y | (y & 63));
        }

        boolean _buffered;

	public:
        static const uint16_t Width = 256;
        static const uint16_t Height = 64;

        LM6800(
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t csa, uint8_t csb, uint8_t csc, uint8_t e,
            uint8_t rs, uint8_t rw, uint8_t reset = NULL); 

		void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void fillScreen(uint16_t color);
        void doSetPixel(int16_t x, int16_t y, uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

        void updateScreen();

        void startBuffer() { _buffered = true; }
        void endBuffer() { _buffered = false; updateScreen(); }

	protected:
		uint8_t colstart, rowstart;
        uint8_t _variant;


        uint8_t buffer[2048];
};

#endif
