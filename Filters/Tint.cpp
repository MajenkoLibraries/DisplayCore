#include <Tint.h>

uint16_t Tint::function(uint16_t col) {

    int r = col >> 11;
    int g = col >> 5 & 0b111111;
    int b = col & 0b11111;

    int tr = _c >> 11;
    int tg = _c >> 5 & 0b111111;
    int tb = _c & 0b11111;

    r <<= 3;
    g <<= 2;
    b <<= 3;

    tr <<= 3;
    tg <<= 2;
    tb <<= 3;

    uint32_t c = (r + g + b) / 3;

    tr = tr * c / 255;
    tg = tg * c / 255;
    tb = tb * c / 255;
    
    return rgb(tr, tg, tb);
}
