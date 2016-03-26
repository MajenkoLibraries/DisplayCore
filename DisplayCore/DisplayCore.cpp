#include <DisplayCore.h>
#include <stdarg.h>

/*! Utility function to convert a 24-bit RGB value into a 16-bit RGB value. */
uint16_t rgb(uint32_t c) {
    uint8_t r = c >> 16;
    uint8_t g = c >> 8;
    uint8_t b = c;

    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    return ((r << 11) | (g << 5) | b);
}

/*! Utility function to convert three component colour values (R, G, B) into a 16-bit RGB value.*/
uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    return ((r << 11) | (g << 5) | b);
}

/*! The default constructor takes no parameters. It creates a blank screen class with no communication abilities. */
DisplayCore::DisplayCore() {
    cursor_y = cursor_x = 0;
    textcolor = 0xFFFF;
    textbgcolor = 0;
    wrap = true;
    font = Fonts::Default;
}

/*! \name Drawing Functions
 *  These functions draw pretty shapes on the screen.
 */


/**@{*/

/*! Draw a circle
 *  =============
 *  This function draws the outline of a circle.  Its center is at (x0, y0), it has radis (r) and is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.drawCircle(50, 50, 20, Color::Red);
 */
void DisplayCore::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    startBuffer();
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    setPixel(x0, y0+r, color);
    setPixel(x0, y0-r, color);
    setPixel(x0+r, y0, color);
    setPixel(x0-r, y0, color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        setPixel(x0 + x, y0 + y, color);
        setPixel(x0 - x, y0 + y, color);
        setPixel(x0 + x, y0 - y, color);
        setPixel(x0 - x, y0 - y, color);
        setPixel(x0 + y, y0 + x, color);
        setPixel(x0 - y, y0 + x, color);
        setPixel(x0 + y, y0 - x, color);
        setPixel(x0 - y, y0 - x, color);
    }
    endBuffer();
}

/*! Draw a filled circle
 *  ====================
 *  This function draws a filled circle.  It is highly optimised to get the maximum possible speed out of it.
 *
 *  Like the drawCircle function it centers the circle at (x0, y0), has radius (radius) and is drawn in (color).
 *
 *  Example:
 *
 *      tft.fillCircle(50, 50, 20, Color::Red);
 */
void DisplayCore::fillCircle(int16_t x0, int16_t y0, int16_t radius, uint16_t color) {
    startBuffer();
    int32_t r2 = radius * radius;
    for (int y1 = 0-radius; y1 <= 0; y1++) {
        int32_t y12 = y1 * y1;
        for (int x1 = 0-radius; x1 <= 0; x1++) {
            if (x1 * x1 + y12 <= r2) {
                drawHorizontalLine(x0 + x1, y0 + y1, 2 * (0-x1), color);
                drawHorizontalLine(x0 + x1, y0 - y1, 2 * (0-x1), color);
                break;
            }
        }
    }
    endBuffer();
}

static void inline swap(int16_t &i0, int16_t &i1) {
    int i2 = i0;
    i0 = i1;
    i1 = i2;
}

/*! Draw a straight line
 *  ====================
 *  This function uses Bresenham's algorithm to draw a straight line.  The line
 *  starts at coordinates (x0, y0) and extends to coordinates (x1, y1).  The line
 *  is drawn in color (color).
 *
 *  Example:
 *
 *      tft.drawLine(10, 10, 40, 60, Color::Green);
 */
// bresenham's algorithm - thx wikpedia
void DisplayCore::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    startBuffer();
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            setPixel(y0, x0, color);
        } else {
            setPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
    endBuffer();
}

/*! Draw a thick straight line
 *  ====================
 *  This function uses Bresenham's algorithm to draw a straight line.  The line
 *  starts at coordinates (x0, y0) and extends to coordinates (x1, y1).  The line
 *  is drawn in color (color).
 *
 *  Thickness is added using the highly inefficient "cheating" method of drawing
 *  circles instead of pixels.
 *
 *  Example:
 *
 *      tft.drawLine(10, 10, 40, 60, 4, Color::Green);
 */
// bresenham's algorithm - thx wikpedia
void DisplayCore::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int width, uint16_t color) {
    startBuffer();
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            fillCircle(y0, x0, width / 2, color);
        } else {
            fillCircle(x0, y0, width / 2, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
    endBuffer();
}

/*! Set clipping boundaries
 *  =======================
 *  The clipping boundaries limit where a pixel can be drawn on the screen. It allows
 *  you to define an area where primitives will be drawn within and any portion outside
 *  the clipping area will be discarded.
 *
 *  Example:
 *
 *      setClipping(100, 100, 200, 200);
 */
void DisplayCore::setClipping(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    _clip_x0 = x0;
    _clip_x1 = x1;
    _clip_y0 = y0;
    _clip_y1 = y1;
}

/*! Clear clipping boundaries
 *  =========================
 *
 *  Remove the clipping boundary imposed by setClipping().
 *
 *  Example:
 * 
 *      clearClipping();
 */
void DisplayCore::clearClipping() {
    _clip_x0 = 0;
    _clip_y0 = 0;
    _clip_x1 = getWidth() - 1;
    _clip_y1 = getHeight() - 1;
}

void DisplayCore::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
    startBuffer();
    for(int z = 0; z < w; z++) {
        setPixel(x + z, y, c);
    }
    endBuffer();
}

void DisplayCore::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t c) {
    startBuffer();
    for(int z = 0; z < h; z++) {
        setPixel(x, y + z, c);
    }
    endBuffer();
}

/*! Draw a rectangle
 *  ================
 *  This function uses accelerated line drawing routines if available.  It draws a rectangle on the
 *  screen.  The upper-left corner of the rectangle is at (x, y), and it extends to the right and down
 *  for a distance of (w) and (h) pixels respectively.  It is drawn in colour (color).
 *
 *  Example:
 * 
 *      tft.drawRectangle(10, 10, 200, 300, Color::Blue);
 */
