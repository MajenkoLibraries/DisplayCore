#include <DisplayCore.h>
#include <stdarg.h>

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
void DisplayCore::drawRectangle(int x, int y, int w, int h, color_t color) {
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
void DisplayCore::fillRectangle(int x, int y, int w, int h, color_t color) {
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
void DisplayCore::fillScreen(color_t color) {
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
void DisplayCore::drawRoundRect(int x, int y, int w, int h, int r, color_t color) {
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
void DisplayCore::fillRoundRect(int x, int y, int w, int h, int r, color_t color) {
    startBuffer();
    // smarter version
    fillRectangle(x+r, y, w-2*r, h, color);

    // draw four corners
    fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
    endBuffer();
}

