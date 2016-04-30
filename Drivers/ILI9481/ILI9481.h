#ifndef _ILI9481_H
#define _ILI9481_H

#include <DisplayCore.h>

class ILI9481 : public DisplayCore {
    private:
        uint8_t pin_rs;
        uint8_t pin_rd;
        uint8_t pin_wr;
        uint8_t pin_cs;
        uint8_t pin_reset;
        uint8_t pin_d0;
        uint8_t pin_d1;
        uint8_t pin_d2;
        uint8_t pin_d3;
        uint8_t pin_d4;
        uint8_t pin_d5;
        uint8_t pin_d6;
        uint8_t pin_d7;
        uint8_t pin_d8;
        uint8_t pin_d9;
        uint8_t pin_d10;
        uint8_t pin_d11;
        uint8_t pin_d12;
        uint8_t pin_d13;
        uint8_t pin_d14;
        uint8_t pin_d15;

        p32_ioport *port_rs;
        p32_ioport *port_rd;
        p32_ioport *port_wr;
        p32_ioport *port_d0;
        p32_ioport *port_d1;
        p32_ioport *port_d2;
        p32_ioport *port_d3;
        p32_ioport *port_d4;
        p32_ioport *port_d5;
        p32_ioport *port_d6;
        p32_ioport *port_d7;
        p32_ioport *port_d8;
        p32_ioport *port_d9;
        p32_ioport *port_d10;
        p32_ioport *port_d11;
        p32_ioport *port_d12;
        p32_ioport *port_d13;
        p32_ioport *port_d14;
        p32_ioport *port_d15;

        uint32_t mask_rs;
        uint32_t mask_rd;
        uint32_t mask_wr;
        uint32_t mask_d0;
        uint32_t mask_d1;
        uint32_t mask_d2;
        uint32_t mask_d3;
        uint32_t mask_d4;
        uint32_t mask_d5;
        uint32_t mask_d6;
        uint32_t mask_d7;
        uint32_t mask_d8;
        uint32_t mask_d9;
        uint32_t mask_d10;
        uint32_t mask_d11;
        uint32_t mask_d12;
        uint32_t mask_d13;
        uint32_t mask_d14;
        uint32_t mask_d15;

        uint8_t bus_width;

    public:
        static const int Width      = 320;
        static const int Height     = 480;

        ILI9481(
            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15
        );

        ILI9481(
            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7
        );

        ILI9481() {}

		void setAddrWindow(int x0, int y0, int x1, int y1);
        void fillScreen(color_t color);
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

        virtual color_t colorAt(int x, int y);

        void startDisplay();

        virtual void initializeDevice();
        virtual void data8(uint8_t);
        virtual void data16(uint16_t);
        virtual void command(uint16_t);
        virtual uint16_t read(boolean cont = false);
        virtual void getRectangle(int x, int y, int w, int h, color_t *buf);
};

#ifdef _PMMODE_MODE16_POSITION
class ILI9481_PMP : public ILI9481 {
    private:

        uint8_t pin_reset;

    public:
        ILI9481_PMP(uint8_t res) : pin_reset(res) {}

        void initializeDevice();
        void data8(uint8_t);
        void data16(uint16_t);
        void command(uint16_t);
        uint16_t read(boolean cont = false);
};
#endif

#endif
