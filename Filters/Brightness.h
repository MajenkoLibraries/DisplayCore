#ifndef _FILTER_ADJUST_BRIGHTNESS_H_
#define _FILTER_ADJUST_BRIGHTNESS_H_

#include <Filters.h>

class Brightness : public Filter {
    private:
        int16_t _b;
    public:
        Brightness() : Filter() {};
        uint16_t function(uint16_t);
        void adjustBrightness(int16_t b) { _b = b; };
};

#endif
