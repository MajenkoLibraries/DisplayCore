#ifndef _FILTER_MONOCHROME_H
#define _FILTER_MONOCHROME_H

#include <Filters.h>

class Monochrome : public Filter {
    private:
        int16_t _c;
    public:
        Monochrome() : Filter() {};
        uint16_t function(uint16_t);
};

#endif
