#include <Contrast.h>

color_t Contrast::function(color_t col) {

    int r = col >> 11;
    int g = col >> 5 & 0b111111;
    int b = col & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    if (_c < -255) _c = -255;
    if (_c > 255) _c = 255;

    int mul = _c + 255;

    r = r * mul / 255;
    g = g * mul / 255;
    b = b * mul / 255;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    return rgb(r, g, b);
}
