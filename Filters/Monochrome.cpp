#include <Monochrome.h>

uint16_t Monochrome::function(uint16_t col) {

    int r = col >> 11;
    int g = col >> 5 & 0b111111;
    int b = col & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    uint32_t c = (r + g + b) / 3;
    
    return rgb(c, c, c);
}