void DisplayCore::drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    startBuffer();
    drawHorizontalLine(x, y, w, color);
    drawHorizontalLine(x, y+h-1, w, color);
    drawVerticalLine(x, y, h, color);
    drawVerticalLine(x+w-1, y, h, color);
    endBuffer();
}

/*! Draw a rectangle
 *  ================
 *  This function draws a filled rectangle on the screen.  
 *  The upper-left corner of the rectangle is at (x, y), and it extends to the right and down
 *  for a distance of (w) and (h) pixels respectively.  It is drawn in colour (color).
 *
 *  Example:
 * 
 *      tft.fillRectangle(10, 10, 200, 300, Color::Blue);
 *
 *  It is expected that actual screen drivers will override this function with a high speed
 *  optimized function.
 */
void DisplayCore::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    startBuffer();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            setPixel(x + j, y + i, color);
        }
    }
    endBuffer();
}

/*! Fill the screen with a colour
 *  =============================
 *  This function fills the entire screen with a solid colour.
 * 
 *  Example: 
 *
 *      tft.fillScreen(Color::Black);
 */
void DisplayCore::fillScreen(uint16_t color) {
    startBuffer();
    bgColor = color;
    fillRectangle(0, 0, getWidth(), getHeight(), color);
    endBuffer();
}

/*! Draw a rounded rectangle
 *  ========================
 *  A rounded rectangle is a normal rectangle but with the corners rounded off.
 *  It is drawn with the upper-left corner at (x,y) and a width of (w) and height of (h).
 *  The corners are rounded off at a radius of (r) pixels, and it is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.drawRoundRect(10, 10, 100, 50, 4, Color::Yellow);
 */
void DisplayCore::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    startBuffer();
    // smarter version
    drawHorizontalLine(x+r  , y    , w-2*r, color); // Top
    drawHorizontalLine(x+r  , y+h-1, w-2*r, color); // Bottom
    drawVerticalLine(  x    , y+r  , h-2*r, color); // Left
    drawVerticalLine(  x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    drawCircleHelper(x+r    , y+r    , r, 1, color);
    drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
    endBuffer();
}

/*! Draw a filled rounded rectangle
 *  ===============================
 *  A rounded rectangle is a normal rectangle but with the corners rounded off.
 *  It is drawn with the upper-left corner at (x,y) and a width of (w) and height of (h).
 *  The corners are rounded off at a radius of (r) pixels, and it is drawn (and filled) in colour (color).
 *
 *  Example:
 *
 *      tft.fillRoundRect(10, 10, 100, 50, 4, Color::Yellow);
 */
void DisplayCore::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    startBuffer();
    // smarter version
    fillRectangle(x+r, y, w-2*r, h, color);

    // draw four corners
    fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
    endBuffer();
}

/*! Draw a triangle
 *  ===============
 *  A simple three lines joined together to form a triangle.  The three points of the triangle are defined
 *  as (x0, y0), (x1, y1) and (x2, y2).  It is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.drawTriangle(40, 10, 60, 30, 20, 30, Color::Cyan);
 */
void DisplayCore::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    startBuffer();
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
    endBuffer();
}

/*! Draw a filled triangle
 *  ======================
 *  A simple three lines joined together to form a triangle.  The three points of the triangle are defined
 *  as (x0, y0), (x1, y1) and (x2, y2).  It is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.fillTriangle(40, 10, 60, 30, 20, 30, Color::Cyan);
 */
void DisplayCore::fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    int16_t a, b, y, last;

    startBuffer();

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        swap(y0, y1); swap(x0, x1);
    }
    if (y1 > y2) {
        swap(y2, y1); swap(x2, x1);
    }
    if (y0 > y1) {
        swap(y0, y1); swap(x0, x1);
    }

    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        drawHorizontalLine(a, y0, b-a+1, color);
        endBuffer();
        return;
    }

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        if(a > b) swap(a,b);
        drawHorizontalLine(a, y, b-a+1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    for(; y<=y2; y++) {
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        if(a > b) swap(a,b);
        drawHorizontalLine(a, y, b-a+1, color);
    }
    endBuffer();
}

/**@}*/

/*! \name Image drawing
 *  These routines are used for drawing basic bitmap images to the screen.
 */
/**@{*/
/*! Draw a 1-bit bitmap image
 *  =========================
 *  A 1-bit bitmap image is a byte array where each byte represents 8 contiguous pixels.
 *  The image is rendered to the screen as naturally transparent, with set bits rendered in (color)
 *  and unset bits skipped.  The image is rendered with the upper left corner at (x,y) and the image
 *  is (w,h) in size.
 *
 *  Example:
 *
 *      const byte letterA[] = {
 *          0b00000000,
 *          0b00111100,
 *          0b01000010,
 *          0b01000010,
 *          0b01111110,
 *          0b01000010,
 *          0b01000010,
 *          0b00000000};
 *      tft.drawBitmap(100, 100, letterA, 8, 8, Color::Red);
 */
void DisplayCore::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    int16_t i, j, byteWidth = (w + 7) / 8;

    startBuffer();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                setPixel(x+i, y+j, color);
            }
        }
    }
    endBuffer();
}

/*! Draw an RGB (565) image
 *  =======================
 *  A 565 raw RGB image is rendered to the screen at (x,y).  The image data is stored
 *  as an array of 16-bit values, and is (w,h) pixels in size.
 *
 *  Example:
 *
 *    tft.drawRGB(10, 30, myImage, 16, 16);
 */
void DisplayCore::drawRGB(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    startBuffer();
    int16_t i, j;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            setPixel(x+i, y+j, bitmap[j * w + i]);
        }
    }
    endBuffer();
}

