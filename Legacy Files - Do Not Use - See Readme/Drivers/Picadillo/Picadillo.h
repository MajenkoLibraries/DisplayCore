#ifndef _PICADILLO_H
#define _PICADILLO_H

#ifdef _BOARD_PICADILLO_35T_

#include <DisplayCore.h>
#include <AnalogTouch.h>

class Picadillo : public DisplayCore
{
    private:
        static const uint8_t HX8357_EXIT_SLEEP_MODE            = 0x11;
        static const uint8_t HX8357_SET_DISPLAY_OFF            = 0x28;
        static const uint8_t HX8357_SET_DISPLAY_ON             = 0x29;
        static const uint8_t HX8357_SET_COLUMN_ADDRESS         = 0x2A;
        static const uint8_t HX8357_SET_PAGE_ADDRESS           = 0x2B;
        static const uint8_t HX8357_WRITE_MEMORY_START         = 0x2C;
        static const uint8_t HX8357_READ_MEMORY_START          = 0x2E;
        static const uint8_t HX8357_SET_TEAR_ON                = 0x35;
        static const uint8_t HX8357_SET_ADDRESS_MODE           = 0x36;
        static const uint8_t HX8357_SET_PIXEL_FORMAT           = 0x3A;
        static const uint8_t HX8357_WRITE_MEMORY_CONTINUE      = 0x3C;
        static const uint8_t HX8357_READ_MEMORY_CONTINUE       = 0x3E;
        static const uint8_t HX8357_SET_INTERNAL_OSCILLATOR    = 0xB0;
        static const uint8_t HX8357_SET_POWER_CONTROL          = 0xB1;
        static const uint8_t HX8357_SET_DISPLAY_MODE           = 0xB4;
        static const uint8_t HX8357_SET_VCOM_VOLTAGE           = 0xB6;
        static const uint8_t HX8357_ENABLE_EXTENSION_COMMAND   = 0xB9;
        static const uint8_t HX8357_SET_PANEL_DRIVING          = 0xC0;
        static const uint8_t HX8357_SET_PANEL_CHARACTERISTIC   = 0xCC;
        static const uint8_t HX8357_SET_GAMMA_CURVE            = 0xE0;
        static const uint8_t HX8357_GETSCAN                    = 0x45;

        static const uint8_t HX8357_INVON                      = 0x21;
        static const uint8_t HX8357_INVOFF                     = 0x20;
        static const uint8_t HX8357_DISPLAYOFF                 = 0x28;
        static const uint8_t HX8357_DISPLAYON                  = 0x29;

	public:
        static const uint8_t opWrite = 0;
        static const uint8_t opRead = 1;

        static const int Width      = 320;
        static const int Height     = 480;


		Picadillo() : DisplayCore(), _brightness(255) {}

		void setAddrWindow(int x0, int y0, int x1, int y1);
		void setAddrWindowRead(int x0, int y0, int x1, int y1);
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
        void getRectangle(int x, int y, int w, int h, color_t *buf);

        void initializeDevice();

        void openWindow(int x0, int y0, int x1, int y1);
        void windowData(color_t d);
        void windowData(color_t *d, int l);
        void closeWindow();

        void writeCommand(uint16_t);
        void writeData(uint16_t);
        uint16_t readData(boolean cont = false);
        uint8_t readByte(boolean fresh = false);
		
        void enableBacklight();
        void disableBacklight();
        void setBacklight(int b);

        int getScanLine();

	protected:
		uint8_t colstart, rowstart;
        int _brightness;
};

#endif
#endif
