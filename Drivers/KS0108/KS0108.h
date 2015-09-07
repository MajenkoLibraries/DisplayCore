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

        void command(uint8_t c);
        void data(uint8_t d);

	public:
        // Provide the two PMP addresses for the reg and data ports
		KS0108(uint32_t reg, uint32_t data) : _buffered(0), _reg(reg), _data(data) {}

        void initializeDevice();
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

#endif

