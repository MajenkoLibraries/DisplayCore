#ifndef _PICADILLO_H_
#define _PICADILLO_H_

#include <DisplayCore.h>
#include <AnalogTouch.h>

class Picadillo : public DisplayCore
{
	public:
        static const uint8_t opWrite = 0;
        static const uint8_t opRead = 1;

        static const uint8_t cacheInvalid = 0;
        static const uint8_t cacheClean = 1;
        static const uint8_t cacheDirty = 2;

        static const uint8_t cacheDimension = 4;
        uint16_t _cacheData[(1<<cacheDimension) * (1<<cacheDimension)];
        uint8_t _cacheState;

        int16_t _cacheX;
        int16_t _cacheY;

        uint8_t _lastOp;

        void loadCacheBlock(int16_t x, int16_t y);
        void flushCacheBlock();

        static const uint16_t Width      = 320;
        static const uint16_t Height     = 480;


		Picadillo() : DisplayCore(), _lastOp(Picadillo::opWrite), _brightness(255) {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void setAddrWindowRead(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn();  
        void displayOff();  
        uint16_t colorAt(int16_t x, int16_t y);

        void initializeDevice();

        void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void windowData(uint16_t d);
        void windowData(uint16_t *d, uint32_t l);
        void closeWindow();

        void inline writeCommand(uint16_t);
        void inline writeData(uint16_t);
		
        void enableBacklight();
        void disableBacklight();
        void setBacklight(uint8_t b);

	protected:
		uint8_t colstart, rowstart;
        uint8_t _brightness;
};

#endif
