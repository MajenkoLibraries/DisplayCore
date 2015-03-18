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

    public:
        static const uint16_t Width      = 320;
        static const uint16_t Height     = 480;

        ILI9481(
            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15
        );

        ILI9481() {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void fillScreen(uint16_t color);
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

        virtual uint16_t colorAt(int16_t x, int16_t y);

        void startDisplay();

        virtual void initializeDevice();
        virtual void data(uint16_t);
        virtual void command(uint16_t);
        virtual uint16_t read(boolean cont = false);
        virtual void getRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *buf);
};

class ILI9481_PMP : public ILI9481 {
    private:

        uint8_t pin_reset;

    public:
        ILI9481_PMP(uint8_t res) : pin_reset(res) {}

        void initializeDevice();
        void data(uint16_t);
        void command(uint16_t);
        uint16_t read(boolean cont = false);
};


#endif
