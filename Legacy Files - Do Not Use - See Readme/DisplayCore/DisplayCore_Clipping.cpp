#include <DisplayCore.h>
#include <stdarg.h>

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
void DisplayCore::setClipping(int x0, int y0, int x1, int y1) {
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

boolean DisplayCore::clipToScreen(int &x, int &y, int &w, int &h) {
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

