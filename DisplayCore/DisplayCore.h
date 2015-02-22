#ifndef _DISPLAY_CORE_H
#define _DISPLAY_CORE_H

#if ARDUINO >= 100
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#define RGB(r,g,b) ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

#include <stdint.h>

#include <Color.h>
#include <DefaultFont.h>

typedef struct {
    uint8_t linesPerCharacter;
    uint8_t bytesPerLine;
    uint8_t startGlyph;
    uint8_t endGlyph;
    uint8_t bitsPerPixel;
} FontHeader;

struct coord {
    uint16_t x;
    uint16_t y;
};

typedef struct {
    float x;
    float y;
    float z;
} point3d;

typedef struct {
    union {
        uint16_t value;
        struct {
            unsigned r:5;
            unsigned g:6;
            unsigned b:5;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed)) Color565;

extern uint16_t rgb(uint32_t c);
extern uint16_t rgb(uint8_t r, uint8_t g, uint8_t b);

class DisplayCore : public Print
{
    public:
        DisplayCore();
        virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        virtual void drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        virtual void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        virtual void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        virtual void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
        virtual void drawRGB(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h);
        virtual void drawRGBA(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, uint16_t trans);
        virtual void setCursor(int16_t x, int16_t y);
        virtual void setCursorX(int16_t x);
        virtual void setCursorY(int16_t y);
        virtual int16_t getCursorX();
        virtual int16_t getCursorY();
        virtual int16_t getCursor(boolean x);
        virtual void setTextColor(uint16_t c);
        virtual void setTextColor(uint16_t fg, uint16_t bg);
        virtual uint16_t getTextColor();
        virtual void invertTextColor();
        virtual void setTextWrap(boolean w);
        virtual uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
        virtual void setFont(const uint8_t *f);
        virtual void translateCoordinates(int16_t *x, int16_t *y);
        virtual void drawBezier(
            int16_t x0, int16_t y0,
            int16_t x1, int16_t y1,
            int16_t x2, int16_t y2,
            int16_t x3, int16_t y3,
            int resolution,
            uint16_t color
        );

        virtual void fillBezier(
            int16_t x0, int16_t y0,
            int16_t x1, int16_t y1,
            int16_t x2, int16_t y2,
            int16_t x3, int16_t y3,
            int resolution,
            uint16_t color
        );

        virtual void fillScreen(uint16_t color);
        virtual void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);


        void setClipping(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
        void clearClipping();

        /*! \name Pure virtual functions
         *  These are all functions that must be implemented in a TFT driver in order for it to function.
         */
         /**@{*/
    
        /*! Set screen rotation
         *  ===================
         *  This rotates the screen. Value is between 0 and 3, for 0°, 90°, 180° or 270°.
         *
         *  Example:
         *
         *      tft.setRotation(1);
         */
        virtual void setRotation(uint8_t rotation) = 0;
        /*! Draw a pixel
         *  ============
         *  A pixel, coloured (color) is drawn at (x,y).
         *  
         *  Example:
         *  
         *      tft.drawPixel(100, 100, Color::Green);
         */
        virtual void setPixel(int16_t x, int16_t y, uint16_t color) = 0;
        /*! Draw a horizontal line
         *  ======================
         *  A horizontal line of width (w) is drawn from point (x,y) in colour (color);
         * 
         *  Example:
         *
         *      tft.drawHorizontalLine(10, 10, 50, Color::Blue);
         */
        virtual void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        /*! Draw a vertical line
         *  ====================
         *  A vertical line of height (h) is drawn from point (x,y) in colour (color);
         * 
         *  Example:
         *
         *      tft.drawVerticalLine(10, 10, 50, Color::Blue);
         */
        virtual void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        /*! Initialize the display
         *  ======================
         *  The display is configured and made ready to work.  This function *must* be called
         *  before anything can happen on the screen, and it *should* be called before any other function.
         *
         *  Example:
         *
         *      tft.initializeDevice();
         */
        virtual void initializeDevice() = 0;
        /*! Turn on the display
         *  ===================
         *  Enable the video output of the display (if supported).
         *
         *  Example:
         *
         *      tft.displayOn();
         */
        virtual void displayOn() = 0;
        /*! Turn off the display
         *  ====================
         *  Disable the video output of the display (if supported).
         *
         *  Example:
         *
         *      tft.displayOff();
         */
        virtual void displayOff() = 0;
        /*! Invert the display colours
         *  ==========================
         *  All colours become reversed.  Black becomes white, red becomes cyan, etc.
         *
         *  Example:
         *
         *      tft.invertDisplay(true);
         */
        virtual void invertDisplay(boolean i) = 0;
         /**@}*/
        virtual uint16_t stringWidth(const char *text);
        virtual uint16_t stringHeight(const char *text);

        virtual void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        virtual void windowData(uint16_t d);
        virtual void windowData(uint16_t *d, uint32_t l);
        virtual void closeWindow();

        virtual uint16_t bgColorAt(int16_t x, int16_t y);
        virtual uint16_t colorAt(int16_t x, int16_t y);
#if ARDUINO >= 100
        size_t write(uint8_t c);
#else
        void write(uint8_t c);
#endif

        /*! The text cursor X position */
        int16_t cursor_x;
        /*! The text cursor Y position */
        int16_t cursor_y;
        /*! Whether or not text wrapping is enabled */
        boolean wrap;
        /*! Text foreground colour */
        uint16_t textcolor;
        /*! Text background colour */
        uint16_t textbgcolor;
        /*! Width of the TFT screen */
        uint16_t _width;
        /*! Height of the TFT screen */
        uint16_t _height;
        /*! Current rotation */
        uint8_t rotation;
        uint8_t drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);

        /*! Get screen width
         *  ================
         *  Returns the width (in pixels) of the screen.
         *
         *  Example:
         *
         *    int width = tft.getWidth();
         */
        virtual uint16_t getWidth() { return _width; };
        /*! Get screen height
         *  =================
         *  Returns the height (in pixels) of the screen.
         *
         *  Example:
         *
         *    int height = tft.getHeight();
         */
        virtual uint16_t getHeight() { return _height; };

        point3d rgb2xyz(uint16_t c);
        point3d xyz2lab(point3d c);
        float deltaE(point3d labA, point3d labB);
        uint32_t deltaOrth(uint16_t c1, uint16_t c2);
        static uint32_t rgb2hsv(uint16_t rgb);
        static uint16_t hsv2rgb(uint32_t hsv);

        void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
        void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

        uint16_t mix(uint16_t a, uint16_t b, uint8_t pct);

        boolean clipToScreen(int16_t &x, int16_t &y, int16_t &w, int16_t &h);

        void fatalError(const char *title, const char *message);

        void setFontScaleX(uint8_t sx);
        void setFontScaleY(uint8_t sy);

        uint32_t color2rgb(uint16_t c);


        int16_t _clip_x0;
        int16_t _clip_x1;
        int16_t _clip_y0;
        int16_t _clip_y1;

    protected:
        /*! A pointer to the currently selected font table */
        const uint8_t *font;
        /*! The current X scaling factor of the font */
        uint8_t font_scale_x;
        /*! The current Y scaling factor of the font */
        uint8_t font_scale_y;

    private:
        uint16_t winx0;
        uint16_t winy0;
        uint16_t winx1;
        uint16_t winy1;
        uint16_t winpx;
        uint16_t winpy;

};