/*! Draw a transparent RGB (565) image
 *  ==================================
 *  A 565 raw RGB image is rendered to the screen at (x,y).  The image data is stored
 *  as an array of 16-bit values, and is (w,h) pixels in size.  Any pixels with colour
 *  (trans) are skipped.
 *
 *  Example:
 *
 *    tft.drawRGBA(10, 30, myImage, 16, 16, Color::Black);
 */
void DisplayCore::drawRGBA(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, uint16_t trans) {
    startBuffer();
    int16_t i, j;
    uint16_t col;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            col = bitmap[j * w + i];
            if (col != trans) {
                setPixel(x+i, y+j, col);
            }
        }
    }
    endBuffer();
}
/**@}*/

/*! \name Text handing functions
 *  These are functions used for dealing with text and printing of strings to the screen.
 */
/**@{*/

/*! Calculate the width of a string
 *  ===============================
 *  The total width of a string of characters is calculated by examining the width of each
 *  character using the current font in turn and accumulating the total width.
 *
 *  Example:
 *
 *      int width = tft.stringWidth("The quick brown fox jumped over the lazy dog");
 */
uint16_t DisplayCore::stringWidth(const char *text) {
    uint16_t w = 0;
    if (font == NULL) {
        return 0;
    }
    FontHeader *header = (FontHeader *)font;

    for (const char *t = text; *t; t++) {
        char c = *t;
        if (c < header->startGlyph) {
            if (c >= 'A' && c <= 'Z') {
                c += ('a' - 'A');
            }
        }
        if (c > header->endGlyph) {
            if (c >= 'a' && c <= 'z') {
                c -= ('a' - 'A');
            }
        }
        if (c >= header->startGlyph && c <= header->endGlyph) {
            uint8_t co = c - header->startGlyph;
            uint32_t charstart = (co * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
            uint8_t charwidth = font[charstart++];
            w += charwidth;
        }
    }
    return w;
}
        
/*! Calculate the height of a string
 *  ================================
 *  As fonts are all fixed height, this just returns the height of the
 *  currently selected font in pixels.
 *
 *  Example:
 *
 *      int height = stringHeight("The quick brown fox jumped over the lazy dog");
 */
uint16_t DisplayCore::stringHeight(const char *text) {
    if (font == NULL) {
        return 0;
    }
    FontHeader *header = (FontHeader *)font;

    return header->linesPerCharacter;
}
        

#if ARDUINO >= 100
size_t DisplayCore::write(const uint8_t *buffer, size_t size) {
    startBuffer();
    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }
    endBuffer();
    return size;
}
#else
void DisplayCore::write(const uint8_t *buffer, size_t size) {
    startBuffer();
    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }
    endBuffer();
}
#endif

/*! Write a character to the screen
 *  ===============================
 *  This writes a single character to the screen at the current cursor position.  It is used by (among other
 *  things) the print routines for rendering strings.
 *
 *  Example:
 *
 *      tft.write('Q');
 */
#if ARDUINO >= 100
size_t DisplayCore::write(uint8_t c) {
    if (font == NULL) {
        return 0;
    }
#else
void DisplayCore::write(uint8_t c) {
    if (font == NULL) {
        return;
    }
#endif
    FontHeader *header = (FontHeader *)font;

    if (c == '\n') {
        cursor_y += header->linesPerCharacter;
        cursor_x = 0;
    } else if (c == '\r') {
        // skip em
    } else {
        if (c < header->startGlyph) {
            if (c >= 'A' && c <= 'Z') {
                c += ('a' - 'A');
            }
        }
        if (c > header->endGlyph) {
            if (c >= 'a' && c <= 'z') {
                c -= ('a' - 'A');
            }
        }
        if (c >= header->startGlyph && c <= header->endGlyph) {
            uint8_t co = c - header->startGlyph;
            uint32_t charstart = (co * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
            uint8_t charwidth = font[charstart++];
            if (wrap && (cursor_x > (getWidth() - charwidth))) {
                cursor_y += header->linesPerCharacter;
                cursor_x = 0;
            }
            cursor_x += drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor);
        }
    }
#if ARDUINO >= 100
    return 1;
#endif
}

/*! Draw a character
 *  ================
 *  This is the heart of the text handling.  It takes the current font, locates the right character (c)
 *  data, and renders it to the screen at the specified (x,y) location.  It is drawn in colour (color), and
 *  the background is filled in (bg).  If (bg) and (color) are equal then the background pixels are
 *  skipped.
 *
 *  Example:
 *
 *      tft.drawChar(30, 30, 'Q', Color::Red, Color::Blue);
 */
uint8_t DisplayCore::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg) {

    if (font == NULL) {
        return 0;
    }

    FontHeader *header = (FontHeader *)font;

    if (c < header->startGlyph || c > header->endGlyph) {
        return 0;
    }

    startBuffer();

    c = c - header->startGlyph;

    // Start of this character's data is the character number multiplied by the
    // number of lines in a character (plus one for the character width) multiplied
    // by the number of bytes in a line, and then offset by 4 for the header.
    uint32_t charstart = (c * ((header->linesPerCharacter * header->bytesPerLine) + 1)) + sizeof(FontHeader); // Start of character data
    uint8_t charwidth = font[charstart++]; // The first byte of a block is the width of the character

    uint8_t nCols = 1 << header->bitsPerPixel;
    uint32_t bitmask = nCols - 1;
    uint16_t cmap[nCols];

    if (bg != color) {
        for (uint8_t i = 0; i < nCols; i++) {
            cmap[i] = mix(bg, color, 255 * i / bitmask);
        }

        openWindow(x, y, charwidth, header->linesPerCharacter);

        for (int8_t lineNumber = 0; lineNumber < header->linesPerCharacter; lineNumber++ ) {
            uint8_t lineData = 0;

            int8_t bitsLeft = -1;
            uint8_t byteNumber = 0;


            for (int8_t pixelNumber = 0; pixelNumber < charwidth; pixelNumber++) {
                if (bitsLeft <= 0) {
                    bitsLeft = 8;
                    lineData = font[charstart + (lineNumber * header->bytesPerLine) + (header->bytesPerLine - byteNumber - 1)];
                    byteNumber++;
                }
                uint32_t pixelValue = lineData & bitmask;

                windowData(cmap[pixelValue]);
    
                lineData >>= header->bitsPerPixel;
                bitsLeft -= header->bitsPerPixel;
            }
        }
        closeWindow();
    } else {

        for (int8_t lineNumber = 0; lineNumber < header->linesPerCharacter; lineNumber++ ) {
            uint8_t lineData = 0;

            int8_t bitsLeft = -1;
            uint8_t byteNumber = 0;


            for (int8_t pixelNumber = 0; pixelNumber < charwidth; pixelNumber++) {
                if (bitsLeft <= 0) {
                    bitsLeft = 8;
                    lineData = font[charstart + (lineNumber * header->bytesPerLine) + (header->bytesPerLine - byteNumber - 1)];
                    byteNumber++;
                }
                uint32_t pixelValue = lineData & bitmask;

                // If we have some kind of foreground colour...
                if (pixelValue > 0) {
                    // If it is at full opacity...
                    if (pixelValue == bitmask) {
                        setPixel(x + pixelNumber, y + lineNumber, color);
                    // Otherwise mix or fade the colour...
                    } else {
                        uint16_t bgc = colorAt(x+pixelNumber, y+lineNumber);
                        setPixel(x + pixelNumber, y + lineNumber, mix(bgc, color, 255 * pixelValue / bitmask));
                    }
                }
                lineData >>= header->bitsPerPixel;
                bitsLeft -= header->bitsPerPixel;
            }
        }
    }
    endBuffer();
    return charwidth;
}

