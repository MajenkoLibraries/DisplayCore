#ifndef _SSD1963_H
#define _SSD1963_H

#include <DisplayCore.h>

// the SSD1963 controller can be connected to the TFT screen with 18 or 24 data lines. So we need to tell the constructor which one.
static const uint8_t TFTBUS18 = 18;
static const uint8_t TFTBUS24 = 24;

class SSD1963 : public DisplayCore {

    private:

        static const uint8_t SSD1963_NOP                   = 0x00;
        static const uint8_t SSD1963_SoftReset             = 0x01;
        static const uint8_t SSD1963_GetPowerMode          = 0x0A;
        static const uint8_t SSD1963_GetAddressMode        = 0x0B;
        static const uint8_t SSD1963_GetDisplayMode        = 0x0D;
        static const uint8_t SSD1963_GetTearEffectsStatus  = 0x0E;
        static const uint8_t SSD1963_EnterSleepMode        = 0x10;
        static const uint8_t SSD1963_ExitSleepMode         = 0x11;
        static const uint8_t SSD1963_EnterPartialMode      = 0x12;
        static const uint8_t SSD1963_EnterNormalMode       = 0x13;
        static const uint8_t SSD1963_ExitInvertMode        = 0x20;
        static const uint8_t SSD1963_EnterInvertMode       = 0x21;
        static const uint8_t SSD1963_SetGammaCurve         = 0x26;
        static const uint8_t SSD1963_SetDisplayOff         = 0x28;
        static const uint8_t SSD1963_SetDisplayOn          = 0x29;
        static const uint8_t SSD1963_SetColumnAddress      = 0x2A;
        static const uint8_t SSD1963_SetPageAddress        = 0x2B;
        static const uint8_t SSD1963_WriteMemoryStart      = 0x2C;
        static const uint8_t SSD1963_ReadMemoryStart       = 0x2E;
        static const uint8_t SSD1963_SetPartialArea        = 0x30;
        static const uint8_t SSD1963_SetScrollArea         = 0x33;
        static const uint8_t SSD1963_SetTearOff            = 0x34;
        static const uint8_t SSD1963_SetTearOn             = 0x35;
        static const uint8_t SSD1963_SetAddressMode        = 0x36;
        static const uint8_t SSD1963_SetScrollStart        = 0x37;
        static const uint8_t SSD1963_ExitIdleMode          = 0x38;
        static const uint8_t SSD1963_EnterIdleMode         = 0x39;
        static const uint8_t SSD1963_WriteMemoryContinue   = 0x3C;
        static const uint8_t SSD1963_ReadMemoryContinue    = 0x3E;
        static const uint8_t SSD1963_SetTearScanline       = 0x44;
        static const uint8_t SSD1963_GetScanline           = 0x45;
        static const uint8_t SSD1963_ReadDDB               = 0xA1;
        static const uint8_t SSD1963_SetLCDMode            = 0xB0;
        static const uint8_t SSD1963_GetLCDMode            = 0xB1;
        static const uint8_t SSD1963_SetHoriPeriod         = 0xB4;
        static const uint8_t SSD1963_GetHoriPeriod         = 0xB5;
        static const uint8_t SSD1963_SetVertPeriod         = 0xB6;
        static const uint8_t SSD1963_GetVertPeriod         = 0xB7;
        static const uint8_t SSD1963_SetGPIOConf           = 0xB8;
        static const uint8_t SSD1963_GetGPIOConf           = 0xB9;
        static const uint8_t SSD1963_SetGPIOValue          = 0xBA;
        static const uint8_t SSD1963_GetGPIOValue          = 0xBB;
        static const uint8_t SSD1963_SetPostProc           = 0xBC;
        static const uint8_t SSD1963_GetPostProc           = 0xBD;
        static const uint8_t SSD1963_SetPWMConf            = 0xBE;
        static const uint8_t SSD1963_GetPWMConf            = 0xBF;
        static const uint8_t SSD1963_SetLCDGen0            = 0xC0;
        static const uint8_t SSD1963_GetLCDGen0            = 0xC1;
        static const uint8_t SSD1963_SetLCDGen1            = 0xC2;
        static const uint8_t SSD1963_GetLCDGen1            = 0xC3;
        static const uint8_t SSD1963_SetLCDGen2            = 0xC4;
        static const uint8_t SSD1963_GetLCDGen2            = 0xC5;
        static const uint8_t SSD1963_SetLCDGen3            = 0xC6;
        static const uint8_t SSD1963_GetLCDGen3            = 0xC7;
        static const uint8_t SSD1963_SetGPIO0Rop           = 0xC8;
        static const uint8_t SSD1963_GetGPIO0Rop           = 0xC9;
        static const uint8_t SSD1963_SetGPIO1Rop           = 0xCA;
        static const uint8_t SSD1963_GetGPIO1Rop           = 0xCB;
        static const uint8_t SSD1963_SetGPIO2Rop           = 0xCC;
        static const uint8_t SSD1963_GetGPIO2Rop           = 0xCD;
        static const uint8_t SSD1963_SetGPIO3Rop           = 0xCE;
        static const uint8_t SSD1963_GetGPIO3Rop           = 0xCF;
        static const uint8_t SSD1963_SetDBCConf            = 0xD0;
        static const uint8_t SSD1963_GetDBCConf            = 0xD1;
        static const uint8_t SSD1963_SetDBCTh              = 0xD4;
        static const uint8_t SSD1963_GetDBCTh              = 0xD5;
        static const uint8_t SSD1963_SetPLL                = 0xE0;
        static const uint8_t SSD1963_SetPLLMN              = 0xE2;
        static const uint8_t SSD1963_GetPLLMN              = 0xE3;
        static const uint8_t SSD1963_GetPLLStatus          = 0xE4;
        static const uint8_t SSD1963_SetDeepSleep          = 0xE5;
        static const uint8_t SSD1963_SetLShiftFreq         = 0xE6;
        static const uint8_t SSD1963_GetLShiftFreq         = 0xE7;
        static const uint8_t SSD1963_SetPixelDataInterface = 0xF0;
        static const uint8_t SSD1963_GetPixelDataInterface = 0xF1;

