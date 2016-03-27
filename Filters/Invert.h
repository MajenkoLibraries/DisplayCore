#ifndef _FILTER_INVERT_H
#define _FILTER_INVERT_H

#include <Filters.h>

class Invert : public Filter {
    private:
        int16_t _c;
    public:
        Invert() : Filter() {};
        color_t function(color_t);
};

#endif