/*! Set the text cursor
 *  ===================
 *  All future printing will happen from the pixel (x,y).
 *
 *  Example:
 *
 *      tft.setCursor(0, 100);
 */
void DisplayCore::setCursor(int16_t x, int16_t y) {
    cursor_x = x;
    cursor_y = y;
}

/*! Set the text X cursor
 *  =====================
 *  All future printing will happen from the X pixel (x).
 *
 *  Example:
 *
 *      tft.setCursorX(100);
 */
void DisplayCore::setCursorX(int16_t x) {
    cursor_x = x;
}

/*! Set the text Y cursor
 *  =====================
 *  All future printing will happen from the Y pixel (y).
 *
 *  Example:
 *
 *      tft.setCursorY(100);
 */
void DisplayCore::setCursorY(int16_t y) {
    cursor_y = y;
}

/*! Get X Cursor 
 *  ============
 *  Returns the current X position of the text cursor.
 *
 *  Example:
 *
 *      int x = tft.getCursorX();
 */
int16_t DisplayCore::getCursorX() {
    return cursor_x;
}

/*! Get Y Cursor 
 *  ============
 *  Returns the current Y position of the text cursor.
 *
 *  Example:
 *
 *      int y = tft.getCursorY();
 */
int16_t DisplayCore::getCursorY() {
    return cursor_y;
}

/*! Get Text Cursor 
 *  ============
 *  Returns the ether the current X or Y position of the text cursor.  A parameter of `true`
 *  requests the X coordinate, otherwise the Y coordinate is returned.
 *
 *  Example:
 *
 *      int x = tft.getCursor(true);
 *      int y = tft.getCursor(false);
 */
int16_t DisplayCore::getCursor(boolean x) {
    if( x )
        return cursor_x;
    return cursor_y;
}

/*! Set the text foreground colour
 *  ==============================
 *  Sets the foreground colour of all future printing to (c).
 *
 *  Example:
 *
 *      tft.setTextColor(Color::Magenta);
 */
void DisplayCore::setTextColor(uint16_t c) {
    textcolor = c;
}

/*! Sets both foreground and background colour
 *  ==========================================
 *  Sets both the foreground and the background colours of all
 *  future printing.  If the foreground and background colours match
 *  the background will be transparent.
 *
 *  Example:
 *
 *      tft.setTextColor(Color::Red, Color::Blue);
 */
void DisplayCore::setTextColor(uint16_t fg, uint16_t bg) {
   textcolor = fg;
   textbgcolor = bg;
    bgColor = bg;
}

/*! Invert the text colours
 *  =======================
 *  The foreground becomes the background, and the background becomes the foreground.
 *
 *  Example:
 *
 *      tft.invertTextColor();
 */
void DisplayCore::invertTextColor( ){
	setTextColor( textbgcolor, textcolor );
}

/*! Enable or disable text wrapping
 *  ===============================
 *  With text wrapping enabled, when text reaches the right-hand edge of the
 *  screen it wraps around back to the left on the next line down.  This function
 *  alows you to enable (true) or disable (false) this functionality.  By default
 *  text wrapping is enabled.
 *
 *  Example:
 * 
 *      tft.setTextWrap(false);
 */
void DisplayCore::setTextWrap(boolean w) {
  wrap = w;
}

/*! Set the current font
 *  ====================
 *  The current font is set to the font provided.  A font is a byte array of data with
 *  metric information embedded in it.
 *
 *  Example:
 * 
 *      tft.setFont(Fonts::Ubuntu12);
 */
void DisplayCore::setFont(const uint8_t *f) {
    font = f;
}

/*! Get the current foreground colour
 *  =================================
 *  Returns the currently selected foreground colour.
 *
 *  Example:
 *
 *      unsigned int color = tft.getTextColor();
 */
uint16_t DisplayCore::getTextColor() {
    return textcolor;
}

/**@}*/

/*! \name Colour handling
 *  These functions are all related to manipulating colours in one way or another.
 */

