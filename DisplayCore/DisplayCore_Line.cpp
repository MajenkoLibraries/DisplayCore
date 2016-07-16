#include <DisplayCore.h>
#include <stdarg.h>

#include "swap.h"

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
void DisplayCore::drawLine(int x0, int y0, int x1, int y1, color_t color) {
    startBuffer();
    int steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int err = dx / 2;
    int ystep;

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
void DisplayCore::drawLine(int x0, int y0, int x1, int y1, int width, color_t color) {
    startBuffer();
    int steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int err = dx / 2;
    int ystep;

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

void DisplayCore::drawHorizontalLine(int x, int y, int w, color_t c) {
    startBuffer();
    for(int z = 0; z < w; z++) {
        setPixel(x + z, y, c);
    }
    endBuffer();
}

void DisplayCore::drawVerticalLine(int x, int y, int h, color_t c) {
    startBuffer();
    for(int z = 0; z < h; z++) {
        setPixel(x, y + z, c);
    }
    endBuffer();
}

