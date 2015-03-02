#ifndef _FILTER_ADJUST_HSV_H
#define _FILTER_ADJUST_HSV_H

#include <Filters.h>

class AdjustHSV : public Filter {
    private:
        int16_t _h;
        int16_t _s;
        int16_t _v;
    public:
        AdjustHSV() : Filter() {};
        uint16_t function(uint16_t);
        void adjustHue(int16_t h) { _h = h; };
        void adjustSaturation(int16_t s) { _s = s; };
        void adjustValue(int16_t v) { _v = v; };
};

#endif
