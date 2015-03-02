#ifndef _SSD1963_7_H_
#define _SSD1963_7_H_

#include <DisplayCore.h>

class SSD1963_7 : public DisplayCore {

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

        static const uint8_t _PIN_D0 = 0;
        static const uint8_t _PIN_D1 = 1;
        static const uint8_t _PIN_D2 = 2;
        static const uint8_t _PIN_D3 = 3;
        static const uint8_t _PIN_D4 = 4;
        static const uint8_t _PIN_D5 = 5;
        static const uint8_t _PIN_D6 = 6;
        static const uint8_t _PIN_D7 = 7;
        static const uint8_t _PIN_D8 = 8;
        static const uint8_t _PIN_D9 = 9;
        static const uint8_t _PIN_D10 = 10;
        static const uint8_t _PIN_D11 = 11;
        static const uint8_t _PIN_D12 = 12;
        static const uint8_t _PIN_D13 = 13;
        static const uint8_t _PIN_D14 = 14;
        static const uint8_t _PIN_D15 = 15;
        static const uint8_t _PIN_CS = 16;
        static const uint8_t _PIN_RS = 17;
        static const uint8_t _PIN_WR = 18;
        static const uint8_t _PIN_RD = 19;

        p32_ioport *_port_d0;
        p32_ioport *_port_d1;
        p32_ioport *_port_d2;
        p32_ioport *_port_d3;
        p32_ioport *_port_d4;
        p32_ioport *_port_d5;
        p32_ioport *_port_d6;
        p32_ioport *_port_d7;
        p32_ioport *_port_d8;
        p32_ioport *_port_d9;
        p32_ioport *_port_d10;
        p32_ioport *_port_d11;
        p32_ioport *_port_d12;
        p32_ioport *_port_d13;
        p32_ioport *_port_d14;
        p32_ioport *_port_d15;
        p32_ioport *_port_cs;
        p32_ioport *_port_rs;
        p32_ioport *_port_wr;
        p32_ioport *_port_rd;

        uint32_t _mask_d0;
        uint32_t _mask_d1;
        uint32_t _mask_d2;
        uint32_t _mask_d3;
        uint32_t _mask_d4;
        uint32_t _mask_d5;
        uint32_t _mask_d6;
        uint32_t _mask_d7;
        uint32_t _mask_d8;
        uint32_t _mask_d9;
        uint32_t _mask_d10;
        uint32_t _mask_d11;
        uint32_t _mask_d12;
        uint32_t _mask_d13;
        uint32_t _mask_d14;
        uint32_t _mask_d15;
        uint32_t _mask_cs;
        uint32_t _mask_rs;
        uint32_t _mask_wr;
        uint32_t _mask_rd;

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

        uint8_t _brightness;

        int8_t pins[20];
        inline void command(uint16_t cmd) {
            _port_rs->lat.clr = _mask_rs;
            (cmd & 0x0001) ? _port_d0->lat.set = _mask_d0 : _port_d0->lat.clr = _mask_d0;
            (cmd & 0x0002) ? _port_d1->lat.set = _mask_d1 : _port_d1->lat.clr = _mask_d1;
            (cmd & 0x0004) ? _port_d2->lat.set = _mask_d2 : _port_d2->lat.clr = _mask_d2;
            (cmd & 0x0008) ? _port_d3->lat.set = _mask_d3 : _port_d3->lat.clr = _mask_d3;
            (cmd & 0x0010) ? _port_d4->lat.set = _mask_d4 : _port_d4->lat.clr = _mask_d4;
            (cmd & 0x0020) ? _port_d5->lat.set = _mask_d5 : _port_d5->lat.clr = _mask_d5;
            (cmd & 0x0040) ? _port_d6->lat.set = _mask_d6 : _port_d6->lat.clr = _mask_d6;
            (cmd & 0x0080) ? _port_d7->lat.set = _mask_d7 : _port_d7->lat.clr = _mask_d7;
            (cmd & 0x0100) ? _port_d8->lat.set = _mask_d8 : _port_d8->lat.clr = _mask_d8;
            (cmd & 0x0200) ? _port_d9->lat.set = _mask_d9 : _port_d9->lat.clr = _mask_d9;
            (cmd & 0x0400) ? _port_d10->lat.set = _mask_d10 : _port_d10->lat.clr = _mask_d10;
            (cmd & 0x0800) ? _port_d11->lat.set = _mask_d11 : _port_d11->lat.clr = _mask_d11;
            (cmd & 0x1000) ? _port_d12->lat.set = _mask_d12 : _port_d12->lat.clr = _mask_d12;
            (cmd & 0x2000) ? _port_d13->lat.set = _mask_d13 : _port_d13->lat.clr = _mask_d13;
            (cmd & 0x4000) ? _port_d14->lat.set = _mask_d14 : _port_d14->lat.clr = _mask_d14;
            (cmd & 0x8000) ? _port_d15->lat.set = _mask_d15 : _port_d15->lat.clr = _mask_d15;
            _port_wr->lat.clr = _mask_wr;
            _port_wr->lat.set = _mask_wr;
        }

