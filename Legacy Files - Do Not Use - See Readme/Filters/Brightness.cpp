#include <Brightness.h>

color_t Brightness::function(color_t col) {

    int r = col >> 11;
    int g = col >> 5 & 0b111111;
    int b = col & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    r = r + _b;
    g = g + _b;
    b = b + _b;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    
    return rgb(r, g, b);
}