/**@{*/
/*! Convert RGB to 565 colour
 *  =========================
 *  This function takes an RGB triplet (r, g, b) and converts it into
 *  a 16-bit 565 colour.
 *
 *  Example:
 *
 *      unsigned int yellow = tft.color565(255, 255, 0);
 */
uint16_t DisplayCore::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

/*! Get the 3D colour space of a colour
 *  ===================================
 *  This function converts a 565 colour into a 3D coordinate
 *  in RGB colour space (X, Y, Z).
 *
 *  Example:
 *
 *      point3d color = tft.rgb2xyz(Color::Cyan);
 */
point3d DisplayCore::rgb2xyz(uint16_t rgb) {
    uint8_t red = rgb >> 11;
    uint8_t green = rgb >> 5 & 0b111111;
    uint8_t blue = rgb & 0b11111;

    point3d xyz;

    red = red << 3;
    green = green << 2;
    blue = blue << 3;

    float r = red / 255.0;
    float g = green / 255.0;
    float b = blue / 255.0;

    if (r > 0.04045) {
        r  = pow(((r + 0.055) / 1.055), 2.4);
    } else {
        r  = r / 12.92;
    }

    if (g > 0.04045) {
        g  = pow(((g + 0.055) / 1.055), 2.4);
    } else {
        g  = g / 12.92;
    }

    if (b > 0.04045) {
        b  = pow(((b + 0.055) / 1.055), 2.4);
    } else {
        b  = b / 12.92;
    }

    r = r * 100.0;
    g = g * 100.0;
    b = b * 100.0;

    xyz.x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    xyz.y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    xyz.z = r * 0.0193 + g * 0.1192 + b * 0.9505;
    return xyz;
}

/*! Convert a 3D colour space point to LAB
 *  ======================================
 *  Calculate the LAB colour space value of a 3D point in
 *  RGB colour space.
 *
 *  Example:
 *
 *      point3d labcolor = tft.xyz2lab(color3d);
 */
point3d DisplayCore::xyz2lab(point3d xyz) {
    point3d lab;

    float x = xyz.x / 100.0;
    float y = xyz.y / 100.0;
    float z = xyz.z / 100.0;
    
    if (x > 0.008856) {
        x = pow(x, 1.0/3.0);
    } else {
        x = (7.787 * x) + (16.0 / 116.0);
    }

    if (y > 0.008856) {
        y = pow(y, 1.0/3.0);
    } else {
        y = (7.787 * y) + (16.0 / 116.0);
    }

    if (z > 0.008856) {
        z = pow(z, 1.0/3.0);
    } else {
        z = (7.787 * z) + (16.0 / 116.0);
    }

    lab.x = (116.0 * y) - 16.0;
    lab.y = 500.0 * (x - y);
    lab.z = 200.0 * (y - z);
    return lab;
}

/*! Calculate the DeltaE between two LAB colours
 *  ============================================
 *  This function takes two LAB colours and calculates
 *  the difference (delta) between them.
 *
 *  Example:
 *
 *      float delta = tft.deltaE(colorA, colorB);
 */
float DisplayCore::deltaE(point3d labA, point3d labB) {
    return sqrt(
        (pow(labA.x - labB.x, 2.0))
        + (pow(labA.y - labB.y, 2.0))
        + (pow(labA.z - labB.z, 2.0))
    );
}

/*! Calculate the orthogonal difference between colours
 *  ===================================================
 *  Two RGB 565 colours are compared and the orthogonal distance
 *  between them (as HSV colours) is calculated.
 *
 *  Example:
 *
 *      unsigned long delta = tft.deltaOrth(Color::Yellow, Color::Orange);
 */
uint32_t DisplayCore::deltaOrth(uint16_t c1, uint16_t c2) {
    uint32_t hsv1 = rgb2hsv(c1);
    uint32_t hsv2 = rgb2hsv(c2);

    uint8_t h1 = (hsv1 >> 16) & 0xFF;
    uint8_t h2 = (hsv2 >> 16) & 0xFF;
    uint8_t s1 = (hsv1 >> 8) & 0xFF;
    uint8_t s2 = (hsv2 >> 8) & 0xFF;
    uint8_t v1 = hsv1 & 0xFF;
    uint8_t v2 = hsv2 & 0xFF;

    int32_t hd = h1 - h2;
    int32_t sd = s1 - s2;
    int32_t vd = v1 - v2;

    uint32_t sos = (hd * hd) + (sd * sd) + (vd * vd);
    return sos;
}

/*! Convert a 565 RGB colour to HSV
 *  ===============================
 *  Calculate the HSV values for a 565 16-bit RGB colour.
 *
 *  Example:
 *
 *      unsigned long hsv = tft.rgb2hsv(Color::Green);
 */
uint32_t DisplayCore::rgb2hsv(uint16_t rgb)
{
    uint8_t r = rgb >> 11;
    uint8_t g = rgb >> 5 & 0b111111;
    uint8_t b = rgb & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    uint8_t h, s, v;

    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    v = rgbMax;
    if (v == 0)
    {
        h = 0;
        s = 0;
        return (h << 16) | (s << 8) | v;
    }

    s = 255 * long(rgbMax - rgbMin) / v;
    if (s == 0)
    {
        h = 0;
        return (h << 16) | (s << 8) | v;
    }

    if (rgbMax == r)
        h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    else if (rgbMax == g)
        h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    else
        h = 171 + 43 * (r - g) / (rgbMax - rgbMin);

    return (h << 16) | (s << 8) | v;
}

