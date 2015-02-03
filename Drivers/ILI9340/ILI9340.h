#ifndef _ILI9340_H_
#define _ILI9340_H_

#include <DisplayCore.h>
#include <DSPI.h>

class ILI9340 : public DisplayCore {
    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
        p32_ioport *_csp;
        p32_ioport *_dcp;
        uint32_t _csb;
        uint32_t _dcb;

	public:
        static const uint16_t Width      = 240;
        static const uint16_t Height     = 320;

		ILI9340(DSPI *spi, uint8_t cs, uint8_t dc) : _spi(spi), _cs(cs), _dc(dc) {}
		ILI9340(DSPI &spi, uint8_t cs, uint8_t dc) : _spi(&spi), _cs(cs), _dc(dc) {}

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
        void openWindow(uint16_t, uint16_t, uint16_t, uint16_t);
        void windowData(uint16_t);
        void windowData(uint16_t *, uint32_t);
        void closeWindow();

        void initializeDevice();

        void data(uint8_t);
        void command(uint8_t);

};

#endif
