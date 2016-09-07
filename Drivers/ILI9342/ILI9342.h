#ifndef _ILI9342_H
#define _ILI9342_H

#include <DisplayCore.h>
#include <DSPI.h>

#ifdef __PIC32MZ__
#define _PMP_IRQ _PMP_VECTOR
#endif

class ILI9342 : public DisplayCore {
    protected:

        const uint8_t ILI9342_SOFTRESET        = 0x01;
        const uint8_t ILI9342_SLEEPIN          = 0x10;
        const uint8_t ILI9342_SLEEPOUT         = 0x11;
        const uint8_t ILI9342_NORMALDISP       = 0x13;
        const uint8_t ILI9342_INVERTOFF        = 0x20;
        const uint8_t ILI9342_INVERTON         = 0x21;
        const uint8_t ILI9342_GAMMASET         = 0x26;
        const uint8_t ILI9342_DISPLAYOFF       = 0x28;
        const uint8_t ILI9342_DISPLAYON        = 0x29;
        const uint8_t ILI9342_COLADDRSET       = 0x2A;
        const uint8_t ILI9342_PAGEADDRSET      = 0x2B;
        const uint8_t ILI9342_MEMORYWRITE      = 0x2C;
        const uint8_t ILI9342_PIXELFORMAT      = 0x3A;
        const uint8_t ILI9342_FRAMECONTROL     = 0xB1;
        const uint8_t ILI9342_DISPLAYFUNC      = 0xB6;
        const uint8_t ILI9342_ENTRYMODE        = 0xB7;
        const uint8_t ILI9342_POWERCONTROL1    = 0xC0;
        const uint8_t ILI9342_POWERCONTROL2    = 0xC1;
        const uint8_t ILI9342_VCOMCONTROL1     = 0xC5;
        const uint8_t ILI9342_VCOMCONTROL2     = 0xC7;
        const uint8_t ILI9342_MEMCONTROL       = 0x36;
        const uint8_t ILI9342_MADCTL           = 0x36;

        const uint8_t ILI9342_MADCTL_MY        = 0x80;
        const uint8_t ILI9342_MADCTL_MX        = 0x40;
        const uint8_t ILI9342_MADCTL_MV        = 0x20;
        const uint8_t ILI9342_MADCTL_ML        = 0x10;
        const uint8_t ILI9342_MADCTL_RGB       = 0x00;
        const uint8_t ILI9342_MADCTL_BGR       = 0x08;
        const uint8_t ILI9342_MADCTL_MH        = 0x04;

        p32_ioport *_d0_port;
        p32_ioport *_d1_port;
        p32_ioport *_d2_port;
        p32_ioport *_d3_port;
        p32_ioport *_d4_port;
        p32_ioport *_d5_port;
        p32_ioport *_d6_port;
        p32_ioport *_d7_port;
        p32_ioport *_d8_port;
        p32_ioport *_d9_port;
        p32_ioport *_d10_port;
        p32_ioport *_d11_port;
        p32_ioport *_d12_port;
        p32_ioport *_d13_port;
        p32_ioport *_d14_port;
        p32_ioport *_d15_port;

        p32_ioport *_cs_port;
        p32_ioport *_wr_port;
        p32_ioport *_rd_port;
        p32_ioport *_rs_port;

        uint32_t _d0_mask;
        uint32_t _d1_mask;
        uint32_t _d2_mask;
        uint32_t _d3_mask;
        uint32_t _d4_mask;
        uint32_t _d5_mask;
        uint32_t _d6_mask;
        uint32_t _d7_mask;
        uint32_t _d8_mask;
        uint32_t _d9_mask;
        uint32_t _d10_mask;
        uint32_t _d11_mask;
        uint32_t _d12_mask;
        uint32_t _d13_mask;
        uint32_t _d14_mask;
        uint32_t _d15_mask;

        uint32_t _cs_mask;
        uint32_t _wr_mask;
        uint32_t _rd_mask;
        uint32_t _rs_mask;

        uint8_t _rs_pin;
        uint8_t _wr_pin;
        uint8_t _rd_pin;
        uint8_t _cs_pin;
        uint8_t _reset_pin;

        uint8_t _d0_pin;
        uint8_t _d1_pin;
        uint8_t _d2_pin;
        uint8_t _d3_pin;
        uint8_t _d4_pin;
        uint8_t _d5_pin;
        uint8_t _d6_pin;
        uint8_t _d7_pin;
        uint8_t _d8_pin;
        uint8_t _d9_pin;
        uint8_t _d10_pin;
        uint8_t _d11_pin;
        uint8_t _d12_pin;
        uint8_t _d13_pin;
        uint8_t _d14_pin;
        uint8_t _d15_pin;

        void configureScreen();


	public:
        static const int Width      = 320;
        static const int Height     = 240;

        ILI9342() {}

		ILI9342(uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : 
            _rs_pin(rs), _wr_pin(wr), _rd_pin(rd), _cs_pin(cs), _reset_pin(reset),
            _d0_pin(d0), _d1_pin(d1), _d2_pin(d2), _d3_pin(d3),
            _d4_pin(d4), _d5_pin(d5), _d6_pin(d6), _d7_pin(d7),
            _d8_pin(255), _d9_pin(255), _d10_pin(255), _d11_pin(255),
            _d12_pin(255), _d13_pin(255), _d14_pin(255), _d15_pin(255)
             {}
        
		ILI9342(uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
                uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15) : 
            _rs_pin(rs), _wr_pin(wr), _rd_pin(rd), _cs_pin(cs), _reset_pin(reset),
            _d0_pin(d0), _d1_pin(d1), _d2_pin(d2), _d3_pin(d3),
            _d4_pin(d4), _d5_pin(d5), _d6_pin(d6), _d7_pin(d7),
            _d8_pin(d8), _d9_pin(d9), _d10_pin(d10), _d11_pin(d11),
            _d12_pin(d12), _d13_pin(d13), _d14_pin(d14), _d15_pin(d15)
             {}
        
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
        virtual void windowData(color_t *, int);
        virtual void closeWindow();

        virtual void initializeDevice();

        virtual void data(uint16_t);
        virtual void command(uint16_t);

};

class ILI9342_PMP : public ILI9342 {
    private:
        virtual void command(uint16_t d);
        virtual void data(uint16_t d);

    public:
        static const int Width      = 320;
        static const int Height     = 240;

        ILI9342_PMP(uint8_t cs, uint8_t reset);
        virtual void initializeDevice();
        virtual void windowData(color_t *, int);
        virtual void closeWindow();
};

#endif
