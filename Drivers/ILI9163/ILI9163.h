#ifndef _ILI9163_H
#define _ILI9163_H

#include <DisplayCore.h>
#include <DSPI.h>

class ILI9163 : public DisplayCore {
    private:
        uint8_t pin_rs;
        uint8_t pin_cs;
        uint8_t pin_reset;
        DSPI *_dspi;

        p32_ioport *port_rs;
        p32_ioport *port_cs;

        uint32_t mask_rs;
        uint32_t mask_cs;

    public:
        static const uint16_t Width      = 128;
        static const uint16_t Height     = 128;

        ILI9163(DSPI *dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(dspi), pin_cs(cs), pin_rs(rs), pin_reset(reset) {}

        ILI9163() {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn();
        void displayOff();
        void openWindow(uint16_t, uint16_t, uint16_t, uint16_t);
        void windowData(uint16_t);
        void windowData(uint16_t *, uint32_t);
        void closeWindow();

        void startDisplay();

        virtual void initializeDevice();
        virtual void data(uint16_t);
        virtual void command(uint16_t);
};
#endif
