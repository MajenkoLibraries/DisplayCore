#ifndef _KS0108H_
#define _KS0108H_

#include <DisplayCore.h>

#define GLCD_CMD_OFF         0b00111110
#define GLCD_CMD_ON          0b00111111
#define GLCD_CMD_SET_Y       0b01000000
#define GLCD_CMD_SET_PAGE    0b10111000
#define GLCD_CMD_START       0b11000000

#define GLCD_STAT_BUSY   0b10000000
#define GLCD_STAT_ONOFF  0b00100000
#define GLCD_STAT_RESET  0b00010000

#define C2B(X, Y) (((Y) << 6) + (X))

// A single KS0108 chip on the PMP.

class KS0108 : public DisplayCore {

    private:
        uint8_t _buffer[8 * 64];
        uint32_t _reg;
        uint32_t _data;
        int _buffered;

        void setPage(uint8_t page);
        void setY(uint8_t y);

        virtual void command(uint8_t c);
        virtual void data(uint8_t d);

	public:
        // Provide the two PMP addresses for the reg and data ports
		KS0108(uint32_t reg, uint32_t data) : _buffered(0), _reg(reg), _data(data) {}
        KS0108() {}

        virtual void initializeDevice();
        virtual void displayInit();

        void setPixel(int16_t x, int16_t y, uint16_t color);

        void startBuffer();
        void endBuffer();

        void setRotation(uint8_t r) {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean b) {}

        uint16_t getWidth();
        uint16_t getHeight();
};

class KS0108_2 : public DisplayCore {

    private:
        KS0108 _lcd1;
        KS0108 _lcd2;

	public:
        // Provide the two PMP addresses for the reg and data ports
		KS0108_2(uint32_t reg1, uint32_t data1, uint32_t reg2, uint32_t data2) : _lcd1(reg1, data1), _lcd2(reg2, data2) {}

        void initializeDevice();

        void setPixel(int16_t x, int16_t y, uint16_t color);

        void startBuffer();
        void endBuffer();

        void setRotation(uint8_t r) {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean b) {}

        uint16_t getWidth();
        uint16_t getHeight();
};

class KS0108_BB : public KS0108 {
    private:
        uint8_t _rs;
        uint8_t _rw;
        uint8_t _e;
        uint8_t _cs;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _d4;
        uint8_t _d5;
        uint8_t _d6;
        uint8_t _d7;

        p32_ioport *_port_rs;
        p32_ioport *_port_rw;
        p32_ioport *_port_e;
        p32_ioport *_port_cs;
        p32_ioport *_port_d0;
        p32_ioport *_port_d1;
        p32_ioport *_port_d2;
        p32_ioport *_port_d3;
        p32_ioport *_port_d4;
        p32_ioport *_port_d5;
        p32_ioport *_port_d6;
        p32_ioport *_port_d7;

        uint32_t _mask_rs;
        uint32_t _mask_rw;
        uint32_t _mask_e;
        uint32_t _mask_cs;
        uint32_t _mask_d0;
        uint32_t _mask_d1;
        uint32_t _mask_d2;
        uint32_t _mask_d3;
        uint32_t _mask_d4;
        uint32_t _mask_d5;
        uint32_t _mask_d6;
        uint32_t _mask_d7;

        void command(uint8_t c);
        void data(uint8_t d);

    public:
        KS0108_BB(
            uint8_t rs, uint8_t rw, uint8_t e, uint8_t cs,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7
        ) : _rs(rs), _rw(rw), _e(e), _cs(cs),
            _d0(d0), _d1(d1), _d2(d2), _d3(d3),
            _d4(d4), _d5(d5), _d6(d6), _d7(d7)
        {}

        void initializeDevice();
};

class KS0108_BB2 : public DisplayCore {

    private:
        KS0108_BB _lcd1;
        KS0108_BB _lcd2;

	public:
        // Provide the two PMP addresses for the reg and data ports
        KS0108_BB2(
            uint8_t rs, uint8_t rw, uint8_t e, uint8_t cs1, uint8_t cs2,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7
        ) : _lcd1(rs, rw, e, cs1, d0, d1, d2, d3, d4, d5, d6, d7),
            _lcd2(rs, rw, e, cs2, d0, d1, d2, d3, d4, d5, d6, d7)
        {}

        void initializeDevice();

        void setPixel(int16_t x, int16_t y, uint16_t color);

        void startBuffer();
        void endBuffer();

        void setRotation(uint8_t r) {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean b) {}

        uint16_t getWidth();
        uint16_t getHeight();
};
#endif
