#ifndef BD663474_H_
#define BD663474_H_

#include <DisplayCore.h>
#include <DSPI.h>

class BD663474 : public DisplayCore {
    private:
        DSPI *_dspi;
        uint8_t _pin_cs;
        uint8_t _pin_rs;
        uint8_t _pin_reset;

        p32_ioport *_port_cs;
        p32_ioport *_port_rs;

        uint32_t _mask_cs;
        uint32_t _mask_rs;

	public:
        static const uint16_t Width      = 240;
        static const uint16_t Height     = 320;

		BD663474(DSPI *dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(dspi), _pin_cs(cs), _pin_rs(rs), _pin_reset(reset) {}
		BD663474(DSPI &dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(&dspi), _pin_cs(cs), _pin_rs(rs), _pin_reset(reset) {}
		BD663474() {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented
        void startDisplay();

        virtual void initializeDevice();
        virtual void command(uint16_t);
        virtual void data(uint16_t);

};

#endif
