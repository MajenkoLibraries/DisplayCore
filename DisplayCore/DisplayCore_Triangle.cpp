#include <DisplayCore.h>
#include <stdarg.h>

#include "swap.h"

/*! Draw a triangle
 *  ===============
 *  A simple three lines joined together to form a triangle.  The three points of the triangle are defined
 *  as (x0, y0), (x1, y1) and (x2, y2).  It is drawn in colour (color).
 *
 *  Example:
 *
 *      tft.drawTriangle(40, 10, 60, 30, 20, 30, Color::Cyan);
 */
void DisplayCore::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
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
void DisplayCore::fillTriangle ( int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    int a, b, y, last;

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