        static const uint16_t SSD1963_EMODE = 0x0003;

        static const uint16_t SSD1963_TRI = 0x8000;
        static const uint16_t SSD1963_DFM = 0x4000;
        static const uint16_t SSD1963_BGR = 0x1000;
        static const uint16_t SSD1963_HWM = 0x0200;
        static const uint16_t SSD1963_ORG = 0x0080;
        static const uint16_t SSD1963_ID0 = 0x0000;
        static const uint16_t SSD1963_ID1 = 0x0010;
        static const uint16_t SSD1963_ID2 = 0x0020;
        static const uint16_t SSD1963_ID3 = 0x0030;
        static const uint16_t SSD1963_AM  = 0x0008;

        static const uint16_t   HDP=799;
        static const uint16_t   HT=928;
        static const uint16_t   HPS=46;
        static const uint16_t   LPS=15;
        static const uint8_t    HPW=48;

        static const uint16_t   VDP=479;
        static const uint16_t   VT=525;
        static const uint16_t   VPS=16;
        static const uint16_t   FPS=8;
        static const uint8_t    VPW=16;

        virtual void command(uint16_t cmd);
        virtual void data8(uint8_t cmd);
        virtual void data(uint16_t cmd);
        virtual uint16_t read();
        virtual void initInterface();

    protected:

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
        p32_ioport *port_cs;
        p32_ioport *port_rs;
        p32_ioport *port_wr;
        p32_ioport *port_rd;

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
        uint32_t mask_cs;
        uint32_t mask_rs;
        uint32_t mask_wr;
        uint32_t mask_rd;

        uint8_t bus_width;

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

        uint8_t _profile;


        void setAddrWindow(int x0, int y0, int x1, int y1);

        int _brightness;

        int8_t pins[20];

   public:

        static const int Width = 800; // Don't use this any more!
        static const int Height = 480; // Don't use this any more!

        static const uint8_t TFT7         = 0x01; // 7" TFT Screen
        static const uint8_t VGA640       = 0x02; // 640x480 VGA
        static const uint8_t VGA720       = 0x03; // 720x400 9x16 text mode
        static const uint8_t MIKROMEDIA   = 0x04; // MikroElektronika MikroMedia MX7

        SSD1963(
            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
            uint8_t tft_bus_width = TFTBUS18
        );

        SSD1963(
            uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t tft_bus_width = TFTBUS18
        );

        SSD1963() {}

        void fillScreen(color_t color);
        void setPixel(int x, int y, color_t color);
        void drawVerticalLine(int x, int y, int h, color_t color);
        void drawHorizontalLine(int x, int y, int w, color_t color);
        void fillRectangle(int x, int y, int w, int h, color_t color);
        void setRotation(int r);
        void invertDisplay(boolean i);
        void displayOn();
        void displayOff();

        color_t colorAt(int x, int y);

        void initializeDevice();

        void initializeDevice(uint8_t p) {
            _profile = p;
            initializeDevice();
        }

        virtual void windowData(color_t d);
        virtual void windowData(const color_t *d, int num);
        virtual void openWindow(int, int, int, int);

        void enableBacklight();
        void disableBacklight();
        void setBacklight(int b);

};

class SSD1963_PORTB : public SSD1963 {
    private:
        virtual void command(uint16_t cmd);
        virtual void data8(uint8_t cmd);
        virtual void data(uint16_t cmd);
        virtual uint16_t read();
        virtual void initInterface();

    public:
      SSD1963_PORTB(
         uint8_t rs, uint8_t wr, uint8_t rd, uint8_t cs, uint8_t reset,
         uint8_t tft_bus_width = TFTBUS18
         );

        void windowData(color_t d);
        void windowData(color_t *d, int l);
        void openWindow(int, int, int, int);
        void closeWindow();
};

#endif


