#ifndef _FILTER_INVERT_H
#define _FILTER_INVERT_H

#include <Filters.h>

class Invert : public Filter {
    private:
        int16_t _c;
    public:
        Invert() : Filter() {};
        uint16_t function(uint16_t);
};

#endif
