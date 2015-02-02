#include <Invert.h>

uint16_t Invert::function(uint16_t col) {

    int r = col >> 11;
    int g = col >> 5 & 0b111111;
    int b = col & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    r = 255 - r;
    g = 255 - g;
    b = 255 - b;

    return rgb(r, g, b);
}