uint16_t DisplayCore::hsv2rgb(uint32_t hsv) {
    int hue = (hsv >> 16) & 0xFF;
    int sat = (hsv >> 8) & 0xFF;
    int val = hsv & 0xFF;
    unsigned int H_accent = hue/43;
    unsigned int bottom = ((255 - sat) * val)>>8;
    unsigned int top = val;
    unsigned char rising  = ((top-bottom)  *(hue%43   )  )  /  43  +  bottom;
    unsigned char falling = ((top-bottom)  *(43-hue%43)  )  /  43  +  bottom;

    int r = 0;
    int g = 0;
    int b = 0;
   
    switch(H_accent) {
        case 0:
                r = top;
                g = rising;
                b = bottom;
        break;
       
        case 1:
                r = falling;
                g = top;
                b = bottom;
        break;
       
        case 2:
                r = bottom;
                g = top;
                b = rising;
        break;
       
        case 3:
                r = bottom;
                g = falling;
                b = top;
        break;
       
        case 4:
                r = rising;
                g = bottom;
                b = top;
        break;
       
        case 5:
                r = top;
                g = bottom;
                b = falling;
        break;
    }
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    return rgb(r, g, b);
}



/*! Get the colour at a location
 *  ============================
 *  Returns the colour at (x,y) as seen by the screen.
 *
 *  Example:
 *
 *      unsigned int color = tft.colorAt(100, 100);
 */
uint16_t DisplayCore::colorAt(int16_t x, int16_t y) {
    return bgColor;
}

void DisplayCore::getRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *buf) {
    for (int16_t i = 0; i < w*h; i++) {
        buf[i] = bgColor;
    }
}

/*! Mix two colours together
 *  ========================
 *  Returns a new colour that is the mixing of the two provided colours.
 *
 *  Example:
 *
 *      unsigned int yellow = tft.mix(Color::Red, Color::Green);
 */
uint16_t DisplayCore::mix(uint16_t a, uint16_t b, uint8_t pct) {
    Color565 col_a;
    Color565 col_b;
    Color565 col_out;
    col_a.value = a;
    col_b.value = b;
    uint32_t temp;
    temp = (((int32_t)col_a.r * (255-pct)) / 255) + (((uint32_t)col_b.r * pct) / 255);
    col_out.r = temp;
    temp = (((int32_t)col_a.g * (255-pct)) / 255) + (((uint32_t)col_b.g * pct) / 255);
    col_out.g = temp;
    temp = (((int32_t)col_a.b * (255-pct)) / 255) + (((uint32_t)col_b.b * pct) / 255);
    col_out.b = temp;
    return col_out.value;
}

/**@}*/

/*! \name Window operations
 *  The window system is what makes some of the fastest operations available.
 */
/**@{*/
/*! Open a window
 *  =============
 *  Opens the rectangle defined by (x0,y0) to (x1,y1) as a raw data window.
 *
 *  Example:
 *  
 *      tft.openWindow(0, 0, 100, 100);
 */
void DisplayCore::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    winx0 = x0;
    winy0 = y0;
    winx1 = x0 + x1;
    winy1 = y0 + y1;
    winpx = 0;
    winpy = 0;
    startBuffer();
}

/*! Send pixel data to the window 
 *  =============================
 *  Sends the raw pixel data for one pixel to the currently opened window.
 *
 *  Example:
 *
 *      tft.windowData(Color::Red);
 */
void DisplayCore::windowData(uint16_t d) {
    setPixel(winx0 + winpx, winy0 + winpy, d);
    winpx++;
    if ((winx0 + winpx) >= winx1) {
        winpx = 0;
        winpy++;
    }
    if ((winy0 + winpy) >= winy1) {
        winpy = 0;
    }
}

/*! Send a block of pixel data to the window 
 *  ========================================
 *  The array of pixel data (*d) ans size (l) is dumped verbatim
 *  to the currently opened window.
 *
 *  Example:
 *
 *      tft.windowData(myData, 1000);
 */
void DisplayCore::windowData(uint16_t *d, uint32_t l) {
    for (uint32_t i = 0; i < l; i++) {
        windowData(d[i]);
    }
}

/*! Close the window
 *  ================
 *  Close the currently opened window and return to normal
 *  drawing operations.
 *
 *  Example:
 *
 *      tft.closeWindow();
 */

void DisplayCore::closeWindow() {
    endBuffer();
}

/**@}*/


/*! \name Helper Functions
 *  These are functions used by other functions to do their work.  They may be useful in other situations as well, but they won't be as fully documented.
 */
/**@{*/
boolean DisplayCore::clipToScreen(int16_t &x, int16_t &y, int16_t &w, int16_t &h) {
    if (x < 0) {
        w += x;
        x = 0;
        if (w <= 0) {
            return false;
        }
    }

    if (y < 0) {
        h += y;
        y = 0;
        if (h <= 0) {
            return false;
        }
    }

    if (x >= getWidth()) {
        return false;
    }

    if (y >= getHeight()) {
        return false;
    }

    if (x + w >= getWidth()) {
        w = getWidth()-x;
        if (w <= 0) {
            return false;
        }
    }

    if (y + h >= getHeight()) {
        h = getHeight()-y;
        if (h <= 0) {
            return false;
        }
    }
    return true;
}


/*! This is a helper function.  It is used to draw portions of a circle. */

void DisplayCore::drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
    startBuffer();
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            setPixel(x0 + x, y0 + y, color);
            setPixel(x0 + y, y0 + x, color);
        } 
        if (cornername & 0x2) {
            setPixel(x0 + x, y0 - y, color);
            setPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            setPixel(x0 - y, y0 + x, color);
            setPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            setPixel(x0 - y, y0 - x, color);
            setPixel(x0 - x, y0 - y, color);
        }
    }
    endBuffer();
}

/*! This is a helper function.  It is used to draw segments of a filled circle. */
void DisplayCore::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    startBuffer();
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
            drawVerticalLine(x0+x, y0-y, 2*y+0+delta, color);
            drawVerticalLine(x0+y, y0-x, 2*x+0+delta, color);
        }
        if (cornername & 0x2) {
            drawVerticalLine(x0-x, y0-y, 2*y+0+delta, color);
            drawVerticalLine(x0-y, y0-x, 2*x+0+delta, color);
        }
    }
    endBuffer();
}

