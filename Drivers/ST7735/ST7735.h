#ifndef _ST7735_H_
#define _ST7735_H_

#include <DisplayCore.h>
#include <DSPI.h>

class ST7735 : public DisplayCore {

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
		void streamCommands(uint8_t *cmdlist);
		uint8_t colstart, rowstart;
        void command(uint8_t);
        void data(uint8_t);

        uint32_t _linebuffer[2][160];
        uint8_t _xferline;
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _variant;

};

#endif
