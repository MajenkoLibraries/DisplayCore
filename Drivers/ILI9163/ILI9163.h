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
        static const int Width      = 128;
        static const int Height     = 128;

        ILI9163(DSPI *dspi, uint8_t cs, uint8_t rs, uint8_t reset) : _dspi(dspi), pin_cs(cs), pin_rs(rs), pin_reset(reset) {}

        ILI9163() {}

		void setAddrWindow(int x0, int y0, int x1, int y1);
        void setPixel(int x, int y, color_t color);
        void drawVerticalLine(int x, int y, int h, color_t color);
        void drawHorizontalLine(int x, int y, int w, color_t color);
        void fillRectangle(int x, int y, int w, int h, color_t color);
        void setRotation(int r);
        void invertDisplay(boolean i);
        void displayOn();
        void displayOff();
        void openWindow(int, int, int, int);
        void windowData(color_t);
        void windowData(color_t *, int);
        void closeWindow();

        void startDisplay();

        virtual void initializeDevice();
        virtual void data(uint16_t);
        virtual void command(uint16_t);
};
#endif
