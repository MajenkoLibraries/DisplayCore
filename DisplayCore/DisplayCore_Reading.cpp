#include <DisplayCore.h>
#include <stdarg.h>

/*! Get the colour at a location
 *  ============================
 *  Returns the colour at (x,y) as seen by the screen.
 *
 *  Example:
 *
 *      unsigned int color = tft.colorAt(100, 100);
 */
color_t DisplayCore::colorAt(int x, int y) {
    return bgColor;
}

void DisplayCore::getRectangle(int x, int y, int w, int h, color_t *buf) {
    for (int i = 0; i < w*h; i++) {
        buf[i] = bgColor;
    }
}

