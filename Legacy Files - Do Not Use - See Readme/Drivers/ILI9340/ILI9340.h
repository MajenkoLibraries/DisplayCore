#ifndef _ILI9340_H
#define _ILI9340_H

#include <DisplayCore.h>
#include <DSPI.h>

class ILI9340 : public DisplayCore {
    private:
        static const uint8_t ILI9340_NOP = 0x00;
        static const uint8_t ILI9340_SWRESET = 0x01;
        static const uint8_t ILI9340_RDDID = 0x04;
        static const uint8_t ILI9340_RDDST = 0x09;

        static const uint8_t ILI9340_SLPIN = 0x10;
        static const uint8_t ILI9340_SLPOUT = 0x11;
        static const uint8_t ILI9340_PTLON = 0x12;
        static const uint8_t ILI9340_NORON = 0x13;

        static const uint8_t ILI9340_RDMODE = 0x0A;
        static const uint8_t ILI9340_RDMADCTL = 0x0B;
        static const uint8_t ILI9340_RDPIXFMT = 0x0C;
        static const uint8_t ILI9340_RDIMGFMT = 0x0A;
        static const uint8_t ILI9340_RDSELFDIAG = 0x0F;

        static const uint8_t ILI9340_INVOFF = 0x20;
        static const uint8_t ILI9340_INVON = 0x21;
        static const uint8_t ILI9340_GAMMASET = 0x26;
        static const uint8_t ILI9340_DISPOFF = 0x28;
        static const uint8_t ILI9340_DISPON = 0x29;

        static const uint8_t ILI9340_CASET = 0x2A;
        static const uint8_t ILI9340_PASET = 0x2B;
        static const uint8_t ILI9340_RAMWR = 0x2C;
        static const uint8_t ILI9340_RAMRD = 0x2E;

        static const uint8_t ILI9340_PTLAR = 0x30;
        static const uint8_t ILI9340_MADCTL = 0x36;

        static const uint8_t ILI9340_MADCTL_MY = 0x80;
        static const uint8_t ILI9340_MADCTL_MX = 0x40;
        static const uint8_t ILI9340_MADCTL_MV = 0x20;
        static const uint8_t ILI9340_MADCTL_ML = 0x10;
        static const uint8_t ILI9340_MADCTL_RGB = 0x00;
        static const uint8_t ILI9340_MADCTL_BGR = 0x08;
        static const uint8_t ILI9340_MADCTL_MH = 0x04;

        static const uint8_t ILI9340_PIXFMT = 0x3A;

        static const uint8_t ILI9340_FRMCTR1 = 0xB1;
        static const uint8_t ILI9340_FRMCTR2 = 0xB2;
        static const uint8_t ILI9340_FRMCTR3 = 0xB3;
        static const uint8_t ILI9340_INVCTR = 0xB4;
        static const uint8_t ILI9340_DFUNCTR = 0xB6;

        static const uint8_t ILI9340_PWCTR1 = 0xC0;
        static const uint8_t ILI9340_PWCTR2 = 0xC1;
        static const uint8_t ILI9340_PWCTR3 = 0xC2;
        static const uint8_t ILI9340_PWCTR4 = 0xC3;
        static const uint8_t ILI9340_PWCTR5 = 0xC4;
        static const uint8_t ILI9340_VMCTR1 = 0xC5;
        static const uint8_t ILI9340_VMCTR2 = 0xC7;

        static const uint8_t ILI9340_RDID1 = 0xDA;
        static const uint8_t ILI9340_RDID2 = 0xDB;
        static const uint8_t ILI9340_RDID3 = 0xDC;
        static const uint8_t ILI9340_RDID4 = 0xDD;

        static const uint8_t ILI9340_GMCTRP1 = 0xE0;
        static const uint8_t ILI9340_GMCTRN1 = 0xE1;


        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _reset;
        p32_ioport *_csp;
        p32_ioport *_dcp;
        uint32_t _csb;
        uint32_t _dcb;

	public:
        static const int Width      = 240;
        static const int Height     = 320;

		ILI9340(DSPI *spi, uint8_t cs, uint8_t dc, uint8_t reset) : _spi(spi), _cs(cs), _dc(dc), _reset(reset) {}
		ILI9340(DSPI &spi, uint8_t cs, uint8_t dc, uint8_t reset) : _spi(&spi), _cs(cs), _dc(dc), _reset(reset) {}

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

        void data(uint8_t);
        void command(uint8_t);

};

#endif
