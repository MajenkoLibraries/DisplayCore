#ifndef _ST7735_H
#define _ST7735_H

#include <DisplayCore.h>
#include <DSPI.h>

class ST7735 : public DisplayCore {
    private:
        static const uint8_t ST7735_NOP     = 0x00;
        static const uint8_t ST7735_SWRESET = 0x01;
        static const uint8_t ST7735_RDDID   = 0x04;
        static const uint8_t ST7735_RDDST   = 0x09;

        static const uint8_t ST7735_SLPIN   = 0x10;
        static const uint8_t ST7735_SLPOUT  = 0x11;
        static const uint8_t ST7735_PTLON   = 0x12;
        static const uint8_t ST7735_NORON   = 0x13;

        static const uint8_t ST7735_INVOFF  = 0x20;
        static const uint8_t ST7735_INVON   = 0x21;
        static const uint8_t ST7735_DISPOFF = 0x28;
        static const uint8_t ST7735_DISPON  = 0x29;
        static const uint8_t ST7735_CASET   = 0x2A;
        static const uint8_t ST7735_RASET   = 0x2B;
        static const uint8_t ST7735_RAMWR   = 0x2C;
        static const uint8_t ST7735_RAMRD   = 0x2E;

        static const uint8_t ST7735_PTLAR   = 0x30;
        static const uint8_t ST7735_COLMOD  = 0x3A;
        static const uint8_t ST7735_MADCTL  = 0x36;

        static const uint8_t ST7735_FRMCTR1 = 0xB1;
        static const uint8_t ST7735_FRMCTR2 = 0xB2;
        static const uint8_t ST7735_FRMCTR3 = 0xB3;
        static const uint8_t ST7735_INVCTR  = 0xB4;
        static const uint8_t ST7735_DISSET5 = 0xB6;

        static const uint8_t ST7735_PWCTR1  = 0xC0;
        static const uint8_t ST7735_PWCTR2  = 0xC1;
        static const uint8_t ST7735_PWCTR3  = 0xC2;
        static const uint8_t ST7735_PWCTR4  = 0xC3;
        static const uint8_t ST7735_PWCTR5  = 0xC4;
        static const uint8_t ST7735_VMCTR1  = 0xC5;

        static const uint8_t ST7735_RDID1   = 0xDA;
        static const uint8_t ST7735_RDID2   = 0xDB;
        static const uint8_t ST7735_RDID3   = 0xDC;
        static const uint8_t ST7735_RDID4   = 0xDD;

        static const uint8_t ST7735_PWCTR6  = 0xFC;

        static const uint8_t ST7735_GMCTRP1 = 0xE0;
        static const uint8_t ST7735_GMCTRN1 = 0xE1;

        static const uint8_t DELAY = 0x80;

        static const uint8_t MADCTL_MY  = 0x80;
        static const uint8_t MADCTL_MX  = 0x40;
        static const uint8_t MADCTL_MV  = 0x20;
        static const uint8_t MADCTL_ML  = 0x10;
        static const uint8_t MADCTL_RGB = 0x08;
        static const uint8_t MADCTL_MH  = 0x04;

        static const uint8_t Bcmd[];
        static const uint8_t Rcmd1[];
        static const uint8_t Rcmd2red[];
        static const uint8_t Rcmd2green[];
        static const uint8_t Rcmd3[];
        static const uint8_t Gcmd[];



	public:
        /*! Adafruit screen with a green tab */
        static const uint8_t GreenTab   = 0x00;
        /*! Adafruit screen with a red tab */
        static const uint8_t RedTab     = 0x01;
        /*! Adafruit screen with a black tab */
        static const uint8_t BlackTab   = 0x02;
        /*! Adafruit "Type B" screen */
        static const uint8_t TypeB      = 0x03;
        /*! The native size of the screen is 128 pixels wide */
        static const uint8_t Width      = 128;
        /*! The native size of the screen is 160 pixels high */
        static const uint8_t Height     = 160;

		ST7735(DSPI *spi, uint8_t cs, uint8_t dc, uint8_t variant) : _spi(spi), _cs(cs), _dc(dc), _variant(variant) {}
		ST7735(DSPI &spi, uint8_t cs, uint8_t dc, uint8_t variant) : _spi(&spi), _cs(cs), _dc(dc), _variant(variant) {}

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

	private:
		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void streamCommands(const uint8_t *cmdlist);
		uint8_t colstart, rowstart;
        void command(uint8_t);
        void data(uint8_t);

        uint32_t _linebuffer[2][160];
        uint8_t _xferline;
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _variant;
        p32_ioport *_csp;
        p32_ioport *_dcp;
        uint32_t _csb;
        uint32_t _dcb;

};

#endif
