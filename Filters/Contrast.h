#ifndef _FILTER_ADJUST_CONTRAST_H
#define _FILTER_ADJUST_CONTRAST_H

#include <Filters.h>

class Contrast : public Filter {
    private:
        int16_t _c;
    public:
        Contrast() : Filter() {};
        uint16_t function(uint16_t);
        void adjustContrast(int16_t c) { _c = c; };
};

#endif