class Touch {
    public:
        /*! Create a new touch screen object
         *  ================================
         *  This takes a pointer to a communication device, and the width and height of the touch screen.
         */
        Touch(uint16_t w, uint16_t h) : _width(w), _height(h) {}
        /*! Initialize the device
         *  =====================
         *  This configures and enables the touch screen device. It should be called before any other touch screen
         *  functions.
         */
        virtual void initializeDevice() = 0;
        /*! Get X coordinate
         *  ================
         *  This returns the X coordinate of the current touch position.
         */
        virtual uint16_t x() = 0;
        /*! Get Y coordinate
         *  ================
         *  This returns the Y coordinate of the current touch position.
         */
        virtual uint16_t y() = 0;
        /*! Get pressed status
         *  ==================
         *  Returns true if the touch screen is pressed, false otherwise.
         */
        virtual boolean isPressed() = 0;
        /*! Calculate the touch pressure
         *  ============================
         *  For touch screens that can calculate how hard you are pressing them, this returns the pressure value.  For others it returns 0.
         *
         *  Example:
         *
         *      int pressure = ts.pressure();
         */
        virtual uint16_t pressure() { return 0; }
        /*! Set rotation
         *  ============
         *  This sets the screen orientation of the touch screen.  It should be set to the same as the
         *  rotation used for the screen.
         */
        virtual void setRotation(uint8_t r) = 0;

        /*! Sample the touch screen
         *  =======================
         *  This performs a sampling of the touch screen to get the current coordinates and touch status.
         *  It should be called regularly to update the current touch screen data.
         */
        virtual void sample() = 0;

        virtual void scaleX(float x) { _scale_x = x; }
        virtual void scaleY(float y) { _scale_y = y; }
        virtual void offsetX(float x) { _offset_x = x; }
        virtual void offsetY(float y) { _offset_y = y; }

        float _scale_x;
        float _scale_y;
        int16_t _offset_x;
        int16_t _offset_y;

    protected:
        /*! The width of the toush screen in pixels */
        uint16_t _width;  
        /*! The height of the touch screen in pixels */
        uint16_t _height; 

};

class Filter;

class Filter {
    protected:
        Filter *_next;
    public:
        Filter() : _next(NULL) {};
        uint16_t process(uint16_t);
        virtual uint16_t function(uint16_t) = 0;
        void chain(Filter &f) { _next = &f; }
        void chain(Filter *f) { _next = f; }
        void endChain() { _next = NULL; }
};

class Image : public DisplayCore {
    protected:
        Filter *_filter;
    public:
        static const uint8_t MirrorH = 0x01;
        static const uint8_t MirrorV = 0x02;
        static const uint8_t Rotate180 = 0x03;

        Image() : _filter(NULL) {};

        virtual uint16_t getWidth() { return _width; }
        virtual uint16_t getHeight() { return _height; }

        virtual void draw(DisplayCore *dev, int16_t x, int16_t y) = 0;
        virtual void draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t) = 0;
        virtual void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform) = 0;
        virtual void drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) = 0;

        void draw(DisplayCore &dev, int16_t x, int16_t y) { draw(&dev, x, y); }
        void draw(DisplayCore &dev, int16_t x, int16_t y, uint16_t t) { draw(&dev, x, y, t); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform) { drawTransformed(&dev, x, y, transform); }
        void drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) { drawTransformed(&dev, x, y, t); }

        void setFilter(Filter &f) { _filter = &f; };
        void removeFilter() { _filter = NULL; };

        void setRotation(uint8_t r) {}
        void setPixel(int16_t x, int16_t y, uint16_t c) {}
        void initializeDevice() {}
        void displayOn() {}
        void displayOff() {}
        void invertDisplay(boolean i) {}

        uint16_t _width;
        uint16_t _height;
};


#endif


