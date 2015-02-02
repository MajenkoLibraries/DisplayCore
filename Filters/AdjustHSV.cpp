#include <AdjustHSV.h>

uint16_t AdjustHSV::function(uint16_t col) {
    uint32_t hsv = DisplayCore::rgb2hsv(col);
    int h = ((hsv >> 16) & 0xFF);
    int s = ((hsv >> 8) & 0xFF);
    int v = (hsv & 0xFF);
    h += _h;
    s += _s;
    v += _v;

    while (h < 0) h += 256;
    while (h > 255) h -= 256;
    if (s < 0) s = 0;
    if (s > 255) s = 255;
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    col = DisplayCore::hsv2rgb((h << 16) | (s << 8) | v);
    return col;
}
