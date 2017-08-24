#include <DisplayCore.h>
#include <stdarg.h>

/*! Draw a circle
 *  =============
 *  This function draws the outline of a circle.  Its center is at (x0, y0), it has radis (r) and is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.drawCircle(50, 50, 20, Color::Red);
 */
void DisplayCore::drawCircle(int x0, int y0, int r, color_t color) {
    startBuffer();
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

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
void DisplayCore::fillCircle(int x0, int y0, int radius, color_t color) {
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

void DisplayCore::drawCircleHelper( int x0, int y0, int r, int cornername, color_t color) {
    startBuffer();
    int f     = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x     = 0;
    int y     = r;

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
void DisplayCore::fillCircleHelper(int x0, int y0, int r, int cornername, int delta, color_t color) {
    startBuffer();
    int f     = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x     = 0;
    int y     = r;

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