        inline void data(uint16_t cmd) {
            _port_rs->lat.set = _mask_rs;
            (cmd & 0x0001) ? _port_d0->lat.set = _mask_d0 : _port_d0->lat.clr = _mask_d0;
            (cmd & 0x0002) ? _port_d1->lat.set = _mask_d1 : _port_d1->lat.clr = _mask_d1;
            (cmd & 0x0004) ? _port_d2->lat.set = _mask_d2 : _port_d2->lat.clr = _mask_d2;
            (cmd & 0x0008) ? _port_d3->lat.set = _mask_d3 : _port_d3->lat.clr = _mask_d3;
            (cmd & 0x0010) ? _port_d4->lat.set = _mask_d4 : _port_d4->lat.clr = _mask_d4;
            (cmd & 0x0020) ? _port_d5->lat.set = _mask_d5 : _port_d5->lat.clr = _mask_d5;
            (cmd & 0x0040) ? _port_d6->lat.set = _mask_d6 : _port_d6->lat.clr = _mask_d6;
            (cmd & 0x0080) ? _port_d7->lat.set = _mask_d7 : _port_d7->lat.clr = _mask_d7;
            (cmd & 0x0100) ? _port_d8->lat.set = _mask_d8 : _port_d8->lat.clr = _mask_d8;
            (cmd & 0x0200) ? _port_d9->lat.set = _mask_d9 : _port_d9->lat.clr = _mask_d9;
            (cmd & 0x0400) ? _port_d10->lat.set = _mask_d10 : _port_d10->lat.clr = _mask_d10;
            (cmd & 0x0800) ? _port_d11->lat.set = _mask_d11 : _port_d11->lat.clr = _mask_d11;
            (cmd & 0x1000) ? _port_d12->lat.set = _mask_d12 : _port_d12->lat.clr = _mask_d12;
            (cmd & 0x2000) ? _port_d13->lat.set = _mask_d13 : _port_d13->lat.clr = _mask_d13;
            (cmd & 0x4000) ? _port_d14->lat.set = _mask_d14 : _port_d14->lat.clr = _mask_d14;
            (cmd & 0x8000) ? _port_d15->lat.set = _mask_d15 : _port_d15->lat.clr = _mask_d15;
            _port_wr->lat.clr = _mask_wr;
            _port_wr->lat.set = _mask_wr;
        }


	public:
        /*! The width of the screen is 800 pixels */
        static const uint16_t Width      = 800;
        /*! The height of the screen is 480 pixels */
        static const uint16_t Height     = 480;

		SSD1963_7(
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11,
            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
            uint8_t cs, uint8_t rs, uint8_t wr, uint8_t rd);

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn();
        void displayOff();

        void initializeDevice();

        void windowData(uint16_t d);
        void openWindow(uint16_t, uint16_t, uint16_t, uint16_t);

        void enableBacklight();
        void disableBacklight();
        void setBacklight(uint8_t b);

};

#endif
