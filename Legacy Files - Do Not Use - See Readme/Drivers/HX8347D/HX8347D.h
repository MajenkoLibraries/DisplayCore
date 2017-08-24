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
        static const int Width      = 240;
        static const int Height     = 320;


		HX8347D(DSPI &spi, int dc, int cs) : DisplayCore(), _spi(&spi), _dc(dc), _cs(cs) {}

		void setAddrWindow(int x0, int y0, int x1, int y1);
		void setAddrWindowRead(int x0, int y0, int x1, int y1);
        void fillScreen(color_t color);
        void setPixel(int x, int y, color_t color);
        void drawVerticalLine(int x, int y, int h, color_t color);
        void drawHorizontalLine(int x, int y, int w, color_t color);
        void fillRectangle(int x, int y, int w, int h, color_t color);
        void setRotation(int r);
        void invertDisplay(boolean i);
        void displayOn();  
        void displayOff();  

        void initializeDevice();

        void openWindow(int x0, int y0, int x1, int y1);
        void windowData(color_t d);
        void windowData(color_t *d, uint32_t l);
        void closeWindow();

        void writeCommand(uint8_t);
        void writeData(uint8_t);
        void setRegister(uint8_t reg, uint8_t val);
		
};

#endif
