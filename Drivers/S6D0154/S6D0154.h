#ifndef _S6D0154_H
#define _S6D0154_H

#include <DisplayCore.h>
#include <DSPI.h>

class S6D0154 : public DisplayCore {
    private:
        p32_ioport *_d0_port;
        p32_ioport *_d1_port;
        p32_ioport *_d2_port;
        p32_ioport *_d3_port;
        p32_ioport *_d4_port;
        p32_ioport *_d5_port;
        p32_ioport *_d6_port;
        p32_ioport *_d7_port;

        p32_ioport *_cs_port;
        p32_ioport *_wr_port;
        p32_ioport *_rd_port;
        p32_ioport *_rs_port;

        uint32_t _d0_mask;
        uint32_t _d1_mask;
        uint32_t _d2_mask;
        uint32_t _d3_mask;
        uint32_t _d4_mask;
        uint32_t _d5_mask;
        uint32_t _d6_mask;
        uint32_t _d7_mask;

        uint32_t _cs_mask;
        uint32_t _wr_mask;
        uint32_t _rd_mask;
        uint32_t _rs_mask;

        uint8_t _rs_pin;
        uint8_t _wr_pin;
        uint8_t _rd_pin;
        uint8_t _cs_pin;
        uint8_t _reset_pin;
        uint8_t _d0_pin;
        uint8_t _d1_pin;
        uint8_t _d2_pin;
        uint8_t _d3_pin;
        uint8_t _d4_pin;
        uint8_t _d5_pin;
        uint8_t _d6_pin;
        uint8_t _d7_pin;

        void data(uint8_t, bool cont = false);
        void command(uint8_t, bool cont = false);
        uint8_t read(bool cont = false);

        void regset(uint8_t r, uint16_t v) {
            command(r, true);
            data(v >> 8, true);
            data(v, false);
        }


	public:
        static const int Width      = 240;
        static const int Height     = 320;

		S6D0154(uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : 
            _rs_pin(rs), _wr_pin(wr), _rd_pin(rd), _cs_pin(cs), _reset_pin(reset),
            _d0_pin(d0), _d1_pin(d1), _d2_pin(d2), _d3_pin(d3),
            _d4_pin(d4), _d5_pin(d5), _d6_pin(d6), _d7_pin(d7) {}
        
		void setAddrWindow(int x0, int y0, int x1, int y1);
        void fillScreen(color_t color);
        void setPixel(int x, int y, color_t color);
        void drawVerticalLine(int x, int y, int h, color_t color);
        void drawHorizontalLine(int x, int y, int w, color_t color);
        void fillRectangle(int x, int y, int w, int h, color_t color);
        void setRotation(int r);
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented
        void openWindow(int, int, int, int);
        void windowData(color_t);
        void windowData(color_t *, int);
        void closeWindow();

        void initializeDevice();

        uint32_t readIdCode();

};

#endif
