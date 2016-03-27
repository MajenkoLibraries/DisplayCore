#ifndef _GOLDELOX_H
#define _GOLDELOX_H

#include <DisplayCore.h>

class Goldelox : public DisplayCore {
    private:
        Stream *_dev;
        uint16_t _width;
        uint16_t _height;
        uint8_t _reset;
        uint16_t _window_x;
        uint16_t _window_y;
        uint16_t _window_w;
        uint16_t _window_h;

        static const uint16_t MOVE_CURSOR       = 0xFFE4;
        static const uint16_t PUT_CHARACTER     = 0xFFFE;
        static const uint16_t PUT_STRING        = 0x0006;
        static const uint16_t CHARACTER_WIDTH   = 0x0002;
        static const uint16_t CHARACTER_HEIGHT  = 0x0001;
        static const uint16_t TEXT_FG_COLOR     = 0xFF7F;
        static const uint16_t TEXT_BG_COLOR     = 0xFF7E;
        static const uint16_t SET_FONT          = 0xFF7D;
        static const uint16_t TEXT_WIDTH        = 0xFF7C;
        static const uint16_t TEXT_HEIGHT       = 0xFF7B;
        static const uint16_t TEXT_X_GAP        = 0xFF7A;
        static const uint16_t TEXT_Y_GAP        = 0xFF79;
        static const uint16_t TEXT_BOLD         = 0xFF76;
        static const uint16_t TEXT_INVERSE      = 0xFF74;
        static const uint16_t TEXT_ITALIC       = 0xFF75;
        static const uint16_t TEXT_OPACITY      = 0xFF77;
        static const uint16_t TEXT_UNDERLINE    = 0xFF73;
        static const uint16_t TEXT_ATTRIBUTES   = 0xFF72;
        static const uint16_t SET_TEXT_PARMS    = 0xFFE3;

        static const uint16_t CLEAR_SCREEN      = 0xFFD7;
        static const uint16_t CHANGE_COLOR      = 0xFFBE;
        static const uint16_t DRAW_CIRCLE       = 0xFFCD;
        static const uint16_t FILL_CIRCLE       = 0xFFCC;
        static const uint16_t DRAW_LINE         = 0xFFD2;
        static const uint16_t DRAW_RECTANGLE    = 0xFFCF;
        static const uint16_t FILL_RECTANGLE    = 0xFFCE;
        static const uint16_t DRAW_POLYLINE     = 0x0005;
        static const uint16_t DRAW_POLYGON      = 0x0004;
        static const uint16_t DRAW_TRIANGLE     = 0xFFC9;
        static const uint16_t CALCULATE_ORBIT   = 0x0003;
        static const uint16_t PUT_PIXEL         = 0xFFCB;
        static const uint16_t READ_PIXEL        = 0xFFCA;
        static const uint16_t MOVE_ORIGIN       = 0xFFD6;
        static const uint16_t DRAW_MOVE         = 0xFFD4;
        static const uint16_t CLIPPING          = 0xFF6C;
        static const uint16_t SET_CLIP_WINDOW   = 0xFFBF;
        static const uint16_t EXTEND_CLIP       = 0xFFBC;
        static const uint16_t SET_BG            = 0xFF6E;
        static const uint16_t SET_OUTLINE       = 0xFF67;
        static const uint16_t CONTRAST          = 0xFF66;
        static const uint16_t FRAME_DELAY       = 0xFF69;
        static const uint16_t LINE_PATTERN      = 0xFF65;
        static const uint16_t SCREEN_MODE       = 0xFF68;
        static const uint16_t SET_GFX_PARMS     = 0xFFD8;

        static const uint16_t SET_BAUD          = 0x000B;

        static const uint8_t ACK            = 0x06;
        static const uint8_t NAK            = 0x15;

        boolean command(uint16_t *data, uint8_t len);
        

	public:
		Goldelox(Stream *dev, int w, int h) : _dev(dev), _width(w), _height(h), _reset(255) {}
		Goldelox(Stream &dev, int w, int h) : _dev(&dev), _width(w), _height(h), _reset(255) {}
		Goldelox(Stream *dev, int w, int h, uint8_t reset) : _dev(dev), _width(w), _height(h), _reset(reset) {}
		Goldelox(Stream &dev, int w, int h, uint8_t reset) : _dev(&dev), _width(w), _height(h), _reset(reset) {}

        void initializeDevice();
        void displayOn();
        void displayOff();
        void fillScreen(color_t color);
        void setPixel(int x, int y, color_t color);
        void drawLine(int x0, int y0, int x1, int y1, color_t color);
        int getWidth() { return _width; }
        int getHeight() { return _height; }
        void drawVerticalLine(int x, int y, int h, color_t color);
        void drawHorizontalLine(int x, int y, int w, color_t color);
        void drawRectangle(int x, int y, int w, int h, color_t color);
        void fillRectangle(int x, int y, int w, int h, color_t color);
        void setRotation(uint8_t r) {};

        void invertDisplay(boolean i) {};

        void changeBaudRate(uint32_t baud);

        void openWindow(int x, int y, int w, int h);
        void closeWindow();
        void windowData(color_t d);
        void windowData(color_t *d, int l);
};

#endif
