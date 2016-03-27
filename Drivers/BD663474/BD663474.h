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
        static const int Width      = 240;
        static const int Height     = 320;

		BD663474(DSPI *dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(dspi), _pin_cs(cs), _pin_rs(rs), _pin_reset(reset) {}
		BD663474(DSPI &dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(&dspi), _pin_cs(cs), _pin_rs(rs), _pin_reset(reset) {}
		BD663474() {}

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
        void startDisplay();

        virtual void initializeDevice();
        virtual void command(uint16_t);
        virtual void data(uint16_t);

};

#endif
