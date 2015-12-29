#ifndef _HX8347D_H
#define _HX8347D_H

#include <DisplayCore.h>
#include <DSPI.h>

class HX8347D : public DisplayCore
{
    private:
        DSPI *_spi;
        int _dc;
        int _cs;

        p32_ioport *_cs_port;
        p32_ioport *_dc_port;
        uint32_t _cs_mask;
        uint32_t _dc_mask;

	public:
        static const uint16_t Width      = 240;
        static const uint16_t Height     = 320;


		HX8347D(DSPI &spi, int dc, int cs) : DisplayCore(), _spi(&spi), _dc(dc), _cs(cs) {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void setAddrWindowRead(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn();  
        void displayOff();  

        void initializeDevice();

        void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void windowData(uint16_t d);
        void windowData(uint16_t *d, uint32_t l);
        void closeWindow();

        void writeCommand(uint8_t);
        void writeData(uint8_t);
        void setRegister(uint8_t reg, uint8_t val);
		
};

#endif