#ifndef max
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#endif

/*! Display a fatal error
 *  =====================
 *  Used internally by various functions and libraries to display
 *  a fatal error message.  This is an error that cannot be recovered
 *  from, so the program stops here.
 *
 *  Example:
 *
 *      tft.fatalError("MEMORY ERROR", "Unable to allocate space for objects");
 */
void DisplayCore::fatalError(const char *title, const char *message) {
    int16_t width = getWidth();
    int16_t height = getHeight();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x + (y & 1)) & 1) {
                setPixel(x, y, Color::Black);
            }
        }
    }
    setFont(Fonts::Default);
    int sx = 1;
    int16_t swidth = stringWidth((char *)message);
    int16_t twidth = stringWidth((char *)title);
    uint16_t mwidth = max(swidth, twidth);
    while (mwidth < width) {
        sx++;
        swidth = stringWidth((char *)message);
        twidth = stringWidth((char *)title);
        mwidth = max(swidth, twidth);
    }
    sx--;
    swidth = stringWidth((char *)message);
    int16_t sheight = stringHeight((char *)message);
    twidth = stringWidth((char *)title);
    mwidth = max(swidth, twidth);

    int16_t strw2 = swidth / 2;
    int16_t ttlw2 = twidth / 2;
    int16_t maxw2 = mwidth / 2;
    int16_t scrw2 = width / 2;
    int16_t scrh2 = height / 2;
    fillRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Black);
    fillRoundRect(scrw2 - maxw2 - 10, scrh2 - sheight - 10, mwidth + 20, sheight * 2 + 20, 10, Color::Red);
    drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Red);

    setTextColor(Color::Black, Color::Red);
    setCursor(scrw2 - ttlw2, scrh2 - sheight - 1);
    print(title);
    setTextColor(Color::Black, Color::Red);
    setCursor(scrw2 - strw2, scrh2 + 1);
    print(message);

    while(1) {
        delay(500);
        drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Black);
        drawRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Red);
        delay(500);
        drawRoundRect(scrw2 - maxw2 - 12, scrh2 - sheight - 12, mwidth + 24, sheight * 2 + 24, 12, Color::Red);
        drawRoundRect(scrw2 - maxw2 - 14, scrh2 - sheight - 14, mwidth + 28, sheight * 2 + 28, 12, Color::Black);
    }
}

uint16_t Filter::process(uint16_t incol) {
    uint16_t outcol = function(incol);
    if (_next != NULL) {
        return _next->process(outcol);
    }
    return outcol;
}




/**@}*/

void DisplayCore::translateCoordinates(int16_t *x, int16_t *y) {
    int16_t t;
    switch (rotation) {
        case 1:
            t = *x;
            *x = getWidth() - *y;
            *y = t;
            break;
        case 2:
            *x = getWidth() - *x;
            *y = getHeight() - *y;
            break;
        case 3:
            t = *x;
            *x = *y;
            *y = getHeight() - t;
            break;
    }
}

uint32_t DisplayCore::color2rgb(uint16_t rgb) {
    uint8_t red = rgb >> 11;
    uint8_t green = rgb >> 5 & 0b111111;
    uint8_t blue = rgb & 0b11111;

    red = red << 3;
    green = green << 2;
    blue = blue << 3;

    return (red << 16) | (green << 8) | (blue);
}

void DisplayCore::drawBezier(
    int16_t x0, int16_t y0,
    int16_t x1, int16_t y1,
    int16_t x2, int16_t y2,
    int16_t x3, int16_t y3,
    int resolution,
    uint16_t color
) {
    startBuffer();

    boolean first = true;
    float points = 1.0/(float)resolution;
    float t = 0.0, sx = 0, sy = 0;
    float ex, ey;


    for (t = 0.0; t < 1.0; t += points)
    {
        ex = pow (1-t, 3) * x0 + 3 * t * pow (1-t, 2) * x1 +
                   3 * pow (t, 2) * (1-t) * x2 + pow (t, 3) * x3;
 
        ey = pow (1-t, 3) * y0 + 3 * t * pow (1-t, 2) * y1 +
                   3 * pow (t, 2) * (1-t) * y2 + pow (t, 3) * y3;

        if (!first) {
            drawLine(sx, sy, ex, ey, color);
        }
        first = false;
        sx = ex;
        sy = ey;
    }
    drawLine(sx, sy, x3, y3, color);
    endBuffer();
}

void DisplayCore::fillBezier(
    int16_t x0, int16_t y0,
    int16_t x1, int16_t y1,
    int16_t x2, int16_t y2,
    int16_t x3, int16_t y3,
    int resolution,
    uint16_t color
) {

    startBuffer();

    boolean first = true;
    float points = 1.0/(float)resolution;
    float t = 0.0, sx = 0, sy = 0;
    float ex, ey;


    for (t = 0.0; t < 1.0; t += points)
    {
        ex = pow (1-t, 3) * x0 + 3 * t * pow (1-t, 2) * x1 +
                   3 * pow (t, 2) * (1-t) * x2 + pow (t, 3) * x3;
 
        ey = pow (1-t, 3) * y0 + 3 * t * pow (1-t, 2) * y1 +
                   3 * pow (t, 2) * (1-t) * y2 + pow (t, 3) * y3;

        if (!first) {
            fillTriangle(sx, sy, ex, ey, x0, y0, color);
        }
        first = false;
        sx = ex;
        sy = ey;
    }
    fillTriangle(x0, y0, sx, sy, x3, y3, color);
    endBuffer();
}

#if defined(__PIC32MX__) || defined(__PIC32MZ__)
p32_ioport *DisplayCore::getPortInformation(uint8_t pin, uint32_t *mask) {
    uint32_t portno = digitalPinToPort(pin);
    if (portno == NOT_A_PIN) {
        return NULL;
    }
    if (mask != NULL) {
        *mask = digitalPinToBitMask(pin);
    }
    return (p32_ioport *)portRegisters(portno);
}
#endif

void Widget::setValue(int v) {
    _value = v;
    _redraw = true;
}

int Widget::getValue() {
    return _value;
}

void Widget::handleTouch() {
    if (!_touch) {
        return;
    }

    if (!isEnabled()) {
        return;
    }

    boolean pressed = _ts->isPressed();

    if (pressed != _dbPressed) {
        _dbPressed = pressed;
        if (!_dbPressed) {
            _dbStart = 0;
        } else {
            _dbStart = millis();
        }
    }

    if (_dbStart == 0) {
        pressed = false;
    } else {
        if (millis() - _dbStart > 50) {
            pressed = true;
        } else {
            pressed = false;
        }
    }
        

    if (pressed) {
        _tx = _ts->x();
        _ty = _ts->y();
    }

    boolean inBounds = (
        (_tx >= (_x + _sense_x)) && (_tx < (_x + _sense_x + _sense_w)) &&
        (_ty >= (_y + _sense_y)) && (_ty < (_y + _sense_y + _sense_h))
    );

    // Press

    if ((pressed && inBounds) && (!_active)) {
        _active = true;
        _st = millis();
        _sx = _tx - _x;
        _sy = _ty - _y;
        _rt = millis();
        _rp = 0;
        _redraw = true;
      //  draw(_dev, _x, _y);

        if (_press != NULL) {
            Event e = {this, _sx, _sy, _sx, _sy, EVENT_PRESS};
            _rx = _sx;
            _ry = _sy;
            _press(&e);
        }
    }

    // Release
    if ((!pressed) && (_active)) {
        _active = false;
        _et = millis();
        _ex = _tx - _x;
        _ey = _ty - _y;
        _redraw = true;
     //   draw(_dev, _x, _y);

        if (_release != NULL) {
            _rx = _ex;
            _ry = _ey;
            Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_RELEASE};
            _release(&e);
        }

        if (((_et - _st) > 10) && ((_et - _st) < 2000)) {
            if (_tap != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_TAP};
                _tap(&e);
            }
        }
    }

    if ((pressed && !inBounds) && _active) {
        _active = false;
        _redraw = true;
        //draw(_dev, _x, _y);
    }
    // Drag
    if ((pressed && inBounds) && _active) {
        _ex = _tx - _x;
        _ey = _ty - _y;
        if (_sx != _ex || _sy != _ey) {
            if (_drag != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_DRAG};
                _drag(&e);
            }
        }
        // Key repeat

        if (_rp == 0) {
            _rt = millis();
            _rp = 1;
            if (_repeat != NULL) {
                _rx = _ex;
                _ry = _ey;
                Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                _repeat(&e);
            }
        } else if (_rp == 1) {
            if (millis() - _rt >= 1000) {
                _rt = millis();
                _rp = 2;
                _rc = 0;
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
            }

        } else if (_rp == 2) {
            if (millis() - _rt >= 200) {
                _rt = millis();
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
                _rc++;
                if (_rc == 10) {
                    _rp = 3;
                }
            }
        } else if (_rp == 3) {
            if (millis() - _rt >= 50) {
                _rt = millis();
                if (_repeat != NULL) {
                    _rx = _ex;
                    _ry = _ey;
                    Event e = {this, _ex, _ey, _ex - _sx, _ex - _sy, EVENT_REPEAT};
                    _repeat(&e);
                }
            }
        }

        _sx = _ex;
        _sy = _ey;
    }
}

void Widget::draw(DisplayCore *dev, int16_t x, int16_t y, uint16_t t) { draw(dev, x, y); }
void Widget::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform) { draw(dev, x, y); }
void Widget::drawTransformed(DisplayCore *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) { draw(dev, x, y); }
void Widget::draw(DisplayCore &dev, int16_t x, int16_t y) { draw(&dev, x, y); }
void Widget::draw(DisplayCore &dev, int16_t x, int16_t y, uint16_t t) { draw(&dev, x, y, t); }
void Widget::drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform) { drawTransformed(&dev, x, y, transform); }
void Widget::drawTransformed(DisplayCore &dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) { drawTransformed(&dev, x, y, t); }

void Widget::render() {
    handleTouch();
    if (_redraw) {
        draw(_dev, _x, _y);
        _redraw = false;
    }
}

void Widget::redraw() {
    _redraw = true;
}

uint16_t DisplayCore::getWidth() {
    return _width;
}

uint16_t DisplayCore::getHeight() {
    return _height;
}

void Widget::setEnabled(boolean e) {
    if (e != _enabled) {
        _redraw = true;
    }
    _enabled = e;
}

boolean Widget::isEnabled() {
    return _enabled;
}

boolean Widget::isActive() {
    return _active;
}

Form::Form(int num...) {
    va_list args;
    _size = num;
    _list = (Widget **)malloc(sizeof(Widget) * _size);
    va_start(args, num);
    for (int i = 0; i < _size; i++) {
        _list[i] = va_arg(args, Widget *);
    }

}

Form::~Form() {
    free(_list);
}

void Form::render() {
    for (int i = 0; i < _size; i++) {
        _list[i]->render();
    }
}

void Form::redraw() {
    for (int i = 0; i < _size; i++) {
        _list[i]->redraw();
    }
}

void Form::onPress(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onPress(func);
    }
}

void Form::onRelease(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onRelease(func);
    }
}

void Form::onTap(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onTap(func);
    }
}

void Form::onDrag(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onDrag(func);
    }
}

void Form::onRepeat(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onRepeat(func);
    }
}

